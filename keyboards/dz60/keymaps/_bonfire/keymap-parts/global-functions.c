/**
 * Key Mods Function
 *
 * This turns 3d, 4b, 4d and 4e into arrow keys when tapped,
 * and RSFT, RCTL, RGUI and HYPR, respectively.
 *
 * @DEPRECATED -- view: https://docs.qmk.fm/#/custom_quantum_functions
 */
const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_MODS_TAP_KEY(MOD_RSFT, KC_UP),
    [1] = ACTION_MODS_TAP_KEY(MOD_RCTL, KC_DOWN),
    [2] = ACTION_MODS_TAP_KEY(MOD_RGUI, KC_LEFT),
    [3] = ACTION_MODS_TAP_KEY(MOD_HYPR, KC_RIGHT),
};
