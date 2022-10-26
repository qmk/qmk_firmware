#include "rgb_matrix.h"
#include "sn32f24xb.h"

#if !defined(RGB_MATRIX_HUE_STEP)
#    define RGB_MATRIX_HUE_STEP 8
#endif

#if !defined(RGB_MATRIX_SAT_STEP)
#    define RGB_MATRIX_SAT_STEP 16
#endif

#if !defined(RGB_MATRIX_VAL_STEP)
#    define RGB_MATRIX_VAL_STEP 16
#endif

#if !defined(RGB_MATRIX_SPD_STEP)
#    define RGB_MATRIX_SPD_STEP 16
#endif

#ifdef MATRIX_NO_SCAN
#    define ROWS_PER_HAND (MATRIX_ROWS)

#    ifndef MATRIX_IO_DELAY
#        define MATRIX_IO_DELAY 30
#    endif
#endif
/*
    COLS key / led
    SS8050 transistors NPN driven low
    base      - GPIO
    collector - LED Col pins
    emitter   - VDD

    VDD     GPIO
    (E)     (B)
     |  PNP  |
     |_______|
         |
         |
        (C)
        LED

    ROWS RGB
    SS8550 transistors PNP driven high
    base      - GPIO
    collector - LED RGB row pins
    emitter   - GND

        LED
        (C)
         |
         |
      _______
     |  NPN  |
     |       |
    (B)     (E)
    GPIO    GND
*/
static uint8_t chan_col_order[LED_MATRIX_COLS] = {0}; // track the channel col order
static uint8_t current_row                     = 0;   // LED row scan counter
static uint8_t row_idx                         = 0;   // key row scan counter
#ifdef MATRIX_NO_SCAN
extern matrix_row_t raw_matrix[MATRIX_ROWS];    // raw values
extern matrix_row_t matrix[MATRIX_ROWS];        // debounced values
static matrix_row_t shared_matrix[MATRIX_ROWS]; // scan values
static bool         matrix_locked  = false;     // matrix update check
static bool         matrix_scanned = false;
#endif
static const uint32_t periodticks                      = 256;
static const uint32_t freq                             = (RGB_MATRIX_HUE_STEP * RGB_MATRIX_SAT_STEP * RGB_MATRIX_VAL_STEP * RGB_MATRIX_SPD_STEP * RGB_MATRIX_LED_PROCESS_LIMIT);
static const pin_t    led_row_pins[LED_MATRIX_ROWS_HW] = LED_MATRIX_ROW_PINS; // We expect a R,B,G order here
static const pin_t    led_col_pins[LED_MATRIX_COLS]    = LED_MATRIX_COL_PINS;
static RGB            led_state[RGB_MATRIX_LED_COUNT]; // led state buffer
bool                  enable_pwm = false;
#ifdef UNDERGLOW_RBG // handle underglow with flipped B,G channels
static const uint8_t underglow_leds[UNDERGLOW_LEDS] = UNDERGLOW_IDX;
#endif

#ifdef MATRIX_NO_SCAN
void matrix_output_unselect_delay(uint8_t line, bool key_pressed) {
    for (int i = 0; i < TIME_US2I(MATRIX_IO_DELAY); ++i) {
        __asm__ volatile("" ::: "memory");
    }
}
bool is_matrix_locked(void) {
    return matrix_locked;
}
#endif // MATRIX_NO_SCAN

/* PWM configuration structure. We use timer CT16B1 with 24 channels. */
static PWMConfig pwmcfg = {
    freq,        /* PWM clock frequency. */
    periodticks, /* PWM period (in ticks) 1S (1/10kHz=0.1mS 0.1ms*10000 ticks=1S) */
    NULL,        /* RGB Callback */
    {
        /* Default all channels to disabled - Channels will be configured during init */
        [0 ... 23] = {PWM_OUTPUT_DISABLED, NULL, 0},
    },
    0 /* HW dependent part.*/
};

static void rgb_ch_ctrl(PWMConfig *cfg) {
    /* Enable PWM function, IOs and select the PWM modes for the LED column pins */
    for (uint8_t i = 0; i < LED_MATRIX_COLS; i++) {
        switch (led_col_pins[i]) {
            // Intentional fall-through for the PWM B-pin mapping
            case B8:
                cfg->channels[0].pfpamsk = 1;
            case A0:
                cfg->channels[0].mode = PWM_OUTPUT_ACTIVE_LOW;
                chan_col_order[i]     = 0;
                break;

            case B9:
                cfg->channels[1].pfpamsk = 1;
            case A1:
                cfg->channels[1].mode = PWM_OUTPUT_ACTIVE_LOW;
                chan_col_order[i]     = 1;
                break;

            case B10:
                cfg->channels[2].pfpamsk = 1;
            case A2:
                cfg->channels[2].mode = PWM_OUTPUT_ACTIVE_LOW;
                chan_col_order[i]     = 2;
                break;

            case B11:
                cfg->channels[3].pfpamsk = 1;
            case A3:
                cfg->channels[3].mode = PWM_OUTPUT_ACTIVE_LOW;
                chan_col_order[i]     = 3;
                break;

            case B12:
                cfg->channels[4].pfpamsk = 1;
            case A4:
                cfg->channels[4].mode = PWM_OUTPUT_ACTIVE_LOW;
                chan_col_order[i]     = 4;
                break;

            case B13:
                cfg->channels[5].pfpamsk = 1;
            case A5:
                cfg->channels[5].mode = PWM_OUTPUT_ACTIVE_LOW;
                chan_col_order[i]     = 5;
                break;

            case B14:
                cfg->channels[6].pfpamsk = 1;
            case A6:
                cfg->channels[6].mode = PWM_OUTPUT_ACTIVE_LOW;
                chan_col_order[i]     = 6;
                break;

            case B15:
                cfg->channels[7].pfpamsk = 1;
            case A7:
                cfg->channels[7].mode = PWM_OUTPUT_ACTIVE_LOW;
                chan_col_order[i]     = 7;
                break;

            case C0:
                cfg->channels[8].pfpamsk = 1;
            case A8:
                cfg->channels[8].mode = PWM_OUTPUT_ACTIVE_LOW;
                chan_col_order[i]     = 8;
                break;

            case C1:
                cfg->channels[9].pfpamsk = 1;
            case A9:
                cfg->channels[9].mode = PWM_OUTPUT_ACTIVE_LOW;
                chan_col_order[i]     = 9;
                break;

            case C2:
                cfg->channels[10].pfpamsk = 1;
            case A10:
                cfg->channels[10].mode = PWM_OUTPUT_ACTIVE_LOW;
                chan_col_order[i]      = 10;
                break;

            case C3:
                cfg->channels[11].pfpamsk = 1;
            case A11:
                cfg->channels[11].mode = PWM_OUTPUT_ACTIVE_LOW;
                chan_col_order[i]      = 11;
                break;

            case C4:
                cfg->channels[12].pfpamsk = 1;
            case A12:
                cfg->channels[12].mode = PWM_OUTPUT_ACTIVE_LOW;
                chan_col_order[i]      = 12;
                break;

            case C5:
                cfg->channels[13].pfpamsk = 1;
            case A13:
                cfg->channels[13].mode = PWM_OUTPUT_ACTIVE_LOW;
                chan_col_order[i]      = 13;
                break;

            case C6:
                cfg->channels[14].pfpamsk = 1;
            case A14:
                cfg->channels[14].mode = PWM_OUTPUT_ACTIVE_LOW;
                chan_col_order[i]      = 14;
                break;

            case C7:
                cfg->channels[15].pfpamsk = 1;
            case A15:
                cfg->channels[15].mode = PWM_OUTPUT_ACTIVE_LOW;
                chan_col_order[i]      = 15;
                break;

            case C8:
                cfg->channels[16].pfpamsk = 1;
            case B0:
                cfg->channels[16].mode = PWM_OUTPUT_ACTIVE_LOW;
                chan_col_order[i]      = 16;
                break;

            case C9:
                cfg->channels[17].pfpamsk = 1;
            case B1:
                cfg->channels[17].mode = PWM_OUTPUT_ACTIVE_LOW;
                chan_col_order[i]      = 17;
                break;

            case C10:
                cfg->channels[18].pfpamsk = 1;
            case B2:
                cfg->channels[18].mode = PWM_OUTPUT_ACTIVE_LOW;
                chan_col_order[i]      = 18;
                break;

            case C11:
                cfg->channels[19].pfpamsk = 1;
            case B3:
                cfg->channels[19].mode = PWM_OUTPUT_ACTIVE_LOW;
                chan_col_order[i]      = 19;
                break;

            case C12:
                cfg->channels[20].pfpamsk = 1;
            case B4:
                cfg->channels[20].mode = PWM_OUTPUT_ACTIVE_LOW;
                chan_col_order[i]      = 20;
                break;

            case C13:
                cfg->channels[21].pfpamsk = 1;
            case B5:
                cfg->channels[21].mode = PWM_OUTPUT_ACTIVE_LOW;
                chan_col_order[i]      = 21;
                break;

            case C14:
                cfg->channels[22].pfpamsk = 1;
            case B6:
                cfg->channels[22].mode = PWM_OUTPUT_ACTIVE_LOW;
                chan_col_order[i]      = 22;
                break;

            case C15:
                cfg->channels[23].pfpamsk = 1;
            case B7:
                cfg->channels[23].mode = PWM_OUTPUT_ACTIVE_LOW;
                chan_col_order[i]      = 23;
                break;
        }
    }
}
static void rgb_callback(PWMDriver *pwmp);

static void shared_matrix_rgb_enable(void) {
    pwmcfg.callback = rgb_callback;
    pwmEnablePeriodicNotification(&PWMD1);
}

static void shared_matrix_rgb_disable_pwm(void) {
    // Disable PWM outputs on column pins
    for (uint8_t y = 0; y < LED_MATRIX_COLS; y++) {
        pwmDisableChannelI(&PWMD1, chan_col_order[y]);
    }
}

static void shared_matrix_rgb_disable_leds(void) {
    // Disable LED outputs on RGB channel pins
    for (uint8_t x = 0; x < LED_MATRIX_ROWS_HW; x++) {
        writePinLow(led_row_pins[x]);
    }
}

static void update_pwm_channels(PWMDriver *pwmp) {
    matrix_row_t row_shifter = MATRIX_ROW_SHIFTER;
    for (uint8_t col_idx = 0; col_idx < LED_MATRIX_COLS; col_idx++, row_shifter <<= 1) {
#ifdef MATRIX_NO_SCAN
#    if (DIODE_DIRECTION == ROW2COL)
        // Scan the key matrix column
        if (!matrix_scanned) {
            matrix_locked = true;
            matrix_read_rows_on_col(shared_matrix, col_idx, row_shifter);
        }
#    endif // DIODE_DIRECTION == ROW2COL
#endif     // MATRIX_NO_SCAN
        uint8_t led_index = g_led_config.matrix_co[row_idx][col_idx];
        // Check if we need to enable RGB output
        if (led_state[led_index].b != 0) enable_pwm |= true;
        if (led_state[led_index].g != 0) enable_pwm |= true;
        if (led_state[led_index].r != 0) enable_pwm |= true;
        // Update matching RGB channel PWM configuration
        switch (current_row % LED_MATRIX_ROW_CHANNELS) {
            case 0:
                if (enable_pwm) pwmEnableChannelI(pwmp, chan_col_order[col_idx], led_state[led_index].b);
                break;
            case 1:
                if (enable_pwm) pwmEnableChannelI(pwmp, chan_col_order[col_idx], led_state[led_index].g);
                break;
            case 2:
                if (enable_pwm) pwmEnableChannelI(pwmp, chan_col_order[col_idx], led_state[led_index].r);
                break;
            default:;
        }
    }
}
static void rgb_callback(PWMDriver *pwmp) {
    chSysLockFromISR();
    // Disable the interrupt
    pwmDisablePeriodicNotificationI(pwmp);
    // Advance to the next LED RGB channels
    current_row++;
    if (current_row >= LED_MATRIX_ROWS_HW) current_row = 0;
    uint8_t last_row_idx = row_idx;
    // Advance to the next key matrix row
    if (current_row % LED_MATRIX_ROW_CHANNELS == 2) row_idx++;
    if (row_idx >= LED_MATRIX_ROWS) row_idx = 0;
    // Disable LED output before scanning the key matrix
    shared_matrix_rgb_disable_leds();
    shared_matrix_rgb_disable_pwm();
#ifdef MATRIX_NO_SCAN
#    if (DIODE_DIRECTION == COL2ROW)
    // Scan the key matrix row
    if (!matrix_scanned) {
        matrix_locked = true;
        matrix_read_cols_on_row(shared_matrix, row_idx);
    }
#    endif // DIODE_DIRECTION == COL2ROW
#endif     // MATRIX_NO_SCAN
    update_pwm_channels(pwmp);
#ifdef MATRIX_NO_SCAN
    // Assume we have finished scanning the matrix
    if (last_row_idx > row_idx) {
        matrix_scanned = true;
        matrix_locked  = false;
    }
#endif // MATRIX_NO_SCAN
    if (enable_pwm) writePinHigh(led_row_pins[current_row]);
    // Advance the timer to just before the wrap-around, that will start a new PWM cycle
    pwm_lld_change_counter(pwmp, 0xFFFF);
    // Enable the interrupt
    pwmEnablePeriodicNotificationI(pwmp);
    chSysUnlockFromISR();
}

void SN32F24xB_init(void) {
    for (uint8_t x = 0; x < LED_MATRIX_ROWS_HW; x++) {
        setPinOutput(led_row_pins[x]);
        writePinLow(led_row_pins[x]);
    }
    // Determine which PWM channels we need to control
    rgb_ch_ctrl(&pwmcfg);
#ifdef MATRIX_NO_SCAN
    // initialize matrix state: all keys off
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        shared_matrix[i] = 0;
    }
#endif // MATRIX_NO_SCAN
    pwmStart(&PWMD1, &pwmcfg);
    shared_matrix_rgb_enable();
}

void SN32F24xB_set_color(int index, uint8_t r, uint8_t g, uint8_t b) {
#ifdef UNDERGLOW_RBG
    bool flip_gb = false;
    for (uint8_t led_id = 0; led_id < UNDERGLOW_LEDS; led_id++) {
        if (underglow_leds[led_id] == index) {
            flip_gb = true;
        }
    }
    if (flip_gb) {
        led_state[index].r = r;
        led_state[index].b = g;
        led_state[index].g = b;
    } else {
#endif // UNDERGLOW_RBG
        led_state[index].r = r;
        led_state[index].b = b;
        led_state[index].g = g;
#ifdef UNDERGLOW_RBG
    }
#endif // UNDERGLOW_RBG
}

void SN32F24xB_set_color_all(uint8_t r, uint8_t g, uint8_t b) {
    for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        SN32F24xB_set_color(i, r, g, b);
    }
}
#ifdef MATRIX_NO_SCAN
bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    if (!matrix_scanned) return false; // Nothing to process until we have the matrix scanned

    bool changed = memcmp(raw_matrix, shared_matrix, sizeof(shared_matrix)) != 0;
    if (changed) memcpy(raw_matrix, shared_matrix, sizeof(shared_matrix));

    matrix_scanned = false;

    return changed;
}
#endif // MATRIX_NO_SCAN