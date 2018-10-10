#include <avr/io.h>
#include <avr/power.h>
#include <avr/wdt.h>
#include "lufa.h"
#include "print.h"
#include "sendchar.h"
#include "xm04.h"
#include "xm04_task.h"
//#include "serial.h"
#include "keyboard.h"
#include "keycode.h"
#include "action.h"
#include "action_util.h"
#include "wait.h"
#include "suart.h"
#include "suspend.h"
extern bool dozing;
extern bool sleeping;
extern bool force_usb;

static void SetupHardware(void)
{
    /* Disable watchdog if enabled by bootloader/fuses */
    MCUSR &= ~(1 << WDRF);
    wdt_disable();

    /* Disable clock division */
    clock_prescale_set(clock_div_1);

    // Leonardo needs. Without this USB device is not recognized.
    USB_Disable();

    USB_Init();

    // for Console_Task
    USB_Device_EnableSOFEvents();
}

int main(void)  __attribute__ ((weak));
int main(void)
{
    SetupHardware();
    sei();

    /* wait for USB startup to get ready for debug output */
    uint8_t timeout = 255;  // timeout when USB is not available(Bluetooth)
    while (timeout-- && USB_DeviceState != DEVICE_STATE_Configured) {
        wait_ms(4);
#if defined(INTERRUPT_CONTROL_ENDPOINT)
        ;
#else
        USB_USBTask();
#endif
    }
    if (USB_DeviceState == DEVICE_STATE_Configured) {
        force_usb = true;
    }
    print("\nUSB init\n");

    xm04_init();
    xm04_task_init();

    /* init modules */
    keyboard_init();


#ifdef SLEEP_LED_ENABLE
    sleep_led_init();
#endif

    print("Keyboard start\n");
    while (1) {
        if (dozing) {  //if using while, when waking up the first or more keys will be missed.
            suspend_power_down();
            if (suspend_wakeup_condition()) {
                dozing = 0;
                if (sleeping) {
                    sleeping = 0;
                    turn_on_bt();
                }
            }
        }
        if (!sleeping){
            keyboard_task();
#if !defined(INTERRUPT_CONTROL_ENDPOINT)
            USB_USBTask();
#endif
            xm04_task();
        }
    }
}
