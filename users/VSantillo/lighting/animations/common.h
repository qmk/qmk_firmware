static HSV hsvLerp(HSV a, HSV b, float t) {
    // Prepare incoming hue values in QMK format
    // QMK HSV Values are [0, 255], representing a Hue value from [0, 360] degrees
    float a_h = a.h / 255.0f; // Map QMK HSV from [0, 1]
    float b_h = b.h / 255.0f;
    float d = b_h - a_h;

    // If a.h > b.h, swap variables
    if (a_h > b_h) {
        float temp_h = b_h;
        b_h = a_h;
        a_h = temp_h;

        d = -d;
        t = 1.0f - t;
    }

    // Calculate the Hue in HSV space
    float h = 0.0f;
    if (d > 0.5f) {
        a_h = a_h + 1.0f;
        h = fmod((a_h + t * (b_h - a_h)), 1);
    } else if (d <= 0.5f) {
        h = a_h + t * d;
    }

    // Set and interpolate
    HSV hsv;
    hsv.h = (uint8_t)(255*h);
    hsv.s = 255;
    hsv.v = 255;

    // Return HSV value
    return hsv;
}
