Jonavin Kastenwagen 48 Keymap
Designed to match my other keymaps

NOTE: Uses userpace user/jonavin

Feature changes from Default
  - Bottom row mapping LCtrl, LAlt, LGui, spacebars, MO(2)/LOWER, MO(1)/FN, RCtrl
  - CAPS as MO(3)/RAISE - tap to toggle
  - numpad in MO(3) layer
  - double tap L Shift for CAPS
  - RESET moved to under encoder in MO(2)
  - implement Win Key Lock 
  - GRV Escape overides
  - ENCODERS
    - TOP LEFT
      - Volume up/down
    - TOP RIGHT
      - Left Shift held - change layers
      - Right Shift held - Page Up/Down
      - Left Ctrl held - navigate next/prev words
      - Left Alt held - change media next/prev track
      - RAISE + Encode push toggles between volume change and tab scrolling
    - ENCODER_DIRECTION_FLIP has been defined to avoid issues with encoder going in opposition direction

OPTIONS in rules.mk
---------------------------------------

STARTUP_NUMLOCK_ON = yes
- turns on NUMLOCK by default

ENCODER_DEFAULTACTIONS_ENABLE = yes
- Enabled default encoder funtions
- When enabled, use this in the keymap for an additional encoder processing 
-   bool encoder_update_keymap(uint8_t index, bool clockwise)
  
OPTION: set ENCODER_DEFAULTACTIONS_INDEX in config.h to the encoder number if the encoder is not index 0  -- set to 1 for top right encoder

TD_LSFT_CAPSLOCK_ENABLE = yes
- This will enable double tap on Left Shift to toggle CAPSLOCK
-   KC_LSFTCAPS to bind to left Shift to enable feature
-   KC_LSFTCAPSWIN does the same thing but will not turn on CAPS when Win Lkey is disabled
    
INVERT_NUMLOCK_INDICATOR
- inverts the Num lock indicator, LED is on when num lock is off

ALTTAB_SCROLL_ENABLE
- When ENCODER_DEFAULTACTIONS_ENABLE = yes, 
    Enables Alt-Tab scrolling functions in default encoder, 
    bind KS_TSTOG to a key to enable/disable Alt-Tab vs Volume control
- When defining your own encoder functions use encoder_action_alttabscroll(bool clockwise) to assign the encodr action


Layout
![image](https://user-images.githubusercontent.com/71780717/128580303-5d660a5f-1420-4e38-b40a-212573496b1c.png)
