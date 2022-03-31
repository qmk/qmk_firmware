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


def _xap_transaction(device, sub, route, ret_len, *args):
    # gen token
    tok = random.getrandbits(16)
    token = tok.to_bytes(2, byteorder='little')

    # send with padding
    # TODO: this code is total garbage
    args_data = []
    args_len = 2
    if len(args) == 1:
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
    array_alpha = device.read(4 + ret_len, 100)

    # validate tok sent == resp
    if str(token) != str(array_alpha[:2]):
        return None
    return array_alpha[4:]


def _query_device(device):
    ver_data = _xap_transaction(device, 0x00, 0x00, 4)
    if not ver_data:
        return {'xap': 'UNKNOWN'}

    # to u32 to BCD string
    a = (ver_data[3] << 24) + (ver_data[2] << 16) + (ver_data[1] << 8) + (ver_data[0])
    ver = f'{a>>24}.{a>>16 & 0xFF}.{a & 0xFFFF}'

    secure = int.from_bytes(_xap_transaction(device, 0x00, 0x03, 1), 'little')
    secure = 'unlocked' if secure == 2 else 'LOCKED'

    return {'xap': ver, 'secure': secure}


def _query_device_info_len(device):
    len_data = _xap_transaction(device, 0x01, 0x05, 4)
    if not len_data:
        return 0

    # to u32
    return (len_data[3] << 24) + (len_data[2] << 16) + (len_data[1] << 8) + (len_data[0])


def _query_device_info_chunk(device, offset):
    return _xap_transaction(device, 0x01, 0x06, 32, offset)


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
            print_dotted_output(data)
            # _xap_transaction(device, 0x01, 0x07, 1)


@cli.argument('-d', '--device', help='device to select - uses format <pid>:<vid>.')
@cli.argument('-i', '--index', default=0, help='device index to select.')
@cli.argument('-l', '--list', arg_only=True, action='store_true', help='List available devices.')
@cli.subcommand('Acquire debugging information from usb XAP devices.', hidden=False if cli.config.user.developer else True)
def xap(cli):
    """Acquire debugging information from XAP devices
    """
    # Lazy load to avoid issues
    global hid
    import hid

    if cli.args.list:
        return _list_devices()

    cli.log.warn("TODO: Device specific stuff")
