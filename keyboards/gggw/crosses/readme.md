# Crosses by Good Great Grand Wonderful

![crosses](imgur.com image replace me!)

*A short description of the keyboard/project*

* Keyboard Maintainer: [Good Great Grand Wonderful LLC](https://github.com/Good-Great-Grand-Wonderful)
* Hardware Supported: 
 * Matrix configurations in: 3x5, 3x6, 4x6 boards with a three key thumb cluster.
 * Trackballs!
 * OLED Displays
 * Any SPI / I2C breakout using a 6P JST SH for SPI and a 2.54mm breakout for I2C.
* Hardware Availability: *Links to where you can find this hardware*

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb gggw/crosses/<LAYOUT> -km default

Flashing example for this keyboard:

    qmk flash -kb gggw/crosses/<LAYOUT> -km default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Double-tap the reset button on the RP2040
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
