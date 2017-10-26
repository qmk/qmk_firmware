# Basic keycodes

Basic keycodes are based on [HID Usage Keyboard/Keypad Page(0x07)](http://www.usb.org/developers/hidpage/Hut1_12v2.pdf) with following exceptions:

* `KC_NO` = 0 for no action
* `KC_TRNS` = 1 for layer transparency
* internal special keycodes in the `0xA5-DF` range (tmk heritage).

## Letters and Numbers

|KC_1|KC_2|KC_3|KC_4|KC_5|KC_6|KC_7|KC_8|
|----|----|----|----|----|----|----|----|
|KC_9|KC_0|KC_F1|KC_F2|KC_F3|KC_F4|KC_F5|KC_F6|
|KC_F7|KC_F8|KC_F9|KC_F10|KC_F11|KC_F12|KC_F13|KC_F14|
|KC_F15|KC_F16|KC_F17|KC_F18|KC_F19|KC_F20|KC_F21|KC_F22|
|KC_F23|KC_F24|KC_A|KC_B|KC_C|KC_D|KC_E|KC_F|
|KC_G|KC_H|KC_I|KC_J|KC_K|KC_L|KC_M|KC_N|
|KC_O|KC_P|KC_Q|KC_R|KC_S|KC_T|KC_U|KC_V|
|KC_W|KC_X|KC_Y|KC_Z|||||

## Punctuation

|Long Name|Short Name|Description|
|---------|----------|-----------|
|KC_ENTER|KC_ENT|`Return (ENTER)`|
|KC_ESCAPE|KC_ESC|`ESCAPE`|
|KC_BSPACE|KC_BSPC|`DELETE (Backspace)`|
|KC_TAB||`Tab`|
|KC_SPACE|KC_SPC|Spacebar|
|KC_MINUS|KC_MINS|`-` and `_`|
|KC_EQUAL|KC_EQL|`=` and `+`|
|KC_LBRACKET|KC_LBRC|`[` and `{`|
|KC_RBRACKET|KC_RBRC|`]` and `}`|
|KC_BSLASH|KC_BSLS|`\` and <code>&#124;</code> |
|KC_NONUS_HASH|KC_NUHS|Non-US `#` and `~`|
|KC_NONUS_BSLASH|KC_NUBS|Non-US `\` and <code>&#124;</code> |
|KC_INT1|KC_RO|JIS `\` and <code>&#124;</code> |
|KC_INT2|KC_KANA|International216|
|KC_INT3|KC_JYEN|Yen Symbol (`¥`)|
|KC_SCOLON|KC_SCLN|`;` and `:`|
|KC_QUOTE|KC_QUOT|`‘` and `“`|
|KC_GRAVE|KC_GRV|Grave Accent and Tilde|
|KC_COMMA|KC_COMM|`,` and `<`|
|KC_DOT||`.` and `>`|
|KC_SLASH|KC_SLSH|`/` and `?`|
|KC_CAPSLOCK|KC_CAPS|Caps Lock|

## Modifiers

|Long Name|Short Name|Description|
|---------|----------|-----------|
|KC_LCTRL|KC_LCTL|LeftControl|
|KC_LSHIFT|KC_LSFT|LeftShift|
|KC_LALT||LeftAlt|
|KC_LGUI||Left GUI(Windows/Apple/Meta key)|
|KC_RCTRL|KC_RCTL|RightControl|
|KC_RSHIFT|KC_RSFT|RightShift|
|KC_RALT||RightAlt|
|KC_RGUI||Right GUI(Windows/Apple/Meta key)|
|KC_LOCKING_CAPS|KC_LCAP|Locking Caps Lock|
|KC_LOCKING_NUM|KC_LNUM|Locking Num Lock|
|KC_LOCKING_SCROLL|KC_LSCR|Locking Scroll Lock|
|KC_INT4|KC_HENK|JIS Henken|
|KC_INT5|KC_MHEN|JIS Muhenken|

## Commands

|Long Name|Short Name|Description|
|---------|----------|-----------|
|KC_PSCREEN|KC_PSCR|PrintScreen|
|KC_SCROLLLOCK|KC_SLCK|Scroll Lock|
|KC_PAUSE|KC_PAUS|Pause|
|KC_INSERT|KC_INS|Insert|
|KC_HOME||Home|
|KC_PGUP||PageUp|
|KC_DELETE|KC_DEL|Delete Forward|
|KC_END||End|
|KC_PGDOWN|KC_PGDN|PageDown|
|KC_RIGHT|KC_RGHT|RightArrow|
|KC_LEFT||LeftArrow|
|KC_DOWN||DownArrow|
|KC_UP||UpArrow|
|KC_APPLICATION|KC_APP|Application|
|KC_POWER||Power|
|KC_EXECUTE||Execute|
|KC_HELP||Help|
|KC_MENU||Menu|
|KC_SELECT||Select|
|KC_AGAIN||Again|
|KC_UNDO||Undo|
|KC_CUT||Cut|
|KC_COPY||Copy|
|KC_PASTE||Paste|
|KC_FIND||Find|
|KC_ALT_ERASE||Alternate Erase|
|KC_SYSREQ||SysReq/Attention|
|KC_CANCEL||Cancel|
|KC_CLEAR||Clear|
|KC_PRIOR||Prior|
|KC_RETURN||Return|
|KC_SEPARATOR||Separator|
|KC_OUT||Out|
|KC_OPER||Oper|
|KC_CLEAR_AGAIN||Clear/Again|
|KC_CRSEL||CrSel/Props|
|KC_EXSEL||ExSel|
|KC_SYSTEM_POWER|KC_PWR|System Power Down|
|KC_SYSTEM_SLEEP|KC_SLEP|System Sleep|
|KC_SYSTEM_WAKE|KC_WAKE|System Wake|
|KC_MAIL|KC_MAIL||
|KC_CALCULATOR|KC_CALC||
|KC_MY_COMPUTER|KC_MYCM||
|KC_WWW_SEARCH|KC_WSCH||
|KC_WWW_HOME|KC_WHOM||
|KC_WWW_BACK|KC_WBAK||
|KC_WWW_FORWARD|KC_WFWD||
|KC_WWW_STOP|KC_WSTP||
|KC_WWW_REFRESH|KC_WREF||
|KC_WWW_FAVORITES|KC_WFAV||

## Media Keys

Windows and Mac use different key codes for next track and previous track. Make sure you choose the keycode that corresponds to your OS.

|Long Name|Short Name|Description|
|---------|----------|-----------|
|KC_STOP||Stop|
|KC__MUTE||Mute (macOS)|
|KC__VOLUP||Volume Up (macOS)|
|KC__VOLDOWN||Volume Down (macOS)|
|KC_AUDIO_MUTE|KC_MUTE|Mute (Windows/macOS/Linux)|
|KC_AUDIO_VOL_UP|KC_VOLU|Volume Up (Windows/macOS/Linux)|
|KC_AUDIO_VOL_DOWN|KC_VOLD|Volume Down (Windows/macOS/Linux)|
|KC_MEDIA_NEXT_TRACK|KC_MNXT|Next Track (Windows)|
|KC_MEDIA_PREV_TRACK|KC_MPRV|Previous Track (Windows)|
|KC_MEDIA_FAST_FORWARD|KC_MFFD|Next Track (macOS)|
|KC_MEDIA_REWIND|KC_MRWD|Previous Track (macOS)|
|KC_MEDIA_STOP|KC_MSTP||
|KC_MEDIA_PLAY_PAUSE|KC_MPLY||
|KC_MEDIA_SELECT|KC_MSEL||

## Numpad

|Long Name|Short Name|Description|
|---------|----------|-----------|
|KC_NUMLOCK|KC_NLCK|Keypad Num Lock and Clear|
|KC_KP_SLASH|KC_PSLS|Keypad /|
|KC_KP_ASTERISK|KC_PAST|Keypad *|
|KC_KP_MINUS|KC_PMNS|Keypad -|
|KC_KP_PLUS|KC_PPLS|Keypad +|
|KC_KP_ENTER|KC_PENT|Keypad ENTER|
|KC_KP_1|KC_P1|Keypad 1 and End|
|KC_KP_2|KC_P2|Keypad 2 and Down Arrow|
|KC_KP_3|KC_P3|Keypad 3 and PageDn|
|KC_KP_4|KC_P4|Keypad 4 and Left Arrow|
|KC_KP_5|KC_P5|Keypad 5|
|KC_KP_6|KC_P6|Keypad 6 and Right Arrow|
|KC_KP_7|KC_P7|Keypad 7 and Home|
|KC_KP_8|KC_P8|Keypad 8 and Up Arrow|
|KC_KP_9|KC_P9|Keypad 9 and PageUp|
|KC_KP_0|KC_P0|Keypad 0 and Insert|
|KC_KP_DOT|KC_PDOT|Keypad . and Delete|
|KC_KP_EQUAL|KC_PEQL|Keypad =|
|KC_KP_COMMA|KC_PCMM|Keypad Comma|
|KC_KP_EQUAL_AS400||Keypad Equal Sign|

## Special Keys

|Long Name|Short Name|Description|
|---------|----------|-----------|
|KC_NO||Ignore this key. (NOOP) |

## Mousekey

|Long Name|Short Name|Description|
|---------|----------|-----------|
|KC_MS_UP|KC_MS_U|Mouse Cursor Up|
|KC_MS_DOWN|KC_MS_D|Mouse Cursor Down|
|KC_MS_LEFT|KC_MS_L|Mouse Cursor Left|
|KC_MS_RIGHT|KC_MS_R|Mouse Cursor Right|
|KC_MS_BTN1|KC_BTN1|Mouse Button 1|
|KC_MS_BTN2|KC_BTN2|Mouse Button 2|
|KC_MS_BTN3|KC_BTN3|Mouse Button 3|
|KC_MS_BTN4|KC_BTN4|Mouse Button 4|
|KC_MS_BTN5|KC_BTN5|Mouse Button 5|
|KC_MS_WH_UP|KC_WH_U|Mouse Wheel Up|
|KC_MS_WH_DOWN|KC_WH_D|Mouse Wheel Down|
|KC_MS_WH_LEFT|KC_WH_L|Mouse Wheel Left|
|KC_MS_WH_RIGHT|KC_WH_R|Mouse Wheel Right|
|KC_MS_ACCEL0|KC_ACL0|Mouse Acceleration 0|
|KC_MS_ACCEL1|KC_ACL1|Mouse Acceleration 1|
|KC_MS_ACCEL2|KC_ACL2|Mouse Acceleration 2|
