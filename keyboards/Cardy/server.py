import hid
import time
vid = 0xFEED	# Change it for your device
pid = 0x6090	# Change it for your device
msg = 'hk\0'.encode()
with hid.Device(vid, pid) as h:
	print(f'Device manufacturer: {h.manufacturer}')
	print(f'Product: {h.product}')
	h.write(msg)
	print(h.read(len(msg)))