#pragma once

void matrix_init_user(void) {
#ifdef STENO_ENABLE
    steno_set_mode(STENO_MODE_BOLT);  // or STENO_MODE_GEMINI
#endif
}
