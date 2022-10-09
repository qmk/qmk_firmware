# Keyhive Sofle Keyboard

![SofleKeyboard version 2.1 RGB Keyhive](https://i.imgur.com/WH9OoWuh.jpg)

Sofle is 6×4+5 keys column-staggered split keyboard. Based on Lily58, Corne and Helix keyboards.

For details about the keyboard design, refer to Josef's blog: [Sofle Keyboard - a split keyboard based on Lily58 and Crkbd](https://josef-adamcik.cz/electronics/let-me-introduce-you-sofle-keyboard-split-keyboard-based-on-lily58.html)

Build guide: [Keyhive Sofle RGB build guide](https://github.com/keyhive/build_guides/blob/master/docs/keyboards/sofle-rgb.md)

* Keyboard Maintainer: [Winder](https://github.com/winder)
* Hardware Supported: Keyhive Sofle RGB, ProMicro / Elite-C
* Hardware Availability: [Keyhive](https://keyhive.xyz/shop/sofle)

### Acknowledgements

* Solartempest - the image on this page and most of the code is either copied directly or inspired by their fork. [Solartempest's fork.](https://github.com/solartempest/qmk_firmware/tree/master/keyboards/solartempest/sofle).
* [Keyhive fork](https://github.com/keyhive/qmk_firmware) defined all of the board settings.

# Supported Keymaps

The keyhive schematic has been slightly modified compared to the open source sofle and not all keymaps are compatible.

* **default**: Basic functionality, no rgb, no VIA.
* [keyhive_via](../keymaps/keyhive_via/readme.md) - Includes rgblighting and special support for remapping encoders with VIA.
* **Other**: may work but backwards compatibility is not guaranteed or tested.

# VIA Support
As of 1.3.1, the VIA tool does not support Keyhive/Sofle V2 out of the box.
See [keyhive_via](../keymaps/keyhive_via/readme.md) for details about configuring and using VIA.

# Compiling

Make example for this keyboard (after setting up your build environment):

    make sofle/keyhive:default

## Flashing

Flash using the correct command below (or use QMK Toolbox). These commands can be mixed if, for example, you have an Elite C on the left and a pro micro on the right.

Press reset button on the keyboard when asked.

Disconnect the first half, connect the second one and repeat the process.

    # for Pro Micro-based builds
    make sofle/keyhive:default:avrdude-split-left
    make sofle/keyhive:default:avrdude-split-right

    # for Elite C or DFU bootloader builds
    make sofle/keyhive:default:dfu-split-left
    make sofle/keyhive:default:dfu-split-right

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
