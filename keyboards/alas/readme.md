# Alas

This is a standard 60% layout PCB. It supports VIA.

* Keyboard Maintainer: [Yiancar](http://yiancar-designs.com/) and on [GitHub](https://github.com/yiancar)
* Hardware Supported: A 60% keyboard with STM32F072CB
* Hardware Availability: https://geekhack.org/index.php?topic=119025.0 

![Layer 0](https://i.imgur.com/LL5mZXAh.png)
![Layer 1](https://i.imgur.com/RJDVmtyh.png)

## Instructions

### Build

Make example for this keyboard (after setting up your build environment):

    make alas:default

Flashing example for this keyboard:

    make alas:default:flash

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
- Flash using QMK Toolbox or CLI (`make alas:<keymap>:flash`)
