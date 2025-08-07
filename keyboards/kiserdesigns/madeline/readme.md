# Madeline

![Madeline](https://i.imgur.com/MBT5kg2h.jpg)

*A cool QAZ-Alice hybrid designed based on the Adalyn by [Marv](https://github.com/MarvFPV/Adalyn) with a PCB by [Rossman360](https://github.com/Rossman360)*
* Keyboard Maintainer: [NCKiser](https://github.com/NCKiser)
* Hardware Supported: Madeline PCB, rp2040
* Hardware Availability: kb.rubybuilds.com

Make example for this keyboard (after setting up your build environment):

    make kiserdesigns/madeline:default

Flashing example for this keyboard:

    make kiserdesigns/madeline:default:flash
    
See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
## Bootloader
Enter the bootloader in 3 ways:
* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly double-tap the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
