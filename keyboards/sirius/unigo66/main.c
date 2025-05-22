#include <avr/wdt.h>
#include <avr/power.h>

// LUFA
#include "lufa.h"

#include "sendchar.h"
#include "debug.h"
#include "keyboard.h"
#include "gpio.h"
#include "wait.h"
#include "led.h"

/* LED ping configuration */
#define TMK_LED
//#define LEONARDO_LED
#if defined(TMK_LED)
// For TMK converter and Teensy
#define LED_TX_INIT    gpio_set_pin_output(D6)
#define LED_TX_ON      gpio_write_pin_high(D6)
#define LED_TX_OFF     gpio_write_pin_low(D6)
#define LED_TX_TOGGLE  gpio_toggle_pin(D6)
#elif defined(LEONARDO_LED)
// For Leonardo(TX LED)
#define LED_TX_INIT    gpio_set_pin_output(D5)
#define LED_TX_ON      gpio_write_pin_low(D5)
#define LED_TX_OFF     gpio_write_pin_high(D5)
#define LED_TX_TOGGLE  gpio_toggle_pin(D5)
#else
#define LED_TX_INIT
#define LED_TX_ON
#define LED_TX_OFF
#define LED_TX_TOGGLE
#endif


static void LUFA_setup(void)
{
    /* Disable watchdog if enabled by bootloader/fuses */
    MCUSR &= ~(1 << WDRF);
    wdt_disable();

    /* Disable clock division */
#if (F_CPU == 8000000)
    clock_prescale_set(clock_div_2);    // 16MHz crystal divided by 2
#else
    clock_prescale_set(clock_div_1);
#endif

    // Leonardo needs. Without this USB device is not recognized.
    USB_Disable();

    USB_Init();

    // for Console_Task
    USB_Device_EnableSOFEvents();
    print_set_sendchar(sendchar);
}



int main(void)
{
    // LED for debug
    LED_TX_INIT;
    LED_TX_ON;

    debug_enable = true;
    debug_keyboard = true;

    host_set_driver(&lufa_driver);
    keyboard_init();

    LUFA_setup();

    /* NOTE: Don't insert time consuming job here.
     * It'll cause unclear initialization failure when DFU reset(worm start).
     */
    sei();

/* Some keyboards bootup quickly and cannot be initialized with this startup wait.*/
    // wait for startup of sendchar routine
    while (USB_DeviceState != DEVICE_STATE_Configured) ;
    if (debug_enable) {
        _delay_ms(1000);
    }

    dprintln("init: done");

    for (;;) {
        keyboard_task();

#if !defined(INTERRUPT_CONTROL_ENDPOINT)
        // LUFA Task for control request
        USB_USBTask();
#endif
    }

    return 0;
}
