# [gourdo1's](mailto:gourdo1@outlook.com) GMMK Pro ANSI layout

This Windows-centric ANSI layout is based on [Jonavin's](https://github.com/qmk/qmk_firmware/tree/master/keyboards/gmmk/pro/rev1/ansi/keymaps/jonavin) GMMK Pro layout with many additions, fixes, a revamped keymap, persistent user customizations, updated layers, [Tomas Guinan's paddle game](https://github.com/qmk/qmk_firmware/tree/master/keyboards/gmmk/pro/rev1/ansi/keymaps/paddlegame) and expanded RGB effects and controls.

![image](https://raw.githubusercontent.com/gourdo1/media/main/susuwatari.jpg)

## Features:

### Core Functionality

* Quick & Easy Customization: Open a text editor and hit [FN]` (tilde key) to view toggle-able features. (added Jun 29, 2022)
* [VIA](https://www.caniusevia.com/) support enabled (added Mar 16, 2022)
* Most [default Glorious shortcuts](https://cdn.shopify.com/s/files/1/0549/2681/files/GMMK_Pro_User_Guide.pdf) enabled
* [N-key Rollover](https://en.wikipedia.org/wiki/Rollover_\(keyboard\)#n-key_rollover) (NKRO) -- toggled with [FN]R
* 1000Hz polling rate with 5ms debounce time for quick response in games
* Mouse Keys! Don't want to move your hands off the keyboard or you didn't bring it with you? Use cursor keys to move the mouse
* Overlay numpad on 789-UIOP-JKL;-M,. & Space-bar mapped to Enter key for rapid number entry
* Gaming mode ([FN]Win-key) locks out Win-key and double-tap Shift Capslock; Also RGB highlights WSAD and nearby gaming keys
* Caps Word enabled: To capitalize the next word only, press and release left and right shift at the same time. (added Feb 25, 2022)
* Multi-monitor app moving shortcuts: [FN] ],[ (square brackets) to move current app window to next monitor (added Apr 11, 2022)
* Capslock toggled by double tap of Left Shift key or FN + Capslock (RGB green highlighted)
* Paddle game accessible via [FN]P. Hit [FN]P again or double tap [ESC] to exit (added May 5, 2022)
* Single-handed shortcut for Ctrl-Alt-Delete: [FN]/ (added May 14, 2022)
* Single-handed shortcut for WinKey-L (lock Windows): [FN]L (added May 17, 2022)
* Domain shortcuts: [FN]. for .com, [FN]O for outlook.com, [FN]Y for yahoo.com, [FN]H for hotmail.com, [FN]G for gmail.com. (added Apr 7, 2022)
* FN-Backslash for [Bootloader mode](https://github.com/qmk/qmk_firmware/blob/master/docs/newbs_flashing.md)
* Home key on F13, Del key right of Backspace
* Insert accessible via Shift-Backspace (so shift delete still works in Windows Explorer)
* PrtScrn, Scroll Lock, Pause/Break are top right on the keyboard: [FN]F11, [FN]F12, [FN]F13
* [Colemak](https://colemak.com/) key layout support (Accessible via Left Shift + turn Encoder clockwise until side LEDs light up purple)
* Double tap ESC any time to revert to base layer (added Feb 26, 2022)
* RGB backlight effects expanded to include framebuffer effects and reactive keypress modes (updated May 24, 2022)
* RGB backlight now remembers last color & effect settings after power down (updated May 24, 2022)

### Quick & Easy Customization
* Below features can be toggled by holding [FN] and pressing the number corresponding to that feature. Changes are saved to EEPROM for persistence.
* Print current settings by opening a text editor and pressing [FN]~ (CAUTION: verbose!)
* Quick view current settings by holding [FN] and viewing RGB under number keys (green means ON, violet means OFF)

#### Toggle-able Settings:
    1. CapsLock RGB - highlight under alpha keys
    2. Numpad RGB - highlight under numpad layer keys
    3. ESC key - Double tap ESC key to go to base layer
    4. Swap DEL and HOME - Default is DEL to the right of BKSPC & HOME is above BKSPC
    5. Capslock function - Toggle between double tap LShift for CapsLock with Numpad on CapsLock key (default) and standard CapsLock
    6. Encoder button - default mutes volume; alternate plays/pauses media
    7. Insert function - Toggle between SHIFT-BKSPC and SHIFT-DEL
    8. Modded-Space override - Use standard Space in place of modded-Space functions

### Numpad + Mouse Keys (Capslock key)

* Overlay numpad + [Mouse Keys](https://github.com/qmk/qmk_firmware/blob/master/docs/feature_mouse_keys.md) are accessed through Capslock key hold (temp) or double press (locked) with RGB highlighting
* Numpad uses Space-bar as Enter for rapid number entry (added May 17, 2022)
* This layer disables much of the keyboard, except X/C/V for cut/copy/paste, WASD for cursor, Q/E for PgUp/PgDn, cursor keys become mouse keys, surrounding keys become mouse buttons and all number keys become numpad versions (so Alt char codes work regardless of which set you use)
* FN and N keys light up orange if system numlock is off (inverted status), indicating numpad keys will not deliver expected output ([FN]N to toggle)
* Double zero on comma key.
* [Mouse Keys](https://github.com/qmk/qmk_firmware/blob/master/docs/feature_mouse_keys.md) allow you to use the mouse without taking your hand off the keyboard. (added Mar 15, 2022)
* Mouse controls are: Cursor keys = move mouse; RShift = button1, End = button2, RCtrl = button3, PgUp/PgDn = Scroll wheel
* Mouse Keys can also be accessed as a standalone layer by Left Shift-turning the Encoder until the cursor keys light up green

### Encoder Functionality

* Default knob turn changes volume; button press toggles mute
* Exponential encoder - quick repeated volume up doubles increase; quick repeated volume down triples decrease (added Feb 17, 2022)
* FN + knob turn changes RGB idle timeout
* FN + knob push puts PC to Sleep (Added May 14, 2022)
* holding Left Shift changes layers
* holding Right Shift navigates page up/down
* holding Left Ctrl navigates prev/next word
* holding Right Ctrl changes RGB hue/color
* holding Left Alt changes media prev/next track

### Paddle Game

* Based on [Tomas Guinan's excellent GMMK Pro paddle game](https://github.com/qmk/qmk_firmware/tree/master/keyboards/gmmk/pro/rev1/ansi/keymaps/paddlegame)
* Paddle Game playable by pressing [FN]P (P lights up green in FN layer if game is enabled in firmware, otherwise it lights up red)
* Use rotary encoder to control paddle
* Contains 12 levels, indicated by blue LED on F-key row
* Player has 4 lives, indicated by nav cluster
* Deflect white balls while avoiding red ones
* Use [FN]P, double tap ESC or otherwise change layer to quit game

### Global RGB Controls

* RGB backlight lighting effect: [FN]up/down
* RGB backlight effect speed: [FN]left/right
* RGB backlight hue cycle: [FN]A/D
* RGB backlight brightness: [FN]W/S
* RGB backlight saturation: [FN]Q/E (added Feb 4, 2022)
* RGB backlight night mode toggle: [FN]Z (indicators still work)
* RGB backlight timeout: [FN]Encoder or "-" and "=" (default 15 minutes) (updated June 28, 2022)
    *  F-key row indicator lights (cyan and blue) in FN layer display the current backlight timeout in minutes
* [FN]Z to turn off RGB backlighting (indicator lights still work); press again to toggle
* Left side RGB indicators in order from top: System NumLock off (orange), Scroll Lock (red), Numpad (blue), Capslock (green).

### Advanced Controls

* [FN]\ to get to bootloader mode
* [FN][ESC] to clear EEPROM (added Apr 11, 2022)
* [FN]R to toggle N-key Rollover (added Apr 11, 2022)
* [FN]/ is single-handed shortcut to Ctrl-Alt-Delete (added May 14, 2022)
* [FN]L is single-handed shortcut to Win-L (lock Windows) (added May 17, 2022)
* [FN][Encoder press] to sleep Windows PC (added May 14, 2022)

Link to latest firmware binary: https://github.com/gourdo1/gmmkpro-media/raw/main/gmmk_pro_rev1_ansi_gourdo1.bin

Link to cheatsheet: https://github.com/gourdo1/gmmkpro-media/raw/main/GMMK_Pro_Cheatsheet.pdf


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
![image](https://raw.githubusercontent.com/gourdo1/gmmkpro-media/main/base.png)

### FN Layer
![image](https://raw.githubusercontent.com/gourdo1/gmmkpro-media/main/fn1.png)

### Layer 2 (Numpad)
![image](https://raw.githubusercontent.com/gourdo1/gmmkpro-media/main/numpad.png)

### COLEMAK layer
![image](https://user-images.githubusercontent.com/71780717/131235050-980d2f54-2d23-4ae8-a83f-9fcdbe60d6cb.png)
