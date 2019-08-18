/*
Copyright 2019 Massdrop Inc.

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

#include "arm_atsam_protocol.h"
#include "tmk_core/common/led.h"
#include "rgb_matrix.h"
#include <string.h>
#include <math.h>

#ifdef USE_MASSDROP_CONFIGURATOR
__attribute__((weak))
led_instruction_t led_instructions[] = { { .end = 1 } };
static void led_matrix_massdrop_config_override(int i);
#endif // USE_MASSDROP_CONFIGURATOR


void SERCOM1_0_Handler( void )
{
    if (SERCOM1->I2CM.INTFLAG.bit.ERROR)
    {
        SERCOM1->I2CM.INTFLAG.reg = SERCOM_I2CM_INTENCLR_ERROR;
    }
}

void DMAC_0_Handler( void )
{
    if (DMAC->Channel[0].CHINTFLAG.bit.TCMPL)
    {
        DMAC->Channel[0].CHINTFLAG.reg = DMAC_CHINTENCLR_TCMPL;

        i2c1_stop();

        i2c_led_q_running = 0;

        i2c_led_q_run();

        return;
    }

    if (DMAC->Channel[0].CHINTFLAG.bit.TERR)
    {
        DMAC->Channel[0].CHINTFLAG.reg = DMAC_CHINTENCLR_TERR;
    }
}

issi3733_driver_t issidrv[ISSI3733_DRIVER_COUNT];

issi3733_led_t led_map[ISSI3733_LED_COUNT] = ISSI3733_LED_MAP;
RGB led_buffer[ISSI3733_LED_COUNT];

uint8_t gcr_desired;                    //User's desired GCR value (brightness setting)
uint8_t gcr_actual;                     //The GCR value about to be written to LED drivers
uint8_t gcr_actual_last;                //The GCR value last written to LED drivers
#ifdef USE_MASSDROP_CONFIGURATOR
uint8_t gcr_breathe;                    //The maximum attained GCR value during a breathe cycle (for smooth light transitions)
float breathe_mult;
float pomod;
uint32_t power_sum = 0;                 //Sum of RGB values for current LED pattern (about to be visible)
uint32_t power_sum_last;                //Sum of RGB values for previous LED pattern (currently visible)
#endif // USE_MASSDROP_CONFIGURATOR

//Actions to take for GCR
#define ACT_GCR_NONE            0       //Take no action on GCR
#define ACT_GCR_INC             1       //Increase GCR
#define ACT_GCR_DEC             2       //Decrease GCR

//GCR step settings
#define LED_GCR_STEP_AUTO       1       //How many GCR steps to take per increase or decrease call
#define ACT_GCR_DEC_COUNT       -1      //Number at which a GCR decrease will actually happen (decrements should happen fast to react to sudden high load)
#define ACT_GCR_INC_COUNT       5       //Number at which a GCR increase will actually happen (increments should happen slow to gently approach power limits)

int8_t gcr_change_counter;              //GCR increase and decrease calls are counted here and acted upon when a count limit is hit
uint16_t v_5v_cat_hit;                  //Flag for when 5v catastrophic level has been reached, and timer for recovery period
uint64_t v_5v_low_timer;                //Timer for disabling USB extra device after causing a low voltage situation for an amount of time (-1 indicates timer not active)

//WARNING: Automatic GCR is in place to prevent USB shutdown and LED driver overloading
//Note: GCR updates are currently synced to come before a PWM update, so GCR updates actually happen off the PWM update timer
void gcr_compute(void)
{
    uint8_t action = ACT_GCR_NONE;                                  //Default GCR action to be taken
    uint8_t gcr_use = gcr_desired;                                  //The GCR value to test against

    if (!I2C3733_Control_Get())                                     //If LED drivers are not on
    {
        gcr_actual = 0;                                             //Minimize GCR
        return;                                                     //Nothing else to do
    }

#ifdef USE_MASSDROP_CONFIGURATOR
    if (led_animation_breathing)                                    //If breathing effect is being used
    {
        gcr_use = gcr_breathe;                                      //Set max GCR possible to the highest GCR attained during breathe cycles
    }
#endif // USE_MASSDROP_CONFIGURATOR

    if (usb_gcr_auto)                                               //If automatic GCR is enabled
    {
        //If 5v bus is low or the desired GCR is less than actual, and we have not reached the decrease threshold
        if ((uint16_t)g_v_5v_avg < V5_LOW || gcr_desired < gcr_actual)
        {
            if (gcr_change_counter > ACT_GCR_DEC_COUNT)
            {
                gcr_change_counter--;                                   //Decrease GCR change count
            }
        }
        else if ((uint16_t)g_v_5v_avg > V5_HIGH)  //else if 5v bus is high and we have not reached the increase threshold
        {
            if (gcr_change_counter < ACT_GCR_INC_COUNT)
            {
                gcr_change_counter++;                                   //Increase GCR change count
            }
        }
        else
        {
            //If no action, seek zero
            if (gcr_change_counter > 0) { gcr_change_counter--; }
            else if (gcr_change_counter < 0) { gcr_change_counter++; }
        }

        if (gcr_change_counter == ACT_GCR_DEC_COUNT)                //If change counter has reached the decrease threshold
        {
            //Note: Not checking if there is room to decrease here as that is taken into account differently on the actual decrease action
            action = ACT_GCR_DEC;                                   //Set action to decrease
        }
        else if (gcr_change_counter == ACT_GCR_INC_COUNT)           //Else if change counter has reached the increase threshold
        {
            if (gcr_actual < gcr_use && I2C3733_Control_Get())      //If there is room to increase and LED drivers are on
            {
                action = ACT_GCR_INC;                               //Set action to increase
            }
        }
    }
    else                                                            //Else automatic GCR is disabled so immediately follow user's desired value
    {
        if (gcr_actual < gcr_use) action = ACT_GCR_INC;             //If actual has not met the use value, set action to increase
        else if (gcr_actual > gcr_use) action = ACT_GCR_DEC;        //Else if the actual is more than the use value, set action to decrease
    }

    if (action == ACT_GCR_INC)
    {
        gcr_change_counter = 0;
        if (LED_GCR_STEP_AUTO > LED_GCR_MAX - gcr_actual) gcr_actual = LED_GCR_MAX; //Obey max and prevent wrapping
        else gcr_actual += LED_GCR_STEP_AUTO;
    }
    else if (action == ACT_GCR_DEC)
    {
        gcr_change_counter = 0;
        if (LED_GCR_STEP_AUTO > gcr_actual) //Prevent wrapping
        {
            gcr_actual = 0;
        }
        else
        {
            //Power successfully cut back from LED drivers
            gcr_actual -= LED_GCR_STEP_AUTO;

#ifdef USE_MASSDROP_CONFIGURATOR
            //If breathe mode is active, the top end can fluctuate if the host can not supply enough current
            //So set the breathe GCR to where it can safely reach
            if (led_animation_breathing == 1)
            {
                gcr_breathe = gcr_actual;
                //PS: At this point, setting breathing to exhale makes a noticebly shorter cycle
                //    and the same would happen maybe one or two more times. Therefore I'm favoring
                //    powering through one full breathe and letting GCR settle completely
            }
#endif // USE_MASSDROP_CONFIGURATOR
        }
    }
}

void issi3733_prepare_arrays(void)
{
    memset(issidrv,0,sizeof(issi3733_driver_t) * ISSI3733_DRIVER_COUNT);

    int i;
    uint8_t addrs[ISSI3733_DRIVER_COUNT] = ISSI3773_DRIVER_ADDRESSES;

    for (i=0;i<ISSI3733_DRIVER_COUNT;i++)
    {
        issidrv[i].addr = addrs[i];
    }

    for (uint8_t i = 0; i < ISSI3733_LED_COUNT; i++)
    {
        //BYTE: 1 + (SW-1)*16 + (CS-1)
        led_map[i].rgb.g = issidrv[led_map[i].adr.drv-1].pwm + 1 + ((led_map[i].adr.swg-1)*16 + (led_map[i].adr.cs-1));
        led_map[i].rgb.r = issidrv[led_map[i].adr.drv-1].pwm + 1 + ((led_map[i].adr.swr-1)*16 + (led_map[i].adr.cs-1));
        led_map[i].rgb.b = issidrv[led_map[i].adr.drv-1].pwm + 1 + ((led_map[i].adr.swb-1)*16 + (led_map[i].adr.cs-1));

        //BYTE: 1 + (SW-1)*2 + (CS-1)/8
        //BIT: (CS-1)%8
        *(issidrv[led_map[i].adr.drv-1].onoff + 1 + (led_map[i].adr.swg-1)*2+(led_map[i].adr.cs-1)/8) |= (1<<((led_map[i].adr.cs-1)%8));
        *(issidrv[led_map[i].adr.drv-1].onoff + 1 + (led_map[i].adr.swr-1)*2+(led_map[i].adr.cs-1)/8) |= (1<<((led_map[i].adr.cs-1)%8));
        *(issidrv[led_map[i].adr.drv-1].onoff + 1 + (led_map[i].adr.swb-1)*2+(led_map[i].adr.cs-1)/8) |= (1<<((led_map[i].adr.cs-1)%8));
    }
}

void led_matrix_prepare(void)
{
    for (uint8_t i = 0; i < ISSI3733_LED_COUNT; i++)
    {
        *led_map[i].rgb.r = 0;
        *led_map[i].rgb.g = 0;
        *led_map[i].rgb.b = 0;
    }
}

void led_set_one(int i, uint8_t r, uint8_t g, uint8_t b)
{
    if (i < ISSI3733_LED_COUNT)
    {
#ifdef USE_MASSDROP_CONFIGURATOR
        led_matrix_massdrop_config_override(i);
#else
        led_buffer[i].r = r;
        led_buffer[i].g = g;
        led_buffer[i].b = b;
#endif // USE_MASSDROP_CONFIGURATOR
    }
}

void led_set_all(uint8_t r, uint8_t g, uint8_t b)
{
  for (uint8_t i = 0; i < ISSI3733_LED_COUNT; i++)
  {
    led_set_one(i, r, g, b);
  }
}

void init(void)
{
    DBGC(DC_LED_MATRIX_INIT_BEGIN);

    issi3733_prepare_arrays();

    led_matrix_prepare();

    gcr_change_counter = 0;
    v_5v_cat_hit = 0;

    DBGC(DC_LED_MATRIX_INIT_COMPLETE);
}

void flush(void)
{
    uint8_t drvid;

#ifdef USE_MASSDROP_CONFIGURATOR
    //If there will be a sudden spike in required power, lower GCR prior to change according to some ratio
    if (power_sum > (uint32_t)((float)power_sum_last * 1.5))
    {
        //Lower GCR according to a percentage of the change in power ratio
        gcr_actual = (uint8_t)((((float)gcr_actual * ((float)power_sum_last / (float)power_sum)) * 0.8) + 0.5);
    }
    power_sum_last = power_sum;
    power_sum = 0;

    //NOTE: Allow GCR updates even if the drivers lighting is disabled
    if (gcr_actual != gcr_actual_last)
    {
        for (drvid=0;drvid<ISSI3733_DRIVER_COUNT;drvid++) { I2C_LED_Q_GCR(drvid); } //Queue data
        gcr_actual_last = gcr_actual;
        if (!I2C3733_Control_Get()) { i2c_led_q_run(); } //Run the queue if we know flush will not complete due to drivers being disabled
    }
#endif // USE_MASSDROP_CONFIGURATOR

    if (!I2C3733_Control_Get()) { return; } //Prevent calculations and I2C traffic if LED drivers are not enabled

    //Wait for previous transfer to complete
    //If timings are proper, we should never get into this busy wait state
    while (i2c_led_q_running) {}

    //Copy buffer to live DMA region
    for (uint8_t i = 0; i < ISSI3733_LED_COUNT; i++)
    {
        *led_map[i].rgb.r = led_buffer[i].r;
        *led_map[i].rgb.g = led_buffer[i].g;
        *led_map[i].rgb.b = led_buffer[i].b;
    }

    for (drvid = 0; drvid < ISSI3733_DRIVER_COUNT; drvid++) { I2C_LED_Q_PWM(drvid); } //Queue data

    i2c_led_q_run();

    //Perform any once-per-frame calculations or setup here

#ifdef USE_MASSDROP_CONFIGURATOR
    if (led_animation_breathing)
    {
        led_animation_breathe_cur += BREATHE_STEP * breathe_dir;

        if (led_animation_breathe_cur >= BREATHE_MAX_STEP) { breathe_dir = -1; }
        else if (led_animation_breathe_cur <= BREATHE_MIN_STEP) { breathe_dir = 1; }

        //Brightness curve created for 256 steps, 0 - ~98%
        breathe_mult = 0.000015 * led_animation_breathe_cur * led_animation_breathe_cur;
        if (breathe_mult > 1) { breathe_mult = 1; }
        else if (breathe_mult < 0) { breathe_mult = 0; }
    }

    pomod = 0;
    if (led_animation_speed != 0) //Avoid DIV0
    {
        pomod = (float)((g_rgb_counters.tick / 10) % (uint32_t)(1000.0f / led_animation_speed)) / 10.0f * led_animation_speed;
    }
    pomod *= 100.0f;
    pomod = (uint32_t)pomod % 10000;
    pomod /= 100.0f;
#endif // USE_MASSDROP_CONFIGURATOR
}

void led_matrix_indicators(void)
{
    uint8_t kbled = keyboard_leds();
    if (kbled && rgb_matrix_config.enable)
    {
        for (uint8_t i = 0; i < ISSI3733_LED_COUNT; i++)
        {
            if (
            #if USB_LED_NUM_LOCK_SCANCODE != 255
                (led_map[i].scan == USB_LED_NUM_LOCK_SCANCODE && (kbled & (1<<USB_LED_NUM_LOCK))) ||
            #endif //NUM LOCK
            #if USB_LED_CAPS_LOCK_SCANCODE != 255
                (led_map[i].scan == USB_LED_CAPS_LOCK_SCANCODE && (kbled & (1<<USB_LED_CAPS_LOCK))) ||
            #endif //CAPS LOCK
            #if USB_LED_SCROLL_LOCK_SCANCODE != 255
                (led_map[i].scan == USB_LED_SCROLL_LOCK_SCANCODE && (kbled & (1<<USB_LED_SCROLL_LOCK))) ||
            #endif //SCROLL LOCK
            #if USB_LED_COMPOSE_SCANCODE != 255
                (led_map[i].scan == USB_LED_COMPOSE_SCANCODE && (kbled & (1<<USB_LED_COMPOSE))) ||
            #endif //COMPOSE
            #if USB_LED_KANA_SCANCODE != 255
                (led_map[i].scan == USB_LED_KANA_SCANCODE && (kbled & (1<<USB_LED_KANA))) ||
            #endif //KANA
            (0))
            {
                led_buffer[i].r = 255 - led_buffer[i].r;
                led_buffer[i].g = 255 - led_buffer[i].g;
                led_buffer[i].b = 255 - led_buffer[i].b;
            }
        }
    }

}

const rgb_matrix_driver_t rgb_matrix_driver = {
  .init = init,
  .flush = flush,
  .set_color = led_set_one,
  .set_color_all = led_set_all
};

/*==============================================================================
=                           Legacy Lighting Support                            =
==============================================================================*/

#ifdef USE_MASSDROP_CONFIGURATOR
// Ported from Massdrop QMK Github Repo

// TODO?: wire these up to keymap.c
uint8_t led_animation_orientation = 0;
uint8_t led_animation_direction = 0;
uint8_t led_animation_breathing = 0;
uint8_t led_animation_id = 0;
float led_animation_speed = 4.0f;
uint8_t led_lighting_mode = LED_MODE_NORMAL;
uint8_t led_animation_breathe_cur = BREATHE_MIN_STEP;
uint8_t breathe_dir = 1;
uint8_t led_animation_circular = 0;
float led_edge_brightness = 1.0f;
uint8_t led_edge_mode = LED_EDGE_MODE_ALL;

static void led_run_pattern(led_setup_t *f, float* ro, float* go, float* bo, float pos) {
    float po;

    while (f->end != 1)
    {
        po = pos; //Reset po for new frame

        //Add in any moving effects
        if ((!led_animation_direction && f->ef & EF_SCR_R) || (led_animation_direction && (f->ef & EF_SCR_L)))
        {
            po -= pomod;

            if (po > 100) po -= 100;
            else if (po < 0) po += 100;
        }
        else if ((!led_animation_direction && f->ef & EF_SCR_L) || (led_animation_direction && (f->ef & EF_SCR_R)))
        {
            po += pomod;

            if (po > 100) po -= 100;
            else if (po < 0) po += 100;
        }

        //Check if LED's po is in current frame
        if (po < f->hs) { f++; continue; }
        if (po > f->he) { f++; continue; }
        //note: < 0 or > 100 continue

        //Calculate the po within the start-stop percentage for color blending
        po = (po - f->hs) / (f->he - f->hs);

        //Add in any color effects
        if (f->ef & EF_OVER)
        {
            *ro = (po * (f->re - f->rs)) + f->rs;// + 0.5;
            *go = (po * (f->ge - f->gs)) + f->gs;// + 0.5;
            *bo = (po * (f->be - f->bs)) + f->bs;// + 0.5;
        }
        else if (f->ef & EF_SUBTRACT)
        {
            *ro -= (po * (f->re - f->rs)) + f->rs;// + 0.5;
            *go -= (po * (f->ge - f->gs)) + f->gs;// + 0.5;
            *bo -= (po * (f->be - f->bs)) + f->bs;// + 0.5;
        }
        else
        {
            *ro += (po * (f->re - f->rs)) + f->rs;// + 0.5;
            *go += (po * (f->ge - f->gs)) + f->gs;// + 0.5;
            *bo += (po * (f->be - f->bs)) + f->bs;// + 0.5;
        }

        f++;
    }
}

//TODO: For circular animation fix?// void disp_calc_extents(void)
//TODO: For circular animation fix?// {
//TODO: For circular animation fix?//     issi3733_led_t *cur = led_map;
//TODO: For circular animation fix?//
//TODO: For circular animation fix?//     disp.left = 1e10;
//TODO: For circular animation fix?//     disp.right = -1e10;
//TODO: For circular animation fix?//     disp.top = -1e10;
//TODO: For circular animation fix?//     disp.bottom = 1e10;
//TODO: For circular animation fix?//
//TODO: For circular animation fix?//     while (cur < lede)
//TODO: For circular animation fix?//     {
//TODO: For circular animation fix?//         if (cur->x < disp.left) disp.left = cur->x;
//TODO: For circular animation fix?//         if (cur->x > disp.right) disp.right = cur->x;
//TODO: For circular animation fix?//         if (cur->y < disp.bottom) disp.bottom = cur->y;
//TODO: For circular animation fix?//         if (cur->y > disp.top) disp.top = cur->y;
//TODO: For circular animation fix?//
//TODO: For circular animation fix?//         cur++;
//TODO: For circular animation fix?//     }
//TODO: For circular animation fix?//
//TODO: For circular animation fix?//     disp.width = disp.right - disp.left;
//TODO: For circular animation fix?//     disp.height = disp.top - disp.bottom;
//TODO: For circular animation fix?//     disp.max_distance = sqrtf(powf(disp.width, 2) + powf(disp.height, 2));
//TODO: For circular animation fix?// }

#define RGB_MAX_DISTANCE 232.9635f

static void led_matrix_massdrop_config_override(int i)
{
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

    if (led_lighting_mode == LED_MODE_KEYS_ONLY && LED_IS_EDGE(led_map[i].scan)) {
        //Do not act on this LED
    } else if (led_lighting_mode == LED_MODE_NON_KEYS_ONLY && !LED_IS_EDGE(led_map[i].scan)) {
// TODO: sort this out
/*
    if (led_lighting_mode == LED_MODE_KEYS_ONLY && HAS_FLAGS(g_led_config.flags[i], LED_FLAG_UNDERGLOW)) {
        //Do not act on this LED
    } else if (led_lighting_mode == LED_MODE_NON_KEYS_ONLY && !HAS_FLAGS(g_led_config.flags[i], LED_FLAG_UNDERGLOW)) {
*/
        //Do not act on this LED
    } else if (led_edge_mode == LED_EDGE_MODE_ALTERNATE && LED_IS_EDGE_ALT(led_map[i].scan)) {
        //Do not act on this LED (Edge alternate lighting mode)
    } else if (led_lighting_mode == LED_MODE_INDICATORS_ONLY) {
        //Do not act on this LED (Only show indicators)
    } else {
        led_instruction_t* led_cur_instruction = led_instructions;
        while (!led_cur_instruction->end) {
            // Check if this applies to current layer
            if ((led_cur_instruction->flags & LED_FLAG_MATCH_LAYER) &&
                (led_cur_instruction->layer != highest_active_layer)) {
                goto next_iter;
            }

            // Check if this applies to current index
            if (led_cur_instruction->flags & LED_FLAG_MATCH_ID) {
                uint8_t modid = i / 32;                                     //Calculate which id# contains the led bit
                uint32_t modidbit = 1 << (i % 32);                          //Calculate the bit within the id#
                uint32_t *bitfield = &led_cur_instruction->id0 + modid;     //Add modid as offset to id0 address. *bitfield is now idX of the led id
                if (~(*bitfield) & modidbit) {                              //Check if led bit is not set in idX
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

        //Clamp values 0-255
        if (ro > 255) ro = 255; else if (ro < 0) ro = 0;
        if (go > 255) go = 255; else if (go < 0) go = 0;
        if (bo > 255) bo = 255; else if (bo < 0) bo = 0;

        if (led_animation_breathing)
        {
            ro *= breathe_mult;
            go *= breathe_mult;
            bo *= breathe_mult;
        }
    }

    //Adjust edge LED brightness
    if (led_edge_brightness != 1 && LED_IS_EDGE(led_map[i].scan))
    {
        ro *= led_edge_brightness;
        go *= led_edge_brightness;
        bo *= led_edge_brightness;
    }

    led_buffer[i].r = (uint8_t)ro;
    led_buffer[i].g = (uint8_t)go;
    led_buffer[i].b = (uint8_t)bo;

    power_sum += (uint8_t)ro + (uint8_t)go + (uint8_t)bo;
}

#endif // USE_MASSDROP_CONFIGURATOR
