#include "sweet16.h"


enum layers {
 num,
 media,
 hacking
};

enum custom_keycodes {
  MAC_ALERT = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	   /* Default Layer
     |--------+---------+---+---|
     |   7    |    8    | 9 | / |
     |--------+---------+---+---|
     |   4    |    5    | 6 | * |
     |--------+---------+---+---|
     |   1    |    2    | 3 | - |
     |--------+---------+---+---|
     | hack/0 | media/. |Ent| + |
     |--------+---------+---+---|
    */	
    [num] = LAYOUT_ortho_4x4(
        KC_P7,				KC_P8,				KC_P9,		KC_PSLS,
        KC_P4,				KC_P5,				KC_P6,		KC_PAST,
        KC_P1,				KC_P2,				KC_P3,		KC_PMNS,
        LT(hacking, KC_P0),	LT(media, KC_DOT),	KC_PENT,	KC_PPLS
    ),    
    	   /* Media Layer
     |-------+------------+--+-----------|
     | Mute  | PLAY/PAUSE |  |           |
     |-------+------------+--+-----------|
     | VOLUP | VOLDN      |  |           |
     |-------+------------+--+-----------|
     | PREV  | NEXT       |  |           |
     |-------+------------+--+-----------|
     |       |            |  | POWER OFF |
     |-------+------------+--+-----------|
    */	
    [media] = LAYOUT_ortho_4x4(
        KC_MUTE, KC_MPLY, KC_NO, KC_NO,
        KC_VOLU, KC_VOLD, KC_NO, KC_NO,
        KC_MPRV, KC_MNXT, KC_NO, KC_NO,
        KC_NO,   KC_NO,	  KC_NO, KC_PWR
    ),  
	   /* HACKING Layer
     |--------------+--+--+-------|
     | script alert |  |  |       |
     |--------------+--+--+-------|
     |              |  |  |       |
     |--------------+--+--+-------|
     |              |  |  |       |
     |--------------+--+--+-------|
     |              |  |  | RESET |
     |--------------+--+--+-------|
    */
    
    [hacking] = LAYOUT_ortho_4x4(
        MAC_ALERT,	KC_NO,	KC_NO,	KC_NO,
        KC_NO,		KC_NO,	KC_NO,	KC_NO,
        KC_NO,		KC_NO,	KC_NO,	KC_NO,
        KC_NO,		KC_NO,	KC_NO,	RESET
    )

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MAC_ALERT:
            if (record->event.pressed) {
                SEND_STRING("<script>alert(1)</script>");
            }
            return false;
            break;
    }
    return true;
}


