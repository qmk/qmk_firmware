#pragma once

//////////////////////////////////////////////////////////////////////////////
// Configurations

#ifndef KEYBALL_CPI_DEFAULT
#    define KEYBALL_CPI_DEFAULT 600
#endif

#ifndef KEYBALL_SCROLL_DIV_DEFAULT
#    define KEYBALL_SCROLL_DIV_DEFAULT 2 // 4: 1/8 (1/2^(n-1))
#endif

#ifndef KEYBALL_REPORTMOUSE_INTERVALe
#    define KEYBALL_REPORTMOUSE_INTERVAL 8 // mouse report rate: 125Hz
#endif

#ifndef KEYBALL_SCROLLBALL_INHIVITOR
#    define KEYBALL_SCROLLBALL_INHIVITOR 50
#endif

#ifndef KEYBALL_SCROLLSNAP_ENABLE
#    define KEYBALL_SCROLLSNAP_ENABLE 1
#endif

#ifndef KEYBALL_SCROLLSNAP_RESET_TIMER
#    define KEYBALL_SCROLLSNAP_RESET_TIMER 100
#endif

#ifndef KEYBALL_SCROLLSNAP_TENSION_THRESHOLD
#    define KEYBALL_SCROLLSNAP_TENSION_THRESHOLD 12
#endif


//////////////////////////////////////////////////////////////////////////////
// Constants

#define KEYBALL_TX_GETINFO_INTERVAL 500
#define KEYBALL_TX_GETINFO_MAXTRY 10
#define KEYBALL_TX_GETMOTION_INTERVAL 4

//////////////////////////////////////////////////////////////////////////////
// Types


typedef union {
    uint32_t raw;
    struct {
        uint8_t cpi : 7;
        uint8_t sdiv : 3; // scroll divider
    };
} keyball_config_t;

typedef struct {
    int16_t x;
    int16_t y;
} keyball_motion_t;

typedef uint8_t keyball_cpi_t;

typedef struct {

    uint8_t cpi_value;
    bool    cpi_changed;

    bool     scroll_mode;
    uint32_t scroll_mode_changed;
    uint8_t  scroll_div;

    uint32_t scroll_snap_last;
    int8_t   scroll_snap_tension_h;

    uint16_t       last_kc;
    keypos_t       last_pos;
    report_mouse_t last_mouse;
} keyball_t;


void keyball_motion_to_mouse_scroll(report_mouse_t *r, int16_t x, int16_t y);
void keyball_add_cpi(int8_t delta);
uint8_t keyball_get_cpi(void);
void keyball_set_cpi(uint8_t cpi);
bool keyball_get_scroll_mode(void);
void keyball_set_scroll_mode(bool);
void keyball_scroll_toggle(void);
uint8_t keyball_get_scroll_div(void);
void keyball_set_scroll_div(uint8_t div);
void keyball_add_scroll_div(int8_t delta);