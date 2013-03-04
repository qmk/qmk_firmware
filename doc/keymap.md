Keymap framework - how to define your keymap
============================================
***NOTE: This is not final version, may be inconsistent with source code and changed occasionally for a while.***

## Keymap
**Keymap** is comprised of multiple layers of key layout, you can define **16** layers at most.
**Layer** is an array of **keycodes** to define **actions** on each physical keys.
respective layers can be validated simultaneously. Layers are indexed with 0 to 15 and higher layer has precedence.

    Keymap with 16 Layers               Layer: array of Keycodes
    ---------------------               ------------------------
          stack of layers               content of layer
           ____________ precedence               _______________________
          /           / | high                  / ESC / F1  / F2  / F3   ....
      15 /___________// |                      /-----/-----/-----/-----
      14 /___________// |                     / TAB /     /     /      ....
      13 /___________/_ |                    /-----/-----/-----/-----
       :  / : : : : : / |                   /LCtrl/     /     /      ....
       3 /___________// |               :  /  :     :     :     :
       2 /___________// |               2 `--------------------------
       1 /___________// |               1 `--------------------------
       0 /___________/  V low           0 `--------------------------
                            

### Keymap status
Keymap has its state in two parameters:
**`default_layer`** indicates a base keymap layer(0-15) which is always valid and to be referred, **`keymap_stat`** is 16bit variable which has current on/off status of layers on its each bit.

Keymap layer '0' is usually `default_layer` and which is the only valid layer and other layers is initially off after boot up firmware, though, you can configured them in `config.h`.
To change `default_layer` will be useful when you want to switch key layout completely, say you use Colmak instead of Qwerty.

    Initial state of Keymap         Change base layout              
    -----------------------         ------------------              
                                                                    
      15                              15                            
      14                              14                            
      13                              13                            
       :                               :                            
       3                               3   ____________             
       2   ____________                2  /           /             
       1  /           /             ,->1 /___________/              
    ,->0 /___________/              |  0                            
    |                               |                               
    `--- default_layer = 0          `--- default_layer = 1          
         keymap_stat   = 0x0001          keymap_stat   = 0x0002     
    

On the other hand, you shall change `keymap_state` to overlay base layer with some layers for feature such as navigation keys, function key(F1-F12), media keys or special actions.

    Overlay feature layer
    ---------------------      bit|status
           ____________        ---+------
      15  /           /        15 |   0
      14 /___________// -----> 14 |   1
      13 /___________/  -----> 13 |   1
       :                        : |   
       3   ____________         3 |   0
       2  /           /         2 |   0
    ,->1 /___________/  ----->  1 |   1
    |  0                        0 |   0
    |                                 |
    `--- default_layer = 1            |
         keymap_stat   = 0x6002 <-----'

    
### Layer Precedence and Transparency
Note that ***higher layer has higher priority on stack of layers***, namely firmware falls down from top layer to bottom to look up keycode. Once it spots keycode other than **`KC_TRNS`**(transparent) on a layer it stops searching and lower layers aren't referred.

You can place `KC_TRNS` on overlay layer changes just part of layout to fall back on lower or base layer.
Key with `KC_TRANS` doen't has its own keycode and refers to its lower layers for keycode, instead.
See layer 1 or 2 below for example.


### Keymap Example
Keymap is **`keymaps[]`** C array in fact and you can define layers in it with **`KEYMAP()`** C macro and keycodes. To use complex actions you need to define `Fn` keycode in **`fn_actions[]`** array.

This is a keymap example for [HHKB](http://en.wikipedia.org/wiki/Happy_Hacking_Keyboard) keyboard.
This example has three layers, 'Qwerty' as base layer, 'Cursor' and  'Mousekey'.
In this example,

 `Fn0` is a **momentary layer switching** key, you can use keys on Cursor layer while holding the key.

 `Fn1` is a momentary layer switching key with tapping feature, you can get semicolon **';'** with taping the key and switch layers while holding the key. The word **'tap'** or **'tapping'** mean to press and release a key quickly.

 `Fn2` is a **toggle layer switch** key, you can stay switched layer after releasing the key unlike momentary switching.

You can find other keymap definitions in file `keymap.c` located on project directories.

    static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        /* 0: Qwerty
         * ,-----------------------------------------------------------.
         * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  \|  `|
         * |-----------------------------------------------------------|
         * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|Backs|
         * |-----------------------------------------------------------|
         * |Contro|  A|  S|  D|  F|  G|  H|  J|  K|  L|Fn1|  '|Enter   |
         * |-----------------------------------------------------------|
         * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift |Fn0|
         * `-----------------------------------------------------------'
         *       |Gui|Alt  |Space                  |Alt  |Fn2|
         *       `-------------------------------------------'
         */
        KEYMAP(ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSLS,GRV, \
               TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSPC, \
               LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   FN1, QUOT,ENT, \
               LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,RSFT,FN0, \
                    LGUI,LALT,          SPC,                RALT,FN2),
        /* 1: Cursor(HHKB mode)
         * ,-----------------------------------------------------------.
         * |Pwr| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Ins|Del|
         * |-----------------------------------------------------------|
         * |Caps |   |   |   |   |   |   |   |Psc|Slk|Pus|Up |   |Backs|
         * |-----------------------------------------------------------|
         * |Contro|VoD|VoU|Mut|   |   |  *|  /|Hom|PgU|Lef|Rig|Enter   |
         * |-----------------------------------------------------------|
         * |Shift   |   |   |   |   |   |  +|  -|End|PgD|Dow|Shift |   |
         * `-----------------------------------------------------------'
         *      |Gui |Alt  |Space                  |Alt  |Gui|
         *      `--------------------------------------------'
         */ 
        KEYMAP(PWR, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, INS, DEL, \
               CAPS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,PSCR,SLCK,PAUS,UP,  TRNS,BSPC, \
               LCTL,VOLD,VOLU,MUTE,TRNS,TRNS,PAST,PSLS,HOME,PGUP,LEFT,RGHT,ENT, \
               LSFT,TRNS,TRNS,TRNS,TRNS,TRNS,PPLS,PMNS,END, PGDN,DOWN,RSFT,TRNS, \
                    LGUI,LALT,          SPC,                RALT,RGUI),
        /* 2: Mousekey
         * ,-----------------------------------------------------------.
         * |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Ins|Del|
         * |-----------------------------------------------------------|
         * |Tab  |   |   |   |   |   |MwL|MwD|MwU|MwR|   |   |   |Backs|
         * |-----------------------------------------------------------|
         * |Contro|   |   |   |   |   |McL|McD|McU|McR|   |   |Return  |
         * |-----------------------------------------------------------|
         * |Shift   |   |   |   |   |Mb3|Mb2|Mb1|Mb4|Mb5|   |Shift |   |
         * `-----------------------------------------------------------'
         *      |Gui |Alt  |Mb1                    |Alt  |   |
         *      `--------------------------------------------'
         * Mc: Mouse Cursor / Mb: Mouse Button / Mw: Mouse Wheel 
         */
        KEYMAP(ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, INS, DEL, \
               TAB, TRNS,TRNS,TRNS,TRNS,TRNS,WH_L,WH_D,WH_U,WH_R,TRNS,TRNS,TRNS,BSPC, \
               LCTL,TRNS,ACL0,ACL1,ACL2,TRNS,MS_L,MS_D,MS_U,MS_R,TRNS,QUOT,ENT, \
               LSFT,TRNS,TRNS,TRNS,TRNS,BTN3,BTN2,BTN1,BTN4,BTN5,SLSH,RSFT,TRNS, \
                    LGUI,LALT,          BTN1,               RALT,TRNS),
    };

    static const uint16_t PROGMEM fn_actions[] = {
        ACTION_KEYMAP(1),                            // FN0
        ACTION_KEYMAP_TAP_KEY(2, KC_SCLN),           // FN1
        ACTION_KEYMAP_TOGGLE(2),                     // FN2
    };




## 1. Keycode
See [`common/keycode.h`](common/keycode.h) or keycode table below. Keycode is internal **8bit code** to inidicate action performed on key in keymap. Keycode has `KC_` prefixed symbol respectively. Most of keycodes like `KC_A` have simple action registers key to host on press and unregister on release, while some of other keycodes has some special actions like `Fn` keys, Media contorl keys, System control keys and Mousekeys.

 ***In `KEYMAP()` macro you should omit prefix part `KC_` of keycode to keep keymap compact.*** For example, just use `A` instead you place `KC_A` in `KEYMAP()`. Some keycodes has 4-letter **short name** in addition to descriptive name, you'll prefer short one in `KEYMAP()`.

### 1.0 Other key
- `KC_NO` for no aciton
- `KC_TRNS` for layer transparency (See above)

### 1.1 Normal key
- `KC_A` to `KC_Z`, `KC_1` to `KC_0` for alpha numeric key
- `KC_MINS`, `KC_EQL`, `KC_GRV`, `KC_RBRC`, `KC_LBRC`, `KC_COMM`, `KC_DOT`, `KC_BSLS`, `KC_SLSH`, `KC_SCLN`, `KC_QUOT`
- `KC_ESC`, `KC_TAB`, `KC_SPC`, `KC_BSPC`, `KC_ENT`, `KC_DEL`, `KC_INS`
- `KC_UP`, `KC_DOWN`, `KC_RGHT`, `KC_LEFT`, `KC_PGUP`, `KC_PGDN`, `KC_HOME`, `KC_END`
- `KC_CAPS`, `KC_NLCK`, `KC_SLCK`, `KC_PSCR`, `KC_PAUS`, `KC_APP`, `KC_F1` to `KC_F24`
- `KC_P1` to `KC_P0`, `KC_PDOT`, `KC_PCMM`, `KC_PSLS`, `KC_PAST`, `KC_PMNS`, `KC_PPLS`, `KC_PEQL`, `KC_PENT` for keypad.

### 1.2 Modifier
There are 8 modifiers which has discrimination between left and right. 

- `KC_LCTL` and `KC_RCTL` for Control
- `KC_LSFT` and `KC_RSFT` for Shift
- `KC_LALT` and `KC_RALT` for Alt
- `KC_LGUI` and `KC_RGUI` for Windows key or Command key in Mac

### 1.3 Mousekey
- `KC_MS_U`, `KC_MS_D`, `KC_MS_L`, `KC_MS_R` for mouse cursor
- `KC_WH_U`, `KC_WH_D`, `KC_WH_L`, `KC_WH_R` for mouse wheel
- `KC_BTN1`, `KC_BTN2`, `KC_BTN3`, `KC_BTN4`, `KC_BTN5` for mouse buttons

### 1.4 System & Media key
- `KC_PWR`, `KC_SLEP`, `KC_WAKE` for Power, Sleep, Wake
- `KC_MUTE`, `KC_VOLU`, `KC_VOLD` for audio volume control
- `KC_MNXT`, `KC_MPRV`, `KC_MSTP`, `KC_MPLY`, `KC_MSEL` for media control
- `KC_MAIL`, `KC_CALC`, `KC_MYCM` for application launch
- `KC_WSCH`, `KC_WHOM`, `KC_WBAK`, `KC_WFWD`, `KC_WSTP`, `KC_WREF`, `KC_WFAV` for web browser operation

### 1.5 Fn key
`KC_FNnn` are keycodes for `Fn` key which not given any actions at the beginning unlike most of keycodes has its own inborn action. To use these keycodes in `KEYMAP` you need to assign action you want at first. Action of `Fn` key is defined in `fn_actions[]` and its index of the array is identical with number part of `KC_FNnn`. Thus `KC_FN0` keyocde indicates the action defined in first element of the array. ***32 `Fn` keys can be defined at most.***

### 1.6 Keycode Table
 See keycode table in [`doc/keycode.txt`](doc/keycode.txt) for description of keycodes.

 In regard to implementation side most of keycodes are identical with [HID usage][HID_usage](pdf) sent to host for real and some virtual keycodes are defined to support special actions.
[HID_usage]: http://www.usb.org/developers/devclass_docs/Hut1_11.pdf



## 2. Action
See [`common/action.h`](common/action.h). Action is a **16bit code** and defines function to perform on events of a key like press, release, holding and tapping.

Most of keys just register 8bit scancode to host, but to support other complex features needs 16bit extended action codes internally. However, using 16bit action codes in keymap results in double size in memory against using jsut keycodes. To avoid this waste 8bit keycodes are used in `KEYMAP` instead of action codes.

***You can just use keycodes of `Normal key`, `Modifier`, `Mousekey` and `System & Media key` in keymap*** to indicate corresponding actions instead of using action codes. While ***to use other special actions you should use keycode of `Fn` key defined in `fn_actions[]`.***

Usually action codes are needed only when you want to use layer switching, or 

### 2.1 Key action
This is a simple action that registers scancodes(HID usage in fact) to host on press event of key and unregister on release.

#### 2.1.1 Normal key and Modifier
This action usually won't be used expressly because you can use keycodes in `KEYMAP()` instead.
You can define `Key` action on *'A'* key and *'left shift'* modifier with:

    ACTION_KEY(KC_A)
    ACTION_KEY(KC_LSHIFT)

#### 2.1.2 Key with modifiers
This action is comprised of strokes of modifiers and a key. `Macro` action is needed if you want more complex key strokes.
Say you want to assign a key to `Shift + 1` to get charactor *'!'* or `Alt + Tab` to switch application windows.

    ACTION_LMOD_KEY(KC_LSHIFT, KC_1)
    ACTION_LMOD_KEY(KC_LALT, KC_TAB)

Or `Alt,Shift + Tab` can be defined. `ACTION_LMODS_KEY()` requires **4-bit modifier state** and a **keycode** as arguments. See `keycode.h` for `MOD_BIT()` macro.

    ACTION_LMODS_KEY((MOD_BIT(KC_LALT) | MOD_BIT(KC_LSHIFT)), KC_TAB)



### 2.2 Layer Actions

#### 2.2.0 Default Layer
`default_layer` is layer which always is on and refered to when actions is not defined on other layers.

##### Return to Default Layer
Turns on `default layer` only with clearing other all layers.

    ACTION_DEFAULT_LAYER

##### Set Default Layer
Sets 'default layer' to layer and turn it on without clear any other layers.

    ACTION_DEFAULT_LAYER_SET(layer)

This does it on { press | release | both }.

    ACTION_DEFAULT_LAYER_SET(layer, on)


#### 2.2.1 Keymap
These actions operate given layer argument which ranges from 0 to 15.

##### Switch to layer
Turns on layer momentary while holding, in other words turn on when key is pressed and off when released.

    ACTION_KEYMAP_MOMENTARY(layer)


##### Toggle layer
Turns on layer on first type and turns off on next.

    ACTION_KEYMAP_TOGGLE(layer)


##### Switch to layer with tap key
Turns on layer momentary while holding but registers key on tap.

    ACTION_KEYMAP_TAP_KEY(layer, key)


##### Switch to layer with tap toggle
Turns on layer momentary while holding but toggles it with serial taps.

    ACTION_KEYMAP_TAP_TOGGLE(layer)


##### Invert layer
Inverts current layer state. If the layer is on it becomes off with this action.

    ACTION_KEYMAP_INV(layer, on)


##### Turn On layer
Turns on layer state.

    ACTION_KEYMAP_ON(layer, on)

Turns on layer state on press and turn off on release. This is identical to **'Switch to layer'** action.

    ACTION_KEYMAP_ON_OFF(layer)


##### Turn Off layer
Turns off layer state.

    ACTION_KEYMAP_OFF(layer, on)


##### Set layer
Turn on layer only.
`keymap_stat = (1<<layer) [layer: 0-15]`

    ACTION_KEYMAP_SET(layer, on)

Turns on layer only and clear all layer on release..

    ACTION_KEYMAP_SET_CLEAR(layer)


#### 2.2.2 Overlay
***TBD***

In addition to actions of `Keymap` above these actions are also available.

##### Invert 4bit layer states
Invert 4bits out of 16bits of overlay status on both press and release.
`overlay_stat = (overlay_stat ^ bits<<(shift*4)) [bits: 0-15, shift: 0-3]`

    ACTION_OVERLAY_INV4(bits, shift)


### 2.3 Macro action
***TBD***

`Macro` action indicates complex key strokes.
 
    MACRO( MD(LSHIFT), D(D), END )
    MACRO( U(D), MU(LSHIFT), END )
    MACRO( I(255), T(H), T(E), T(L), T(L), W(255), T(O), END )

#### 2.3.1 Normal mode
- **I()**   change interavl of stroke.
- **D()**   press key
- **U()**   release key
- **T()**   type key(press and release)
- **W()**   wait
- **MD()**  modifier down
- **MU()**  modifier up
- **END**   end mark

#### 2.3.2 Extended mode

***TODO: sample impl***
See `keyboard/hhkb/keymap.c` for sample.


### 2.4 Function action
***TBD***

There are two type of action, normal `Function` and tappable `Function`.
These actions call user defined function with `id`, `opt`, and key event information as arguments.

#### 2.4.1 Function
To define normal `Function` action in keymap use this.

    ACTION_FUNCTION(id, opt)

#### 2.4.2 Function with tap
To define tappable `Function` action in keymap use this.

    ACTION_FUNCTION_TAP(id, opt)

#### 2.4.3 Implement user function
`Function` actions can be defined freely with C by user in callback function:

    void keymap_call_function(keyrecord_t *event, uint8_t id, uint8_t opt)

This C function is called every time key is operated, argument `id` selects action to be performed and `opt` can be used for option. Functon `id` can be 0-255 and `opt` can be 0-15.

 `keyrecord_t` is comprised of key event and tap count. `keyevent_t` indicates which and when key is pressed or released. From `tap_count` you can know tap state, 0 means no tap. These information will be used in user function to decide how action of key is performed.

    typedef struct {
        keyevent_t  event;
        uint8_t     tap_count;
    } keyrecord_t;

    typedef struct {
        key_t    key;
        bool     pressed;
        uint16_t time;
    } keyevent_t;

    typedef struct {
        uint8_t col;
        uint8_t row;
    } key_t;

***TODO: sample impl***
See `keyboard/hhkb/keymap.c` for sample.





## 3. Layer
 Layer is key-action map to assign action to every physical key. You can define multiple layers in keymap and make layers active out of keymap during operation at will.

 First layer is indexed by `0` which usually become `default layer` and active in initial state.

You can define **16 layers** at most in each keymaps and overlays.

            ____________
           /           /
          /           //
      15 /___________///
      14 /___________//_
      13 /___________/ /
          /: : : : :  //
       3 /___________///
       2 /___________///
       1 /___________//
    .->0 /___________/ 
    `--- default_layer = 0

 you can define a layer with placing keycode symbols separated with `comma` in `KEYMAP`, which is formed with resemblance to physical keyboard layout so as you can easily put keycode on place you want to map. ***You can define most of keys with just using keycodes*** except for `Fn` key serving special actions.

### 3.0 Transparency
With KC_TRNS you can define transparent key which itself doesn't have action but refer to lower valid layer. Transparent key is useful when you want to change part of layout not over all.



## 4. Layer switching
You can have some ways to switch layer with these actions.
There are two kind of layer switch action `Layer Set` and `Layer Bit` and two type of switching behaviour **Momentary** and **Toggle**.

### 4.1 Momentary switching
Momentary switching changes layer only while holding Fn key.

#### 4.1.1 Momentary Set
This action makes `Layer 1` active on key press event and inactive on release event..

    ACTION_KEYMAP_MOMENTARY(1)


It switches to destination layer immediately when key is pressed, after that actions on keymap of destination layer is perfomed. ***Thus you shall need to place action to come back on destination layer***, or you will be stuck in destination layer without way to get back. To get back to `default layer` you can use this action.

    ACTION_LAYER_DEFAULT

#### 4.1.2 Momentary Bit
This `Layer Bit` action performs XOR `1` with `current layer` on both press and release event. If you are on `Layer 0` now next layer to switch will be `Layer 1`. To come back to previous layer you need to place same action on destination layer.

    ACTION_LAYER_BIT(1)

### 4.2 Toggle switching
Toggle switching changes layer after press then release. You keep being on the layer until you press key to return.

#### 4.2.1 Toggle Set
This `Layer Set Toggle` action is to set `Layer 1` to `current layer` on release and do none on press.

    ACTION_LAYER_SET_TOGGLE(1)

To get back to `default layer` you can use this action.

    ACTION_LAYER_DEFAULT

#### 4.2.2 Toggle Bit
This `Layer Bit Toggle` action is to XOR `1` with `current layer` on release and do none on press. If you are on `Layer 2` you'll switch to `Layer 3` on press. To come back to previous layer you need to place same action on destination layer.

    ACTION_LAYER_BIT_TOGGLE(1)


### 4.3 Momentary switching with Tap key
These actions switch to layer only while holding `Fn` key and register key on tap. **Tap** means to press and release key quickly.

    ACTION_LAYER_SET_TAP_KEY(2, KC_SCLN)
    ACTION_LAYER_SET_BIT_KEY(2, KC_SCLN)

With these you can place layer switching function on normal alphabet key like `;` without losing its original register function.

### 4.4 Momentary switching with Tap Toggle
This changes layer only while holding `Fn` key and toggle layer after several taps. **Tap** means to press and release key quickly.

    ACTION_LAYER_SET_TAP_TOGGLE(layer)
    ACTION_LAYER_BIT_TAP_TOGGLE(layer)

Number of taps can be defined with `TAPPING_TOGGLE` in `config.h`, `5` by default.


## Tapping
### Tap Key
### One Shot Modifier


## Legacy Keymap
This was used in prior version and still works due to legacy support code in `common/keymap.c`. Legacy keymap doesn't support many of features that new keymap offers.

In comparison with new keymap how to define Fn key is different. It uses two arrays `fn_layer[]` and `fn_keycode[]`. The index of arrays corresponds with postfix number of `Fn` key. Array `fn_layer[]` indicates destination layer to switch and `fn_keycode[]` has keycodes to send when tapping `Fn` key.

In following setting example, `Fn0`, `Fn1` and `Fn2` switch layer to 1, 2 and 2 respectively. `Fn2` registers `Space` key when tap while `Fn0` and `Fn1` doesn't send any key.

    static const uint8_t PROGMEM fn_layer[] = {
        1,              // Fn0
        2,              // Fn1
        2,              // Fn2
    };

    static const uint8_t PROGMEM fn_keycode[] = {
        KC_NO,          // Fn0
        KC_NO,          // Fn1
        KC_SPC,         // Fn2
    };


## Terminology
- keymap
- layer
- layout
- key
- keycode
- scancode
- action
- layer transparency
- layer precedence
- register
- tap
- Fn key
