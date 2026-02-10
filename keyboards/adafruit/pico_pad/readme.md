# PICO PAD

![PICO PAD](https://imgur.com/Nl4tZPl.jpg)

A RP2040 powered direct pins QMK keyboard in 3x7 layout.

A guide can be found here: [Pico Mechanical Keyboard](https://learn.adafruit.com/diy-pico-mechanical-keyboard-with-fritzing-circuitpython/overview)

* Keyboard Maintainer: [IcyAvocado](https://github.com/icyavocado)
* Hardware Supported: [Pico 1 Microcontrollers - RP2040](https://www.raspberrypi.com/documentation/microcontrollers/pico-series.html#pico-1-family)
* Hardware Availability: [The PiHut](https://thepihut.com/products/raspberry-pi-pico) | [Adafruit Parts](https://learn.adafruit.com/diy-pico-mechanical-keyboard-with-fritzing-circuitpython/overview)

Make example for this board (after setting up your build environment):

```sh
qmk compile -kb adafruit/pico_pad -km default
```

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader:
* **Physical reset button**: Briefly press the reset button on the left of the PCB - some may have pads you must short instead
* **Boot button**: Press and hold the BOOTSEL button on the pico when powered on
