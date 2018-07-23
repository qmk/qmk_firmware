SSD1306 OLED Display via I2C
======

Features
--------

Some features supported by the firmware:


* I2C connection between the two halves is required as the OLED display will use this connection as well. Note this
  requires pull-up resistors on the data and clock lines.
* OLED display will connect from either side


Wiring
------


Work in progress...


<<<<<<< HEAD
OLED Configuration
-------------------------------
=======
## Customize

see `qmk_firmware/keyboards/helix/rev2/keymaps/default/rules.mk`

```
# Helix keyboard customize
# you can edit follows 7 Variables
#  jp: 以下の7つの変数を必要に応じて編集します。
HELIX_ROWS = 5              # Helix Rows is 4 or 5
OLED_ENABLE = no            # OLED_ENABLE
LOCAL_GLCDFONT = no         # use each keymaps "helixfont.h" insted of "common/glcdfont.c"
LED_BACK_ENABLE = no        # LED backlight (Enable WS2812 RGB underlight.)
LED_UNDERGLOW_ENABLE = no   # LED underglow (Enable WS2812 RGB underlight.)
LED_ANIMATIONS = yes        # LED animations
IOS_DEVICE_ENABLE = no      # connect to IOS device (iPad,iPhone)

```
## Compile

go to qmk top directory.
```
$ cd qmk_firmware
```

build
```
$ make helix:default
```

flash to keyboard
```
$ make helix:default:avrdude
```

## Link
* more detail wrote in Japanese [helix/Doc/firmware_jp.md](https://github.com/MakotoKurauchi/helix/blob/master/Doc/firmware_jp.md)
* [Helix top](https://github.com/MakotoKurauchi/helix)
>>>>>>> 1225120b92411f4fa1a9dc79af2fd85bd5aa6dcc

Work in progress...
