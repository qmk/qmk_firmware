# ProjectKeyboard Alice PCB

ProjectKeyboard Alice Keyboard Replacement PCB

Keyboard Maintainer: onefiftynine

Hardware Supported: STM32F072CBT6  
Make example for this keyboard (after setting up your build environment):

    make projectkb/alice:default

If you are flashing this keyboard/pcb for the first time:

    * Set the dip switch on the reverse of the PCB to 1
    * Hit the reset button and then do
    * make projectkb/alice:default:dfu-util
    * After flashing the keyboard successfully, you can reset the dip switch back to 0

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
