# HHKB Alternate Controller (YANG HHKB BLE Mod)

![YANG HHKB BLE Mod](https://i.imgur.com/aZP1GYc.jpeg)

An alternative controler for the HHKB designed by YANG (yangdigi)
based on the hasu controller.

Keyboard Maintainer: [Kan-Ru Chen](https://github.com/kanru)  
Hardware Supported: YANG HHKB BLE Controller  
Hardware Availability: https://kbdfans.com/products/hhkb-ble-mod-upgrade-module

Make example for this keyboard (after setting up your build environment):

    make hhkb_yang:default

To flash, first boot your keyboard into bootloader (hold ESC and attach usb cable):

    make LUFA_DEVICE=/dev/sda hhkb_yang:default:flash

LUFA_DEVICE should point to the emulated storage device by the lufa-ms
bootloader. **Caution**: if set to incorrect device it may wipe out
your actual disk.

## Features planned:

- [x] QMK (via USB)
- [x] Bluetooth (BLE)
- [x] Power saving mode
  - [x] Idle mode
  - [x] Deep sleep mode
- [ ] LEDs
- [ ] Battery service
- [ ] Special commands
  - [ ] Switch BT peer

## Entering flash mode

Different ways to enter flash mode:

* Press and hold the ESC key. Insert the USB cable to enter the flash
  mode. When the OS shows the drive disk, you can release the key.

* Use the magic command LSHIFT+RSHIFT+B to reboot to bootloader then
  quickly hold the ESC key.

If you reflash the wrong firmware or did not reflash successfully, you
can no longer enter the flash mode, especially the wireless keyboard
with battery. You need to turn off the keyboard's power switch, and
re-enter the flash mode, reflash the correct firmware.

After entering the bootloader(flash mode), three indicators on the top
right of the HHKB BLE controller will flash. LED3(green) will flash
quickly when writing firmware to the controller.

If these three leds are not soldered or your hhkb case is black, you
can't know their status, but you can still see LED3 under the right
USB port.

## Help page of original firmware

http://help.ydkb.io/doku.php?id=en:kb-mods:hhkb-ble
