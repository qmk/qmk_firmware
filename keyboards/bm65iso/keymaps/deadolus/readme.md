# Deadolus' keymap for the bm65iso

* Six layers (even though three are mostly empty)
* Different color for each layer (r,g,b,c,m,y)
* **Keys with something else defined than KC_TRNS are lit up in the layer color, so you easily can see which keys have some function defined**
* Caps-Lock lights up when active and on layer 0
* Some leader shortcuts defined - nothing useful yet
* Some space cadet keys defined for easier insertion of () and {}
* Bootmagic lite enabled via default settings so you can plug in the keyboard while holding esc to land in bootloader mode
* Manages all this and still fits in to the program memory

Make example for this keyboard (after setting up your build environment):

    make bm65iso:deadolus

Flashing example for this keyboard:

    make bm65iso:deadolus:flash

Keyboard Maintainer: **[deadolus](https://github.com/deadolus)**
