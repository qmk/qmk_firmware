#include "g/engine.h"
#include "process_steno.h"
#include "config_engine.h"

#define TYPING_LAYER 1

// Override layer switch code. We can always dump back down to layer 0
bool send_steno_chord_user(steno_mode_t mode, uint8_t chord[6]) {
    uint8_t gemHigher[] = {64, 0, 0, 112, 0, 0};  // (PWR | FN | ST3 | ST4)
    if (memcmp(chord, gemHigher, sizeof(chord[0]) * 6) == 0) {
        layer_on(1);
        return false;
    }
    return true;
}

C_SIZE process_engine_pre(C_SIZE cur_chord, uint16_t keycode, keyrecord_t *record) {
    // Check if we're on Typing Layer, if so do engine-y processing
    if ((layer_state & (1 << TYPING_LAYER)) != 0) return true;

    return false;
}
