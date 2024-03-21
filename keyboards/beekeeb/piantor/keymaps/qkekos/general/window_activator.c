
#include "../__init__.h"

char *get_window_name(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case WN_STEM: return "steam";
        case WN_DIS: return "discord";
        case WN_DISB: return "discordPTB";
        case WN_CHRM: return "chrome";
        case WN_TELG: return "telegram";
        case WN_WSL: return "wsl";
        case WN_TBX: return "toolbox";
    }

    return "";
}

int window_activator_pr(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) return PR_IGNORE;

    switch (keycode) {
        case WN_STEM:
        case WN_DIS:
        case WN_DISB:
        case WN_CHRM:
        case WN_TELG:
        case WN_WSL:
        case WN_TBX:
            uprintf("qmk_show_window: %s\n", get_window_name(keycode, record));
            return false;
    }

    return PR_IGNORE;
}
