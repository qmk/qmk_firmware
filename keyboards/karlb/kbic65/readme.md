# Planck

![KBIC65 top-down view](https://github.com/b-karl/KBIC65/blob/main/img/photoshoot/full_keyboard_straight_above.jpg)

A compact 40% (12x4) ortholinear keyboard kit made and sold by OLKB and Massdrop. [More info on qmk.fm](https://qmk.fm/planck/)

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
