# Scotto

Applies to layouts:
- LAYOUT_ortho_4x10
- LAYOUT_split_3x5_2
- LAYOUT_split_3x5_3

### QWERTY

Scotto's default functional layout is Colemak. To compile this layout in QWERTY (US English), append compile command with `KEYMAP=QWERTY` environment variable.
```
qmk compile -kb <keyboardName> -km scotto -e KEYMAP=QWERTY
```
Example for [Ferris Sweep](/keyboards/ferris/sweep/):
```
qmk compile -kb ferris/sweep -km scotto -e KEYMAP=QWERTY
```
