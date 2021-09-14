# Planck Through Hole Kit

![THK](https://i.imgur.com/Fj8X0TDl.jpg)

The OG 4x12, through-hole, ortho board.

[Buildlog](https://erovia.github.io/posts/thk/)

* Keyboard Maintainer: [Erovia](https://github.com/Erovia)
* Hardware Supported: [Planck THK](https://github.com/olkb/planck_thk)
* Hardware Availability: The hardware was released under GPLv3, see link above.

Make example for this keyboard (after setting up your build environment):

    make planck/thk:thk

Flashing example for this keyboard:

    make planck/thk:thk:flash

**Reset**: With [the recommended bootloader](https://github.com/Erovia/planck_thk_usbasploader) a single press on the RESET button.

## Audio

The board has rudimental [audio](https://docs.qmk.fm/#/feature_audio) support.  
As it can cause the USB connection to crash, likely due the mcu not being able to keep up with the USB's strict timing requirements, it's is disabled for the `thk` keymap.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
