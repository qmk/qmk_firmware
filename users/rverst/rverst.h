#ifndef RVERST_H
#define RVERST_H

#include QMK_KEYBOARD_H

enum userspace_mode {
    MAC = 0,
    WINDOWS,
    LINUX,
    MAC_UNI,
    WINDOWS_UNI,
    LINUX_UNI,
};

enum userspace_keycodes {
    RV_NON = SAFE_RANGE,
    RV_SM0,     // set MAC
    RV_SM1,     // set WINDOWS
    RV_SM2,     // set LINUX
    RV_SM3,     // set MAC_UNI
    RV_SM4,     // set WINDOWS_UNI
    RV_SM5,     // set LINUX_UNI
    RV_SM0S,    // set MAC and save
    RV_SM1S,    // set WINDOWS and save
    RV_SM2S,    // set LINUX and save
    RV_SM3S,    // set MAC_UNI and save
    RV_SM4S,    // set WINDOWS_UNI and save
    RV_SM5S,    // set LINUX_UNI and save
    RV_AUML,    // äÄ
    RV_OUML,    // öÖ
    RV_UUML,    // üÜ
    RV_EUR,     // €
    RV_SZ,      // ß

};

typedef union {
   uint32_t raw;
   struct {
       bool    mode_1    :1;
       bool    mode_2    :1;
       bool    mode_3    :1;
   };
} userspace_config_t;

extern userspace_config_t userspace_config;

int get_mode(void);
void set_mode(int mode, bool save);
void switch_mode(int mode);

void keyboard_pre_init_keymap(void);
void keyboard_post_init_keymap(void);
void eeconfig_init_keymap(void);
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);


#endif // RVERST
