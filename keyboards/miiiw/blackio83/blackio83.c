/* Copyright 2023 ArthurCyy <https://github.com/ArthurCyy>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "blackio83.h"
#include "usb_main.h"
#include "usb_util.h"

#define LOOP_10HZ_PERIOD    100
deferred_token loop10hz_token  = INVALID_DEFERRED_TOKEN;
uint32_t loop_10Hz(uint32_t trigger_time, void *cb_arg);

static const SerialConfig mwproto_uart_config = {
    .speed = MWPROTO_BITRATE,
};

static void POWER_EnterSleep(void) {
    /* Clear Wake-up flag */
    PWR->CR |= PWR_CR_CWUF | PWR_CR_CSBF;
    /* Select Sleep mode */
    /* PWR->CR |= PWR_CR_PDDS | PWR_CR_LPDS; */
    /* Set SLEEPDEEP bit of Cortex System Control Register */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
    /* Request Wait For Interrupt */
    __WFI();
    /* Reset SLEEPDEEP bit of Cortex System Control Register */
    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
    NVIC_SystemReset();
}

extern void ws2812_poweron(void);
extern void ws2812_poweroff(void);

static bool p_setup = false;
static bool s_init = false;
void ws2812_poweron(void) {
    if(p_setup) return;
    p_setup = true;
    s_init = false;
    setPinOutput(RGB_EN_PIN);
    writePinHigh(RGB_EN_PIN);
}

void ws2812_poweroff(void) {
    if(!p_setup) return;
    p_setup = false;
    setPinInputLow(WS2812_DI_PIN);
    writePinLow(RGB_EN_PIN);
}

void keyboard_pre_init_kb() {
	keyboard_pre_init_user();

    setPinInputLow(MWPROTO_STATUS_PIN);
    setPinOutput(MWPROTO_WAKEUP_PIN);
    writePinLow(MWPROTO_WAKEUP_PIN);
    wait_ms(2);
    writePinHigh(MWPROTO_WAKEUP_PIN);

	palSetLineMode(MWPROTO_TX_PIN, PAL_MODE_ALTERNATE(MWPROTO_TX_PAL_MODE) | PAL_OUTPUT_TYPE_OPENDRAIN);
	sdStart(&MWPROTO_DRIVER, &mwproto_uart_config);
}

void keyboard_post_init_kb(void) {
    keyboard_post_init_user();

    print(/* clang-format off */
        "\n<--QMK Keyboard-->\n"
        "Vendor: " STR(MANUFACTURER) "(" STR(VENDOR_ID) ")\n"
        "Product: " STR(PRODUCT) " (" STR(PRODUCT_ID) ")\n"
        "Version: " STR(DEVICE_VER) "\n"
        "BUILD: " __DATE__ "\n"
    ); /* clang-format on */

    writePinLow(MWPROTO_WAKEUP_PIN);
    wait_ms(50);
    sdPutI(&MWPROTO_DRIVER, 0xA5);
    sdPutI(&MWPROTO_DRIVER, 0x12);
    sdPutI(&MWPROTO_DRIVER, 0x01);
    sdPutI(&MWPROTO_DRIVER, 0x02);
    sdPutI(&MWPROTO_DRIVER, 0xB4);
    writePinHigh(MWPROTO_WAKEUP_PIN);

    ws2812_poweron();
    loop10hz_token = defer_exec(LOOP_10HZ_PERIOD, loop_10Hz, NULL);
}

__attribute__((weak)) void shutdown_user(void) {
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_suspend_state(true);
#endif  // RGB_MATRIX_ENABLE
    wait_ms(10);
    ws2812_poweroff();
}

#ifdef DIP_SWITCH_ENABLE
bool dip_switch_update_mask_kb(uint32_t state) {
    if (!dip_switch_update_mask_user(state)) { return false; }
    
    if(state & 0x01) {
        led_suspend();
        usbDisconnectBus(&USB_DRIVER);
        usbStop(&USB_DRIVER);
        shutdown_user();
        setPinInputHigh(POWER_SWITCH_PIN);
        palEnableLineEvent(POWER_SWITCH_PIN, PAL_EVENT_MODE_RISING_EDGE);
        POWER_EnterSleep();
    }
    
    return true;
}
#endif

uint32_t loop_10Hz(uint32_t trigger_time, void *cb_arg) {
    
    if(last_input_activity_elapsed() > 1000) {
        static uint32_t pmu_timer = 0;
        if(timer_elapsed32(pmu_timer) > 3000) {
            pmu_timer = timer_read32();
            writePinLow(MWPROTO_WAKEUP_PIN);
            if(readPin(MWPROTO_STATUS_PIN))
                wait_us(500);
            else
                wait_us(1500);
            sdPutI(&MWPROTO_DRIVER, 0xA5);
            sdPutI(&MWPROTO_DRIVER, 0x28);
            sdPutI(&MWPROTO_DRIVER, 0x00);
            sdPutI(&MWPROTO_DRIVER, 0x8D);
            writePinHigh(MWPROTO_WAKEUP_PIN);
        }
    }

    extern matrix_row_t matrix[MATRIX_ROWS];
    static uint32_t restore_tick = 0;
    if(matrix[0] == 0x4000 && matrix[1] == 0 && 
       matrix[2] == 0 && matrix[3] == 0 && matrix[4] == 0 && matrix[5] == 0x201) {
        if(restore_tick++ > 50) {
            restore_tick = 0;
            writePinLow(MWPROTO_WAKEUP_PIN);
            if(readPin(MWPROTO_STATUS_PIN))
                wait_us(500);
            else
                wait_us(1500);
            sdPutI(&MWPROTO_DRIVER, 0xA5);
            sdPutI(&MWPROTO_DRIVER, 0x1F);
            sdPutI(&MWPROTO_DRIVER, 0x01);
            sdPutI(&MWPROTO_DRIVER, 0x0F);
            sdPutI(&MWPROTO_DRIVER, 0xB4);
            writePinHigh(MWPROTO_WAKEUP_PIN);
            wait_ms(50);
            eeconfig_init();
    #ifdef RGB_MATRIX_ENABLE
            extern void rgb_matrix_update_pwm_buffers(void);
            for(int i = 0; i < 5; i++) {
                rgb_matrix_set_color_all(RGB_WHITE);
                rgb_matrix_update_pwm_buffers();
                wait_ms(500);
                rgb_matrix_set_color_all(RGB_OFF);
                rgb_matrix_update_pwm_buffers();
                wait_ms(500);
            }
    #endif
            wait_ms(500);
            soft_reset_keyboard();
        }
    } else {
        restore_tick = 0;
    }

    static uint32_t debug_tick = 0;
	if (debug_tick++ > 9 ) {
        dprintf("trigger %d\n", trigger_time);
		debug_tick = 0;
	}

    return LOOP_10HZ_PERIOD;
}
