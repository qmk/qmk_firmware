# EroIzzy Keymap

This keymap is VIA enabled and has side light effects for caps lock mode.

## Installation

Download and copy this folder and place it in you ../keyboards/gmmk/pro/ansi/keymaps/ folder
```bash
../keyboards/gmmk/pro/ansi/keymaps/
```

## Usage

These values are set default to white. Just change the RGB values to change the side lights color.
```
const int LED_R = 255;
const int LED_G = 255;
const int LED_B = 255;
```

This part controls the rate at which the side lights to strobe. Set the value in milliseconds

```
const int max = 60;
```
This keymap also changes the LED below CAPS LOCK to white by default. You can change it to be any of the preset QMK colors or add 3 parameters for RGB control.

```
rgb_matrix_set_color(3, RGB_WHITE);
//or
rgb_matrix_set_color(3, 255, 255, 255);
```
