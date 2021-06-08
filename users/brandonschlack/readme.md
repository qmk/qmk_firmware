# Overview

My QMK home. I feel as though I stand on the shoulders of giants, for a lot of my code here is borrowed and adapted from so many contributors here, and that I hope my code here can help or inspire others.

## Layers, Handlers, and Macros
### Layers

I have some predefined layer names for keyboards:
* **_BASE**: Default Layer, QWERTY layout.
* **_FN1**: Function Layer for 60% and above, and additional macros and shortcuts on 50% and below. 
* **_LOWER** and **_RAISE**: Function layers for 40%

and macropads:
* **_REEDER**: Shortcuts for [Reeder.app](https://reederapp.com/), my RSS feed reader
* **_MEDIA**: Media controls
* **_NAVI**: Navigation macros, for changing tabs and scrolling
* **_KARABINER**: Generic macro keys, meant to be customized per app with [Karabiner](https://pqrs.org/osx/karabiner/)

#### Protected Layers
I have some named "protected" layers, meant to be at the end of the layer list for changing keyboard settings and features.

* **KEYMAP_LAYERS**: Add additional layers in keymap.
* **_AUDIO**: Audio feature controls.
* **_LIGHT**: RGB Light/Matrix feature controls.
* **_ADJUST**: General keyboard settings and toggles. Can also contain RGB and Audio controls on larger boards that don't need and extra layer for those controls.

### EEPROM User Config

I have a custom userspace config implemented to save settings on the board to persist across shutdowns. I currently store:

* rgb_layer_change - a toggle for using RGB themes for layer indication
* rgb_theme - a pointer to the currently set RGB Theme

### Process Handlers

### Keycode Aliases

I am a macOS user and so a lot of my aliases are 

### Macros


## Tap Dances

### Tap Dance Trigger Layer

## RGB
### RGB Theme
