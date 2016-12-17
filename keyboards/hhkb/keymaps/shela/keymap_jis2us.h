#ifndef KEYMAP_JIS2US_H
#define KEYMAP_JIS2US_H

/* keymap for convert from JIS to US */
const uint16_t PROGMEM keymap_jis2us[][2] = {
    [KC_A ... KC_CAPS] = { 0x00, 0x00 }, /* default value */

    [KC_1]    = { KC_1,    KC_EXLM    }, /* 1 and ! -> 1 and ! */
    [KC_2]    = { KC_2,    KC_LBRC    }, /* 2 and " -> 2 and @ */
    [KC_3]    = { KC_3,    KC_HASH    }, /* 3 and # -> 3 and # */
    [KC_4]    = { KC_4,    KC_DLR     }, /* 4 and $ -> 4 and $ */
    [KC_5]    = { KC_5,    KC_PERC    }, /* 5 and % -> 5 and % */
    [KC_6]    = { KC_6,    KC_EQL     }, /* 6 and & -> 6 and ^ */
    [KC_7]    = { KC_7,    KC_CIRC    }, /* 7 and ' -> 7 and & */
    [KC_8]    = { KC_8,    KC_DQT     }, /* 8 and ( -> 8 and * */
    [KC_9]    = { KC_9,    KC_ASTR    }, /* 9 and ) -> 9 and ( */
    [KC_0]    = { KC_0,    KC_LPRN    }, /* 0 and (no assign) -> 0 and ) */
    [KC_MINS] = { KC_MINS, S(KC_RO)   }, /* - and = -> - and _ */
    [KC_EQL]  = { KC_UNDS, KC_COLN    }, /* ^ and ~ -> = and + */
    [KC_LBRC] = { KC_RBRC, KC_RCBR    }, /* @ and ` -> [ and { */
    [KC_RBRC] = { KC_BSLS, KC_PIPE    }, /* [ and { -> ] and } */
    [KC_BSLS] = { KC_JYEN, S(KC_JYEN) }, /* ] and } -> / and | */
    [KC_NUHS] = { KC_NUHS, S(KC_NUHS) }, /* (no assign) */
    [KC_SCLN] = { KC_SCLN, KC_QUOT    }, /* ; and + -> ; and : */
    [KC_QUOT] = { KC_AMPR, KC_AT      }, /* : and * -> ' and " */
    [KC_GRV]  = { KC_LCBR, KC_PLUS    }, /* (no assign) -> ` and ~ */
    [KC_COMM] = { KC_COMM, KC_LT      }, /* , and < -> , and < */
    [KC_DOT]  = { KC_DOT,  KC_GT      }, /* . and > -> . and > */
    [KC_SLSH] = { KC_SLSH, KC_QUES    }, /* / and ? -> / and ? */
};

#endif
