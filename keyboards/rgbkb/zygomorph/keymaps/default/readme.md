# The Default Zygomorph Layout
## Layout

### Base modifier layout
```
   * ,-----------------------------------------.  ,-----------------------------------------.
   * | GESC |      |      |      |      |      |  |      |      |      |      |      | BkSp |
   * |------+------+------+------+------+------|  |------+------+------+------+------+------|
   * | Tab  |      |      |      |      |      |  |      |      |      |      |      |   \  |
   * |------+------+------+------+------+------|  |------+------+------+------+------+------|
   * |FN(CAPS)|    |      |      |      |      |  |      |      |      |      |      |   '  |
   * |------+------+------+------+------+------|  |------+------+------+------+------+------|
   * |Shift |      |      |      |      |      |  |      |      |      |      |      |Shift |
   * |------+------+------+------+------+------|  |------+------+------+------+------+------|
   * | Ctrl |  Win |  Alt |  RGB | ADJ  | Space|  | Space|  FN  | Left | Down | Up   |Right |
   * `-----------------------------------------'  `-----------------------------------------'
```

### Qwerty alphas
```
     * ,-----------------------------------------.  ,-----------------------------------------.
     * |      |      |      |      |      |      |  |      |      |      |      |      |      |
     * |------+------+------+------+------+------|  |------+------+------+------+------+------|
     * |      |   Q  |   W  |   E  |   R  |   T  |  |   Y  |   U  |   I  |   O  |   P  |      |
     * |------+------+------+------+------+------|  |------+------+------+------+------+------|
     * |      |   A  |   S  |   D  |   F  |   G  |  |   H  |   J  |   K  |   L  |   ;  |      |
     * |------+------+------+------+------+------|  |------+------+------+------+------+------|
     * |      |   Z  |   X  |   C  |   V  |   B  |  |   N  |   M  |   ,  |   .  |   /  |      |
     * |------+------+------+------+------+------|  |------+------+------+------+------+------|
     * |      |      |      |      |      |      |  |      |      |      |      |      |      |
     * `-----------------------------------------'  `-----------------------------------------'
```

### Colemak alphas
```
     * ,-----------------------------------------.  ,-----------------------------------------.
     * |      |      |      |      |      |      |  |      |      |      |      |      |      |
     * |------+------+------+------+------+------|  |------+------+------+------+------+------|
     * |      |   Q  |   W  |   F  |   P  |   G  |  |   J  |   L  |   U  |   Y  |   ;  |      |
     * |------+------+------+------+------+------|  |------+------+------+------+------+------|
     * |      |   A  |   R  |   S  |   T  |   D  |  |   H  |   N  |   E  |   I  |   O  |      |
     * |------+------+------+------+------+------|  |------+------+------+------+------+------|
     * |      |   Z  |   X  |   C  |   V  |   B  |  |   K  |   M  |   ,  |   .  |   /  |      |
     * |------+------+------+------+------+------|  |------+------+------+------+------+------|
     * |      |      |      |      |      |      |  |      |      |      |      |      |      |
     * `-----------------------------------------'  `-----------------------------------------'
```

### Function (FN)
```
     * ,-----------------------------------------.  ,-----------------------------------------.
     * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
     * |------+------+------+------+------+------|  |------+------+------+------+------+------|
     * |      | PGDN |  UP  | PGUP |      |      |  |      | PGDN |  UP  | PGUP | PRINT| HOME |
     * |------+------+------+------+------+------|  |------+------+------+------+------+------|
     * |      | LEFT | DOWN | RIGHT|      |      |  |      | LEFT | DOWN | RIGHT|INSERT| END  |
     * |------+------+------+------+------+------|  |------+------+------+------+------+------|
     * |      |      |      |      |      |      |  |      |      |      |      |      |      |
     * |------+------+------+------+------+------|  |------+------+------+------+------+------|
     * |      |      |      |RGBMOD|      |      |  |      | PLAY | NEXT | MUTE | VOL- | VOL+ |
     * `-----------------------------------------'  `-----------------------------------------'
```

### Adjust (ADJ)
```
     * ,-----------------------------------------.  ,-----------------------------------------.
     * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
     * |------+------+------+------+------+------|  |------+------+------+------+------+------|
     * |      | SAD  | VAI  | SAI  | RESET|      |  |      |      |      |      |      |      |
     * |------+------+------+------+------+------|  |------+------+------+------+------+------|
     * |      | HUD  | VAD  | HUI  |RGBRST|      |  |      |QWERTY|COLEMK|      |      |      |
     * |------+------+------+------+------+------|  |------+------+------+------+------+------|
     * |      |      |      |      |      |      |  |      |      |RGBTOG|  HUI |  SAI | VAI  |
     * |------+------+------+------+------+------|  |------+------+------+------+------+------|
     * |      |      |      |RGBMOD|      |      |  |      |      |RGBRMOD| HUD |  SAD | VAD  |
     * `-----------------------------------------'  `-----------------------------------------'
```

## Customize

see `qmk_firmware/keyboards/zygomorph/rev1/keymaps/default/rules.mk`

```

# Variables you can set for Zygomorph

BOOTMAGIC_ENABLE = no       # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = no        # Mouse keys(+4700)
EXTRAKEY_ENABLE = yes       # Audio control and System control(+450)
CONSOLE_ENABLE = yes        # Console for debug(+400)
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = no            # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
RGBLIGHT_ENABLE = yes       # Enable global lighting effects. Do not enable with RGB Matrix
RGBLIGHT_ANIMATIONS = yes   # LED animations
RGB_MATRIX_ENABLE = no      # Enable per-key coordinate based RGB effects. Do not enable with RGBlight (+8500)
RGB_MATRIX_KEYPRESSES = no  # Enable reactive per-key effects. Can be very laggy (+1500)
RGBLIGHT_FULL_POWER = yes   # Allow maximum RGB brightness. Otherwise, limited to a safe level for a normal USB-A port
SWAP_HANDS_ENABLE = no      # Enable one-hand typing
ENCODER_ENABLE = yes        # Enable rotary encoder (+90)
OLED_ENABLE = yes
OLED_DRIVER = SSD1306    # Enable the OLED Driver (+5000)
IOS_DEVICE_ENABLE = no      # Limit max brightness to connect to IOS device (iPad,iPhone)


```
## Compile

go to qmk top directory.
```
$ cd qmk_firmware
```

build
```
$ make rgbkb/zygomorph:default
```

After the initial flash with AVRdudess, you should be able to flash using this:
```
$ make rgbkb/zygomorph:default:dfu
```
