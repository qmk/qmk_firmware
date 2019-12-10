Telophase
=========

A wireless split compact keyboard.

Hardware Supported: Telophase PCB

Make example for this keyboard (after setting up your build environment):

    make telophase:default

See [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) then the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.

## Hardware versions

There are two versions of the Pro Micro, a 3V and a 5V version. Depending on the version you're using, you'll need to set the processor frequency to `8000000` or `16000000` respectively. Do this by changing `F_CPU` in rules.mk.

## Telophase Notes

These configuration files were based off the Atreus keyboard. It assumes a Pro Micro is being used, however retains the 'make upload' feature from the Atreus branch. This keyboard uses a completely different 'matrix scan' system to other keyboards, it relies on an external nRF51822 microcontroller maintaining a matrix of keystates received from the keyboard halves. The matrix.c file contains the code to poll the external microcontroller for the key matrix. As long as this file is not changed, all other QMK features are supported.
