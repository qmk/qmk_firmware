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

#include "arm_atsam_protocol.h"
#include "tmk_core/common/led.h"
#include <string.h>

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

issi3733_led_t led_map[ISSI3733_LED_COUNT+1] = ISSI3733_LED_MAP;
issi3733_led_t *lede = led_map + ISSI3733_LED_COUNT; //End pointer of mapping

uint8_t gcr_desired;
uint8_t gcr_breathe;
uint8_t gcr_use;
uint8_t gcr_actual;
uint8_t gcr_actual_last;

#define ACT_GCR_NONE    0
#define ACT_GCR_INC     1
#define ACT_GCR_DEC     2

#define LED_GCR_STEP_AUTO 2

static uint8_t gcr_min_counter;
static uint8_t v_5v_cat_hit;

//WARNING: Automatic GCR is in place to prevent USB shutdown and LED driver overloading
void gcr_compute(void)
{
    uint8_t action = ACT_GCR_NONE;

    if (led_animation_breathing)
        gcr_use = gcr_breathe;
    else
        gcr_use = gcr_desired;

    //If the 5v takes a catastrophic hit, disable the LED drivers briefly, assert auto gcr mode, min gcr and let the auto take over
    if (v_5v < V5_CAT)
    {
        I2C3733_Control_Set(0);
        //CDC_print("USB: WARNING: 5V catastrophic level reached! Disabling LED drivers!\r\n"); //Blocking print is bad here!
        v_5v_cat_hit = 20; //~100ms recover
        gcr_actual = 0; //Minimize GCR
        usb_gcr_auto = 1; //Force auto mode enabled
        return;
    }
    else if (v_5v_cat_hit > 1)
    {
        v_5v_cat_hit--;
        return;
    }
    else if (v_5v_cat_hit == 1)
    {
        I2C3733_Control_Set(1);
        CDC_print("USB: WARNING: Re-enabling LED drivers\r\n");
        v_5v_cat_hit = 0;
        return;
    }

    if (usb_gcr_auto)
    {
        if (v_5v_avg < V5_LOW) action = ACT_GCR_DEC;
        else if (v_5v_avg > V5_HIGH && gcr_actual < gcr_use) action = ACT_GCR_INC;
        else if (gcr_actual > gcr_use) action = ACT_GCR_DEC;
    }
    else
    {
        if (gcr_actual < gcr_use) action = ACT_GCR_INC;
        else if (gcr_actual > gcr_use) action = ACT_GCR_DEC;
    }

    if (action == ACT_GCR_NONE)
    {
        gcr_min_counter = 0;
    }
    else if (action == ACT_GCR_INC)
    {
        if (LED_GCR_STEP_AUTO > LED_GCR_MAX - gcr_actual) gcr_actual = LED_GCR_MAX; //Obey max and prevent wrapping
        else gcr_actual += LED_GCR_STEP_AUTO;
        gcr_min_counter = 0;
    }
    else if (action == ACT_GCR_DEC)
    {
        if (LED_GCR_STEP_AUTO > gcr_actual) //Prevent wrapping
        {
            gcr_actual = 0;
            //At this point, power can no longer be cut from the LED drivers, so focus on cutting out extra port if active
            if (usb_extra_state != USB_EXTRA_STATE_DISABLED_UNTIL_REPLUG) //If not in a wait for replug state
            {
                if (usb_extra_state == USB_EXTRA_STATE_ENABLED) //If extra usb is enabled
                {
                    gcr_min_counter++;
                    if (gcr_min_counter > 200) //5ms per check = 1s delay
                    {
                        USB_ExtraSetState(USB_EXTRA_STATE_DISABLED_UNTIL_REPLUG);
                        usb_extra_manual = 0; //Force disable manual mode of extra port
                        if (usb_extra_manual) CDC_print("USB: Disabling extra port until replug and manual mode toggle!\r\n");
                        else CDC_print("USB: Disabling extra port until replug!\r\n");
                    }
                }
            }
        }
        else
        {
            //Power successfully cut back from LED drivers
            gcr_actual -= LED_GCR_STEP_AUTO;
            gcr_min_counter = 0;

            //If breathe mode is active, the top end can fluctuate if the host can not supply enough current
            //So set the breathe GCR to where it becomes stable
            if (led_animation_breathing == 1)
            {
                gcr_breathe = gcr_actual;
                //PS: At this point, setting breathing to exhale makes a noticebly shorter cycle
                //    and the same would happen maybe one or two more times. Therefore I'm favoring
                //    powering through one full breathe and letting gcr settle completely
            }
        }
    }
}

led_disp_t disp;

void issi3733_prepare_arrays(void)
{
    memset(issidrv,0,sizeof(issi3733_driver_t) * ISSI3733_DRIVER_COUNT);

    int i;
    uint8_t addrs[ISSI3733_DRIVER_COUNT] = ISSI3773_DRIVER_ADDRESSES;

    for (i=0;i<ISSI3733_DRIVER_COUNT;i++)
    {
        issidrv[i].addr = addrs[i];
    }

    issi3733_led_t *cur = led_map;

    while (cur < lede)
    {
        //BYTE: 1 + (SW-1)*16 + (CS-1)
        cur->rgb.g = issidrv[cur->adr.drv-1].pwm + 1 + ((cur->adr.swg-1)*16 + (cur->adr.cs-1));
        cur->rgb.r = issidrv[cur->adr.drv-1].pwm + 1 + ((cur->adr.swr-1)*16 + (cur->adr.cs-1));
        cur->rgb.b = issidrv[cur->adr.drv-1].pwm + 1 + ((cur->adr.swb-1)*16 + (cur->adr.cs-1));

        //BYTE: 1 + (SW-1)*2 + (CS-1)/8
        //BIT: (CS-1)%8
        *(issidrv[cur->adr.drv-1].onoff + 1 + (cur->adr.swg-1)*2+(cur->adr.cs-1)/8) |= (1<<((cur->adr.cs-1)%8));
        *(issidrv[cur->adr.drv-1].onoff + 1 + (cur->adr.swr-1)*2+(cur->adr.cs-1)/8) |= (1<<((cur->adr.cs-1)%8));
        *(issidrv[cur->adr.drv-1].onoff + 1 + (cur->adr.swb-1)*2+(cur->adr.cs-1)/8) |= (1<<((cur->adr.cs-1)%8));

        cur++;
    }
}

void disp_calc_extents(void)
{
    issi3733_led_t *cur = led_map;

    disp.left = 1e10;
    disp.right = -1e10;
    disp.top = -1e10;
    disp.bottom = 1e10;

    while (cur < lede)
    {
        if (cur->x < disp.left) disp.left = cur->x;
        if (cur->x > disp.right) disp.right = cur->x;
        if (cur->y < disp.bottom) disp.bottom = cur->y;
        if (cur->y > disp.top) disp.top = cur->y;

        cur++;
    }

    disp.width = disp.right - disp.left;
    disp.height = disp.top - disp.bottom;
}

void disp_pixel_setup(void)
{
    issi3733_led_t *cur = led_map;

    while (cur < lede)
    {
        cur->px = (cur->x - disp.left) / disp.width * 100;
        cur->py = (cur->y - disp.bottom) / disp.height * 100;
        *cur->rgb.r = 0;
        *cur->rgb.g = 0;
        *cur->rgb.b = 0;

        cur++;
    }
}

void led_matrix_prepare(void)
{
    disp_calc_extents();
    disp_pixel_setup();
}

uint8_t led_enabled;
float led_animation_speed;
uint8_t led_animation_direction;
uint8_t led_animation_orientation;
uint8_t led_animation_breathing;
uint8_t led_animation_breathe_cur;
uint8_t breathe_step;
uint8_t breathe_dir;
uint64_t led_next_run;

uint8_t led_animation_id;
uint8_t led_lighting_mode;

issi3733_led_t *led_cur;
uint8_t led_per_run = 15;
float breathe_mult;

__attribute__ ((weak))
void led_matrix_run(void)
{
    float ro;
    float go;
    float bo;
    float po;
    uint8_t led_this_run = 0;
    led_setup_t *f = (led_setup_t*)led_setups[led_animation_id];

    if (led_cur == 0) //Denotes start of new processing cycle in the case of chunked processing
    {
        led_cur = led_map;

        disp.frame += 1;

        breathe_mult = 1;

        if (led_animation_breathing)
        {
            led_animation_breathe_cur += breathe_step * breathe_dir;

            if (led_animation_breathe_cur >= BREATHE_MAX_STEP)
                breathe_dir = -1;
            else if (led_animation_breathe_cur <= BREATHE_MIN_STEP)
                breathe_dir = 1;

            //Brightness curve created for 256 steps, 0 - ~98%
            breathe_mult = 0.000015 * led_animation_breathe_cur * led_animation_breathe_cur;
            if (breathe_mult > 1) breathe_mult = 1;
            else if (breathe_mult < 0) breathe_mult = 0;
        }
    }

    uint8_t fcur = 0;
    uint8_t fmax = 0;

    //Frames setup
    while (f[fcur].end != 1)
    {
        fcur++; //Count frames
    }

    fmax = fcur; //Store total frames count

    while (led_cur < lede && led_this_run < led_per_run)
    {
        ro = 0;
        go = 0;
        bo = 0;

        if (led_lighting_mode == LED_MODE_KEYS_ONLY && led_cur->scan == 255)
        {
            //Do not act on this LED
        }
        else if (led_lighting_mode == LED_MODE_NON_KEYS_ONLY && led_cur->scan != 255)
        {
            //Do not act on this LED
        }
        else if (led_lighting_mode == LED_MODE_INDICATORS_ONLY)
        {
            //Do not act on this LED (Only show indicators)
        }
        else
        {
            //Act on LED
            for (fcur = 0; fcur < fmax; fcur++)
            {

                if (led_animation_orientation)
                {
                  po = led_cur->py;
                }
                else
                {
                  po = led_cur->px;
                }

                float pomod;
                pomod = (float)(disp.frame % (uint32_t)(1000.0f / led_animation_speed)) / 10.0f * led_animation_speed;

                //Add in any moving effects
                if ((!led_animation_direction && f[fcur].ef & EF_SCR_R) || (led_animation_direction && (f[fcur].ef & EF_SCR_L)))
                {
                    pomod *= 100.0f;
                    pomod = (uint32_t)pomod % 10000;
                    pomod /= 100.0f;

                    po -= pomod;

                    if (po > 100) po -= 100;
                    else if (po < 0) po += 100;
                }
                else if ((!led_animation_direction && f[fcur].ef & EF_SCR_L) || (led_animation_direction && (f[fcur].ef & EF_SCR_R)))
                {
                    pomod *= 100.0f;
                    pomod = (uint32_t)pomod % 10000;
                    pomod /= 100.0f;
                    po += pomod;

                    if (po > 100) po -= 100;
                    else if (po < 0) po += 100;
                }

                //Check if LED's po is in current frame
                if (po < f[fcur].hs) continue;
                if (po > f[fcur].he) continue;
                //note: < 0 or > 100 continue

                //Calculate the po within the start-stop percentage for color blending
                po = (po - f[fcur].hs) / (f[fcur].he - f[fcur].hs);

                //Add in any color effects
                if (f[fcur].ef & EF_OVER)
                {
                    ro = (po * (f[fcur].re - f[fcur].rs)) + f[fcur].rs;// + 0.5;
                    go = (po * (f[fcur].ge - f[fcur].gs)) + f[fcur].gs;// + 0.5;
                    bo = (po * (f[fcur].be - f[fcur].bs)) + f[fcur].bs;// + 0.5;
                }
                else if (f[fcur].ef & EF_SUBTRACT)
                {
                    ro -= (po * (f[fcur].re - f[fcur].rs)) + f[fcur].rs;// + 0.5;
                    go -= (po * (f[fcur].ge - f[fcur].gs)) + f[fcur].gs;// + 0.5;
                    bo -= (po * (f[fcur].be - f[fcur].bs)) + f[fcur].bs;// + 0.5;
                }
                else
                {
                    ro += (po * (f[fcur].re - f[fcur].rs)) + f[fcur].rs;// + 0.5;
                    go += (po * (f[fcur].ge - f[fcur].gs)) + f[fcur].gs;// + 0.5;
                    bo += (po * (f[fcur].be - f[fcur].bs)) + f[fcur].bs;// + 0.5;
                }
            }
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

        *led_cur->rgb.r = (uint8_t)ro;
        *led_cur->rgb.g = (uint8_t)go;
        *led_cur->rgb.b = (uint8_t)bo;

#ifdef USB_LED_INDICATOR_ENABLE
        if (keyboard_leds())
        {
            uint8_t kbled = keyboard_leds();
            if (
                #if USB_LED_NUM_LOCK_SCANCODE != 255
                (led_cur->scan == USB_LED_NUM_LOCK_SCANCODE && kbled & (1<<USB_LED_NUM_LOCK)) ||
                #endif //NUM LOCK
                #if USB_LED_CAPS_LOCK_SCANCODE != 255
                (led_cur->scan == USB_LED_CAPS_LOCK_SCANCODE && kbled & (1<<USB_LED_CAPS_LOCK)) ||
                #endif //CAPS LOCK
                #if USB_LED_SCROLL_LOCK_SCANCODE != 255
                (led_cur->scan == USB_LED_SCROLL_LOCK_SCANCODE && kbled & (1<<USB_LED_SCROLL_LOCK)) ||
                #endif //SCROLL LOCK
                #if USB_LED_COMPOSE_SCANCODE != 255
                (led_cur->scan == USB_LED_COMPOSE_SCANCODE && kbled & (1<<USB_LED_COMPOSE)) ||
                #endif //COMPOSE
                #if USB_LED_KANA_SCANCODE != 255
                (led_cur->scan == USB_LED_KANA_SCANCODE && kbled & (1<<USB_LED_KANA)) ||
                #endif //KANA
                (0))
            {
                if (*led_cur->rgb.r > 127) *led_cur->rgb.r = 0;
                else *led_cur->rgb.r = 255;
                if (*led_cur->rgb.g > 127) *led_cur->rgb.g = 0;
                else *led_cur->rgb.g = 255;
                if (*led_cur->rgb.b > 127) *led_cur->rgb.b = 0;
                else *led_cur->rgb.b = 255;
            }
        }
#endif //USB_LED_INDICATOR_ENABLE

        led_cur++;
        led_this_run++;
    }
}

uint8_t led_matrix_init(void)
{
    DBGC(DC_LED_MATRIX_INIT_BEGIN);

    issi3733_prepare_arrays();

    led_matrix_prepare();

    disp.frame = 0;
    led_next_run = 0;

    led_enabled = 1;
    led_animation_id = 0;
    led_lighting_mode = LED_MODE_NORMAL;
    led_animation_speed = 4.0f;
    led_animation_direction = 0;
    led_animation_orientation = 0;
    led_animation_breathing = 0;
    led_animation_breathe_cur = BREATHE_MIN_STEP;
    breathe_step = 1;
    breathe_dir = 1;

    gcr_min_counter = 0;
    v_5v_cat_hit = 0;

    //Run led matrix code once for initial LED coloring
    led_cur = 0;
    rgb_matrix_init_user();
    led_matrix_run();

    DBGC(DC_LED_MATRIX_INIT_COMPLETE);

    return 0;
}

__attribute__ ((weak))
void rgb_matrix_init_user(void) {

}

#define LED_UPDATE_RATE 10  //ms

//led data processing can take time, so process data in chunks to free up the processor
//this is done through led_cur and lede
void led_matrix_task(void)
{
    if (led_enabled)
    {
        //If an update may run and frame processing has completed
        if (CLK_get_ms() >= led_next_run && led_cur == lede)
        {
            uint8_t drvid;

            led_next_run = CLK_get_ms() + LED_UPDATE_RATE;  //Set next frame update time

            //NOTE: GCR does not need to be timed with LED processing, but there is really no harm
            if (gcr_actual != gcr_actual_last)
            {
                for (drvid=0;drvid<ISSI3733_DRIVER_COUNT;drvid++)
                    I2C_LED_Q_GCR(drvid); //Queue data
                gcr_actual_last = gcr_actual;
            }

            for (drvid=0;drvid<ISSI3733_DRIVER_COUNT;drvid++)
                I2C_LED_Q_PWM(drvid); //Queue data

            i2c_led_q_run();

            led_cur = 0; //Signal next frame calculations may begin
        }
    }

    //Process more data if not finished
    if (led_cur != lede)
    {
        //DBG_1_OFF; //debug profiling
        led_matrix_run();
        //DBG_1_ON; //debug profiling
    }
}

