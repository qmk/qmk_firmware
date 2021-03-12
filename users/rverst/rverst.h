#ifndef RVERST_H
#define RVERST_H

#include QMK_KEYBOARD_H

enum userspace_mode {
    MAC = 0,
    WINDOWS,
    MAC_UNI,
    WINDOWS_UNI,
    LINUX_UNI,
};

enum userspace_keycodes {
    RV_NON = SAFE_RANGE,
    RV_SM0,   // set Mac Unicode mode
    RV_SM1,   // set Window Unicode mode
    RV_SM2,   // set Linux Unicode mode
    RV_SM3,   // set Mac lagecy mode
    RV_SM4,   // set Windows legacy mode
    RV_SM0S,  // set Mac Unicode mode and save
    RV_SM1S,  // set Windows Unicode mode and save
    RV_SM2S,  // set Linux Unicode and save
    RV_SM3S,  // set Mac legacy mode
    RV_SM4S,  // set Windows legacy and save
    RV_SAYM,  // say mode
    RV_AUML,  // äÄ
    RV_OUML,  // öÖ
    RV_UUML,  // üÜ
    RV_EUR,   // €
    RV_SZ,    // ß§
    RV_TM,    // ™
    RV_RT,    // ®
    RV_CC,    // ©
    RV_DEG,   // °
    RV_SNAP,  // Screenshot
    RV_PM,    // ±
    RV_UNEQ,  // ≠
    RV_SUP1,  // ¹
    RV_SUP2,  // ²
    RV_SUP3,  // ³

};

typedef union {
    uint32_t raw;
    struct {
        bool mode_1 : 1;
        bool mode_2 : 1;
        bool mode_3 : 1;
    };
} userspace_config_t;

extern userspace_config_t userspace_config;

int  get_mode(void);
void set_mode(int mode, bool save);
void switch_mode(int mode);
bool is_unicode(int mode);

void keyboard_pre_init_keymap(void);
void keyboard_post_init_keymap(void);
void eeconfig_init_keymap(void);
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);

#endif  // RVERST
