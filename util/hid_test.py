import hid
import time

vid = 0x04D8
pid = 0xEED3

en = hid.enumerate()

for dev in en:
    if dev['vendor_id'] == 1240 and dev['product_id'] == 61139 and dev['usage_page'] == 65329 and dev['usage'] == 98:
        device = hid.Device(path=dev['path'])
        break

print(f"Connected to device: {device.product} by {device.manufacturer} - SN {device.serial} on path {dev['path']}")

print(
    """
    Select your option:
        1) All LEDs
        2) Keylight only
        3) Underglow only
        4) No LEDs
        5) Test notification
    """
)

choice = int(input("> "))

if choice in range(5):
    data = (1).to_bytes(1, 'big') + (choice).to_bytes(1, 'big') + b'\x00' * 62
    device.write(data)
elif choice == 5:
    # Get current state
    data = (3).to_bytes(1, 'big') + b'\x00' * 63
    device.write(data)
    # Read response
    status = device.read(1)
    print(status)
    # Start notification
    data = (2).to_bytes(1, 'big') + (1).to_bytes(1, 'big') + b'\x00' * 62
    device.write(data)
    time.sleep(3)
    device.write((1).to_bytes(1, 'big') + (1).to_bytes(1, 'big') + b'\x00' * 62)

# print(f"Sending data: {data}")


device.close()
