# jonavin's GMMK Pro layout

- Add Fn layer keys from Glorious Core mapping that's missing in the default qmk mapping
- Add PrtScr, Scroll Lock, Break, NumLock to Fn layer
- Implement Win key lock using Fn+Win like in Glorious Core firmware
- Layer 2 mod on Caps Lock with double-tap to switch to this layer, double tap to switch back
- Layer 2 provides arrows on WASD and additional nav keys + right hand numpad with 00; an be used for Alt Code entry
- Layer 2 left spacebar Backspace
- add double tap of Left Shift to toggle Caps Lock
- additional encoder functionality
    - FN Layer - change rgb idle timeout
    - holding Left shift, change layers
    - holding right shift, Navigate page up/down
    - holding Left Ctrl, navigate prev/next word
    - holding Right Ctrl, changes RGB hue/colour
    - holding Left Alt, change media prev/next track
    - default is change volume
    
- LED/RGB Functionality
    - RGB idle timeout (default 5 minutes)
        - Can be changed in FN layer with < and > or encoder
        - setting to zero disables timeout
        - indicators in FN layer using RGB in FN and number rows to show the timeout in minutes
    - LED address location map as enum definition in rgb_matrix_map.h
    - LED group lists for arrows, numpad, F row, num row, left and right side LEDs
    - default startup in single mode with default colour 
    - Capslock, Scroll Lock, and Num Lock (not set) indicator on left side LED
    - Layer indicator on right side LED
    - Fn key light up red when Fn layer activate
    - Win Key light up red when Win Lock mode enabled
    - Layer 2 activation lights up Numpad area
    - Fn + Z to turn off all RGB lights except rgb indicators; press again to toggle

rules.mk OPTIONS - Active features from userspace
STARTUP_NUMLOCK_ON = yes
    - turns on NUMLOCK by default

ENCODER_DEFAULTACTIONS_ENABLE = yes
    - Enabled default encoder funtions
  
TD_LSFT_CAPSLOCK_ENABLE = yes
    - This will enable double tap on Left Shift to toggle CAPSLOCK when using KC_LSFTCAPS

IDLE_TIMEOUT_ENABLE = yes
    - Enables Timer functionality; for RGB idle timeouts that can be changed dynamically

COLEMAK_LAYER_ENABLE = yes
    - Enabled optional 5th layer for COLEMAK layout
    - Use Shift and encoder to enter 5th layer, right led indicator lights up BLUE
    
## All layers diagram
Default layer
![image](https://user-images.githubusercontent.com/71780717/124177658-82324880-da7e-11eb-9421-b69100131062.png)

Fn Layer
![image](https://user-images.githubusercontent.com/71780717/131255937-06c9691b-835f-4c94-93e6-6d1dc3de272b.png)

Layer 2 (Caps Lock Mod)
![image](https://user-images.githubusercontent.com/71780717/124177683-8b231a00-da7e-11eb-9434-e2475f679a54.png)

Optional COLEMAK layer
![image](https://user-images.githubusercontent.com/71780717/131235050-980d2f54-2d23-4ae8-a83f-9fcdbe60d6cb.png)
