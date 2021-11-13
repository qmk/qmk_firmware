# @mattgauf's GMMK Pro layout

### `_DEFAULT`
> *Based on the default ansi layout, this keymap contains the following changes to the default layer.* 
 - Screensaver: `HYPER(F17)`
   - `KC_PSCR` → `MG_F17`
 - `KC_DEL` → `KC_HOME`
 
> *Additionally the encoder will follow new rules when holding a key.*
 - `KC_GUI` will cycle through applications (macOS variant)
 - `KC_GUI + KC_ALT` will tap the left and right arrows.
 - `KC_GUI + KC_SHIFT` will tap Undo and Redo (macOS variant)
 
### `_EFFECTS`
> *The function layer is now used for additional layer access, effect keys, and media keys (following the Macbook Pro fn key layout).* 

> *Additionally while effects is active, the encoder will only adjust the brightness of the RGB matrix.*
 - The RGB matrix effect and speed keys are located on the right hand vertical nav column.
   - `KC_HOME` → `RGB_MOD`
   - `KC_PGUP` → `RGB_RMOD`
   - `KC_PGDN` → `RGB_SPI`
   - `KC_END` → `RGB_SPD`
 - The RGB matrix Hue, Saturation keys are mapped to the arrow keys.
   - `KC_UP` → `RGB_SAI`
   - `KC_DN` → `RGB_SAD`
   - `KC_LEFT` → `RGB_HUD`
   - `KC_RIGHT` → `RGB_HUI`
 - The RGB matrix toggle is intercepted in process_record_user() cycling through the `LED_FLAG` modifiers. (`NONE`, `UNDERGLOW`, `KEYLIGHT`, `ALL`)
   - `KC_SLSH` → `RGB_TOG`
 - Hibernate: `HYPER(F18)`
   - `MG_F17` → `MG_F18`
   

### `_UTILITY`
*The utility layer is currently used for remapping* `KF_F9` *to* `KC_F12` *&* `MG_F17` *to the dynamic macro keys.*
 - Playback
   - `KC_F9` → `DM_PLY1`
   - `KC_F10` → `DM_PLY2`
 - Record
   - `KC_F11` → `DM_REC1`
   - `KC_F12` → `DM_REC2`
 - Stop Recording
   - `MG_F17` → `DM_RSTP`

### `_DFUMODE`
> *The final layer is used for resetting the board or triggering an immediate shutdown.*
 - DFU Mode
   - `KC_ESC` → `RESET`
 - Shutdown: `HYPER(F19)`
   - `MG_F17` → `MG_F19`
 - Encoder press, triggers debug output.
   - `KC_MUTE` → `DEBUG`
