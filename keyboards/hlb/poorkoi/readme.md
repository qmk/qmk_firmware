# HLB PoorKoi

60% HLB PoorKoi's pcb is based on 4pplet/waffling60/rev_e (https://github.com/4pplet/waffling60).
* PCB features tsangan layout with ansi/iso layouts as well as split spacebar, split left/right shift, stepped capslock.
* PCB feature dedicated graphic art and flex cut were removed.

Regarding source code we added extra features with dedicated custom keycode **L_INDIC**: 

* LED indicator and capslock indicator are managed through lightning layers
* Layer indicator is shown even if rgb underglow is off
* Added a led indicator when custom keycode L_INDIC is on/off
  * Blink on top when off
  * Blink on bottom when on

Make example for this keyboard (after setting up your build environment):

    make hlb/poorkoi:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard.
* **Physical reset button**: Short the reset pins on the back of pcb with tweezers.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available.
