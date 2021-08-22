# KBIC65

![KBIC65 top-down view](https://github.com/b-karl/KBIC65/blob/main/img/photoshoot/full_keyboard_straight_above.jpg)

A 65%/70 key FR4-stack open-source keyboard with some design optimizations for wireless. For more info visit the [KBIC65 website](https://karlb.eu/kbic65/) or the [GitHub repo](https://github.com/b-karl/KBIC65).

* Keyboard Maintainer: [Karl Berggren](https://github.com/b-karl)
* Hardware Supported: [KBIC65](https://github.com/b-karl/KBIC65)
* Hardware Availability: Open-source design [available on GitHub](https://github.com/b-karl/KBIC65)

Make example for this keyboard (after setting up your build environment):

```
 qmk compile -kb karlb/kbic65 -km default
```


See the [QMK setup documentation](https://docs.qmk.fm/#/newbs_getting_started) to set up the QMK tools. I recommend flashing using

```
 qmk flash -kb karlb/kbic65 -km default
```

Firmware and default keymap tested using a KBIC65 with an Elite-C rev 4 controller.
