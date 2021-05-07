# Vim-mode Keymap

This layout is designed with the vim philosophy in mind: You should be able to do your work without lifting your hands off the keyboard. Some movement keys (like the arrow keys) have been directly borrowed from vim, and other keys (like the numpad) have been placed in easy-to-reach areas, following the vim philosophy.

Based on the default keymap.

## Features:

* Vim-like `hjkl` arrow keys in raise layer.
* Right-hand numpad in lower layer.
* All brackets and the most frequently used operators are intuitively handled in the lower layer for easy access.
* Ctrl is just to the left of the left-hand pinky.
* The raise layer provides the symbol bar on the first row that you're used to.
* Media keys available in adjust layer (complete) and in the bottom-right corner of the default layer (frequently used).
* The two keys that are traditionally the keys for `space` behave differently. The right-hand key inserts a space. The left-hand key inserts a tab. This is intuitive: Both keys that would normally make up the spacebar are increasing the space, but in different manners.


## Some things to look out for:

* Page up, page down, home, and end have been placed directly under the `hjkl` arrow keys, and each key moves the same direction as the key above it. (for instance, `h` moves left. Home has therefore been placed on `n`). You may ask why this was done instead of placing page down on `f` and page up on `b`. Here's why:
  * In short, `f` and `b` are in prime locations for other types of keys, and using those keys for page down and page up would interrupt the space available for other keys. Using vim-style `f` and `b` would require either divide up the list of function keys with unrelated keys, which is unintuitive, or move all the function keys to another later, requiring restructuring that does not lend itself to an intuitive layout.
* Audio is not tested. If it doesn't work, please open an issue.
