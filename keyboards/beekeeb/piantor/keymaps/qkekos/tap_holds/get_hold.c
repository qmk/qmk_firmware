
#include "../__init__.h"

struct HoldKey {
    int key;
    enum languages lang;
    int *hold_keys;
};

int media_hold_keys[] = { KC_DOT, KC_SLSH, KC_NO };

int ctrl_hold_keys[] = {
    TD_EXLM, TD_EQL, TD_DQT,
    TD_BSLS, TD_UNDS, TD_COLN,
    TD_ARR, TD_ECLP, TD_SALL,
    TH_NAV, KC_NO
};

int shift_hold_keys[] = {
    KC_SLSH, TD_EXLM, TD_EQL,
    TD_DQT, TD_BSLS, TD_UNDS,
    TD_COLN, TD_ARR, TD_ECLP,
    TD_SALL, KC_NO
};

int shift_eng_hold_keys[] = {
    KC_COMM, KC_DOT, KC_NO
};

struct HoldKey hold_keys[] = {
    // QWERTY
    {MHR_F, ANY, shift_hold_keys},
    {MHR_J, ANY, shift_hold_keys},

    {LHR_D, ANY, ctrl_hold_keys},
    {LHR_K, ANY, ctrl_hold_keys},

    {HR_SCLN, ANY, media_hold_keys},

    // STURDY
    {MHR_D, ANY, shift_hold_keys},
    {MHR_N, ANY, shift_hold_keys},

    {LHR_R, ANY, ctrl_hold_keys},
    {LHR_E, ANY, ctrl_hold_keys},

    {HR_I, ANY, media_hold_keys},

    // ENG ONLY
    {MHR_D, ENG, shift_eng_hold_keys},
    {MHR_N, ENG, shift_eng_hold_keys},

    // TERMINATOR
    {KC_NO, ANY, NULL},
};

bool get_hold_on_next_key(uint16_t keycode, uint16_t next_key) {
    for (int i = 0; hold_keys[i].key != KC_NO; i++)
        if (
            (hold_keys[i].lang == ANY || hold_keys[i].lang == current_lang) &&
            hold_keys[i].key == keycode
        )
            for (int j = 0; hold_keys[i].hold_keys[j] != KC_NO; j++)
                if (hold_keys[i].hold_keys[j] == next_key)
                    return true;

    return false;
}
