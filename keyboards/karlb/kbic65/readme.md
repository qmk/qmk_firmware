# KBIC65

![KBIC65 top-down view](https://github.com/b-karl/KBIC65/blob/main/img/photoshoot/full_keyboard_straight_above.jpg)

A 65%/70 key FR4-stack open-source keyboard with some design optimizations for wireless. For more info visit the [KBIC65 website](https://karlb.eu/kbic65/) or the [GitHub repo](https://github.com/b-karl/KBIC65).

* Keyboard Maintainer: [Karl Berggren](https://github.com/b-karl)
* Hardware Supported: [KBIC65](https://github.com/b-karl/KBIC65)
* Hardware Availability: Open-source design [available on GitHub](https://github.com/b-karl/KBIC65)

Firmware and default keymap have been tested using a KBIC65 with an Elite-C rev 4 controller.

## Build firmware

Make example for this keyboard (after setting up your build environment):

```bash
 qmk compile -kb karlb/kbic65 -km default
```

See the [QMK setup documentation](https://docs.qmk.fm/#/newbs_getting_started) to set up the QMK tools. I recommend flashing using

```bash
 qmk flash -kb karlb/kbic65 -km default
```

## Bootloader

Since the keyboard is designed to have an exposed ProMicro the bootloader can always be entered by short circuiting the `RST` and `GND` pins on the ProMicro. If the keyboard is configured with the default keymap, the bootloader can be entered by pressing `R_GUI/FN + B`


