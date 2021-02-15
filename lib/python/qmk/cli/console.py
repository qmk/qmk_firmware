"""hid_listen
"""
import hid
import asyncio
import signal
from pathlib import Path

from milc import cli


def _is_console_hid(x):
    return x['usage_page'] == 0xFF31 and x['usage'] == 0x0074


def _search():
    return list(filter(_is_console_hid, hid.enumerate()))


def list_devices():
    cli.log.info('Available devices:')
    devices = _search()
    for dev in devices:
        cli.log.info("  %02x:%02x %s %s", dev['vendor_id'], dev['product_id'], dev['manufacturer_string'], dev['product_string'])


def state_search(loop):
    print('.', end='', flush=True)
    found = _search()
    selected = found[0] if found[0:] else None

    if selected:
        loop.call_later(1, state_connect, loop, selected)
    else:
        loop.call_later(1, state_search, loop)


def state_connect(loop, selected):
    print()
    print('Listening to %s:' % selected['path'].decode())
    device = hid.Device(path=selected['path'])
    loop.call_soon(state_read, loop, device)


def state_read(loop, device):
    print(device.read(32).decode('ascii'), end='')
    loop.call_later(0.1, state_read, loop, device)


def state_exception(loop, context):
    # print('Exception handler called')
    # print(context)
    print('Device disconnected.')
    print('Waiting for new device:')
    loop.call_soon(state_search, loop)


@cli.argument('-l', '--list', arg_only=True, action='store_true', help='List available hid_listen devices.')
@cli.subcommand('kinda hid_listen ish.')
def console(cli):
    """TODO:
    """

    if cli.args.list:
        return list_devices()

    print('Waiting for device:')

    loop = asyncio.get_event_loop()

    loop.add_signal_handler(signal.SIGINT, loop.stop)  # Handle ctrl+c
    loop.set_exception_handler(state_exception)  # Handle disconnect/connect errors
    loop.call_soon(state_search, loop)

    try:
        loop.run_forever()
    finally:
        loop.close()
