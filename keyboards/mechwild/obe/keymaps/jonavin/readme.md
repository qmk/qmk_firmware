# Jonavin's MechWild Orange Boy Ergo keymap

-->  This keymap makes use of user/jonavin userspace 

Features
  - Split spacebars, Split Backspace
  - Inverted Num Lock indicator (LED on when num lock if off) 
  - RGB Winlock indicator (requires LED stripto be installed)
  - RGB Layer indicators: FN/MO1 - Purple; LOWER/MO2 - Yellow; RAISE/MO3/NumPad - Green
  - quick demo https://youtu.be/gR1awbsouLk

- Add PrtScr, Scroll Lock, Break, NumLock to Fn layer
- Implement Win key lock using Fn+Win 
- Layer 2 (LOWER) when right B is held -- for emoticons
- Layer 2 RGB functions, and EEPROM Reset
- Layer 3 (RAISE) mod on Caps Lock with double-tap to switch to this layer, double tap to switch back
    - provides arrows on WASD and additional nav keys + right hand numpad with 00; an be used for Alt Code entry
    - left spacebar Backspace
- add double tap of Left Shift to toggle Caps Lock
- Up arrow is also Shift when held
- Pushing the encoder switches the default encoder scroll between volume control and Alt-Tab 


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
    
INVERT_NUMLOCK_INDICATOR
    - inverts the Num lock indicator, LED is on when num lokc is off
    
ALTTAB_SCROLL_ENABLE
    - bind KS_TSTOG to a different key to change how this toggle happens 
   
## All layers diagram
![image](https://user-images.githubusercontent.com/71780717/137356366-6b23c71b-9499-473e-a1e3-c65644135fc6.png)
