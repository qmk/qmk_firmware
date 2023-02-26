import hid

# Define the VID (Vendor ID) and PID (Product ID) for your keyboard
VID = 0x4000
PID = 0x1111

# Open the HID device with the specified VID and PID
device = hid.device(VID, PID)

# Send a raw HID message to the device
data = [0x01, 0x02, 0x03] # Example raw HID data
device.write(data)

# Read the response from the device
response = device.read(64) # Read up to 64 bytes of data
print(response)
