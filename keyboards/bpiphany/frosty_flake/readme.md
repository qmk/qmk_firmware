# Frosty Flake Controller

This is the firmware for Rev. 20140521 of the Frosty Flake controller
by [Bathroom Epiphanies](http://bathroomepiphanies.com/controllers/),
a replacement controller for the [Cooler Master Quick Fire
Rapid](http://www.coolermaster.com/peripheral/keyboards/quickfirerapid/).

The code was adapted from the [BathroomEpiphanies TMK
Firmware](https://github.com/BathroomEpiphanies/epiphanies_tmk_keyboard/tree/master/be_controllers),
but has been cleaned up to match the
[schematic](https://deskthority.net/wiki/File:Frosty_Flake_Schematics.pdf)
and gone through some minor refactoring for QMK.

## 104 and 87 layout support

Support for both 104 key and 87 key layouts is provided. See the
keymaps `default` (104) and `tkl` (87) for example layouts.

Keyboard Maintainer: QMK Community  
Hardware Supported: Frosty Flake  
Hardware Availability: https://1upkeyboards.com/qfr-frosty-flake-controller.html  

Make example for this keyboard (after setting up your build environment):

104 key default layout:

```
make bpiphany/frosty_flake:default
```

To directly flash the frosty_flake after compiling use

```
make bpiphany/frosty_flake:default:dfu
```

87 key tkl layout:

```
make bpiphany/frosty_flake:tkl:dfu
```

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
