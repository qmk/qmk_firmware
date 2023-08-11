# Kprepublic BM40HSRGB Coffee

A layout that aims to be familiar to people that have used larger boards

## The layout

The primary layer ( `_MAIN` ) is as close to standard qwerty as I could get.
| row | 1    | 2    | 3 | 4   | 5   | 6   | 7   | 8   | 9   | 10  | 11 | 12   |
|-----|------|------|---|-----|-----|-----|-----|-----|-----|-----|----|------|
| 1   | esc  |  q   | w |  e  |  r  |  t  | y   | u   | i   | o   | p  | bksp |
| 2   | tab  |  a   | s |  d  |  f  |  g  | h   | j   | k   | l   | ;  | '    |
| 3   | shft |  z   | x |  c  |  v  |  b  | n   | m   | ,   | .   | /  | rtrn |
| 4   | ctrl | win  |   | alt | SUB | spc | <- | CTR | lft | dwn | up | rght |

The secondary layer ( `_SUB` ) is for syntax, F keys, and number keys
| row | 1   | 2  | 3  | 4  | 5   | 6   | 7   | 8  | 9    | 10  | 11 | 12   |
|-----|-----|----|----|----|-----|-----|-----|----|------|-----|----|------|
| 1   | grv | 1  | 2  | 3  | 4   | 5   | 6   | 7  | 8    | 9   | 0  | del  |
| 2   |     | F1 | F2 | F3 | F4  | F5  | F6  | -  | =    | [   | ]  | pgup |
| 3   | _   | F7 | F8 | F9 | F10 | F11 | F12 |    | home | end | \  | pgdn |
| 4   | _   | _  |    | _  | _   | _   | <-  | _  |      |     |    |      |

The control layer ( `_CTR` ) is for lighting, media, and macros
| row | 1 | 2     | 3    |  4      |  5      | 6       | 7   | 8    | 9    | 10   | 11 | 12      |
|-----|---|-------|------|---------|---------|---------|-----|------|------|------|----|---------|
| 1   |   | SPD-  | BRI+ |  SPD+   |  HUE+   | SAT+    |     |      | VOL+ |      |    | MCR_REC |
| 2   |   | EFCT- | BRI- |  EFCT+  |  HUE-   | SAT-    |     | PREV | PLAY | NEXT |    | MCR_PLY |
| 3   |   |       | TOG  |         |         |         |     |      | VOL- |      |    | MCR_SWT |
| 4   |   |       |      | TRBO_TI | TRBO_ST | MSE_TOG | <-  |      |      |      |    |         |

The mouse layer ( `_MSE` ) is for making the keyboard function as a mouse as well
| row | 1 | 2    | 3    | 4    | 5     | 6       | 7   | 8     | 9     | 10    | 11    | 12 |
|-----|---|------|------|------|-------|---------|-----|-------|-------|-------|-------|----|
| 1   |   |      |      |      |       |         |     |       |       |       |       |    |
| 2   |   | MS_L | MS_D | MS_U | MS_R  |         |     | L_CLC | SCR_D | SCR_U | R_CLC |    |
| 3   |   |      |      |      |       |         |     |       |       |       |       |    |
| 4   |   |      |      |      | ACL_D | MSE_TOG | <-  | ACL_U |       |       |       |    |

| Key name | Explanation                                  |
|----------|----------------------------------------------|
| \_       | Passthrough the key on the layer below       |
| <-       | Same key as imediate left. Used for spacebar |
| SUB      | Goes to _SUB layer while held down           |
| CTR      | Goes to _CTR layer while held down           |
| MSE_TOG  | Toggles the mouse layer on or off            |
| SPD +/-  | Changes speed for the RGB effect             |
| BRI +/-  | Changes the brightness of the lighting       |
| EFCT +/- | Moves to the next/previous effect            |
| TOG      | Toggles the lighting on or off               |
| HUE +/-  | Changes the hue for RGB effects              |
| SAT +/-  | Changes the saturation for RGB effects       |
| MSE      | Toggles the Mouse layer                      |
| VOL +/-  | Raises or lowers media volume                |
| PREV     | Goes to previous media                       |
| PLAY     | Play/Pause media                             |
| NEXT     | Goes to next media                           |
| MCR_REC  | Record macro ( Press again to stop )         |
| MCR_PLY  | Play recorded macro                          |
| MCR_SWT  | Switch active macro                          |
| MS_L     | Move mouse cursor left                       |
| MS_U     | Move mouse cursor up                         |
| MS_D     | Move mouse cursor down                       |
| MD_R     | Move mouse cursor right                      |
| L_CLC    | Mouse left click                             |
| R_CLC    | Mouse right click                            |
| SCR_U    | Mouse scroll up                              |
| SCR_D    | Mouse scroll down                            |
| ACL_U    | Raise mouse/scroll speed                     |
| ACL_D    | Lower mouse/scroll speed                     |
| TRBO_ST  | Set turbo key (Hold), start/stop turbo (Tap) |
| TRBO_TI  | Turbo speed +/- (Hold to switch direction)   |

## Compiling

Compiling: `make kprepublic/bm40hsrgb:coffee`

Flashing: `make kprepublic/bm40hsrgb:coffee:flash`
