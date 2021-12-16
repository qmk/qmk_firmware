# Nostromo

![Nostromo](https://i.imgur.com/q1QXjzH.jpg)

Nostromo is a simple 5x12 layout ortholinear keyboard complete with
[PCB FILES](https://github.com/su8044/qmk_firmware/tree/nostromo_maintenance/keyboards/nostromo/PCB_5x12),
and
[CASE FILES](https://github.com/su8044/qmk_firmware/tree/nostromo_maintenance/keyboards/nostromo/DWG).
using a Blackpill F411 MCU and QMK Firmware. Pins are available for RGB, and LED backlight controlled by PWM

if you have any questions please let me know by email. hope you enjoy it!

* Keyboard Maintainer: [su8044](https://github.com/su8044)

Make example for this keyboard (after setting up your build environment):

    make nostromo:default

To reset the board into bootloader mode press simultaneously the "reset" and "boot" buttons located on the blackpill board for a second and then release. You can also just press the "boot" button and then connect the sub c cable

Keep in mind some blackpill's on the market have issues to reset the board into bootloader mode. I have found some laptops present the issue much less often than a desktop pc.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
