# Birkir's Keymap for XIUDI's 60% XD60 PCB

Custom layout with some custom layers. Mac friendly.

## Layout
![Birkir's Layout](https://i.imgur.com/I69AYG1.png)

### Layer 0
Base layer as shown on layout above

### Layer 1
Active while pressing and holding `MENU`

RGB is purple while active

- `ESC` is `~`

### Layer 2
Toggled on and off with `FN`

RGB is red while active

RGB settings are persisted for layer 0 when done.

 - `1` Backlight DEC
 - `2` Backlight INC
 - `3` Backlight OFF
 - `4` Backlight ON
 - `5` RGB Toggle
 - `6` RGB Mode
 - `7` RGB Hue DEC (-)
 - `8` RGB Hue INC (+)
 - `9` RGB Saturation DEC (-)
 - `0` RGB Saturation INC (+)
 - `-/_` RGB Brightness DEC (-)
 - `+/=` RGB Brightness INC (+)
 - `BACKSPACE` RGB Mode set to PLAIN

## TODO

- Mac shortcuts on Layer 1
- More dynamic keyboard configuration on Layer 2

## Build
To build the default keymap, simply run `make xiudi/xd60:birkir`.
