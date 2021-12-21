# jonavin's KBD 67 Lite keymap

NOTE: This keymap uses features from qmk userspace in user/jonavin.  I fyou copy this keymap you should also the user folder.

- Add PrtScr, Scroll Lock, Break, NumLock to Fn layer
- add double tap of Left Shift to toggle Caps Lock
- Implement Win key lock using Fn+Win 
- Layer 2 mod on Caps Lock with double-tap to switch to this layer, double tap to switch back
- Layer 2 provides arrows on WASD and additional nav keys + right hand numpad with 00; an be used for Alt Code entry
- Layer 2 spacebar Backspace
    
- LED/RGB Functionality
    - RGB idle timeout (default 5 minutes)
        - Can be changed in FN layer with < and >
        - setting to zero disables timeout
        - indicators in FN layer using RGB in number and qwerty rows to show the timeout in minutes
    - LED address location map as enum definition in rgb_matrix_map.h
    - LED group lists for arrows, numpad, qwerty row, num row LEDs
    - default startup in single colour mode 
    - Capslock, Scroll Lock, and Num Lock (not set) indicator
    - Fn key light up GOLD when Fn layer activate
    - Win Key light up red when Win Lock mode enabled
    - Layer 2 activation lights up Numpad area
    - Fn + Z to turn off all RGB lights except rgb indicators; press again to toggle

rules.mk OPTIONS - Active features from userspace
STARTUP_NUMLOCK_ON = yes
    - turns on NUMLOCK by default

TD_LSFT_CAPSLOCK_ENABLE = yes
    - This will enable double tap on Left Shift to toggle CAPSLOCK when using KC_LSFTCAPS

IDLE_TIMEOUT_ENABLE = yes
    - Enables Timer functionality; for RGB idle timeouts that can be changed dynamically

INVERT_NUMLOCK_INDICATOR = yes
    - inverts the Num lock indicator, LED is on when num lock is off

## All layers diagram
![image](https://user-images.githubusercontent.com/71780717/146864247-4ec05ef7-7936-45db-9db9-02fb17d3f7ed.png)

