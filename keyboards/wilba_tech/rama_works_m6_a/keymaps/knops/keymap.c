#include QMK_KEYBOARD_H

/*KNOPS_MISC*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /*KNOPS_LAYOUT*/

};

void set_led_state(int ledId, bool state)
{
    if (state)
    {
        switch (ledId)
        {
        case 0:
            PORTD |= (1 << 6);
            break;
        case 1:
            PORTB |= (1 << 6);
            break;
        case 2:
            PORTF |= (1 << 5);
            break;
        case 3:
            PORTB |= (1 << 4);
            break;
        case 4:
            PORTC |= (1 << 7);
            break;
        case 5:
            PORTF |= (1 << 7);
            break;
        }
    }
    else
    {
        switch (ledId)
        {
        case 0:
            PORTD &= ~(1 << 6);
            break;
        case 1:
            PORTB &= ~(1 << 6);
            break;
        case 2:
            PORTF &= ~(1 << 5);
            break;
        case 3:
            PORTB &= ~(1 << 4);
            break;
        case 4:
            PORTC &= ~(1 << 7);
            break;
        case 5:
            PORTF &= ~(1 << 7);
            break;
        }
    }
}

void led_init_ports_user(void)
{
    // Switch #1
    DDRD |= (1 << 6);
    PORTD &= ~(1 << 6);

    // Switch #2
    DDRB |= (1 << 6);
    PORTB &= ~(1 << 6);

    // Switch #3
    DDRF |= (1 << 5);
    PORTF &= ~(1 << 5);

    // Switch #4
    DDRB |= (1 << 4);
    PORTB &= ~(1 << 4);

    // Switch #5
    DDRC |= (1 << 7);
    PORTC &= ~(1 << 7);

    // Switch #6
    DDRF |= (1 << 7);
    PORTF &= ~(1 << 7);
}

void led_set_layer(int layer)
{

    /*KNOPS_SIMPLELED_STATES*/
}

void matrix_init_user(void)
{
    led_init_ports_user();

    led_set_layer(0);

    /*KNOPS_INIT*/
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    //keyevent_t event = record->event;

    /*KNOPS_MACRO*/
    return NULL;
}

void matrix_scan_user(void)
{
    /*KNOPS_SCAN*/
}

void led_set_user(uint8_t usb_led)
{

    /*KNOPS_FUNCTIONALLED_STATES*/
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{

    /*KNOPS_PROCESS_STATE*/
    return NULL;
}
