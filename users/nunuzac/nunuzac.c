#include "nunuzac.h"

static os_type current_os = WLX;

os_type get_current_os(void) {
    return current_os;
}

void set_current_os(os_type val) {
    current_os = val;
}

uint16_t get_os_shortcut(shortcut_t intended) {
    switch (intended) {
        case COPY:
            if(current_os == OSX)
                return QK_LGUI | KC_C;
            return QK_LCTL | KC_C;
        case CUT:
            if(current_os == OSX)
                return QK_LGUI | KC_X;
            return QK_LCTL | KC_X;
        case PASTE:
            if(current_os == OSX)
                return QK_LGUI | KC_V;
            return QK_LCTL | KC_V;
        case SAVE:
            if(current_os == OSX)
                return QK_LGUI | KC_S;
            return QK_LCTL | KC_S;
        case UNDO:
            if(current_os == OSX)
                return QK_LGUI | KC_Z;
            return QK_LCTL | KC_Z;
        case REDO:
            if(current_os == OSX)
                return QK_LGUI | QK_LSFT | KC_Z;
            return QK_LCTL | QK_LSFT | KC_Z;
        case NEW_TAB:
            if(current_os == OSX)
                return QK_LGUI | KC_T;
            return QK_LCTL | KC_T;
        case LAST_TAB:
            if(current_os == OSX)
                return QK_LGUI | QK_LSFT | KC_T;
            return QK_LCTL | QK_LSFT | KC_T;
        case FIND:
            if(current_os == OSX)
                return QK_LGUI | KC_F;
            return QK_LCTL | KC_F;
        case FIND_ALL:
            if(current_os == OSX)
                return QK_LGUI | QK_LSFT | KC_F;
            return QK_LCTL | QK_LSFT | KC_F;
        case REPLACE:
            if(current_os == OSX)
                return QK_LGUI | KC_H;
            return QK_LCTL | KC_H;
        case REPLACE_ALL:
            if(current_os == OSX)
                return QK_LGUI | QK_LSFT | KC_H;
            return QK_LCTL | QK_LSFT | KC_H;
    }
    return KC_TRNS;
}
