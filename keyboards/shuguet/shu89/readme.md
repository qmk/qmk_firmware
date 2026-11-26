# SHU89

An 89-key split TKL with open-source PCBs and 3D printed cases, powered by a pair
of RP2040 controllers.

* Keyboard Maintainer: [shuguet](https://github.com/shuguet)
* Based on the original handwired keyboard by [jurassic73](https://github.com/jurassic73/split89)
* Hardware Supported: RP2040

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb shuguet/shu89 -km default

Flashing example for this keyboard:

    qmk flash -kb shuguet/shu89 -km default

Both halves run the same firmware and each must be flashed.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools)
and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide)
for more information.
Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left most key on the half you want to reset,
  (likely Esc or F6, if following standard keymap) and plug that half in.
  This also clears the stored settings, which is the way to undo a bad lighting
  or keymap state.
* **Physical reset button**: Double-press the button next to the USB port on the side
  of the case
* **Keycode in layout**: Press the key mapped to `QK_BOOT`, on `Fn` + `Esc` in the
  default keymap

## Lighting

The default lighting is the `alphas_mods` animation, which colours the modifier
keys differently from the alphas using the `LED_FLAG_MODIFIER` flags already set
in `keyboard.json`. On top of that the keyboard adds two indicators:

* Caps Lock glows red while it is active
* holding a layer dims every key that does nothing on that layer, leaving only
  the keys that are bound

Either can be turned off from a keymap by adding a `config.h` next to your
`keymap.c` or `keymap.json`:

```c
#pragma once

#define SHU89_CAPS_LOCK_INDICATOR 0
#define SHU89_LAYER_INDICATOR 0
```

Both default to `1`.

The alpha and modifier colours come from the `rgb_matrix` settings in
`keyboard.json`, so they are changed there or at runtime. The Caps Lock colour is
its own setting, given as an HSV hue and saturation, and defaults to pure red:

```c
#define SHU89_CAPS_LOCK_HUE 170  /* blue */
#define SHU89_CAPS_LOCK_SAT 0    /* 0 gives white */
```

Its brightness always follows the current RGB brightness, so it dims with the
rest of the board.

A keymap that wants to replace the lighting entirely can instead define
`rgb_matrix_indicators_advanced_user()` and return `false`.
