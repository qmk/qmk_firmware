#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
  // Key Matrix to LED Index
  { 5, 0 }
}, {
  // LED Index to Physical Position
  { 0,  64 }, { 0,  32 }, { 0,  0 }, { 224,  0 }, { 224,  32 }, { 224,  64 }
}, {
  // LED Index to Flag
  4, 2, 2, 2, 2, 4
} };

#endif