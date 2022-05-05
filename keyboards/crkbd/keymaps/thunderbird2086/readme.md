# Thunderbird2086's custom CRKBD Layout

The concept is Mac and **baby finger** friendly keymap.

## Layers
- Colemak-DH: base layer. The option(⌥) and command(⌘) keys are assigned to thumb blocks as well as home position keys on each side.  Also, far end two columns are assigned to shift(⇧) and control(⌃) keys.
  ![colemak-dh](https://i.imgur.com/R7EzTTt.png)
  - Thumb keys
    | Tap         |  Double tap           |  Long tap        |
    | ---         | ---                   |  ---             |
    | Command(⌘)  | Command(⌘) + Space(␣) |                  |
    | Delete(⌦)   |                       |  Function layer  |
    | Backspace(⌫)|                       |  Function layer  |
    | Space(␣)    |                       |  Code layer      |
    | Enter(⏎)    |                       |  Code layer      |
  - Staggered keys
    | Tap         |  Double tap           |  Long tap        |
    | ---         | ---                   |  ---             |
    | TAB         | Control(⌃) + TAB      |                  |
    | a           |                       |  Control(⌃)      |
    | z           |                       |  Shift(⇧)        |
    | t           |                       |  Option(⌥)       |
    | n           |                       |  Command(⌘)      |
    | o           |                       |  Control(⌃)      |
    | '           |                       |  Control(⌃)      |
    | /           |                       |  Shift(⇧)        |
    | =           |                       |  Adjust layer    |

- QWERTY: same as Colemak-DH layer
  ![qwery](https://i.imgur.com/v9JBwQu.png)
  - Thumb keys : same as Colemak-DH
  - Staggered keys : almost same as Colemak-DH except
    | Tap         |  Double tap           |  Long tap        |
    | ---         | ---                   |  ---             |
    | f           |                       |  Option(⌥)       |
    | j           |                       |  Command(⌘)      |
    | ;           |                       |  Control(⌃)      |

- CODE: numbers and symbols.  
  ![symbol](https://i.imgur.com/BPgPlYX.png)
  - Thumb keys
    | Tap         |  Double tap           |  Long tap        |
    | ---         | ---                   |  ---             |
    | ESC         | Caps lock             |                  |
  - Staggered keys
    | Tap         |  Double tap           |  Long tap        |
    | ---         | ---                   |  ---             |
    | `           | Command(⌘) + `        |                  |

- FUNCTION: function, meadia and navigation keys 
  ![function](https://i.imgur.com/cs5haUP.png)
  - Thumb keys
    | Tap         |  Double tap           |  Long tap        |
    | ---         | ---                   |  ---             |
    | ESC         | Caps lock             |                  |

- ADJUST: RGB control, Power control, default layer setting and reset
  ![adjust](https://i.imgur.com/uDIhigd.png)
- SECRET: hold `ADJUST` and `FUNCTION` to activate

## Custom OLED
This keymap includes custom OLED font and code. The font contains some logos and status indidcators from [gotham](../gotham) and [soundmonster](../soundmonster) including my own CAPS LOCK icon.  Enable OLED in rukes.mk to check it out. Feel free to reuse the font or parts of it.

## Flashing
Flash using `make crkbd:thunderbird2086:avrdude` for Pro Micro and `make crkbd:thunderbird2086:dfu` for Elite-C.
