
// DEFINE MACROS
#define ARRAYSIZE(arr)  sizeof(arr)/sizeof(arr[0])


// LAYERS
enum custom_layers {
    _BASE,
    _FN1,
    _MO2,
    _MO3,
};

#define _LOWER  _MO2
#define _RAISE  _MO3

// KEYCODES
enum custom_keycodes {
  KC_00 = SAFE_RANGE,
  KC_WINLCK,    //Toggles Win key on and off
  RGB_TOI,   // Timeout idle time up
  RGB_TOD,   // Timeout idle time down
};


//bool _isWinKeyDisabled = false;



// TIMEOUTS
#define TIMEOUT_THRESHOLD_DEFAULT   5    // default timeout minutes
#define TIMEOUT_THRESHOLD_MAX       140  // upper limits (2 hours and 10 minutes -- no rgb indicators above this value)
static uint16_t timeout_timer = 0;
static uint16_t timeout_counter = 0;  //in minute intervals
static uint16_t timeout_threshold = TIMEOUT_THRESHOLD_DEFAULT;

void timeout_reset_timer(void) {
    timeout_timer = timer_read();
    timeout_counter = 0;
};

void timeout_update_threshold(bool increase) {
    if (increase && timeout_threshold < TIMEOUT_THRESHOLD_MAX) timeout_threshold++;
    if (!increase && timeout_threshold > 0) timeout_threshold--;
};

void timeout_tick(void) {
    if (timeout_threshold > 0) {
        if (timer_elapsed(timeout_timer) >= 60000) { // 1 minute tick
            timeout_counter++;
            timeout_timer = timer_read();
        }
        #ifdef RGB_MATRIX_ENABLE
            if (timeout_threshold > 0 && timeout_counter >= timeout_threshold) {
                rgb_matrix_disable_noeeprom();
            }
        #endif
    } // timeout_threshold = 0 will disable timeout
}
