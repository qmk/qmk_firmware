#include QMK_KEYBOARD_H

#include "gui_state.h"
#include "fast_random.h"
#include "burst.h"
#include "draw_helper.h"

// burst stuff
static int      current_burst = 0;
static uint32_t burst_timer   = 0;

// WPM stuff
static int      current_wpm = 0;
static uint16_t wpm_timer   = 0;

// This smoothing is 40 keystrokes
static const float wpm_smoothing = WPM_SMOOTHING;

// store values 
uint8_t burst_scope[SIZE_SCOPE] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint8_t wpm_scope[SIZE_SCOPE]   = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// current max wpm
int     max_wpm                 = MAX_WPM_INIT;

// scope animation stuff
#define ANIM_SCOPE_FRAME_DURATION 40
#define ANIM_SLEEP_SCOPE_FRAME_NUMBER 10

uint32_t anim_sleep_scope_timer = 0;
uint8_t anim_sleep_scope_duration[ANIM_SLEEP_SCOPE_FRAME_NUMBER] = {30, 30, 30, 30, 20, 20, 30, 30, 32, 35};
uint8_t current_sleep_scope_frame                                = 0;
uint8_t sleep_scope_frame_destination                            = ANIM_SLEEP_SCOPE_FRAME_NUMBER - 1;


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
    // clean central zone
    draw_rectangle_fill(3, 82, 28, 120, false);

// redraw some parts of the frame
    drawline_hr(1, SCOPE_Y_BOTTOM, 32, 1);
    drawline_vt(0, SCOPE_Y_BOTTOM - 1, 42, 1);
    drawline_vt(31, SCOPE_Y_BOTTOM - 1, 47, 1);
}

static void render_scope_white(void) {
    static const char PROGMEM raw_logo[] = {
        240, 8, 4, 226, 241, 248, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 0, 0, 255, 255, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 255, 127, 128, 128, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 128, 128, 127,
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}

static void render_scope_chart(void) {
    // clean the frame
    render_scope_white();
    
    uint8_t y_offset = SCOPE_Y_BOTTOM - 3;

    for (uint8_t i = 0; i < SIZE_SCOPE; i++) {
        // offset
        uint8_t x = 3 + i;

        // new black vertical line for burst
        uint8_t iCurrentBurst = burst_scope[i];
        drawline_vt(x, y_offset, (iCurrentBurst * 4) / 10, 0);

// new black point for wpm, white if it's on the burst line 
   uint8_t iCurrentWpm   = wpm_scope[i];
        uint8_t yWpm = y_offset - ((iCurrentWpm * 4) / 10);
        oled_write_pixel(x, yWpm, !(iCurrentWpm > iCurrentBurst));
    }
}

void reset_scope(void) {
        // off : doit s'allumer
        anim_sleep_scope_timer    = timer_read32();
        current_sleep_scope_frame = ANIM_SLEEP_SCOPE_FRAME_NUMBER - 1;

    sleep_scope_frame_destination = 0;
}


uint32_t    anim_scope_idle_timer = 0;
static void render_glitch_square(void) {
    if (timer_elapsed32(anim_scope_idle_timer) > 60) {
        anim_scope_idle_timer = timer_read32();
        RenderScopeBlack();
        for (uint8_t i = 0; i < 4; i++) {
            uint8_t size  = 4 + (fastrand() % 6);
            uint8_t color = 255;
            draw_gradient(3 + (fastrand() % 19), 85 + (fastrand() % 20), size, size, color, color, 4);
        }
        for (uint8_t j = 0; j < 4; j++) {
            uint8_t size  = (fastrand() % 6);
            uint8_t color = 100 + (fastrand() % 100);
            draw_gradient(3 + (fastrand() % 19), 100 + (fastrand() % 20), size, size, color, color, 4);
        }
    }
}

int      current_glitch_scope_time  = 150;
uint32_t glitch_scope_timer         = 0;
uint8_t  current_glitch_scope_index = 0;


void render_scope_idle(void) {
       uint8_t glitch_prob = get_glitch_probability();
    get_glitch_index(&glitch_scope_timer, &current_glitch_scope_time, &current_glitch_scope_index, 150, 350,glitch_prob, 2);

  
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

        anim_sleep_scope_timer = timer_read32();

        render_tv_animation(current_sleep_scope_frame, 3, 80, 25, 48);

        if (sleep_scope_frame_destination > current_sleep_scope_frame) {
            current_sleep_scope_frame++;
        } else {
            current_sleep_scope_frame--;
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
         wpm_timer = timer_read();
        current_wpm += (-current_wpm) * wpm_smoothing;
    }
}

void decay_scope(void) {
    decay_burst();
    decay_wpm();
}
