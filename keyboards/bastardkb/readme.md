# Information for Various BastardKB Hardware

## Handedness Pin on Elite-C Holder
The [Elite-C Holder](https://github.com/Bastardkb/Elite-C-holder) supports setting [handedness by pin](https://docs.qmk.fm/features/split_keyboard#handedness-by-pin) on pin F1 of an Elite-C.

To utilise this, you must be using an Elite-C compatible development board (with the bottom 5 pins broken out) and install the necessary resistor. The following firmware configuration can be made in your keymap directory:
```Makefile
# rules.mk

PIN_COMPATIBLE = elite_c
```

```c
// config.h
#pragma once

#define SPLIT_HAND_PIN F1
#define SPLIT_HAND_PIN_LOW_IS_LEFT
```
