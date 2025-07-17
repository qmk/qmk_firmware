const uint16_t PROGMEM activate_game_layer[] = {DE_Q, DE_W, DE_Y, COMBO_END};
const uint16_t PROGMEM capslock_word_toggle[] = {HRL_BRACKETS_T, HRL_BRACKETS_N,
                                                 COMBO_END};

combo_t key_combos[] = {COMBO(activate_game_layer, TO(1)),
                        COMBO(capslock_word_toggle, CW_TOGG)};
