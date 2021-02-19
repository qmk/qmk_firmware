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

from milc import cli


class StateMachine(queue.Queue):
    def transition(self, func, *args):
        self.put(lambda: func(self, *args))

    def transition_later(self, delay, func, *args):
        time.sleep(delay)
        self.put(lambda: func(self, *args))

    def on_exception(self, func):
        self._except_func = func

    def run_forever(self):
        while True:
            try:
                f = self.get()
                f()
            except KeyboardInterrupt:
                break
            except BaseException as e:
                if self._except_func:
                    self._except_func(e)


def _is_console_hid(x):
    return x['usage_page'] == 0xFF31 and x['usage'] == 0x0074


def _is_filtered_device(x):
    name = "%04x:%04x" % (x['vendor_id'], x['product_id'])
    return name.lower().startswith(cli.args.device.lower())


def _search():
    devices = filter(_is_console_hid, hid.enumerate())
    if cli.args.device:
        devices = filter(_is_filtered_device, devices)

    return list(devices)


def list_devices():
    cli.log.info('Available devices:')
    devices = _search()
    for dev in devices:
        cli.log.info("  %02x:%02x %s %s", dev['vendor_id'], dev['product_id'], dev['manufacturer_string'], dev['product_string'])


def state_search(sm):
    print('.', end='', flush=True)

    found = _search()
    selected = found[cli.args.index] if found[cli.args.index:] else None

    if selected:
        sm.transition_later(0.5, state_connect, selected)
    else:
        sm.transition_later(1, state_search)


def state_connect(sm, selected):
    print()
    print('Listening to %s:' % selected['path'].decode())
    device = hid.Device(path=selected['path'])
    sm.transition_later(1, state_read, device)


def state_read(sm, device):
    print(device.read(32, 1).decode('ascii'), end='')
    sm.transition(state_read, device)


def state_exception(sm, context):
    # print(str(e))
    print('Device disconnected.')
    print('Waiting for new device:')
    sm.transition(state_search)


@cli.argument('-d', '--device', help='device to select - uses format <pid>:<vid>.')
@cli.argument('-i', '--index', default=0, help='device index to select.')
@cli.argument('-l', '--list', arg_only=True, action='store_true', help='List available hid_listen devices.')
@cli.subcommand('Acquire debugging information from usb hid devices.', hidden=False if cli.config.user.developer else True)
def console(cli):
    """Acquire debugging information from usb hid devices
    """

    if cli.args.list:
        return list_devices()

    print('Waiting for device:')

    sm = StateMachine()
    sm.transition(state_search)
    sm.on_exception(lambda e: sm.transition(state_exception, e))

    sm.run_forever()
