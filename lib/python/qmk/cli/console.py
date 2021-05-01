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

from milc import cli

IS_LINUX = 'linux' in platform().lower()


class ConsoleMessages(queue.Queue):
    """Process and print console messages from devices.
    """
    def print_message(self, message):
        """Nicely format and print a message.
        """
        cli.echo('{fg_blue}%(vid)s:%(pid)s:%(index)s{fg_reset}: %(text)s' % message)

    def run_forever(self):
        while True:
            try:
                self.print_message(self.get())

            except KeyboardInterrupt:
                break

            except Exception as e:
                cli.log.error("Uncaught exception: %s: %s", e.__class__.__name__, e)
                cli.log.exception(e)


class StateMachine(queue.Queue):
    def __init__(self, console):
        self.console = console

        super().__init__()

    def transition(self, func, *args):
        self.put(lambda: func(*args))

    def transition_later(self, delay, func, *args):
        time.sleep(delay)
        self.put(lambda: func(*args))

    def on_exception(self, e):
        cli.log.error('Exception: %s: %s', e.__class__.__name__, e)
        cli.log.exception(e)
        self.transition(self.on_exception, e)

    def run_forever(self):
        while True:
            try:
                f = self.get()
                f()
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

    def search(self, *rest):
        print('.', end='', flush=True)

        found = list(self.find_devices())
        selected = found[cli.args.index] if found[cli.args.index:] else None

        if selected:
            self.transition_later(0.5, self.on_connect, selected)
        else:
            self.transition_later(1, self.search)

    def on_connect(self, selected, *rest):
        print()
        print('Listening to %s:' % selected['path'].decode())
        device = hid.Device(path=selected['path'])
        self.transition_later(1, self.read, device)

    def read(self, device, *rest):
        print(device.read(32, 1).decode('ascii'), end='')
        self.transition(self.read, device)

    def on_exception(self, context, *rest):
        print(str(context))
        print('Device disconnected.')
        print('Waiting for new device..', end="")
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

    print('Waiting for device..', end="")
    sm.transition(sm.search)
    sm.run_forever()
