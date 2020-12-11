#ifndef RVERST_H
#define RVERST_H

#include "quantum.h"

#define LEADER_TIMEOUT 200
#ifdef LEADER_TIMEOUT
#include "leader.h"
#endif

enum os_mode {
    MAC = 0,
    LINUX,
    WINDOWS,
};

typedef union {
    uint32_t raw;
    struct {
        bool    mode_l    :1;
        bool    mode_h    :1;
    };
} userspace_config_t;

extern userspace_config_t userspace_config;

int get_mode(void);
void set_mode(int);

void keyboard_pre_init_keymap(void);
void eeconfig_init_keymap(void);
void matrix_init_keymap(void);
void matrix_scan_keymap(void);


#endif // RVERST_H
