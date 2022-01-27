
#include "v1.h"

void matrix_init_kb(void)
{
    setPinOutput(LED_KEY_PRESS_PIN);
    writePinHigh(LED_KEY_PRESS_PIN);

    matrix_init_user();
    led_update_kb(host_keyboard_led_state());
}

bool led_update_kb(led_t led_state)
{
    writePin(LED_CAPS_LOCK_PIN, !led_state.caps_lock);
    writePin(LED_NUM_LOCK_PIN, !led_state.num_lock);

    return true;
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record)
{
    if (record->event.pressed)
    {
        writePinLow(LED_KEY_PRESS_PIN);
    }
    else
    {
        writePinHigh(LED_KEY_PRESS_PIN);
    }

    return true;
}
