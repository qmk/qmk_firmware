import hid
vid = 0xFEED
pid = 0x6060
h = hid.device()
h.open(vid,pid)
print(f'Device manufacturer: {h.get_manufacturer_string()}')
print(f'Product: {h.get_product_string()}')
h.set_nonblocking(1)
h.write(bytes([3,5]))

# NOTE: Change the 64 here if your board uses 32-byte RAW_EPSIZE
def pad_message(payload):
    return payload + b'\x00' * (32 - len(payload))

def tobyte(data):
    if type(data) is bytes:
        return data
    else:
        return (data).to_bytes(1, 'big')

def tobytes(data):
    out = b''
    for num in data:
        out += tobyte(num)
    return out


# print(f'Serial Number: {h.serial}')
#     # 0x03,!0x02......
#     #h.send_feature_report(b'\0x03\0x44')
