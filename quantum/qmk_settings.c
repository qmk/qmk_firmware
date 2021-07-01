#include "qmk_settings.h"

#include <stddef.h>
#include <string.h>

#include "progmem.h"
#include "dynamic_keymap.h"

qmk_settings_t QS;

#define DECLARE_SETTING(id, field)  { .qsid=id, .ptr=&QS.field, .sz=sizeof(QS.field) }

static const qmk_settings_proto_t protos[] PROGMEM = {
   DECLARE_SETTING(1, grave_esc_override),
   DECLARE_SETTING(2, debounce_time),
   DECLARE_SETTING(3, auto_shift),
   DECLARE_SETTING(4, auto_shift_timeout),
   DECLARE_SETTING(5, osk_tap_toggle),
   DECLARE_SETTING(6, osk_timeout),
   DECLARE_SETTING(7, tapping_term),
   DECLARE_SETTING(8, tap_hold),
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
}

void qmk_settings_reset(void) {
    /* TODO: this should take values from various #define's */
    QS.grave_esc_override = 0;
    QS.debounce_time = 5;
    QS.auto_shift = 0;
    QS.auto_shift_timeout = 175;
    QS.osk_tap_toggle = 0;
    QS.osk_timeout = 5000;
    QS.tapping_term = 200;
    QS.tap_hold = 0;

    save_settings();
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
    return 0;
}
