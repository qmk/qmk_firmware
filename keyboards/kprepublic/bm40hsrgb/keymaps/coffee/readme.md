# Kprepublic BM40HSRGB Coffee

A layout that aims to be familiar to people that have used larger boards

## The layout

The primary layer ( `_MAIN` ) is as close to standard qwerty as I could get.
```
esc  |  q   |  w   |   e   |  r   |  t   | y   | u    | i    | o    | p  | bksp
tab  |  a   |  s   |   d   |  f   |  g   | h   | j    | k    | l    | ;  | '
shft |  z   |  x   |   c   |  v   |  b   | n   | m    | ,    | .    | /  | rtrn
ctrl | win  |      |  alt  | SUB  |     spc    | CTR  | lft  | dwn  | up | rght
```

The secondary layer ( `_SUB` ) is for syntax, F keys, and number keys
```
grv |   1   |  2   |  3    | 4    | 5    | 6   | 7    | 8    | 9    | 0  | del
    |   F1  |  F2  |  F3   | F4   | F5   | F6  | -    | =    | [    | ]  | pgup
 _  |   F7  |  F8  |  F9   | F10  | F11  | F12 |      | home | end  | \  | pgdn
 _  |   _   |      |  _    | _    |      _     | _    |      |      |    |
```

The control layer ( `_CTR` ) is for lighting, media, and macros
```
    | SPD-  | BRI+ | SPD+  | HUE+ | SAT+ |     |      | VOL+ |      |    | MCR_REC
    | EFCT- | BRI- | EFCT+ | HUE- | SAT- |     | PREV | PLAY | NEXT |    | MCR_PLY
    |       | TOG  |       |      |      |     |      | VOL- |      |    | MCR_SWT
    |       |      |       |      |      _     |      |      |      |    |
```

| Key name | Explanation                            |
| -------- | -------------------------------------- |
| \_       | Passthrough the key on the layer below |
| SUB      | Goes to _SUB layer while held down     |
| CTR      | Goes to _CTR layer while held down     |
| SPD +/-  | Changes speed for the RGB effect       |
| BRI +/-  | Changes the brightness of the lighting |
| EFCT +/- | Moves to the next/previous effect      |
| TOG      | Toggles the lighting on or off         |
| HUE +/-  | Changes the hue for RGB effects        |
| SAT +/-  | Changes the saturation for RGB effects |
| MSE      | Toggles the Mouse layer                |
| VOL +/-  | Raises or lowers media volume          |
| PREV     | Goes to previous media                 |
| PLAY     | Play/Pause media                       |
| NEXT     | Goes to next media                     |
| MCR_REC  | Record macro ( Press again to stop )   |
| MCR_PLY  | Play recorded macro                    |
| MCR_SWT  | Switch active macro                    |

## Compiling

Compiling: `make kprepublic/bm40hsrgb:coffee`

Flashing: `make kprepublic/bm40hsrgb:coffee:flash`
