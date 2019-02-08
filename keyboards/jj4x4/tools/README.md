# JJ40 Tools

## usb_detach.c

When trying to flash on Linux, you may encounter a "Resource Unavailable" error. This means that Linux's HID driver has taken exclusive control of the keyboard, and the program script can't flash it.
This program can force Linux to give up a device, so that the programming script can reset it.

### To compile:
```
gcc usb_detach.c -o usb_detach
```

### To run:
1. Use `lsusb` to discover the Bus and Device numbers for your keyboard.
2. Run the program: `sudo ./usb_detach /dev/bus/usb/<BUS>/<DEVICE>`.
3. Build and program the firmware as normal.
