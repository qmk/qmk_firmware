# The default keymap for quick17

## CONTROL(default) Layer
```
    ,-----------------------------------------------.
    | Tab   | PgUp  |  Up   | PgDn  | Home  |  Ins  |
    |-------+-------+-------+-------+-------+-------|
    | Ctrl  | Left  | Down  | Right | End   |  Del  |
    |-------+-------+-------+-------+-------+-------|
    | Shift | GUI   |  Esc  |  Alt  | FN/Spc| EDIT1 |
    `-----------------------------------------------'
```

## EDIT1 Layer
```
    ,--------------------------------------------------.
    | Esc   |   W   |   E   |   R   |    Y    | Bspc   |
    |-------+-------+-------+-------+---------+--------|
    | Ctrl  |   A   |   D   |   F   |    H    | Ctrl+Z |
    |-------+-------+-------+-------+---------+--------|
    | Shift |   X   |   V   |   B   |EDIT2/Spc| Ctrl+S |
    `--------------------------------------------------'
```

## EDIT2 Layer
```
    ,-------------------------------------------------.
    | Esc   |   Q   | BTN3  |  Ins  | Enter  | Bspc   |
    |-------+-------+-------+-------+--------+--------|
    | Ctrl  |   [   |   ]   | PgDn  | PgUp   | Ctrl+Z |
    |-------+-------+-------+-------+--------+--------|
    | Shift |   FN  |RGB_TOG|CONTROL| (NONE) | (NONE) |
    `-------------------------------------------------'
```

## FN Layer
```
    ,---------------------------------------------------.
    | Esc   | LANG  | (NONE) |RGB_TOG| Media > | Vol+   |
    |-------+-------+--------+-------+---------+--------|
    | Caps  | Numlk | (NONE) |RGB_MOD| Media < | Vol-   |
    |-------+-------+--------+-------+---------+--------|
    | Win   | mac   | EEP_RST| RESET | CONTROL | Mute   |
    `---------------------------------------------------'
```
### difference between mac-Mode and Win-Mode
- In mac Mode, `Ctrl` key will be changed into `command` key.
- `LANG` key will change its behaviour.

### "LANG" key behaviour

|LED-sign|Blue|Red|Green|
|---|---|---|---|
|mac Mode|-|かな|英数|
|Win Mode|半角/全角(Alt+`)|-|-|

## Rotary encoder behaviour

|On layer...|Clockwise|C-Clockwise|
|---|---|---|
|CONTROL|Scroll Up|Scroll Down|
|EDIT1|Vol+|Vol-|
|EDIT2|[|]|
|FN|Media >|Media <|
