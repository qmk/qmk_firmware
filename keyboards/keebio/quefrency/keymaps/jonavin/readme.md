# jonavin's Quefrency layout - No Macros 65%

- ANSI qwerty layout with split Backspace, 1.25 Left mods, 1u right
- Left Fn key is Spacebar tap and Fn when held
- Layer 2 mod on Caps Lock with double-tap to switch to this layer, double tap to switch back
- Layer 2 provides arrows on WASD and additional nav keys + right hand numpad with 00
- ESC is set to GRAVESC (Esc when pressed, Shift-Esc is ~  and Win-ESC is `), plus handling for Ctrl-Shift-ESC to bring up Task Manager in Windows 
- Layer 2 left spacebar Backspace
- add double tap of Left Shift to toggle Caps Lock
- add Win Key lock function using Fn+Win
- additional encoder functionality
    - holding L shift, Navigate page up/down
    - holding Left Ctrl, navigate prev/next word
    - holding Left Alt, change media prev/next track
    - default is change volume
- RGB Functionality
    - additional RGB function key binds to arrow on Fn layer
    - Add capslock indicator, win key lock indicator
    - Fn and layer 2 indicators using RGB underglow

rules.mk OPTIONS - Active features from userspace
STARTUP_NUMLOCK_ON = yes
    - turns on NUMLOCK by default

TD_LSFT_CAPSLOCK_ENABLE = yes
    - This will enable double tap on Left Shift to toggle CAPSLOCK when using KC_LSFTCAPS

## All layers diagram

Default Layer
![image](https://user-images.githubusercontent.com/71780717/127251683-ad445b40-95a9-4d2a-b164-a96f3a13464e.png)

MO(1) / FN layer
![image](https://user-images.githubusercontent.com/71780717/127251736-047f2f73-dfff-4fcc-bf0e-a5378e2fee08.png)

MO(2) / Numpad layer
![image](https://user-images.githubusercontent.com/71780717/127251985-4f564a56-8836-4db0-9cbd-ec859755a8d9.png)
