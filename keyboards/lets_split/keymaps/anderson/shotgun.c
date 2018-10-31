#include "shotgun.h"

#define FOR_CHORDS int c = chords_size; while (c--)
#define FOR_CHORD_KEYS int k = 2; while(k--)

void shotgun_register(uint16_t key) {
    FOR_CHORDS {
        FOR_CHORD_KEYS {
            if (chords[c].keys[k] == key) {
                chords[c].keys[k].pressed = timer_read();
            }
        }
    }
}

void shotgun_unregister(uint16_t key) {
    FOR_CHORDS {
        FOR_CHORD_KEYS {
            if (chords[c].keys[k] == key) {
                chords[c].keys[k].pressed = 0;
            }
        }
    }
}

void shotgun_process(void) {
    FOR_CHORDS {
        FOR_CHORD_KEYS {
        }
    }
}
