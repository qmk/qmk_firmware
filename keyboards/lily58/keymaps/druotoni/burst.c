#include QMK_KEYBOARD_H
#include "gui_state.h"

#include "burst.h"

#include "draw_helper.h"


// burst Stuff
static int      current_burst = 0;
static uint32_t burst_timer   = 0;

// WPM Stuff
static int      current_wpm = 0;
static uint16_t wpm_timer   = 0;

// This smoothing is 40 keystrokes
static const float wpm_smoothing = WPM_SMOOTHING;

uint8_t burst_scope[SIZE_SCOPE] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint8_t wpm_scope[SIZE_SCOPE]   = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int     max_wpm                 = MAX_WPM_INIT;

static int get_current_burst(void) { return current_burst; }

static int calculerPourcentageTemps(uint32_t temps_ecoule) {
    int retour = ((100 * (temps_ecoule)) / (BURST_FENETRE));
    return retour;
}

static void update_wpm(uint16_t keycode) {
    if (wpm_timer > 0) {
        current_wpm += ((60000 / timer_elapsed(wpm_timer) / WPM_ESTIMATED_WORD_SIZE) - current_wpm) * wpm_smoothing;
        if (current_wpm > LIMIT_MAX_WPM) {
            current_wpm = LIMIT_MAX_WPM;
        }
    }
    wpm_timer = timer_read();
}

void update_scope(uint16_t keycode) {
    update_wpm(keycode);

    uint32_t temps_ecoule = timer_elapsed32(burst_timer);

    if (temps_ecoule > BURST_FENETRE) {
        // 1er frappe après longtemps
        current_burst = 40;
    } else {
        current_burst = 100 - calculerPourcentageTemps(temps_ecoule);
    }
    burst_timer = timer_read32();
}



static int get_current_wpm(void) { return current_wpm; }


// ---------------------------------- SCOPE

static void update_scope_array(void) {
    int burst = get_current_burst();
    int wpm   = get_current_wpm();

    max_wpm = (wpm == 0) ? MAX_WPM_INIT : ((wpm > max_wpm) ? wpm : max_wpm);

    // pourcentage par rapport au max
    wpm = (100 * wpm) / max_wpm;
    if (wpm > 100) wpm = 100;

    for (uint8_t i = 0; i < SIZE_SCOPE - 1; i++) {
        uint8_t iBurstOld = burst_scope[i + 1];
        uint8_t iWpmOld   = wpm_scope[i + 1];

        burst_scope[i] = iBurstOld;
        wpm_scope[i]   = iWpmOld;
    }
    burst_scope[SIZE_SCOPE - 1] = burst;
    wpm_scope[SIZE_SCOPE - 1]   = wpm;

    uint8_t pBaisse = 0;
    for (uint8_t i = 0; i < SIZE_SCOPE - (SIZE_SCOPE / 4); i++) {
        pBaisse = 2 + ((SIZE_SCOPE - 1 - i)) / 2;
        burst_scope[i] -= ((burst_scope[i] * pBaisse) / 100);
    }
}

static void RenderScopeBlack(void) {
    //  for(uint8_t i = 10; i <= 15; i++){
    //     oled_set_cursor(0, i);
    // oled_write("     ", false);
    // }

    oled_set_cursor(0, 10);
    oled_write("     ", false);

    oled_set_cursor(0, 11);
    oled_write("     ", false);
    oled_set_cursor(0, 12);
    oled_write("     ", false);
    oled_set_cursor(0, 13);
    oled_write("     ", false);
    oled_set_cursor(0, 14);
    oled_write("     ", false);
    oled_set_cursor(0, 15);
    oled_write("     ", false);

    drawline_hr(1, SCOPE_Y_BOTTOM, 32, 1);
    drawline_vt(0, SCOPE_Y_BOTTOM - 1, 43, 1);
    drawline_vt(31, SCOPE_Y_BOTTOM - 1, 47, 1);

    oled_write_pixel(4, (10 * 8) + 0, true);
    oled_write_pixel(3, (10 * 8) + 1, true);
    oled_write_pixel(2, (10 * 8) + 2, true);
    oled_write_pixel(1, (10 * 8) + 3, true);
}

static void render_scope_white(void) {
    static const char PROGMEM raw_logo[] = {
        240, 8, 4, 226, 241, 248, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 0, 0, 255, 255, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 255, 127, 128, 128, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 128, 128, 127,
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}

static void render_scope_chart(void) {
    render_scope_white();
    uint8_t x_offset = 3;
    uint8_t y_offset = SCOPE_Y_BOTTOM - 3;

    for (uint8_t i = 0; i < SIZE_SCOPE; i++) {
        uint8_t x = x_offset + i;

        uint8_t iCurrentBurst = burst_scope[i];
        uint8_t iCurrentWpm   = wpm_scope[i];

        // uint8_t ilenght = (iCurrentBurst * 4) / 10;
        // drawline_vt(x, y_offset, ilenght, 0);

       
        drawline_vt(x, y_offset, (iCurrentBurst * 4) / 10, 0);

        uint8_t yWpm = y_offset - ((iCurrentWpm * 4) / 10);

        oled_write_pixel(x, yWpm, !(iCurrentWpm > iCurrentBurst));
    }
}

// static void render_tv_animation(uint8_t frame_number, uint8_t x, uint8_t y, uint8_t width, uint8_t heigth) {
//     uint8_t xCenter = x + (width / 2);
//     uint8_t yCenter = y + (heigth / 2);

//     switch (frame_number) {
//         case 0:
//             // a fond : allume
//             drawline_hr_heigth(x, yCenter, width, 17, true);
//             break;

//         case 1:
//             drawline_hr_heigth(x, yCenter, width, 12, true);
//             draw_ellipse_fill(xCenter, yCenter, 7, 15, true);
//             break;

//         case 2:
//             drawline_hr_heigth(x, yCenter, width, 5, true);
//             draw_ellipse_fill(xCenter, yCenter, 5, 8, true);
//             break;

//         case 3:
//             drawline_hr_heigth(x, yCenter, width, 3, true);
//             draw_ellipse_fill(xCenter, yCenter, 3, 4, true);
//             break;

//         case 4:
//             drawline_hr_heigth(x, yCenter, width, 2, true);
//             draw_fill_circle(xCenter, yCenter, 3, true);
//             break;

//         case 5:
//             // central line
//             drawline_hr(x, yCenter, width, true);
//             draw_fill_circle(xCenter, yCenter, 2, true);
//             break;

//         case 6:
//             // cross
//             drawline_hr(xCenter, yCenter + 1, 2, true);
//             drawline_hr(xCenter, yCenter - 1, 2, true);

//             // central line
//             drawline_hr(x, yCenter, width, true);
//             break;

//         case 7:
//             // cross
//             drawline_hr(xCenter, yCenter + 1, 2, true);
//             drawline_hr(xCenter, yCenter - 1, 2, true);
//             // central line
//             drawline_hr(xCenter - 8, yCenter, 18, true);
//             // static
//             oled_write_pixel(xCenter - 13, yCenter, true);
//             oled_write_pixel(xCenter + 12, yCenter, true);
//             break;

//         case 8:
//             // cross
//             drawline_hr(xCenter, yCenter + 1, 2, true);
//             drawline_hr(xCenter, yCenter - 1, 2, true);
//             // central line
//             drawline_hr(xCenter - 2, yCenter, 4, true);
//             // static
//             drawline_hr(xCenter - 7, yCenter, 2, true);
//             drawline_hr(xCenter + 6, yCenter, 3, true);

//           //  oled_write_pixel(xCenter - 11, yCenter, true);
//             oled_write_pixel(xCenter - 11, yCenter, true);
//             oled_write_pixel(xCenter + 12, yCenter, true);
//             oled_write_pixel(xCenter + 14, yCenter, true);
//             break;

//         case 9:
//             // central line
//             drawline_hr(xCenter, yCenter, 2, true);
//             break;
//     }
// }

#define ANIM_SCOPE_FRAME_DURATION 40
#define ANIM_SLEEP_SCOPE_FRAME_NUMBER 10

uint32_t anim_sleep_scope_timer = 0;

uint8_t anim_sleep_scope_duration[ANIM_SLEEP_SCOPE_FRAME_NUMBER] = {30, 30, 30, 30, 20, 20, 30, 30, 32, 35};
uint8_t current_sleep_scope_frame                                = 0;
uint8_t sleep_scope_frame_destination                            = ANIM_SLEEP_SCOPE_FRAME_NUMBER - 1;

void reset_scope(bool bNeedOpen) {

       // allume : doit s'eteindre
        current_sleep_scope_frame     = 0;

    if (bNeedOpen) {
        // eteind : doit s'allumer
        anim_sleep_scope_timer        = timer_read32();
        current_sleep_scope_frame     = ANIM_SLEEP_SCOPE_FRAME_NUMBER  - 1;
      //  sleep_scope_frame_destination = 0;
    } 
sleep_scope_frame_destination = (ANIM_SLEEP_SCOPE_FRAME_NUMBER  - 1) - current_sleep_scope_frame;

}

uint32_t anim_scope_timer = 0;

static void RenderScopeSleep(void) {
    if (timer_elapsed32(anim_sleep_scope_timer) > anim_sleep_scope_duration[current_sleep_scope_frame]) {
        RenderScopeBlack();

        // sleep_scope_frame_destination = 9;
        if (current_sleep_scope_frame != sleep_scope_frame_destination) {
            anim_sleep_scope_timer = timer_read32();

            render_tv_animation(current_sleep_scope_frame, 3, 80, 25, 48);

            if (sleep_scope_frame_destination > current_sleep_scope_frame) {
                current_sleep_scope_frame++;
            } else {
                current_sleep_scope_frame--;
            }
        }
    }
}

void render_scope(gui_state_t t) {
    if (timer_elapsed32(anim_scope_timer) > ANIM_SCOPE_FRAME_DURATION) {
        anim_scope_timer = timer_read32();
        update_scope_array();

        oled_set_cursor(0, 10);

        if (t == _WAKINGUP) {
            RenderScopeSleep();
            return;
        }

        if (t == _IDLE) {
            sleep_scope_frame_destination = ANIM_SLEEP_SCOPE_FRAME_NUMBER - 1;
            RenderScopeSleep();
            return;
        }

        render_scope_chart();
    }
}


static void decay_burst(void) {
    uint32_t temps_ecoule     = timer_elapsed32(burst_timer);
    int      poucentageEcoule = 0;
    if (temps_ecoule > BURST_FENETRE * 4) {
        poucentageEcoule = 100;

    } else {
        poucentageEcoule = ((100 * (temps_ecoule)) / (BURST_FENETRE * 4));
    }

    current_burst = current_burst - poucentageEcoule;
    if (current_burst <= 0) current_burst = 0;
}

static void decay_wpm(void) {
    if (timer_elapsed(wpm_timer) > 1000) {
        current_wpm += (-current_wpm) * wpm_smoothing;
        wpm_timer = timer_read();
    }
}


void decay_scope(void) {
    decay_burst();
    decay_wpm();
}
