
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
        case WN_PYCH: return "pycharm";
    }

    return "";
}

int window_activator_pr(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) return PR_IGNORE;
    char *window_name = get_window_name(keycode, record);

    if (strlen(window_name)) {
        uprintf("qmk_show_window: %s\n", window_name);
        return false;
    }

    return PR_IGNORE;
}
