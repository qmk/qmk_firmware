#pragma once

#ifdef RGBLIGHT_ENABLE
#define RGBLIGHT_EFFECT_BREATHING
#endif

#ifdef OLED_ENABLE
#define SPLIT_LAYER_STATE_ENABLE    // This enables syncing of the layer state between both halves
#define SPLIT_LED_STATE_ENABLE      // This enables syncing of the Host LED status (caps lock, num lock, etc) between both halves
#endif