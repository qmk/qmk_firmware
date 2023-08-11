# MechMerlin's DZ60 Keymap

The purpose of this keymap is to provide examples on how to do some common QMK features. 

Make example for this keyboard (after setting up your build environment):

    make dz60:mechmerlin

## Merlin's DZ60 Hardware Info
---

The DZ60 is a 60% pcb produced by KBDFans. It comes in two variants, USB Mini B and USB C. It supports many many layouts. It also supports both backlight and RGB underglow. The USB C variant does not have a hardware reset switch. USB C to C is not supported. 

Merlin's DZ60 uses
- Layout B, in QMK this is LAYOUT_60_b_ansi. 
- USB C
- 50g Zilents
- Arrows are 78g Zilents
- KPRepublic XD64 Case

## Layers
---

Merlin's keymap has three different layers. To switch layers you can use the `MO(X)` keycode, where `X` is the layer you want to switch to. 

### _BL

This is the base layer also known as layer 0. It is a standard QWERTY layout. It has the `_FL` layer switch key. 

### _FL

This is the function layer also known as layer 1. It utiizes the following:
- Function Keys
- Navigation Keys
- Audio keys such as Mute, Volume Down and Volume Up. 
- `_CL` layer switch key 

### _CL

This is the control layer also known as layer 2. It utilizes the following:
- RGB Controls
- `RESET` key

## Non Standard Keycodes
---
### RESET

As long `BOOTMAGIC_ENABLE` is set to `yes` in `rules.mk`, the DZ60 can be put into bootloader mode by holding the `Escape` key while plugging in. However sometmes this doesn't work or is troublesome to do, might as well use the `RESET` keycode to accomplish this. 

### RSFT_T(KC_SLSH)

Layout B is missing the `?` key and is instead replaced with a `right shift`. This keycode makes it so that the key can be tapped for `?` and held for `right shift`. 

### LCTL_T(KC_CAPS)

`Caps Lock` is only ever used by tapping, why not use it as a `control` key when held? This keycode makes it so that the key can be tapped for `caps lock` and held for `control`. 


## RGB Lighting
---

### RGBLIGHT_SLEEP

This is set in `mechmerlin/config.h` so that when the computer goes to sleep, the RGB lights will also go to sleep on the keyboard. They will turn back on when the computer wakes. 

### RGB Underglow Color: Yellow

This is set in `mechmerlin/keymap.c` in the `matrix_init_user` function. The list of available colors can be found in [`quantum/color.h`](https://github.com/qmk/qmk_firmware/blob/master/quantum/color.h).
