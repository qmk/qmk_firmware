/*
Its to cheat in maplestory xd.
*/
#include QMK_KEYBAORD_H
#define ______ KC_TRNS

static uint16_t key_trigger = 0;
static uint16_t key_timer = 0;

enum custom_keycodes {
  //MAPLE
  NORELOAD = SAFE_RANGE,
  HAMMER,
  SHOTGUN,
  SGPSKATE,
  FORWARDSGP,
  BACKWARDSGP,
  VERTICALFARM,
  HORIZONTALFARM
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // M-MACROS
        case NORELOAD:
            if (record->event.pressed) {
                key_trigger = 1;
            } else {
                key_trigger = 0;
            }
            break;

        case HAMMER:
            if (record->event.pressed) {
                SEND_STRING(
                    SS_DOWN(X_N)
                    SS_DOWN(X_F4)
                    SS_TAP(X_F3)
                    SS_DELAY(300)
                    SS_UP(X_N)
                    SS_DELAY(100)
                    SS_UP(X_F4)
                    SS_DELAY(5)
                    SS_TAP(X_SCLN)
                );
            }
            break;

        case SHOTGUN:
            if (record->event.pressed) {
                key_trigger = 2;
            } else {
                key_trigger = 0;
            }
            break;

        case SGPSKATE:
            if (record->event.pressed) {
                key_trigger = 5;
            } else {
                key_trigger = 0;
            }
            break; 

        case FORWARDSGP:
            if (record->event.pressed) {
                key_trigger = 6;
            } else {
                key_trigger = 0;
            }
            break; 

        case BACKWARDSGP:
            if (record->event.pressed) {
                key_trigger = 7;
            } else {
                key_trigger = 0;
            }
            break; 

        case VERTICALFARM:// on release key starts the farm or stops it
            if (record->event.pressed) {
            } else {
                if(key_trigger !=3) {
                    key_trigger= 3;
                }
                else {
                    key_trigger = 0; 
                }
            }
            break;

        case HORIZONTALFARM:
            if (record->event.pressed) {
            } else {
                if(key_trigger !=4) {
                    key_trigger= 4;
                }
                else {
                    key_trigger = 0;
                }
            }
            break;
    }
    return true;
};

void matrix_scan_user(void) { 

    switch (key_trigger)
    {
        case 1: {//NORELOAD REPEAT
            if (timer_elapsed(key_timer) > 10) {  // if timer has exceed set amount of time
                SEND_STRING(SS_TAP(X_F8)SS_DOWN(X_F4) SS_DELAY(200) SS_TAP(X_F1) SS_DELAY(300) SS_TAP(X_F2) SS_DELAY(200) SS_UP(X_F4) SS_DELAY(5) SS_TAP(X_SCLN));
                key_timer = timer_read32();  // reset the timer 
            }
        } break;

        case 2: {//SHOTGUN
            if(timer_elapsed(key_timer)>50) {
                SEND_STRING(
                    SS_DOWN(X_F4)
                    SS_DELAY(200)
                    SS_TAP(X_DOT)
                    SS_DELAY(200)
                    SS_UP(X_F4)
                    SS_DELAY(5)
                    SS_TAP(X_SCLN)
                );
                key_timer = timer_read32();  // reset the timer 
            }
        }break;

        case 3: {//VERTICALFARM
             if (timer_elapsed(key_timer) > 200) {  
                SEND_STRING(
                    SS_DOWN(X_F4) SS_DELAY(200) SS_TAP(X_F1) SS_DELAY(300) SS_TAP(X_F2) SS_DELAY(300) SS_UP(X_F4) SS_DELAY(5) SS_TAP(X_SCLN)
                    SS_DELAY(400)
                    SS_DOWN(X_F4) SS_DELAY(200) SS_TAP(X_F1) SS_DELAY(300) SS_TAP(X_F2) SS_DELAY(300) SS_UP(X_F4) SS_DELAY(5) SS_TAP(X_SCLN)
                    SS_DELAY(400)
                     SS_DOWN(X_F4) SS_DELAY(200) SS_TAP(X_F1) SS_DELAY(300) SS_TAP(X_F2) SS_DELAY(300) SS_UP(X_F4) SS_DELAY(5) SS_TAP(X_SCLN)
                    SS_DELAY(400)
                     SS_DOWN(X_F4) SS_DELAY(200) SS_TAP(X_F1) SS_DELAY(300) SS_TAP(X_F2) SS_DELAY(300) SS_UP(X_F4) SS_DELAY(5) SS_TAP(X_SCLN)
                    SS_DELAY(400)
                    
                    SS_DOWN(X_N) SS_DOWN(X_F4) SS_DELAY(100) SS_TAP(X_U) SS_DELAY(400) SS_UP(X_N) SS_DELAY(100) SS_UP(X_F4) SS_DELAY(5) SS_TAP(X_SCLN)
                    SS_DELAY(1000)
                   
                    SS_DOWN(X_RIGHT)
                    SS_DELAY(480)
                    SS_UP(X_RIGHT)   
                    SS_DELAY(500)
                    SS_DOWN(X_LEFT)
                    SS_DELAY(80)
                    SS_UP(X_LEFT)   

                    SS_DELAY(400)
                    SS_DOWN(X_F4) SS_DELAY(200)SS_TAP(X_DOT)SS_DELAY(200)SS_UP(X_F4)SS_DELAY(5)SS_TAP(X_SCLN)
                    SS_DELAY(400)
                    SS_DOWN(X_F4) SS_DELAY(200)SS_TAP(X_DOT)SS_DELAY(200)SS_UP(X_F4)SS_DELAY(5)SS_TAP(X_SCLN)
                     SS_DOWN(X_F4) SS_DELAY(200) SS_TAP(X_F1) SS_DELAY(300) SS_TAP(X_F2) SS_DELAY(300) SS_UP(X_F4) SS_DELAY(5) SS_TAP(X_SCLN)
                    SS_DELAY(400)
                     SS_DOWN(X_F4) SS_DELAY(200) SS_TAP(X_F1) SS_DELAY(300) SS_TAP(X_F2) SS_DELAY(300) SS_UP(X_F4) SS_DELAY(5) SS_TAP(X_SCLN)
                    SS_DELAY(400)
                );
                key_timer = timer_read32();  // reset the timer to 
            }
        } break;

        case 4: {  // HORIZONTAL FARM
            if (timer_elapsed(key_timer) > 1000) {
                SEND_STRING(
                    // LEFT ONCE
                    SS_DOWN(X_LEFT) SS_DELAY(100) SS_DOWN(X_F4) SS_DELAY(200) SS_TAP(X_F1) SS_DELAY(300) SS_TAP(X_F2) SS_DELAY(300) SS_UP(X_F4) SS_DELAY(5) SS_TAP(X_SCLN) SS_DELAY(200) SS_DOWN(X_F4) SS_DELAY(500) SS_UP(X_F4) SS_UP(X_LEFT) SS_TAP(X_2)
                        SS_DELAY(300)
                    SS_DOWN(X_LEFT) SS_DELAY(100) SS_DOWN(X_F4) SS_DELAY(200) SS_TAP(X_F1) SS_DELAY(300) SS_TAP(X_F2) SS_DELAY(300) SS_UP(X_F4) SS_DELAY(5) SS_TAP(X_SCLN) SS_DELAY(200) SS_DOWN(X_F4) SS_DELAY(500) SS_UP(X_F4) SS_UP(X_LEFT) SS_TAP(X_1)
                        SS_DELAY(300)
                    SS_DOWN(X_LEFT) SS_DELAY(100) SS_DOWN(X_F4) SS_DELAY(200) SS_TAP(X_F1) SS_DELAY(300) SS_TAP(X_F2) SS_DELAY(300) SS_UP(X_F4) SS_DELAY(5) SS_TAP(X_SCLN) SS_DELAY(200) SS_DOWN(X_F4) SS_DELAY(500) SS_UP(X_F4) SS_UP(X_LEFT)
                        SS_DELAY(300)
                    SS_DOWN(X_LEFT) SS_DELAY(100) SS_DOWN(X_F4) SS_DELAY(200) SS_TAP(X_F1) SS_DELAY(300) SS_TAP(X_F2) SS_DELAY(300) SS_UP(X_F4) SS_DELAY(5) SS_TAP(X_SCLN) SS_DELAY(200) SS_DOWN(X_F4) SS_DELAY(500) SS_UP(X_F4) SS_UP(X_LEFT) SS_TAP(X_1)
                        SS_DELAY(300)
                                            SS_DOWN(X_LEFT) SS_DELAY(100) SS_DOWN(X_F4) SS_DELAY(200) SS_TAP(X_F1) SS_DELAY(300) SS_TAP(X_F2) SS_DELAY(300) SS_UP(X_F4) SS_DELAY(5) SS_TAP(X_SCLN) SS_DELAY(200) SS_DOWN(X_F4) SS_DELAY(500) SS_UP(X_F4) SS_UP(X_LEFT) SS_TAP(X_2)
                        SS_DELAY(300)
                    SS_DOWN(X_LEFT) SS_DELAY(100) SS_DOWN(X_F4) SS_DELAY(200) SS_TAP(X_F1) SS_DELAY(300) SS_TAP(X_F2) SS_DELAY(300) SS_UP(X_F4) SS_DELAY(5) SS_TAP(X_SCLN) SS_DELAY(200) SS_DOWN(X_F4) SS_DELAY(500) SS_UP(X_F4) SS_UP(X_LEFT) SS_TAP(X_1)
                        SS_DELAY(300)
                    SS_DOWN(X_LEFT) SS_DELAY(100) SS_DOWN(X_F4) SS_DELAY(200) SS_TAP(X_F1) SS_DELAY(300) SS_TAP(X_F2) SS_DELAY(300) SS_UP(X_F4) SS_DELAY(5) SS_TAP(X_SCLN) SS_DELAY(200) SS_DOWN(X_F4) SS_DELAY(500) SS_UP(X_F4) SS_UP(X_LEFT)
                        SS_DELAY(300)
                    SS_DOWN(X_LEFT) SS_DELAY(100) SS_DOWN(X_F4) SS_DELAY(200) SS_TAP(X_F1) SS_DELAY(300) SS_TAP(X_F2) SS_DELAY(300) SS_UP(X_F4) SS_DELAY(5) SS_TAP(X_SCLN) SS_DELAY(200) SS_DOWN(X_F4) SS_DELAY(500) SS_UP(X_F4) SS_UP(X_LEFT) SS_TAP(X_1)
                        SS_DELAY(300)

                    // RIGHT ONCE
                    SS_DOWN(X_RIGHT) SS_DELAY(100) SS_DOWN(X_F4) SS_DELAY(200) SS_TAP(X_F1) SS_DELAY(300) SS_TAP(X_F2) SS_DELAY(300) SS_UP(X_F4) SS_DELAY(5) SS_TAP(X_SCLN) SS_DELAY(200) SS_DOWN(X_F4) SS_DELAY(500) SS_UP(X_F4) SS_UP(X_RIGHT) SS_TAP(X_2)
                        SS_DELAY(300)
                    SS_DOWN(X_RIGHT) SS_DELAY(100) SS_DOWN(X_F4) SS_DELAY(200) SS_TAP(X_F1) SS_DELAY(300) SS_TAP(X_F2) SS_DELAY(300) SS_UP(X_F4) SS_DELAY(5) SS_TAP(X_SCLN) SS_DELAY(200) SS_DOWN(X_F4) SS_DELAY(500) SS_UP(X_F4) SS_UP(X_RIGHT) SS_TAP(X_1)
                        SS_DELAY(300)
                    SS_DOWN(X_RIGHT) SS_DELAY(100) SS_DOWN(X_F4) SS_DELAY(200) SS_TAP(X_F1) SS_DELAY(300) SS_TAP(X_F2) SS_DELAY(300) SS_UP(X_F4) SS_DELAY(5) SS_TAP(X_SCLN) SS_DELAY(200) SS_DOWN(X_F4) SS_DELAY(500) SS_UP(X_F4) SS_UP(X_RIGHT)
                        SS_DELAY(300)
                    SS_DOWN(X_RIGHT) SS_DELAY(100) SS_DOWN(X_F4) SS_DELAY(200) SS_TAP(X_F1) SS_DELAY(300) SS_TAP(X_F2) SS_DELAY(300) SS_UP(X_F4) SS_DELAY(5) SS_TAP(X_SCLN) SS_DELAY(200) SS_DOWN(X_F4) SS_DELAY(500) SS_UP(X_F4) SS_UP(X_RIGHT) SS_TAP(X_1)
                        SS_DELAY(300)
                                            SS_DOWN(X_RIGHT) SS_DELAY(100) SS_DOWN(X_F4) SS_DELAY(200) SS_TAP(X_F1) SS_DELAY(300) SS_TAP(X_F2) SS_DELAY(300) SS_UP(X_F4) SS_DELAY(5) SS_TAP(X_SCLN) SS_DELAY(200) SS_DOWN(X_F4) SS_DELAY(500) SS_UP(X_F4) SS_UP(X_RIGHT) SS_TAP(X_2)
                        SS_DELAY(300)
                    SS_DOWN(X_RIGHT) SS_DELAY(100) SS_DOWN(X_F4) SS_DELAY(200) SS_TAP(X_F1) SS_DELAY(300) SS_TAP(X_F2) SS_DELAY(300) SS_UP(X_F4) SS_DELAY(5) SS_TAP(X_SCLN) SS_DELAY(200) SS_DOWN(X_F4) SS_DELAY(500) SS_UP(X_F4) SS_UP(X_RIGHT) SS_TAP(X_1)
                        SS_DELAY(300)
                    SS_DOWN(X_RIGHT) SS_DELAY(100) SS_DOWN(X_F4) SS_DELAY(200) SS_TAP(X_F1) SS_DELAY(300) SS_TAP(X_F2) SS_DELAY(300) SS_UP(X_F4) SS_DELAY(5) SS_TAP(X_SCLN) SS_DELAY(200) SS_DOWN(X_F4) SS_DELAY(500) SS_UP(X_F4) SS_UP(X_RIGHT)
                        SS_DELAY(300)
                    SS_DOWN(X_RIGHT) SS_DELAY(100) SS_DOWN(X_F4) SS_DELAY(200) SS_TAP(X_F1) SS_DELAY(300) SS_TAP(X_F2) SS_DELAY(300) SS_UP(X_F4) SS_DELAY(5) SS_TAP(X_SCLN) SS_DELAY(200) SS_DOWN(X_F4) SS_DELAY(500) SS_UP(X_F4) SS_UP(X_RIGHT) SS_TAP(X_1)
                        SS_DELAY(300)
                );
                key_timer = timer_read32();  // reset the timer to
            }
        } break;

        case 5: {
                if (timer_elapsed(key_timer) > 410) {
                SEND_STRING(
                    SS_TAP(X_F4)
                    SS_DELAY(210)
                    SS_DOWN(X_SCLN)
                    SS_TAP(X_QUOT)
                    SS_UP(X_SCLN)
                    SS_TAP(X_DOT)
                );
                  key_timer = timer_read32();  // reset the timer to
            }
            }
            break;

        case 6: {
                if (timer_elapsed(key_timer) > 10) {
                SEND_STRING(
                    SS_DOWN(X_F4)   
                    SS_DELAY(150)//50
                    SS_TAP(X_DOT)
                    SS_DELAY(150)//50
                    SS_UP(X_F4)   
                    SS_DELAY(200)
                    SS_TAP(X_SCLN)
                );
                  key_timer = timer_read32();  // reset the timer to
            }
            }
            break;

            case 7: {
                if (timer_elapsed(key_timer) > 10) {
               SEND_STRING(
                    SS_DOWN(X_F5)   
                    SS_DELAY(150)//50
                    SS_TAP(X_DOT)
                    SS_DELAY(150)//50
                    SS_UP(X_F5)   
                    SS_DELAY(200)
                    SS_TAP(X_SCLN)
                );
                  key_timer = timer_read32();  // reset the timer to
            }
            }
            break;

        default:
        break;
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_bs_rshift(
		KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,          KC_BSLS,
		KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,                   KC_ENT,
		KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_RSFT,
		KC_LCTL, KC_LGUI,                   KC_LALT, MO(1),   KC_SPC,  KC_RALT,                                     KC_RGUI, KC_RGUI, KC_RCTL
    ),
    [1] = LAYOUT_split_bs_rshift(
        QK_BOOT,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_BSPC,
        _______, _______, KC_PGUP, _______, _______, _______, _______, _______, KC_UP,   _______, KC_MPRV, KC_MPLY, KC_MNXT,          _______,
        _______, KC_HOME, KC_PGDN, KC_END,  _______, KC_VOLD, KC_VOLU, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,                   _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_PSCR, _______,
        _______, _______, _______,          _______,          _______,          _______,                   _______, _______, _______
    )
};
