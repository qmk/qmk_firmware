## Billiam's DZ60 layout

### Initial Installation

These are the steps if you've never done this before:

1. Build your hex file
```
make dz60:billiams # be in the qmk_firmware directory to do this
```
A hex file `dz60_billiams.hex` will be created in the base qmk_firmware directory

2. Before plugging in your keyboard into your computer, hold SPACE and B keys down
3. Plug the computer in, which will put the keyboard in bootlegger mode
4. If you are using [QMK toolbox](https://github.com/qmk/qmk_toolbox/releases), upload the .hex file you made above, select it and hit the flash button. Don't hit the load button, that will load the default keymap and that's not what you want! Unless it is, in which case click away.


### Notes

This layout is for a Build 4 DZ60 with a 2U left shift, 2U right shift and an arrow
cluster in the bottom right.

Settings:

* The capslock key is replaced with a second function key.
* The Alt an Cmd keys are swapped to replicate the Mac layout.
* Del is available as Fn+Backspace
* / ? are available when you tap the right shift. Otherwise RShift is shift when held down
* RESET is available as Fn+Esc
* Underglow toggle and mode selection are available as Fn+A and Fn+S

### 0 Qwerty
```
,-----------------------------------------------------------------------------------------.
|  `  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |   Bkspc   |
|-----------------------------------------------------------------------------------------+
| Tab    |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |    \   |
|-----------------------------------------------------------------------------------------+
|   Fn    |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |    Enter    |
|-----------------------------------------------------------------------------------------+
| Shift     |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  | Tap:/ RSh |  U  | ESC |
|-----------------------------------------------------------------------------------------+
| Ctrl |  Alt  |  Cmd  |              Space                | Cmd |  Fn  |  L  |  D  |  R  |
`-----------------------------------------------------------------------------------------'
```

### 1 Fn Layer
```
FN Layer
,-----------------------------------------------------------------------------------------.
|  `  |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  F7 |  F8 |  F9 | F10 | F11 | F12 |    DEL    |
|-----------------------------------------------------------------------------------------+
|        |RBB T|RGB M| Hue+| Hue-| Sat+| Sat-| Val+| Val-|     |     |      | Prev | Next |
|-----------------------------------------------------------------------------------------+
|         | BL T| BL M| BL+ | BL- |     |     |     |     |     | Vol-| Vol+|  Play/Pause |
|-----------------------------------------------------------------------------------------+
|           |     |     |     |     |     |     |     |Scr- |Scr+ |         | PG_UP |RESET|
|-----------------------------------------------------------------------------------------+
|      |       |       |                                 |     |     | HOME | PG_DN | END |
`-----------------------------------------------------------------------------------------'
```

