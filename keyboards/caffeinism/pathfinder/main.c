#include "keyboard.h"
#include "quantum.h"

void platform_setup(void);
void protocol_setup(void);
void protocol_init(void);
void protocol_task(void);
void protocol_task(void);

int main(void) {
    platform_setup();
    protocol_setup();
    keyboard_setup();

    protocol_init();

    /* Main loop with timeout */
    uint16_t key_timer = timer_read32();
    while (timer_elapsed32(key_timer) < LOOP_TIMEOUT) {
        protocol_task();
        housekeeping_task();
    }

    reset_keyboard();
    return 0;
}
