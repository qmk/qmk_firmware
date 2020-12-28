# Lx3 Whale 75

* PCB/QMK maintainer: [ebastler](https://github.com/ebastler)
* Keyboard designer: Lx3
* Support Discord channel: [discord.gg/UC8gTdVnsj](https://discord.gg/UC8gTdVnsj)
* Hardware supported: Whale 75
* Hardware availability: Groupbuy

## Keyboard specs
* Programmable via QMK and VIA
* 75% form-factor
* Centered top side USB-C connector
* ANSI and ISO layout, split and 2u backspace, regular or winkeyless bottom row
* Rotary encoder (Alps EC11 style) or F13 key in top right
* Adressable RGB underglow (18 LEDs)
* Single-color 3mm in-switch-LEDs
* 3 indicator LEDs 
* Powered by STM32F303C MCU
* No physical reset/boot switch - just bridge-able pins
* Bootmagic Lite on ESC key allows for easy flashing
* Native USB bootloader - no need for programming dongles

## Default keymap layout binds
Layer 1 toggle: FN key (to the right of ralt, left of the arrow cluster)

Alternate layer hardware control keys (All on layer 1):
* Esc: Enable/disable underglow
* F1/F2: lower/increase underglow brightness
* F3/F4: lower/increase backlight brightness
* F5/F6: lower/increase underglow hue
* F7/F8: lower/increase underglow saturation
* F9/F10: previous/next underglow effect

Encoder mapping (Layer 0):
* CCW/CW: Decrease/Increase volume
* Click: Mute audio

Encoder mapping (Layer 1):
* CCW/CW: Previous/Next track
* Click: Play/Pause
