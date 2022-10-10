# Ergomax

![ergomax](https://user-images.githubusercontent.com/2750789/49322894-c9bc5680-f4c8-11e8-8044-eddc92af2d22.png)

Ergomax is a split ergo keyboard based on ergodox, with more room for activities.


Keyboard Maintainer: [LouWii](https://github.com/louwii)

Hardware Supported: Ergomax PCBs (left and right), ProMicro controller

Hardware Availability: not available yet


Make example for this keyboard (after setting up your build environment):

    make ergomax/rev1:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Builds

The Ergomax can work in 2 ways:
* independent (each side is connected directly to the computer and acts independently)
* master/slave split keyboard where the left side is the master side, connects to the computer. Right side connects to the left side via the TRRS (jack) cable and acts as 1 keyboard

Firmwares are different in each case and can be compiled via different commands

### Independent

```
make ergomax/rev1_left:default_left
```

will compile the firmware for the left side, with the default keymap layout

```
make ergomax/rev1_right:default_right
```

same, but for the right side

### Master/Slave Split

```
make ergomax/rev1:default
```

will compile the 1 firmware file that will work for both sides, with the default keymap layout.

The right side will only need to be flashed if it had the independent version of the firmware. If your Ergomax is already working in the master/slave configuration and the only thing you changed is the keymap layout, you only need to flash the firmware on the left (master) side.