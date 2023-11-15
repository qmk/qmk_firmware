
#include "../__init__.h"

int get_combo_action(int combo_index) {
    for (int i = 0; combo_actions_keys[i][0] != -1; i++)
        if (combo_actions_keys[i][0] == combo_index)
            return combo_actions_keys[i][1];

    return KC_NO;
}

uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    return COMBO_TERM + (combo->keys[2] == KC_NO ? 0 : 20);
}
