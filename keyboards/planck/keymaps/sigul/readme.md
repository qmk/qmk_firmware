# The ANSI Italian Planck Layout
by Silvio Gulizia

- [x] add layer _FN with F keys and VI navigation
- [x] add layer _MOUSE with mouse keys
- [x] add "MOUSEKEY_ENABLE = yes" in rules.mk to enable mouse keys
- [x] add layer _NUMPAD to have a numpad
- [x] add keycode NUMPAD to toggle _NUMPAD
- [x] modify layer ADJUST to simplify remembering commands
- [x] add custom keycodes ESCFN and TABFN on QUERTY to add the ability to use arrows with hjkl by activating layer FN when held with the definition LT(_FN,KC_ESC) and LT(_FN, KC_TAB)
- [x] added "#define USB_MAX_POWER_CONSUMPTION 100" in config.h to use the keyboard with the iPad
- [x] add "#define TAPPING_TOGGLE 2" to config.h to enable tapping toggle with 2 taps on LOWER and RAISE keys
- [ ] add toggle function for LOWER and RAISE on FN layer
- [ ] add tapping toggle to LOWER and RAISE keys
- [x] add "KEY_LOCK_ENABLE = yes" in rules.mk to enable caps lock
- [ ] add caps lock (KC_LOCK) to LOWER layer on the shift key
- [ ] add tap toggle for NUMPAD
- [ ] add layer _MACRO
- [ ] add macro to ouput website, email, tel, address, VAT ID credentials
- [ ] add secrets file in user space to add passwords on a password layer
- [ ] add home, end, pgup and pgwon on _LOWER for arrows
- [ ] move media keys on _RAISE
- [ ] add space cadet shift and shift enter
- [ ] revert IT_ to KC_ where not required
- [ ] add custom keycode for full screen, half screen left, and half screen right
- [ ] rename ADJUST layer to SYSTEM

OLD NOTES
- [ ] remove key lock because it can only be used on standard keys
- [ ] LCAG(KC_UP) con freccia per full screen
- [ ] LCMD_T(kc) command or key
- [ ] verify if SFT_T(KC_CAPSLOCK) shift when held and caps lock when tapped is a bettere option
- [ ] add brightness up (KC_BRMU or KC_BRIU) and down (KC_BRMD or KC_BRID)
