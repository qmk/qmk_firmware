bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t index_to_light = NO_LED;

    switch (get_highest_layer(layer_state | default_layer_state)) {
        case 1:
            index_to_light = 3;
            break;
        case 2:
            index_to_light = 2;
            break;
        case 3:
            index_to_light = 1;
            break;
        case 4:
            index_to_light = 0;
            break;
        default:
            break;
    }

    // Light up only the selected LED if it's within the current render range
    if (index_to_light != NO_LED && index_to_light >= led_min && index_to_light < led_max) {
        rgb_matrix_set_color(index_to_light, RGB_GREEN); // You can choose any color
    }

    return false;  // Let other lighting effects (if any) still apply
}
