# gourdo1's GMMK Pro ANSI layout

This Windows-centric layout is based on [Jonavin's](https://github.com/qmk/qmk_firmware/tree/master/keyboards/gmmk/pro/ansi/keymaps/jonavin) GMMK Pro layout with several additions, modifications, a tweaked keymap, updated layers and expanded RGB controls.

![image](https://raw.githubusercontent.com/gourdo1/media/main/susuwatari.jpg)

## Features:

### Core Functionality

* [VIA](https://www.caniusevia.com/) support enabled (added Mar 16, 2022)
* Most [default Glorious shortcuts](https://cdn.shopify.com/s/files/1/0549/2681/files/GMMK_Pro_User_Guide.pdf) enabled
* [N-key Rollover](https://en.wikipedia.org/wiki/Rollover_\(keyboard\)#n-key_rollover) (NKRO) -- toggled with FN+R
* Gaming mode (FN + Win-key) locks out Win-key as well as double-tap Shift Capslock; Also RGB highlights WSAD and nearby gaming related keys
* [Caps Word](https://getreuer.info/posts/keyboards/caps-word/index.html) enabled: To capitalize the next word only, press and release both left and right shift keys at the same time. (added Feb 25, 2022)
* Multi-monitor app moving shortcuts: FN + [,] (square brackets) to move current app window to next monitor (added Apr 11, 2022)
* Domain shortcuts: FN+.=".com", FN+O="outlook.com", FN+Y="yahoo.com", FN+H="hotmail.com", FN+G="gmail.com". (added Apr 7, 2022)
* Capslock toggled by double tap of Left Shift key or FN + Capslock (RGB green highlighted)
* Fn-Backslash for [Bootloader mode](https://github.com/qmk/qmk_firmware/blob/master/docs/newbs_flashing.md)
* Home key on F13, Del key right of Backspace
* Insert accessible via Shift-Backspace (so shift delete still works in Windows Explorer)
* PrtScrn, Scroll Lock, Pause/Break are top right on the keyboard: Fn+F11, Fn+F12, Fn+F13
* [Colemak](https://colemak.com/) key layout support (Layer accessible via Left Shift + turn Encoder clockwise until side LEDs light up purple)
* Double tap ESC any time to revert to base layer (added Feb 26, 2022)

### Numpad + Mouse Keys (Capslock key)

* Overlay numpad + [Mouse Keys](https://github.com/qmk/qmk_firmware/blob/master/docs/feature_mouse_keys.md) are accessed through Capslock key hold (temp) or double press (locked) with RGB highlighting
* This layer disables much of the keyboard, except X/C/V for cut/copy/paste, WASD for cursor, Q/E for PgUp/PgDn, cursor keys become mouse keys, surrounding keys become mouse buttons and all number keys become numpad versions (so Alt char codes work regardless of which set you use)
* Fn & N keys light up orange if system numlock is off (inverted status), indicating numpad keys will not deliver expected output (FN + N to toggle)
* Double zero on comma key.
* [Mouse Keys](https://github.com/qmk/qmk_firmware/blob/master/docs/feature_mouse_keys.md) allow you to use the mouse without taking your hand off the keyboard. (added Mar 15, 2022)
* Mouse controls are: Cursor keys = move mouse; RShift = button1, End = button2, RCtrl = button3, PgUp/PgDn = Scroll wheel
* Mouse Keys can also be accessed as a standalone layer by Left Shift-turning the Encoder until the cursor keys light up green

### Encoder Functionality

* Default knob turn changes volume; button press toggles mute
* Exponential encoder - quick repeated volume up doubles increase; quick repeated volume down triples decrease (added Feb 17, 2022)
* FN knob turn changes RGB idle timeout
* holding Left Shift changes layers
* holding Right Shift navigates page up/down
* holding Left Ctrl navigates prev/next word
* holding Right Ctrl changes RGB hue/color
* holding Left Alt changes media prev/next track

### Global RGB Controls

* RGB backlight lighting effect: FN + up/down
* RGB backlight effect speed: FN + left/right
* RGB backlight hue cycle: FN + A/D
* RGB backlight brightness: FN + W/S
* RGB backlight saturation: FN + Q/E (added Feb 4, 2022)
* RGB backlight night mode toggle: FN + Z (indicators still work)
* RGB backlight timeout: FN + Encoder or "-" and "=" (default 15 minutes) (updated Apr 7, 2022)
    * indicators in FN layer using RGB in F-key and number rows to show the current timeout in minutes
* RGB indicators on left side LEDs: Capslock (green), Scroll Lock (red), and Num Lock not set (orange) 
* FN + Z to turn off RGB backlighting; press again to toggle

### Advanced Controls

* FN + \ to get to bootloader mode
* FN + [ESC] to clear EEPROM (then unplug and re-plug) (added Apr 11, 2022)
* FN + R to toggle N-key Rollover (added Apr 11, 2022)

Link to latest firmware binary: https://github.com/gourdo1/media/raw/main/gmmk_pro_ansi_gourdo1.bin

Link to cheatsheet: https://github.com/gourdo1/media/raw/main/GMMK_Pro_Cheatsheet.pdf


## rules.mk Options

STARTUP_NUMLOCK_ON = yes             - turns on NUMLOCK by default

ENCODER_DEFAULTACTIONS_ENABLE = yes  - Enabled default encoder functions

TD_LSFT_CAPSLOCK_ENABLE = yes        - This will enable double tap on Left Shift to toggle CAPSLOCK when using KC_LSFTCAPS

IDLE_TIMEOUT_ENABLE = yes            - Enables Timer functionality; for RGB idle timeouts that can be changed dynamically

INVERT_NUMLOCK_INDICATOR             - inverts the Numlock indicator, LED is on when numlock is off -- numlock interferes with numpad keys, so should generally be off when numpad layer is active.

COLEMAK_LAYER_ENABLE = yes           - Enable optional 5th layer for COLEMAK layout. Use Shift + encoder to enter 5th layer.


## Layer Diagrams
### Base layer
![image](https://raw.githubusercontent.com/gourdo1/media/main/base.png)

### Fn Layer
![image](https://raw.githubusercontent.com/gourdo1/media/main/fn1.png)

### Layer 2 (Numpad)
![image](https://raw.githubusercontent.com/gourdo1/media/main/numpad.png)

### COLEMAK layer
![image](https://user-images.githubusercontent.com/71780717/131235050-980d2f54-2d23-4ae8-a83f-9fcdbe60d6cb.png)
