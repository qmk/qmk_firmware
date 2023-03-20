#include "i2c_master.h"

void keyboard_post_init_user(void) {
    i2c_init();
}
