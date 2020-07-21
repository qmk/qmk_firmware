#include "taphold.h"

bool taphold_process(uint16_t keycode, keyrecord_t *record) {
    for (int i = 0; i < taphold_config_size; i++) {
        taphold_t *config = &taphold_config[i];
        if (config->key == keycode && record->event.pressed) {
            if (config->mode == TAPHOLD_LAYER) {
                layer_on(config->longAction);
            } else {
                register_code(config->longAction);
            }
            config->time = timer_read32();
            config->keypos = record->event.key;
            return false;
        } else if (KEYEQ(record->event.key, config->keypos) && !record->event.pressed) {
            if (config->mode == TAPHOLD_LAYER) {
                layer_off(config->longAction);
            } else {
                unregister_code(config->longAction);
            }
            if (timer_elapsed32(config->time) < taphold_timeout) {
                tap_code(config->shortAction);
            }
            config->keypos.row = 255;
            return false;
        }
    }
    return true;
}
