# IDOBAO ID80

This is my layout for the IDOBAO ID80. It depends of my [user files](../../../../users/rverst)
and the main goal is to give an convenient and unified access to some special keys
(umlauts, ß, €) for different operating systems (Mac, Windows and Linux).

## Overview

- Layer 0 is the base US-ANSI layout with Mac-style system keys and a OSL-Key for Layer 1 right of the space bar.
- Layer 1 has the special keys and some media-functions like mute, volume up/down etc.
- Layer 2 and 3 are basically the same as Layer 0 and 1 but in Colemak-Layout
- Layer 4 and 5 has some functions like switching the keyboard mode, switching the default layer etc.


## Keyboard modes

- *F1:* Mac Unicode mode (use 'Unicode Hex Input' as input source)
- *F2:* Windows Unicode mode (use [WinCompse](https://github.com/SamHocevar/wincompose) software)
- *F3:* Linux Unicode mode (not tested yet but should work out of the box)
-  *1:* Mac legacy mode (uses option-sequences, e.g. `<option>+u a` for an `ä`), if I'm not able to set the input source
-  *2:* Windows legacy mode (uses altgr-sequences e.g. `<altgr>+0228` for an `ä`, if I'm not able to use WinCompose)

Layer 4 to switch the modes temporary, layer 5 to switch and save to eeprom.
