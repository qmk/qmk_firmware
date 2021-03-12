#ifndef RV_UNICODE_H
#define RV_UNICODE_H

#ifdef UNICODE_SELECTED_MODES
#    undef UNICODE_SELECTED_MODES
#    define UNICODE_SELECTED_MODES UC_MAC, UC_LNX, UC_WINC
#endif

enum unicode_names { BANG, IRONY, SNEK };

const uint32_t PROGMEM unicode_map[] = {
    [BANG]  = 0x203D,
    [IRONY] = 0x2E2E,
    [SNEK]  = 0x1F40D,
};

#endif  // RV_UNICODE_H
