LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    SEQ_ONE_KEY(TD(APMR_PIPE)) {
        register_code(KC_LCTL);
        register_code(KC_LSFT);
        register_code(KC_U);

        unregister_code(KC_U);
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
    }
}
