# M Juma Planck Layout

## Layers

```ascii
Keymap: 32 Layers                   Layer: action code matrix
-----------------                   ---------------------
stack of layers                     array_of_action_code[row][column]
       ____________ precedence               _______________________
      /           / | high                  / ESC / F1  / F2  / F3   ....
  31 /___________// |                      /-----/-----/-----/-----
  30 /___________// |                     / TAB /  Q  /  W  /  E   ....
  29 /___________/  |                    /-----/-----/-----/-----
   :   _:_:_:_:_:__ |               :   /LCtrl/  A  /  S  /  D   ....
   :  / : : : : : / |               :  /  :     :     :     :
   2 /___________// |               2 `--------------------------
   1 /___________// |               1 `--------------------------
   0 /___________/  V low           0 `--------------------------
```

### Qwerty

```ascii
,-----------------------------------------------------------------------------------.
| Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
|------+------+------+------+------+-------------+------+------+------+------+------|
| GEsc |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
|------+------+------+------+------+------|------+------+------+------+------+------|
| Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
|------+------+------+------+------+------+------+------+------+------+------+------|
| Ctrl | FN   | GUI  | Alt  |Lower |  Space FN   |Raise | Left | Down |  Up  |Right |
`-----------------------------------------------------------------------------------'
```

#### Qwerty Layer Features

- [Grave Escape](https://docs.qmk.fm/#/feature_grave_esc)
- [Tap Dance](https://docs.qmk.fm/#/feature_tap_dance) Left Shift
    - Tap => Shift
    - Double Tap => Capslock
- [Mod-Tap](https://docs.qmk.fm/#/mod_tap) Enter
    - Tap => Enter
    - Hold => Right Shift
- [Layer Toggle](https://docs.qmk.fm/#/feature_layers) Space
    - Tap => Space
    - Hold => Activate ***Space Function*** Layer

### Raise

```ascii
,-----------------------------------------------------------------------------------.
|   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
|------+------+------+------+------+-------------+------+------+------+------+------|
|      |      |      |      |      |      |   *  |   4  |   5  |   6  |   -  |  \   |
|------+------+------+------+------+------|------+------+------+------+------+------|
|      |      |      |      |      |      |   /  |   1  |   2  |   3  |   +  |Enter |
|------+------+------+------+------+------+------+------+------+------+------+------|
|      |      |      |      |      |    Space    |      |   0  |   .  |   =  |      |
`-----------------------------------------------------------------------------------'
```

### Lower

```ascii
,-----------------------------------------------------------------------------------.
|   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
|------+------+------+------+------+-------------+------+------+------+------+------|
|      |      |      |   /  |   {  |   [  |   ]  |   }  |   \  |   -  |   =  |  |   |
|------+------+------+------+------+------|------+------+------+------+------+------|
|      |      |      |      |      |      |      |      |      |   _  |   +  |Enter |
|------+------+------+------+------+------+------+------+------+------+------+------|
|      |      |      |      |      |    Space    |      | Home | PgDn | PgUp | End  |
`-----------------------------------------------------------------------------------'
```

### Function

```ascii
,-----------------------------------------------------------------------------------.
|      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  | Del  |
|------+------+------+------+------+-------------+------+------+------+------+------|
|      |  F11 |  F12 |  F13 |  F14 |  F15 |      |INSERT| Home | PgUp |      |      |
|------+------+------+------+------+------|------+------+------+------+------+------|
|      |      |      |      |      |      |      |DELETE| End  | PgDn |      | Enter|
|------+------+------+------+------+------+------+------+------+------+------+------|
|      |      |      |      |      |    Space    |      |      |      |      |      |
`-----------------------------------------------------------------------------------'
```

### Space Function

```ascii
,------------------------------------------------------------------------------------.
|PRNT SC|      |  UP  |      |      |      |      |      |      |      |      |      |
|-------+------+------+------+------+-------------+------+------+------+------+------|
|       | LEFT | DOWN | RIGHT|      |      | LEFT | DOWN |  UP  | RIGHT|      |      |
|-------+------+------+------+------+------|------+------+------+------+------+------|
|       |ALT+1 |ALT+2 |ALT+3 |ALT+4 |ALT+5 |ALT+6 |ALT+7 |ALT+8 |ALT+9 |ALT+10|      |
|-------+------+------+------+------+------+------+------+------+------+------+------|
|       |      |      |      |VOLDWN|             |VOL UP| PREV | MUTE |PLY/PS| NEXT |
`------------------------------------------------------------------------------------'
```

### Gaming

```ascii
,-----------------------------------------------------------------------------------.
| Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
|------+------+------+------+------+-------------+------+------+------+------+------|
| Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
|------+------+------+------+------+------|------+------+------+------+------+------|
| Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
|------+------+------+------+------+------+------+------+------+------+------+------|
| Ctrl | FN   | GUI  | Alt  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
`-----------------------------------------------------------------------------------'
```

### Adjust (Lower + Raise)

```ascii
,-----------------------------------------------------------------------------------.
|      |RESET |DEBUG |      |      |      |      |DMREC1|DMREC2|      |      |      |
|------+------+------+------+------+-------------+------+------+------+------+------|
|      |GAMING|      |      |      |      |      |DMPLY1|DMPLY2|Audoff|Aud on|      |
|------+------+------+------+------+------|------+------+------+------+------+------|
|      |      |      |      |      |      |      |DMRSTP|      |Musoff|Mus on|MusMod|
|------+------+------+------+------+------+------+------+------+------+------+------|
|      |      |      |AG_TOG|      |             |      |      |Voice-|Voice+|      |
`-----------------------------------------------------------------------------------'
```

#### Adjust Layer Features

```text
RESET:       Put the keyboard into bootloader mode for flashing
DEBUG:       Toggle debug mode
EEP_RST:     Reinitializes the keyboard’s EEPROM (persistent memory)

AG_TOG:      Toggle Alt and GUI swap on both sides (Mac)

DM_REC1:     Start recording Macro 1
DM_REC2:     Start recording Macro 2
DM_PLY1:     Replay Macro 1
DM_PLY2:     Replay Macro 2
DM_RSTP:     Finish the macro that is currently being recorded.

AU_ON:   Audio mode on
AU_OFF:  Audio mode off
AU_TOG:  Toggles Audio mode
MU_ON:   Turn music mode on
MU_OFF:  Turn music mode off
MU_TOG:  Toggle music mode
MU_MOD:  Cycle through the music modes:
    CHROMATIC_MODE:  Chromatic scale, row changes the octave
    GUITAR_MODE:     Chromatic scale, but the row changes the string (+5 st)
    VIOLIN_MODE:     Chromatic scale, but the row changes the string (+7 st)
    MAJOR_MODE:      Major scale

In Music Mode:
    LCTL:    start a recording
    LALT:    stop recording/stop playing
    LGUI:    play recording
    KC_UP:   speed-up playback
    KC_DOWN: slow-down playback
```

## Compilation

Use the docker image to compile this keyboard layout by running the following from the root of the repo:

```sh
util/docker_build.sh planck/rev6:mjuma
```

## Flashing

Flashing on linux can be done through the docker image

```sh
sudo util/docker_build.sh planck/rev6:mjuma:flash
```

or on Windows using the [QMK Toolbox](https://github.com/qmk/qmk_toolbox)
