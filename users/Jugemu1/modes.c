#include "modes.h"
#include "eeconfig.h"
#include "eeprom.h"

volatile modes current_mode = MODE_WINDOWS;

const char *get_current_mode_name(void){
    switch(current_mode){
        case MODE_WINDOWS:
            return "Windows";
        case MODE_MAC:
            return "Mac";
        default:
            return "Unknown";
    }
}

modes get_mode(void){
    current_mode = eeprom_read_byte(EECONFIG_MODE_INDEX);
    return current_mode;
}

void set_mode(modes new_mode){
    current_mode = new_mode;
    eeprom_update_byte(EECONFIG_MODE_INDEX, new_mode);
}

void cycle_mode(void){
    modes new_mode = current_mode + 1;
    if(new_mode >= MODE_LAST){       //use first
        new_mode = (modes)0;
    }
    set_mode(new_mode);
}

void init_mode(void){
    modes mode = get_mode();
    set_mode(mode);
}
