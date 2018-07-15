#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    LAYOUT(
        TO(1), KC_A, KC_B, KC_C, KC_D, KC_E),

    LAYOUT(
        TO(2), KC_F, KC_G, KC_H, KC_I, KC_J),

    LAYOUT(
        TO(3), KC_K, KC_L, KC_M, KC_N, KC_O),

    LAYOUT(
        TO(4), KC_P, KC_Q, KC_R, KC_S, KC_T),

    LAYOUT(
        TO(5), KC_U, KC_V, KC_W, KC_X, KC_Y),

    LAYOUT(
        TO(0), KC_Z, KC_1, KC_2, KC_3, KC_4)};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    //keyevent_t event = record->event;

    switch (id)
    {
    case 0:
        if (record->event.pressed)
        {
            return MACRO(T(T), T(G), T(L), T(H), T(F), T(ENT), END);
        }
        break;
    case 1:
        if (record->event.pressed)
        {
            return MACRO(T(T), T(G), T(G), T(ENT), END);
        }
        break;
    case 2:
        if (record->event.pressed)
        {
            return MACRO(D(NO), T(L), U(NO), END);
        }
        break;
    case 3:
        if (record->event.pressed)
        {
            return MACRO(D(LCTL), T(Z), U(LCTL), END);
        }
        break;
    case 4:
        if (record->event.pressed)
        {
            return MACRO(D(LCTL), D(LSFT), T(Z), U(LSFT), U(LCTL), END);
        }
        break;
    case 5:
        if (record->event.pressed)
        {
            return MACRO(D(LCTL), T(X), U(LCTL), END);
        }
        break;
    case 6:
        if (record->event.pressed)
        {
            return MACRO(D(LCTL), T(C), U(LCTL), END);
        }
        break;
    case 7:
        if (record->event.pressed)
        {
            return MACRO(D(LCTL), T(V), U(LCTL), END);
        }
        break;
    }
    return MACRO_NONE;
}

// M6-A LEDs are connected to D6, B6, F5, B4, C7, F7
// This is 1-based because I copied it from Knops code.
void set_switch_led(int ledId, bool state)
{
    if (state)
    {
        switch (ledId)
        {
        case 1:
            PORTD |= (1 << 6);
            break;
        case 2:
            PORTB |= (1 << 6);
            break;
        case 3:
            PORTF |= (1 << 5);
            break;
        case 4:
            PORTB |= (1 << 4);
            break;
        case 5:
            PORTC |= (1 << 7);
            break;
        case 6:
            PORTF |= (1 << 7);
            break;
        }
    }
    else
    {
        switch (ledId)
        {
        case 1:
            PORTD &= ~(1 << 6);
            break;
        case 2:
            PORTB &= ~(1 << 6);
            break;
        case 3:
            PORTF &= ~(1 << 5);
            break;
        case 4:
            PORTB &= ~(1 << 4);
            break;
        case 5:
            PORTC &= ~(1 << 7);
            break;
        case 6:
            PORTF &= ~(1 << 7);
            break;
        }
    }
}

void set_layer_led(int layerId)
{
    // UNUSED
}

void led_set_layer(int layer);

void matrix_init_user(void)
{
    led_init_ports();
    led_set_layer(0);
}

void matrix_scan_user(void)
{
}

// M6-A LEDs are connected to D6, B6, F5, B4, C7, F7
void led_init_ports()
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

void led_set_user(uint8_t usb_led)
{

    if (usb_led & (1 << USB_LED_NUM_LOCK))
    {
    }
    else
    {
    }

    if (usb_led & (1 << USB_LED_CAPS_LOCK))
    {
    }
    else
    {
    }

    if (usb_led & (1 << USB_LED_SCROLL_LOCK))
    {
    }
    else
    {
    }

    if (usb_led & (1 << USB_LED_COMPOSE))
    {
    }
    else
    {
    }

    if (usb_led & (1 << USB_LED_KANA))
    {
    }
    else
    {
    }
}

void led_set_layer(int layer)
{
    switch (layer)
    {
    case 0:
        set_switch_led(1, true);
        set_switch_led(2, false);
        set_switch_led(3, false);
        set_switch_led(4, false);
        set_switch_led(5, false);
        set_switch_led(6, false);
        break;
    case 1:
        set_switch_led(1, false);
        set_switch_led(2, true);
        set_switch_led(3, false);
        set_switch_led(4, false);
        set_switch_led(5, false);
        set_switch_led(6, false);
        break;
    case 2:
        set_switch_led(1, false);
        set_switch_led(2, false);
        set_switch_led(3, true);
        set_switch_led(4, false);
        set_switch_led(5, false);
        set_switch_led(6, false);
        break;
    case 3:
        set_switch_led(1, false);
        set_switch_led(2, false);
        set_switch_led(3, false);
        set_switch_led(4, true);
        set_switch_led(5, false);
        set_switch_led(6, false);
        break;
    case 4:
        set_switch_led(1, false);
        set_switch_led(2, false);
        set_switch_led(3, false);
        set_switch_led(4, false);
        set_switch_led(5, true);
        set_switch_led(6, false);
        break;
    case 5:
        set_switch_led(1, false);
        set_switch_led(2, false);
        set_switch_led(3, false);
        set_switch_led(4, false);
        set_switch_led(5, false);
        set_switch_led(6, true);
        break;
    default:
        set_switch_led(1, true);
        set_switch_led(2, true);
        set_switch_led(3, true);
        set_switch_led(4, true);
        set_switch_led(5, true);
        set_switch_led(6, true);
        break;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    switch (keycode)
    {
    case TO(0):
        if (record->event.pressed)
        {
            led_set_layer(0);
        }
        break;
    case TO(1):
        if (record->event.pressed)
        {
            led_set_layer(1);
        }
        break;
    case TO(2):
        if (record->event.pressed)
        {
            led_set_layer(2);
        }
        break;
    case TO(3):
        if (record->event.pressed)
        {
            led_set_layer(3);
        }
        break;
    case TO(4):
        if (record->event.pressed)
        {
            led_set_layer(4);
        }
        break;
    case TO(5):
        if (record->event.pressed)
        {
            led_set_layer(5);
        }
        break;
    }
    return true;
}
