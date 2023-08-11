# p4yne's keymap for the bm65iso

* Eight layers (DE, LYR_SW_MEDIA, MOUSE_DSKTP_NAV, DYN_MACRO_NUMPAD_LEADER, GAMING, US, US_SHIFTED, DE_FLAG_LIGHTNING)
* Different color for each layer (DRK_RED, RED, MAGENTA, PURPLE, DRK_GOLD, DRK_BLUE, BLUE, DRK_RED)
* Keys with something else defined than KC_TRNS are lit up in the layer color, so you easily can see which keys have some function defined
* Custom layer types for KC_TRNS keys to let lower layer shine through, or stay black/off
* Custom lighting based on layer, key and led flag 
* Caps-Lock lights up when active
* Some leader shortcuts defined - nothing useful yet
* Some space cadet keys defined for easier insertion of () and {}
* Bootmagic lite enabled via default settings so you can plug in the keyboard while holding esc to land in bootloader mode
* Manages all this and still fits in to the program memory

Make example for this keyboard (after setting up your build environment):

    make kprepublic/bm65hsrgb_iso:p4yne

Flashing example for this keyboard:

    make kprepublic/bm65hsrgb_iso:p4yne:flash

Keyboard Maintainer: **[p4yne](https://github.com/p4yne)**
