## raffle's keymap
The default keymap is just enough to get started. This keymap adds a pok3r-like
raise layer, backlight RGB control layer, and firmware reset/debug adjust layer
for ANSI layouts.

In the default layer, the following modifications are made (using standard ANSI
keys for LHS):

- `CAPS` = `LCTRL`
- `LCTRL` = `RAISE`
- `APP` = `RGB`
- `LCTRL` + `APP` (`RAISE` + `RGB`) = `ADJUST`
- `GRV` = `ESC`

Additionally, the pok3r's `SHIFT` + `ESC` for `~` is maintained (with either `SHIFT`).

### Raise Layer
Emulates standard pok3r layout (without the onboard macro keys)

Highlights:

- `IJKL` for arrow keys
- `H`/`N` for `HOME`/`END`
- `U`/`P` for `PGUP`/`PGDN`
- `1` - `=` for `F1` - `F12`
- `Y` for calculator

Other standard keys from the pok3r layout are carried over. See the keymap or
the pok3r documentation for details.

### RGB Layer
Uses navigation keys from `RAISE` layer for RGB adjustment

- `I`/`K` for Value (brightness) Increase/Decrease
- `U`/`P` for Hue (color) Increase/Decrease
- `H`/`N` for Saturation Incrase/Decrease
- `GRV` to toggle RGB on/off
- `1`-`9` to activate QMK's predefined RGB animations

### Adjust Layer

- `GRV` activates firmware reset for flashing
- `1` enters debug mode
