#include "rverst.h"

int get_mode(void) {

    if (userspace_config.mode_l && !userspace_config.mode_h) {
        return LINUX;
    } else if (!userspace_config.mode_l && userspace_config.mode_h) {
        return WINDOWS;
    }

    return MAC;
}

void set_mode(int mode) {

    if (mode == get_mode()) {
        return;
    }

    if (mode == LINUX) {
        userspace_config.mode_l = true;
        userspace_config.mode_h = false;
    } else if (mode == WINDOWS) {
        userspace_config.mode_l = false;
        userspace_config.mode_h = true;
    } else {
        userspace_config.mode_l = false;
        userspace_config.mode_h = false;
    }

    // todo: play sound?
    // todo: set underglow color?

    eeconfig_update_user(userspace_config.raw);
}

//**********************
// keyboard_pre_init
//**********************

__attribute__((weak))
void keyboard_pre_init_keymap(void);

void keyboard_pre_init_user(void) {
    userspace_config.raw = eeconfig_read_user();
    keyboard_pre_init_keymap();
}

//**********************
// eeconfig_init
//**********************

__attribute__((weak))
void eeconfig_init_keymap(void);

void eeconfig_init_user(void) {

    userspace_config.raw = 0;

    eeconfig_update_user(userspace_config.raw);
    eeconfig_init_keymap();
    keyboard_init();
}


//**********************
// matrix_init
//**********************

__attribute__((weak))
void matrix_init_keymap(void) {}

void matrix_init_user(void) {

    matrix_init_keymap();
}


//**********************
// matrix_scan
//**********************

__attribute__((weak))
void matrix_scan_keymap(void) {}

void matrix_scan_user(void) {
#ifdef LEADER_TIMEOUT
    matrix_scan_leader();
#endif
    matrix_scan_keymap();
}
