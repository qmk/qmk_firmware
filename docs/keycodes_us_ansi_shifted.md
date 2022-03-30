# US ANSI Shifted Symbols

These keycodes correspond to characters that are "shifted" on a standard US ANSI keyboard. They do not have keycodes of their own but are simply shortcuts for `LSFT(kc)`, and as such send a Left Shift with the unshifted keycode, not the symbol itself.

## Caveats

Unfortunately, these keycodes cannot be used in Mod-Taps or Layer-Taps, since any modifiers specified in the keycode are ignored.

Additionally, you may run into issues when using Remote Desktop Connection on Windows. Because these codes send shift very fast, Remote Desktop may miss the codes.

To fix this, open Remote Desktop Connection, click on "Show Options", open the "Local Resources" tab. In the keyboard section, change the drop down to "On this Computer". This will fix the issue, and allow the characters to work correctly.

## Keycodes

[keycodes/keycodes_us_ansi_shifted_symbols.md](keycodes/keycodes_us_ansi_shifted_symbols.md ':include')