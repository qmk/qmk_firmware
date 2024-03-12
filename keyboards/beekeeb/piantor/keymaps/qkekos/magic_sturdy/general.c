
#include "../__init__.h"

uint16_t magic_keycode_cast(uint16_t keycode, keyrecord_t *record);
uint16_t magic_double_tap_cast(uint16_t keycode, keyrecord_t *record, uint16_t magic_key);

int prev_key_timestamp;
int current_key_timestamp;

bool is_training_mode_active = true;
bool is_hard_mode_active = true;

void enable_magic_training(void) { is_training_mode_active = true; }
void enable_hard_training(void) { is_hard_mode_active = true; }

void toggle_magic_training(void) { is_training_mode_active = !is_training_mode_active; }
void toggle_hard_training(void) { is_hard_mode_active = !is_training_mode_active; }

void sequence_transform_on_missed_rule_user(const st_trie_rule_t *rule) {
    if (!is_training_mode_active) return;

    flick_leds(1.5, 250);
    uprintf("Could have used %s -> %s!\n", rule->sequence, rule->transform);

    if (is_hard_mode_active) {
        tap_code16(C(KC_BSPC));
        process_sequence_transform(C(KC_BSPC), next_record, US_AREP);
    }
}

int sturdy_pr(uint16_t keycode, keyrecord_t *record) {
    prev_key_timestamp = current_key_timestamp;
    current_key_timestamp = timer_read();

    // 🤡 For whatever the fuck reason without such code block keyboard crashes
    // This code is unreachable, condition is alwas false, but not for LTO 
    if (keycode * -1 == record->tap.count) {
        process_sequence_transform(KC_NO, record, US_AREP);
    }

    keycode = magic_keycode_cast(keycode, record);
    if (!process_sequence_transform(keycode, record, US_AREP))
        return false;

    return PR_IGNORE;
}

uint16_t magic_keycode_cast(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SMT_N:
            return record->tap.count == 2 ? DB_LTTR : keycode;

        case TH_REP:
            return record->tap.count ? US_REP : keycode;

        case OS_LSFT:
            return KC_ENT;

        case KC_1 ... KC_0:
        case S(KC_1) ... S(KC_0):
        case KC_MINUS ... KC_SLASH:
            return KC_SPC;

        case KC_B:
        case KC_Z:
        case KC_H:
        case KC_F:
        case KC_Q:
            return magic_double_tap_cast(keycode, record, DB_LTTR);
    }

    return keycode;
}

uint16_t magic_double_tap_cast(uint16_t keycode, keyrecord_t *record, uint16_t magic_key) {
    if (
        !record->event.pressed ||
        highest_layer != STURDY ||
        sequence_transform_past_keycode(0) != keycode ||
        timer_elapsed(prev_key_timestamp) > (get_tapping_term(keycode, NULL) + 50)
    ) return keycode;

    return magic_key;
}
