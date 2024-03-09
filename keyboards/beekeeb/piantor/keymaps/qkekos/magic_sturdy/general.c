
#include "../__init__.h"

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

int trigger_magic_key(uint16_t magic_key, keyrecord_t *record) {
    if (!process_sequence_transform(magic_key, record, US_AREP))
        return false;

    return PR_IGNORE;
}

int sturdy_pr(uint16_t keycode, keyrecord_t *record) {
    prev_key_timestamp = current_key_timestamp;
    current_key_timestamp = timer_read();

    switch (keycode) {
        case SMT_N:
            if (record->tap.count != 2) break;
            return trigger_magic_key(DB_LTTR, record);

        case KC_B:
        case KC_Z:
        case KC_H:
        case KC_F:
        case KC_Q:
            return process_double_tap(keycode, record, DB_LTTR);

        case LT_I:
            if (record->event.pressed && record->tap.count == 2 && sequence_transform_past_keycode(1) != KC_V) {
                tap_code16(KC_BSPC);
                add_weak_mods(MOD_BIT(KC_LSFT));
                return PR_IGNORE;
            }

            break;

        case TH_REP:
            if (record->tap.count) keycode = US_REP;
            break; 
    }

    if (!process_sequence_transform(keycode, record, US_AREP))
        return false;

    return PR_IGNORE;
}

int process_double_tap(uint16_t keycode, keyrecord_t *record, uint16_t magic_key) {
    if (
        !record->event.pressed ||
        highest_layer != STURDY ||
        sequence_transform_past_keycode(0) != keycode ||
        timer_elapsed(prev_key_timestamp) > (get_tapping_term(keycode, NULL) + 50)
    ) {
        if (!process_sequence_transform(keycode, record, US_AREP))
            return false;

        return PR_IGNORE;
    }

    return trigger_magic_key(magic_key, record);
}
