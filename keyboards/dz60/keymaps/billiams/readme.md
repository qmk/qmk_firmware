## Billiam's DZ60 layout

This layout is optimized for MacOS and is for a Build 4 DZ60 with a 2U left shift, 2U right shift and an arrow
cluster in the bottom right. Don't use this layout if you didn't get Build 4, you will enter a world of pain Donny.

Settings:

* The `CAPS LOCK` key is replaced with a second function key.
* The `ALT` and `CMD` keys are swapped to replicate the Mac layout.
* Del is available as `Fn` + `Backspace`
* `/ ?` are available when you tap the right shift. Otherwise RShift is shift when held down
* RESET is available as `Fn`+ ` ESC`
* Underglow toggle is available as `Fn` + `Q`. Yes your keyboard has lights even if you didn't get the LEDs. Bonus!
* vim-style arrow key bindings H J K L in layer 1
* The `Bkspc` and `\` keys have been swapped, the reach was too great to have backspace on the top row

### Initial Installation

I found the instructions to be longer than they had to be, and I ended up having to Google some steps anyway. These are the steps I took to get my keyboard setup, in case you are new to the process.

1. Clone the qmk_firmware repo locally
```
# Choose one:
git clone git@github.com:qmk/qmk_firmware.git # OR
git clone https://github.com/qmk/qmk_firmware.git
```
2. Customize your layout by starting with a [keymap](https://github.com/qmk/qmk_firmware/tree/master/keyboards/dz60/keymaps). I copied [StephenGrier](https://github.com/qmk/qmk_firmware/tree/master/keyboards/dz60/keymaps/stephengrier)'s and modified it for DZ60 Build 4 and changed a few things, like the `grave` key, `ESC` and `/`.

3. Build your hex file
```
make dz60:billiams # be in the qmk_firmware directory to do this
```
A hex file `dz60_billiams.hex` will be created in the base qmk_firmware directory

4. Before plugging in your keyboard into your computer, hold `SPACE` and `B` keys down
5. Holding those keys down, plug the keyboard into your computer, which will put the keyboard in bootlegger mode
6. If you are using [QMK toolbox](https://github.com/qmk/qmk_toolbox/releases), upload the .hex file you made above, select it and hit the flash button. For the love of all that is good and holy on Earth, don't hit the load button, that will load the default keymap and that's not what you want! Unless it is, in which case click away.

Note: If you didn't follow my instructions in 4 and accidentally loaded the default keymap, then to `RESET` the keyboard and kick it into bootleg mode again, hold the `down arrow` key and `\`. The default layout is Build 1 and sets the `MENU` key on that build to `Fn`. `MENU` corresponds to `down arrow` in build 4. Note that you don't have to unplug the keyboard.

Hope this helps!

### 0 Qwerty
```
,-----------------------------------------------------------------------------------------.
|  `  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |     \     |
|-----------------------------------------------------------------------------------------+
| Tab    |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  | Bkspc  |
|-----------------------------------------------------------------------------------------+
|   Fn    |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |    Enter    |
|-----------------------------------------------------------------------------------------+
| Shift     |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  | Tap:/ RSh |  U  | ESC |
|-----------------------------------------------------------------------------------------+
| Ctrl |  Alt  |  Cmd  |              Space                | Alt |  Fn  |  L  |  D  |  R  |
`-----------------------------------------------------------------------------------------'
```

### 1 Fn Layer
```
FN Layer
,-----------------------------------------------------------------------------------------.
|  `  |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  F7 |  F8 |  F9 | F10 | F11 | F12 |    DEL    |
|-----------------------------------------------------------------------------------------+
|        |RBB T|RGB M| Hue-| Hue+| Sat-| Sat+| Val-| Val+| Mute | Vol-| Vol+| Prev | Next |
|-----------------------------------------------------------------------------------------+
|         |     |     |     |     |     | Left| Down| Up |Right|      |      | Play/Pause |
|-----------------------------------------------------------------------------------------+
|           |     |     |     |     |     |     |     |Scr- |Scr+ |         | PG_UP |RESET|
|-----------------------------------------------------------------------------------------+
|      |       |       |                                 |     |     | HOME | PG_DN | END |
`-----------------------------------------------------------------------------------------'
```
