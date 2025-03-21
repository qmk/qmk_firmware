# NK65B

This is a standard fixed layout 65% PCB. It supports VIA and full per-key RGB. This is revision B.

![NK65](https://i.imgur.com/EXNbVpL.jpg)

Keyboard Maintainer: [Yiancar](http://yiancar-designs.com/) and on [GitHub](https://github.com/yiancar)
Hardware Supported: A 65% keyboard with STM32F072CB or APM compatible
Hardware Availability: https://novelkeys.xyz/

## Instructions

### Build

Make example for this keyboard (after setting up your build environment):

    make novelkeys/nk65b:via

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
- Flash using QMK Toolbox or dfu-util (`make nk65b:<keymap>:flash`)
