"""Interactions with compatible XAP devices
"""
import json
import random
import gzip
from platform import platform

from milc import cli


def _is_xap_usage(x):
    return x['usage_page'] == 0xFF51 and x['usage'] == 0x0058


def _is_filtered_device(x):
    name = "%04x:%04x" % (x['vendor_id'], x['product_id'])
    return name.lower().startswith(cli.args.device.lower())


def _search():
    devices = filter(_is_xap_usage, hid.enumerate())
    if cli.args.device:
        devices = filter(_is_filtered_device, devices)

    return list(devices)


def print_dotted_output(kb_info_json, prefix=''):
    """Print the info.json in a plain text format with dot-joined keys.
    """
    for key in sorted(kb_info_json):
        new_prefix = f'{prefix}.{key}' if prefix else key

        if key in ['parse_errors', 'parse_warnings']:
            continue
        elif key == 'layouts' and prefix == '':
            cli.echo('    {fg_blue}layouts{fg_reset}: %s', ', '.join(sorted(kb_info_json['layouts'].keys())))
        elif isinstance(kb_info_json[key], bytes):
            conv = "".join(["{:02X}".format(b) for b in kb_info_json[key]])
            cli.echo('    {fg_blue}%s{fg_reset}: %s', new_prefix, conv)
        elif isinstance(kb_info_json[key], dict):
            print_dotted_output(kb_info_json[key], new_prefix)
        elif isinstance(kb_info_json[key], list):
            data = kb_info_json[key]
            if len(data) and isinstance(data[0], dict):
                for index, item in enumerate(data, start=0):
                    cli.echo('    {fg_blue}%s.%s{fg_reset}: %s', new_prefix, index, str(item))
            else:
                cli.echo('    {fg_blue}%s{fg_reset}: %s', new_prefix, ', '.join(sorted(map(str, data))))
        else:
            cli.echo('    {fg_blue}%s{fg_reset}: %s', new_prefix, kb_info_json[key])


def _xap_transaction(device, sub, route, *args):
    # gen token
    tok = random.getrandbits(16)
    token = tok.to_bytes(2, byteorder='little')

    # send with padding
    # TODO: this code is total garbage
    args_data = []
    args_len = 2
    if len(args) == 1:
        if isinstance(args[0], (bytes, bytearray)):
            args_len += len(args[0])
            args_data = args[0]
        else:
            args_len += 2
            args_data = args[0].to_bytes(2, byteorder='little')

    padding_len = 64 - 3 - args_len
    padding = b"\x00" * padding_len
    if args_data:
        padding = args_data + padding
    buffer = token + args_len.to_bytes(1, byteorder='little') + sub.to_bytes(1, byteorder='little') + route.to_bytes(1, byteorder='little') + padding

    # prepend 0 on windows because reasons...
    if 'windows' in platform().lower():
        buffer = b"\x00" + buffer

    device.write(buffer)

    # get resp
    array_alpha = device.read(64, 100)

    # validate tok sent == resp
    if str(token) != str(array_alpha[:2]):
        return None
    if int(array_alpha[2]) != 0x01:
        return None

    payload_len = int(array_alpha[3])
    return array_alpha[4:4 + payload_len]


def _query_device(device):
    ver_data = _xap_transaction(device, 0x00, 0x00)
    if not ver_data:
        return {'xap': 'UNKNOWN', 'secure': 'UNKNOWN'}

    # to u32 to BCD string
    a = (ver_data[3] << 24) + (ver_data[2] << 16) + (ver_data[1] << 8) + (ver_data[0])
    ver = f'{a>>24}.{a>>16 & 0xFF}.{a & 0xFFFF}'

    secure = int.from_bytes(_xap_transaction(device, 0x00, 0x03), 'little')
    secure = 'unlocked' if secure == 2 else 'LOCKED'

    return {'xap': ver, 'secure': secure}


def _query_device_id(device):
    return _xap_transaction(device, 0x01, 0x08)


def _query_device_info_len(device):
    len_data = _xap_transaction(device, 0x01, 0x05)
    if not len_data:
        return 0

    # to u32
    return (len_data[3] << 24) + (len_data[2] << 16) + (len_data[1] << 8) + (len_data[0])


def _query_device_info_chunk(device, offset):
    return _xap_transaction(device, 0x01, 0x06, offset)


def _query_device_info(device):
    datalen = _query_device_info_len(device)
    if not datalen:
        return {}

    data = []
    offset = 0
    while offset < datalen:
        data += _query_device_info_chunk(device, offset)
        offset += 32
    str_data = gzip.decompress(bytearray(data[:datalen]))
    return json.loads(str_data)


def _list_devices():
    """Dump out available devices
    """
    cli.log.info('Available devices:')
    devices = _search()
    for dev in devices:
        device = hid.Device(path=dev['path'])

        data = _query_device(device)
        cli.log.info("  %04x:%04x %s %s [API:%s] %s", dev['vendor_id'], dev['product_id'], dev['manufacturer_string'], dev['product_string'], data['xap'], data['secure'])

        if cli.config.general.verbose:
            # TODO: better formatting like "lsusb -v"?
            data = _query_device_info(device)
            data["_id"] = _query_device_id(device)
            print_dotted_output(data)


def xap_dump_keymap(device):
    # get layer count
    layers = _xap_transaction(device, 0x04, 0x01)
    layers = int.from_bytes(layers, "little")
    print(f'layers:{layers}')

    # get keycode [layer:0, row:0, col:0]
    # keycode = _xap_transaction(device, 0x04, 0x02, b"\x00\x00\x00")

    # get encoder [layer:0, index:0, clockwise:0]
    keycode = _xap_transaction(device, 0x05, 0x02, b"\x00\x00\x00")

    keycode = int.from_bytes(keycode, "little")
    keycode_map = {
        # TODO: this should be data driven...
        0x04: 'KC_A',
        0x05: 'KC_B',
        0x29: 'KC_ESCAPE',
        0xF9: 'KC_MS_WH_UP',
    }
    print(f'keycode:{keycode_map.get(keycode, "unknown")}[{keycode}]')

    # set encoder [layer:0, index:0, clockwise:0, keycode:KC_A]
    _xap_transaction(device, 0x05, 0x03, b"\x00\x00\x00\x04\00")


def xap_doit():
    print("xap_doit")
    # Reboot
    # _xap_transaction(device, 0x01, 0x07)
    exit(1)


def xap_broadcast_listen(device):
    try:
        cli.log.info("Listening for XAP broadcasts...")
        while 1:
            array_alpha = device.read(64, 100)
            if str(b"\xFF\xFF") == str(array_alpha[:2]):
                if array_alpha[2] == 1:
                    cli.log.info("  Broadcast: Secure[%02x]", array_alpha[4])
                else:
                    cli.log.info("  Broadcast: type[%02x] data:[%02x]", array_alpha[2], array_alpha[4])
    except KeyboardInterrupt:
        cli.log.info("Stopping...")


def xap_unlock(device):
    _xap_transaction(device, 0x00, 0x04)


@cli.argument('-d', '--device', help='device to select - uses format <pid>:<vid>.')
@cli.argument('-i', '--index', default=0, help='device index to select.')
@cli.argument('-l', '--list', arg_only=True, action='store_true', help='List available devices.')
@cli.argument('action', nargs='?', arg_only=True)
@cli.subcommand('Acquire debugging information from usb XAP devices.', hidden=False if cli.config.user.developer else True)
def xap(cli):
    """Acquire debugging information from XAP devices
    """
    # Lazy load to avoid issues
    global hid
    import hid

    if cli.args.list:
        return _list_devices()

    # Connect to first available device
    devices = _search()
    if not devices:
        cli.log.error("No devices found!")
        return False

    dev = devices[0]
    device = hid.Device(path=dev['path'])
    cli.log.info("Connected to:%04x:%04x %s %s", dev['vendor_id'], dev['product_id'], dev['manufacturer_string'], dev['product_string'])

    # xap_doit(device)
    if cli.args.action == 'unlock':
        xap_unlock(device)
        cli.log.info("Done")

    elif cli.args.action == 'dump':
        xap_dump_keymap(device)

    elif cli.args.action == 'listen':
        xap_broadcast_listen(device)

    elif not cli.args.action:
        xap_broadcast_listen(device)
