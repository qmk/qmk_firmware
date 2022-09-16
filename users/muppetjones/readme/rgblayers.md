# Dynamic Underglow Lighting Per-Layer

This bit of code allows you to define layer lighting that respects your current eeprom settings, e.g., brightness. It does this by storing the base state rgb

## Setup

1. Enable RGB underglow in your `rules.mk`

   ```
   RGBLIGHT_ENABLE = yes      # Enable keyboard RGB underglow
   ```

2. (Optional) Add RGB configuration to your `config.h`

   ```
   #ifdef RGBLIGHT_ENABLE
   // #    define RGBLIGHT_ANIMATIONS
   #    define RGBLIGHT_HUE_STEP 8
   #    define RGBLIGHT_SAT_STEP 16
   #    define RGBLIGHT_VAL_STEP 16
   #    define RGBLIGHT_LIMIT_VAL 150
   #    define RGBLIGHT_SLEEP
   // #    define RGBLIGHT_LAYERS
   #endif
   ```

3. Add `set_layer_hsv` function. This is where you define your layer-specific colors by setting the HSV properties on the `layer_color` pointer. This example uses the QMK RGB configuration parameters to keep the layer colors offset based on the current EEPROM HSV.

   > NOTE: The HSV values should be between 0 and 255, but setting the modulus on saturation causes the lights to go white on my board. I _think_ this is due to overflow, but I haven't had the chance to try and resolve it yet.


    ```
    #ifdef RGBLIGHT_ENABLE
    void set_layer_hsv(layer_state_t state, HSV* layer_color) {
        int32_t h = layer_color->h, s = layer_color->s, v = layer_color->v;
        switch (get_highest_layer(state)) {
            case _RAISE:
                h += 2 * RGBLIGHT_HUE_STEP;
                break;
            case _LOWER:
                h += -2 * RGBLIGHT_HUE_STEP;
                break;
            case _NAV:
                h += 1 * RGBLIGHT_HUE_STEP;
                break;
            case _MOUSE:
                h += -7 * RGBLIGHT_HUE_STEP;
                break;
            default:
                break;
        }
        layer_color->h = h % 255;
        layer_color->s = s;
        layer_color->v = v % 255;
        return;
    }
    #endif
    ```

4. (Optional) If you're using `post_process_record_user`, you'll need to change the name in your keymap to `post_process_record_keymap`. We use the user function to update the HSV state after one of the RGB keycodes is pressed.
