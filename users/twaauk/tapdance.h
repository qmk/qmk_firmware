#ifndef TAP_DANCE_H
#define TAP_DANCE_H

#if defined(TAP_DANCE_ENABLE)
enum {
    TD_YY_MINUS,
};

tap_dance_action_t tap_dance_actions[] = {
    [TD_YY_MINUS] = ACTION_TAP_DANCE_DOUBLE(KC_Y, KC_MINS),
};
#endif
#endif
