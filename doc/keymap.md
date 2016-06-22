Keymap framework - how to define your keymap
============================================
***NOTE: This is not final version, may be inconsistent with source code and changed occasionally for a while.***

## 0. Keymap and layers
**Keymap** is comprised of multiple layers of key layout, you can define **32 layers** at most.
**Layer** is an array of **keycodes** to define **actions** for each physical keys.
respective layers can be validated simultaneously. Layers are indexed with 0 to 31 and higher layer has precedence.

    Keymap: 32 Layers                   Layer: Keycode matrix
    -----------------                   ---------------------
    stack of layers                     array_of_keycode[row][column]
           ____________ precedence               _______________________
          /           / | high                  / ESC / F1  / F2  / F3   ....
      31 /___________// |                      /-----/-----/-----/-----
      30 /___________// |                     / TAB /  Q  /  W  /  E   ....
      29 /___________/  |                    /-----/-----/-----/-----
       :   _:_:_:_:_:__ |               :   /LCtrl/  A  /  S  /  D   ....
       :  / : : : : : / |               :  /  :     :     :     :
       2 /___________// |               2 `--------------------------
       1 /___________// |               1 `--------------------------
       0 /___________/  V low           0 `--------------------------



### 0.1 Keymap status
Keymap has its state in two parameters:
**`default_layer`** indicates a base keymap layer(0-31) which is always valid and to be referred, **`keymap_stat`** is 16bit variable which has current on/off status of layers on its each bit.

Keymap layer '0' is usually `default_layer` and which is the only valid layer and other layers is initially off after boot up firmware, though, you can configured them in `config.h`.
To change `default_layer` will be useful when you switch key layout completely, say you want Colmak instead of Qwerty.

    Initial state of Keymap          Change base layout              
    -----------------------          ------------------              

      31                               31
      30                               30
      29                               29
       :                                :
       :                                :   ____________
       2   ____________                 2  /           /
       1  /           /              ,->1 /___________/
    ,->0 /___________/               |  0
    |                                |
    `--- default_layer = 0           `--- default_layer = 1
         layer_state   = 0x00000001       layer_state   = 0x00000002

On the other hand, you shall change `layer_state` to overlay base layer with some layers for feature such as navigation keys, function key(F1-F12), media keys or special actions.

    Overlay feature layer
    ---------------------      bit|status
           ____________        ---+------
      31  /           /        31 |   0
      30 /___________// -----> 30 |   1
      29 /___________/  -----> 29 |   1
       :                        : |   :
       :   ____________         : |   :
       2  /           /         2 |   0
    ,->1 /___________/  ----->  1 |   1
    |  0                        0 |   0
    |                                 +
    `--- default_layer = 1            |
         layer_state   = 0x60000002 <-'



### 0.2 Layer Precedence and Transparency
Note that ***higher layer has higher priority on stack of layers***, namely firmware falls down from top layer to bottom to look up keycode. Once it spots keycode other than **`KC_TRNS`**(transparent) on a layer it stops searching and lower layers aren't referred.

You can place `KC_TRNS` on overlay layer changes just part of layout to fall back on lower or base layer.
Key with `KC_TRANS` doesn't has its own keycode and refers to lower valid layers for keycode, instead.
See example below.


### 0.3 Keymap Example
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
        ACTION_LAYER_MOMENTARY(1),                  // FN0
        ACTION_LAYER_TAP_KEY(2, KC_SCLN),           // FN1
        ACTION_LAYER_TOGGLE(2),                     // FN2
    };




## 1. Keycode
See [`common/keycode.h`](../common/keycode.h) or keycode table below for the detail. Keycode is internal **8bit code** to indicate action performed on key in keymap. Keycode has `KC_` prefixed symbol respectively. Most of keycodes like `KC_A` have simple action registers key to host on press and unregister on release, while some of other keycodes has some special actions like `Fn` keys, Media control keys, System control keys and Mousekeys.

 ***In `KEYMAP()` macro you should omit prefix part `KC_` of keycode to keep keymap compact.*** For example, just use `A` instead you place `KC_A` in `KEYMAP()`. Some keycodes has 4-letter **short name** in addition to descriptive name, you'll prefer short one in `KEYMAP()`.

### 1.0 Other key
- `KC_NO` for no action
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
`KC_FNnn` are keycodes for `Fn` key which not given any actions at the beginning unlike most of keycodes has its own inborn action. To use these keycodes in `KEYMAP()` you need to assign action you want at first. Action of `Fn` key is defined in `fn_actions[]` and its index of the array is identical with number part of `KC_FNnn`. Thus `KC_FN0` keycode indicates the action defined in first element of the array. ***32 `Fn` keys can be defined at most.***

### 1.6 Keycode Table
 See keycode table in [`doc/keycode.txt`](./keycode.txt) for description of keycodes.

 In regard to implementation side most of keycodes are identical with [HID usage][HID_usage](pdf) sent to host for real and some virtual keycodes are defined to support special actions.
[HID_usage]: http://www.usb.org/developers/hidpage/Hut1_12v2.pdf



## 2. Action
See [`common/action_code.h`](../common/action_code.h). Action is a **16bit code** and defines function to perform on events of a key like press, release, holding and tapping.

Most of keys just register 8bit scancode to host, but to support other complex features needs 16bit extended action codes internally. However, using 16bit action codes in keymap results in double size in memory compared to using just keycodes. To avoid this waste 8bit keycodes are used in `KEYMAP()` instead of action codes.

***You can just use keycodes of `Normal key`, `Modifier`, `Mousekey` and `System & Media key` in keymap*** to indicate corresponding actions instead of using action codes. While ***to use other special actions you should use keycode of `Fn` key defined in `fn_actions[]`.***


### 2.1 Key Action
This is a simple action that registers scancodes(HID usage in fact) to host on press event of key and unregister on release.

#### Parameters
+ **mods**: { ` MOD_LCTL`, ` MOD_LSFT`, ` MOD_LALT`, ` MOD_LGUI`,
              ` MOD_RCTL`, ` MOD_RSFT`, ` MOD_RALT`, ` MOD_RGUI` }
+ **key**: keycode


#### 2.1.1 Normal key and Modifier
***This action usually won't be used expressly in keymap*** because you can just use keycodes in `KEYMAP()` instead.

You can define these actions on *'A'* key and *'left shift'* modifier with:

    ACTION_KEY(KC_A)
    ACTION_KEY(KC_LSFT)

#### 2.1.2 Modified key
This action is comprised of strokes of modifiers and a key. `Macro` action is needed if you want more complex key strokes.

Say you want to assign a key to `Shift + 1` to get character *'!'* or `Alt + Tab` to switch application windows.

    ACTION_MODS_KEY(MOD_LSFT, KC_1)
    ACTION_MODS_KEY(MOD_LALT, KC_TAB)

Or `Alt,Shift + Tab` can be defined. `ACTION_MODS_KEY(mods, key)` requires **4-bit modifier state** and a **keycode** as arguments. See `keycode.h` for `MOD_BIT()` macro.

    ACTION_MODS_KEY(MOD_LALT | MOD_LSFT, KC_TAB)

#### 2.1.3 Multiple Modifiers
Registers multiple modifiers with pressing a key. To specify multiple modifiers use `|`.

    ACTION_MODS(MOD_ALT | MOD_LSFT)

#### 2.1.3 Modifier with Tap key([Dual role][dual_role])
Works as a modifier key while holding, but registers a key on tap(press and release quickly).


    ACTION_MODS_TAP_KEY(MOD_RCTL, KC_ENT)



### 2.2 Layer Action
These actions operate layers of keymap.

#### Parameters
You can specify a **target layer** of action and **when the action is executed**. Some actions take a **bit value** for bitwise operation.


+ **layer**: `0`-`31`
+ **on**: { `ON_PRESS` | `ON_RELEASE` | `ON_BOTH` }
+ **bits**: 4-bit value and 1-bit mask bit


#### 2.2.1 Default Layer
Default Layer is a layer which always is valid and referred to when actions is not defined on other overlay layers.

This sets Default Layer to given parameter `layer` and activate it.

    ACTION_DEFAULT_LAYER_SET(layer)


#### 2.2.2 Momentary 
Turns on `layer` momentarily while holding, in other words it activates when key is pressed and deactivate when released.

    ACTION_LAYER_MOMENTARY(layer)


#### 2.2.3 Toggle Switch
Turns on `layer` with first type(press and release) and turns off with next.

    ACTION_LAYER_TOGGLE(layer)


#### 2.2.4 Momentary Switch with tap key
Turns on `layer` momentary while holding, but registers key on tap(press and release quickly).

    ACTION_LAYER_TAP_KEY(layer, key)


#### 2.2.5 Momentary Switch with tap toggle
Turns on `layer` momentary while holding and toggles it with serial taps.

    ACTION_LAYER_TAP_TOGGLE(layer)


#### 2.2.6 Invert state of layer
Inverts current state of `layer`. If the layer is on it becomes off with this action.

    ACTION_LAYER_INVERT(layer, on)


#### 2.2.7 Turn On layer
Turns on layer state.

    ACTION_LAYER_ON(layer, on)

Turns on layer state on press and turns off on release.

    ACTION_LAYER_ON_OFF(layer)


#### 2.2.8 Turn Off layer
Turns off layer state.

    ACTION_LAYER_OFF(layer, on)

Turns off layer state on press and activates on release.

    ACTION_LAYER_OFF_ON(layer)


#### 2.2.9 Set layer
Turn on layer only.
`layer_state = (1<<layer) [layer: 0-31]`

    ACTION_LAYER_SET(layer, on)

Turns on layer only and clear all layer on release..

    ACTION_LAYER_SET_CLEAR(layer)


#### 2.2.10 Bitwise operation

**part** indicates which part of 32bit layer state(0-7). **bits** is 5-bit value. **on** indicates when the action is executed.

    ACTION_LAYER_BIT_AND(part, bits, on)
    ACTION_LAYER_BIT_OR(part, bits, on)
    ACTION_LAYER_BIT_XOR(part, bits, on)
    ACTION_LAYER_BIT_SET(part, bits, on)

These actions works with parameters as following code.

    uint8_t shift = part*4;
    uint32_t mask = (bits&0x10) ? ~(0xf<<shift) : 0;
    uint32_t layer_state = layer_state <bitop> ((bits<<shift)|mask);


Default Layer also has bitwise operations, they are executed when key is released.

    ACTION_DEFAULT_LAYER_BIT_AND(part, bits)
    ACTION_DEFAULT_LAYER_BIT_OR(part, bits)
    ACTION_DEFAULT_LAYER_BIT_XOR(part, bits)
    ACTION_DEFAULT_LAYER_BIT_SET(part, bits)



### 2.3 Macro action
***TBD***

`Macro` action indicates complex key strokes.
 
    MACRO( D(LSHIFT), D(D), END )
    MACRO( U(D), U(LSHIFT), END )
    MACRO( I(255), T(H), T(E), T(L), T(L), W(255), T(O), END )

#### 2.3.1 Macro Commands
- **I()**   change interval of stroke.
- **D()**   press key
- **U()**   release key
- **T()**   type key(press and release)
- **W()**   wait
- **END**   end mark

#### 2.3.2 Examples

***TODO: sample implementation***
See `keyboards/hhkb/keymap.c` for sample.



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

This C function is called every time key is operated, argument `id` selects action to be performed and `opt` can be used for option. Function `id` can be 0-255 and `opt` can be 0-15.

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

***TODO: sample implementation***
See `keyboards/hhkb/keymap.c` for sample.



### 2.5 Backlight Action
These actions control the backlight.

#### 2.5.1 Change backlight level
Increase backlight level.

    ACTION_BACKLIGHT_INCREASE()

Decrease backlight level.

    ACTION_BACKLIGHT_DECREASE()

Step through backlight levels.

    ACTION_BACKLIGHT_STEP()

Turn a specific backlight level on or off.

    ACTION_BACKLIGHT_LEVEL(1)

#### 2.5.2 Turn on / off backlight
Turn the backlight on and off without changing level.

    ACTION_BACKLIGHT_TOGGLE()



## 3. Layer switching Example
There are some ways to switch layer with 'Layer' actions.

### 3.1 Momentary switching
Momentary switching changes layer only while holding Fn key.

This action makes 'Layer 1' active(valid) on key press event and inactive on release event. Namely you can overlay a layer on lower layers or default layer temporarily with this action.

    ACTION_LAYER_MOMENTARY(1)


Note that after switching on press the actions on destination layer(Layer 1) are performed.
***Thus you shall need to place an action to go back on destination layer***, or you will be stuck in destination layer without way to get back. Usually you need to place same action or 'KC_TRNS` on destination layer to get back.


### 3.2 Toggle switching
Toggle switching performed after releasing a key. With this action you can keep staying on the destination layer until you type the key again to return.

This performs toggle switching action of 'Layer 2'.

    ACTION_LAYER_TOGGLE(2)



### 3.3 Momentary switching with Tap key
These actions switch a layer only while holding a key but register the key on tap. **Tap** means to press and release a key quickly.

    ACTION_LAYER_TAP_KEY(2, KC_SCLN)

With this you can place a layer switching action on normal key like ';' without losing its original key register function. This action allows you to have layer switching action without necessity of a dedicated key. It means you can have it even on home row of keyboard.



### 3.4 Momentary switching with Tap Toggle
This switches layer only while holding a key but toggle layer with several taps. **Tap** means to press and release key quickly.

    ACTION_LAYER_TAP_TOGGLE(1)

Number of taps can be configured with `TAPPING_TOGGLE` in `config.h`, `5` by default.



### 3.5 Momentary switching with Modifiers
This registers modifier key(s) simultaneously with layer switching.

    ACTION_LAYER_MODS(2, MOD_LSFT | MOD_LALT)



## 4. Tapping
Tapping is to press and release a key quickly. Tapping speed is determined with setting of `TAPPING_TERM`, which can be defined in `config.h`, 200ms by default.

### 4.1 Tap Key
This is a feature to assign normal key action and modifier including layer switching to just same one physical key. This is a kind of [Dual role key][dual_role]. It works as modifier when holding the key but registers normal key when tapping.

Modifier with tap key:

    ACTION_MODS_TAP_KEY(MOD_RSFT, KC_GRV)

Layer switching with tap key:

    ACTION_LAYER_TAP_KEY(2, KC_SCLN)

[dual_role]: http://en.wikipedia.org/wiki/Modifier_key#Dual-role_keys


### 4.2 Tap Toggle
This is a feature to assign both toggle layer and momentary switch layer action to just same one physical key. It works as momentary layer switch when holding a key but toggle switch with several taps.

    ACTION_LAYER_TAP_TOGGLE(1)


### 4.3 Oneshot Modifier
This runs onetime effects which modify only on just one following key. It works as normal modifier key when holding down while oneshot modifier when tapping. The behavior of oneshot modifiers is similar to the [sticky keys](https://en.wikipedia.org/wiki/StickyKeys) functionality found in most operating systems.

    ACTION_MODS_ONESHOT(MOD_LSFT)

Oneshot layer key:

    ACTION_LAYER_ONESHOT(MY_LAYER)

Say you want to type 'The', you have to push and hold Shift key before type 't' then release it before type 'h' and 'e', otherwise you'll get 'THe' or 'the' unintentionally. With Oneshot Modifier you can tap Shift then type 't', 'h' and 'e' normally, you don't need to holding Shift key properly here. This mean you can release Shift before 't' is pressed down.

Oneshot effect is cancel unless following key is pressed down within `ONESHOT_TIMEOUT` of `config.h`. No timeout when it is `0` or not defined.

Most implementations of sticky keys allow you to lock a modifier by double tapping the modifier. The layer then remains locked untill the modifier is tapped again. To enable this behaviour for oneshot modifiers set `ONESHOT_TAP_TOGGLE` to the number taps required. The feature is disabled if `ONESHOT_TAP_TOGGLE<2` or not defined.


### 4.4 Tap Toggle Mods
Similar to layer tap toggle, this works as a momentary modifier when holding, but toggles on with several taps. A single tap will 'unstick' the modifier again.

    ACTION_MODS_TAP_TOGGLE(MOD_LSFT)




## 5. Legacy Keymap
This was used in prior version and still works due to legacy support code in `common/keymap.c`. Legacy keymap doesn't support many of features that new keymap offers. ***It is not recommended to use Legacy Keymap for new project.***

To enable Legacy Keymap support define this macro in `config.h`.

    #define USE_LEGACY_KEYMAP

Legacy Keymap uses two arrays `fn_layer[]` and `fn_keycode[]` to define Fn key. The index of arrays corresponds with postfix number of `Fn` key. Array `fn_layer[]` indicates destination layer to switch and `fn_keycode[]` has keycodes to send when tapping `Fn` key.

In following setting example, `Fn0`, `Fn1` and `Fn2` switch layer to 1, 2 and 2 respectively. `Fn2` registers `Space` key when tapping while `Fn0` and `Fn1` doesn't send any key.

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


## 6. Terminology
***TBD***
### keymap
is comprised of multiple layers.
### layer
is matrix of keycodes.
### key
is physical button on keyboard or logical switch on software.
### keycode
is codes used on firmware.
### action
is a function assigned on a key.
### layer transparency
Using transparent keycode one layer can refer key definition on other lower layer.
### layer precedence
Top layer has higher precedence than lower layers.
### tapping
is to press and release a key quickly.
### Fn key
is key which executes a special action like layer switching, mouse key, macro or etc.
### dual role key
<http://en.wikipedia.org/wiki/Modifier_key#Dual-role_keys>
