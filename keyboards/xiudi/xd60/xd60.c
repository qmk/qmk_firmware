#include "xd60.h"


extern inline void xd60_caps_led_on(void);
extern inline void xd60_bl_led_on(void);

extern inline void xd60_caps_led_off(void);
extern inline void xd60_bl_led_off(void);


bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        if (led_state.caps_lock) {
            xd60_caps_led_on();
        } else {
            xd60_caps_led_off();
        }
    }
    return res;
}
