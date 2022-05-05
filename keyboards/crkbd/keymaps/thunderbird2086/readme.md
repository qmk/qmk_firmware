# Thunderbird2086's custom CRKBD Layout

The concept is Mac and **baby finger** friendly keymap.

## Layers
- Colemak-DH: base layer. The option(⌥) and command(⌘) keys are assigned to thumb blocks as well as home position keys on each side.  Also, far end two rows are assigned to shift(⇧) and control(⌃) keys.
  ![colemak-dh](https://i.imgur.com/3BLzMSy.png)
- QWERTY: same as Colemak-DH layer
  ![qwery](https://i.imgur.com/v9JBwQu.png)
- CODE: numbers and symbols.  
  ![symbol](https://i.imgur.com/BPgPlYX.png)
- FUNCTION: function, meadia and navigation keys 
  ![function](https://i.imgur.com/cs5haUP.png)
- ADJUST: RGB control, Power control, default layer setting and reset
  ![adjust](https://i.imgur.com/uDIhigd.png)
- SECRET: hold `ADJUST` and `FUNCTION` to activate

## Custom OLED
This keymap includes custom OLED font and code. The font contains some logos and status indidcators from [gotham](../gotham) and [soundmonster](../soundmonster) including my own CAPS LOCK icon.  Enable OLED in rukes.mk to check it out. Feel free to reuse the font or parts of it.

## Flashing
Flash using `make crkbd:thunderbird2086:avrdude` for Pro Micro and `make crkbd:thunderbird2086:dfu` for Elite-C.
