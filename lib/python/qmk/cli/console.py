"""Acquire debugging information from usb hid devices

cli implementation of https://www.pjrc.com/teensy/hid_listen.html

State machine is implemented as follows:

     +-+
     +-+                                                More Data?
      |                                              +------------+
      |                                              |            |
+-----+-------+      +-----------------+       +-----+------+     |
|             |      |                 |       |            |     |
|   Search    +----->+     Connect     +------>+   Read     +<----+
|             |      |                 |       |            |
+-----+-------+      +-----------------+       +------+-----+
      ^                                               |
      |               Disconnect/Error?               |
      +-----------------------------------------------+
"""
import hid
import queue
import time
from platform import platform
from threading import Thread

from milc import cli

IS_LINUX = 'linux' in platform().lower()


class ConsoleMessages(queue.Queue):
    """Process and print console messages from devices.
    """
    def print_message(self, message):
        """Nicely format and print a message.
        """
        cli.echo('{fg_blue}%(vendor_id)04x:%(product_id)04x:%(pathstr)s{fg_reset}: %(text)s' % message)

    def run_forever(self):
        while True:
            try:
                self.print_message(self.get())

            except KeyboardInterrupt:
                break

            except Exception as e:
                cli.log.error("Uncaught exception: %s: %s", e.__class__.__name__, e)
                cli.log.exception(e)


class MonitorDevice(object):
    def __init__(self, console, hid_device):
        self.console = console
        hid_device['pathstr'] = hid_device['path'].decode('utf-8')
        self.hid_device = hid_device
        self.device = hid.Device(path=hid_device['path'])
        self.current_line = ''

        print()
        cli.log.info('Listening to {fg_cyan}%s %s{fg_reset} ({fg_blue}%04x:%04x{fg_reset}) on {fg_blue}%s{fg_reset}:', hid_device['manufacturer_string'], hid_device['product_string'], hid_device['vendor_id'], hid_device['product_id'], hid_device['path'].decode())

    def read(self, size, encoding='ascii', timeout=1):
        """Read size bytes from the device.
        """
        return self.device.read(size, timeout).decode(encoding)

    def read_line(self):
        """Read from the device's console until we get a \n.
        """
        while '\n' not in self.current_line:
            self.current_line += self.read(32)

        lines = self.current_line.split('\n', 1)
        self.current_line = lines[1]

        return lines[0]

    def on_exception(self, e):
        cli.log.error('Exception: %s: %s: %s', self.__class__.__name__, e.__class__.__name__, e)
        cli.log.exception(e)

    def run_forever(self):
        while True:
            self.console.put({
                **self.hid_device,
                'text': self.read_line()
            })


class StateMachine(queue.Queue):
    def __init__(self, console):
        self.console = console

        super().__init__()

    def transition(self, func, *args, delay=None, **kwargs):
        if delay:
            time.sleep(delay)
        self.put((func, args, kwargs))

    def on_exception(self, e):
        cli.log.error('Exception: %s: %s', e.__class__.__name__, e)
        cli.log.exception(e)
        self.transition(self.on_exception, e)

    def run_forever(self):
        self.transition(self.search)

        while True:
            try:
                f, args, kwargs = self.get()
                f(*args, **kwargs)
            except KeyboardInterrupt:
                break
            except BaseException as e:
                self.on_exception(e)

    def is_console_hid(self, hid_device):
        return hid_device['usage_page'] == 0xFF31 and hid_device['usage'] == 0x0074

    def has_3rd_interface(self, hid_device):
        return hid_device['interface_number'] == 2

    def is_filtered_device(self, hid_device):
        name = "%04x:%04x" % (hid_device['vendor_id'], hid_device['product_id'])
        return name.lower().startswith(cli.args.device.lower())

    def find_devices(self):
        hid_devices = hid.enumerate()
        devices = list(filter(self.is_console_hid, hid_devices))

        if not devices:
            # Some versions of linux don't report usage and usage_page. In that
            # case we fallback to devices that have a 3rd interface
            devices = filter(self.has_3rd_interface, hid_devices)

        if cli.args.device:
            devices = filter(self.is_filtered_device, devices)

        return devices

    def search(self):
        print('.', end='', flush=True)

        found = list(self.find_devices())
        selected = found[cli.args.index] if found[cli.args.index:] else None

        if selected:
            self.transition(self.on_connect, selected, delay=0.5)
        else:
            self.transition(self.search, delay=1)

    def on_connect(self, hid_device):
        monitor = MonitorDevice(self.console, hid_device)
        self.transition(monitor.run_forever, delay=1)

    def on_exception(self, e):
        cli.log.error('Exception: %s: %s: %s', self.__class__.__name__, e.__class__.__name__, e)
        cli.log.exception(e)
        cli.log.info('Device disconnected.')
        print('Waiting for new device..', end="", flush=True)
        self.transition(self.search)


def list_devices(sm):
    cli.log.info('Available devices:')

    for dev in sm.find_devices():
        cli.log.info("  %04x:%04x %s %s", dev['vendor_id'], dev['product_id'], dev['manufacturer_string'], dev['product_string'])


@cli.argument('-d', '--device', help='device to select - uses format <pid>:<vid>[:<index>].')
@cli.argument('-i', '--index', default=0, help='device index to select.')
@cli.argument('-l', '--list', arg_only=True, action='store_true', help='List available hid_listen devices.')
@cli.subcommand('Acquire debugging information from usb hid devices.', hidden=False if cli.config.user.developer else True)
def console(cli):
    """Acquire debugging information from usb hid devices
    """
    console = ConsoleMessages()
    sm = StateMachine(console)

    if cli.args.list:
        return list_devices(sm)

    print('Waiting for device..', end="", flush=True)
    sm_t = Thread(target=sm.run_forever, daemon=True)
    sm_t.start()
    console.run_forever()
