#include QMK_KEYBOARD_H
#include "gui_state.h"
#include "fast_random.h"

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
    draw_rectangle_fill(3, 82, 28, 120, false);

    drawline_hr(1, SCOPE_Y_BOTTOM, 32, 1);
    drawline_vt(0, SCOPE_Y_BOTTOM - 1, 42, 1);
    drawline_vt(31, SCOPE_Y_BOTTOM - 1, 47, 1);

    // oled_write_cursor(0, 10, "     ", false);
    // oled_write_cursor(0, 11, "     ", false);
    // oled_write_cursor(0, 12, "     ", false);
    // oled_write_cursor(0, 13, "     ", false);
    // oled_write_cursor(0, 14, "     ", false);
    // oled_write_cursor(0, 15, "     ", false);

    // drawline_hr(1, SCOPE_Y_BOTTOM, 32, 1);
    // drawline_vt(0, SCOPE_Y_BOTTOM - 1, 43, 1);
    // drawline_vt(31, SCOPE_Y_BOTTOM - 1, 47, 1);

    // oled_write_pixel(4, (10 * 8) + 0, true);
    // oled_write_pixel(3, (10 * 8) + 1, true);
    // oled_write_pixel(2, (10 * 8) + 2, true);
    // oled_write_pixel(1, (10 * 8) + 3, true);
}

static void render_scope_white(void) {
    static const char PROGMEM raw_logo[] = {
        240, 8, 4, 226, 241, 248, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 0, 0, 255, 255, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 255, 127, 128, 128, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 128, 128, 127,
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}

static void render_scope_chart(void) {
    render_scope_white();
    //  uint8_t x_offset = 3;
    uint8_t y_offset = SCOPE_Y_BOTTOM - 3;

    for (uint8_t i = 0; i < SIZE_SCOPE; i++) {
        uint8_t x = 3 + i;

        uint8_t iCurrentBurst = burst_scope[i];
        uint8_t iCurrentWpm   = wpm_scope[i];

        // uint8_t ilenght = (iCurrentBurst * 4) / 10;
        // drawline_vt(x, y_offset, ilenght, 0);

        drawline_vt(x, y_offset, (iCurrentBurst * 4) / 10, 0);

        uint8_t yWpm = y_offset - ((iCurrentWpm * 4) / 10);

        oled_write_pixel(x, yWpm, !(iCurrentWpm > iCurrentBurst));
    }
}

#define ANIM_SCOPE_FRAME_DURATION 40
#define ANIM_SLEEP_SCOPE_FRAME_NUMBER 10

uint32_t anim_sleep_scope_timer = 0;

uint8_t anim_sleep_scope_duration[ANIM_SLEEP_SCOPE_FRAME_NUMBER] = {30, 30, 30, 30, 20, 20, 30, 30, 32, 35};
uint8_t current_sleep_scope_frame                                = 0;
uint8_t sleep_scope_frame_destination                            = ANIM_SLEEP_SCOPE_FRAME_NUMBER - 1;

void reset_scope(bool bNeedOpen) {
    // allume : doit s'éteindre
    current_sleep_scope_frame = 0;

    if (bNeedOpen) {
        // off : doit s'allumer
        anim_sleep_scope_timer    = timer_read32();
        current_sleep_scope_frame = ANIM_SLEEP_SCOPE_FRAME_NUMBER - 1;
        //  sleep_scope_frame_destination = 0;
    }
    sleep_scope_frame_destination = (ANIM_SLEEP_SCOPE_FRAME_NUMBER - 1) - current_sleep_scope_frame;
}

uint32_t    anim_scope_idle_timer = 0;
static void render_glitch_square(void) {
    if (timer_elapsed32(anim_scope_idle_timer) > 60) {
        anim_scope_idle_timer = timer_read32();
        RenderScopeBlack();
        for (int i = 0; i < 4; i++) {
            int size  = 4 + (fastrand() % 6);
            int color = 255;
            draw_gradient(3 + (fastrand() % 19), 85 + (fastrand() % 20), size, size, color, color, 4);
        }
        for (int j = 0; j < 4; j++) {
            int size  = (fastrand() % 6);
            int color = 100 + (fastrand() % 100);
            draw_gradient(3 + (fastrand() % 19), 100 + (fastrand() % 20), size, size, color, color, 4);
        }
    }
}

int      current_glitch_scope_time  = 150;
uint32_t glitch_scope_timer         = 0;
uint8_t  current_glitch_scope_index = 0;

// void get_glitch_index(uint32_t *glitch_timer, int *current_glitch_scope_time, uint8_t *glitch_index, uint8_t min_time, uint16_t max_time, uint8_t glitch_probobility, uint8_t glitch_frame_number) {
//     if (timer_elapsed32(*glitch_timer) > *current_glitch_scope_time) {
//         // end of the last glitch period
//         *glitch_timer = timer_read32();
//         // new random glich period
//         *current_glitch_scope_time = min_time + fastrand() % (max_time - min_time);

//         bool bGenerateGlitch = (fastrand() % 100) < glitch_probobility;
//         if (!bGenerateGlitch) {
//             // no glitch
//             *glitch_index = 0;
//             return;
//         }

//         // get a new glitch index
//         *glitch_index = fastrand() % glitch_frame_number;
//     }
// }

void render_scope_idle(void) {
    get_glitch_index(&glitch_scope_timer, &current_glitch_scope_time, &current_glitch_scope_index, 150, 350, 50, 2);

    // if (timer_elapsed32(glitch_scope_timer) > current_glitch_scope_time) {
    //     glitch_scope_timer = timer_read32();

    //     bool bGenerateGlitch = (fastrand() % 100) < 50;
    //     if (bGenerateGlitch) {
    //         current_glitch_scope_index = fastrand() % 2;
    //     } else {
    //         // logo clean
    //         current_glitch_scope_index = 0;
    //     }

    //     current_glitch_scope_time = fastrand() % 150;
    // }

    switch (current_glitch_scope_index) {
        case 0:
            RenderScopeBlack();
            return;
        case 1:
            render_glitch_square();
            return;
    }
}

uint32_t anim_scope_timer = 0;

static void RenderScopeSleep(void) {
    if (current_sleep_scope_frame == sleep_scope_frame_destination) {
        render_scope_idle();
        return;
    }

    if (timer_elapsed32(anim_sleep_scope_timer) > anim_sleep_scope_duration[current_sleep_scope_frame]) {
        RenderScopeBlack();

        // sleep_scope_frame_destination = 9;
        //  if (current_sleep_scope_frame != sleep_scope_frame_destination) {
        anim_sleep_scope_timer = timer_read32();

        render_tv_animation(current_sleep_scope_frame, 3, 80, 25, 48);

        if (sleep_scope_frame_destination > current_sleep_scope_frame) {
            current_sleep_scope_frame++;
        } else {
            current_sleep_scope_frame--;
        }
    }
}

// for(int i = 0; i < 4; i++){
//     int size = (fastrand() % 10);
//     int color = 200 + (fastrand() % 50);
// draw_gradient(3 + (fastrand() % 25), 85 + (fastrand() % 20), size, size, color, color, 4);
// }

// for(int j = 0; j < 4; j++){
//     int size = (fastrand() % 8);
//     int color = 150 + (fastrand() % 50);
// draw_gradient(3 + (fastrand() % 25), 95 + (fastrand() % 20), size, size, color, color, 4);
// }

// for(int i = 0; i < 4; i++){
//      int y = (fastrand() % 20);
//     int size = 5 + (fastrand() % 6) - y/4;
//     int color = 255 - (y * 1.5);
// draw_gradient(3 + (fastrand() % 19), 85 + y, size, size, color, color, 4);
// }

// for(int i = 0; i < 4; i++){
//      int y = (fastrand() % 10);
//     int size = 4 + (fastrand() % 6);
//     int color = 255;
// draw_gradient(3 + (fastrand() % 19), 82 + y, size, size, color, color, 4);
// }
// for(int j = 0; j < 3; j++){
//      int y = (fastrand() % 15);
//     int size = 1 + (fastrand() % 4);
//     int color = 100 + (fastrand() % 100);
// draw_gradient(3 + (fastrand() % 19),  97 + y, size, size, color, color, 4);
// }

// for(int k = 0; k < 3; k++){
//      int y = (fastrand() % 15);
//     int size = 1+ (fastrand() % 4);
//     int color = 50 + (fastrand() % 50);
// draw_gradient(3 + (fastrand() % 19),  105 + y, size, size, color, color, 4);
// }

// for(int i = 0; i < 4; i++){
//     int size = 3 + (fastrand() % 7);
//     int color = 200 + (fastrand() % 50);
// draw_gradient(3 + (fastrand() % 19), 85 + (fastrand() % 10), size, size, color, color, 4);
// }

// for(int j = 0; j < 4; j++){
//     int size = 2 + (fastrand() % 6);
//     int color = 150 + (fastrand() % 50);
// draw_gradient(3 + (fastrand() % 19), 100 + (fastrand() % 10), size, size, color, color, 4);
// }

// for(int k = 0; k < 4;  k++){
//     int size = 0 + (fastrand() % 6);
//     int color = 0 + (fastrand() % 100);
// draw_gradient(3 + (fastrand() % 19), 105 + (fastrand() % 15), size, size, color, color, 4);
// }

// draw_gradient(15, 110, 15, 15, 60, 60, 4);

// void draw_gradient(uint8_t x, uint8_t y, uint8_t width, uint8_t heigth, uint8_t color_start, uint8_t color_end, uint8_t tres)

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
    uint32_t temps_ecoule = timer_elapsed32(burst_timer);

    int poucentageEcoule = 100;

    if (temps_ecoule <= BURST_FENETRE * 4) {
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
