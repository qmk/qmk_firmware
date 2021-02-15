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
+-----^-------+      +-----------------+       +------+-----+
      |                                               |
      +-----------------------------------------------+
                      Disconnect/Error
"""
import hid
import asyncio
import signal

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


def state_search(state_machine):
    print('.', end='', flush=True)
    found = _search()
    selected = found[0] if found[0:] else None

    if selected:
        state_machine.call_later(1, state_connect, state_machine, selected)
    else:
        state_machine.call_later(1, state_search, state_machine)


def state_connect(state_machine, selected):
    print()
    print('Listening to %s:' % selected['path'].decode())
    device = hid.Device(path=selected['path'])
    state_machine.call_soon(state_read, state_machine, device)


def state_read(state_machine, device):
    print(device.read(32).decode('ascii'), end='')
    state_machine.call_later(0.1, state_read, state_machine, device)


def state_exception(state_machine, context):
    # print('Exception handler called')
    # print(context)
    print('Device disconnected.')
    print('Waiting for new device:')
    state_machine.call_soon(state_search, state_machine)


@cli.argument('-l', '--list', arg_only=True, action='store_true', help='List available hid_listen devices.')
@cli.subcommand('Acquire debugging information from usb hid devices.', hidden=False if cli.config.user.developer else True)
def console(cli):
    """Acquire debugging information from usb hid devices
    """

    if cli.args.list:
        return list_devices()

    print('Waiting for device:')

    state_machine = asyncio.get_event_loop()

    state_machine.add_signal_handler(signal.SIGINT, state_machine.stop)  # Handle ctrl+c
    state_machine.set_exception_handler(state_exception)  # Handle disconnect/connect errors
    state_machine.call_soon(state_search, state_machine)

    try:
        state_machine.run_forever()
    finally:
        state_machine.close()
