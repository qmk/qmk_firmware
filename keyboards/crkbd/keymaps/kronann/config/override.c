#include QMK_KEYBOARD_H

const key_override_t question_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_MINUS, KC_QUES);
const key_override_t dot_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, KC_COMM);
const key_override_t comma_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, KC_SCLN);
const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);


const key_override_t left_array_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_LBRC, KC_LCBR);
const key_override_t right_array_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_RBRC, KC_RCBR);

const key_override_t backspace_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_F12, KC_BSPC);
const key_override_t mute_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_AUDIO_VOL_DOWN, KC_AUDIO_MUTE);


// _NUMBERS override
const key_override_t four_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_4, KC_DLR);
const key_override_t five_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_5, KC_PERC);
const key_override_t six_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_6, KC_CIRC);
const key_override_t seven_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_7, KC_AMPR);
const key_override_t eight_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_8, KC_ASTR);
const key_override_t nine_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_9, KC_HASH);
const key_override_t zero_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_0, KC_AT);


// This globally defines all key overrides to be used
const key_override_t *key_overrides[] = {
    &question_key_override,
    &dot_key_override,
    &comma_key_override,
    &delete_key_override,
    &backspace_key_override,
    &mute_key_override,
    &four_key_override,
    &five_key_override,
    &six_key_override,
    &seven_key_override,
    &eight_key_override,
    &nine_key_override,
    &zero_key_override,
    &left_array_key_override,
    &right_array_key_override,
};
