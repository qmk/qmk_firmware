# RS: Code Friendly 40% – 60% Keymaps

The rs keymap collection is an evolution of my previous keymap optimized for coding with a 60% keyboards like the Iris. I tried to keep the simplicity of my previous keymap with all the keys necessary for coding on a single layer in addition to the base one. It work well with any 40% and 60% keyboard, split or not.

To build it, use:

    make <keyboard>:rs

Example:

    make keebio/iris:rs
    make crkbd:rs
    make planck:rs
    make preonic:rs
    make ergotravel:rs
    make handwired/rs60:rs

Because I sometime have to use my internal keyboard I my macbook, a [karabiner configuration](karabiner.json) is also provided to get most of the features of this keyboard, including the code layer / backspace on right command key etc.

This set of keymaps have been tested with those keyboards:
- [Planck](../../keyboards/planck/)
- [Preonic](../../keyboards/preonic/)
- [My preonic clone](../../keyboards/handwired/rs60/)

This keymap in is also available for other keyboards:
- [Crkdb/rs](../../keyboards/crkbd/keymaps/rs/keymap.c)
- [Iris/rs](../../keyboards/keebio/iris/keymaps/rs/keymap.c)
- [Ergotravel/rs](../../keyboards/ergotravel/keymaps/rs/keymap.c)
- [ortho_5x12/rs](../../layouts/community/ortho_5x12/rs/keymap.c)
- [ortho_4x12/rs](../../layouts/community/ortho_4x12/rs/keymap.c)
