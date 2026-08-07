# The Default Sol Layout
## Layout

### Qwerty layout
```
   * ,------------------------------------------------.  ,------------------------------------------------.
   * | GESC |   1  |   2  |   3  |   4  |   5  |   -  |  |   =  |   6  |   7  |   8  |   9  |   0  | BkSp |
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |   [  |  |   ]  |   Y  |   U  |   I  |   O  |   P  |   \  |
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * |FN(CAPS)| A  |   S  |   D  |   F  |   G  |   (  |  |   )  |   H  |   J  |   K  |   L  |   ;  |   '  |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * |Shift |   Z  |   X  |   C  |   V  |   B  |   {  |  |   }  |   N  |   M  |   ,  |   .  |   /  |Enter |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * | Ctrl |  Win |  Alt |  RGB | ADJ  | Space| DEL  |  | Enter| Space|  FN  | Left | Down | Up   |Right |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------'
   *                                    | Space| DEL  |  | Enter| Space|
   *                                    `-------------'  `-------------'
```

### Colemak layout
```
   * ,------------------------------------------------.  ,------------------------------------------------.
   * | GESC |   1  |   2  |   3  |   4  |   5  |   -  |  |   =  |   6  |   7  |   8  |   9  |   0  | BkSp |
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   F  |   P  |   B  |   [  |  |   ]  |   J  |   L  |   U  |   Y  |   ;  |   \  |
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * |FN(CAPS)| A  |   R  |   S  |   T  |   G  |   (  |  |   )  |   K  |   N  |   E  |   I  |   O  |   '  |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * |Shift |   Z  |   X  |   C  |   D  |   V  |   {  |  |   }  |   M  |   H  |   ,  |   .  |   /  |Enter |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * | Ctrl |  Win |  Alt |  RGB | ADJ  | Space| DEL  |  | Enter| Space|  FN  | Left | Down | Up   |Right |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------'
   *                                    | Space| DEL  |  | Enter| Space|
   *                                    `-------------'  `-------------'
```

### Function (FN)
```
   * ,------------------------------------------------.  ,------------------------------------------------.
   * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |      |  |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * |      | PGDN |  UP  | PGUP |      |      |      |  |      |      | PGDN |  UP  | PGUP | PRINT| HOME |
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * |      | LEFT | DOWN | RIGHT|      |      |      |  |      |      | LEFT | DOWN | RIGHT|INSERT| END  |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * |      |      |      |RGBMOD|      |      |      |  |      |      | PLAY | NEXT | MUTE | VOL- | VOL+ |
   * `------+------+------+------+------+------+------|  |------+------+------+------+------+------+------'
   *                                    |      |      |  |      |      |
   *                                    `-------------'  `-------------'
```

### Adjust (ADJ)
```
   * ,------------------------------------------------.  ,------------------------------------------------.
   * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |      |  |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * |      | SAD  | VAI  | SAI  | QK_BOOT|      |      |  |      |      |  P7  |  P8  |  P9  |      |      |
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * |      | HUD  | VAD  | HUI  |RGBRST|      |      |  |      |      |  P4  |  P5  |  P6  |      |      |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |  |      |      |  P1  |  P2  |  P3  |      |      |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * |      |      |      |RGBMOD|      |      |      |  |      |      |  P0  | PDOT | NLCK |QWERTY|COLEMK|
   * `------+------+------+------+------+------+------|  |------+------+------+------+------+------+------'
   *                                    |      |      |  |      |      |
   *                                    `-------------'  `-------------'
```

## Customize

see `qmk_firmware/keyboards/sol/rev1/keymaps/default/rules.mk`

```

# Variables you can set for SOL

BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no        # Mouse keys(+4700)
EXTRAKEY_ENABLE = yes       # Audio control and System control(+450)
CONSOLE_ENABLE = yes        # Console for debug(+400)
COMMAND_ENABLE = yes        # Commands for debug and configuration
NKRO_ENABLE = no
RGBLIGHT_ENABLE = yes       # Enable global lighting effects. Do not enable with RGB Matrix
LED_MIRRORED = yes          # Mirror LEDs across halves (enable DIP 1 on slave, and DIP 2 and 3 on master)
RGB_MATRIX_ENABLE = no      # Enable per-key coordinate based RGB effects. Do not enable with RGBlight (+8500)
RGB_MATRIX_KEYPRESSES = no  # Enable reactive per-key effects. Can be very laggy (+1500)
RGBLIGHT_FULL_POWER = no    # Allow maximum RGB brightness. Otherwise, limited to a safe level for a normal USB-A port
SWAP_HANDS_ENABLE = no      # Enable one-hand typing

OLED_ENABLE = no     # Enable the OLED Driver (+5000)
IOS_DEVICE_ENABLE = no      # Limit max brightness to connect to IOS device (iPad,iPhone)


```
## Compile

go to qmk top directory.
```
$ cd qmk_firmware
```

build
```
$ make rgbkb/sol:default
```

After the initial flash with AVRdudess, you should be able to flash using this:
```
$ make rgbkb/sol:default:dfu
```
