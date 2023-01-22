#include "../font/logos.c"

void oled_display(void) {

    /* Layers */
    switch (get_highest_layer(layer_state)) {

        case _BASE:
            oled_write_raw_P(qmk_logo, sizeof(qmk_logo));
            break;

        case _NUMERIC:
            oled_write_raw_P(qmk_numeric, sizeof(qmk_numeric));
            break;

        case _MOUSE:
            oled_write_raw_P(qmk_mouse, sizeof(qmk_mouse));
            break;

        case _ARROWS:
            oled_write_raw_P(qmk_arrows, sizeof(qmk_arrows));
            break;

        case _ADJUST:
            oled_write_raw_P(qmk_adjust, sizeof(qmk_adjust));
            break;

        case _FN:
            oled_write_raw_P(qmk_fn, sizeof(qmk_fn));
            break;
    }

    /* Leader */
    if (is_leader_active) {

        oled_write_raw_P(qmk_leader, sizeof(qmk_leader));
    }

    /* Modifier keys */
    if (get_mods()) {

        if (get_mods() & MOD_MASK_CTRL) {

            oled_write_char(0x01, false);
            oled_write_char(0x02, false);
            oled_write_char(0x03, false);
            oled_write_char(0x04, false);
            oled_write_char(0x05, false);

            oled_write_char(0x21, false);
            oled_write_char(0x22, false);
            oled_write_char(0x23, false);
            oled_write_char(0x24, false);
            oled_write_char(0x25, false);
        }
        if (get_mods() & MOD_BIT(KC_LALT)) {

            oled_write_char(0x41, false);
            oled_write_char(0x42, false);
            oled_write_char(0x43, false);
            oled_write_char(0x44, false);
            oled_write_char(0x45, false);

            oled_write_char(0x61, false);
            oled_write_char(0x62, false);
            oled_write_char(0x63, false);
            oled_write_char(0x64, false);
            oled_write_char(0x65, false);
        }
        if (get_mods() & MOD_BIT(KC_RALT)) {

            oled_write_char(0x81, false);
            oled_write_char(0x82, false);
            oled_write_char(0x83, false);
            oled_write_char(0x84, false);
            oled_write_char(0x85, false);

            oled_write_char(0xA1, false);
            oled_write_char(0xA2, false);
            oled_write_char(0xA3, false);
            oled_write_char(0xA4, false);
            oled_write_char(0xA5, false);
        }
        if (get_mods() & MOD_MASK_SHIFT) {

            oled_write_char(0x4B, false);
            oled_write_char(0x4C, false);
            oled_write_char(0x4D, false);
            oled_write_char(0x4E, false);
            oled_write_char(0x4F, false);

            oled_write_char(0x6B, false);
            oled_write_char(0x6C, false);
            oled_write_char(0x6D, false);
            oled_write_char(0x6E, false);
            oled_write_char(0x6F, false);
        }
        if (get_mods() & MOD_MASK_GUI) {

            oled_write_char(0x8B, false);
            oled_write_char(0x8C, false);
            oled_write_char(0x8D, false);
            oled_write_char(0x8E, false);
            oled_write_char(0x8F, false);

            oled_write_char(0xAB, false);
            oled_write_char(0xAC, false);
            oled_write_char(0xAD, false);
            oled_write_char(0xAE, false);
            oled_write_char(0xAF, false);
        }
    }
};

bool oled_task_user(void) {
    oled_display();
    return false;
}
