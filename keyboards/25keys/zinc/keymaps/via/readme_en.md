# The VIA Zinc Layout
## layout

### Qwerty

```
 ,-----------------------------------------.             ,-----------------------------------------.
 | Tab  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  | Bksp |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 | Ctrl |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   ;  |  '   |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 | Shift|   Z  |   X  |   C  |   V  |   B  |             |   N  |   M  |   ,  |   .  |   /  |Enter |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 | Esc  |  Fn  | Alt  | Win  |Lower |Space |             | Space| Raise| Left | Down |  Up  | Right|
 `------------------------------------------             ------------------------------------------'
```

### Lower
```
 ,-----------------------------------------.             ,-----------------------------------------.
 |   ~  |   !  |   @  |   #  |   $  |   %  |             |   ^  |   &  |   *  |   (  |   )  |      |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 |      |      |      |      |      |      |             |   -  |   _  |   +  |   {  |   }  |  |   |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 |      |      |      |      |      |      |             |      |      |      | Home | End  |      |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 |      |      |      |      |      |      |             |      |      | Next | Vol- | Vol+ | Play |
 `-----------------------------------------'             `-----------------------------------------'
```

### RAISE
```
 ,-----------------------------------------.             ,-----------------------------------------.
 |   `  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  | Del  |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 |      |  F1  |  F2  |  F3  |  F4  |  F5  |             |  F6  |   -  |   =  |   [  |   ]  |  \   |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 |      |  F7  |  F8  |  F9  |  F10 |  F11 |             |  F12 |      |      |      |      |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 |      |      |      |      |      |      |             |      |      | Next | Vol- | Vol+ | Play |
 `-----------------------------------------'             `-----------------------------------------'
```

### Adjust
```
 ,-----------------------------------------.             ,-----------------------------------------.
 |      | Reset|RGBRST|Aud on|Audoff|      |             |      |Qwerty|Colemk|Dvorak|      | Ins  |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 |      |RGB ON| HUE+ | SAT+ | VAL+ | Mac  |             | Win  |  -   |   =  |Print |ScLock|Pause |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 |MODE R|RGBMOD| HUE- | SAT- | VAL- |      |             |      |      |      |      |PageUp|      |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 |      |      |      | EISU | EISU | EISU |             | KANA | KANA | KANA | Home |PageDn| End  |
 `-----------------------------------------'             `-----------------------------------------'
```

### Adjust2 (Lower + Raise)
```
 ,-----------------------------------------.             ,-----------------------------------------.
 |      | Reset|RGBRST|Aud on|Audoff|      |             |      |Qwerty|Colemk|Dvorak|      | Ins  |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 |      |RGB ON| HUE+ | SAT+ | VAL+ | Mac  |             | Win  |  -   |   =  |Print |ScLock|Pause |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 |MODE R|RGBMOD| HUE- | SAT- | VAL- |      |             |      |      |      |      |PageUp|      |
 |------+------+------+------+------+------|             |------+------+------+------+------+------|
 |      |      |      | EISU | EISU | EISU |             | KANA | KANA | KANA | Home |PageDn| End  |
 `-----------------------------------------'             `-----------------------------------------'
```
## Compile

go to qmk top directory.

```
$ cd qmk_firmware
```
make with `zinc:<keymap_name>`

```
$ make zinc:default
```

To make and flash with `:flash`

```
$ make zinc:default:flash
```


## Customize

You can customize from the command line.

```
# Zinc keyboard 'default' keymap: convenient command line option
make ZINC=<options> zinc:defualt
#    option= back | under | both | cont | na | ios
#    ex.
#      make ZINC=under    zinc:via 
#      make ZINC=under,ios zinc:via
#      make ZINC=back     zinc:via
#      make ZINC=back,na  zinc:via
#      make zinc:via
```

Or edit `qmk_firmware/keyboards/zinc/rev1/keymaps/~/rules.mk` directly.

```
# Zinc keyboard customize
LED_BACK_ENABLE = no        # LED backlight (Enable SK6812mini backlight)
LED_UNDERGLOW_ENABLE = no   # LED underglow (Enable WS2812 RGB underlight)
LED_BOTH_ENABLE = no        # LED backlight and underglow
LED_RGB_CONT = no           # LED continuous backlight or/and underglow between left Zinc and right Zinc
LED_ANIMATIONS = yes        # LED animations
IOS_DEVICE_ENABLE = no      # connect to IOS device (iPad,iPhone)
```
