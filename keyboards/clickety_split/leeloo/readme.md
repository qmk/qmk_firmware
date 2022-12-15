# Clickety Split | Leeloo v2

![Leeloo v2](https://imgur.com/swPHS0B)

Leeloo v2 is the evolution of Leeloo, which is a 4x6x5m ortholinear split keyboard designed, created, and sold by Clickety Split Ltd.

* Keyboard Maintainer: [Clickety Split](https://github.com/ClicketySplit)
* Hardware Supported: Leeloo PCB rev1/rev2, Pro Micro, Elite-C
* Hardware Availability: [clicketysplit.ca/pages/leeloo](https://clicketysplit.ca/pages/leeloo)

# Leeloo

![Leeloo](https://imgur.com/x1ew17D)

The original design and release of Leeloo.

# Sample Build Commands for Leeloo v1 and v2

After setting up the build environment, consider the following Make commands:

Leeloo v1:
```
    make clickety_split/leeloo/rev1:default
    make clickety_split/leeloo/rev1:default:flash
```

Leeloo v2:
```
    make clickety_split/leeloo/rev2:default_led
    make clickety_split/leeloo/rev2:default_led:dfu
```

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with the [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
