#include "knight.h"
void matrix_init_kb(void) {
    setPinOutput(D1);
    setPinOutput(E2);
    matrix_init_user();
};
bool led_update_kb(led_t led_state) {
    if(led_update_user(led_state)) {
        if (led_state.num_lock) {
            writePinLow(D1);
        } else {
            writePinHigh(D1);
        }
        if (led_state.caps_lock) {
            writePinLow(E2);
        } else {
            writePinHigh(E2);
        }
        return true;
    }
}
