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
#include "rgb_matrix.h"
#include <string.h>
#include <math.h>

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

uint8_t gcr_desired;
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
        else if (v_5v_avg > V5_HIGH && gcr_actual < gcr_desired) action = ACT_GCR_INC;
        else if (gcr_actual > gcr_desired) action = ACT_GCR_DEC;
    }
    else
    {
        if (gcr_actual < gcr_desired) action = ACT_GCR_INC;
        else if (gcr_actual > gcr_desired) action = ACT_GCR_DEC;
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
        led_buffer[i].r = r;
        led_buffer[i].g = g;
        led_buffer[i].b = b;
    }
}

void led_set_all(uint8_t r, uint8_t g, uint8_t b)
{
  for (uint8_t i = 0; i < ISSI3733_LED_COUNT; i++)
  {
    led_buffer[i].r = r;
    led_buffer[i].g = g;
    led_buffer[i].b = b;
  }
}

void init(void)
{
    DBGC(DC_LED_MATRIX_INIT_BEGIN);

    issi3733_prepare_arrays();

    led_matrix_prepare();

    gcr_min_counter = 0;
    v_5v_cat_hit = 0;

    DBGC(DC_LED_MATRIX_INIT_COMPLETE);
}

void flush(void)
{
    // Wait for previous transfer to complete
    while (i2c_led_q_running)
    {
        CLK_delay_ms(20);
    }

    // Copy buffer to live DMA region
    for (uint8_t i = 0; i < ISSI3733_LED_COUNT; i++)
    {
        *led_map[i].rgb.r = led_buffer[i].r;
        *led_map[i].rgb.g = led_buffer[i].g;
        *led_map[i].rgb.b = led_buffer[i].b;
    }

    uint8_t drvid;

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
