Copyright 2017 James Morgan <ja.morgan1@outlook.com>

#MogranJM's Nyquist layout

```
make nyquist/rev1:DivergeJM
```

This keymap is based on my Terminus_Mini (../../../terminus\_mini/default) layout (credit for the names of these layouts goes to UniKeyboard & reddit's /u/blahlicus)

The terminus_mini is a handwired 4x12 ortholinear keyboard with two 2U thumb bar keys. This implementation of the layout converts it to a split 5x12 (two halves, each 5x6) keyboard with a 2U thumb key on the inner bottom corner of each half. 

The TERMINUS\_MINI layout (../../../terminus_mini/terminus_mini.h) is handwired and the 2U keys are handled using KC_NO to detail that two columns do not have a 4th column. This layout is based on a PCB, so the keymap represents the 2U keys as duplicates of the same 1U key.

```
.----------------------------------------.     .-----------------------------------------. 
| Esc |   1  |   2  |   3  |   4  |   5  |     |   6  |   7  |   8  |   9  |   0  | Del  | 
|-----+------+------+------+------+------|     |------+------+------+------+------+------| 
| Tab |   Q  |   W  |   F  |   P  |   G  |     |   J  |   L  |   U  |   Y  |   ;  |  \\  | 
|-----+------+------+------+------+------|     |------+------+------+------+------+------| 
| BS  |   A  |   R  |   S  |   T  |   D  |     |   H  |   N  |   E  |   I  |   O  |  '   | 
|-----+------+------+------+------+------|     |------+------+------+------+------+------| 
| LSPO|   Z  |   X  |   C  |   V  |   B  |     |   K  |   M  |   ,  |  \.  |   /  | RSPC | 
|-----+------+------+------+------+------|     |------+------+------+------+------+------| 
| Ctrl| LGUI | LAlt | Lower| Space/Lower |     | Enter/Raise |  Fn  | Mouse| Menu | Ctrl | 
'----------------------------------------'     '-----------------------------------------' 
```

### Base Layer - Colemak
The base layout is Colemak by default. Since the CapsLock key is replaced with BackSpace, this layout has the delete key in the traditional backspace location. 

* QWERTY and Dvorak layers are accessible via the Adjust layer using the standard case switch macro as defined in the default Planck keymap.
* I've implemented COLEMAK = SAFE\_RANGE when enumerating the custom\_keycodes, but I don't actually know what this does...
* Space cadet is implemented in the shift keys (hold for shift, tap for respective parentheses)
* I never find myself using the right-modifiers on a standard keyboard, so I've only implemented LGUI and LALT. I have intentions of improving my use of the ctrl key in correct hand alternation, so CTRL is implemented in both outside corners of the home row.

### Alternate Base Layers - QWERTY & Dvorak
```
QWERTY
 .----------------------------------------.     .-----------------------------------------.
 | Esc |   1  |   2  |   3  |   4  |   5  |     |   6  |   7  |   8  |   9  |   0  | Del  |
 |-----+------+------+------+------+------|     |------+------+------+------+------+------|
 | Tab |   Q  |   W  |   E  |   R  |   T  |     |   Y  |   U  |   I  |   O  |   P  |  \   |
 |-----+------+------+------+------+------|     |------+------+------+------+------+------|
 | BS  |   A  |   S  |   D  |   F  |   G  |     |   H  |   J  |   K  |   L  |   ;  |  "   |
 |-----+------+------+------+------+------|     |------+------+------+------+------+------|
 | LSPO|   Z  |   X  |   C  |   V  |   B  |     |   N  |   M  |   ,  |   .  |   /  | RSPC |
 |-----+------+------+------+------+------|     |------+------+------+------+------+------|
 | Ctrl| LGUI | Lower| LAlt |    SpaceLW  |     |    RSEnter  |  Fn  | Mouse| Menu | Ctrl |
 `----------------------------------------'     '-----------------------------------------'

DVORAK
 .----------------------------------------.     .-----------------------------------------.
 | Esc  |   1  |   2  |   3  |   4  |   5 |     |   6  |   7  |   8  |   9  |   0  | Del  |
 |------+------+------+------+------+-----|     |------+------+------+------+------+------|
 | Tab  |   "  |   ,  |   .  |   P  |   Y |     |   F  |   G  |   C  |   R  |   L  |  \   |
 |------+------+------+------+------+-----|     |------+------+------+------+------+------|
 |  BS  |   A  |   O  |   E  |   U  |   I |     |   D  |   H  |   T  |   N  |   S  |  /   |
 |------+------+------+------+------+-----|     |------+------+------+------+------+------|
 | LSPO |   ;  |   Q  |   J  |   K  |   X |     |   B  |   M  |   W  |   V  |   Z  | RSPC |
 |------+------+------+------+------+-----|     |------+------+------+------+------+------|
 | Ctrl | LGUI | Lower| LAlt |   SpaceLW  |     |   RSEnter   |  Fn  | Mouse| Menu | Ctrl |
 `----------------------------------------'     '-----------------------------------------'
```

#### Layer Shifting
* The 4th key on the bottom row of the left hand PCB is used to access the *LOWER* layer via Tap/Toggle
* The left 2U key is a **TAP_KEY** macro - Hold for momentary *LOWER* layer, Tap for Space.
* The right 2U key is a **TAP_KEY** macro - Hold for momentary *RAISE* layer, Tap for Enter
* The 2nd key on the bottom row of the right hand PCB is a **LAYER_MOMENTARY** for the *FUNCTION* layer
* The 3rd key on the bottom row of the right hand PCB is a **TAP_TOGGLE** macro for the *MOUSE* layer

The base layout is Colemak. Since the CapsLock key is replaced with BackSpace, this layout has the delete key in the traditional backspace location. 

* QWERTY and Dvorak layers have been removed from the keymap that was initially developed from the default Planck keymap.
* I've implemented COLEMAK = SAFE\_RANGE when enumerating the custom\_keycodes, but I don't actually know what this does...

* Space cadet is implemented in the shift keys (hold for shift, tap for respective parentheses)
* I never find myself using the right-modifiers on a standard keyboard, so I've only implemented LGUI and LALT. I have intentions of improving my use of the ctrl key in correct hand alternation, so CTRL is implemented in both outside corners of the home row.

### LOWER - Numpad & Navigation keys
```
 ,-----------------------------------------.    .-----------------------------------------. 
 |  Esc |      |      |      |      |      |    |   =  |   /  |   \* |  \-  |      | Del  | 
 |------+------+------+------+------+------|    |------+------+------+------+------+------| 
 |  Tab | PgUp | Home |  Up  |  End |      |    |   7  |   8  |   9  |  \+  |      |  \\  | 
 |------+------+------+------+------+------|    |------+------+------+------+------+------| 
 |  BS  | PgDn | Left | Down |Right |      |    |   4  |   5  |   6  | Enter|      |   '  | 
 |------+------+------+------+------+------|    |------+------+------+------+------+------| 
 | LSPO |   Z  |   X  |   C  |   V  |      |    |   1  |   2  |   3  | Enter|      | RSPC | 
 |------+------+------+------+-------------|    |-------------+------+------+------+------| 
 | Ctrl | LGUI | Alt  | LOWER| Space/Lower |    |      0      |  \.  |  Fn  |ADJUST| Ctrl | 
 `-----------------------------------------'    `-----------------------------------------' 
```
The *LOWER* layer contains a navigation cluster on the left hand and a numpad on the right. This layer is momentary when the left thumb-bar or LOWER key is held and toggled on/off when the LOWER key is tapped.

The Navigation cluster is offset to the right compared to the traditional **WASD** nav cluster. With this implementation, you don't need to move your hand from the home position when navigating. Page Up & Down keys are found on the far left of the cluster.

All unused (blank on the above keymap) keys are locked out using the XXXXXXX filler (KC_NO), all modifiers (edge |_| keys \[except 0, \. & Fn\] on the 
above keymap) and the ZXCV cluster are transparent (_______) to the Base layer.

The ADJUST layer can be accessed via the second from right key on the bottom row. This layer contains a keymap that is used to change the base layer.

[] TO DO!! - It would be nice to have a **TAP_DANCE_DOUBLE** implementation whereby a double tap of the right 2U key sends KC_PENT
* Couldn't get this to work in Rev1, produced an error in the Make process.
* When this is done, I can remove the clunky double Enter on the 4th column of the right hand PCB (numpad enter).

### RAISE - Symbol Layer
```
 ,-----------------------------------.     .-----------------------------------.
 | Esc |  1  |  2  |  3  |  4  |  5  |     |  6  |  7  |  8  |  9  |  0  | Del |
 |-----+-----+-----+-----+-----+-----|     |-----+-----+-----+-----+-----+-----|
 | Tab |  !  |  @  |  #  |  $  |  %  |     |  ^  |  &  |  *  |  -  |  +  |  \  |
 |-----+-----+-----+-----+-----+-----|     |-----+-----+-----+-----+-----+-----|
 | BS  |     |     |     |     |     |     |     |     |     |     |     |  '  |
 |-----+-----+-----+-----+-----------|     |-----+-----+-----+-----+-----+-----|
 | LSPO|  <- | %>% |  {  |  [  |  `  |     |  |  |  ]  |  }  |  .  |  ?  |RSPC |
 |-----+-----+-----+-----+-----+-----|     |-----+-----+-----+-----+-----+-----|
 | Ctrl|LGUI | Alt |     |Space/Lower|     |Enter/Raise|  Fn |Mouse| Menu| Ctrl|
 '-----------------------------------'     '-----------------------------------'
```
The *RAISE* layer contains the symbols. This layer is momentary when the right thumb bar is held.

* Standard symbols can be found on the row above home, in the traditional number row order as they occur on a standard keyboard.
* Shifted symbols can be found on the second-from bottom row, above the bars - these include brackets, braces, grave and pipe keys.
	* At this stage, you need to shift to get to the Tilde key. I'd like to remove the shift requirement as I've done with the "|" Pipe, but we'll see. 
	* Special operators for R (Pointer: <- and dplyr pipe: %>%) can be found next to the left shift key
* The bottom row of this layer is a replication of that of the Base layer, except that the **TAP_TOGGLE** *LOWER* key is blocked with **XXXXXXX**.

### FUNCTION - Function & Media keys
```
,-----------------------------------------.     .-----------------------------------------.
|  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |     |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
|------+------+------+------+------+------|     |------+------+------+------+------+------|
| Esc  | Mute | Vol- | Vol+ |      | 	  |     |      |      |      |      |      | Ins  |
|------+------+------+------+------+------|     |------+------+------+------+------+------|
| Caps | Stop | |<<  | >/|| |  >>| |      |     |      |      |      |      |      |PrtSc |
|------+------+------+------+------+------|     |------+------+------+------+------+------|
| LSOB |      |      |      |      |      |     |      |      |      |      |      |ScrLk |
|------+------+------+------+------+------|     |------+------+------+------+------+------|
| Ctrl | LGUI | Alt  |      | Space/Lower |     | Enter/Raise |  Fn  | Mouse|      |PsBrk |
'-----------------------------------------'     '-----------------------------------------'
```
The *FUNCTION* layer contains media keys as well as the F-row. This layer is momentary and requires Fn to be held.

* The media cluster is based on the nav cluster in the *LOWER* layer, with RW, PP & FF in the Left, Down & Right positions.
* Mute, and Vol +/- are next to each other in ascending (L->R) volume order, Stop is below Mute.
* Insert, Print Screen, Scroll Lock & Pause Break are all implemented on the far right column. I don't really use these keys so their position is not optimised.
* Caps lock is implemented on this layer, in the traditional position, in place of BackSpace on the Base layer.

### MOUSE - Mouse keys: The functionality of this layer is not as optimal as using a true mouse, generally slower but will work in a pinch.
```
 ,----------------------------------------.     .----------------------------------------. 
 |  Esc |      |      |      |      |     |     |     |      |      |      |      |  Del | 
 |------+------+------+------+------+-----|     |-----+------+------+------+------+------| 
 |  Tab | WhlU | WhlL | MsUp | WhlR |     |     |     |  M3  |  M4  |  M5  |      |      | 
 |------+------+------+------+------+-----|     |-----+------+------+------+------+------| 
 |      | WhlD | MsL  | MsDn | MsR  |     |     |     |LClick|RClick|      |      |      | 
 |------+------+------+------+------+-----|     |-----+------+------+------+------+------| 
 | LSPO |      |      |      |      |     |     |     |      |      |      |      | RSCB | 
 |------+------+------+------+------+-----|     |-----+------+------+------+------+------| 
 | Ctrl |      |      |      |Sensitivity |     | Sensitivity|      |MOUSE |      | Ctrl | 
 '----------------------------------------'     '----------------------------------------'
 ```
The *MOUSE* layer contains keys replicating functions found on the mouse. 

* The navigation cluster (Up, Down, Left, Right) is a replication of the Navigation cluster on the *LOWER* layer. The scroll keys are analagous to the Page Up & down keys.
* The primary click (right & left) buttons are on the right home row (index & middle fingers)
* Secondary click buttons are above the standard keys (M3/Wheel click, M4, M5) but I do not use this function.

### ADJUST - Keyboard Settings: Primarily used to change the base layer at this stage
```
,-----------------------------------------.     ,----------------------------------------.
|      |      |      |      |      |RESET |     |     |      |      |      |      |      |
|------+------+------+------+------+------|     |-----+------+------+------+------+------|
|      |      |      |      |      |      |     |     |TermOn|TermOf|      |      |  Del |
|------+------+------+------+------+------|     |-----+------+------+------+------+------|
|      |      |      |      |      |      |     |     |Qwerty|Colemk|Dvorak|      |      |
|------+------+------+------+------+------|     |-----+------+------+------+------+------|
|      |      |      |      |      |      |     |     |      |      |      |      |      |
|------+------+------+------+------+------|     |-----+------+------+------+------+------|
|      |      |/LOWER|      |             |     |            |      |      |/RAISE|      |
`-----------------------------------------'     `----------------------------------------'
```
