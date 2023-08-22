![merrittlj keymap image](https://i.imgur.com/5H9icXOh.png)

# "merrittlj" keymap

This is the my specialized Dvorak-based keymap. While a review of the "keymap.c" file is necessary to properly understand this keymap, a brief summary will follow:

To start, this is based off of the Dvorak layout. If you want to change it to a differing layout, simply change all the letters on the "base" layer. The base keymap contains the standard Dvorak layout letter-wise, with numbers borrowed from Programmer Dvorak(without the shift necessary) on the top-most row. The left and right-most columns on the keyboard are arrow/page keys, and dynamic macro keys, respectively.

Space, backspace, the symbol layer key, and shift can all be found on the direct thumb keys. Neighboring these keys are tab, enter, the functional layer key, and the additonal layer key.

All symbols are seperated into their own layer, accessed via the symbol layer key found on the top-most right direct thumb key. As the standard Dvorak layout contains symbols in the top-left three letters(that would be found on other boards), these have been replaced by the super, control, and meta keys respectively. Symbols on the symbol layer are based on my own personal preference by usage and placement, so feel free to modify as needed.

The functional layer is where you can find home, end, functional number keys, etc. The additonal layer has miscellaneous keys or specific-to-QMK keys.

This summary is not a substitute for the actual file if you plan on using this keymap. The keymap isn't based much on evidence, more personal preference: so feel free to modify as wanted.