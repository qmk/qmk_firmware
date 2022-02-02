# gourdo1's GMMK Pro layout

This layout is based on Jonavin's GMMK Pro layout with some modifications to keymap, functionality and RGB.

Features:

	* Most default Glorious shortcuts enabled
	* Re-worked/simplified overlay numpad upon Capslock key hold (temp) or double press (locked) with RGB highlighting
	* Capslock toggled by double press of left Shift key or FN+Capslock
	* RGB backlit Capslock mode (under all alpha keys)
	* Winkey-locked/gaming mode with RGB highlights under WSAD and nearby gaming keys
	* Fn & N keys light up orange if system numlock is on indicating interference with numpad overlay (Fn+N to disable)
	* Keyboard RGB backlights custom timeout value controlled via Fn + Encoder or "," and "." (default 15 minutes)
		- setting to zero disables timeout
        - indicators in FN layer using RGB in F-key and number rows to show the current timeout in minutes
	* Home key on F-key row, Del key next to Backspace
	* Insert accessible via Shift-Backspace
	* Numpad layer (capslock key) disables much of keyboard, except X, C, V for cut, copy, paste, WASD become cursor keys and all number keys become numpad versions (so Alt character codes work regardless of which number keys you use)
	* Numpad turns both (bottom right) right arrow and End keys into Numpad Enter for convenience.
	* Encoder functionality:
		- default is change volume
		- FN Layer - change rgb idle timeout
		- holding Left shift, change layers
		- holding right shift, Navigate page up/down
		- holding Left Ctrl, navigate prev/next word
		- holding Right Ctrl, changes RGB hue/colour
		- holding Left Alt, change media prev/next track
	* PrtScrn, Scroll Lock, Pause/Break are top right on the keyboard: Fn+F11, Fn+F12, Fn+Home
	* Capslock, Scroll Lock, and Num Lock (not set) indicators on left side LEDs
    * Fn + Z to turn off all RGB lights except rgb indicators; press again to toggle

Link to latest firmware binary: https://github.com/gourdo1/qmk_firmware/blob/master/gmmk_pro_ansi_gourdo1.bin
	
rules.mk Options
================

STARTUP_NUMLOCK_ON = yes     		 - turns on NUMLOCK by default
ENCODER_DEFAULTACTIONS_ENABLE = yes  - Enabled default encoder funtions
TD_LSFT_CAPSLOCK_ENABLE = yes    	 - This will enable double tap on Left Shift to toggle CAPSLOCK when using KC_LSFTCAPS
IDLE_TIMEOUT_ENABLE = yes   		 - Enables Timer functionality; for RGB idle timeouts that can be changed dynamically
INVERT_NUMLOCK_INDICATOR   			 - inverts the Numlock indicator, LED is on when numlock is off -- numlock interferes with numpad keys, so should generally be off when numpad layer is active.
COLEMAK_LAYER_ENABLE = yes   		 - Enabled optional 5th layer for COLEMAK layout. Use Shift and encoder to enter 5th layer.


## All layers diagram
Default layer
![image](https://user-images.githubusercontent.com/71780717/124177658-82324880-da7e-11eb-9421-b69100131062.png)

Fn Layer
![image](https://user-images.githubusercontent.com/71780717/131255937-06c9691b-835f-4c94-93e6-6d1dc3de272b.png)

Layer 2 (Caps Lock Mod)
![image](https://user-images.githubusercontent.com/71780717/124177683-8b231a00-da7e-11eb-9434-e2475f679a54.png)

Optional COLEMAK layer
![image](https://user-images.githubusercontent.com/71780717/131235050-980d2f54-2d23-4ae8-a83f-9fcdbe60d6cb.png)
