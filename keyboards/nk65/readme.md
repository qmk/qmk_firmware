NK65
=========

[NK65](https://mechboards.co.uk/wp-content/uploads/2018/04/IMG_20180420_140353.jpg)

This is a standard fixed layout 60% PCB. It comes in three variants; ISO, ANSI and HHKB and support full per-key RGB.

Keyboard Maintainer: [Yiancar](http://yiancar-designs.com/) and on [github](https://github.com/yiancar)  
Hardware Supported: A 65% keyboard with STM32F303CC   
Hardware Availability: https://novelkeys.xyz/   

Due to the RGB implementation, the NK65 is currently not compatible with community layouts.

## Instructions

### Build

Make example for this keyboard (after setting up your build environment):

    make nk65:default_via

See [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) then the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.

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
- Flash using QMK Toolbox or dfu-util (`make nk65:<keymap>:dfu-util`)
