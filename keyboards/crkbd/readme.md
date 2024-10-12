# Corne Keyboard (CRKBD)

![Crkbd](https://user-images.githubusercontent.com/736191/40575636-6fba63a4-6123-11e8-9ca0-3f990f1f9f4c.jpg)

A split keyboard with 3x6 vertically staggered keys and 3 thumb keys.
Also, it has the option that use extension keys and rotary encoders.

* Keyboard Maintainer: [foostan](https://github.com/foostan/) [@foostan](https://twitter.com/foostan)  
* Hardware Supported: Corne PCB
* Hardware Availability: [PCB & Case Data](https://github.com/foostan/crkbd)

Flash example for this keyboard of v1 - v3:

```sh
qmk flash -kb crkbd/rev1 -km default
```

Flash example for this keyboard of v4:

```sh
qmk flash -kb crkbd/rev4/standard -km default
```

Flash example for this keyboard of v4 mini:

```sh
qmk flash -kb crkbd/rev4/mini -km default
```

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

The Corne PCBs have a reset and boot buttons next to the TRRS jack to enter in to the bootloader.

Additionally, if you hold down the "Q" or "P" buttons when plugging in that half of the keyboard (per the default QWERTY layout), this will jump to the bootloader and reset the EEPROM (persistent storage).  This would normally be the very top corner-most position, but due to the breakaway column, it's left at Q and P for compatibility. 