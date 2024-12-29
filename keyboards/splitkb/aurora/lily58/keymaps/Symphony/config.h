#define MASTER_LEFT
#define OS_DETECTION_DEBOUNCE_250
#define OS_DETECTION_KEYBOARD_RESET
#define OS_DETECTION_SINGLE_REPORT
#define RGB_MATRIX_LAYER_EFFECTS
// RGB Matrix configuration
#define RGB_DI_PIN D3                 // Pin connected to RGB
#define DRIVER_LED_TOTAL 68           // Total number of LEDs
#define RGB_MATRIX_KEYPRESSES         // Enable reactive keypress effects
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS // Enable framebuffer effects
// #define SPLIT_TRANSPORT_MIRROR       // Enable to mirror effects
#define SPLIT_LAYER_STATE_ENABLE

#define RGB_MATRIX_SPLIT { 34, 34 }  // Adjust numbers to match your setup

#define USE_SERIAL
#define SOFT_SERIAL_PIN D2
