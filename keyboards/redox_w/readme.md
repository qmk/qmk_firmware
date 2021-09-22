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

```sh
make redox_w:default
```

Example of flashing this keyboard:

```sh
make redox_w:default:avrdude
```

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

For nRF51822 firmware upload instruction and development see [the Redox wireless firmware repository](https://github.com/mattdibi/redox-w-firmware).

## Redox-w Notes

These configuration files were based off the [Mitosis](https://github.com/qmk/qmk_firmware/tree/master/keyboards/mitosis) and [Atreus](https://github.com/technomancy/atreus) keyboard. It assumes a Pro Micro is being used, however retains the 'make upload' feature from the Atreus branch. This keyboard uses a completely different 'matrix scan' system to other keyboards, it relies on an external nRF51822 microcontroller maintaining a matrix of keystates received from the keyboard halves. The matrix.c file contains the code to poll the external microcontroller for the key matrix. As long as this file is not changed, all other QMK features are supported.
