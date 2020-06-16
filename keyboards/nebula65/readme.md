# Nebula65

This is a standard fixed layout 65% PCB. It supports VIA, full per-key RGB and underglow RGB.

* Keyboard Maintainer: [Yiancar](http://yiancar-designs.com/) and on [GitHub](https://github.com/yiancar)
* Hardware Supported: A 65% keyboard with STM32F303CC
* Hardware Availability: https://spaceholdings.net/

## Instructions

### Build

Make example for this keyboard (after setting up your build environment):

    make nebula65:via

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
- Flash using QMK Toolbox or dfu-util (`make nebula65:<keymap>:flash`)
