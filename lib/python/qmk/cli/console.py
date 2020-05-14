"""hid_listen
"""
import hid
import platform
from pathlib import Path
from time import sleep

from milc import cli

def patch_linux(dev):
    platform_id = platform.platform().lower()
    if 'linux' in platform_id:
        hidraw = Path(dev['path'].decode('UTF-8')).name
        descriptor_path = Path('/sys/class/hidraw/') / hidraw / 'device/report_descriptor'

        report = descriptor_path.read_bytes()

        dev['usage_page'] = (report[2] << 8) + report[1];
        dev['usage'] = report[4];
    return dev

def is_console_hid(x):
    return x['usage_page'] == 0xFF31 and x['usage'] == 0x0074

def search():
    return list(filter(is_console_hid, map(patch_linux, hid.enumerate())))

@cli.argument('-l', '--list', arg_only=True, action='store_true', help='List available hid_listen devices.')
@cli.argument('-i', '--index', default=0, type=int, help='Device index.')
@cli.subcommand('kinda hid_listen ish.')
def console(cli):
    """TODO.
    """

    if cli.args.list:
        cli.log.info('Available devices:')
        devices = search()
        for dev in devices:
            cli.log.info("%02x:%02x %s %s", dev['vendor_id'], dev['product_id'], dev['manufacturer_string'], dev['product_string'])
        return

    print('Waiting for device:')

    selected = None
    while selected is None:
        found = search()
        selected = found[cli.args.index] if found[cli.args.index:] else None

        print('.', end = '', flush=True)
        sleep(1)

    print()
    print('Listening to %s:' % selected['path'].decode())
    device = hid.Device(path=selected['path'])
    while True:
        print(device.read(32).decode('ascii'), end = '')
