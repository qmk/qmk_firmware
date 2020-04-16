
#include <stdint.h>

#include "bmp_process_extended_keycode.h"
#include "bmp_custom_keycode.h"
#include "bmp_extended_keycode.h"
#include "quantum.h"
#include "timer.h"
#include "action.h"

typedef enum {
    EXKC_NONE,
    EXKC_PRESSED,
    EXKC_OVER_TAPPING_TERM,
    EXKC_PRESS_INTERRUPT,
    EXKC_RELEASE_INTERRUPT,
    EXKC_RELEASED,
    EXKC_RELEASED_IN_TAPPING_TERM,
} exkc_event_t;

typedef enum {
    EXKC_STATE_NONE,
    EXKC_STATE_ACTIVE,
    EXKC_STATE_PENDING,
    EXKC_STATE_HOLD,
    EXKC_STATE_TAPPED,
    EXKC_STATE_INACTIVE,
    EXKC_STATE_END,
} exkc_state_t;

typedef struct {
    keyevent_t   keyevent;
    exkc_event_t event;
    exkc_state_t state;
    uint16_t     last_event_time;
    bool         last_keystate;
    uint8_t      tapping_count;
} exkc_status_t;

typedef struct {
    void (*onPress)(bmp_ex_keycode_t const *const exkc, exkc_status_t const *const status);
    void (*onHold)(bmp_ex_keycode_t const *const exkc, exkc_status_t const *const status);
    void (*onTap)(bmp_ex_keycode_t const *const exkc, exkc_status_t const *const status);
    void (*onReleaseTap)(bmp_ex_keycode_t const *const exkc, exkc_status_t const *const status);
    void (*onReleaseHold)(bmp_ex_keycode_t const *const exkc, exkc_status_t const *const status);
} exkc_event_func_t;

static exkc_status_t    exkc_status[BMP_EX_KC_LEN];
extern const bmp_ex_keycode_t bmp_ex_keycodes[BMP_EX_KC_LEN];
extern const uint32_t bmp_ex_keycode_num;

extern uint16_t get_tapping_term(uint16_t keycode);

static void preprocess_exkc_common(keyevent_t const *const keyevent);
static void exkc_get_event(uint16_t input_keycode, uint16_t exkc_idx, keyevent_t *const event);
static bool process_exkc_event(uint16_t input_keycode, uint16_t exkc_idx, keyevent_t *const keyevent);

static void lte_onPress(bmp_ex_keycode_t const *const exkc, exkc_status_t const *const status);
static void lte_onHold(bmp_ex_keycode_t const *const exkc, exkc_status_t const *const status);
static void lte_onTap(bmp_ex_keycode_t const *const exkc, exkc_status_t const *const status);
static void lte_onReleaseTap(bmp_ex_keycode_t const *const exkc, exkc_status_t const *const status);
static void lte_onReleaseHold(bmp_ex_keycode_t const *const exkc, exkc_status_t const *const status);
static void tlt_onPress(bmp_ex_keycode_t const *const exkc, exkc_status_t const *const status);
static void tlt_onHold(bmp_ex_keycode_t const *const exkc, exkc_status_t const *const status);
static void tlt_onTap(bmp_ex_keycode_t const *const exkc, exkc_status_t const *const status);
static void tlt_onReleaseTap(bmp_ex_keycode_t const *const exkc, exkc_status_t const *const status);
static void tlt_onReleaseHold(bmp_ex_keycode_t const *const exkc, exkc_status_t const *const status);
static void tdd_onPress(bmp_ex_keycode_t const *const exkc, exkc_status_t const *const status);
static void tdd_onHold(bmp_ex_keycode_t const *const exkc, exkc_status_t const *const status);
static void tdd_onTap(bmp_ex_keycode_t const *const exkc, exkc_status_t const *const status);
static void tdd_onReleaseTap(bmp_ex_keycode_t const *const exkc, exkc_status_t const *const status);
static void tdd_onReleaseTap(bmp_ex_keycode_t const *const exkc, exkc_status_t const *const status);
static void tdd_onReleaseHold(bmp_ex_keycode_t const *const exkc, exkc_status_t const *const status);
static void tdh_onPress(bmp_ex_keycode_t const *const exkc, exkc_status_t const *const status);
static void tdh_onHold(bmp_ex_keycode_t const *const exkc, exkc_status_t const *const status);
static void tdh_onTap(bmp_ex_keycode_t const *const exkc, exkc_status_t const *const status);
static void tdh_onReleaseTap(bmp_ex_keycode_t const *const exkc, exkc_status_t const *const status);
static void tdh_onReleaseTap(bmp_ex_keycode_t const *const exkc, exkc_status_t const *const status);
static void tdh_onReleaseHold(bmp_ex_keycode_t const *const exkc, exkc_status_t const *const status);

static const exkc_event_func_t event_func_undefined = {.onPress = NULL, NULL, NULL, NULL, NULL};
static const exkc_event_func_t lte_event_func       = {lte_onPress, lte_onHold, lte_onTap, lte_onReleaseTap, lte_onReleaseHold};
static const exkc_event_func_t tlt_event_func       = {tlt_onPress, tlt_onHold, tlt_onTap, tlt_onReleaseTap, tlt_onReleaseHold};
static const exkc_event_func_t tdd_event_func       = {tdd_onPress, tdd_onHold, tdd_onTap, tdd_onReleaseTap, tdd_onReleaseHold};
static const exkc_event_func_t tdh_event_func       = {tdh_onPress, tdh_onHold, tdh_onTap, tdh_onReleaseTap, tdh_onReleaseHold};

static void state_transition_common(uint16_t exkc_idx);
bool bmp_process_extended_keycode(uint16_t *const p_keycode, keyrecord_t *const record);

static int pending_exkc_num = 0;
static bool pending_normal_kc_flag;
static bool process_normal_kc_flag;

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    dprintf("Process KC:%d\n", keycode);
    bool cont = bmp_process_extended_keycode(&keycode, record);
    if (!cont) {
        return false;
    }
    return process_record_user(keycode, record);
}

void bmp_check_timeout_extended_keycode() {
    uint16_t       keycode;
    exkc_status_t *p_status;

    for (int idx = 0; idx < bmp_ex_keycode_num; idx++) {
        keycode  = idx + EXKC_START;
        p_status = &exkc_status[idx];

        if (p_status->state != EXKC_STATE_NONE &&
            p_status->state != EXKC_STATE_HOLD &&
            timer_elapsed(p_status->last_event_time) >
                get_tapping_term(keycode)) {
            p_status->event = EXKC_OVER_TAPPING_TERM;
            dprintf("[EXKC]idx:%d:OVER_TT\n", idx);
        } else {
            p_status->event = EXKC_NONE;
        }
    }
}

void bmp_action_exec_impl(keyevent_t event) {
    for (int idx = 0; idx < bmp_ex_keycode_num; idx++) {
        state_transition_common(idx);
    }

    bmp_check_timeout_extended_keycode();
    preprocess_exkc_common(&event);

    for (int idx = 0; idx < bmp_ex_keycode_num; idx++) {
        state_transition_common(idx);
    }
}

 #define PENDING_BUF_MAX 16
 enum{
     PRESS_BUF,
     RELEASE_BUF
 };

 static keyevent_t pending_buffer[PENDING_BUF_MAX][2]; // use pressed as vecant flag
 static int pending_buffer_cnt[2] = {0, 0};
 static int pending_buffer_max_idx = 0;
 #define MAX(a, b) (a>b ? a: b)

 static bool send_pending_buffer(keyevent_t *event)
 {
     int idx = 0;
     if (event->pressed) {
         for (idx = 0; idx < PENDING_BUF_MAX; idx++) {
             if (pending_buffer[idx][PRESS_BUF].pressed == false) {
                 pending_buffer[idx][PRESS_BUF] = *event;
                 pending_buffer_max_idx = MAX(pending_buffer_max_idx, idx + 1);
                 pending_buffer_cnt[PRESS_BUF]++;
                 dprintf("[PDB](p) idx:%d cnt:%d max:%d\n", idx, pending_buffer_cnt[PRESS_BUF], pending_buffer_max_idx);                                                                       return true;
             }
         }
     } else {
         for (idx = 0; idx < pending_buffer_max_idx; idx++) {
             if (pending_buffer[idx][PRESS_BUF].pressed == true
                && pending_buffer[idx][RELEASE_BUF].pressed == false
                && KEYEQ(pending_buffer[idx][PRESS_BUF].key, event->key)) {
                 pending_buffer[idx][RELEASE_BUF] = *event;
                 pending_buffer[idx][RELEASE_BUF].pressed = true; // use press flag as ful    l flag
                 pending_buffer_cnt[RELEASE_BUF]++;
                 dprintf("[PDB](r) idx:%d cnt:%d max:%d\n", idx, pending_buffer_cnt[RELEASE_BUF], pending_buffer_max_idx);
                 return true;
             }
         }
     }

     // buffering failed
     return false;
 }

bool bmp_process_extended_keycode(uint16_t *const p_keycode, keyrecord_t *const record) {
    uint16_t keycode = *p_keycode;
    static bool skip_next_call = false;
    bool continue_process = true;

    if (skip_next_call) {
        return true;
    }

    for (int idx = 0; idx < bmp_ex_keycode_num; idx++) {
        exkc_get_event(keycode, idx, &record->event);
    }

    for (int idx = 0; idx < bmp_ex_keycode_num; idx++) {
        process_exkc_event(keycode, idx, &record->event);
    }

    if (pending_exkc_num > 0) {
        pending_normal_kc_flag = true;
    }

    if (pending_normal_kc_flag) {
        if ( EXKC_START >= *p_keycode || *p_keycode >= EXKC_END) {
            // queueing keyevent
            continue_process = send_pending_buffer(&record->event) ? false : true;
        }
    }

    if (pending_exkc_num <= 0) {
        pending_normal_kc_flag = false;
        if (pending_buffer_cnt[PRESS_BUF] + pending_buffer_cnt[RELEASE_BUF] > 0) {
            process_normal_kc_flag = true;
        }
    }

    if (process_normal_kc_flag) {
        // process events
        keyevent_t keyevent;
        skip_next_call = true;
        for (int idx = 0; idx < pending_buffer_max_idx; idx++) {
            if (pending_buffer[idx][PRESS_BUF].pressed) {
                keyevent = pending_buffer[idx][PRESS_BUF];
                pending_buffer[idx][PRESS_BUF].pressed = false;
                dprintf("[PDB] proc(p):%d\n", idx);
                action_exec(keyevent);
            }

            if (pending_buffer[idx][RELEASE_BUF].pressed) {
                keyevent = pending_buffer[idx][RELEASE_BUF];
                pending_buffer[idx][RELEASE_BUF].pressed = false;
                keyevent.pressed = false;
                dprintf("[PDB] proc(r):%d\n", idx);
                action_exec(keyevent);
            }
        }

        skip_next_call = false;
        process_normal_kc_flag = false;
        pending_buffer_max_idx = 0;
        pending_buffer_cnt[PRESS_BUF] = 0;
        pending_buffer_cnt[RELEASE_BUF] = 0;

        return false;
    }

    // if ( keycode < EXKC_START || keycode > EXKC_END)
    // {
    //     return true;
    // }

    return continue_process;
}

static void preprocess_exkc_common(keyevent_t const *const keyevent) {
    for (int idx = 0; idx < bmp_ex_keycode_num; idx++) {
        if (exkc_status[idx].state != EXKC_STATE_NONE && keyevent->pressed && !KEYEQ(exkc_status[idx].keyevent.key, keyevent->key)) {
            dprintf("[EXKC]idx:%d:INTERRUPTED(PRESS)\n", idx);
            exkc_status[idx].event = EXKC_PRESS_INTERRUPT;
        } else if (exkc_status[idx].state != EXKC_STATE_NONE
            && !keyevent->pressed
            && !KEYEQ(((keypos_t){.row = 255, .col =255}), keyevent->key)
            && !KEYEQ(exkc_status[idx].keyevent.key, keyevent->key)) {
            dprintf("[EXKC]idx:%d:INTERRUPTED(RELEASE)\n", idx);
            exkc_status[idx].event = EXKC_RELEASE_INTERRUPT;
        } else {
            // set EXKC_NONE in timeout checker
            // exkc_status[idx].event = EXKC_NONE;
        }
    }
}

static void exkc_get_event(uint16_t input_keycode, uint16_t exkc_idx, keyevent_t *const keyevent) {
    uint16_t       keycode  = exkc_idx + EXKC_START;
    exkc_status_t *p_status = &exkc_status[exkc_idx];

    if (p_status->event != EXKC_NONE) {
        return;
    }

    if (input_keycode == keycode) {
        if ((!p_status->last_keystate) && keyevent->pressed) {
            p_status->event    = EXKC_PRESSED;
            p_status->keyevent = *keyevent;
            dprintf("[EXKC]idx:%d:PRESSED\n", exkc_idx);

            p_status->last_keystate = keyevent->pressed;
        } else if (p_status->last_keystate && (!keyevent->pressed)) {
            if (timer_elapsed(p_status->last_event_time) < get_tapping_term(keycode)) {
                p_status->event = EXKC_RELEASED_IN_TAPPING_TERM;
                dprintf("[EXKC]idx:%d:RELEASED_IN_TT\n", exkc_idx);
            } else {
                p_status->event = EXKC_RELEASED;
                dprintf("[EXKC]idx:%d:RELEASED_OVER_TT\n", exkc_idx);
            }

            p_status->last_keystate = keyevent->pressed;
        }
    } else if (p_status->state == EXKC_STATE_NONE) {
        return;
    }

    // if (p_status->event != EXKC_NONE && p_status->event != EXKC_OVER_TAPPING_TERM) {
    //     p_status->last_event_time = timer_read();
    // }
}

static bool process_exkc_event(uint16_t input_keycode, uint16_t exkc_idx, keyevent_t *const keyevent) {
    switch (get_exkc_type(&bmp_ex_keycodes[exkc_idx])) {
        default:
            return true;
            break;
    }

    return true;
}

static exkc_event_func_t const *get_event_func(uint16_t exkc_idx) {
    switch (get_exkc_type(&bmp_ex_keycodes[exkc_idx])) {
        case NO_EXKC:
            return &event_func_undefined;
            break;
        case LTE:
            return &lte_event_func;
            break;
        case TLT:
            return &tlt_event_func;
            break;
        case TDD:
            return &tdd_event_func;
            break;
        case TDH:
            return &tdh_event_func;
            break;
        default:
            return &event_func_undefined;
            break;
    }

    return &event_func_undefined;
}

static void state_transition_common(uint16_t exkc_idx) {
    exkc_status_t *          p_status      = &exkc_status[exkc_idx];
    exkc_state_t             current_state = p_status->state;
    exkc_event_t             event         = p_status->event;
    exkc_event_func_t const *p_event_func  = get_event_func(exkc_idx);
    bmp_ex_keycode_t const * p_exkc        = &bmp_ex_keycodes[exkc_idx];

    switch (current_state) {
        case EXKC_STATE_NONE:
            if (event == EXKC_PRESSED) {
                p_status->state = EXKC_STATE_ACTIVE;
                dprintf("[EXKC]idx:%d:NONE->ACTIVE\n", exkc_idx);
                if (p_event_func->onPress != NULL) {
                    p_event_func->onPress(p_exkc, p_status);
                }
                p_status->last_event_time = timer_read();
            }
            break;

        case EXKC_STATE_ACTIVE:
            if (event == EXKC_OVER_TAPPING_TERM) {
                p_status->state = EXKC_STATE_HOLD;
                dprintf("[EXKC]idx:%d:ACTIVE->HOLD\n", exkc_idx);
                if (p_event_func->onHold != NULL) {
                    p_event_func->onHold(p_exkc, p_status);
                }
            } else if (event == EXKC_PRESS_INTERRUPT) {
                p_status->state = EXKC_STATE_PENDING;
                pending_exkc_num++;
                dprintf("[EXKC]idx:%d:ACTIVE->PENDING:%d\n", exkc_idx, pending_exkc_num);
            } else if (event == EXKC_RELEASED_IN_TAPPING_TERM) {
                p_status->state = EXKC_STATE_TAPPED;
                p_status->last_event_time = timer_read();
                p_status->tapping_count++;

                dprintf("[EXKC]idx:%d:ACTIVE->TAPPED:%d\n", exkc_idx, p_status->tapping_count);
                if (p_event_func->onTap != NULL) {
                    p_event_func->onTap(p_exkc, p_status);
                }
            }
            break;

        case EXKC_STATE_PENDING:
            if (event == EXKC_OVER_TAPPING_TERM || event == EXKC_RELEASE_INTERRUPT) {
                p_status->state = EXKC_STATE_HOLD;
                pending_exkc_num--;
                dprintf("[EXKC]idx:%d:PENDING->HOLD\n", exkc_idx);
                if (p_event_func->onHold != NULL) {
                    p_event_func->onHold(p_exkc, p_status);
                }
            }
            else if (event == EXKC_RELEASED_IN_TAPPING_TERM) {
                p_status->state = EXKC_STATE_TAPPED;
                p_status->last_event_time = timer_read();
                pending_exkc_num--;
                p_status->tapping_count++;
                dprintf("[EXKC]idx:%d:PENDING->TAPPED:%d\n", exkc_idx, p_status->tapping_count);
                if (p_event_func->onTap != NULL) {
                    p_event_func->onTap(p_exkc, p_status);
                }
            }

            break;

        case EXKC_STATE_HOLD:
            if (event == EXKC_RELEASED || event == EXKC_RELEASED_IN_TAPPING_TERM) {
                dprintf("[EXKC]idx:%d:HOLD->INACTIVE\n", exkc_idx);
                p_status->state = EXKC_STATE_INACTIVE;

                if (p_event_func->onReleaseHold != NULL) {
                    p_event_func->onReleaseHold(p_exkc, p_status);
                }
            }
            break;

        case EXKC_STATE_TAPPED:
            if (event == EXKC_PRESSED) {
                p_status->state = EXKC_STATE_ACTIVE;
                p_status->last_event_time = timer_read();
                dprintf("[EXKC]idx:%d:TAPPED->ACTIVE:%d\n", exkc_idx, p_status->tapping_count);
                if (p_event_func->onPress != NULL) {
                    p_event_func->onPress(p_exkc, p_status);
                }
            } else if (event == EXKC_OVER_TAPPING_TERM || event == EXKC_PRESS_INTERRUPT) {
                p_status->state = EXKC_STATE_INACTIVE;
                dprintf("[EXKC]idx:%d:TAPPED->INACTIVE\n", exkc_idx);

                if (p_event_func->onReleaseTap != NULL) {
                    p_event_func->onReleaseTap(p_exkc, p_status);
                }
            }
            break;

        case EXKC_STATE_INACTIVE:
            p_status->state         = EXKC_STATE_NONE;
            p_status->tapping_count = 0;
            dprintf("[EXKC]idx:%d:INACTIVE->NONE\n", exkc_idx);
            break;

        default:
            break;
    }
}

static inline void tap_code_ex(uint16_t kc, exkc_status_t const *const status) {
    if (kc < QK_MODS_MAX) {
        tap_code16(kc);
    } else if (kc >= SAFE_RANGE) {
        keyrecord_t record;
        record.event         = status->keyevent;
        record.event.pressed = true;
        process_record_user(kc, &record);
        record.event.pressed = false;
        process_record_user(kc, &record);
    }
}

static inline void register_code_ex(uint16_t kc, exkc_status_t const *const status) {
    if (kc < QK_MODS_MAX) {
        register_code16(kc);
    } else if (kc >= SAFE_RANGE) {
        keyrecord_t record;
        record.event         = status->keyevent;
        record.event.pressed = true;
        process_record_user(kc, &record);
    }
}

static inline void unregister_code_ex(uint16_t kc, exkc_status_t const *const status) {
    if (kc < QK_MODS_MAX) {
        unregister_code16(kc);
    } else if (kc >= SAFE_RANGE) {
        keyrecord_t record;
        record.event         = status->keyevent;
        record.event.pressed = false;
        process_record_user(kc, &record);
    }
}

static void lte_onPress(bmp_ex_keycode_t const *const exkc, exkc_status_t const *const status) {
    return;
    // uint8_t layer = lte_get_layer(&exkc);
    // uint16_t keycode = lte_get_tapcode(&exkc);
}

static void lte_onHold(bmp_ex_keycode_t const *const exkc, exkc_status_t const *const status) {
    uint8_t layer = lte_get_layer(exkc);
    uint16_t keycode = lte_get_tapcode(exkc);
    // uint16_t keycode = lte_get_tapcode(&exkc);
    if (status->tapping_count == 0) {
        layer_on(layer);
        clear_keyboard_but_mods();  // To avoid stuck keys
    } else {
        register_code_ex(keycode, status);
    }
}

static void lte_onTap(bmp_ex_keycode_t const *const exkc, exkc_status_t const *const status) {
    // uint8_t layer = lte_get_layer(exkc);
    uint16_t keycode = lte_get_tapcode(exkc);
    tap_code_ex(keycode, status);
}

static void lte_onReleaseTap(bmp_ex_keycode_t const *const exkc, exkc_status_t const *const status) {
    return;
}

static void lte_onReleaseHold(bmp_ex_keycode_t const *const exkc, exkc_status_t const *const status) {
    uint8_t layer = lte_get_layer(exkc);
    uint16_t keycode = lte_get_tapcode(exkc);

    if (status->tapping_count == 0) {
        layer_off(layer);
        clear_keyboard_but_mods();  // To avoid stuck keys
    } else {
        unregister_code_ex(keycode, status);
    }
}

static void tlt_onPress(bmp_ex_keycode_t const *const exkc, exkc_status_t const *const status) { return; }

static void tlt_onHold(bmp_ex_keycode_t const *const exkc, exkc_status_t const *const status) {
    uint16_t keycode = tlt_get_tapcode(exkc);
    if (status->tapping_count == 0) {
        layer_on(tlt_get_layer1(exkc));
        update_tri_layer(tlt_get_layer1(exkc), tlt_get_layer2(exkc), tlt_get_layer3(exkc));
        clear_keyboard_but_mods();  // To avoid stuck keys
    } else {
        register_code_ex(keycode, status);
    }
}

static void tlt_onTap(bmp_ex_keycode_t const *const exkc, exkc_status_t const *const status) {
    uint16_t keycode = tlt_get_tapcode(exkc);
    tap_code_ex(keycode, status);
}

static void tlt_onReleaseTap(bmp_ex_keycode_t const *const exkc, exkc_status_t const *const status) {
    return;
}

static void tlt_onReleaseHold(bmp_ex_keycode_t const *const exkc, exkc_status_t const *const status) {
    uint16_t keycode = tlt_get_tapcode(exkc);
    if (status->tapping_count == 0) {
        layer_off(tlt_get_layer1(exkc));
        update_tri_layer(tlt_get_layer1(exkc), tlt_get_layer2(exkc), tlt_get_layer3(exkc));
        clear_keyboard_but_mods();  // To avoid stuck keys
    } else {
        unregister_code_ex(keycode, status);
    }
}

static void tdd_onPress(bmp_ex_keycode_t const *const exkc, exkc_status_t const *const status) {
    return;
}

static void tdd_onHold(bmp_ex_keycode_t const *const exkc, exkc_status_t const *const status) {
    uint16_t kc = KC_NO;
    uint8_t tap = status->tapping_count % 2;

    if (tap == 0) {
        kc = tdd_get_kc1(exkc);
    }
    else if (tap == 1) {
        kc = tdd_get_kc2(exkc);
    }

    register_code_ex(kc, status);
}

static void tdd_onTap(bmp_ex_keycode_t const *const exkc, exkc_status_t const *const status) {
    uint16_t kc = KC_NO;
    uint8_t tap = status->tapping_count % 2;

    if (tap == 0) {
        kc = tdd_get_kc2(exkc);
        tap_code_ex(kc, status);
    }
    return;
}

static void tdd_onReleaseTap(bmp_ex_keycode_t const *const exkc, exkc_status_t const *const status) {
    uint16_t kc = KC_NO;
    uint8_t tap = status->tapping_count % 2;

    if (tap == 1) {
        kc = tdd_get_kc1(exkc);
        tap_code_ex(kc, status);
    }
}

static void tdd_onReleaseHold(bmp_ex_keycode_t const *const exkc, exkc_status_t const *const status) {
    uint16_t kc = KC_NO;
    uint8_t tap = status->tapping_count % 2;

    if (tap == 0) {
        kc = tdd_get_kc1(exkc);

    } else if (tap == 1) {
        kc = tdd_get_kc2(exkc);
    }

    unregister_code_ex(kc, status);
}

static void tdh_onPress(bmp_ex_keycode_t const *const exkc, exkc_status_t const *const status) {
    return;
}

static void tdh_onHold(bmp_ex_keycode_t const *const exkc, exkc_status_t const *const status) {
    uint16_t kc = KC_NO;
    kc = tdh_get_kc2(exkc);
    register_code_ex(kc, status);
}

static void tdh_onTap(bmp_ex_keycode_t const *const exkc, exkc_status_t const *const status) {
    uint16_t kc = KC_NO;
    kc = tdh_get_kc1(exkc);
    tap_code_ex(kc, status);
    return;
}

static void tdh_onReleaseTap(bmp_ex_keycode_t const *const exkc, exkc_status_t const *const status) {
}

static void tdh_onReleaseHold(bmp_ex_keycode_t const *const exkc, exkc_status_t const *const status) {
    uint16_t kc = KC_NO;
    kc = tdh_get_kc2(exkc);
    unregister_code_ex(kc, status);
}
