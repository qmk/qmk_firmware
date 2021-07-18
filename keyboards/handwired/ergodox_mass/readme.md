# ergodox_mass

![ergodox_mass](https://i.imgur.com/s6H9pae.jpg)

Custom variant of the ErgoDox with some rearranged keys, extra thumb cluster
keys, and a redesigned PCB.

- Keyboard Maintainer: [mass](https://github.com/mass)
- Hardware Supported: Custom PCB, ATMEGA32U4
- Hardware Availability: Contact Me

Make example for this keyboard (after setting up your build environment):

    make handwired/ergodox_mass:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

### Flashing with dfu-programmer
- Put device into !HWB reset
- `dfu-programmer atmega32u4 erase`
- `dfu-programmer atmega32u4 flash handwired_ergodox_mass_default.hex`
