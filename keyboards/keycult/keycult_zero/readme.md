# Keycult Zero

This is a standard 60% layout PCB. It supports VIA.

* Keyboard Maintainer: [Yiancar](http://yiancar-designs.com/) and on [GitHub](https://github.com/yiancar)
* Hardware Supported: A 60% keyboard with STM32F072CB
* Hardware Availability: https://novelkeys.com/ 

## Instructions

### Build

Make example for this keyboard (after setting up your build environment):

    make keycult/keycult_zero:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

### Reset

- Unplug
- Hold Escape
- Plug In
- Unplug
- Release Escape

### Flash

- Unplug
- Hold Escape
- Plug In
- Flash using QMK Toolbox or CLI (`make keycult/keycult_zero:<keymap>:flash`)
