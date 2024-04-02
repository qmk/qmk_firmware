# NK87B

![NK87B](https://i.imgur.com/nw29fvc.png)

This is a standard fixed layout TKL PCB. It supports VIA and full per-key RGB. This is revision B.

* Keyboard Maintainer: [Yiancar](https://yiancar-designs.com/) and on [GitHub](https://github.com/yiancar)
* Hardware Supported: A TKL keyboard with STM32F072CB or APM compatible
* Hardware Availability: https://novelkeys.xyz/

## Instructions

### Build

Make example for this keyboard (after setting up your build environment):

    make novelkeys/nk87b:default

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
- Flash using QMK Toolbox or dfu-util (`make nk87b:<keymap>:dfu-util`)
