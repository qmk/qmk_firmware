#include "8x18_arm.h"

void keyboard_pre_init_kb(void){
    //init the CAPS LOCK LED pin as an output
    setPinOutput(STM32LED);

// disable JTAG  to enable PB3 and PB4
    AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_JTAGDISABLE;
    AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_DISABLE;

    //call any user initialization code
    keyboard_pre_init_user();
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        writePin(STM32LED, !led_state.caps_lock);
    }
    return res;
}
