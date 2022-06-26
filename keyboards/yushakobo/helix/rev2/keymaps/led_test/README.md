# LED test Keymap

## Layout

The layout is the same as default.

## Feature

* OLED is enabled.
* LED backlight is enabled and always lit.
* The lighting color of LED changes periodically. Red, Green and Blue.

The user can check whether the LED is lit or not.

## Compile

```
$ cd qmk_firmware
$ make helix:led_test
```

## Flash QMK Firmware

Execute the 'make' command and press the reset switch on the keyboard.
```
$ make helix:led_test:flash
```
