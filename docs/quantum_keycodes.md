# Quantum Keycodes

All keycodes within quantum are numbers between `0x0000` and `0xFFFF`. Within your `keymap.c` it may look like you have functions and other special cases, but ultimately the C preprocessor will translate those into a single 4 byte integer. QMK has reserved `0x0000` through `0x00FF` for standard keycodes. These are keycodes such as `KC_A`, `KC_1`, and `KC_LCTL`, which are basic keys defined in the USB HID specification. 

On this page we have documented keycodes between `0x00FF` and `0xFFFF` which are used to implement advanced quantum features. If you define your own custom keycodes they will be put into this range as well. Keycodes above `0x00FF` may not be used with any of the mod/layer-tap keys listed 

## QMK keycodes

|Name|Description|
|----|-----------|
|`RESET`|Put the keyboard into DFU mode for flashing|
|`DEBUG`|Toggles debug mode|
|`KC_GESC`/`GRAVE_ESC`|Acts as escape when pressed normally but when pressed with Shift or GUI will send a `~`|
|`KC_LSPO`|Left shift when held, open paranthesis when tapped|
|`KC_RSPC`|Right shift when held, close paranthesis when tapped|
|`KC_LEAD`|The [leader key](leader_key.md)|
|`FUNC(n)`/`F(n)`|Call `fn_action(n)`|
|`M(n)`|to call macro n|
|`MACROTAP(n)`|to macro-tap n idk FIXME|
|`KC_LOCK`|The [lock key](key_lock.md)|

## Bootmagic Keycodes

Shortcuts for bootmagic options (these work even when bootmagic is off.)

|Name|Description|
|----|-----------|
|`MAGIC_SWAP_CONTROL_CAPSLOCK`|Swap Capslock and Left Control|
|`MAGIC_CAPSLOCK_TO_CONTROL`|Treat Capslock like a Control Key|
|`MAGIC_SWAP_LALT_LGUI`|Swap the left Alt and GUI keys|
|`MAGIC_SWAP_RALT_RGUI`|Swap the right Alt and GUI keys|
|`MAGIC_NO_GUI`|Disable the GUI key|
|`MAGIC_SWAP_GRAVE_ESC`|Swap the Grave and Esc key.|
|`MAGIC_SWAP_BACKSLASH_BACKSPACE`|Swap backslack and backspace|
|`MAGIC_HOST_NKRO`|Force NKRO on|
|`MAGIC_SWAP_ALT_GUI`/`AG_SWAP`|Swap Alt and Gui on both sides|
|`MAGIC_UNSWAP_CONTROL_CAPSLOCK`|Disable the Control/Capslock swap|
|`MAGIC_UNCAPSLOCK_TO_CONTROL`|Disable treating Capslock like Control |
|`MAGIC_UNSWAP_LALT_LGUI`|Disable Left Alt and GUI switching|
|`MAGIC_UNSWAP_RALT_RGUI`|Disable Right Alt and GUI switching|
|`MAGIC_UNNO_GUI`|Enable the GUI key |
|`MAGIC_UNSWAP_GRAVE_ESC`|Disable the Grave/Esc swap |
|`MAGIC_UNSWAP_BACKSLASH_BACKSPACE`|Disable the backslash/backspace swap|
|`MAGIC_UNHOST_NKRO`|Force NKRO off|
|`MAGIC_UNSWAP_ALT_GUI`/`AG_NORM`|Disable the Alt/GUI switching|
|`MAGIC_TOGGLE_NKRO`|Turn NKRO on or off|

<!-- FIXME: this formatting needs work

## Audio

```c
#ifdef AUDIO_ENABLE
    AU_ON,
    AU_OFF,
    AU_TOG,

    #ifdef FAUXCLICKY_ENABLE
        FC_ON,
        FC_OFF,
        FC_TOG,
    #endif

    // Music mode on/off/toggle
    MU_ON,
    MU_OFF,
    MU_TOG,

    // Music voice iterate
    MUV_IN,
    MUV_DE,
#endif
```

### Midi

#if !MIDI_ENABLE_STRICT || (defined(MIDI_ENABLE) && defined(MIDI_BASIC))
    MI_ON,  // send midi notes when music mode is enabled
    MI_OFF, // don't send midi notes when music mode is enabled
#endif

MIDI_TONE_MIN,
MIDI_TONE_MAX

MI_C = MIDI_TONE_MIN,
MI_Cs,
MI_Db = MI_Cs,
MI_D,
MI_Ds,
MI_Eb = MI_Ds,
MI_E,
MI_F,
MI_Fs,
MI_Gb = MI_Fs,
MI_G,
MI_Gs,
MI_Ab = MI_Gs,
MI_A,
MI_As,
MI_Bb = MI_As,
MI_B,

MIDI_TONE_KEYCODE_OCTAVES > 1

where x = 1-5:
MI_C_x,
MI_Cs_x,
MI_Db_x = MI_Cs_x,
MI_D_x,
MI_Ds_x,
MI_Eb_x = MI_Ds_x,
MI_E_x,
MI_F_x,
MI_Fs_x,
MI_Gb_x = MI_Fs_x,
MI_G_x,
MI_Gs_x,
MI_Ab_x = MI_Gs_x,
MI_A_x,
MI_As_x,
MI_Bb_x = MI_As_x,
MI_B_x,

MI_OCT_Nx 1-2
MI_OCT_x 0-7
MIDI_OCTAVE_MIN = MI_OCT_N2,
MIDI_OCTAVE_MAX = MI_OCT_7,
MI_OCTD, // octave down
MI_OCTU, // octave up

MI_TRNS_Nx 1-6
MI_TRNS_x 0-6
MIDI_TRANSPOSE_MIN = MI_TRNS_N6,
MIDI_TRANSPOSE_MAX = MI_TRNS_6,
MI_TRNSD, // transpose down
MI_TRNSU, // transpose up

MI_VEL_x 1-10
MIDI_VELOCITY_MIN = MI_VEL_1,
MIDI_VELOCITY_MAX = MI_VEL_9,
MI_VELD, // velocity down
MI_VELU, // velocity up

MI_CHx 1-16
MIDI_CHANNEL_MIN = MI_CH1
MIDI_CHANNEL_MAX = MI_CH16,
MI_CHD, // previous channel
MI_CHU, // next channel

MI_ALLOFF, // all notes off

MI_SUS, // sustain
MI_PORT, // portamento
MI_SOST, // sostenuto
MI_SOFT, // soft pedal
MI_LEG,  // legato

MI_MOD, // modulation
MI_MODSD, // decrease modulation speed
MI_MODSU, // increase modulation speed
#endif // MIDI_ADVANCED

-->

## Backlight

These keycodes control the backlight. Most keyboards use this for single color in-switch lighting.

|Name|Description|
|----|-----------|
|`BL_x`|Set a specific backlight level between 0-9|
|`BL_ON`|An alias for `BL_9`|
|`BL_OFF`|An alias for `BL_0`|
|`BL_DEC`|Turn the backlight level down by 1|
|`BL_INC`|Turn the backlight level up by 1|
|`BL_TOGG`|Toggle the backlight on or off|
|`BL_STEP`|Step through backlight levels, wrapping around to 0 when you reach the top.|

## RGBLIGHT WS2818 LEDs

This controls the `RGBLIGHT` functionality. Most keyboards use WS2812 (and compatible) LEDs for underlight or case lighting.

|Name|Description|
|----|-----------|
|`RGB_TOG`|toggle on/off|
|`RGB_MOD`|cycle through modes|
|`RGB_HUI`|hue increase|
|`RGB_HUD`|hue decrease|
|`RGB_SAI`|saturation increase|
|`RGB_SAD`|saturation decrease|
|`RGB_VAI`|value increase|
|`RGB_VAD`|value decrease|

## Thermal Printer (experimental)

|Name|Description|
|----|-----------|
|`PRINT_ON`|Start printing everything the user types|
|`PRINT_OFF`|Stop printing everything the user types|

## Keyboard output selection

This is used when multiple keyboard outputs can be selected. Currently this only allows for switching between USB and Bluetooth on keyboards that support both.

|Name|Description|
|----|-----------|
|`OUT_AUTO`|auto mode|
|`OUT_USB`|usb only|
|`OUT_BT`|bluetooth (when `BLUETOOTH_ENABLE`)|

## Modifiers

These are special keycodes that simulate pressing several modifiers at once.

|Name|Description|
|----|-----------|
|`KC_HYPR`|Hold down LCTL + LSFT + LALT + LGUI|
|`KC_MEH`|Hold down LCTL + LSFT + LALT|

/* FIXME: Should we have these in QMK too?
 * |`KC_LCAG`|`LCTL` + `LALT` + `LGUI`|
 * |`KC_ALTG`|`RCTL` + `RALT`|
 * |`KC_SCMD`/`KC_SWIN`|`LGUI` + `LSFT`|
 * |`KC_LCA`|`LCTL` + `LALT`|
 */

### Modifiers with keys

|Name|Description|
|----|-----------|
|`LCTL(kc)`|`LCTL` + `kc`|
|`LSFT(kc)`/`S(kc)`|`LSFT` + `kc`|
|`LALT(kc)`|`LALT` + `kc`|
|`LGUI(kc)`|`LGUI` + `kc`|
|`RCTL(kc)`|`RCTL` + `kc`|
|`RSFT(kc)`|`RSFT` + `kc`|
|`RALT(kc)`|`RALT` + `kc`|
|`RGUI(kc)`|`RGUI` + `kc`|
|`HYPR(kc)`|`LCTL` + `LSFT` + `LALT` + `LGUI` + `kc`|
|`MEH(kc)`|`LCTL` + `LSFT` + `LALT` + `kc`|
|`LCAG(kc)`|`LCTL` + `LALT` + `LGUI` + `kc`|
|`ALTG(kc)`|`RCTL` + `RALT` + `kc`|
|`SCMD(kc)`/`SWIN(kc)`|`LGUI` + `LSFT` + `kc`|
|`LCA(kc)`|`LCTL` + `LALT` + `kc`|

### One Shot Keys

Most modifiers work by being held down while you push another key. You can use `OSM()` to setup a "One Shot" modifier. When you tap a one shot mod it will remain is a pressed state until you press another key. 

To specify a your modifier you need to pass the `MOD` form of the key. For example, if you want to setup a One Shot Control you would use `OSM(MOD_LCTL)`.

|Name|Description|
|----|-----------|
|`OSM(mod)`|use mod for one keypress|
|`OSL(layer)`|switch to layer for one keypress|

### Mod-tap keys

These keycodes will press the mod(s) when held, and the key when tapped. They only work with [basic keycodes](basic_keycodes.md). 

|Name|Description|
|----|-----------|
|`CTL_T(kc)`/`LCTL_T(kc)`|`LCTL` when held, `kc` when tapped|
|`RCTL_T(kc)`|`RCTL` when held, `kc` when tapped|
|`SFT_T(kc)`/`LSFT_T(kc)`|`LSFT` when held, `kc` when tapped|
|`RSFT_T(kc)`|`RSFT` when held, `kc` when tapped|
|`ALT_T(kc)`/`LALT_T(kc)`|`LALT` when held, `kc` when tapped|
|`RALT_T(kc)`/`ALGR_T(kc)`|`RALT` when held, `kc` when tapped|
|`GUI_T(kc)`/`LGUI_T(kc)`|`LGUI` when held, `kc` when tapped|
|`RGUI_T(kc)`|`RGUI` when held, `kc` when tapped|
|`C_S_T(kc)`|`LCTL` + `LSFT` when held, `kc` when tapped|
|`MEH_T(kc)`|`LCTL` + `LSFT` + `LALT` when held, `kc` when tapped|
|`LCAG_T(kc)`|`LCTL` + `LALT` + `LGUI` when held, `kc` when tapped|
|`RCAG_T(kc)`|`RCTL` + `RALT` + `RGUI` when held, `kc` when tapped|
|`ALL_T(kc)`|`LCTL` + `LSFT` + `LALT` + `LGUI` when held, `kc` when tapped [more info](http://brettterpstra.com/2012/12/08/a-useful-caps-lock-key/)|
|`SCMD_T(kc)`/`SWIN_T(kc)`|`LGUI` + `LSFT` when held, `kc` when tapped|
|`LCA_T(kc)`|`LCTL` + `LALT` when held, `kc` when tapped|

## US ANSI Shifted symbols

These keycodes correspond to characters that are "shifted" on a standard US ANSI keyboards. They do not have dedicated keycodes but are instead typed by holding down shift and then sending a keycode. 

It's important to remember that all of these keycodes send a left shift - this may cause unintended actions if unaccounted for. The short code is preferred in most situations.

|Short Name|Long Name|Description|
|----------|---------|-----------|
|`KC_TILD`|`KC_TILDE`|tilde `~`|
|`KC_EXLM`|`KC_EXCLAIM`|exclamation mark `!`|
|`KC_AT`||at sign `@`|
|`KC_HASH`||hash sign `#`|
|`KC_DLR`|`KC_DOLLAR`|dollar sign `$`|
|`KC_PERC`|`KC_PERCENT`|percent sign `%`|
|`KC_CIRC`|`KC_CIRCUMFLEX`|circumflex `^`|
|`KC_AMPR`|`KC_AMPERSAND`|ampersand `&`|
|`KC_ASTR`|`KC_ASTERISK`|asterisk `*`|
|`KC_LPRN`|`KC_LEFT_PAREN`|left parenthesis `(`|
|`KC_RPRN`|`KC_RIGHT_PAREN`|right parenthesis `)`|
|`KC_UNDS`|`KC_UNDERSCORE`|underscore `_`|
|`KC_PLUS`||plus sign `+`|
|`KC_LCBR`|`KC_LEFT_CURLY_BRACE`|left curly brace `{`|
|`KC_RCBR`|`KC_RIGHT_CURLY_BRACE`|right curly brace `}`|
|`KC_LT`/`KC_LABK`|`KC_LEFT_ANGLE_BRACKET`|left angle bracket `<`|
|`KC_GT`/`KC_RABK`|`KC_RIGHT_ANGLE_BRACKET`|right angle bracket `>`|
|`KC_COLN`|`KC_COLON`|colon `:`|
|`KC_PIPE`||pipe `\|`|
|`KC_QUES`|`KC_QUESTION`|question mark `?`|
|`KC_DQT`/`KC_DQUO`|`KC_DOUBLE_QUOTE`|double quote `"`|

## Layer Changes

These are keycodes that can be used to change the current layer.

|Name|Description|
|----|-----------|
|`LT(layer, kc)`|turn on layer (0-15) when held, kc ([basic keycodes](basic_keycodes.md)) when tapped|
|`TO(layer)`|turn on layer when depressed|
|`MO(layer)`|momentarily turn on layer when depressed (requires `KC_TRNS` on destination layer)|
|`DF(layer)`|sets the base (default) layer|
|`TG(layer)`|toggle layer on/off|
|`TT(layer)`|tap toggle? idk FIXME|
|`OSL(layer)`|switch to layer for one keycode|

## Unicode

These keycodes can be used in conjuction with the [Unicode](unicode_and_additional_language_support.md) support.

|`UNICODE(n)`/`UC(n)`|if `UNICODE_ENABLE`, this will send characters up to `0x7FFF`|
|`X(n)`|if `UNICODEMAP_ENABLE`, also sends unicode via a different method|

# `SAFE_RANGE`, or safely defining custom keycodes

Sometimes you want to define your own custom keycodes to make your keymap easier to read. QMK provides `SAFE_RANGE` to help you do that. `SAFE_RANGE` is the first available keycode in the `0x0000`-`0xFFFF` range and you can use it when creating your own custom keycode enum:

```
enum my_keycodes {
  FOO = SAFE_RANGE,
  BAR
};
```

You can then use `process_record_user()` to do something with your keycode:

```
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case FOO:
      // Do something here
      break;
    case BAR:
      // Do something here
      break;
  }
}
```
