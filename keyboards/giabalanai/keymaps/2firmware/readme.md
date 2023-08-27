# A personal keymap for giabalanai with RGBLIGHT_ENABLE = yes in rules.mk, which 3araht is using.
"2firmware" requires writing the firmware separately to left and right keyboards in order to have different functionality when USB cable is connected to the left side keyboard. It can be used without the right side.
(EE_HANDS is defined in 2firmware/config.h).  

When USB cable is connected to the left side keyboard, QWERTY layout is used by default.


Use below for writing the firmware to the left side keyboard.
> make giabalanai:2firmware:avrdude-split-left  

Use below for writing the firmware to the right side keyboard.
> make giabalanai:2firmware:avrdude-split-right  
