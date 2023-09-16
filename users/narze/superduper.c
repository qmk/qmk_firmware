#include "superduper.h"
#include "eeconfig.h"
#include "eeprom.h"
#include "keymap_colemak.h"

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

combo_t key_combos[] = {
    [CB_SUPERDUPER] = COMBO_ACTION(superduper_combos[_QWERTY]),
};

volatile bool superduper_enabled = true;

const uint16_t PROGMEM empty_combo[] = {COMBO_END};

bool toggle_superduper_mode(void) {
    superduper_enabled = !superduper_enabled;

    if (superduper_enabled) {
        set_superduper_key_combos();
    } else {
        clear_superduper_key_combos();
    }

    return superduper_enabled;
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
