# Keycult 1800

This is a 1800 layout PCB

* Keyboard Maintainer: [Yiancar](https://yiancar-designs.com/) and on [GitHub](https://github.com/yiancar)
* Hardware Supported: A 1800 keyboard with STM32F072CB or APM compatible
* Hardware Availability: https://keycult.com/ 

## Instructions

### Build

Make example for this keyboard (after setting up your build environment):

    make keycult/keycult1800:default

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
- Flash using QMK Toolbox or dfu-util (`make keycult/keycult1800:<keymap>:dfu-util`)
