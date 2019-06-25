# Anne Pro

![Anne Pro](https://i.imgur.com/wF7mz7u.jpg)

QMK firmware port for the Anne Pro 60% keyboard produced by [Obins](http://en.obins.net).

__This firmware is not created or supported by the creator of this keyboard!__

Keyboard Maintainer: [Michiel Visser](https://github.com/msvisser)  
Hardware Supported: Anne Pro (this means no support for the _Anne Pro 2_)  
Hardware Availability: Discontinued, [possible vendors](https://www.reddit.com/r/AnnePro/wiki/vendors)

Before building the firmware for this keyboard a patch has to be applied:

    ./keyboards/anne_pro/apply_patch.sh

Make example for this keyboard (after setting up your build environment):

    make anne_pro:default

Flashing the firmware can easily be done when the keyboard is in DFU mode:

    make anne_pro:default:dfu-util

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
