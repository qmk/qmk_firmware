# blu vimclutch

[blu006](https://github.com/blu006)'s vimclutch implementation using QMK

* Keyboard Maintainer: [blu006](https://github.com/blu006)
* Hardware Supported: [github link](https://github.com/blu006/vimclutch_hw)
* Hardware Vendors Listed on the Page

This keyboard is designed to be placed from left-to-right with the USB-B micro port aligned to the left side and the widest side horizontally aligned.  Some may call this the "transverse" orientation.  The two tactile buttons are for layer switching and are numbered from left-to-right.  The default state is for the leftmost layer to be active.  With the default layout, this is the "voice chat" mode which uses `F13` as a push-to-talk button.

On the default keymap, here's what happens with your clutch:
* On press, `ESC` and then `a` are pressed.
* On release, `ESC` is pressed

You can also use the shift key on your keyboard to jump to the end of line.

Here are some included keymaps and their modes to get you started:
* default: voice chat and vim clutch
* vc_i: the same as default but using `i` instead of `a`
* vim_ai: vim clutch only, selectable between `a` and `i`

Also includes a mode for single-keypress in case of "push to talk clutch"

Make example for this keyboard after setting up your development environment:

    make blu/vimclutch:default
      
Flashing example for this keyboard:

    make blu/vimclutch:default

## Bootloader

Reset button on the reverse side of the enclosure for initializing flashing.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
