# Katia

Katia is a split mechanical keyboard with a 6x3 column-staggered layout and three thumb keys per half. It uses hot-swap Cherry MX sockets with individually addressable per-key LEDs.

- Maintainer: [ikajdan](https://github.com/ikajdan)
- Hardware: [ikajdan/katia](https://github.com/ikajdan/katia)

The latest release of the hardware design files can be found on the [releases page](https://github.com/ikajdan/katia/releases/latest).

Make example for this keyboard (after setting up your build environment):

    make katia:default

Flashing example for this keyboard:

    make katia:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

To enter the bootloader:

- Hold the Bootmagic key while plugging in the USB cable: in the default keymap this is the `Q` position on the left half and the `P` position on the right half.
- Press the `QK_BOOT` key in the default keymap: enter layer 3 and press the top-left key on the half currently connected over USB.

Flash both halves of the keyboard. When connected by USB, each half appears as a separate device. The same firmware can be used for both halves.
