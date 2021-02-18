import hid
import time
import psutil
vid = 0xFEED	# Change it for your device
pid = 0x6090	# Change it for your device

with hid.Device(vid, pid) as h:
	print(f'Device manufacturer: {h.manufacturer}')
	print(f'Product: {h.product}')
	while True:
		cpu = psutil.cpu_percent(interval=1.2)
		msg = f'CPU: {cpu}\0'.encode()
		h.write(msg)
		# print(h.read(len(msg)))