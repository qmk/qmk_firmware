# Kimiko

## Rev2

A split keyboard with 4x6 vertically staggered keys and a Kyria style thumb thumb cluster.

![Kimiko Rev2](https://i.imgur.com/TBP8Bcrh.jpg)

- Keyboard Maintainer: [BenRoe](https://github.com/BenRoe/) [@keycapsss](https://twitter.com/keycapsss)
- Hardware Supported: Pro Micro 5V/16Mhz and compatible
- Hardware Availability: [Keycapsss.com](https://keycapsss.com)

### Features (Rev2)

- 62 Per key RGB led's (SK6812 Mini-E)
  - RGB Matrix is enabled as default in rules.mk
  - The effects can be configured in config.h
- Support for 1 rotary encoder per side (two possible positions)
- Support for 1 OLED display per side  
  - 128x32 (SSD1306) or Nice!View are supported  
  - With 1 OLED on each side, they have to be the same  
  - Default configuration for 128x32 OLED  


Make firmware .hex for this keyboard (after setting up your build environment):

```bash
qmk compile -kb keycapsss/kimiko/rev2 -km rev2
```

Use [QMK Toolbox](https://github.com/qmk/qmk_toolbox) to flash the firmware hex file to the keyboard controller.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Rev1

A split keyboard with 4x6 vertically staggered keys and thumb keys.

![Kimiko Rev1](https://i.imgur.com/md6V6Eoh.jpg)

- Keyboard Maintainer: [BenRoe](https://github.com/BenRoe/) [@keycapsss](https://twitter.com/keycapsss)
- Hardware Supported: Pro Micro 5V/16Mhz and compatible
- Hardware Availability: [Keycapsss.com](https://keycapsss.com)

### Features (Rev1)

- Per key RGB led's (SK6812 Mini-E)
- 6 underglow RGB led's per side (SK6812 Mini)
- Support for 1 rotary encoder per side (two possible positions)

Make firmware .hex for this keyboard (after setting up your build environment):

```bash
qmk compile -kb keycapsss/kimiko/rev1 -km default
```

Use [QMK Toolbox](https://github.com/qmk/qmk_toolbox) to flash the firmware hex file to the keyboard controller.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
