# An ANSI Italian Planck Layout
by Silvio Gulizia

The idea behind this layout is to have an American Keyboard with accented vowels (for Italian) to avoid switching language on the Mac every time you switch form English to Italian and being able to get the advantages that comes with the American (ANSI) keyboard when you write in English, code, or just want to use keybaord shorcuts (most of which are based on the American Keybaord).

Some things I did, useful to you fi you want to have a look to the scheme or even replicate it for your language.

- [x] add layer _FN with F keys and VI navigation
- [x] add layer _MOUSE with mouse keys
- [x] add "MOUSEKEY_ENABLE = yes" in rules.mk to enable mouse keys (moved to users/sigul/rules.mk)
- [x] add definition to control the mouse movementes in config.h (moved to users/sigul/config.h)
- [x] add layer _NUMPAD to have a numpad
- [x] add keycode NUMPAD to toggle _NUMPAD (moved in users/sigul/sigul.h)
- [x] modify layer ADJUST to simplify remembering commands (Reset on R, Eeprom reset on E and so)
- [x] add custom keycodes ESCFN and TABFN on QUERTYi (default) layer to add the ability to use arrows with hjkl by activating layer FN when held with the definition LT(_FN,KC_ESC) and LT(_FN, KC_TAB)
- [x] added "#define USB_MAX_POWER_CONSUMPTION 100" in config.h to use the keyboard with the iPad (moved to users/sigul/config.h)
- [x] add "#define TAPPING_TOGGLE 3" in config.h to enable tapping toggle with 3 taps on LOWER and RAISE (moved to users/sigul/config.h)
- [x] add tapping toggle to LOWER, RAISE and MOUSE  keys
- [x] add caps lock (KC_CAPS) to RAISE layer on the shift key
- [x] Add del to a thumb layer
- [x] Add MT(MOD_LSFT, KC_ENT) shift when pressed, enter when tapped
- [x] add home, end, pgup and pgwon on _RAISE instead of arrows
- [x] change LSFT to S for more legibility
- [x] add secrets on RAISE to be able to output personal data such as email, phone number, credit cards number...
- [x] remap F keys upon numbers on _FN

To DO
- [ ] Add Hyper on ESC or TAB to be able to use it for custom keyboard shortcuts
- [ ] consider using layer configuration to have just one keymap (see as a reference qmk_firmware/layouts/community/ortho_4x12/bredfield/)
- [ ] add brightness up (KC_BRMU or KC_BRIU) and down (KC_BRMD or KC_BRID)
- [ ] consider adding AUTO_SHIFT_ENABLE = yes in rules.mk to be able to send shifted key depressing a key for twice the time 
- [ ] revert IT_ to KC_ where not required
