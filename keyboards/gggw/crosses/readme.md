# Crosses by Good Great Grand Wonderful

![crosses](https://ergokeyboards.com/cdn/shop/files/3x5-dual-tb-oled.png)

Our thumbs evolved to give us dexterity; shouldn't our keyboards evolve with them? 

* Keyboard Maintainer: [Good Great Grand Wonderful LLC](https://github.com/Good-Great-Grand-Wonderful)
* Hardware Supported: 
 * Matrix configurations in: 3x5, 3x6, 4x6 boards with a three key thumb cluster.
 * Trackballs!
 * OLED Displays
 * Any SPI / I2C breakout using a 6P JST SH for SPI and a 2.54mm breakout for I2C.
* Hardware Availability: https://ergokeyboards.com

### Compiling (after setting up your build environment):

```bash
qmk compile -kb gggw/crosses/<LAYOUT>/<REV> -km default
```

### Flashing example for this keyboard:

```bash
qmk flash -kb gggw/crosses/<LAYOUT>/<REV> -km default
```

#### Concrete example:

`<LAYOUT>` is one of 3x5, 3x6, 4x6

`<REV>` is the firmware required for your thumbclusters which is one of: rev1, rev2

Flashing a 3x6 revision 2 model

```bash
qmk comfile -kb gggw/crosses/3x6/rev2 -km default
```

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader one of two ways:

* **Physical reset button**: Double-tap the reset button on the RP2040
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
