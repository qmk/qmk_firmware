# Gray COD67

The Gray COD67 is a 60% keyboard with a modern and bold design. It features 20 RGB Underglow LED lights and a unique diffuser placement. The COD67 has the most stunning RGB light strip for a custom mechanical keyboard. It also features a center mounted USB C port.

There were only 75 units made worldwide.

Keyboard Maintainer: [MechMerlin](https://github.com/mechmerlin)  
Hardware Supported: Gray COD67  
Hardware Availability: [Zfrontier](https://en.zfrontier.com/products/cod67)  

## Bootloader mode

To put in bootloader mode, hold the `Esc` key while plugging in the USB cable.

## Making firmware

Make example for this keyboard (after setting up your build environment):

    make gray_studio/cod67:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Flashing in Windows

After putting your COD67 in bootloader mode, it will show up as a drive.

* Rename the resulting `.bin` file to `COD67.BIN`.
* Drag and drop your new `COD67.BIN` to the drive, overwriting the previous `COD67.BIN` stored on it.
* Wait a few seconds for it to write. The caps lock LED flashes rapidly while writing.
* Press the `Esc` key again to reset the board. You are now ready to type!

## Flashing in macOS

After putting your COD67 in bootloader mode, it will show up as a drive.

* Rename the resulting `.bin` file to `COD67.BIN`.
* Drag the existing `COD67.BIN` file from the drive to the Trash in Finder.
* Empty the Trash in Finder. It's important you do that due to how macOS handles hidden `.Trashes` on removable drives. It needs to be empty to free up flash space.
* Drag and drop your new `COD67.BIN` to the drive.
* Wait a few seconds for it to write. The caps lock LED flashes rapidly while writing.
* Press the `Esc` key or eject the drive in Finder to reset the board. You are now ready to type!
