"""Acquire debugging information from usb hid devices

cli implementation of https://www.pjrc.com/teensy/hid_listen.html
"""
import hid
from pathlib import Path
from threading import Thread
from time import sleep

from milc import cli

LOG_COLOR = {
    'next': 0,
    'colors': [
        '{fg_blue}',
        '{fg_cyan}',
        '{fg_green}',
        '{fg_magenta}',
        '{fg_red}',
        '{fg_yellow}'
    ]
}


class MonitorDevice(object):
    def __init__(self, hid_device, numeric):
        self.hid_device = hid_device
        self.numeric = numeric
        self.device = hid.Device(path=hid_device['path'])
        self.current_line = ''

        cli.log.info('Listening to %(color)s%(manufacturer_string)s %(product_string)s{style_reset_all} (%(color)s%(vendor_id)04X:%(product_id)04X:%(index)d{style_reset_all})', hid_device)

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

    def run_forever(self):
        while True:
            try:
                message = {**self.hid_device, 'text': self.read_line()}

                if self.numeric:
                    cli.echo('%(color)s%(vendor_id)04X:%(product_id)04X:%(index)d{style_reset_all}: %(text)s' % message)
                else:
                    cli.echo('%(color)s%(manufacturer_string)s:%(product_string)s:%(index)d{style_reset_all}: %(text)s' % message)

            except hid.HIDException:
                break


class FindDevices(object):
    def __init__(self, vid, pid, index, numeric):
        self.vid = vid
        self.pid = pid
        self.index = index
        self.numeric = numeric

    def run_forever(self):
        """Process messages from our queue in a loop.
        """
        live_devices = {}

        while True:
            try:
                for device in list(live_devices):
                    if not live_devices[device]['thread'].is_alive():
                        cli.log.info('Disconnected from %(color)s%(manufacturer_string)s %(product_string)s{style_reset_all} (%(color)s%(vendor_id)04X:%(product_id)04X:%(index)d{style_reset_all})', live_devices[device])
                        del live_devices[device]

                for device in self.find_devices():
                    if device['path'] not in live_devices:
                        device['color'] = LOG_COLOR['colors'][LOG_COLOR['next']]
                        LOG_COLOR['next'] = (LOG_COLOR['next'] + 1) % len(LOG_COLOR['colors'])
                        live_devices[device['path']] = device
                        monitor = MonitorDevice(device, self.numeric)
                        device['thread'] = Thread(target=monitor.run_forever, daemon=True)

                        device['thread'].start()

                sleep(1)

            except KeyboardInterrupt:
                break

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


def int2hex(number):
    """Returns a string representation of the number as hex.
    """
    return "%04X" % number


def list_devices(device_finder):
    cli.log.info('Available devices:')

    for dev in device_finder.find_devices():
        color = LOG_COLOR['colors'][LOG_COLOR['next']]
        LOG_COLOR['next'] = (LOG_COLOR['next'] + 1) % len(LOG_COLOR['colors'])
        cli.log.info("\t%s%s:%s:%d{style_reset_all}\t%s %s", color, int2hex(dev['vendor_id']), int2hex(dev['product_id']), dev['index'], dev['manufacturer_string'], dev['product_string'])


@cli.argument('-d', '--device', help='device to select - uses format <pid>:<vid>[:<index>].')
@cli.argument('-l', '--list', arg_only=True, action='store_true', help='List available hid_listen devices.')
@cli.argument('-n', '--numeric', arg_only=True, action='store_true', help='Show VID/PID instead of names.')
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

    device_finder = FindDevices(vid, pid, index, cli.args.numeric)

    if cli.args.list:
        return list_devices(device_finder)

    print('Looking for devices...', flush=True)
    device_finder.run_forever()
