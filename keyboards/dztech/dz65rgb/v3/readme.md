# DZ65RGB V3

A customizable 65% RGB keyboard.

* Keyboard Maintainer: [moyi4681](https://github.com/moyi4681)
* Hardware Supported: DZ65RGB V3
* Hardware Availability: [KBDfans](https://kbdfans.com/)

## Bootloader mode

To put in bootloader mode, hold the `Esc` key while plugging in the USB cable. or use reset key behind the pcb.

## Making firmware

Make example for this keyboard (after setting up your build environment):

    make dztech/dz65rgb/v3:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## DZ65RGB_V3 Flashing in Windows

After putting your pcb in bootloader mode, it will show up as a drive.

* Delete 'FLASH.bin' file
* Drag and drop your new `dztech_dz65rgb_v3_default.bin` to the drive.
* Wait a few seconds for it to write. 
* replug the usb cable.

## DZ65RGB_V3 Flashing in macOS

After putting your pcb in bootloader mode, it will show up as a drive.

* Drag the existing `flash.BIN` file from the drive to the Trash in Finder.
* Empty the Trash in Finder. It's important you do that due to how macOS handles hidden `.Trashes` on removable drives. It needs to be empty to free up flash space.
* Drag and drop your new `dztech_dz65rgb_v3_default.bin` to the drive.
* Wait a few seconds for it to write. 
* replug the usb cable.
