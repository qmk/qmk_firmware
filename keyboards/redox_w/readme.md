Redox wireless
=======

<p align="center">
<img src="https://github.com/mattdibi/redox-keyboard/raw/master/img/redox-logo.png" alt="Redox logo" width="600"/>
</p>

**Redox**: the **R**educed **E**rgo**dox** project. More information and building instruction [here](https://github.com/mattdibi/redox-keyboard).

A wireless version of the Redox keyboard.

- Keyboard Maintainer: [@mattdibi](https://github.com/mattdibi)
- Hardware Supported: Redox-w rev1.0W PCB
- Hardware Availability: Falbatech

Make example for this keyboard (after setting up your build environment):

    make redox_w:default

Example of flashing this keyboard:

    make redox/rev1:default:avrdude

See [build environment setup](https://docs.qmk.fm/build_environment_setup.html) then the [make instructions](https://docs.qmk.fm/make_instructions.html) for more information.

For nRF51822 firmware upload instruction and development see [the Redox wireless firmware repository](https://github.com/mattdibi/redox-w-firmware).

## Redox-w Notes

These configuration files were based off the Mitosis and Atreus keyboard. It assumes a Pro Micro is being used, however retains the 'make upload' feature from the Atreus branch. This keyboard uses a completely different 'matrix scan' system to other keyboards, it relies on an external nRF51822 microcontroller maintaining a matrix of keystates received from the keyboard halves. The matrix.c file contains the code to poll the external microcontroller for the key matrix. As long as this file is not changed, all other QMK features are supported.
