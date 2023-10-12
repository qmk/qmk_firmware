# HHKB Alternate Controller (YANG HHKB BLE Mod)

![YANG HHKB BLE Mod](https://i.imgur.com/aZP1GYc.jpeg)

An alternative controler for the HHKB designed by YANG (yangdigi)
based on the hasu controller.

* Keyboard Maintainer: [Kan-Ru Chen](https://github.com/kanru)  
* Hardware Supported: YANG HHKB BLE Controller  
* Hardware Availability: https://kbdfans.com/products/hhkb-ble-mod-upgrade-module

Make example for this keyboard (after setting up your build environment):

    make hhkb/yang:default

To flash, first boot your keyboard into bootloader (hold ESC and attach usb cable)
then a virtual USB storage should appear. You can copy the `hhkb_yang_default.bin`
file to the virtual USB storage and override the `HHKB_BLE.BIN` file in there.

Make sure to unmount and eject the virtual USB storage.

## Features:

- [x] QMK (via USB)
- [x] Bluetooth (BLE)
- [x] Power saving mode
  - [x] Idle mode
  - [x] Deep sleep mode
- [x] LEDs
- [x] Battery service
- [x] Special commands
  - [x] Switch BT peer

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

## How to reliably flash LUFA MassStorage bootloader on Linux

The FAT filesystem on Linux very often cannot flush the write cache,
leading to broken firmware in the flash.

We can use `dd` to write to the virtual block storage directly to
bypass the vfs layer.

```
dd if=FLASH.bin of=<path of virtual block device> seek=4
```

Skip 4 sectors because the default sector size of the virtual device
and dd is 512 bytes and the emulated flash file starts at 5th sector.

## How to find the path of the virtual block device

After the keyboard boots into flash mode, on Linux system you should
be able to find the block device in `dmesg` logs.

For exmaple if you type

```
sudo dmesg
```

You should find something like

```
[357885.143593] usb 1-1.4: USB disconnect, device number 24
[357885.627740] usb 1-1.4: new full-speed USB device number 25 using xhci_hcd
[357885.729486] usb 1-1.4: New USB device found, idVendor=03eb, idProduct=1962, bcdDevice= 0.01
[357885.729492] usb 1-1.4: New USB device strings: Mfr=0, Product=0, SerialNumber=0
[357885.745620] SCSI subsystem initialized
[357885.746712] usb-storage 1-1.4:1.0: USB Mass Storage device detected
[357885.746818] scsi host0: usb-storage 1-1.4:1.0
[357885.746919] usbcore: registered new interface driver usb-storage
[357885.747689] usbcore: registered new interface driver uas
[357886.766755] scsi 0:0:0:0: Direct-Access     LUFA     Bootloader       0.00 PQ: 0 ANSI: 0
[357886.773216] scsi 0:0:0:0: Attached scsi generic sg0 type 0
[357886.777474] sd 0:0:0:0: [sdx] 134 512-byte logical blocks: (68.6 kB/67.0 KiB)
[357886.780300] sd 0:0:0:0: [sdx] Write Protect is off
[357886.780302] sd 0:0:0:0: [sdx] Mode Sense: 00 00 00 00
[357886.783113] sd 0:0:0:0: [sdx] Asking for cache data failed
[357886.783114] sd 0:0:0:0: [sdx] Assuming drive cache: write through
[357886.842676]  sdx:
[357886.859528] sd 0:0:0:0: [sdx] Attached SCSI removable disk
```

The `sdx` is the block device name and the full path is at `/dev/sdx`
The above flash command will become

```
dd if=FLASH.bin of=/dev/sdx seek=4
```

**Caution**: if set to incorrect device it may wipe out
your actual disk.

## Help page of original firmware

http://help.ydkb.io/doku.php?id=en:kb-mods:hhkb-ble
