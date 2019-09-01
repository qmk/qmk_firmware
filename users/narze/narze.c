#include "narze.h"
#include "eeconfig.h"
#include "keymap_colemak.h"

// Mod taps does not work with shifted keycodes eg. SFT_T(KC_LPRN)
// So a macro is needed
// Implementation copied from process_space_cadet

static uint8_t mtwm_last = 0;
static uint16_t mtwm_timer = 0;
static uint8_t mtwm_mods = 0;

void perform_mod_tap_with_mod(keyrecord_t *record, uint8_t holdMod, uint8_t tapMod, uint8_t keycode) {
    if (record->event.pressed) {
        mtwm_last  = holdMod;
        mtwm_timer = timer_read();
        mtwm_mods = get_mods();

        if (IS_MOD(holdMod)) {
            register_mods(MOD_BIT(holdMod));
        }
    } else {
        if (mtwm_last == holdMod && timer_elapsed(mtwm_timer) < TAPPING_TERM) {
            if (holdMod != tapMod) {
                if (IS_MOD(holdMod)) {
                    unregister_mods(MOD_BIT(holdMod));
                }
                if (IS_MOD(tapMod)) {
                    register_mods(MOD_BIT(tapMod));
                }
            }
            set_weak_mods(mtwm_mods);
            tap_code(keycode);
            clear_weak_mods();

            if (IS_MOD(tapMod)) {
                unregister_mods(MOD_BIT(tapMod));
            }
        } else {
            if (IS_MOD(holdMod)) {
                unregister_mods(MOD_BIT(holdMod));
            }
        }
    }
}

// SuperDuper

#define SUPERDUPER_COMBO_COUNT 3
#define EECONFIG_SUPERDUPER_INDEX (uint8_t *) 19

enum process_combo_event {
  CB_SUPERDUPER,
};

enum supported_layers {
  _QWERTY,
  _COLEMAK,
  _QWOC
};

const uint16_t PROGMEM superduper_combos[SUPERDUPER_COMBO_COUNT][3] = {
  [_QWERTY] = {KC_S, KC_D, COMBO_END},
  [_COLEMAK] = {KC_R, KC_S, COMBO_END},
  [_QWOC] = {CM_S, CM_D, COMBO_END},
};

combo_t key_combos[COMBO_COUNT] = {
  [CB_SUPERDUPER] = COMBO_ACTION(superduper_combos[_QWERTY]),
};

volatile bool superduper_enabled = true;

const uint16_t empty_combo[] = {COMBO_END};

void toggle_superduper_mode(void) {
    superduper_enabled = !superduper_enabled;

    if (superduper_enabled) {
      set_superduper_key_combos();
    } else {
      clear_superduper_key_combos();
    }
}

void set_superduper_key_combo_layer(uint16_t layer) {
    key_combos[CB_SUPERDUPER].keys = superduper_combos[layer];
    eeprom_update_byte(EECONFIG_SUPERDUPER_INDEX, layer);
}

void set_superduper_key_combos(void) {
  uint8_t layer = eeprom_read_byte(EECONFIG_SUPERDUPER_INDEX);

  switch (layer) {
    case _QWERTY:
    case _COLEMAK:
    case _QWOC:
      key_combos[CB_SUPERDUPER].keys = superduper_combos[layer];
      break;
  }
}

void clear_superduper_key_combos(void) {
  key_combos[CB_SUPERDUPER].keys = empty_combo;
}
