
#include "../__init__.h"

struct IntToInt {
    int key;
    int value;
    int power;
};

#define AltCodeKeysCount 22
#define AltLangKeysCount 6

struct IntToInt alt_lang_keys[] = {
    {'/', S(KC_BSLS)},
    {'?', S(KC_7)},
    {':', S(KC_6)},
    {'.', KC_SLSH},
    {',', S(KC_SLSH)},
    {'"', S(KC_2)},
};

struct IntToInt alt_code_keys[] = {
    {KC_SLSH, 47}, // /
    {S(KC_SLSH), 63},  // ?
    {KC_COLN, 58},  // :
    {KC_DOT, 46},  // .
    {KC_COMM, 44},  // ,
    {KC_DQT, 34},  // "

    {S(KC_2), 64},  // @
    {S(KC_3), 35},  // #
    {S(KC_4), 36},  // $
    {S(KC_6), 94},  // ^
    {S(KC_7), 38},  // &

    {KC_GRV, 96},  // `
    {S(KC_GRV), 126},  // ~
    {S(KC_BSLS), 124},  // |

    {KC_SCLN, 59},  // ;
    {KC_QUOT, 39},  // '

    {KC_LBRC, 91},  // [
    {KC_RBRC, 93},  // ]

    {KC_LCBR, 123},  // {
    {KC_RCBR, 125},  // }

    {KC_LABK, 60},  // <
    {KC_RABK, 62},  // >
};

struct IntToInt char_to_symbols[] = {
    {'/', KC_SLSH}, // /
    {'?', S(KC_SLSH)},  // ?
    {':', KC_COLN},  // :
    {'.', KC_DOT},  // .
    {',', KC_COMM},  // ,
    {'"', KC_DQT},  // "

    {'@', S(KC_2)},  // @
    {'#', S(KC_3)},  // #
    {'$', S(KC_4)},  // $
    {'^', S(KC_6)},  // ^
    {'&', S(KC_7)},  // &

    {'`', KC_GRV},  // `
    {'~', S(KC_GRV)},  // ~
    {'|', S(KC_BSLS)},  // |

    {';', KC_SCLN},  // ;
    {'\'', KC_QUOT},  // '

    {'[', KC_LBRC},  // [
    {']', KC_RBRC},  // ]

    {'{', KC_LCBR},  // {
    {'}', KC_RCBR},  // }

    {'<', KC_LABK},  // <
    {'>', KC_RABK},  // >
};

int compare(const void* a, const void* b) {
    return ((struct IntToInt*)a)->key - ((struct IntToInt*)b)->key;
}

void lang_independant_init(void) {
    qsort(alt_code_keys, AltCodeKeysCount, sizeof(struct IntToInt), compare);
    qsort(char_to_symbols, AltCodeKeysCount, sizeof(struct IntToInt), compare);
    qsort(alt_lang_keys, AltLangKeysCount, sizeof(struct IntToInt), compare);

    for (int i = 0; i < AltCodeKeysCount; i++) {
        alt_code_keys[i].power = floor(log10(alt_code_keys[i].value));
    }
}

struct IntToInt* get_int_by_key(int keycode, struct IntToInt* array, int len) {
    int left = 0, right = len - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (array[mid].key == keycode) {
            return &array[mid];
        }

        if (array[mid].key < keycode) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return NULL;
}

struct IntToInt* get_alt_code_key(int keycode) {
    return get_int_by_key(keycode, alt_code_keys, AltCodeKeysCount);
}

struct IntToInt* get_char_code_key(char key) {
    return get_int_by_key(key, char_to_symbols, AltCodeKeysCount);
}

struct IntToInt* get_alt_lang_key(char key) {
    return get_int_by_key(key, alt_lang_keys, AltLangKeysCount);
}

void send_alt_code(int code, int power) {
    execute_without_mods(
        register_code(KC_LALT);

        for (int i = power; i >= 0; i--) {
            int digit = code / pow(10, i);
            code %= (int) pow(10, i);

            tap_code(digit == 0 ? KC_P0 : (KC_P1 + digit - 1));
        }

        unregister_code(KC_LALT);
    );
}

const int override_repeat_delay = 500;
const int base_override_repeat_rate = 25;

int override_repeat_rate = base_override_repeat_rate;
int current_key = KC_NO;
deferred_token override_repeat_token = INVALID_DEFERRED_TOKEN;

uint32_t restore_base_override_repeat_rate(uint32_t trigger_time, void *cb_arg) {
    override_repeat_rate = base_override_repeat_rate;
    return 0;
}

uint32_t override_repeat_cb(uint32_t trigger_time, void *cb_arg) {
    struct IntToInt *alt_code_key = (struct IntToInt *)cb_arg;
    send_alt_code(alt_code_key->value, alt_code_key->power);

    if (override_repeat_rate == override_repeat_delay)
        defer_exec(override_repeat_delay - base_override_repeat_rate, restore_base_override_repeat_rate, NULL);

    return override_repeat_rate;
}

int handle_override(int keycode) {
    if (is_shift_held()) keycode = S(keycode);
    return keycode;
}

int lang_independant_pr(uint16_t keycode, keyrecord_t *record) {
    if (
        (
            is_alpha_layer_on() &&
            record->event.type != COMBO_EVENT &&
            record->event.pressed
        ) || current_lang == ENG
    ) return PR_IGNORE;

    int primary_key = keycode;
    keycode = handle_override(keycode);

    struct IntToInt *alt_code_key = get_alt_code_key(keycode);

    if (alt_code_key != NULL) {
        override_repeat_rate = override_repeat_delay;

        if (record->event.pressed) {
            current_key = primary_key;

            cancel_deferred_exec(override_repeat_token);
            send_alt_code(alt_code_key->value, alt_code_key->power);

            override_repeat_rate = base_override_repeat_rate;
            override_repeat_token = defer_exec(override_repeat_delay, override_repeat_cb, (void *)alt_code_key);
        } else if (current_key == primary_key) {
            cancel_deferred_exec(override_repeat_token);
            current_key = KC_NO;
        } else return PR_IGNORE;

        return PR_FALSE;
    } else if (!record->event.pressed && current_key == primary_key) {
        cancel_deferred_exec(override_repeat_token);
        current_key = KC_NO;
    }

    return PR_IGNORE;
}

void tap_lang_independant_key(uint16_t keycode) {
    keycode = handle_override(keycode);

    struct IntToInt *alt_code_key = get_alt_code_key(keycode);

    if (alt_code_key != NULL)
        send_alt_code(alt_code_key->value, alt_code_key->power);

    else tap_code16(keycode);
}

const char* charToString(char c) {
    static char str[2];

    str[0] = c;
    str[1] = '\0';

    return str;
}

void send_lang_independant_string_core(const char *str) {
    if (current_lang == ENG) {
        SEND_STRING(str);
        return;
    }

    struct IntToInt *char_code;

    for (int i = 0; str[i] != '\0'; i++) {
        char_code = get_alt_lang_key(str[i]);

        if (char_code != NULL) {
            tap_code16(char_code->value);
            continue;
        }

        char_code = get_char_code_key(str[i]);

        if (char_code != NULL) tap_lang_independant_key(char_code->value);
        else if ((65 <= str[i] && str[i] <= 90) || (97 <= str[i] && str[i] <= 99)) send_alt_code(str[i], 1);
        else if (100 <= str[i] && str[i] <= 122) send_alt_code(str[i], 2);
        else SEND_STRING(charToString(str[i]));
    }
}

void send_lang_independant_string(const char *str) {
    execute_without_mods(send_lang_independant_string_core(str));
}
