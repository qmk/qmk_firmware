#include "MK20D5.h"
#include "wait.h"
#include "gpio_api.h"
#include "PinNames.h"
#include "matrix.h"
#include "timer.h"

#include "action.h"
#include "keycode.h"
#include "host.h"
#include "host_driver.h"
#include "mbed_driver.h"


int main() {
    gpio_t led;
    gpio_init_out(&led, PTA19);

    uint16_t t = 0;

    host_set_driver(&mbed_driver);
    keyboard_init();

    while(1) {
        keyboard_task();

        bool matrix_on = false;
        matrix_scan();
        for (int i = 0; i < MATRIX_ROWS; i++) {
            if (matrix_get_row(i)) {
                matrix_on = true;
                break;
            }
        }
        if (matrix_on)
            gpio_write(&led, 1);
        else {
            if (timer_elapsed(t) > 500) {
                gpio_write(&led, !gpio_read(&led));
                t = timer_read();
            }
        }
    }
}
