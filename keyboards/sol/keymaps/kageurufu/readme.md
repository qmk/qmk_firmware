# KageUrufu's Sol Layout

Read the keymap for the layout, I don't want to deal with maintained ascii art

## Customize

see `qmk_firmware/keyboards/sol/rev1/keymaps/default/rules.mk`

```
# Variables you can set for SOL

BOOTMAGIC_ENABLE = no       # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = no        # Mouse keys(+4700)
EXTRAKEY_ENABLE = yes       # Audio control and System control(+450)
CONSOLE_ENABLE = yes        # Console for debug(+400)
COMMAND_ENABLE = yes        # Commands for debug and configuration
NKRO_ENABLE = no            # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
RGBLIGHT_ENABLE = yes       # Enable global lighting effects. Do not enable with RGB Matrix
LED_ANIMATIONS = yes        # LED animations
LED_MIRRORED = no           # Mirror LEDs across halves (enable DIP 1 on slave, and DIP 2 and 3 on master)
RGB_MATRIX_ENABLE = no      # Enable per-key coordinate based RGB effects. Do not enable with RGBlight (+8500)
RGB_MATRIX_KEYPRESSES = no  # Enable reactive per-key effects. Can be very laggy (+1500)
RGBLIGHT_FULL_POWER = no    # Allow maximum RGB brightness. Otherwise, limited to a safe level for a normal USB-A port
UNICODE_ENABLE = no         # Unicode
SWAP_HANDS_ENABLE = no      # Enable one-hand typing
ENCODER_ENABLE_CUSTOM = yes # Enable rotary encoder (+90)

OLED_ENABLE = no            # OLED_ENABLE (+5000)
IOS_DEVICE_ENABLE = no      # Limit max brightness to connect to IOS device (iPad,iPhone)

```
## Compile

go to qmk top directory.
```
$ cd qmk_firmware
```

build
```
$ make sol:default
```

After the initial flash with AVRdudess, you should be able to flash using this:
```
$ make sol:default:dfu
```