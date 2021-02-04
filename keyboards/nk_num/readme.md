# NK_ Num

This is a standard Numpad PCB. It supports VIA and full per-key RGB.

* Keyboard Maintainer: [Yiancar](http://yiancar-designs.com/) and on [GitHub](https://github.com/yiancar)
* Hardware Supported: A Numpad keyboard with STM32F072CB
* Hardware Availability: https://novelkeys.xyz/

## Instructions

### Build

Make example for this keyboard (after setting up your build environment):

    make nk_num:via

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
- Flash using QMK Toolbox or dfu-util (`make nk_num:<keymap>:dfu-util`)
