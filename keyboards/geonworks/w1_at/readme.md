# W1-AT

This is a standard weird layout PCB, best build with a 10U spacebar. It supports VIA.

* Keyboard Maintainer: [Yiancar](http://yiancar-designs.com/) and on [GitHub](https://github.com/yiancar)
* Hardware Supported: A keyboard with STM32F072CB
* Hardware Availability: https://geon.works/ 

## Instructions

### Build

Make example for this keyboard (after setting up your build environment):

    make geonworks/w1_at:default

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
- Flash using QMK Toolbox or CLI (`make geonworks/w1_at:<keymap>:flash`)
