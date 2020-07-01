# Anne Pro

![Anne Pro](https://i.imgur.com/wF7mz7u.jpg)

QMK firmware port for the Anne Pro 60% keyboard produced by [Obins](http://en.obins.net).

__This firmware is not created or supported by the creator of this keyboard!__

Keyboard Maintainer: [Michiel Visser](https://github.com/msvisser)
Hardware Supported: Anne Pro (this means no support for the _Anne Pro 2_)
Hardware Availability: Discontinued, [possible vendors](https://www.reddit.com/r/AnnePro/wiki/vendors)

Make sure you check out the correct branch for this keyboard and initialize the submodules!

    git checkout anne_pro
    make git-submodule

Make example for this keyboard (after setting up your build environment):

    make anne_pro:default

Flashing the firmware can easily be done when the keyboard is in DFU mode:

    make anne_pro:default:dfu-util

The default Arrows and macOS keyboard layouts are also included and can be used with `arrow` or `macos` instead of `default`.

To convert the `bin` file to a `dfu` file the following script can be used

    ./keyboards/anne_pro/dfuse-pack.py -b 0x08004000:anne_pro_default.bin anne_pro_default.dfu

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
