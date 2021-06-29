#include "qmk_settings.h"

#include <stddef.h>
#include "progmem.h"
#include <string.h>

qmk_settings_t QS;

#define DECLARE_SETTING(id, field)  { .qsid=id, .ptr=&QS.field, .sz=sizeof(QS.field) }

static const qmk_settings_proto_t protos[] PROGMEM = {
   DECLARE_SETTING(1, grave_esc_override),
};

static const qmk_settings_proto_t *find_setting(uint16_t qsid) {
    for (size_t i = 0; i < sizeof(protos)/sizeof(*protos); ++i)
        if (pgm_read_word(&protos[i].qsid) == qsid)
            return &protos[i];
    return NULL;
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
    return 0;
}
