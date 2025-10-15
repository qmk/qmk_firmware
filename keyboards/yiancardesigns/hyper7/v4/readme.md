# Hyper7 v4

This is a very big pcb... It supports VIA.

* Keyboard Maintainer: [Yiancar](http://yiancar-designs.com/) and on [GitHub](https://github.com/yiancar) 
* Hardware Supported: A very big keyboard with STM32F072RB 
* Hardware Availability: https://mechboards.co.uk/ 

## Instructions

### Build

Make example for this keyboard (after setting up your build environment):

    make yiancardesigns/hyper7/v4:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

### Reset

- Unplug
- Hold F3
- Plug In
- Unplug
- Release F3

### Flash

- Unplug
- Hold F3
- Plug In
- Flash using QMK Toolbox or CLI (`make yiancardesigns/hyper7/v4:<keymap>:flash`)
