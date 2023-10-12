# Leopold FC980C replacement controller

![wlhlm FC980C replacement controller render](https://i.imgur.com/5AW0DTmh.png)

* Keyboard Maintainer: [wlhlm](https://github.com/wlhlm)
* Hardware Supported: rev. 1, rev. 2
* [PCB Source](https://github.com/wlhlm/fc980c-controller/)

Make example for this keyboard (after setting up your build environment):

    make leopold/fc980c/wlhlm:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Flashing the firmware onto the keyboard

To be able to flash the controller, it first has to be brought into bootloader mode. There are three ways this can be accomplished:

- Hold the `BOOT0` button at the back of the controller board (also accessible through the case) pressed while plugging the board into USB.
- Hold the `Escape` key while plugging the board into USB (requires QMK to already be flashed onto the controller).
- Press `Fn+Esc` (requires QMK to already be flashed onto the controller).

After entering bootloader mode, new firmware can be flashed. Make example for flashing this keyboard:

    make leopold/fc980c/wlhlm:default:flash

## Actuation point adjustment

Topre keyboards such as the FC980C are based around capacitive sense and allow adjustment of the actuation point. This feature is not supported by the firmware running on the stock FC980C controller, this replacement controller however unlocks said functionality through the flexibility of QMK. Check the `actuation_point_example` keymap for guidance.

