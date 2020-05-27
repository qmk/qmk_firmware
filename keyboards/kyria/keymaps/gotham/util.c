#pragma once

bool is_keyboard_left(void) {
#if defined(MASTER_LEFT)
    return is_keyboard_master();
#elif defined(MASTER_RIGHT)
    return !is_keyboard_master();
#elif defined(SPLIT_HAND_PIN)
    // Test pin SPLIT_HAND_PIN for High/Low, if low it's right hand
    setPinInputHigh(SPLIT_HAND_PIN);
    bool x = !readPin(SPLIT_HAND_PIN);
    setPinInput(SPLIT_HAND_PIN);
    return x;
#elif defined(EE_HANDS)
    return eeconfig_read_handedness();
#endif

    return is_keyboard_master();
}
