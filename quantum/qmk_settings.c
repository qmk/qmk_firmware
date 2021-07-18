#include "qmk_settings.h"

#include <stddef.h>
#include <string.h>

#include "progmem.h"
#include "dynamic_keymap.h"
#include "process_auto_shift.h"
#include "mousekey.h"
#include "process_combo.h"
#include "action_tapping.h"

qmk_settings_t QS;

#define DECLARE_SETTING(id, field)  { .qsid=id, .ptr=&QS.field, .sz=sizeof(QS.field) }
#define DECLARE_SETTING_CB(id, field, callback) { .qsid=id, .ptr=&QS.field, .sz=sizeof(QS.field), .cb=callback }

static void auto_shift_timeout_apply(void) {
    set_autoshift_timeout(QS.auto_shift_timeout);
}

static void mousekey_apply(void) {
    mk_delay = QS.mousekey_delay / 10;
    mk_interval = QS.mousekey_interval;
    mk_max_speed = QS.mousekey_max_speed;
    mk_time_to_max = QS.mousekey_time_to_max;
    mk_wheel_delay = QS.mousekey_wheel_delay / 10;
    mk_wheel_interval    = QS.mousekey_wheel_interval;
    mk_wheel_max_speed   = QS.mousekey_wheel_max_speed;
    mk_wheel_time_to_max = QS.mousekey_wheel_time_to_max;
}

static const qmk_settings_proto_t protos[] PROGMEM = {
   DECLARE_SETTING(1, grave_esc_override),
   DECLARE_SETTING(2, combo_term),
   DECLARE_SETTING(3, auto_shift),
   DECLARE_SETTING_CB(4, auto_shift_timeout, auto_shift_timeout_apply),
   DECLARE_SETTING(5, osk_tap_toggle),
   DECLARE_SETTING(6, osk_timeout),
   DECLARE_SETTING(7, tapping_term),
   DECLARE_SETTING(8, tapping),
   DECLARE_SETTING_CB(9, mousekey_delay, mousekey_apply),
   DECLARE_SETTING_CB(10, mousekey_interval, mousekey_apply),
   DECLARE_SETTING_CB(11, mousekey_move_delta, mousekey_apply),
   DECLARE_SETTING_CB(12, mousekey_max_speed, mousekey_apply),
   DECLARE_SETTING_CB(13, mousekey_time_to_max, mousekey_apply),
   DECLARE_SETTING_CB(14, mousekey_wheel_delay, mousekey_apply),
   DECLARE_SETTING_CB(15, mousekey_wheel_interval, mousekey_apply),
   DECLARE_SETTING_CB(16, mousekey_wheel_max_speed, mousekey_apply),
   DECLARE_SETTING_CB(17, mousekey_wheel_time_to_max, mousekey_apply),
   DECLARE_SETTING(18, tap_code_delay),
   DECLARE_SETTING(19, tap_hold_caps_delay),
};

static const qmk_settings_proto_t *find_setting(uint16_t qsid) {
    for (size_t i = 0; i < sizeof(protos)/sizeof(*protos); ++i)
        if (pgm_read_word(&protos[i].qsid) == qsid)
            return &protos[i];
    return NULL;
}

static void load_settings(void) {
    for (size_t i = 0; i < sizeof(qmk_settings_t); ++i) {
        uint8_t byte;
        byte = dynamic_keymap_get_qmk_settings(i);
        memcpy((char*)&QS + i, &byte, 1);
    }
}

static void save_settings(void) {
    for (size_t i = 0; i < sizeof(qmk_settings_t); ++i) {
        uint8_t old_byte, new_byte;
        old_byte = dynamic_keymap_get_qmk_settings(i);
        memcpy(&new_byte, (char*)&QS + i, 1);
        if (old_byte != new_byte)
            dynamic_keymap_set_qmk_settings(i, new_byte);
    }
}

void qmk_settings_init(void) {
    load_settings();
    /* execute all callbacks to initialize the settings */
    for (size_t i = 0; i < sizeof(protos)/sizeof(*protos); ++i) {
        const qmk_settings_proto_t *proto = &protos[i];
        qmk_setting_callback_t cb = pgm_read_ptr(&proto->cb);
        if (cb)
            cb();
    }
}

void qmk_settings_reset(void) {
    QS.grave_esc_override = 0;
    QS.auto_shift = 0;
    QS.auto_shift_timeout = AUTO_SHIFT_TIMEOUT;
    QS.osk_tap_toggle = ONESHOT_TAP_TOGGLE;
    QS.osk_timeout = ONESHOT_TIMEOUT;

    QS.mousekey_delay = MOUSEKEY_DELAY;
    QS.mousekey_interval = MOUSEKEY_INTERVAL;
    QS.mousekey_move_delta = MOUSEKEY_MOVE_DELTA;
    QS.mousekey_max_speed = MOUSEKEY_MAX_SPEED;
    QS.mousekey_time_to_max = MOUSEKEY_TIME_TO_MAX;
    QS.mousekey_wheel_delay = MOUSEKEY_WHEEL_DELAY;
    QS.mousekey_wheel_interval = MOUSEKEY_WHEEL_INTERVAL;
    QS.mousekey_wheel_max_speed = MOUSEKEY_WHEEL_MAX_SPEED;
    QS.mousekey_wheel_time_to_max = MOUSEKEY_WHEEL_TIME_TO_MAX;

    QS.combo_term = COMBO_TERM;
    QS.tapping_term = TAPPING_TERM;
    QS.tapping = 0;
    QS.tap_code_delay = TAP_CODE_DELAY;
    QS.tap_hold_caps_delay = TAP_HOLD_CAPS_DELAY;

    save_settings();
    /* to trigger all callbacks */
    qmk_settings_init();
}

void qmk_settings_query(uint16_t qsid_gt, void *buffer, size_t sz) {
    /* set all FFs, so caller can identify when all settings are retrieved by looking for an 0xFFFF entry */
    memset(buffer, 0xFF, sz);

    size_t buffer_offset = 0;
    for (size_t i = 0; i < sizeof(protos)/sizeof(*protos); ++i) {
        uint16_t qsid;

        /* if output buffer has no space left, bail out */
        if (buffer_offset + sizeof(qsid) > sz)
            break;

        qsid = pgm_read_word(&protos[i].qsid);
        if (qsid > qsid_gt) {
            memcpy((char*)buffer + buffer_offset, &qsid, sizeof(qsid));
            buffer_offset += sizeof(qsid);
        }
    }
}

int qmk_settings_get(uint16_t qsid, void *setting, size_t maxsz) {
    const qmk_settings_proto_t *proto = find_setting(qsid);
    if (!proto || pgm_read_word(&proto->sz) > maxsz)
        return -1;
    memcpy(setting, pgm_read_ptr(&proto->ptr), pgm_read_word(&proto->sz));
    return 0;
}

int qmk_settings_set(uint16_t qsid, const void *setting, size_t maxsz) {
    const qmk_settings_proto_t *proto = find_setting(qsid);
    if (!proto || pgm_read_word(&proto->sz) > maxsz)
        return -1;
    memcpy(pgm_read_ptr(&proto->ptr), setting, pgm_read_word(&proto->sz));
    save_settings();
    qmk_setting_callback_t cb = pgm_read_ptr(&proto->cb);
    if (cb)
        cb();
    return 0;
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    return QS.tapping_term;
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    return QS.tapping & 1;
}

bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
    return QS.tapping & 2;
}

bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    return QS.tapping & 4;
}

bool get_retro_tapping(uint16_t keycode, keyrecord_t *record) {
    return QS.tapping & 8;
}
