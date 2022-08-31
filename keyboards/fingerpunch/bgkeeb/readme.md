# bgkeeb

* Keyboard Maintainer: sadekbaroudi
* Hardware Supported: bgkeeb PCB rev1 Pro Micro

Make example for this keyboard (after setting up your build environment):

    make fingerpunch/bgkeeb:default

Flashing example for this keyboard ([using the command line](https://docs.qmk.fm/#/newbs_flashing?id=flash-your-keyboard-from-the-command-line)):

    make fingerpunch/bgkeeb:default:flash

See [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) then the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.

## Build Guide

See:
https://github.com/sadekbaroudi/bgkeeb/blob/master/BUILDGUIDE.md

## Choosing which board to plug the USB cable into (choosing Master)

Because the two boards are identical, the firmware has logic to differentiate the left and right board. It uses two strategies to figure things out, [EE_HANDS](https://docs.qmk.fm/#/feature_split_keyboard?id=handedness-by-eeprom) or [by define](https://docs.qmk.fm/#/feature_split_keyboard?id=handedness-by-define). See [setting-handedness](https://docs.qmk.fm/#/config_options?id=setting-handedness) for more information.
