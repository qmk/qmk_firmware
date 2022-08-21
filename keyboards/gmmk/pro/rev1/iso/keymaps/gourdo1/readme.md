# [gourdo1's](mailto:gourdo1@outlook.com) GMMK Pro ISO layout

This Windows-centric ISO layout is based on [Jonavin's](https://github.com/qmk/qmk_firmware/tree/master/keyboards/gmmk/pro/rev1/iso/keymaps/jonavin) GMMK Pro layout with several additions, fixes, a tweaked keymap, updated layers, [Tomas Guinan's paddle game](https://github.com/qmk/qmk_firmware/tree/master/keyboards/gmmk/pro/rev1/ansi/keymaps/paddlegame) and expanded RGB controls.

![image](https://raw.githubusercontent.com/gourdo1/media/main/susuwatari.jpg)

## Features:

### Core Functionality

* ISO layout (added July xx, 2022)
* [VIA](https://www.caniusevia.com/) support enabled (added Mar 16, 2022)
* Most [default Glorious shortcuts](https://cdn.shopify.com/s/files/1/0549/2681/files/GMMK_Pro_User_Guide.pdf) enabled
* [N-key Rollover](https://en.wikipedia.org/wiki/Rollover_\(keyboard\)#n-key_rollover) (NKRO) -- toggled with Fn+R
* 1000Hz polling rate with 5ms debounce time for quick response in games
* Mouse Keys! Don't want to move your hands off the keyboard or you didn't bring it with you on the road? Use cursor keys to move the mouse.
* Overlay numpad on 789-UIOP-JKL;-M,. & Space-bar mapped to Enter key for rapid number entry
* Gaming mode (Fn+Win-key) locks out Win-key as well as double-tap Shift Capslock; Also RGB highlights WSAD and nearby gaming related keys
* [Caps Word](https://getreuer.info/posts/keyboards/caps-word/index.html) enabled: To capitalize the next word only, press and release both left and right shift keys at the same time. (added Feb 25, 2022)
* Multi-monitor app moving shortcuts: Fn+[,] (square brackets) to move current app window to next monitor (added Apr 11, 2022)
* Capslock toggled by double tap of Left Shift key or Fn + Capslock (RGB green highlighted)
* Paddle game accessible via Fn+P; Hit Fn+P again or double tap ESC to exit (added May 5, 2022)
* Single-handed shortcut for Ctrl-Alt-Delete: Fn+/ (added May 14, 2022)
* Single-handed shortcut for Win-L (lock Windows): Fn+L (added May 17, 2022)
* Domain shortcuts: Fn+.=".com", Fn+O="outlook.com", Fn+Y="yahoo.com", Fn+H="hotmail.com", Fn+G="gmail.com". (added Apr 7, 2022)
* Fn-Backslash for [Bootloader mode](https://github.com/qmk/qmk_firmware/blob/master/docs/newbs_flashing.md)
* Home key on F13, Del key right of Backspace
* Insert accessible via Shift-Backspace (so shift delete still works in Windows Explorer)
* PrtScrn, Scroll Lock, Pause/Break are top right on the keyboard: Fn+F11, Fn+F12, Fn+F13
* [Colemak](https://colemak.com/) key layout support (Layer accessible via Left Shift + turn Encoder clockwise until side LEDs light up purple)
* Double tap ESC any time to revert to base layer (added Feb 26, 2022)
* RGB backlight effects expanded to include framebuffer effects and reactive keypress modes (updated May 24, 2022)
* RGB backlight now remembers last color & effect settings after power down (updated May 24, 2022)

### Numpad + Mouse Keys (Capslock key)

* Overlay numpad + [Mouse Keys](https://github.com/qmk/qmk_firmware/blob/master/docs/feature_mouse_keys.md) are accessed through Capslock key hold (temp) or double press (locked) with RGB highlighting
* Numpad uses Space-bar as Enter for rapid number entry (added May 17, 2022)
* This layer disables much of the keyboard, except X/C/V for cut/copy/paste, WASD for cursor, Q/E for PgUp/PgDn, cursor keys become mouse keys, surrounding keys become mouse buttons and all number keys become numpad versions (so Alt char codes work regardless of which set you use)
* Fn and N keys light up orange if system numlock is off (inverted status), indicating numpad keys will not deliver expected output (Fn+N to toggle)
* Double zero on comma key.
* [Mouse Keys](https://github.com/qmk/qmk_firmware/blob/master/docs/feature_mouse_keys.md) allow you to use the mouse without taking your hand off the keyboard. (added Mar 15, 2022)
* Mouse controls are: Cursor keys = move mouse; RShift = button1, End = button2, RCtrl = button3, PgUp/PgDn = Scroll wheel
* Mouse Keys can also be accessed as a standalone layer by Left Shift-turning the Encoder until the cursor keys light up green

### Encoder Functionality

* Default knob turn changes volume; button press toggles mute
* Exponential encoder - quick repeated volume up doubles increase; quick repeated volume down triples decrease (added Feb 17, 2022)
* Fn + knob turn changes RGB idle timeout
* Fn + knob push puts PC to Sleep (Added May 14, 2022)
* holding Left Shift changes layers
* holding Right Shift navigates page up/down
* holding Left Ctrl navigates prev/next word
* holding Right Ctrl changes RGB hue/color
* holding Left Alt changes media prev/next track

### Paddle Game

* Based on [Tomas Guinan's excellent GMMK Pro paddle game](https://github.com/qmk/qmk_firmware/tree/master/keyboards/gmmk/pro/rev1/ansi/keymaps/paddlegame)
* Paddle Game playable by pressing Fn+P (P lights up green in Fn layer if game is enabled in firmware, otherwise it lights up red)
* Use rotary encoder to control paddle
* Contains 12 levels, indicated by blue LED on F-key row
* Player has 4 lives, indicated by nav cluster
* Deflect white balls while avoiding red ones
* Use Fn+P, double tap ESC or otherwise change layer to quit game

### Global RGB Controls

* RGB backlight lighting effect: Fn+up/down
* RGB backlight effect speed: Fn+left/right
* RGB backlight hue cycle: Fn+A/D
* RGB backlight brightness: Fn+W/S
* RGB backlight saturation: Fn+Q/E (added Feb 4, 2022)
* RGB backlight night mode toggle: Fn+Z (indicators still work)
* RGB backlight timeout: Fn+Encoder or "-" and "=" (default 15 minutes) (updated Apr 7, 2022)
    * indicators in Fn layer using RGB in F-key and number rows to show the current timeout in minutes
* Fn+Z to turn off RGB backlighting (indicator lights still work); press again to toggle
* RGB indicators on left side LEDs in order from top: System NumLock off (orange), Scroll Lock (red), Numpad (blue), Capslock (green).

### Advanced Controls

* Fn+\ to get to bootloader mode
* Fn+[ESC] to clear EEPROM (then unplug and re-plug) (added Apr 11, 2022)
* Fn+R to toggle N-key Rollover (added Apr 11, 2022)
* Fn+/ is single-handed shortcut to Ctrl-Alt-Delete (added May 14, 2022)
* Fn+L is single-handed shortcut to Win-L (lock Windows) (added May 17, 2022)
* Fn+[Encoder press] to sleep Windows PC (added May 14, 2022)

Link to latest firmware binary: https://github.com/gourdo1/media/raw/main/gmmk_pro_rev1_ansi_gourdo1.bin

Link to cheatsheet: https://github.com/gourdo1/media/raw/main/GMMK_Pro_Cheatsheet.pdf


## rules.mk Options

STARTUP_NUMLOCK_ON = yes             - Turns on NUMLOCK by default

ENCODER_DEFAULTACTIONS_ENABLE = yes  - Enabled default encoder functions

TD_LSFT_CAPSLOCK_ENABLE = yes        - This will enable double tap on Left Shift to toggle CAPSLOCK when using KC_LSFTCAPS

IDLE_TIMEOUT_ENABLE = yes            - Enables Timer functionality; for RGB idle timeouts that can be changed dynamically

INVERT_NUMLOCK_INDICATOR             - Inverts the Numlock indicator, LED is on when numlock is off -- numlock interferes with overlay numpad, so should  be off when numpad layer is active unless you have an external numpad.

COLEMAK_LAYER_ENABLE = yes           - Enables optional 5th layer for COLEMAK layout. Use Shift + encoder to enter 5th layer.

GAME_ENABLE ?= yes                   - Enables Paddle Game

## Layer Diagrams
### Base layer
![image](https://raw.githubusercontent.com/gourdo1/media/main/base.png)

### Fn Layer
![image](https://raw.githubusercontent.com/gourdo1/media/main/fn1.png)

### Layer 2 (Numpad)
![image](https://raw.githubusercontent.com/gourdo1/media/main/numpad.png)

### COLEMAK layer
![image](https://user-images.githubusercontent.com/71780717/131235050-980d2f54-2d23-4ae8-a83f-9fcdbe60d6cb.png)
