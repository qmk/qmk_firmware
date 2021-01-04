# Mattir's keymap & configs for [Kyria](https://github.com/splitkb/kyria)

## Keymap

This is my customized keymap and layer setup for my kyria. It's based largely on the defaults, but with several things moved to new layers.

Keys in the diagrams below that are blank are "transparent" and they drop down to the lowest layer that has them defined. The keys at the end of the bottom row marked as `ENC` are where my rotary encoders are installed. The 2U height `Spce/Shft` keys are multi-function. You tap them for a space, or hold them for shift.

### Base layer `QWERTY`

```
,-------------------------------------------.                              ,-------------------------------------------.
| Tab    |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  | \   |
|--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
| Esc    |   A  |   S  |  D   |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |  Enter |
|--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
| Leader |   Z  |   X  |   C  |   V  |   B  | ~ `  |      |  |      | - _  |   N  |   M  | ,  < | . >  | /  ? |  ' "   |
`----------------------+------+------+------+------| Spce |  | Spce |------+------+------+------+----------------------'
                       | ENC  | Ctrl | Supr | Rais | Shft |  | Shft | Lowr | Bksp  | Alt | ENC  |
                       `----------------------------------'  `----------------------------------'
```

### Symbols layer `LOWER`

```
,-------------------------------------------.                              ,-------------------------------------------.
|        |  !   |  @   |  #   |  {   |  }   |                              |      |      |      |      |      |        |
|--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
|        |  $   |  %   |  ^   |  (   |  )   |                              |   =  |  +   |  -   |  *   |  /   |        |
|--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
|  FUNCS |  &   |      |      |  [   |  ]   |      |      |  |      |      |      |      |  ,   |  .   |      |        |
`----------------------+------+------+------+------|      |  |      |------+------+------+------+----------------------'
                       | ENC  |      |      |      |      |  |      |      |      |      | ENC  |
                       `----------------------------------'  `----------------------------------'
```

### Numbers and mouse-keys layer `RAISE`

```
,-------------------------------------------.                              ,-------------------------------------------.
|        |   1  |  2   |  3   |  4   |  5   |                              |  6   |  7   |  8   |  9   |  0   |        |
|--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
|        |      | Prev | Play | Next |      |                              | Left | Down | Up   | Right|      |        |
|--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
|        |      | LMsB | MMsB | RMsB |      |      |      |  |      |      | MLeft| Mdown| MUp  |MRight|      |        |
`----------------------+------+------+------+------|      |  |      |------+------+------+------+----------------------'
                       | ENC  |      |      |      |      |  |      |      | Del  |      | ENC  |
                       `----------------------------------'  `----------------------------------'
```

### F-Keys and number-pad layer `FUNCS`

```
,-------------------------------------------.                              ,-------------------------------------------.
|        | F1   |  F2  | F3   | F4   | F5   |                              | np + | np 7 | np 8 | np 9 | np * |        |
|--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
|        | F6   |  F7  | F8   | F9   | F10  |                              | np - | np 4 | np 5 | np 6 | np / |        |
|--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
| FUNCS  | F11  |  F12 |      |      |      |      |      |  |      |      | np 0 | np 1 | np 2 | np 3 | np . |  =     |
`----------------------+------+------+------+------|      |  |      |------+------+------+------+----------------------'
                       | ENC  |      |      |      |      |  |      |      |      |      | ENC  |
                       `----------------------------------'  `----------------------------------'
```

### LED Underglow layer `RGBLED`

There's not much on this layer since several of the functions are set up for my rotary encoders.

```
,-------------------------------------------.                              ,-------------------------------------------.
|        |      |      |      |      |      |                              |      |      |      |      |      |        |
|--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
|        |      |ValUp |HueUp | SatUp| Mode |                              |      |      |      |      |      |        |
|--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
|        |      |ValDn |HueDn | SatDn| Rmode|      |      |  |      |      |      |      |      |      |      |        |
`----------------------+------+------+------+------|      |  |      |------+------+------+------+----------------------'
                       | ENC  |      |      |      |      |  |      |      |      |      | ENC  |
                       `----------------------------------'  `----------------------------------'
```

## Rotary Encoders

I've set up the 2 rotary encoders to serve different functions depending on the active layer. I'll call them `ENC-L` and `ENC-R` for the encoder on the left side, or on the right side. Note that many of these functions are Mac-specific in my case, and if you want to use them for Windows or Linux, you'll need to tweak the key-codes generated.

### Defaults

If a layer is undefined somehow, I have both encoders set to be ignored on rotation.

### Base layer `QWERTY`

`ENC-L`
* Rotate - Volume up and down, determined by rotation direction.
* Click - Mute audio.

`ENC-R`
* Rotate - Undo (command-Z) and Redo (shift-command-Z)
* Click - Toggle to `RGBLED` layer.

### Symbols layer `LOWER`

`ENC-L`
* Rotate - Desktop switching on Mac
* Click - no change (transparent)

`ENC-R`
* Rotate - App switching on Mac
* Click - no change (transparent)

### Numbers and mouse-keys layer `RAISE`

`ENC-L`
* Rotate - Mouse-wheel left and right (equal to side-swiping on Mac trackpads)
* Click - no change (transparent)

`ENC-R`
* Rotate - Mouse-wheel up and down
* Click - no change (transparent)

### F-Keys and number-pad layer `FUNCS`

`ENC-L`
* Rotate - nothing defined, falls back to defaults
* Click - no change (transparent)

`ENC-R`
* Rotate - nothing defined, falls back to defaults
* Click - no change (transparent)

### LED Underglow layer `RGBLED`

`ENC-L`
* Rotate - Adjust hue (color) forward and back
* Click - Turn on/off the underglow LEDs

`ENC-R`
* Rotate - Adjust the value (brightness) up and down
* Click - return to the base `QWERTY` layer

## OLEDs

There isn't much special here that isn't already in the default keymap for the Kyria. The main side (where the USB cable is plugged in) will show the QMK logo and the active layer. The secondary side (connected to the main via the TRRS cable) will show my personal logo.
