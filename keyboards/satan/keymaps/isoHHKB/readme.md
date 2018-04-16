# HKKB-ISO Satan Layout by Stunny

This layout combines the split Right Shift ISO layout with the popular HHKB layout. The Caps Lock key will be replaced in the default layout by the Control key, which is more convenient for some people.

This version is designed to have in its base layer letter 'Ñ' for Spanish writing. Also, 'ç' is included for those who have to write in French, Catalan or other languages that may need it.

This keymap also supports control for a WS2812B RGB led strip connected to pin E2 of the microcontroller. If you want more functionalities, pls check RGB documentation at [QMK Docs]( https://docs.qmk.fm/feature_rgblight.html#rgb-lighting). This also goes for backlighting functionalities. If you want more control, check [QMK Docs](https://docs.qmk.fm/feature_backlight.html#backlighting) on that.

Base Layer:

```
,-----------------------------------------------------------.
|Esc~| 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |
|-----------------------------------------------------------|
|Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]| Ret |
|-----------------------------------------------------------|
|Ctrl   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  Ñ|  ;| ' |urn|
|-----------------------------------------------------------|
|Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift | Fn|
|-----------------------------------------------------------|
|    |Alt|LGUI  |      Space            |RGUI  |Alt|        |
`-----------------------------------------------------------'
```

Function Layer
```
,-----------------------------------------------------------.
|    |F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|PSR|  RESET|
|-----------------------------------------------------------|
|     |   |VUP|   |   |   |   |   |   |   |   |   |   |     |
|-----------------------------------------------------------|
|CapsLck|PRV|VDN|NXT|   |RGB|FRW|BRT|VAI|VAD|INC|DEC|   |   |
|-----------------------------------------------------------|
|        |   |   |  Ç|   |BTG|   |MUT|   |   |   |      |   |
|-----------------------------------------------------------|
|    |   |      |          PLY/PAU      |      |   |        |
`-----------------------------------------------------------'
```

Where:
- `PRV` is `KC_MEDIA_PREV_TRACK`
- `NXT` is `KC_MEDIA_NEXT_TRACK`
- `VUP` is `KC_AUDIO_VOL_UP`
- `VDN` is `KC_AUDIO_VOL_DOWN`
- `MUT` is `KC_AUDIO_MUTE`
- `PLY/PAU` is `KC_MEDIA_PLAY_PAUSE`
- `BTG` is `BL_TOGG` (toggles key backlighting)
- `INC` increases backlighting brightness
- `DEC` decreases backlighting brightness
- `PSR` is `KC_PSCREEN`
- `RGB` is `RGB_TOG`
- `FRW` jumps to next RGB mode
- `BRT` activates RGB breathing mode directly
- `VAI` increases RGB brightness
- `VAD` decreases RGB brightness
