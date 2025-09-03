# Pteron56

![Pteron56](https://i.imgur.com/kt1RSi9h.jpg)

The Pteron56 is a 56-key vertically staggered ortholinear keyboard with a 15 degree inward tilt per hand. 

Initially developed by [FSund](https://github.com/fsund), this keyboard was designed to potentially reduce wrist and typing strain by offsetting the keys in a manner that mimics the natural stagger of the human hand with 4 thumb keys per side arranged around an ~85mm arc to mimic the swimg of one's mighty thumbs.

Users have reported reduced finger movement, reduced wrist movement, and better typing comfort and swiftness with the Pteron layouts compared to a standard keyboard. 

* Keyboard Maintainer: [Alex Moore](https://github.com/kraken-jokes)
* Hardware Supported:
    * PCB: Pteron56v0.2, Pteron56v0.2hsu, Pteron56v0.3, Pteron56v0.4e
    * MCU: Pro-Micro, Elite-C
* Hardware Availability: moorekeys.etsy.com. Open source though so it varies.

Make example for this keyboard (after setting up your build environment):

    make pteron56:default

Flashing example for this keyboard:

    make pteron56:default:flash
  
See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader thusly:
* **Keycode in layout**: Press and hold the right most thumb key on the left side (LT(2(KC_ALT)) and while that is held, hit the top left key on the left side of the keyboard (KC_ESC) which will reset the board and enter bootloader mode. 
Thumb and pinky is my method, but do what you will.
