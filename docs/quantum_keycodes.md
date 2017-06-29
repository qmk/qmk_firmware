# Quantum Keycodes

Something important to realise with keycodes is that they are all numbers between `0x0` and `0xFFFF` - even though they may look like functions, words, or phrases, they are all shortcuts to some number. This allows us to define all of what they do in different places, and store keymaps in a relatively small place (arrays). If you try to "call" a keycode by placing it somewhere besides a keymap, it may compile, but it won't do anything useful. 

All keycodes on this page have a value above `0xFF` (values less are considered the [basic keycodes](basic_keycodes.md)) and won't work with any of the mod/layer-tap keys listed at the bottom.

* `SAFE_RANGE` is always the last keycode in the quantum list, and where custom lists can begin
* `RESET` puts the keyboard into DFU mode for flashing
* `DEBUG` toggles debug mode
* Shortcuts for bootmagic options (work when bootmagic is off)
    * `MAGIC_SWAP_CONTROL_CAPSLOCK`
    * `MAGIC_CAPSLOCK_TO_CONTROL`
    * `MAGIC_SWAP_LALT_LGUI`
    * `MAGIC_SWAP_RALT_RGUI`
    * `MAGIC_NO_GUI`
    * `MAGIC_SWAP_GRAVE_ESC`
    * `MAGIC_SWAP_BACKSLASH_BACKSPACE`
    * `MAGIC_HOST_NKRO`
    * `MAGIC_SWAP_ALT_GUI`/`AG_SWAP`
    * `MAGIC_UNSWAP_CONTROL_CAPSLOCK`
    * `MAGIC_UNCAPSLOCK_TO_CONTROL`
    * `MAGIC_UNSWAP_LALT_LGUI`
    * `MAGIC_UNSWAP_RALT_RGUI`
    * `MAGIC_UNNO_GUI`
    * `MAGIC_UNSWAP_GRAVE_ESC`
    * `MAGIC_UNSWAP_BACKSLASH_BACKSPACE`
    * `MAGIC_UNHOST_NKRO`
    * `MAGIC_UNSWAP_ALT_GUI`/`AG_NORM`
    * `MAGIC_TOGGLE_NKRO`
* `KC_GESC`/`GRAVE_ESC` acts as escape when pressed normally but when pressed with a mod will send a `~`
* `KC_LSPO` left shift when held, open paranthesis when tapped
* `KC_RSPC` right shift when held, close paranthesis when tapped
* `KC_LEAD` the leader key

* `FUNC(n)`/`F(n)` to call `fn_action` n
* `M(n)` to call macro n
* `MACROTAP(n)` to macro-tap n idk FIXME

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

## Midi

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
MIDI_VELOCITY_MAX = MI_VEL_10,
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

## Backlight

* `BL_x` where x = 0-15
* `BL_ON = BL_9`
* `BL_OFF = BL_0`
* `BL_DEC`
* `BL_INC`
* `BL_TOGG`
* `BL_STEP`

## RGB WS2818 LEDs

* `RGB_TOG` toggle on/off
* `RGB_MOD` cycle between modes
* `RGB_HUI` hue increase
* `RGB_HUD` hue decrease
* `RGB_SAI` saturation increase
* `RGB_SAD` saturation decrease
* `RGB_VAI` value increase
* `RGB_VAD` value decrease

## Thermal Printer (experimental)

* `PRINT_ON`
* `PRINT_OFF`

## Keyboard output selection

* `OUT_AUTO` auto mode
* `OUT_USB` usb only
* `OUT_BT` bluetooth (when `BLUETOOTH_ENABLE`)

## Modifiers

* `KC_HYPR` LCTL + LSFT + LALT + LGUI - `MOD_HYPR` is the bit version
* `KC_MEH` LCTL + LSFT + LALT - `MOD_MEH` is the bit version

### Modifiers with keys

* `LCTL(kc)` LCTL + kc
* `LSFT(kc)`/`S(kc)` LSFT + kc
* `LALT(kc)` LALT + kc
* `LGUI(kc)` LGUI + kc
* `RCTL(kc)` RCTL + kc
* `RSFT(kc)` RSFT + kc
* `RALT(kc)` RALT + kc
* `RGUI(kc)` RGUI + kc

* `HYPR(kc)` LCTL + LSFT + LALT + LGUI + kc
* `MEH(kc)`  LCTL + LSFT + LALT + kc 
* `LCAG(kc)` LCTL + LALT + LGUI + kc
* `ALTG(kc)` RCTL + RALT + kc
* `SCMD(kc)`/`SWIN(kc)` LGUI + LSFT + kc
* `LCA(kc)` LCTL + LALT + kc

* `OSM(mod)` use mod for one keypress - use mod bits with this

> Mod bits are the 4-letter part of the keycode prefixed with `MOD_`, e.g. `MOD_LCTL`

### Mod-tap keys

These keycodes will press the mod(s) when held, and the key when tapped. They only work with [basic keycodes](basic_keycodes.md). 

* `CTL_T(kc)`/`LCTL_T(kc)` LCTL when held, kc when tapped
* `RCTL_T(kc)` RCTL when held, kc when tapped

* `SFT_T(kc)`/`LSFT_T(kc)` LSFT when held, kc when tapped
* `RSFT_T(kc)` RSFT when held, kc when tapped

* `ALT_T(kc)`/`LALT_T(kc)` LALT when held, kc when tapped
* `RALT_T(kc)`/`ALGR_T(kc)` RALT when held, kc when tapped

* `GUI_T(kc)`/`LGUI_T(kc)` LGUI when held, kc when tapped
* `RGUI_T(kc)` RGUI when held, kc when tapped

* `C_S_T(kc)` LCTL + LSFT when held, kc when tapped
* `MEH_T(kc)` LCTL + LSFT + LALT when held, kc when tapped
* `LCAG_T(kc)` LCTL + LALT + LGUI when held, kc when tapped
* `RCAG_T(kc)` RCTL + RALT + RGUI when held, kc when tapped
* `ALL_T(kc)` LCTL + LSFT + LALT + LGUI when held, kc tapped [more info](http://brettterpstra.com/2012/12/08/a-useful-caps-lock-key/)
* `SCMD_T(kc)`/`SWIN_T(kc)` LGUI + LSFT when held, kc when tapped
* `LCA_T(kc)` LCTL + LALT when held, kc when tapped

## Shifted symbols

It's important to remember that all of the keycodes also send a left shift - this may cause unintended actions if unaccounted for. The 4-letter code is preferred in most situations.

* `KC_TILD`/`KC_TILDE` tilde `~`
* `KC_EXLM`/`KC_EXCLAIM` exclamation mark `!`
* `KC_AT` at sign `@`
* `KC_HASH` hash sign `#`
* `KC_DLR`/`KC_DOLLAR` dollar sign `$`
* `KC_PERC`/`KC_PERCENT` percent sign `%`
* `KC_CIRC`/`KC_CIRCUMFLEX` circumflex `^`
* `KC_AMPR`/`KC_AMPERSAND` ampersand `&`
* `KC_ASTR`/`KC_ASTERISK` asterisk `*`
* `KC_LPRN`/`KC_LEFT_PAREN` left parenthesis `(`
* `KC_RPRN`/`KC_RIGHT_PAREN` right parenthesis `)`
* `KC_UNDS`/`KC_UNDERSCORE` underscore `_`
* `KC_PLUS` plus sign `+`
* `KC_LCBR`/`KC_LEFT_CURLY_BRACE` left curly brace `{`
* `KC_RCBR`/`KC_RIGHT_CURLY_BRACE` right curly brace `}`
* `KC_LT`/`KC_LABK`/`KC_LEFT_ANGLE_BRACKET` left angle bracket `<`
* `KC_GT`/`KC_RABK`/`KC_RIGHT_ANGLE_BRACKET` right angle bracket `>`
* `KC_COLN`/`KC_COLON` colon `:`
* `KC_PIPE` pipe `|`
* `KC_QUES`/`KC_QUESTION` question mark `?`
* `KC_DQT`/`KC_DOUBLE_QUOTE`/`KC_DQUO` double quote `"`

## Layer adjustments

* `LT(layer, kc)` turn on layer (0-15) when held, kc ([basic keycodes](basic_keycodes.md)) when tapped
* `TO(layer)` turn on layer when depressed
* `MO(layer)` momentarily turn on layer when depressed (requires `KC_TRNS` on destination layer)
* `DF(layer)` sets the base (default) layer
* `TG(layer)` toggle layer on/off
* `OSL(layer)` switch to layer for one keycode
* `TT(layer)` tap toggle? idk FIXME

## Unicode

* `UNICODE(n)`/`UC(n)` if `UNICODE_ENABLE`, this will send characters up to `0x7FFF`
* `X(n)` if `UNICODEMAP_ENABLE`, also sends unicode via a different method