# Ghost Squid Controller

This is the firmware for Rev. 20140518 of the Ghost Squid controller
by [Bathroom Epiphanies](http://bathroomepiphanies.com/controllers/),
a replacement controller for the [Cooler Master Quick Fire
XT](https://www.coolermaster.com/catalog/peripheral/keyboards/quick-fire-xt/).

The code was adapted from the [BathroomEpiphanies QMK
Firmware](https://github.com/BathroomEpiphanies/epiphanies_qmk_keyboard/tree/master/keyboards/ghost_squid_20140518).

## Layout support

Support for both 104 key layout is provided. See the
keymaps `default` for example layout.

Keyboard Maintainer: QMK Community
Hardware Supported: Ghost Squid
Hardware Availability: [1upkeyboards](https://1upkeyboards.com/shop/controllers/qf-xt-ghost-squid-controller-2/)

Make example for this keyboard (after setting up your build environment):

104 key default layout:

```
make bpiphany/ghost_squid:default
```

To directly flash the ghost_squid after compiling use:

```
make bpiphany/ghost_squid:default:dfu
```

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
