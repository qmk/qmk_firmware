# Backlighting

<!-- FIXME: Describe how backlighting works in QMK -->

## Backlight Keycodes

These keycodes control the backlight. Most keyboards use this for single color in-switch lighting.

|Name|Description|
|----|-----------|
|`BL_x`|Set a specific backlight level between 0-9|
|`BL_ON`|An alias for `BL_9`|
|`BL_OFF`|An alias for `BL_0`|
|`BL_DEC`|Turn the backlight level down by 1|
|`BL_INC`|Turn the backlight level up by 1|
|`BL_TOGG`|Toggle the backlight on or off|
|`BL_STEP`|Step through backlight levels, wrapping around to 0 when you reach the top.|
