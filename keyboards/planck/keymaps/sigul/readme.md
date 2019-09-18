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
- [x] add "#define TAPPING_TOGGLE 2" in config.h to enable tapping toggle with 2 taps on LOWER and RAISE keys
- [x] add tapping toggle to LOWER and RAISE keys
- [x] add "KEY_LOCK_ENABLE = yes" in rules.mk to enable caps lock
- [x] add caps lock (KC_CAPS) to RAISE layer on the shift key
- [x] Add del to a thumb layer
- [x] remove key lock because it can only be used on standard keys
- [x] Add MT(MOD_LSFT, KC_ENT) shift when pressed, enter when tapped
- [x] add home, end, pgup and pgwon on _RAISE instead of arrows
- [x] add shift enter
- [x] change LSFT to S for more legibility
- [x] MT(kc) per usare shift come tasto es: MOD_LSFT(LCAG(KC_UP)). ??? MT(MOD_LSFT,KC_CAPS)

- [ ] check audio
- [ ] Add fn behind spacebar
- [ ] add brightness up (KC_BRMU or KC_BRIU) and down (KC_BRMD or KC_BRID)
- [ ] evaluate to add mods with mod taps on the FN layer to use them for nav
- [ ] Evaluate home row lt and mt 
- [ ] add _MACRO on _FN to ouput website, email, tel, address, VAT ID credentials
- [ ] add secrets file in user space to add passwords on a password layer
- [ ] Add Hyper on ESC or TAB
- [ ] add custom keycode for full screen, half screen left, and half screen right such as ?? LCAG(KC_UP) con freccia per full screen
- [ ] consider adding LCMD_T(kc) command or key
- [ ] consider using layer to have just one keymap (see as a reference qmk_firmware/layouts/community/ortho_4x12/bredfield/)
- [ ] remap F keys upon numbers 
- [ ] LCAG(kc) con freccia per full screen 
- [ ] consider adding AUTO_SHIFT_ENABLE = yes in rules.mk to be able to send shifted key depressing a key for twice the time 
- [ ] rename ADJUST layer to SYSTEM
- [ ] revert IT_ to KC_ where not required
- [ ] add swap from Mac to Win key code on Adjust layer
