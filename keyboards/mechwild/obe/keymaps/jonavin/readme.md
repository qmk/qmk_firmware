# Jonavin's MechWild Orange Boy Ergo keymap

-->  This keymap makes user of user/jonavin userspace 

Features
  - Split spacebars, Split Backspace

- Add PrtScr, Scroll Lock, Break, NumLock to Fn layer
- Implement Win key lock using Fn+Win 
- Layer 2 (LOWER) when right B is held -- for emoticons
- Layer 3 (RAISE) mod on Caps Lock with double-tap to switch to this layer, double tap to switch back
    - provides arrows on WASD and additional nav keys + right hand numpad with 00; an be used for Alt Code entry
    - left spacebar Backspace
- add double tap of Left Shift to toggle Caps Lock


rules.mk OPTIONS - Active features from userspace
--------------------------------------------------

STARTUP_NUMLOCK_ON = yes
- turns on NUMLOCK by default

ENCODER_DEFAULTACTIONS_ENABLE = yes
- Enables default encoder funtions
    - holding Left shift, change layers
    - holding right shift, Navigate page up/down
    - holding Left Ctrl, navigate prev/next word
    - holding Left Alt, change media prev/next track
    - default is change volume
  
TD_LSFT_CAPSLOCK_ENABLE = yes
    - This will enable double tap on Left Shift to toggle CAPSLOCK when using KC_LSFTCAPS

IDLE_TIMEOUT_ENABLE = yes
    - Enables Timer functionality; for RGB idle timeouts that can be changed dynamically

EMOTICON_ENABLE
    - adds EMO_ keycodes for text emojis
    
## All layers diagram
![image](https://user-images.githubusercontent.com/71780717/135699192-c02b399b-4ea8-468c-bde0-81364188a039.png)

