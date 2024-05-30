# yacobo

* Keyboard Maintainer: [Stephen Edwards](https://github.com/sje-mse)
* Hardware Supported: IBM 101-key Model M with Yacobo replacement control boards.

Based on ModelH by jhawthorn.

# Build Directions

1. Set up a QMK build environment
2. Copy the contents of this "firmware" folder to a new folder `qmk_firmware/keyboards/yacobo`
3. Connect a suitable STM32F103C8T6 Blue Pill device with stmduino firmware.
4. qmk compile yacobo:default
5. qmk flash yacobo:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
