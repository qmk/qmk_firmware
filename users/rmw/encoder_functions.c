// Encoder functions to mix and match!

#include "encoder_functions.h"

void enc_move_words(bool cw){ // Move whole words. Hold shift to select while moving.
    if (cw) {
        tap_code16(A(KC_RGHT));
    } else {
        tap_code16(A(KC_LEFT));
    }
}
void enc_history_scrubbing(bool cw){ // Undo/Redo.
    if (cw) {
        tap_code16(G(S(KC_Z)));
    } else {
        tap_code16(G(KC_Z));
    }
}
void enc_scrolling(bool cw){ // Scrolling.
    if (cw) {
        tap_code(KC_MS_WH_DOWN);
    } else {
        tap_code(KC_MS_WH_UP);
    }
}
void enc_scrolling_h(bool cw){ // Scrolling.
    if (cw) {
        tap_code(KC_MS_WH_RIGHT);
    } else {
        tap_code(KC_MS_WH_LEFT);
    }
}
void enc_volume_knob(bool cw){ // Volume control.
    if (cw) {
        tap_code(KC_VOLU);
    } else {
        tap_code(KC_VOLD);
    }
}
void enc_move_desktop(bool cw){ // Switch Desktops (Mac).
    if (cw) {
        tap_code16(C(KC_RIGHT));
    } else {
        tap_code16(C(KC_LEFT));
    }
}
void enc_zoom(bool cw){ // Zoom in/zoom out.
    if (cw) {
        tap_code16(G(KC_PLUS));
    } else {
        tap_code16(G(KC_MINUS));
    }
}
