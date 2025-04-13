# franky36

Franky36 is 36 key compact handwired split keyboard that uses single RP2040-Zero controller.

* Keyboard Maintainer: [Grigory Avdyushin](https://github.com/avdyushin)
* Hardware Supported: RP2040-Zero
* Hardware Availability: Handwired [franky36](https://github.com/avdyushin/franky36)

Make example for this keyboard (after setting up your build environment):

    make franky36:default

Flashing example for this keyboard:

    make franky36:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Hold down the reset button on the controller and plug in the keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
