# Keymap for 5 rows Helix keyboard

This keymap is only for 5 rows Helix keyboard.

## Layout

![fig1](https://gist.github.com/mtei/c81a3688206aa50996339cb9ced4751d/raw/662082b66231eb8d1f45776d813c57f29d445e68/helix-five_rows_r2.png)

## Layer

|Priority|Number|Name|Discription|
| ---- | ---- | --- | --- |
|high|16|Adjust| keyboard local functions|
||4|Extra char| some charactors |
||3|Function| function keys |
||2|Dvorak|Dvorak|
||1|Colemak|Colemak|
|low|0|Qwerty|QWERTY (base)|

### Adjust Layer

Adjust Layer has keyboard local function keys.

* LED control.
* Mac/Win mode change.
* Qwerty/Colemak/Dvorak change.

### Mac mode and Win mode

Mac mode swap Alt/Win(GUI) key.

|mode|key|code|
| ---- | ---- | --- |
|Mac mode|Adjust + g(Qwerty)|AG_NORM|
|Win mode|Adjust + h(Qwerty)|AG_SWAP|
|        |Adjust + t(Qwerty)|       |

### LED control

|command|key|code|
| ---- | ---- | --- |
|on/off|Adjust + ,(Qwerty)|RGB_TOG|
|      |Adjust + v(Qwerty)|       |
|change mode|Adjust + Right option |RGB_SMOD|
|           |Adjust + c(Qwerty)|       |
|HUE +|Adjust + .(Qwerty)   |RGB_HUI|
|     |Adjust + Left Control|       |
|HUE -|Adjust + menu        |RGB_HUD|
|     |Adjust + Left Shift  |       |
|SAT +|Adjust + /(Qwerty)   |RGB_SAI|
|     |Adjust + a(Qwerty)   |       |
|SAT -|Adjust + right hand left side Fn|RGB_SAD|
|     |Adjust + z(Qwerty)              |       |
|Bright +|Adjust + Right Shift    |RGB_VAI|
|        |Adjust + s(Qwerty)|       |
|Bright -|Adjust + right hand right side Fn|RGB_VAD|
|        |Adjust + x(Qwerty)               |       |
|reset|Adjust + w(Qwerty)|RGBRST|

### Qwerty, Colemak, Dvorak selection

|char layout|key|
| ---- | ---- |
|Qwerty | Adjust + j(Qwerty) |
|       | Adjust + 5|
|Calemak| Adjust + k(Qwerty) |
|       | Adjust + 4|
|Dvorak | Adjust + l(Qwerty) |
|       | Adjust + 3|

## Note

![fig2](https://gist.github.com/mtei/c81a3688206aa50996339cb9ced4751d/raw/9979482e9aa0b25962fad9ee634cd1c23cef1751/five_rows_making.jpg)
