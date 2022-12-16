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

#define ROWS_PER_HAND (MATRIX_ROWS)

#if !defined(MATRIX_IO_DELAY)
#    define MATRIX_IO_DELAY 30
#endif

#if !defined(PWM_OUTPUT_ACTIVE_LEVEL)
#    define PWM_OUTPUT_ACTIVE_LEVEL PWM_OUTPUT_ACTIVE_LOW
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
static uint8_t        chan_col_order[LED_MATRIX_COLS] = {0};    // track the channel col order
static uint8_t        current_row                     = 0;      // LED row scan counter
static uint8_t        row_idx                         = 0;      // key row scan counter
extern matrix_row_t   raw_matrix[MATRIX_ROWS];                  // raw values
extern matrix_row_t   matrix[MATRIX_ROWS];                      // debounced values
static matrix_row_t   shared_matrix[MATRIX_ROWS];               // scan values
static volatile bool  matrix_locked                    = false; // matrix update check
static volatile bool  matrix_scanned                   = false;
static const uint32_t periodticks                      = 256;
static const uint32_t freq                             = (RGB_MATRIX_HUE_STEP * RGB_MATRIX_SAT_STEP * RGB_MATRIX_VAL_STEP * RGB_MATRIX_SPD_STEP * RGB_MATRIX_LED_PROCESS_LIMIT);
static const pin_t    led_row_pins[LED_MATRIX_ROWS_HW] = LED_MATRIX_ROW_PINS; // We expect a R,B,G order here
static const pin_t    led_col_pins[LED_MATRIX_COLS]    = LED_MATRIX_COL_PINS;
static RGB            led_state[RGB_MATRIX_LED_COUNT];     // led state buffer
static RGB            led_state_buf[RGB_MATRIX_LED_COUNT]; // led state buffer
#ifdef UNDERGLOW_RBG                                       // handle underglow with flipped B,G channels
static const uint8_t underglow_leds[UNDERGLOW_LEDS] = UNDERGLOW_IDX;
#endif

void matrix_output_unselect_delay(uint8_t line, bool key_pressed) {
    for (int i = 0; i < TIME_US2I(MATRIX_IO_DELAY); ++i) {
        __asm__ volatile("" ::: "memory");
    }
}
bool matrix_available(void) {
    return matrix_scanned;
}

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
        // Only P0.0 to P2.15 can be used as pwm output
        if (led_col_pins[i] > C15) continue;
        /* We use a tricky here, accordint to pfpa table of sn32f240b datasheet,
           pwm channel and pfpa of pin Px.y can be calculated as below:
             channel = (x*16+y)%24
             pfpa = 1, when (x*16+y)>23
        */
        uint8_t pio_value             = ((uint32_t)(PAL_PORT(led_col_pins[i])) - (uint32_t)(PAL_PORT(A0))) / ((uint32_t)(PAL_PORT(B0)) - (uint32_t)(PAL_PORT(A0))) * 16 + PAL_PAD(led_col_pins[i]);
        uint8_t ch_idx                = pio_value % 24;
        chan_col_order[i]             = ch_idx;
        cfg->channels[ch_idx].pfpamsk = pio_value > 23;
        cfg->channels[ch_idx].mode    = PWM_OUTPUT_ACTIVE_LEVEL;
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
        pwmDisableChannel(&PWMD1, chan_col_order[y]);
    }
}

static void shared_matrix_rgb_disable_leds(void) {
    // Disable LED outputs on RGB channel pins
    for (uint8_t x = 0; x < LED_MATRIX_ROWS_HW; x++) {
        ATOMIC_BLOCK_FORCEON {
            writePinLow(led_row_pins[x]);
        }
    }
}

static void update_pwm_channels(PWMDriver *pwmp) {
    bool         enable_pwm_output = false;
    matrix_row_t row_shifter       = MATRIX_ROW_SHIFTER;
    for (uint8_t col_idx = 0; col_idx < LED_MATRIX_COLS; col_idx++, row_shifter <<= 1) {
#if (DIODE_DIRECTION == ROW2COL)
        // Scan the key matrix column
        if (!matrix_scanned) {
            matrix_locked = true;
            matrix_read_rows_on_col(shared_matrix, col_idx, row_shifter);
        }
#endif // DIODE_DIRECTION == ROW2COL
        uint8_t led_index = g_led_config.matrix_co[row_idx][col_idx];
        // Check if we need to enable RGB output
        if (led_state[led_index].b != 0) enable_pwm_output |= true;
        if (led_state[led_index].g != 0) enable_pwm_output |= true;
        if (led_state[led_index].r != 0) enable_pwm_output |= true;
        // Update matching RGB channel PWM configuration
        switch (current_row % LED_MATRIX_ROW_CHANNELS) {
            case 0:
                pwmEnableChannel(pwmp, chan_col_order[col_idx], led_state[led_index].b);
                break;
            case 1:
                pwmEnableChannel(pwmp, chan_col_order[col_idx], led_state[led_index].g);
                break;
            case 2:
                pwmEnableChannel(pwmp, chan_col_order[col_idx], led_state[led_index].r);
                break;
            default:;
        }
    }
    // Enable RGB output
    if (enable_pwm_output) {
        ATOMIC_BLOCK_FORCEON {
            writePinHigh(led_row_pins[current_row]);
        }
    }
#if (DIODE_DIRECTION == ROW2COL)
    // The whole matrix has been scanned
    matrix_locked  = false;
    matrix_scanned = true;
#endif // DIODE_DIRECTION == ROW2COL
}
static void rgb_callback(PWMDriver *pwmp) {
    // Disable the interrupt
    pwmDisablePeriodicNotification(pwmp);
    // Advance to the next LED RGB channels
    current_row++;
    if (current_row >= LED_MATRIX_ROWS_HW) current_row = 0;
#if (DIODE_DIRECTION == COL2ROW)
    uint8_t last_row_idx = row_idx;
#endif // DIODE_DIRECTION == COL2ROW
    // Advance to the next key matrix row
    if (current_row % LED_MATRIX_ROW_CHANNELS == 2) row_idx++;
    if (row_idx >= LED_MATRIX_ROWS) row_idx = 0;
    // Disable LED output before scanning the key matrix
    shared_matrix_rgb_disable_leds();
    shared_matrix_rgb_disable_pwm();
#if (DIODE_DIRECTION == COL2ROW)
    // Scan the key matrix row
    static uint8_t first_scanned_row;
    if (!matrix_scanned) {
        if (!matrix_locked) {
            matrix_locked     = true;
            first_scanned_row = row_idx;
        } else {
            if ((last_row_idx != row_idx) && (row_idx == first_scanned_row)) {
                matrix_locked  = false;
                matrix_scanned = true;
            }
        }
        if (matrix_locked) {
            matrix_read_cols_on_row(shared_matrix, row_idx);
        }
    }
#endif // DIODE_DIRECTION == COL2ROW
    update_pwm_channels(pwmp);
    chSysLockFromISR();
    // Advance the timer to just before the wrap-around, that will start a new PWM cycle
    pwm_lld_change_counter(pwmp, 0xFFFF);
    // Enable the interrupt
    pwmEnablePeriodicNotificationI(pwmp);
    chSysUnlockFromISR();
}

void SN32F24xB_init(void) {
    for (uint8_t x = 0; x < LED_MATRIX_ROWS_HW; x++) {
        ATOMIC_BLOCK_FORCEON {
            setPinOutput(led_row_pins[x]);
            writePinLow(led_row_pins[x]);
        }
    }
    // Determine which PWM channels we need to control
    rgb_ch_ctrl(&pwmcfg);
    // initialize matrix state: all keys off
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        shared_matrix[i] = 0;
    }
    pwmStart(&PWMD1, &pwmcfg);
    shared_matrix_rgb_enable();
}

void SN32F24xB_flush(void) {
    memcpy(led_state, led_state_buf, sizeof(RGB) * RGB_MATRIX_LED_COUNT);
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
        led_state_buf[index].r = r;
        led_state_buf[index].b = g;
        led_state_buf[index].g = b;
    } else {
#endif // UNDERGLOW_RBG
        led_state_buf[index].r = r;
        led_state_buf[index].b = b;
        led_state_buf[index].g = g;
#ifdef UNDERGLOW_RBG
    }
#endif // UNDERGLOW_RBG
}

void SN32F24xB_set_color_all(uint8_t r, uint8_t g, uint8_t b) {
    for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        SN32F24xB_set_color(i, r, g, b);
    }
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    if (!matrix_scanned) return false; // Nothing to process until we have the matrix scanned

    bool changed = memcmp(raw_matrix, shared_matrix, sizeof(shared_matrix)) != 0;
    if (changed) memcpy(raw_matrix, shared_matrix, sizeof(shared_matrix));

    matrix_scanned = false;

    return changed;
}
