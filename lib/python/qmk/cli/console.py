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
from pathlib import Path
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
        cli.echo('{fg_blue}%(vendor_id)04X:%(product_id)04X:%(index)d{fg_reset}: %(text)s' % message)

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
        self.hid_device = hid_device
        self.device = hid.Device(path=hid_device['path'])
        self.current_line = ''

        print()
        cli.log.info('Listening to {fg_cyan}%s %s{fg_reset} ({fg_blue}%04X:%04X{fg_reset}):', hid_device['manufacturer_string'], hid_device['product_string'], hid_device['vendor_id'], hid_device['product_id'])

    def read(self, size, encoding='ascii', timeout=1):
        """Read size bytes from the device.
        """
        return self.device.read(size, timeout).decode(encoding)

    def read_line(self):
        """Read from the device's console until we get a \n.
        """
        while '\n' not in self.current_line:
            self.current_line += self.read(32).replace('\x00', '')

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


class FindDevices(queue.Queue):
    def __init__(self, console, vid, pid, index):
        self.console = console
        self.vid = vid
        self.pid = pid
        self.index = index

        super().__init__()

    def transition(self, func, *args, delay=None, **kwargs):
        if delay:
            time.sleep(delay)
        self.put((func, args, kwargs))

    def on_exception(self, e):
        """Called when an exception occurs in `run_forever`.
        """
        cli.log.error('Exception: %s: %s', e.__class__.__name__, e)
        cli.log.exception(e)
        self.transition(self.on_exception, e)

    def run_forever(self):
        """Process messages from our queue in a loop.
        """
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
        """Returns true when the usage page indicates it's a teensy-style console.
        """
        return hid_device['usage_page'] == 0xFF31 and hid_device['usage'] == 0x0074

    def is_filtered_device(self, hid_device):
        """Returns True if the device should be included in the list of available consoles.
        """
        return int2hex(hid_device['vendor_id']) == self.vid and int2hex(hid_device['product_id']) == self.pid

    def find_devices_by_report(self, hid_devices):
        """Returns a list of available teensy-style consoles by doing a brute-force search.

        Some versions of linux don't report usage and usage_page. In that case we fallback to reading the report (possibly inaccurately) ourselves.
        """
        devices = []

        for device in hid_devices:
            path = device['path'].decode('utf-8')

            if path.startswith('/dev/hidraw'):
                number = path[11:]
                report = Path(f'/sys/class/hidraw/hidraw{number}/device/report_descriptor')

                if report.exists():
                    rp = report.read_bytes()

                    if rp[1] == 0x31 and rp[3] == 0x09:
                        devices.append(device)

        return devices

    def find_devices(self):
        """Returns a list of available teensy-style consoles.
        """
        hid_devices = hid.enumerate()
        devices = list(filter(self.is_console_hid, hid_devices))

        if not devices:
            devices = self.find_devices_by_report(hid_devices)

        if self.vid and self.pid:
            devices = list(filter(self.is_filtered_device, devices))

        # Add index numbers
        device_index = {}
        for device in devices:
            id = ':'.join((int2hex(device['vendor_id']), int2hex(device['product_id'])))

            if id not in device_index:
                device_index[id] = 0

            device_index[id] += 1
            device['index'] = device_index[id]

        return devices

    def search(self):
        """Look for devices with teensy-style consoles and, if available, connect to it.
        """
        found = self.find_devices()

        if found:
            if self.index <= len(found):
                monitor = MonitorDevice(self.console, found[self.index-1])
                return self.transition(monitor.run_forever, delay=1)

            print()
            cli.log.warning("Only %d devices found, requested index is %d. Trying again in %d seconds...", len(found), self.index, cli.config.console.wait)
        else:
            print('.', end='', flush=True)

        self.transition(self.search, delay=cli.config.console.wait)

    def on_exception(self, e):
        cli.log.error('Exception: %s: %s: %s', self.__class__.__name__, e.__class__.__name__, e)
        cli.log.exception(e)
        cli.log.info('Device disconnected.')
        print('Waiting for new device..', end="", flush=True)
        self.transition(self.search)


def int2hex(number):
    """Returns a string representation of the number as hex.
    """
    return "%04X" % number


def list_devices(device_finder):
    cli.log.info('Available devices:')

    for dev in device_finder.find_devices():
        cli.log.info("\t%s:%s:%d\t%s %s", int2hex(dev['vendor_id']), int2hex(dev['product_id']), dev['index'], dev['manufacturer_string'], dev['product_string'])


@cli.argument('-d', '--device', help='device to select - uses format <pid>:<vid>[:<index>].')
@cli.argument('-l', '--list', arg_only=True, action='store_true', help='List available hid_listen devices.')
@cli.argument('-w', '--wait', type=int, default=1, help="How many seconds to wait between checks (Default: 1)")
@cli.subcommand('Acquire debugging information from usb hid devices.', hidden=False if cli.config.user.developer else True)
def console(cli):
    """Acquire debugging information from usb hid devices
    """
    vid = None
    pid = None
    index = 1

    if cli.config.console.device:
        device = cli.config.console.device.split(':')

        if len(device) == 2:
            vid, pid = device

        elif len(device) == 3:
            vid, pid, index = device

            if not index.isdigit():
                cli.log.error('Device index must be a number! Got "%s" instead.', index)
                exit(1)

            index = int(index)

            if index < 1:
                cli.log.error('Device index must be greater than 0! Got %s', index)
                exit(1)

        else:
            cli.log.error('Invalid format for device, expected "<pid>:<vid>[:<index>]" but got "%s".', cli.config.console.device)
            cli.print_help()
            exit(1)

        vid = vid.upper()
        pid = pid.upper()

    console = ConsoleMessages()
    device_finder = FindDevices(console, vid, pid, index)

    if cli.args.list:
        return list_devices(device_finder)

    print('Waiting for device..', end="", flush=True)
    device_finder_t = Thread(target=device_finder.run_forever, daemon=True)
    device_finder_t.start()
    console.run_forever()
