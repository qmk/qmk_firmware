## Billiam's Space65 layout (with split backspace)

This layout is optimized for vim users on MacOS with a split backspace.

Settings:

* The `CAPS LOCK` key is a function key.
* The `ALT` and `CMD` keys are swapped to replicate the Mac layout.
* RESET is available as `Fn`+ `Right Ctrl` + `ESC`
* Underglow toggle is available as `Fn` + `Q`.
* vim-style arrow key bindings H J K L in layer 1

### Initial Installation

I found the instructions to be longer than they had to be, and I ended up having to Google some steps anyway. These are the steps I took to get my keyboard setup, in case you are new to the process.

1. Fork and Clone the qmk_firmware repo locally
```
# Choose one:
git clone git@github.com:qmk/qmk_firmware.git # OR
git clone https://github.com/qmk/qmk_firmware.git
```
2. Customize your layout by starting with a [keymap](https://github.com/qmk/qmk_firmware/tree/master/keyboards/gray_studio/space65/keymaps). I copied  the default and changed it to my liking.
3. Before plugging in your keyboard into your computer, hold `ESC` key down
4. Plug the keyboard into your computer, which will put the keyboard in bootloader mode.
5. Build your hex file and flash your keyboard
```
make gray_studio/space65:billiams:flash # be in the qmk_firmware directory to do this
```

Notes:
- If you are using QMK Toolbox, use `make gray_studio/space65:<keymap>` in the base qmk_firmware directory instead of step 5 above which will create a hex file `gray_studio_space65_billiams.hex` which you can then choose in the toolbox and hit flash
- If you accidentally loaded the default keymap, then to `RESET` the keyboard and kick it into bootloader mode again, hold the `ESC` key and plug the board in.

Hope this helps!

### 0 Qwerty
```
,------------------------------------------------------------------------------------------------.
|  `  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  | \ | Del   |  INS |
|------------------------------------------------------------------------------------------------+
| Tab    |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  | Bkspc  | PGUP |
|------------------------------------------------------------------------------------------------+
|   Fn1   |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |    Enter    | PGDN |
|------------------------------------------------------------------------------------------------+
| Shift     |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  | ?/ |    Shift   | up  |  ESC |
|------------------------------------------------------------------------------------------------+
| Ctrl |  Alt  |  Cmd  |              Space               |  Alt |  Ctrl |  Left  | Down | Right |
`------------------------------------------------------------------------------------------------'
```

### 1 Fn Layer
```
,------------------------------------------------------------------------------------------------.
|     |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  F7 |  F8 |  F9 | F10 | F11 | F12 |Vol- |Vol+ | Next |
|------------------------------------------------------------------------------------------------+
|        |RGB T|RGB M| Hue-| Hue+| Sat-| Sat+| Val-| Val+| Spd- | Spd+ |    |      |      | Prev |
|------------------------------------------------------------------------------------------------+
|         | RGBP | RGBG | RGBK |    |     | Left| Down| Up |Right|     |     | Play/Pause |      |
|------------------------------------------------------------------------------------------------+
|           |     |     |     |     |     |     |     |    | Scr- | Scr+ |    |     |PGUP |      |
|------------------------------------------------------------------------------------------------+
|      |       |       |                                  |      |  Fn2  |  HOME  | PGDN  |  END |
`------------------------------------------------------------------------------------------------'
```

### 2 Fn Layer - Just for bootloader mode button
```
,------------------------------------------------------------------------------------------------.
|     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |      |
|------------------------------------------------------------------------------------------------+
|        |     |     |     |     |     |     |     |     |      |     |     |      |      |      |
|------------------------------------------------------------------------------------------------+
|         |     |     |     |     |     |     |     |    |    |      |      |            |       |
|------------------------------------------------------------------------------------------------+
|           |     |     |     |     |     |     |     |     |     |     |     |     |    | RESET |
|------------------------------------------------------------------------------------------------+
|      |       |       |                                   |      |       |       |       |      |
`------------------------------------------------------------------------------------------------'
```
