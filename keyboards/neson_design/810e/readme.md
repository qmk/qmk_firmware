# Neson Design 810E keyboard

* Keyboard Maintainer: [astro](https://github.com/yulei)
* Hardware Supported: Neson Design 810E keyboard
* Hardware Availability: [Public GB](https://geekhack.org/index.php?topic=120539.0)

Make example for this keyboard (after setting up your build environment):

    make neson_design/810e:default

Flashing example for this board:

    make neson_design/810e:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard.
* **Physical reset button**: Shortcut *BOOT0* pin and than plug in the keyboard.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available.
