#include "bmp.h"
#include "bmp_custom_keycode.h"
#include "bmp_pin_def.h"
#include "keycode_str_converter.h"
#include "pointing_device.h"
#include "pmw3360.h"
#include "lib_keyball.h"

const uint8_t CPI_DEFAULT = KEYBALL_CPI_DEFAULT / 100;
const uint8_t CPI_MAX = pmw3360_MAXCPI + 1;
const uint8_t SCROLL_DIV_MAX = 7;

keyball_t keyball = {

    .cpi_value = 0,
    .cpi_changed = false,

    .scroll_mode = false,
    .scroll_div = 0,
};

//////////////////////////////////////////////////////////////////////////////
// Static utilities

// clip2int8 clips an integer fit into int8_t.
static inline int8_t clip2int8(int16_t v)
{
    return (v) < -127 ? -127 : (v) > 127 ? 127 : (int8_t)v;
}


//////////////////////////////////////////////////////////////////////////////
// Public API functions

void keyball_add_cpi(int8_t delta)
{
    int16_t v = keyball_get_cpi() + delta;
    keyball_set_cpi(v < 1 ? 1 : v);
}

uint8_t keyball_get_cpi(void)
{
    return keyball.cpi_value == 0 ? CPI_DEFAULT : keyball.cpi_value;
}

void keyball_set_cpi(uint8_t cpi)
{
    if (cpi > CPI_MAX)
    {
        cpi = CPI_MAX;
    }
    keyball.cpi_value = cpi;
    keyball.cpi_changed = true;
    pmw3360_cpi_set(cpi == 0 ? CPI_DEFAULT - 1 : cpi - 1);
    pmw3360_reg_write(REG_Motion_Burst, 0);
}

bool keyball_get_scroll_mode(void)
{
    return keyball.scroll_mode;
}

void keyball_set_scroll_mode(bool mode)
{
    if (mode != keyball.scroll_mode)
    {
        keyball.scroll_mode_changed = timer_read32();
    }
    keyball.scroll_mode = mode;
}

void keyball_scroll_toggle(void)
{
    keyball_set_scroll_mode(!keyball.scroll_mode);
}

uint8_t keyball_get_scroll_div(void)
{
    return keyball.scroll_div <= 0 ? KEYBALL_SCROLL_DIV_DEFAULT : keyball.scroll_div;
}

void keyball_set_scroll_div(uint8_t div)
{
    keyball.scroll_div = div > SCROLL_DIV_MAX ? SCROLL_DIV_MAX : div;
}

void keyball_add_scroll_div(int8_t delta)
{
    int8_t v = keyball_get_scroll_div() + delta;
    keyball_set_scroll_div(v < 1 ? 1 : v);
}

void keyball_motion_to_mouse_scroll(report_mouse_t *r, int16_t x, int16_t y)
{
    // consume motion of trackball.
    uint8_t div = keyball_get_scroll_div() - 1;

    x = x >> div;
    y = y >> div;

    // apply to mouse report.
    r->h = clip2int8(y);
    r->v = -clip2int8(x);

#if KEYBALL_SCROLLSNAP_ENABLE
    // scroll snap.
    uint32_t now = timer_read32();
    if (r->h != 0 || r->v != 0)
    {
        keyball.scroll_snap_last = now;
    }
    else if (TIMER_DIFF_32(now, keyball.scroll_snap_last) >= KEYBALL_SCROLLSNAP_RESET_TIMER)
    {
        keyball.scroll_snap_tension_h = 0;
    }
    if (abs(keyball.scroll_snap_tension_h) < KEYBALL_SCROLLSNAP_TENSION_THRESHOLD)
    {
        keyball.scroll_snap_tension_h += y;
        r->h = 0;
    }
#endif
}

//////////////////////////////////////////////////////////////////////////////
// Keyboard hooks

void keyboard_post_init_kb(void)
{

    // read keyball configuration from EEPROM
    if (eeconfig_is_enabled())
    {
        keyball_config_t c = {.raw = eeconfig_read_kb()};
        keyball_set_cpi(c.cpi);
        keyball_set_scroll_div(c.sdiv);
    }

    keyboard_post_init_user();
}
