# MechMerlin's Userspace v0.1.1

This is a collection of my most commonly used QMK features. 

A majority of my keyboards are smaller than 75%, ANSI, and staggered. 

## Layers
----

### _BL (Base Layer)
Typical standard QWERTY keymap.

### _FL (Function Layer)
This layer is commonly accessed via `MO(_FL)` on the base layer. It consists of your typical function key F1 through F12 and some RGB and Backlight controls. 

### _AL (Arrow Layer)
This layer is only present on my 60% boards. I habitually use the bottom right modifiers as arrows. 

### _CL (Control Layer)
This is not defined in here as it's present only on `LAYOUT_66` boards, or to be specific, my clueboard. It currently uses the default clueboard controls.

## Custom Keycodes
----

### KC_FNX (Fn Extended)

`KC_FNX` functions as a hold for `MO(X)` and tap for `TG(Y)`. Layer X and Y are different layers. 

It is used primarily on my `LAYOUT_60_ansi` boards as my regular toggle (the 1u key to the right of right shift), is not present there. 

### KC_CTCP (Control Caps)

This is just a wrapper for `CTL_T(KC_CAPS)`. This is a hold for control and tap for caps lock. 

## QMK Features
----

### RGBLIGHT_SLEEP

Ensures that when my computer is in sleep mode, the keyboard underglow lights will also be off. 
