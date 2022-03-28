"""Interactions with compatible XAP devices
"""
import json
import random
import gzip

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
            cli.echo('    {fg_blue}%s{fg_reset}: %s', new_prefix, ', '.join(map(str, sorted(kb_info_json[key]))))
        else:
            cli.echo('    {fg_blue}%s{fg_reset}: %s', new_prefix, kb_info_json[key])


def _list_devices():
    """Dump out available devices
    """
    cli.log.info('Available devices:')
    devices = _search()
    for dev in devices:
        device = hid.Device(path=dev['path'])

        data = _query_device_version(device)
        cli.log.info("  %04x:%04x %s %s [API:%s]", dev['vendor_id'], dev['product_id'], dev['manufacturer_string'], dev['product_string'], data['ver'])

        if cli.config.general.verbose:
            # TODO: better formatting like "lsusb -v"
            datalen = _query_device_info_len(device)

            data = []
            offset = 0
            while offset < datalen:
                data += _query_device_info(device, offset)
                offset += 32
            str_data = gzip.decompress(bytearray(data[:datalen]))
            print_dotted_output(json.loads(str_data))


def _query_device_version(device):
    # gen token
    tok = random.getrandbits(16)
    temp = tok.to_bytes(2, byteorder='big')

    # send with padding
    padding = b"\x00" * 59
    device.write(temp + b'\x02\x00\x00' + padding)

    # get resp
    array_alpha = device.read(8, 100)
    # hex_string = " ".join("%02x" % b for b in array_alpha)

    # validate tok sent == resp
    ver = "UNKNOWN"
    if str(temp) == str(array_alpha[:2]):
        # to BCD string
        a = (array_alpha[7] << 24) + (array_alpha[6] << 16) + (array_alpha[5] << 8) + (array_alpha[4])
        ver = f'{a>>24}.{a>>16 & 0xFF}.{a & 0xFFFF}'

    return {'ver': ver}


def _query_device_info_len(device):
    # gen token
    tok = random.getrandbits(16)
    temp = tok.to_bytes(2, byteorder='big')

    # send with padding
    padding = b"\x00" * 59
    device.write(temp + b'\x02\x01\x05' + padding)

    # get resp
    array_alpha = device.read(8, 100)
    # hex_string = " ".join("%02x" % b for b in array_alpha)

    # validate tok sent == resp
    datalen = "UNKNOWN"
    if str(temp) == str(array_alpha[:2]):
        # to BCD string
        a = (array_alpha[7] << 24) + (array_alpha[6] << 16) + (array_alpha[5] << 8) + (array_alpha[4])
        datalen = f'{a & 0xFFFF}'

    return int(datalen)


def _query_device_info(device, offset):
    # gen token
    tok = random.getrandbits(16)
    temp = tok.to_bytes(2, byteorder='big')

    # send with padding
    padding = b"\x00" * 57
    device.write(temp + b'\x04\x01\x06' + (offset).to_bytes(2, byteorder='big') + padding)

    # get resp
    array_alpha = device.read(4 + 32, 100)

    # hex_string = " ".join("%02x" % b for b in array_alpha)

    # validate tok sent == resp
    if str(temp) == str(array_alpha[:2]):
        return array_alpha[4:]
    return None


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
