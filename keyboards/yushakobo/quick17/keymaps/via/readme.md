# The via keymap for quick17

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
    | Win   | mac   | EE_CLR | QK_BOOT | CONTROL | Mute   |
    `---------------------------------------------------'
```
### difference between mac-Mode and Win-Mode
- In mac Mode, `Ctrl` key will be changed into `command` key.
- `LANG` key will change its behaviour.

### "LANG" key behaviour

- mac Mode: cycle around "かな" and "英数"
- Win Mode: key combinations of Alt and `

## Rotary encoder behaviour

|On layer...|Clockwise|C-Clockwise|
|---|---|---|
|CONTROL|Scroll Up|Scroll Down|
|EDIT1|Vol+|Vol-|
|EDIT2|[|]|
|FN|Media >|Media <|
