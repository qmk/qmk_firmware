# HLB H60-H / H60-S

* Keyboard Maintainer: [H3lli0n](https://github.com/H3lli0n/)
* Hardware Supported: proprietary PCB using RP2040;
* Hardware Availability: PCB for HLB 60% projects like PoorKoi 1, PoorKoi 2

HLB H60-H / H60-S is a multi project pcb supporting various layout. With hotswap you have tsangan bottom row with 3U/1U/3U spacebars and with solder you can use a 8U wire for 10U spacebar.
PCB comes in solder format `hlb60_s` and hotswap format `hlb60_h`. After checking what PCB you own and setting up your build environment, you can compile the default keymap by using one of the options below.

Make example for this keyboard (after setting up your build environment):  

    make hlb/hlb60/<version>:default

Flashing example for this keyboard:

    make hlb/hlb60/<version>:default:flash
    
Where `<version>` can be `hlb60_s` or `hlb60_h`.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the thumb key on the left and plug in the keyboard. For the right side, hold the thumb key on the right and plug the keyboard.
* **Physical reset button**: 
  * Press and hold the BOOT0 button.
  * Press and release the NRST button.
  * Release the BOOT0 button.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
