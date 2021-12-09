/*
Copyright 2018 Massdrop Inc.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#define FLUSH_TIMEOUT 5000
#define EECONFIG_MD_LED ((uint8_t*)(EECONFIG_SIZE + 64))
#define MD_LED_CONFIG_VERSION 1

#ifdef RGB_MATRIX_ENABLE
#    include "arm_atsam_protocol.h"
#    include "led.h"
#    include "rgb_matrix.h"
#    include <string.h>
#    include <math.h>

#    ifdef USE_MASSDROP_CONFIGURATOR
// TODO?: wire these up to keymap.c
md_led_config_t md_led_config = {0};

EECONFIG_DEBOUNCE_HELPER(md_led, EECONFIG_MD_LED, md_led_config);

void eeconfig_update_md_led_default(void) {
    md_led_config.ver = MD_LED_CONFIG_VERSION;

    gcr_desired               = LED_GCR_MAX;
    led_animation_orientation = 0;
    led_animation_direction   = 0;
    led_animation_breathing   = 0;
    led_animation_id          = 0;
    led_animation_speed       = 4.0f;
    led_lighting_mode         = LED_MODE_NORMAL;
    led_enabled               = 1;
    led_animation_breathe_cur = BREATHE_MIN_STEP;
    breathe_dir               = 1;
    led_animation_circular    = 0;
    led_edge_brightness       = 1.0f;
    led_ratio_brightness      = 1.0f;
    led_edge_mode             = LED_EDGE_MODE_ALL;

    eeconfig_flush_md_led(true);
}

void md_led_changed(void) { eeconfig_flag_md_led(true); }

// todo: use real task rather than this bodge
void housekeeping_task_kb(void) { eeconfig_flush_md_led_task(FLUSH_TIMEOUT); }

__attribute__((weak)) led_instruction_t led_instructions[] = {{.end = 1}};
static void                             md_rgb_matrix_config_override(int i);
#    else
uint8_t gcr_desired;
#    endif  // USE_MASSDROP_CONFIGURATOR

void SERCOM1_0_Handler(void) {
    if (SERCOM1->I2CM.INTFLAG.bit.ERROR) {
        SERCOM1->I2CM.INTFLAG.reg = SERCOM_I2CM_INTENCLR_ERROR;
    }
}

void DMAC_0_Handler(void) {
    if (DMAC->Channel[0].CHINTFLAG.bit.TCMPL) {
        DMAC->Channel[0].CHINTFLAG.reg = DMAC_CHINTENCLR_TCMPL;

        i2c1_stop();

        i2c_led_q_running = 0;

        i2c_led_q_run();

        return;
    }

    if (DMAC->Channel[0].CHINTFLAG.bit.TERR) {
        DMAC->Channel[0].CHINTFLAG.reg = DMAC_CHINTENCLR_TERR;
    }
}

issi3733_driver_t issidrv[ISSI3733_DRIVER_COUNT];

issi3733_led_t led_map[ISSI3733_LED_COUNT] = ISSI3733_LED_MAP;
RGB            led_buffer[ISSI3733_LED_COUNT];

uint8_t gcr_actual;
uint8_t gcr_actual_last;
#    ifdef USE_MASSDROP_CONFIGURATOR
uint8_t gcr_breathe;
float   breathe_mult;
float   pomod;
#    endif

#    define ACT_GCR_NONE 0
#    define ACT_GCR_INC 1
#    define ACT_GCR_DEC 2

#    define LED_GCR_STEP_AUTO 2

static uint8_t gcr_min_counter;
static uint8_t v_5v_cat_hit;

// WARNING: Automatic GCR is in place to prevent USB shutdown and LED driver overloading
void gcr_compute(void) {
    uint8_t action  = ACT_GCR_NONE;
    uint8_t gcr_use = gcr_desired;

#    ifdef USE_MASSDROP_CONFIGURATOR
    if (led_animation_breathing) {
        gcr_use = gcr_breathe;
    }
#    endif

    // If the 5v takes a catastrophic hit, disable the LED drivers briefly, assert auto gcr mode, min gcr and let the auto take over
    if (v_5v < V5_CAT) {
        I2C3733_Control_Set(0);
        // CDC_print("USB: WARNING: 5V catastrophic level reached! Disabling LED drivers!\r\n"); //Blocking print is bad here!
        v_5v_cat_hit = 20;  //~100ms recover
        gcr_actual   = 0;   // Minimize GCR
        usb_gcr_auto = 1;   // Force auto mode enabled
        return;
    } else if (v_5v_cat_hit > 1) {
        v_5v_cat_hit--;
        return;
    } else if (v_5v_cat_hit == 1) {
        I2C3733_Control_Set(1);
        CDC_print("USB: WARNING: Re-enabling LED drivers\r\n");
        v_5v_cat_hit = 0;
        return;
    }

    if (usb_gcr_auto) {
        if (v_5v_avg < V5_LOW)
            action = ACT_GCR_DEC;
        else if (v_5v_avg > V5_HIGH && gcr_actual < gcr_use)
            action = ACT_GCR_INC;
        else if (gcr_actual > gcr_use)
            action = ACT_GCR_DEC;
    } else {
        if (gcr_actual < gcr_use)
            action = ACT_GCR_INC;
        else if (gcr_actual > gcr_use)
            action = ACT_GCR_DEC;
    }

    if (action == ACT_GCR_NONE) {
        gcr_min_counter = 0;
    } else if (action == ACT_GCR_INC) {
        if (LED_GCR_STEP_AUTO > LED_GCR_MAX - gcr_actual)
            gcr_actual = LED_GCR_MAX;  // Obey max and prevent wrapping
        else
            gcr_actual += LED_GCR_STEP_AUTO;
        gcr_min_counter = 0;
    } else if (action == ACT_GCR_DEC) {
        if (LED_GCR_STEP_AUTO > gcr_actual)  // Prevent wrapping
        {
            gcr_actual = 0;
            // At this point, power can no longer be cut from the LED drivers, so focus on cutting out extra port if active
            if (usb_extra_state != USB_EXTRA_STATE_DISABLED_UNTIL_REPLUG)  // If not in a wait for replug state
            {
                if (usb_extra_state == USB_EXTRA_STATE_ENABLED)  // If extra usb is enabled
                {
                    gcr_min_counter++;
                    if (gcr_min_counter > 200)  // 5ms per check = 1s delay
                    {
                        USB_ExtraSetState(USB_EXTRA_STATE_DISABLED_UNTIL_REPLUG);
                        usb_extra_manual = 0;  // Force disable manual mode of extra port
                        if (usb_extra_manual)
                            CDC_print("USB: Disabling extra port until replug and manual mode toggle!\r\n");
                        else
                            CDC_print("USB: Disabling extra port until replug!\r\n");
                    }
                }
            }
        } else {
            // Power successfully cut back from LED drivers
            gcr_actual -= LED_GCR_STEP_AUTO;
            gcr_min_counter = 0;

#    ifdef USE_MASSDROP_CONFIGURATOR
            // If breathe mode is active, the top end can fluctuate if the host can not supply enough current
            // So set the breathe GCR to where it becomes stable
            if (led_animation_breathing == 1) {
                gcr_breathe = gcr_actual;
                // PS: At this point, setting breathing to exhale makes a noticebly shorter cycle
                //    and the same would happen maybe one or two more times. Therefore I'm favoring
                //    powering through one full breathe and letting gcr settle completely
            }
#    endif
        }
    }
}

void issi3733_prepare_arrays(void) {
    memset(issidrv, 0, sizeof(issi3733_driver_t) * ISSI3733_DRIVER_COUNT);

    int     i;
    uint8_t addrs[ISSI3733_DRIVER_COUNT] = ISSI3773_DRIVER_ADDRESSES;

    for (i = 0; i < ISSI3733_DRIVER_COUNT; i++) {
        issidrv[i].addr = addrs[i];
    }

    for (uint8_t i = 0; i < ISSI3733_LED_COUNT; i++) {
        // BYTE: 1 + (SW-1)*16 + (CS-1)
        led_map[i].rgb.g = issidrv[led_map[i].adr.drv - 1].pwm + 1 + ((led_map[i].adr.swg - 1) * 16 + (led_map[i].adr.cs - 1));
        led_map[i].rgb.r = issidrv[led_map[i].adr.drv - 1].pwm + 1 + ((led_map[i].adr.swr - 1) * 16 + (led_map[i].adr.cs - 1));
        led_map[i].rgb.b = issidrv[led_map[i].adr.drv - 1].pwm + 1 + ((led_map[i].adr.swb - 1) * 16 + (led_map[i].adr.cs - 1));

        // BYTE: 1 + (SW-1)*2 + (CS-1)/8
        // BIT: (CS-1)%8
        *(issidrv[led_map[i].adr.drv - 1].onoff + 1 + (led_map[i].adr.swg - 1) * 2 + (led_map[i].adr.cs - 1) / 8) |= (1 << ((led_map[i].adr.cs - 1) % 8));
        *(issidrv[led_map[i].adr.drv - 1].onoff + 1 + (led_map[i].adr.swr - 1) * 2 + (led_map[i].adr.cs - 1) / 8) |= (1 << ((led_map[i].adr.cs - 1) % 8));
        *(issidrv[led_map[i].adr.drv - 1].onoff + 1 + (led_map[i].adr.swb - 1) * 2 + (led_map[i].adr.cs - 1) / 8) |= (1 << ((led_map[i].adr.cs - 1) % 8));
    }
}

void md_rgb_matrix_prepare(void) {
    for (uint8_t i = 0; i < ISSI3733_LED_COUNT; i++) {
        *led_map[i].rgb.r = 0;
        *led_map[i].rgb.g = 0;
        *led_map[i].rgb.b = 0;
    }
}

static void led_set_one(int i, uint8_t r, uint8_t g, uint8_t b) {
    if (i < ISSI3733_LED_COUNT) {
#    ifdef USE_MASSDROP_CONFIGURATOR
        md_rgb_matrix_config_override(i);
#    else
        led_buffer[i].r = r;
        led_buffer[i].g = g;
        led_buffer[i].b = b;
#    endif
    }
}

static void led_set_all(uint8_t r, uint8_t g, uint8_t b) {
    for (uint8_t i = 0; i < ISSI3733_LED_COUNT; i++) {
        led_set_one(i, r, g, b);
    }
}

static void init(void) {
    DBGC(DC_LED_MATRIX_INIT_BEGIN);

#    ifdef USE_MASSDROP_CONFIGURATOR
    eeconfig_init_md_led();
    if (md_led_config.ver != MD_LED_CONFIG_VERSION) {
        eeconfig_update_md_led_default();
    }
#    endif

    issi3733_prepare_arrays();

    md_rgb_matrix_prepare();

    gcr_min_counter = 0;
    v_5v_cat_hit    = 0;

    DBGC(DC_LED_MATRIX_INIT_COMPLETE);
}

static void flush(void) {
#    ifdef USE_MASSDROP_CONFIGURATOR
    if (!led_enabled) {
        return;
    }  // Prevent calculations and I2C traffic if LED drivers are not enabled
#    else
    if (!sr_exp_data.bit.SDB_N) {
        return;
    }  // Prevent calculations and I2C traffic if LED drivers are not enabled
#    endif

    // Wait for previous transfer to complete
    while (i2c_led_q_running) {
    }

    // Copy buffer to live DMA region
    for (uint8_t i = 0; i < ISSI3733_LED_COUNT; i++) {
        *led_map[i].rgb.r = led_buffer[i].r;
        *led_map[i].rgb.g = led_buffer[i].g;
        *led_map[i].rgb.b = led_buffer[i].b;
    }

#    ifdef USE_MASSDROP_CONFIGURATOR
    breathe_mult = 1;

    if (led_animation_breathing) {
        //+60us 119 LED
        led_animation_breathe_cur += BREATHE_STEP * breathe_dir;

        if (led_animation_breathe_cur >= BREATHE_MAX_STEP)
            breathe_dir = -1;
        else if (led_animation_breathe_cur <= BREATHE_MIN_STEP)
            breathe_dir = 1;

        // Brightness curve created for 256 steps, 0 - ~98%
        breathe_mult = 0.000015 * led_animation_breathe_cur * led_animation_breathe_cur;
        if (breathe_mult > 1)
            breathe_mult = 1;
        else if (breathe_mult < 0)
            breathe_mult = 0;
    }

    // This should only be performed once per frame
    pomod = (float)((g_rgb_timer / 10) % (uint32_t)(1000.0f / led_animation_speed)) / 10.0f * led_animation_speed;
    pomod *= 100.0f;
    pomod = (uint32_t)pomod % 10000;
    pomod /= 100.0f;

#    endif  // USE_MASSDROP_CONFIGURATOR

    uint8_t drvid;

    // NOTE: GCR does not need to be timed with LED processing, but there is really no harm
    if (gcr_actual != gcr_actual_last) {
        for (drvid = 0; drvid < ISSI3733_DRIVER_COUNT; drvid++) I2C_LED_Q_GCR(drvid);  // Queue data
        gcr_actual_last = gcr_actual;
    }

    for (drvid = 0; drvid < ISSI3733_DRIVER_COUNT; drvid++) I2C_LED_Q_PWM(drvid);  // Queue data

    i2c_led_q_run();
}

void md_rgb_matrix_indicators_advanced(uint8_t led_min, uint8_t led_max) {
    uint8_t kbled = keyboard_leds();
    if (kbled && rgb_matrix_config.enable) {
        for (uint8_t i = led_min; i < led_max; i++) {
            if (
#    if USB_LED_NUM_LOCK_SCANCODE != 255
                (led_map[i].scan == USB_LED_NUM_LOCK_SCANCODE && (kbled & (1 << USB_LED_NUM_LOCK))) ||
#    endif  // NUM LOCK
#    if USB_LED_CAPS_LOCK_SCANCODE != 255
                (led_map[i].scan == USB_LED_CAPS_LOCK_SCANCODE && (kbled & (1 << USB_LED_CAPS_LOCK))) ||
#    endif  // CAPS LOCK
#    if USB_LED_SCROLL_LOCK_SCANCODE != 255
                (led_map[i].scan == USB_LED_SCROLL_LOCK_SCANCODE && (kbled & (1 << USB_LED_SCROLL_LOCK))) ||
#    endif  // SCROLL LOCK
#    if USB_LED_COMPOSE_SCANCODE != 255
                (led_map[i].scan == USB_LED_COMPOSE_SCANCODE && (kbled & (1 << USB_LED_COMPOSE))) ||
#    endif  // COMPOSE
#    if USB_LED_KANA_SCANCODE != 255
                (led_map[i].scan == USB_LED_KANA_SCANCODE && (kbled & (1 << USB_LED_KANA))) ||
#    endif  // KANA
                (0)) {
                if (rgb_matrix_get_flags() & LED_FLAG_INDICATOR) {
                    led_buffer[i].r = 255 - led_buffer[i].r;
                    led_buffer[i].g = 255 - led_buffer[i].g;
                    led_buffer[i].b = 255 - led_buffer[i].b;
                }
            }
        }
    }
}

const rgb_matrix_driver_t rgb_matrix_driver = {.init = init, .flush = flush, .set_color = led_set_one, .set_color_all = led_set_all};

/*==============================================================================
=                           Legacy Lighting Support                            =
==============================================================================*/

#    ifdef USE_MASSDROP_CONFIGURATOR
// Ported from Massdrop QMK GitHub Repo

static void led_run_pattern(led_setup_t* f, float* ro, float* go, float* bo, float pos) {
    float po;

    while (f->end != 1) {
        po = pos;  // Reset po for new frame

        // Add in any moving effects
        if ((!led_animation_direction && f->ef & EF_SCR_R) || (led_animation_direction && (f->ef & EF_SCR_L))) {
            po -= pomod;

            if (po > 100)
                po -= 100;
            else if (po < 0)
                po += 100;
        } else if ((!led_animation_direction && f->ef & EF_SCR_L) || (led_animation_direction && (f->ef & EF_SCR_R))) {
            po += pomod;

            if (po > 100)
                po -= 100;
            else if (po < 0)
                po += 100;
        }

        // Check if LED's po is in current frame
        if (po < f->hs) {
            f++;
            continue;
        }
        if (po > f->he) {
            f++;
            continue;
        }
        // note: < 0 or > 100 continue

        // Calculate the po within the start-stop percentage for color blending
        po = (po - f->hs) / (f->he - f->hs);

        // Add in any color effects
        if (f->ef & EF_OVER) {
            *ro = (po * (f->re - f->rs)) + f->rs;  // + 0.5;
            *go = (po * (f->ge - f->gs)) + f->gs;  // + 0.5;
            *bo = (po * (f->be - f->bs)) + f->bs;  // + 0.5;
        } else if (f->ef & EF_SUBTRACT) {
            *ro -= (po * (f->re - f->rs)) + f->rs;  // + 0.5;
            *go -= (po * (f->ge - f->gs)) + f->gs;  // + 0.5;
            *bo -= (po * (f->be - f->bs)) + f->bs;  // + 0.5;
        } else {
            *ro += (po * (f->re - f->rs)) + f->rs;  // + 0.5;
            *go += (po * (f->ge - f->gs)) + f->gs;  // + 0.5;
            *bo += (po * (f->be - f->bs)) + f->bs;  // + 0.5;
        }

        f++;
    }
}

#        define RGB_MAX_DISTANCE 232.9635f

static void md_rgb_matrix_config_override(int i) {
    float ro = 0;
    float go = 0;
    float bo = 0;
    float po;

    uint8_t highest_active_layer = biton32(layer_state);

    if (led_animation_circular) {
        // TODO: should use min/max values from LED configuration instead of
        // hard-coded 224, 64
        // po = sqrtf((powf(fabsf((disp.width / 2) - (led_cur->x - disp.left)), 2) + powf(fabsf((disp.height / 2) - (led_cur->y - disp.bottom)), 2))) / disp.max_distance * 100;
        po = sqrtf((powf(fabsf((224 / 2) - (float)g_led_config.point[i].x), 2) + powf(fabsf((64 / 2) - (float)g_led_config.point[i].y), 2))) / RGB_MAX_DISTANCE * 100;
    } else {
        if (led_animation_orientation) {
            po = (float)g_led_config.point[i].y / 64.f * 100;
        } else {
            po = (float)g_led_config.point[i].x / 224.f * 100;
        }
    }

    if (led_edge_mode == LED_EDGE_MODE_ALTERNATE && LED_IS_EDGE_ALT(led_map[i].scan)) {
        // Do not act on this LED (Edge alternate lighting mode)
    } else if (led_lighting_mode == LED_MODE_KEYS_ONLY && HAS_FLAGS(g_led_config.flags[i], LED_FLAG_UNDERGLOW)) {
        // Do not act on this LED
    } else if (led_lighting_mode == LED_MODE_NON_KEYS_ONLY && !HAS_FLAGS(g_led_config.flags[i], LED_FLAG_UNDERGLOW)) {
        // Do not act on this LED
    } else if (led_lighting_mode == LED_MODE_INDICATORS_ONLY) {
        // Do not act on this LED (Only show indicators)
    } else {
        led_instruction_t* led_cur_instruction = led_instructions;
        while (!led_cur_instruction->end) {
            // Check if this applies to current layer
            if ((led_cur_instruction->flags & LED_FLAG_MATCH_LAYER) && (led_cur_instruction->layer != highest_active_layer)) {
                goto next_iter;
            }

            // Check if this applies to current index
            if (led_cur_instruction->flags & LED_FLAG_MATCH_ID) {
                uint8_t   modid    = i / 32;                             // Calculate which id# contains the led bit
                uint32_t  modidbit = 1 << (i % 32);                      // Calculate the bit within the id#
                uint32_t* bitfield = &led_cur_instruction->id0 + modid;  // Add modid as offset to id0 address. *bitfield is now idX of the led id
                if (~(*bitfield) & modidbit) {                           // Check if led bit is not set in idX
                    goto next_iter;
                }
            }

            if (led_cur_instruction->flags & LED_FLAG_USE_RGB) {
                ro = led_cur_instruction->r;
                go = led_cur_instruction->g;
                bo = led_cur_instruction->b;
            } else if (led_cur_instruction->flags & LED_FLAG_USE_PATTERN) {
                led_run_pattern(led_setups[led_cur_instruction->pattern_id], &ro, &go, &bo, po);
            } else if (led_cur_instruction->flags & LED_FLAG_USE_ROTATE_PATTERN) {
                led_run_pattern(led_setups[led_animation_id], &ro, &go, &bo, po);
            }

        next_iter:
            led_cur_instruction++;
        }

        if (ro > 255)
            ro = 255;
        else if (ro < 0)
            ro = 0;
        if (go > 255)
            go = 255;
        else if (go < 0)
            go = 0;
        if (bo > 255)
            bo = 255;
        else if (bo < 0)
            bo = 0;

        if (led_animation_breathing) {
            ro *= breathe_mult;
            go *= breathe_mult;
            bo *= breathe_mult;
        }
    }

    // Adjust edge LED brightness
    if (led_edge_brightness != 1 && LED_IS_EDGE(led_map[i].scan)) {
        ro *= led_edge_brightness;
        go *= led_edge_brightness;
        bo *= led_edge_brightness;
    }

    // Adjust ratio of key vs. underglow (edge) LED brightness
    if (LED_IS_EDGE(led_map[i].scan) && led_ratio_brightness > 1.0) {
        // Decrease edge (underglow) LEDs
        ro *= (2.0 - led_ratio_brightness);
        go *= (2.0 - led_ratio_brightness);
        bo *= (2.0 - led_ratio_brightness);
    } else if (LED_IS_KEY(led_map[i].scan) && led_ratio_brightness < 1.0) {
        // Decrease KEY LEDs
        ro *= led_ratio_brightness;
        go *= led_ratio_brightness;
        bo *= led_ratio_brightness;
    }

    led_buffer[i].r = (uint8_t)ro;
    led_buffer[i].g = (uint8_t)go;
    led_buffer[i].b = (uint8_t)bo;
}

#    endif  // USE_MASSDROP_CONFIGURATOR
#endif      // RGB_MATRIX_ENABLE
