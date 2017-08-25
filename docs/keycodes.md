# Overview

When defining a [keymap](keymap.md) each key needs a valid key definition. This page documents the symbols that correspond to keycodes that are available to you in QMK. This is a reference only. Where possible keys link to the page documenting their functionality.

## Keycode Index

|Long Name|Short Name|Description|
|---------|----------|-----------|
|`KC_1`||||
|`KC_2`||||
|`KC_3`||||
|`KC_4`||||
|`KC_5`||||
|`KC_6`||||
|`KC_7`||||
|`KC_8`||||
|`KC_9`||||
|`KC_0`||||
|`KC_F1`||||
|`KC_F2`||||
|`KC_F3`||||
|`KC_F4`||||
|`KC_F5`||||
|`KC_F6`||||
|`KC_F7`||||
|`KC_F8`||||
|`KC_F9`||||
|`KC_F10`||||
|`KC_F11`||||
|`KC_F12`||||
|`KC_F13`||||
|`KC_F14`||||
|`KC_F15`||||
|`KC_F16`||||
|`KC_F17`||||
|`KC_F18`||||
|`KC_F19`||||
|`KC_F20`||||
|`KC_F21`||||
|`KC_F22`||||
|`KC_F23`||||
|`KC_F24`||||
|`KC_A`||||
|`KC_B`||||
|`KC_C`||||
|`KC_D`||||
|`KC_E`||||
|`KC_F`||||
|`KC_G`||||
|`KC_H`||||
|`KC_I`||||
|`KC_J`||||
|`KC_K`||||
|`KC_L`||||
|`KC_M`||||
|`KC_N`||||
|`KC_O`||||
|`KC_P`||||
|`KC_Q`||||
|`KC_R`||||
|`KC_S`||||
|`KC_T`||||
|`KC_U`||||
|`KC_V`||||
|`KC_W`||||
|`KC_X`||||
|`KC_Y`||||
|`KC_Z`||||
|`KC_ENTER`|`KC_ENT`|`Return (ENTER)`|
|`KC_ESCAPE`|`KC_ESC`|`ESCAPE`|
|`KC_BSPACE`|`KC_BSPC`|`DELETE (Backspace)`|
|`KC_TAB`||`Tab`|
|`KC_SPACE`|`KC_SPC`|Spacebar|
|`KC_MINUS`|`KC_MINS`|`-` and `_`|
|`KC_EQUAL`|`KC_EQL`|`=` and `+`|
|`KC_LBRACKET`|`KC_LBRC`|`[` and `{`|
|`KC_RBRACKET`|`KC_RBRC`|`]` and `}`|
|`KC_BSLASH`|`KC_BSLS`|`\` and <code>&#124;</code> |
|`KC_NONUS_HASH`|`KC_NUHS`|Non-US `#` and `~`|
|`KC_NONUS_BSLASH`|`KC_NUBS`|Non-US `\` and <code>&#124;</code> |
|`KC_INT1`|`KC_RO`|JIS `\` and <code>&#124;</code> |
|`KC_INT2`|`KC_KANA`|International216|
|`KC_INT3`|`KC_JYEN`|Yen Symbol (`¥`)|
|`KC_SCOLON`|`KC_SCLN`|`;` and `:`|
|`KC_QUOTE`|`KC_QUOT`|`‘` and `“`|
|`KC_GRAVE`|`KC_GRV`|Grave Accent and Tilde|
|`KC_COMMA`|`KC_COMM`|`,` and `<`|
|`KC_DOT`||`.` and `>`|
|`KC_SLASH`|`KC_SLSH`|`/` and `?`|
|`KC_CAPSLOCK`|`KC_CAPS`|Caps Lock|
|`KC_LCTRL`|`KC_LCTL`|LeftControl|
|`KC_LSHIFT`|`KC_LSFT`|LeftShift|
|`KC_LALT`||LeftAlt|
|`KC_LGUI`||Left GUI(Windows/Apple/Meta key)|
|`KC_RCTRL`|`KC_RCTL`|RightControl|
|`KC_RSHIFT`|`KC_RSFT`|RightShift|
|`KC_RALT`||RightAlt|
|`KC_RGUI`||Right GUI(Windows/Apple/Meta key)|
|`KC_LOCKING_CAPS`|`KC_LCAP`|Locking Caps Lock|
|`KC_LOCKING_NUM`|`KC_LNUM`|Locking Num Lock|
|`KC_LOCKING_SCROLL`|`KC_LSCR`|Locking Scroll Lock|
|`KC_INT4`|`KC_HENK`|JIS Henken|
|`KC_INT5`|`KC_MHEN`|JIS Muhenken|
|`KC_PSCREEN`|`KC_PSCR`|PrintScreen|
|`KC_SCROLLLOCK`|`KC_SLCK`|Scroll Lock|
|`KC_PAUSE`|`KC_PAUS`|Pause|
|`KC_INSERT`|`KC_INS`|Insert|
|`KC_HOME`||Home|
|`KC_PGUP`||PageUp|
|`KC_DELETE`|`KC_DEL`|Delete Forward|
|`KC_END`||End|
|`KC_PGDOWN`|`KC_PGDN`|PageDown|
|`KC_RIGHT`|`KC_RGHT`|RightArrow|
|`KC_LEFT`||LeftArrow|
|`KC_DOWN`||DownArrow|
|`KC_UP`||UpArrow|
|`KC_APPLICATION`|`KC_APP`|Application|
|`KC_POWER`||Power|
|`KC_EXECUTE`||Execute|
|`KC_HELP`||Help|
|`KC_MENU`||Menu|
|`KC_SELECT`||Select|
|`KC_AGAIN`||Again|
|`KC_UNDO`||Undo|
|`KC_CUT`||Cut|
|`KC_COPY`||Copy|
|`KC_PASTE`||Paste|
|`KC_FIND`||Find|
|`KC_ALT_ERASE`||Alternate Erase|
|`KC_SYSREQ`||SysReq/Attention|
|`KC_CANCEL`||Cancel|
|`KC_CLEAR`||Clear|
|`KC_PRIOR`||Prior|
|`KC_RETURN`||Return|
|`KC_SEPARATOR`||Separator|
|`KC_OUT`||Out|
|`KC_OPER`||Oper|
|`KC_CLEAR_AGAIN`||Clear/Again|
|`KC_CRSEL`||CrSel/Props|
|`KC_EXSEL`||ExSel|
|`KC_SYSTEM_POWER`|`KC_PWR`|System Power Down|
|`KC_SYSTEM_SLEEP`|`KC_SLEP`|System Sleep|
|`KC_SYSTEM_WAKE`|`KC_WAKE`|System Wake|
|`KC_MAIL`|`KC_MAIL`||
|`KC_CALCULATOR`|`KC_CALC`||
|`KC_MY_COMPUTER`|`KC_MYCM`||
|`KC_WWW_SEARCH`|`KC_WSCH`||
|`KC_WWW_HOME`|`KC_WHOM`||
|`KC_WWW_BACK`|`KC_WBAK`||
|`KC_WWW_FORWARD`|`KC_WFWD`||
|`KC_WWW_STOP`|`KC_WSTP`||
|`KC_WWW_REFRESH`|`KC_WREF`||
|`KC_WWW_FAVORITES`|`KC_WFAV`||
|`KC_STOP`||Stop|
|`KC__MUTE`||Mute|
|`KC__VOLUP`||Volume Up|
|`KC__VOLDOWN`||Volume Down|
|`KC_AUDIO_MUTE`|`KC_MUTE`||
|`KC_AUDIO_VOL_UP`|`KC_VOLU`||
|`KC_AUDIO_VOL_DOWN`|`KC_VOLD`||
|`KC_MEDIA_NEXT_TRACK`|`KC_MNXT`|Next Track (Windows)|
|`KC_MEDIA_PREV_TRACK`|`KC_MPRV`|Previous Track (Windows)|
|`KC_MEDIA_FAST_FORWARD`|`KC_MFFD`|Next Track (macOS)|
|`KC_MEDIA_REWIND`|`KC_MRWD`|Previous Track (macOS)|
|`KC_MEDIA_STOP`|`KC_MSTP`||
|`KC_MEDIA_PLAY_PAUSE`|`KC_MPLY`||
|`KC_MEDIA_SELECT`|`KC_MSEL`||
|`KC_NUMLOCK`|`KC_NLCK`|Keypad Num Lock and Clear|
|`KC_KP_SLASH`|`KC_PSLS`|Keypad /|
|`KC_KP_ASTERISK`|`KC_PAST`|Keypad *|
|`KC_KP_MINUS`|`KC_PMNS`|Keypad -|
|`KC_KP_PLUS`|`KC_PPLS`|Keypad +|
|`KC_KP_ENTER`|`KC_PENT`|Keypad ENTER`|
|`KC_KP_1`|`KC_P1`|Keypad 1 and End|
|`KC_KP_2`|`KC_P2`|Keypad 2 and Down Arrow|
|`KC_KP_3`|`KC_P3`|Keypad 3 and PageDn|
|`KC_KP_4`|`KC_P4`|Keypad 4 and Left Arrow|
|`KC_KP_5`|`KC_P5`|Keypad 5|
|`KC_KP_6`|`KC_P6`|Keypad 6 and Right Arrow|
|`KC_KP_7`|`KC_P7`|Keypad 7 and Home|
|`KC_KP_8`|`KC_P8`|Keypad 8 and Up Arrow|
|`KC_KP_9`|`KC_P9`|Keypad 9 and PageUp|
|`KC_KP_0`|`KC_P0`|Keypad 0 and Insert|
|`KC_KP_DOT`|`KC_PDOT`|Keypad . and Delete|
|`KC_KP_EQUAL`|`KC_PEQL`|Keypad =|
|`KC_KP_COMMA`|`KC_PCMM`|Keypad Comma|
|`KC_KP_EQUAL_AS400`||Keypad Equal Sign|
|`KC_NO`||Ignore this key. (NOOP) |
|`KC_TRNS`||Make this key transparent to find the key on a lower layer.|
|[`KC_MS_UP`](mouse_keys.md)|`KC_MS_U`|Mouse Cursor Up|
|[`KC_MS_DOWN`](mouse_keys.md)|`KC_MS_D`|Mouse Cursor Down|
|[`KC_MS_LEFT`](mouse_keys.md)|`KC_MS_L`|Mouse Cursor Left|
|[`KC_MS_RIGHT`](mouse_keys.md)|`KC_MS_R`|Mouse Cursor Right|
|[`KC_MS_BTN1`](mouse_keys.md)|`KC_BTN1`|Mouse Button 1|
|[`KC_MS_BTN2`](mouse_keys.md)|`KC_BTN2`|Mouse Button 2|
|[`KC_MS_BTN3`](mouse_keys.md)|`KC_BTN3`|Mouse Button 3|
|[`KC_MS_BTN4`](mouse_keys.md)|`KC_BTN4`|Mouse Button 4|
|[`KC_MS_BTN5`](mouse_keys.md)|`KC_BTN5`|Mouse Button 5|
|[`KC_MS_WH_UP`](mouse_keys.md)|`KC_WH_U`|Mouse Wheel Up|
|[`KC_MS_WH_DOWN`](mouse_keys.md)|`KC_WH_D`|Mouse Wheel Down|
|[`KC_MS_WH_LEFT`](mouse_keys.md)|`KC_WH_L`|Mouse Wheel Left|
|[`KC_MS_WH_RIGHT`](mouse_keys.md)|`KC_WH_R`|Mouse Wheel Right|
|[`KC_MS_ACCEL0`](mouse_keys.md)|`KC_ACL0`|Mouse Acceleration 0|
|[`KC_MS_ACCEL1`](mouse_keys.md)|`KC_ACL1`|Mouse Acceleration 1|
|[`KC_MS_ACCEL2`](mouse_keys.md)|`KC_ACL2`|Mouse Acceleration 2|
|[`RESET`](quantum_keycodes.md#qmk-keycodes)||Put the keyboard into DFU mode for flashing|
|[`DEBUG`](quantum_keycodes.md#qmk-keycodes)||Toggles debug mode|
|[`KC_GESC`](quantum_keycodes.md#qmk-keycodes)|`GRAVE_ESC`|Acts as escape when pressed normally but when pressed with Shift or GUI will send a `~`|
|[`KC_LSPO`](quantum_keycodes.md#qmk-keycodes)||Left shift when held, open paranthesis when tapped|
|[`KC_RSPC`](quantum_keycodes.md#qmk-keycodes)||Right shift when held, close paranthesis when tapped|
|[`KC_LEAD`](feature_leader_key.md)||The leader key|
|[`FUNC(n)`](quantum_keycodes.md#qmk-keycodes)|`F(n)`|Call `fn_action(n)`|
|[`M(n)`](quantum_keycodes.md#qmk-keycodes)||to call macro n|
|[`MACROTAP(n)`](quantum_keycodes.md#qmk-keycodes)||to macro-tap n idk FIXME`|
|[`MAGIC_SWAP_CONTROL_CAPSLOCK`](feature_bootmagic.md)||Swap Capslock and Left Control|
|[`MAGIC_CAPSLOCK_TO_CONTROL`](feature_bootmagic.md)||Treat Capslock like a Control Key|
|[`MAGIC_SWAP_LALT_LGUI`](feature_bootmagic.md)||Swap the left Alt and GUI keys|
|[`MAGIC_SWAP_RALT_RGUI`](feature_bootmagic.md)||Swap the right Alt and GUI keys|
|[`MAGIC_NO_GUI`](feature_bootmagic.md)||Disable the GUI key|
|[`MAGIC_SWAP_GRAVE_ESC`](feature_bootmagic.md)||Swap the Grave and Esc key.|
|[`MAGIC_SWAP_BACKSLASH_BACKSPACE`](feature_bootmagic.md)||Swap backslack and backspace|
|[`MAGIC_HOST_NKRO`](feature_bootmagic.md)||Force NKRO on|
|[`MAGIC_SWAP_ALT_GUI`/`AG_SWAP`](feature_bootmagic.md)||Swap Alt and Gui on both sides|
|[`MAGIC_UNSWAP_CONTROL_CAPSLOCK`](feature_bootmagic.md)||Disable the Control/Capslock swap|
|[`MAGIC_UNCAPSLOCK_TO_CONTROL`](feature_bootmagic.md)||Disable treating Capslock like Control |
|[`MAGIC_UNSWAP_LALT_LGUI`](feature_bootmagic.md)||Disable Left Alt and GUI switching|
|[`MAGIC_UNSWAP_RALT_RGUI`](feature_bootmagic.md)||Disable Right Alt and GUI switching|
|[`MAGIC_UNNO_GUI`](feature_bootmagic.md)||Enable the GUI key |
|[`MAGIC_UNSWAP_GRAVE_ESC`](feature_bootmagic.md)||Disable the Grave/Esc swap |
|[`MAGIC_UNSWAP_BACKSLASH_BACKSPACE`](feature_bootmagic.md)||Disable the backslash/backspace swap|
|[`MAGIC_UNHOST_NKRO`](feature_bootmagic.md)||Force NKRO off|
|[`MAGIC_UNSWAP_ALT_GUI`/`AG_NORM`](feature_bootmagic.md)||Disable the Alt/GUI switching|
|[`MAGIC_TOGGLE_NKRO`](feature_bootmagic.md)||Turn NKRO on or off|
|[`BL_x`](feature_backlight.md)||Set a specific backlight level between 0-9|
|[`BL_ON`](feature_backlight.md)||An alias for `BL_9`|
|[`BL_OFF`](feature_backlight.md)||An alias for `BL_0`|
|[`BL_DEC`](feature_backlight.md)||Turn the backlight level down by 1|
|[`BL_INC`](feature_backlight.md)||Turn the backlight level up by 1|
|[`BL_TOGG`](feature_backlight.md)||Toggle the backlight on or off|
|[`BL_STEP`](feature_backlight.md)||Step through backlight levels, wrapping around to 0 when you reach the top.|
|[`RGB_TOG`](feature_rgblight.md)||toggle on/off|
|[`RGB_MOD`](feature_rgblight.md)||cycle through modes|
|[`RGB_HUI`](feature_rgblight.md)||hue increase|
|[`RGB_HUD`](feature_rgblight.md)||hue decrease|
|[`RGB_SAI`](feature_rgblight.md)||saturation increase|
|[`RGB_SAD`](feature_rgblight.md)||saturation decrease|
|[`RGB_VAI`](feature_rgblight.md)||value increase|
|[`RGB_VAD`](feature_rgblight.md)||value decrease|
|[`PRINT_ON`](feature_thermal_printer.md)||Start printing everything the user types|
|[`PRINT_OFF`](feature_thermal_printer.md)||Stop printing everything the user types|
|[`OUT_AUTO`](feature_bluetooth.md)||auto mode|
|[`OUT_USB`](feature_bluetooth.md)||usb only|
|[`OUT_BT`](feature_bluetooth.md)||bluetooth (when `BLUETOOTH_ENABLE`)|
|[`KC_HYPR`](quantum_keycodes.md#modifiers)||Hold down LCTL + LSFT + LALT + LGUI`|
|[`KC_MEH`](quantum_keycodes.md#modifiers)||Hold down LCTL + LSFT + LALT`|
|[`LCTL(kc)`](quantum_keycodes.md#modifiers)||`LCTL` + `kc`|
|[`LSFT(kc)`](quantum_keycodes.md#modifiers)|[`S(kc)`](quantum_keycodes.md#modifiers)|`LSFT` + `kc`|
|[`LALT(kc)`](quantum_keycodes.md#modifiers)||`LALT` + `kc`|
|[`LGUI(kc)`](quantum_keycodes.md#modifiers)||`LGUI` + `kc`|
|[`RCTL(kc)`](quantum_keycodes.md#modifiers)||`RCTL` + `kc`|
|[`RSFT(kc)`](quantum_keycodes.md#modifiers)||`RSFT` + `kc`|
|[`RALT(kc)`](quantum_keycodes.md#modifiers)||`RALT` + `kc`|
|[`RGUI(kc)`](quantum_keycodes.md#modifiers)||`RGUI` + `kc`|
|[`HYPR(kc)`](quantum_keycodes.md#modifiers)||`LCTL` + `LSFT` + `LALT` + `LGUI` + `kc`|
|[`MEH(kc)`](quantum_keycodes.md#modifiers)||`LCTL` + `LSFT` + `LALT` + `kc`|
|[`LCAG(kc)`](quantum_keycodes.md#modifiers)||`LCTL` + `LALT` + `LGUI` + `kc`|
|[`ALTG(kc)`](quantum_keycodes.md#modifiers)||`RCTL` + `RALT` + `kc`|
|[`SCMD(kc)`](quantum_keycodes.md#modifiers)|[`SWIN(kc)`](quantum_keycodes.md#modifiers)|`LGUI` + `LSFT` + `kc`|
|[`LCA(kc)`](quantum_keycodes.md#modifiers)||`LCTL` + `LALT` + `kc`|
|[`CTL_T(kc)`](quantum_keycodes.md#mod-tap-keys)|[`LCTL_T(kc)`](quantum_keycodes.md#mod-tap-keys)|`LCTL` when held, `kc` when tapped|
|[`RCTL_T(kc)`](quantum_keycodes.md#mod-tap-keys)||[`RCTL` when held, `kc` when tapped|
|[`SFT_T(kc)`](quantum_keycodes.md#mod-tap-keys)|[`LSFT_T(kc)`](quantum_keycodes.md#mod-tap-keys)|`LSFT` when held, `kc` when tapped|
|[`RSFT_T(kc)`](quantum_keycodes.md#mod-tap-keys)||[`RSFT` when held, `kc` when tapped|
|[`ALT_T(kc)`](quantum_keycodes.md#mod-tap-keys)|[`LALT_T(kc)`](quantum_keycodes.md#mod-tap-keys)|`LALT` when held, `kc` when tapped|
|[`RALT_T(kc)`](quantum_keycodes.md#mod-tap-keys)|[`ALGR_T(kc)`](quantum_keycodes.md#mod-tap-keys)|`RALT` when held, `kc` when tapped|
|[`GUI_T(kc)`](quantum_keycodes.md#mod-tap-keys)|[`LGUI_T(kc)`](quantum_keycodes.md#mod-tap-keys)|`LGUI` when held, `kc` when tapped|
|[`RGUI_T(kc)`](quantum_keycodes.md#mod-tap-keys)||`RGUI` when held, `kc` when tapped|
|[`C_S_T(kc)`](quantum_keycodes.md#mod-tap-keys)||`LCTL` + `LSFT` when held, `kc` when tapped|
|[`MEH_T(kc)`](quantum_keycodes.md#mod-tap-keys)||`LCTL` + `LSFT` + `LALT` when held, `kc` when tapped|
|[`LCAG_T(kc)`](quantum_keycodes.md#mod-tap-keys)||`LCTL` + `LALT` + `LGUI` when held, `kc` when tapped|
|[`RCAG_T(kc)`](quantum_keycodes.md#mod-tap-keys)||`RCTL` + `RALT` + `RGUI` when held, `kc` when tapped|
|[`ALL_T(kc)`](quantum_keycodes.md#mod-tap-keys)||`LCTL` + `LSFT` + `LALT` + `LGUI` when held, `kc` when tapped [more info](http://brettterpstra.com/2012/12/08/a-useful-caps-lock-key/)|
|[`SCMD_T(kc)`](quantum_keycodes.md#mod-tap-keys)|[`SWIN_T(kc)`](quantum_keycodes.md#mod-tap-keys)|`LGUI` + `LSFT` when held, `kc` when tapped|
|[`LCA_T(kc)`](quantum_keycodes.md#mod-tap-keys)||`LCTL` + `LALT` when held, `kc` when tapped|
|[`KC_TILD`](keycodes_us_ansi_shifted.md)|`KC_TILDE`|tilde `~`|
|[`KC_EXLM`](keycodes_us_ansi_shifted.md)|`KC_EXCLAIM`|exclamation mark `!`|
|[`KC_AT`](keycodes_us_ansi_shifted.md)||at sign `@`|
|[`KC_HASH`](keycodes_us_ansi_shifted.md)||hash sign `#`|
|[`KC_DLR`](keycodes_us_ansi_shifted.md)|`KC_DOLLAR`|dollar sign `$`|
|[`KC_PERC`](keycodes_us_ansi_shifted.md)|`KC_PERCENT`|percent sign `%`|
|[`KC_CIRC`](keycodes_us_ansi_shifted.md)|`KC_CIRCUMFLEX`|circumflex `^`|
|[`KC_AMPR`](keycodes_us_ansi_shifted.md)|`KC_AMPERSAND`|ampersand `&`|
|[`KC_ASTR`](keycodes_us_ansi_shifted.md)|`KC_ASTERISK`|asterisk `*`|
|[`KC_LPRN`](keycodes_us_ansi_shifted.md)|`KC_LEFT_PAREN`|left parenthesis `(`|
|[`KC_RPRN`](keycodes_us_ansi_shifted.md)|`KC_RIGHT_PAREN`|right parenthesis `)`|
|[`KC_UNDS`](keycodes_us_ansi_shifted.md)|`KC_UNDERSCORE`|underscore `_`|
|[`KC_PLUS`](keycodes_us_ansi_shifted.md)||plus sign `+`|
|[`KC_LCBR`](keycodes_us_ansi_shifted.md)|`KC_LEFT_CURLY_BRACE`|left curly brace `{`|
|[`KC_RCBR`](keycodes_us_ansi_shifted.md)|`KC_RIGHT_CURLY_BRACE`|right curly brace `}`|
|[`KC_LT`/`KC_LABK`](keycodes_us_ansi_shifted.md)|`KC_LEFT_ANGLE_BRACKET`|left angle bracket `<`|
|[`KC_GT`/`KC_RABK`](keycodes_us_ansi_shifted.md)|`KC_RIGHT_ANGLE_BRACKET`|right angle bracket `>`|
|[`KC_COLN`](keycodes_us_ansi_shifted.md)|`KC_COLON`|colon `:`|
|[`KC_PIPE`](keycodes_us_ansi_shifted.md)||pipe `\|`|
|[`KC_QUES`](keycodes_us_ansi_shifted.md)|`KC_QUESTION`|question mark `?`|
|[`KC_DQT`/`KC_DQUO`](keycodes_us_ansi_shifted.md)|`KC_DOUBLE_QUOTE`|double quote `"`|
|[`LT(layer, kc)`](feature_common_shortcuts.md#switching-and-toggling-layers)||turn on layer (0-15) when held, kc ([basic keycodes](keycodes_basic.md)) when tapped|
|[`TO(layer)`](feature_common_shortcuts.md#switching-and-toggling-layers)||turn on layer when depressed|
|[`MO(layer)`](feature_common_shortcuts.md#switching-and-toggling-layers)||momentarily turn on layer when depressed (requires `KC_TRNS` on destination layer)|
|[`DF(layer)`](feature_common_shortcuts.md#switching-and-toggling-layers)||sets the base (default) layer|
|[`TG(layer)`](feature_common_shortcuts.md#switching-and-toggling-layers)||toggle layer on/off|
|[`TT(layer)`](feature_common_shortcuts.md#switching-and-toggling-layers)||tap toggle? idk FIXME`|
|[`OSM(mod)`](quantum_keycodes.md#one-shot-keys)||hold mod for one keypress|
|[`OSL(layer)`](quantum_keycodes.md#one-shot-keys)||switch to layer for one keypress|
|[`UNICODE(n)`](unicode.md)|[`UC(n)`](unicode.md)|if `UNICODE_ENABLE`, this will send characters up to `0x7FFF`|
|[`X(n)`](unicode.md)||if `UNICODEMAP_ENABLE`, also sends unicode via a different method|
