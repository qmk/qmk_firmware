"""Interactions with compatible XAP devices
"""
import json
import random
import gzip
from platform import platform
import enum

from milc import cli

TIMEOUT = 1000
BYTE_ORDER = 'little' # Least Significant Bit (LSB) appears first, see `>>> help(int.to_bytes)`
MAX_MSG_LEN = 64 # 128 # ? according to specs: Maximum total message length is 128 bytes

# Request response flags
FLAG_SUCCESS            = 0b0000_0001 # (1ul << (0))
FLAG_SECURE_FAILURE     = 0b0000_0010 # (1ul << (1))
FLAG_UNLOCK_IN_PROGRESS = 0b0100_0000 # (1ul << (6))
FLAG_UNLOCKED           = 0b1000_0000 # (1ul << (7))
FLAG_FAILED             = 0x00

# Subsystems
# TODO give proper names / generate from JSON / Create IntEnum?
SUB_0, SUB_1, SUB_2, SUB_3, SUB_4, SUB_5 = range(6)

def _to_bytes(integer, length=1, order=BYTE_ORDER):
    """Returns a `bytes` representation of the integer of given length and byte order

    Note: This ensures the object has the expected properties for XAP protocal

    @param integer: integer to convert to `bytes`
    @type integer: int
    @param len: length of the ouput array of bytes
    @param order: The byte order used to represent the integer.
    @returns bytes
    @raises OverflowError: when the integer is not representable with the given number of bytes
    """
    return integer.to_bytes(length, byteorder=order)

def _from_bytes(bytes_, order=BYTE_ORDER):
    """Convert a `bytes` object to int
    N.B: Exact opposite of _to_bytes()

    @param bytes_: hex bytes
    @type bytes_: bytes
    @param order: The byte order used to represent the integer.
    @returns int
    """
    return int.from_bytes(bytes_, byteorder=order)

def _to_unsigned(bytes_, order=BYTE_ORDER):
    """Returns an unsigned int from an array of bytes

        >>> _to_unsigned(b"\xef\xbe\xad\xde")
        3735928559
        >>> hex(_to_unsigned(b"\xef\xbe\xad\xde"))
        '0xdeadbeef'
    """

    return _from_bytes(bytes_, order)

class ComError(Exception):
    """Communication error"""
    pass

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


def _xap_transaction(device, sub, route, payload=b''):
    """
    A XAP transaction is a request from host to device and a response from that device.

    @param device: the HID device to transact with
    @type device: hid.Device
    @param sub: Subsystem ID for the request; A high-level area of functionality within XAP.
    @type sub: int
    @param route: A sequence of IDs describing the route to invoke a _handler_.
    @type route: int
    @param payload: Any received data appended to the _route_, which gets delivered to the _handler_ when received.
    @type payload: bytes or int
    """
    # gen token
    token = _to_bytes(random.getrandbits(16), length=2)

    routing = _to_bytes(sub) + _to_bytes(route)
    # send with padding
    if isinstance(payload, int):
        payload = _to_bytes(payload, length=2)
    padding_len = MAX_MSG_LEN - 1 - len(routing) - len(payload)
    if padding_len < 0:
        raise IndexError(f"payload size too large by {-padding_len} bytes")

    padding = b"\x00" * padding_len
    buffer = token + _to_bytes(len(payload+routing)) + routing + payload + padding

    # prepend 0 on windows because reasons...
    if 'windows' in platform().lower():
        buffer = b"\x00" + buffer
    # print(buffer.hex())

    device.write(buffer)

    # get resp
    array_alpha = device.read(MAX_MSG_LEN, TIMEOUT)

    while token != array_alpha[:2]:
        # FIXME: Will consume and ignore all mismatching messages
        array_alpha = device.read(MAX_MSG_LEN, TIMEOUT)
    # print(array_alpha.hex())
    if array_alpha[2] != FLAG_SUCCESS:
        raise ComError(f"Transaction unsuccesful, got response flag {hex(array_alpha[2])}")

    payload_len = array_alpha[3]
    return array_alpha[4:4 + payload_len]


def _query_device(device):
    ver_data = _xap_transaction(device, SUB_0, 0x00)
    if not ver_data:
        return {'xap': 'UNKNOWN', 'secure': 'UNKNOWN'}

    # to u32 to BCD string
    a = _to_unsigned(ver_data[:4]])
    ver = f'{a>>24}.{a>>16 & 0xFF}.{a & 0xFFFF}'

    secure = _from_bytes(_xap_transaction(device, SUB_0, 0x03))
    secure = 'unlocked' if secure == 2 else 'LOCKED'

    return {'xap': ver, 'secure': secure}


def _query_device_id(device):
    return _xap_transaction(device, SUB_1, 0x08)


def _query_device_info_len(device):
    INFO_PAYLOAD_LEN = 4
    response_data = _xap_transaction(device, SUB_1, 0x05)
    if not response_data:
        raise ValueError(f"Expected response data for info query, got {respsonse_data}")
    elif len(response_data) != INFO_PAYLOAD_LEN:
        raise IndexError(f"Expected response payload to be of size {INFO_PAYLOAD_LEN}, got size {len(response_data)} ({response_data})")
    return _to_unsigned(response_data)

def _query_device_info_chunk(device, offset):
    return _xap_transaction(device, SUB_1, 0x06, offset)


def _query_device_info(device):
    datalen = _query_device_info_len(device)
    if not datalen:
        return {}

    data = []
    offset = 0
    while offset < datalen:
        chunk = _query_device_info_chunk(device, offset)
        data += chunk
        offset += 8*len(chunk)
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
    layers = _xap_transaction(device, SUB_4, 0x01)
    layers = _from_bytes(layers)
    print(f'layers:{layers}')

    # get keycode [layer:0, row:0, col:0]
    # keycode = _xap_transaction(device, SUB_4, 0x02, b"\x00\x00\x00")

    # get encoder [layer:0, index:0, clockwise:0]
    keycode = _xap_transaction(device, SUB_5, 0x02, b"\x00\x00\x00")

    keycode = _from_bytes(keycode)
    keycode_map = {
        # TODO: this should be data driven...
        0x04: 'KC_A',
        0x05: 'KC_B',
        0x29: 'KC_ESCAPE',
        0xF9: 'KC_MS_WH_UP',
    }
    print(f'keycode:{keycode_map.get(keycode, "unknown")}')


def xap_doit():
    print("xap_doit")
    # Reboot
    # _xap_transaction(device, SUB_1, 0x07)
    exit(1)


def xap_broadcast_listen(device):
    try:
        cli.log.info("Listening for XAP broadcasts...")
        while True:
            array_alpha = device.read(MAX_MSG_LEN, TIMEOUT)
            if b'\xFF\xFF' == array_alpha[:2]:
                data_size = array_alpha[3]
                data = bytes(reversed(array_alpha[4:4+data_size]))
                if array_alpha[2] == 1:
                    cli.log.info(f"  Broadcast: Secure[{data.hex()}]")
                else:
                    cli.log.info(f"  Broadcast: type[{hex(array_alpha[2])}] data:[{data.hex()}]")
    except KeyboardInterrupt:
        cli.log.info("Stopping...")


def xap_unlock(device):
    _xap_transaction(device, SUB_0, 0x04)


class CliAction(str, enum.Enum):
    UNLOCK = "unlock"
    DUMP = "dump"
    LISTEN = "listen"

    def __str__(self):
        return self.value

@cli.argument('-d', '--device', help='device to select - uses format <pid>:<vid>.')
@cli.argument('-i', '--index', default=0, help='device index to select.')
@cli.argument('-l', '--list', arg_only=True, action='store_true', help='List available devices.')
@cli.argument('action', nargs='?', arg_only=True, default="listen", choices=list(map(str, CliAction)))
@cli.subcommand('Acquire debugging information from usb XAP devices.', hidden=not cli.config.user.developer)
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
    cli.log.info("Connected to: %04x:%04x %s %s", dev['vendor_id'], dev['product_id'], dev['manufacturer_string'], dev['product_string'])

    # xap_doit(device)
    if cli.args.action == CliAction.UNLOCK:
        ret = xap_unlock(device)
        print(ret)
        cli.log.info("Done")

    elif cli.args.action == CliAction.DUMP:
        xap_dump_keymap(device)

    elif cli.args.action == CliAction.LISTEN:
        xap_broadcast_listen(device)

    else:
        raise ValueError("No action given (expected)")
