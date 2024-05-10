# Skeletyl

A very small keyboard made for ergonomic enthusiasts.

* Keyboard Maintainer: [Bastard Keyboards](https://github.com/Bastardkb/)
* Hardware Supported: elite-C V4
* Hardware Availability: [Bastardkb.com](https://bastardkb.com/)

## Building the firmware

**You must specify the shield version when compiling/flashing the firmware.**

The template is:

```shell
qmk compile -kb bastardkb/skeletyl/{VERSION}/elitec -km {KEYMAP}
```

| Shield Version  | default                                                         | via                                                         |
| --------------- | --------------------------------------------------------------- | ----------------------------------------------------------- |
| v1 (Elite-C)    | `qmk compile -kb bastardkb/skeletyl/v1/elitec -km default`      | `qmk compile -kb bastardkb/skeletyl/v1/elitec -km via`      |
| v2 (Elite-C)    | `qmk compile -kb bastardkb/skeletyl/v2/elitec -km default`      | `qmk compile -kb bastardkb/skeletyl/v2/elitec -km via`      |
| v2 (Splinky v2) | `qmk compile -kb bastardkb/skeletyl/v2/splinky_2 -km default`   | `qmk compile -kb bastardkb/skeletyl/v2/splinky_2 -km via`   |
| v2 (Splinky v3) | `qmk compile -kb bastardkb/skeletyl/v2/splinky_3 -km default`   | `qmk compile -kb bastardkb/skeletyl/v2/splinky_3 -km via`   |
| v2 (STeMCell)   | `qmk compile -kb bastardkb/skeletyl/v2/stemcell -km default`    | `qmk compile -kb bastardkb/skeletyl/v2/stemcell -km via`    |

This keyboard is made to be used with the Miryoku layout, do not use the default keymap.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

See the [keyboard build instructions](http://docs.bastardkb.com/)
