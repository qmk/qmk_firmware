# Sha Default Keymap

The default keymap uses a QWERTY base layout, with a secondary Colemak base layout. Both layouts have symbol placement adjustments on the outer columns, and editing keys and layers on the thumb keys.

There are two extended layers:

* SYMBOL: For typing additional symbols. Activated by layer-tap on the main left thumb key.
* FUNCTION: For function and navigation keys. Activated by layer-tap on the main right thumb key.

When using a Waveshare RP2040-Matrix, the [RGB Light - Lighting Layers](https://docs.qmk.fm/#/feature_rgblight?id=lighting-layers) feature is used to demonstrate how the 5x5 RGB LEDs can indicate keyboard state. The indicators are:

* Base layer on the outer LED ring: QWERTY = yellow, Colemak = cyan
* Lock status indicators using the center 3x3 LEDs: Scroll lock = blue, Caps lock = green, Num lock = red