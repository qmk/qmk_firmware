# Michael Guterl's Ortho 4x12 Layout

I use this layout for both my Planck and Levinson. I also have a very similar
[keymap](/keyboards/preonic/keymaps/mguterl) for my Preonic.

Check out my [userspace](/users/mguterl) for the custom keycodes that are used
in keymap.c.

At a very high level I use 4 layers:

* Qwerty - Letters
* Util   - Vimkeys for navigation and other convenient things
* Raise  - Numbers and F keys
* Lower  - Symbols

```sh
make planck/rev5:mguterl:flash        # For Planck rev5 or earlier and Planck Light
make planck/rev6:mguterl:flash        # For Planck rev6
make keebio/levinson/rev2:mguterl:dfu # For Levinson rev2
```
