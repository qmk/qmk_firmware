# unicomp/pc122/overnumpad_1xb

![unicomp/pc122/overnumpad_1xb](https://sharktastica.co.uk/resources/images/model_ms/shark_UB40T56_unicomp.jpg)

Will support the Unicomp PC122 keyboard

* Keyboard Maintainer: [Purdea Andrei](https://github.com/purdeaandrei)
* Hardware Supported: OverNumpad controller v1.Xb
* Hardware Availability:
  * [controller](https://github.com/purdeaandrei/overnumpad_controller_1xb)
  * [keyboard](https://www.pckeyboard.com/)

To place the keyboard into bootloader mode in order to flash it, hold the top-left key of the
left-side block of the keyboard, while plugging the board in. It's possible to accidentally
brick this feature, if the wrong firmware is flashed onto the keyboard. If that happens,
open up the keyboard, and press the RST&PROG button to enter bootloader mode.

Note: LAYOUT_all is incomplete, because certain pairs of possible key positions are mapped to the same matrix position:
* The hidden key position under the numeric keypad 2-unit vertical enter key overlaps with the key in the 1st column, 4th row of the left-side block (the one that usually comes with "Record" or "Print/Ident" printed on it by default)
* The hidden key position under the numeric keypad 2-unit horizontal 0 key overlaps with the key position that is normally hidden by a 2u vertical keypad plus key. (This key position is usually exposed as a Field + key, or as a keypad - key)
* The hidden key position under the 2-unit backspace key overlaps with F19.
* The hidden key position under the right-shift key overlaps with F20.
As such it's not possible to make a LAYOUT_all macro that shows all key position.
The user may still make use of these normally hidden key positions, by hiding the other key they overlap to (or by leaving them accessible but the other key must have the same keycode):
* To make use of the hidden key under the 2-unit vertical enter key, a 2-unit horizontal key could be used on the 4th row of the left-side block.
* To make use of the hidden key under the 2-unit horizontal keypad 0 key, a 2-unit vertical + key could be used.
* To make use of the hidden key under the backspace key, a 2-unit horizontal key could be used over what is normally F19 and F20.
* To make use of the hidden key under the right-shift key, a 2-unit horizontal key could be used over what is normally F20 and F21.
As such, mathematically there are 2 * 2 * 3 = 12 possible LAYOUT_all combinations, and we have chosen to only provide the default LAYOUT_all layout. If the user chooses to implement one or more of the above mods,
they can still make this firmware work with the single default LAYOUT_all, using the above information, by assigning keycodes to their conventional key position.

Make example for this keyboard (after setting up your build environment):

    make unicomp/pc122/overnumpad_1xb:default

Flashing example for this keyboard:

    make unicomp/pc122/overnumpad_1xb:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
