Yida's keymap for BananaSplit
===

Hightlight: split backspace, ISO Enter, split space, arrows on bottom right, and toggable capslock backlight.

Note that "Previous track" and "next track" might only work with Windows.

Default layer:
```
  -------------------------------------------------------------
  |Esc| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | = | ` |Del|
  -------------------------------------------------------------
  | Tab | Q | W | E | R | T | Y | U | I | O | P | [ | ] | Ent |
  --------------------------------------------------------    -
  | Caps | A | S | D | F | G | H | J | K | L | ; | ' | \ |    |
  -------------------------------------------------------------
  | Shift  | Z | X | C | V | B | N | M | , | . | Shift| Up| / |
  -------------------------------------------------------------
  |Ctrl| GUI| Alt|  Space   |MoL1| Backspc| Hm|End| <-|Dwn| ->|
  -------------------------------------------------------------
  Hm: Home
  MoL1: Mo(L1)
```

Layer_1:
```
  -------------------------------------------------------------
  |   | F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|   |Ins|
  -------------------------------------------------------------
  |     |   |   | @ |   |   |   |   |   |   |   |   |   |     |
  --------------------------------------------------------    -
  |      |   |   |   |   |   |   |   |   |   |   |   |   |    |
  -------------------------------------------------------------
  |        |   |   |Cal|   |www|   |Mut|   |   |      |VUp|   |
  -------------------------------------------------------------
  |    |    |    |  Pause   |    |        |PUp|PDn|PTk|VDn|NTk|
  -------------------------------------------------------------
  @: Email
  Cal: Calculator
  Ins: Insert
  Mut: Mute
  NTk: Next track
  PDn: Page down
  PTk: Previous track
  PUp: Page up
  VDn: Volume down
  VUp: Volume up
  www: Browser home page
```

Compile and flash:

`cd` to `/qmk_firmware` folder, then
```
make bananasplit:jockyxu1122_iso
```

A .hex file will be generated under `/qmk_firmware` folder.


To flash, use QMK Toolbox.
