# A tweaked keymap for Redox

This keymap modifies the [default keymap](https://github.com/qmk/qmk_firmware/tree/master/keyboards/redox) for the awesome [Redox keyboard](https://github.com/mattdibi/redox-keyboard) designed by Mattia Dal Ben.

![Modified Redox keymap](https://github.com/nrichers/qmk_firmware/blob/master/keyboards/redox/keymaps/nrichers/keymap.png)

## Changes to the default keymap ![#99fcbe](https://placehold.it/15/99fcbe/000000?text=+)

These keymap changes are meant to improve the usability of the layout in everyday use:

- Move `GUI` (`SUPER`) key to where default left `CTRL` and right `ALT` are - gives you two frequently used `CMD` keys on macOS where my brain expects them
- Move `/?` into usual location next to right `SHIFT` - the default flash from Falbatech put `\|` here (might not be the Redox default?), which felt unintuitive
- Put `\|` into bottom-left spot where `GUI` (`SUPER`) was - had to go somewhere and this bottom-left placement sort of balances with the almost bottom-right `/?`
- Change default `ESC` into `ESC` on tap, `CTRL` on hold - Love the UNIX-ey `CTRL` key location and wanted to keep `ESC` in the original position
- Change default `'` above right `SHIFT` into `'` on tap, `CTRL` on hold - Love the UNIX-ey CTRL key location, but it can give you 'left claw hand', which a second, mirrored `CTRL` key fixes
- Add `F11` and `F12` keys to two layers - needed on macOS if you want to control volume up and down from your keyboard (not shown, on a different layer)
- On thumb clusters: 
  - Left: Move `SPACE` closest to left thumb and move `BACKSPACE` to the right of that - put the key for 'getting it right' closest to your thumb and reduce usage of my right hand (purely personal preference)
  - Right: Move `ENTER` closest to right thumb and move `DEL` to the left of that - put the key for 'getting it right' closest to your thumb

## Changes to the Redox layout ![#99e6fc](https://placehold.it/15/99e6fc/000000?text=+)

These are physical keycap changes on the board that make reaching the `Layer 1` keys easier and that, subjectively, look more balanced visually:

- Increase the `Layer 1` key sizes from 1U to 1.25U
- Decrease the 1.5 U key size for `[` and `]` to 1.25U

You could even make `[` and `]` 1U so that you can use keycaps from a standard ANSI key set and also increase the size of the `Layer 2` keys to 1.5U. 
