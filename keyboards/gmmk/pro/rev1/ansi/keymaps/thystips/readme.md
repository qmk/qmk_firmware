# ThysTips's GMMK Pro layout

Fork from <https://github.com/qmk/qmk_firmware/tree/master/keyboards/gmmk/pro/rev1/ansi/keymaps/jonavin>

## Features

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
    - Fn + Q restore RGB settings defualt settings

- Emoticons:
  - EMO_SHRUG    = `\_("/)_/`
  - EMO_CONFUSE  = (*_*)
  - EMO_SAD      = :'-(
  - EMO_NERVOUS  = (~_~;)
  - EMO_JOY      = (^o^)
  - EMO_TEARS    = (T_T)
  - EMO_TFLIP    = (ノಠ痊ಠ)ノ彡┻━┻

## rules.mk OPTIONS - Active features from userspace

STARTUP_NUMLOCK_ON = yes
    - turns on NUMLOCK by default

ENCODER_DEFAULTACTIONS_ENABLE = yes
    - Enabled default encoder funtions
  
TD_LSFT_CAPSLOCK_ENABLE = yes
    - This will enable double tap on Left Shift to toggle CAPSLOCK when using KC_LSFTCAPS

IDLE_TIMEOUT_ENABLE = yes
    - Enables Timer functionality; for RGB idle timeouts that can be changed dynamically

INVERT_NUMLOCK_INDICATOR
    - Inverts the Num lock indicator, LED is on when num lokc is off

RGB_MATRIX_FUNCTION_COLOR
    - Choose color use when pressing FN. See list: <https://docs.qmk.fm/#/feature_rgb_matrix?id=colors> 
    
## All layers diagram

Default layer:

![kb-base](https://user-images.githubusercontent.com/6806486/184557799-7b0ef0fd-5837-41c8-9a5b-3e9832635bc2.png)

Fn Layer: 

![kb-fn](https://user-images.githubusercontent.com/6806486/184557805-68df344f-19e6-4fb0-909e-1716e3421200.png)

Layer 2 (Caps Lock Mod):

![kb-caps](https://user-images.githubusercontent.com/6806486/184557809-b992b648-93ca-4ccb-9c79-2f573543b55c.png)
