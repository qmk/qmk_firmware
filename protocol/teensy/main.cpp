#include "WProgram.h"
#include "debug.h"
#include "timer.h"
#include "keyboard.h"
#include "led.h"
#include "host.h"
#include "host_driver.h"
#include "teensy_driver.h"

elapsedMillis blinker;

int main(void)
{
    timer_init();

#ifdef CONSOLE_ENABLE
    debug_enable = true;
    debug_keyboard = true;
    debug_mouse = true;
    while (!Serial) {}
#endif

    dprintln("Setting host driver");
    host_set_driver(&teensy_driver);

    dprintln("Initializing keyboard");
    keyboard_init();

    dprintln("Entering task loop");
    while (1) {
        keyboard_task();
    }
}

