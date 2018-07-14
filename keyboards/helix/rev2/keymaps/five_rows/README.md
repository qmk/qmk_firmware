# Keymap for 5 rows Helix keyboard

This keymap is only for 5 rows Helix keyboard.

## Layout

![fig1](https://gist.github.com/mtei/c81a3688206aa50996339cb9ced4751d/raw/827632dda7db87cf88d41a0d3b476c5962c29213/helix-five_rows_r3.png)

## Layer

|Priority|Number|Name|Discription|
| ---- | ---- | --- | --- |
|high|9|Adjust| keyboard local functions (violet)|
||8|KFunction| TenkeyPad function keys (bule)|
||7|Extra char| some charactors (red)|
||6|Function| function keys (blue)|
||2|Keypad|TenkeyPad|
||2|Dvorak|Dvorak|
||1|Colemak|Colemak|
|low|0|Qwerty|QWERTY (base)|

### Adjust Layer

Adjust Layer has keyboard local function keys.

* LED control.
* Mac/Win mode change.
* Qwerty/Colemak/Dvorak/TenkeyPad change.

![fig2](https://gist.github.com/mtei/c81a3688206aa50996339cb9ced4751d/raw/827632dda7db87cf88d41a0d3b476c5962c29213/helix-five_rows_r3adj.png)

### Mac mode and Win mode

Mac mode swap Alt/Win(GUI) key.

|mode|key|code|
| ---- | ---- | --- |
|Mac mode|Adjust + g(Qwerty)|AG_NORM|
|        |Adjust + h(Qwerty)|       |
|Win mode|Adjust + t(Qwerty)|AG_SWAP|
|        |Adjust + y(Qwerty)|       |

### LED control

|command|key|code|
| ---- | ---- | --- |
|on/off|Adjust + e(Qwerty)|RGB_TOG|
|      |Adjust + i(Qwerty)|       |
|change mode|Adjust + d(Qwerty) |RGB_SMOD|
|           |Adjust + k(Qwerty)|       |
|HUE +|Adjust + Left Control|RGB_HUI|
|     |Adjust + Right Control|       |
|HUE -|Adjust + Left Shift  |RGB_HUD|
|     |Adjust + Right Shift  |       |
|SAT +|Adjust + ;(Qwerty)   |RGB_SAI|
|     |Adjust + a(Qwerty)   |       |
|SAT -|Adjust + z(Qwerty)  |RGB_SAD|
|     |Adjust + /(Qwerty)  |       |
|Bright +|Adjust + s(Qwerty)  |RGB_VAI|
|     |Adjust + l(Qwerty)  |       |
|Bright -|Adjust + x(Qwerty)  |RGB_VAD|
|     |Adjust + >(Qwerty)  |       |
|reset|Adjust + w|RGBRST|

### Qwerty, Colemak, Dvorak, TenkeyPad selection

|char layout|key|
| ---- | ---- |
|Qwerty | Adjust + 5 |
|       | Adjust + 6 |
|Calemak| Adjust + 4 |
|       | Adjust + 7 |
|Dvorak | Adjust + 3 |
|       | Adjust + 8 |
|Keypad | Adjust + 2 |
|       | Adjust + 9 |

## TenkeyPad layout

![fig3](https://gist.github.com/mtei/c81a3688206aa50996339cb9ced4751d/raw/827632dda7db87cf88d41a0d3b476c5962c29213/helix-five_rows_r3key.png)

## Note

![fig4](https://gist.github.com/mtei/c81a3688206aa50996339cb9ced4751d/raw/d6e9af7684c051de4744b9dee9cd96b762bf4e2d/five_rows_making2.jpg)
