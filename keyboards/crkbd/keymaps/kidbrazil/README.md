# KidBrazil's custom CRKBD Layout

![Crkbd](https://user-images.githubusercontent.com/736191/40575636-6fba63a4-6123-11e8-9ca0-3f990f1f9f4c.jpg)

This is a simple layout that I use for both programming and gaming. It is very
closely based on the original CRKBD layout with some modifications to the
position of CTRL and SHIFT.

## Layers
This keymap includes a total of 4 Layers:
- QWERTY
- NUMBERS
- SYMBOLS
- GAMING
- WEAPONS

The first three layers are pretty self explanatory and follow closely the
default keymap for this keyboard. The magic really starts to happen with the
gaming layer.

### Gaming Layer
The gaming layer can be toggled on/off from the SYMBOLS layer. Once on the
gaming layer it will stay there until you toggle it off again. The gaming layer
includes normal WASD and most of the keys FPS games use on the left hand. On the
right hand we have F1-F12 and a few other special keys for games that require
it.

### Weapon
The weapon layer is a momentary layer that can only be reached from the gaming
layer. This layer preserves the left hand almost unchanged, except for when the
layer is activated the top row becomes NUM 1 - 6 for wepon selection. The right
hand is KC_TRNS the whole way so basically it is still the gaming layer.

## Custom Font
This keymap includes a custom font for my LooseTransistor logo. It is fine if
you want to use it I certainly don't mind but if you want your own, just replace
the glcdfont file here and you should be fine.

Alternatively you could remove the font config line from the config.h file so it
will use the default QMK one.

## OLED
This Keymap is setup to use the newer OLED API. Some work has been done to
customize this with showing layer and USB information. I also tried my best to
get a dormant / sleep state going but it is hit or miss and often only works on
the master hand.

### TODO
- Fix OLED and Backlight so they turn off when the computer sleeps, currently
  only the left hand does that and the LEDs still stay on.
- Wait for Spit_common to be implemented in CRKBD and revisit the special color
  layers and animations
