#ifdef ISSI_ENABLE


#include <avr/sfr_defs.h>
#include <avr/timer_avr.h>
#include <avr/wdt.h>
#include "meira.h"
#include "issi.h"
#include "TWIlib.h"
#include "lighting.h"
#include "debug.h"
#include "audio.h"


const uint8_t backlight_pwm_map[BACKLIGHT_LEVELS] = BACKLIGHT_PWM_MAP;

    const uint8_t switch_matrices[] = {0, 1};

void backlight_set(uint8_t level){
#ifdef BACKLIGHT_ENABLE
    uint8_t pwm_value = 0;
    if(level >= BACKLIGHT_LEVELS){
        level = BACKLIGHT_LEVELS;
    }
    if(level > 0){
        pwm_value = backlight_pwm_map[level-1];
    }
    xprintf("BACKLIGHT_LEVELS: %d\n", BACKLIGHT_LEVELS);
    xprintf("backlight_set level: %d pwm: %d\n", level, pwm_value);
    for(int x = 1; x <= 9; x++){
        for(int y = 1; y <= 9; y++){
            activateLED(switch_matrices[0], x, y, pwm_value);
            activateLED(switch_matrices[1], x, y, pwm_value);
        }
    }
#endif
}



void set_backlight_by_keymap(uint8_t col, uint8_t row){
//    dprintf("LED: %02X, %d %d %d\n", lookup_value, matrix, led_col, led_row);
//    activateLED(matrix, led_col, led_row, 255);
}

void force_issi_refresh(void){
    issi_devices[0]->led_dirty = true;
    update_issi(0, true);
    issi_devices[3]->led_dirty = true;
    update_issi(3, true);
}

void led_test(void){
#ifdef WATCHDOG_ENABLE
    // This test take a long time to run, disable the WTD until its complete
    wdt_disable();
#endif
    backlight_set(0);
    force_issi_refresh();
//    for(uint8_t x = 0; x < sizeof(rgb_sequence); x++){
//        set_rgb(rgb_sequence[x], 255, 0, 0);
//        force_issi_refresh();
//        _delay_ms(250);
//        set_rgb(rgb_sequence[x], 0, 255, 0);
//        force_issi_refresh();
//        _delay_ms(250);
//        set_rgb(rgb_sequence[x], 0, 0, 255);
//        force_issi_refresh();
//        _delay_ms(250);
//        set_rgb(rgb_sequence[x], 0, 0, 0);
//        force_issi_refresh();
//    }
#ifdef WATCHDOG_ENABLE
    wdt_enable(WDTO_250MS);
#endif
}

void backlight_init_ports(void){
    xprintf("backlight_init_ports\n");
    issi_init();
}

#endif

