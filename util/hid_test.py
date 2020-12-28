import hid

vid = 0x04D8
pid = 0xEED3

en = hid.enumerate()

for dev in en:
    if dev['vendor_id'] == 1240 and dev['product_id'] == 61139 and dev['usage_page'] == 65329 and dev['usage'] == 98:
        device = hid.Device(path=dev['path'])
        break

print(f"Connected to device: {device.product} by {device.manufacturer} - SN {device.serial} on path {dev['path']}")
data = b'\x01\x01\x97' + b'\x00' * 61
print(f"Sending data: {data}")
device.write(b'\x01\x01\x97' + b'\x00' * 61)
# device.read(32, timeout=10000)
device.close()
