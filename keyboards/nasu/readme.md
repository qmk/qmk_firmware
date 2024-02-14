# Nasu

This is a standard Alice layout PCB. It supports VIA.

* Keyboard Maintainer: [Yiancar](http://yiancar-designs.com/) and on [GitHub](https://github.com/yiancar)
* Hardware Supported: A Alice like keyboard with STM32F072CB
* Hardware Availability: https://candykeys.com

## Instructions

### Build

Make example for this keyboard (after setting up your build environment):

    make nasu:default

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
- Flash using QMK Toolbox or dfu-util (`make nasu:<keymap>:dfu-util`)
