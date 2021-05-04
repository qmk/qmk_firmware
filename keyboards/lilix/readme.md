# Lilix

Lilix is a spin-off of [Helix](https://github.com/MakotoKurauchi/helix), with a completely new firmware.

* Keyboard Maintainer: [Elizabeth Bodaneze](https://github.com/tanshoku)
* Hardware Supported: Helix rev2 PCB, Pro Micro
* Hardware Availability: [PCB & Case Data](https://github.com/MakotoKurauchi/helix)

Make example for this keyboard (after setting up your build environment):

    make lilix:default

Flashing example for this keyboard:

    make lilix:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).



## Customizing:


### RGB animations

Uncomment the animations you want on `config.h`:

```C
/*== choose RGB light animations ==*/
//#define RGBLIGHT_EFFECT_BREATHING
//#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
//#define RGBLIGHT_EFFECT_SNAKE
//#define RGBLIGHT_EFFECT_KNIGHT
//#define RGBLIGHT_EFFECT_CHRISTMAS
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
//#define RGBLIGHT_EFFECT_RGB_TEST
//#define RGBLIGHT_EFFECT_ALTERNATING
//#define RGBLIGHT_EFFECT_TWINKLE
```


### LGBT+ flags

Edit your `keymap.c` to include them:

```C
#define LGBT_FLAGS

#ifdef LGBT_FLAGS
    #include "lgbtflags.h"
#endif
```

...then pick the ones you want by uncommenting them on `lgbtflags.h`:

```C
//Rainbow LGBT+ pride flag
#define LGBT_FLAGS_PRIDE

//Gender flags
//#define LGBT_FLAGS_TRANSGENDER
//#define LGBT_FLAGS_NON_BINARY
//#define LGBT_FLAGS_NON_BINARY_VERTICAL
//#define LGBT_FLAGS_AGENDER
//#define LGBT_FLAGS_GENDERFLUID
//#define LGBT_FLAGS_GENDERQUEER
//#define LGBT_FLAGS_DEMIBOY
//#define LGBT_FLAGS_DEMIGIRL

//Sexuality
//#define LGBT_FLAGS_ACE
//#define LGBT_FLAGS_PAN
//#define LGBT_FLAGS_POLY
//#define LGBT_FLAGS_LESBIAN
//#define LGBT_FLAGS_BI
```

...if you want to remove the rainbow flag, which is the first one, remember to edit the leading commas at the list in `const rgblight_segment_t* const PROGMEM lgbt_rgb_layers[] = RGBLIGHT_LAYERS_LIST(` so it compiles correctly.


### Copyright notice for the art:

The pixel art is provided here for educational purposes only. If you still wish to use or modify it, please contact me through [@monoxromatik](https://twitter.com/monoxromatik) on Twitter or one of the links on my [DeviantArt page](https://www.deviantart.com/idioticbat).
