#include "jotanck.h"

void keyboard_pre_init_kb(void) {
    setPinOutput(JOTANCK_LED1);
    setPinOutput(JOTANCK_LED2);
    
    keyboard_pre_init_user();
}
