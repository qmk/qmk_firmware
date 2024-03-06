# Arrow Mechanics WINGS Mark 1

![Arrow Mechanics WINGS Mark 1](https://i.imgur.com/oQkDmSu.png)

94-key ErgoDox-inspired SPLIT keyboard by [Arrow Mechanics](https://www.arrowmechanics.com/)

- Keyboard Maintainer: [arrowmechanics](https://github.com/arrowmechanics/)

Make example for this board (after setting up your build environment):

```sh
qmk compile -kb arrowmechanics/wings -km default
```

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Features

- 94 low profile keys with GATERON Low Profile 2.0 hotswap sockets
- RGB diode under each key for WS2812-driven lightintg with [RGB Matrix](https://docs.qmk.fm/#/feature_rgb_matrix)
- 2 rotary encoders with push-switches (one per each half)
- Buzzers for sound effects and/or [Music Mode](https://docs.qmk.fm/#/feature_audio?id=music-mode)
- Handy magnetic connectors for joining the halves together or splitting with the use of dedicated cable
- Anti-slippery pads with magnetic expand legs for conveniently adjusting height/lean
- RP2040 Chip + 16MB Flash memory - Dual-core Cortex M0+

## Bootloader

- To enter the bootloader hold down the BOOT push-button on power-up or reset.
