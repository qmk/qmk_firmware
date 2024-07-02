# Dilemma Max (4x6+4)
This keyboard is an upsized version of the [3x5+3 Dilemma](../3x5_3/).

The Dilemma Max is available at [bastardkb.com](https://bastardkb.com).

## Layer and capslock indicators
The Dilemma Max comes with layer indicators using the underglow LEDs and a capslock indicator using the outermost columns of per-key LEDs.

The brightness of both indicators is boosted to counteract them being perceived as dimmer (the underglow has to go through an acrylic plate, and pure red appears dimmer than other colors on these LEDs). This has the side effect that the indicators are visible even if the current RGB brightness is set to zero.

The brightness boosts can be adjusted from your keymap using two defines:
```c
#define LAYER_INDICATOR_BRIGHTNESS_INC 22
#define CAPSLOCK_INDICATOR_BRIGHTNESS_INC 76
```

A value of 255 would make the indicators appear at maximum brightness regardless of the RGB effect brightness. A value of 0 will disable the brightness boosts.
