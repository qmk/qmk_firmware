# cornifi

![cornifi keyboard](https://i.imgur.com/Q7B3VX8.jpeg)

The cornifi keyboard is a split keyboard based on the [corne](https://github.com/foostan/crkbd) with the physical layout of the [fifi](https://github.com/raychengy/fifi_split_keeb).

* Keyboard Maintainer: [v3lmx (github)](https://github.com/v3lmx)
* Hardware Availability: [v3lmx/cornifi (github)](https://github.com/v3lmx/cornifi)

Make example for this keyboard (after setting up your build environment):

    make cornifi:default

Flashing example for this keyboard:

    make cornifi:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Hold down the `boot` button and press the `reset` button
* **Keycode in layout**: Press the key mapped to `TD_BOOT` twice if it is available

## Keymap

It is recommended to make your own keymap using the [external userspace feature(https://docs.qmk.fm/newbs_external_userspace).

You can find an example here: [v3lmx qmk userspace](https://github.com/v3lmx/qmk_userspace)
