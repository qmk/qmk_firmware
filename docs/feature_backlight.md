# Backlighting

<!-- FIXME: Describe how backlighting works in QMK -->

## Backlight Keycodes

These keycodes control the backlight. Most keyboards use this for single color in-switch lighting.

|Key      |Description                               |
|---------|------------------------------------------|
|`BL_TOGG`|Turn the backlight on or off              |
|`BL_STEP`|Cycle through backlight levels            |
|`BL_x`   |Set a specific backlight level between 0-9|
|`BL_ON`  |An alias for `BL_9`                       |
|`BL_OFF` |An alias for `BL_0`                       |
|`BL_INC` |Increase backlight level                  |
|`BL_DEC` |Decrease backlight level                  |
