# Gaming Keyboard

* Keyboard Maintainer: [yangzheng20003 ](https://github.com/yangzheng20003 )
* Hardware Supported: Gaming Keyboard
* Hardware Availability: [ET](https://www.redragonzone.com/)

Make example for this keyboard (after setting up your build environment):

    make et/gaming_keyboard:default
        
Flashing example for this keyboard:

    make et/gaming_keyboard:default:flash

To reset the board into bootloader mode, do one of the following:

* Hold the Reset switch mounted on the bottom side of the PCB while connecting the USB cable
* Hold the Escape key while connecting the USB cable (also erases persistent settings)
* Fn+R_Shift+Esc will reset the board to bootloader mode if you have flashed the default QMK keymap

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
