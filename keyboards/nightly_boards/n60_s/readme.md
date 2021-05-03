# [n]60-s

![n60-s](https://i.imgur.com/QN74bdJl.png)

A 60% pcb that supports standard and tsangan bottom row, split backspace, and split right shift. It supports a piezo buzzer right under the spacebar and a rotary encoder either on the right 1u of a split backspace or split right right shift.

* Keyboard Maintainer: [Neil Brian Ramirez](https://github.com/NightlyBoards)
* Hardware Supported: Atmega32u4

Make example for this keyboard (after setting up your build environment):

    make nightly_boards/n60_s:default
	
Flashing example for this keyboard:

    make nightly_boards/n60_s:default:flash

You can enter bootloader mode by pressing the physical reset button at the back of the pcb or by holding the escape key while plugging the usb cable.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
