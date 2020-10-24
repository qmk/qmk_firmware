#include "ergoluna.h"
void keyboard_pre_init_kb(void){
        writePinHigh(F0);
        keyboard_pre_init_user();
}
