# TSUBASA

![tsubasa](https://github.com/kuriatsu/TSUBASA/blob/main/image/tsubasa.jpg)

Hotswap split row-staggerd keyboard with an OLED and a rotary encoder

* Keyboard Maintainer: [kuriatsu](https://github.com/kuriatsu)
* Hardware Supported: ProMicro
* Hardware Availability and Build Guide: [Repository](https://github.com/kuriatsu/TSUBASA)

Make example for this keyboard (after setting up your build environment):

```bash
qmk compile -kb handwired/tsubasa -km default
```

Flashing example for this keyboard:

```bash
qmk flash -kb handwired/tsubasa -km default
```

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

**Physical reset**: Ground Reset of ProMicro
