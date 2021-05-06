# bakekujira Keyboard (bakekujira)

![Crkbd](https://user-images.githubusercontent.com/736191/40575636-6fba63a4-6123-11e8-9ca0-3f990f1f9f4c.jpg)

![Crkbd](https://user-images.githubusercontent.com/736191/40887871-0eead5dc-678a-11e8-9518-e3ad9e5d2bac.png)

A split, TKL, No F-Row, OLED and LED keyboard

# Overview

Keyboard Maintainer: [idorurez](https://github.com/idorurez)  
Hardware Supported: Proton-C, custom pcb
For Hardware Bill of Materials and additional info: [PCB & Case Data](https://github.com/idorurez/bakekujira)

# Flashing

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

Make example for this keyboard (after setting up your build environment):

It goes without saying, any changes you make to the config requires that you *flash both sides* everytime.

## To Set Handedness

If you haven't set the handedness yet for each side, you'll need to add the `-bl` argument. You need to do this only once for each side. Afterwards, you can continue flashing without the `-bl` argument. 

```sh
qmk flash -kb bakekujira/rev1 -km default -bl dfu-util-split-left
qmk flash -kb bakekujira/rev1 -km default -bl dfu-util-split-right
```

## To Flash

Once you've set the handedness, you can continue flashing everytime you make a change with the following to both sides:

```sh
qmk flash -kb bakekujira/rev1 -km default
```

```sh
make bakekujira:default
```

