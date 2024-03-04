/* Copyright 2023 Albert
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
#include "quantum.h"
#include "uart.h"
// #include "smart_ble.h"
#include "keyboard.h"
#include "analog.h"
#include "print.h"

#include "usb_main.h"
#include "usb_util.h"
#include "usb_driver.h"
#include "os_detection.h"
#include "as84.h"


#define LED1 A9
#define LED2 A10
#define LED_EN A15

#define LOOP_10HZ_PERIOD    100
deferred_token loop10hz_token  = INVALID_DEFERRED_TOKEN;
uint32_t loop_10Hz(uint32_t trigger_time, void *cb_arg);

uint8_t blink_period = 5;
uint8_t blink_count  = 0;
uint8_t blink_time = 0;
uint8_t reset_buff = 0;


static uint8_t reset_flag = 0;
// static uint8_t blink_reset_count = 0;
static uint32_t reset_press_timer = 0;
uint8_t lock_win=0;
uint8_t change_mac = 0;
bool win_lock = 0;

// uint8_t sleep_temp = 0;

static uint8_t default_layer;
//用于记忆现在在那个层
layer_state_t default_layer_state_set_kb(layer_state_t state)
{

    default_layer = state;
    return state;
}
//MAC&WINDOWS切换
uint8_t mac_flag = 2;
void get_mac_win(void)
{
    if(readPin(B14))
    {
        mac_flag = 3;
        if (default_layer != 1)
        {
            set_single_persistent_default_layer(0);
        }
    }
    else
    {
        mac_flag = 2;
        if(default_layer != 4)
        {
            change_mac = 1;
            set_single_persistent_default_layer(2);
        }
    }
}

//休眠
uint8_t sleep = 0;
bool usb_suspend_flag = false;
static uint32_t usb_suspend_time;

static void POWER_EnterSleep(void) {

    sleep = 5;
    // dynamic_keymap_set_keycode(1,6,3,sleep);

    setPinInput(LED1);
    setPinInput(LED2);
    setPinInput(LED_EN);

    cancel_deferred_exec(loop10hz_token);

#if (DIODE_DIRECTION == ROW2COL)

    pin_t col_pins[] = MATRIX_COL_PINS;

    for(uint8_t x=0; x<MATRIX_COLS; x++)
    {
        pin_t pin;
        pin = col_pins[x];
        if (pin != NO_PIN)
        {
            setPinOutput(pin);
            writePinLow(pin);
        }
    }
    // setPinInputHigh(B10);
    const long unsigned int row_pins[] = MATRIX_ROW_PINS;
    for(uint8_t x=0; x<MATRIX_ROWS; x++)
    {
        pin_t pin;
        pin = row_pins[x];
        if (pin != NO_PIN)
        {
            setPinInputHigh(pin);
            palEnableLineEvent(pin, PAL_EVENT_MODE_BOTH_EDGES);
        }
    }
#else

    const long unsigned int row_pins[] = MATRIX_ROW_PINS;
    for(uint8_t x=0; x<MATRIX_ROWS; x++)
    {
        pin_t pin;
        pin = row_pins[x];
        if (pin != NO_PIN)
        {
            setPinOutput(pin);
            writePinLow(pin);
        }
    }

    const long unsigned int col_pins[] = MATRIX_COL_PINS;
    for(uint8_t x=0; x<MATRIX_COLS; x++)
    //for(uint8_t x=0; x<9; x++)
    {
        pin_t pin;
        pin = col_pins[x];
        setPinInputHigh(pin);
        palEnableLineEvent(pin, PAL_EVENT_MODE_BOTH_EDGES);
    }
#endif
    /* going to anabiosis*/
    //chSysLock();
    /* Clear Wake-up flag */
    palEnableLineEvent(A6, PAL_EVENT_MODE_BOTH_EDGES);
    palEnableLineEvent(B14, PAL_EVENT_MODE_BOTH_EDGES);
    _pal_lld_enablepadevent(0,18,PAL_EVENT_MODE_BOTH_EDGES);
    PWR->CR |= PWR_CR_CWUF | PWR_CR_CSBF;
    /* Select Sleep mode */
    //PWR->CR |= PWR_CR_PDDS | PWR_CR_LPDS; //  Can NOT wake up
    /* Set SLEEPDEEP bit of Cortex System Control Register */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
    //}
    /* Request Wait For Interrupt */

    __WFI();
    EXTI->IMR &= ~(1<<18);
    EXTI->EMR &= ~(1<<18);
    EXTI->RTSR &= ~(1<<18);
    EXTI->FTSR &= ~(1<<18);
    EXTI->PR    = 1<<18;
    /* Reset SLEEPDEEP bit of Cortex System Control Register */
    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
    //wait_ms(10);
    stm32_clock_init();
    matrix_init();
    usbWakeupHost(&USB_DRIVER);  //解决休眠无法唤醒的问题
    restart_usb_driver(&USB_DRIVER);

    // clear_keyboard();
    // send_keyboard_report();


    setPinOutput(LED1);
    setPinOutput(LED2);
    setPinOutput(LED_EN);

    // //LOCK WIN
    // if((host_keyboard_leds() & 0x2)==0x2)
    //     writePinHigh(LED1);
    // else
    //     writePinLow(LED1);
    // //scroll锁上时，亮白灯
    // if((host_keyboard_leds() & 0x4)==0x4)
    //     writePinHigh(LED2);
    // else
    //     writePinLow(LED2);

    // lock_win = dynamic_keymap_get_keycode(0,6,3);
    // sleep_temp = dynamic_keymap_get_keycode(1,6,3);

    loop10hz_token = defer_exec(LOOP_10HZ_PERIOD, loop_10Hz, NULL);
//在usb active之前，主机会一直唤醒键盘，usb唤醒中断会一直触发
    // NVIC_SystemReset();
}

uint8_t sleep_flag = 0;
void sleep_mode(void)
{

    if(usb_suspend_flag == true)
    {
        if(timer_elapsed32(usb_suspend_time) > 500)
        {
            POWER_EnterSleep();
            usb_suspend_flag = false;
        }
    }
    if(USB_DRIVER.state == USB_SUSPENDED)
    {
        if(sleep_flag == 1)
        {
            usb_suspend_time = timer_read32();
            sleep_flag = 0;
            usb_suspend_flag = true;
        }
    }
    if(USB_DRIVER.state == USB_ACTIVE)
    {
        // usb_suspend_flag = false;
        sleep_flag = 1;
    }
    else
        sleep_flag = 2;

}

void keyboard_pre_init_kb(void) {
    setPinInputLow(A9);
    setPinInputLow(A10);
    setPinInput(LED_EN);

    setPinInputHigh(A7);
    setPinInputHigh(A6);
}

void keyboard_post_init_kb(void) {

    // uart_init(921600);
    // wait_ms(200);
    // debug_enable=true;
    // debug_keyboard=true;

    AFIO->MAPR = (AFIO->MAPR & ~AFIO_MAPR_SWJ_CFG_Msk);
    AFIO->MAPR|= AFIO_MAPR_SWJ_CFG_DISABLE;
    // restart_usb_driver(&USB_DRIVER);

    setPinOutput(LED1);
    setPinOutput(LED2);
    setPinOutput(LED_EN);
    writePinLow(LED_EN);
    writePinLow(LED1);
    writePinLow(LED2);

    setPinInputHigh(B14);

    lock_win = dynamic_keymap_get_keycode(0,6,3);
    // sleep_temp = dynamic_keymap_get_keycode(1,6,3);


    loop10hz_token = defer_exec(LOOP_10HZ_PERIOD, loop_10Hz, NULL);

}

uint32_t loop_10Hz(uint32_t trigger_time, void *cb_arg)
{
    // uprintf("lock_win:%d\tGUI:%d\teeprom:%d\tdefault_layer:%d\r\n",lock_win,keymap_config.no_gui,dynamic_keymap_get_keycode(0,6,3),default_layer);
    sleep_mode();
    get_mac_win();

    blink_count = (blink_count+1) % (blink_period*2);
    if(default_layer == 4)keymap_config.no_gui=false;

    if(blink_count == 0)
    {
        if(sleep>0)
        {
            if(USB_DRIVER.state == USB_ACTIVE)
            {
                sleep--;
                report_keyboard_t send_report;
                memset(&send_report, 0, sizeof(report_keyboard_t));
                host_keyboard_send(&send_report);
            }
        }
        if(blink_time > 0)
        blink_time--;
    }
    // uprintf("host_keyboard_leds:%d\t reset_buff:%d\r\n",host_keyboard_leds() & 0x2,reset_buff);
    //LOCK WIN
    if((host_keyboard_leds() & 0x2)==0x2 && reset_buff == 0)
    {
        setPinOutput(LED_EN);
        writePinHigh(LED1);
    }
    else
    {
        writePinLow(LED1);
        // setPinInput(LED_EN);
    }
    //scroll锁上时，亮白灯
    if((host_keyboard_leds() & 0x4)==0x4 && reset_buff == 0)
    {
        setPinOutput(LED_EN);
        writePinHigh(LED2);
    }
    else
    {
        writePinLow(LED2);
        // setPinInput(LED_EN);
    }

    if (timer_elapsed32(reset_press_timer) > 3000)
    {
        if(reset_flag == 1)
        {
            blink_time = 3;
            reset_flag = 0;
            blink_count = 0;
            writePinLow(LED1);
            writePinLow(LED2);
            blink_period = 2;
        }
        if(blink_time > 0)
        {
            if(reset_buff == 0)  reset_buff = 1;
            if (blink_count<blink_period)
            {
                writePinLow(LED1);
                writePinLow(LED2);
            }
            else
            {
                writePinHigh(LED1);
                writePinHigh(LED2);
            }
        }
        else
        {
            if(reset_buff ==1)
            {
                reset_buff = 0;
                win_lock = 0;
                lock_win = win_lock;
                dynamic_keymap_set_keycode(0, 6, 3, lock_win);
                eeconfig_init();
                mcu_reset();
            }
        }
    }


    return LOOP_10HZ_PERIOD;
}

// bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {


//     return false;
// }

bool process_record_kb(uint16_t keycode, keyrecord_t* record) {
    //恢复出厂设置
    if(keycode == KC_RESET)
    {
        if (record->event.pressed)
        {
            reset_press_timer=timer_read32();
            reset_flag = 1;
        }
        else
        {
            if(timer_elapsed32(reset_press_timer) < 3000)
            {
                reset_flag  = 0;
            }
        }
    }

    if(keycode == GU_TOG)
    {
        if(record->event.pressed)
        {
            win_lock = !win_lock;
            if(win_lock)    lock_win = 2;
            else    lock_win = 0;
            dynamic_keymap_set_keycode(0,6,3,lock_win);
        }
    }

    if(keycode == KC_LGUI)
    {
        if(record->event.pressed)
        {
            if((win_lock ||  lock_win== 2) && mac_flag == 3)
            {
                win_lock = 1;
                return false;
            }
            else
                return true;
        }
    }

    return process_record_user(keycode, record);
}



