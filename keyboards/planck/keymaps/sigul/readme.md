# An ANSI Italian Planck Layout
by Silvio Gulizia

- [x] add layer _FN with F keys and VI navigation
- [x] add layer _MOUSE with mouse keys
- [x] add "MOUSEKEY_ENABLE = yes" in rules.mk to enable mouse keys
- [x] add definition to control the mouse movementes in config.h
- [x] add layer _NUMPAD to have a numpad
- [x] add keycode NUMPAD to toggle _NUMPAD
- [x] modify layer ADJUST to simplify remembering commands
- [x] add custom keycodes ESCFN and TABFN on QUERTY to add the ability to use arrows with hjkl by activating layer FN when held with the definition LT(_FN,KC_ESC) and LT(_FN, KC_TAB)
- [x] added "#define USB_MAX_POWER_CONSUMPTION 100" in config.h to use the keyboard with the iPad
- [x] add "#define TAPPING_TOGGLE 3" in config.h to enable tapping toggle with 3 taps on LOWER, RAISE and MOUSE  keys
- [x] add tapping toggle to LOWER, RAISE and MOUSE  keys
- [x] add "KEY_LOCK_ENABLE = yes" in rules.mk to enable caps lock
- [x] add caps lock (KC_CAPS) to RAISE layer on the shift key
- [x] Add del to a thumb layer
- [x] remove key lock because it can only be used on standard keys
- [x] Add MT(MOD_LSFT, KC_ENT) shift when pressed, enter when tapped
- [x] add home, end, pgup and pgwon on _RAISE instead of arrows
- [x] add shift enter
- [x] change LSFT to S for more legibility
- [x] MT(kc) per usare shift come tasto es: MOD_LSFT(LCAG(KC_UP)). ??? MT(MOD_LSFT,KC_CAPS)
- [x] add macros on _FN to ouput website, email, tel, address, VAT ID credentials
- [x] remap F keys upon numbers on _FN
- [x] check audio functionality
- [x] Add LT(_FN, IT_D) on D on the Querty layer

- [ ] Add Hyper on ESC or TAB to be able to use it for custom keyboard shortcuts
- [ ] consider using layer configuration to have just one keymap (see as a reference qmk_firmware/layouts/community/ortho_4x12/bredfield/)
- [ ] add brightness up (KC_BRMU or KC_BRIU) and down (KC_BRMD or KC_BRID)

- [ ] add secrets file in user space to add passwords on a password layer
- [ ] consider adding midi on the planck
- [ ] consider adding AUTO_SHIFT_ENABLE = yes in rules.mk to be able to send shifted key depressing a key for twice the time 
- [ ] revert IT_ to KC_ where not required
- [ ] add swap from Mac to Win key code on Adjust layer
- [ ] evaluate to add auto shift 
