# Bachoo Crin

Crin is an F-rowless 65%.

* Keyboard Maintainer: [KnoblesseOblige](https://github.com/KnoblesseOblige)
* Hardware Supported: STM32F303CBT
* Hardware Availability: TBD

Make example for this keyboard (after setting up your build environment):

    make crin:default:flash

To enter the bootloader either:

0. Hold Esc while plugging the PCB in, if BOOTMAGIC lite is enabled.
0. Press the RESET keycode, if programmed on the keymap.
0. Slide the switch just below the reset button to the left and press the reset button.
  * Please note that you must slide it back to the right for the PCB to boot QMK again.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
