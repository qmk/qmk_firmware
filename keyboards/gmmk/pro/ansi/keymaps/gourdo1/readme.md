# gourdo1's GMMK Pro layout

This Windows-centric layout is based on Jonavin's GMMK Pro layout with some modifications to keymap, functionality and RGB.

Features:

Basic Shortcuts

	* Most default Glorious shortcuts enabled
	* Fn-Backslash for Bootloader mode
	* Capslock toggled by double tap of Left Shift key or FN + Capslock (RGB highlighted)
	* Gaming mode (FN + Win-key) locks out Win-key as well as double-tap Shift Capslock; Also RGB highlights WSAD and nearby gaming
        related keys
	* Home key on F-key row, Del key next to Backspace
	* Insert accessible via Shift-Backspace (so shift delete still works in Windows Explorer)
	* PrtScrn, Scroll Lock, Pause/Break are top right on the keyboard: Fn+F11, Fn+F12, Fn+Home

Numpad Overlay Layer

	* Re-worked/simplified overlay numpad upon Capslock key hold (temp) or double press (locked) with RGB highlighting
	* Numpad layer (capslock key) disables much of keyboard, except X, C, V for cut, copy, paste, WASD become cursor keys and all number
        keys become numpad versions (so Alt character codes work regardless of which number keys you use)
	* Numpad turns both right arrow and End keys into Numpad-Enter for convenience.
	* Fn & N keys light up orange if system numlock is off (inverted status), indicating numpad keys will not deliver expected output
        (FN + N to toggle)

Encoder Functionality

	* Default knob turn changes volume; button press toggles mute
	* Exponential encoder - quick repeated volume up doubles increase; quick repeated volume down triples decrease
	* FN knob turn changes RGB idle timeout
	* holding Left Shift changes layers
	* holding Right Shift navigates page up/down
	* holding Left Ctrl navigates prev/next word
	* holding Right Ctrl changes RGB hue/color
	* holding Left Alt changes media prev/next track

RGB

	* RGB backlight lighting effect: FN + up/down
	* RGB backlight effect speed: FN + left/right
	* RGB backlight hue cycle: FN + A/D
	* RGB backlight brightness: FN + W/S
	* RGB backlight night mode toggle: FN + Z (indicators still work)
	* RGB backlight timeout: FN + Encoder or "," and "." (default 15 minutes)
        - indicators in FN layer using RGB in F-key and number rows to show the current timeout in minutes
	* RGB indicators on left side LEDs: Capslock (green), Scroll Lock (red), and Num Lock not set (orange) 
    * FN + Z to turn off all RGB lights except rgb indicators; press again to toggle

Link to latest firmware binary: https://github.com/gourdo1/media/raw/main/gmmk_pro_ansi_gourdo1.bin

Link to cheatsheet: https://github.com/gourdo1/media/raw/main/GMMK_Pro_Cheatsheet.pdf

	
rules.mk Options
================

STARTUP_NUMLOCK_ON = yes     		 - turns on NUMLOCK by default

ENCODER_DEFAULTACTIONS_ENABLE = yes  - Enabled default encoder functions

TD_LSFT_CAPSLOCK_ENABLE = yes    	 - This will enable double tap on Left Shift to toggle CAPSLOCK when using KC_LSFTCAPS

IDLE_TIMEOUT_ENABLE = yes   		 - Enables Timer functionality; for RGB idle timeouts that can be changed dynamically

INVERT_NUMLOCK_INDICATOR   			 - inverts the Numlock indicator, LED is on when numlock is off -- numlock interferes with numpad keys, so should generally be off when numpad layer is active.

COLEMAK_LAYER_ENABLE = yes   		 - Enabled optional 5th layer for COLEMAK layout. Use Shift and encoder to enter 5th layer.


## Layer Diagrams
Base layer
![image](https://raw.githubusercontent.com/gourdo1/media/main/base.png)

Fn Layer
![image](https://raw.githubusercontent.com/gourdo1/media/main/fn1.png)

Layer 2 (Numpad)
![image](https://raw.githubusercontent.com/gourdo1/media/main/numpad.png)

Optional COLEMAK layer
![image](https://user-images.githubusercontent.com/71780717/131235050-980d2f54-2d23-4ae8-a83f-9fcdbe60d6cb.png)
