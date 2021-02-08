#include "gc_read.h"
#include "gc_controller.h"

#define CONTROLLER_TIMEOUT 60

bool init_message[9] = {0, 0, 0, 0, 0, 0, 0, 0, 1};
bool request_message[25] = {
    0, 1, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 1, 1, 
    0, 0, 0, 0, 0, 0, 1, 0, 1};

void start_message(void) {
    setPinOutput(GAMECUBE_DATA_PIN);
    writePinLow(GAMECUBE_DATA_PIN);
}

void send_bit(bool b) {
    if (b) {
        writePinLow(GAMECUBE_DATA_PIN);
        wait_ns(900);
        writePinHigh(GAMECUBE_DATA_PIN);
        wait_ns(2900);
    } else {
        writePinLow(GAMECUBE_DATA_PIN);
        wait_ns(2900);
        writePinHigh(GAMECUBE_DATA_PIN);
        wait_ns(900);
    }
}

void wait_for_ready(void) {
    setPinInputHigh(GAMECUBE_DATA_PIN);

    // wait for long high
    uint8_t ready = 0;
    while (ready < 5) {
        if (readPin(GAMECUBE_DATA_PIN))
            ready++;
        else
            ready = 0;
        wait_us(1);
    }
}

void end_message(void) {
    setPinInputHigh(GAMECUBE_DATA_PIN);
}

uint8_t buffer[9] = {0};
uint16_t buttons_debounce = 0;
bool initialised = false;
bool calibrated = false;
uint8_t mid_values[4] = {128, 128, 128, 128};
uint8_t max_values[4] = {210, 210, 210, 210};
uint8_t min_values[4] = {35, 35, 35, 35};

void gamecube_init(void) {
    setPinInputHigh(GAMECUBE_DATA_PIN);
}

void gamecube_scan(uint16_t * buttons, uint8_t * joysticks) {
    bool exiting = false;
    uint16_t timeout_counter = 0;

    // somehow we're missing the first bit, which can safely be ignored
    // i'm not sure if it's something with the timing or what
    uint8_t buffer_bit = 1;

    chSysLock();

    if (!initialised) {
        wait_for_ready();
        
        start_message();
        for (uint8_t i = 0; i < 9; i++)
            send_bit(init_message[i]);
        end_message();

        initialised = true;
    }

    wait_for_ready();

    start_message();
    for (uint8_t i = 0; i < 25; i++)
        send_bit(request_message[i]);
    end_message();

    while (!exiting) {
        timeout_counter = 0;
        // wait for low or timeout
        while (readPin(GAMECUBE_DATA_PIN)) {
            wait_ns(100);
            timeout_counter++;
            if (timeout_counter > CONTROLLER_TIMEOUT) {
                exiting = true;
                break;
            }
        }

        if (!exiting) {
            // wait for the data part
            wait_ns(1950);
            bool b = readPin(GAMECUBE_DATA_PIN);
            if (b)
                buffer[buffer_bit / 8] |=  (1 << (7 - (buffer_bit % 8)));
            else
                buffer[buffer_bit / 8] &= ~(1 << (7 - (buffer_bit % 8)));
            buffer_bit++;

            // wait for high
            while (!readPin(GAMECUBE_DATA_PIN));
        }
    }

    chSysUnlock();

    // basic debouncing for buttons
    uint16_t combined_buttons = buffer[0] | (buffer[1] << 8);
    *buttons |= buttons_debounce & combined_buttons;
    *buttons &= buttons_debounce | combined_buttons;
    buttons_debounce = combined_buttons;

   if (!calibrated && mid_values[0] > 0) {
        mid_values[0] = buffer[2];
        mid_values[1] = buffer[3];
        mid_values[2] = buffer[4];
        mid_values[3] = buffer[5];
        calibrated = true;
    }

    if (max_values[0] < buffer[2])
        max_values[0] = buffer[2];
    if (max_values[1] < buffer[3])
        max_values[1] = buffer[3];
    if (max_values[2] < buffer[4])
        max_values[2] = buffer[4];
    if (max_values[3] < buffer[5])
        max_values[3] = buffer[5];

    if (min_values[0] > buffer[2])
        min_values[0] = buffer[2];
    if (min_values[1] > buffer[3])
        min_values[1] = buffer[3];
    if (min_values[2] > buffer[4])
        min_values[2] = buffer[4];
    if (min_values[3] > buffer[5])
        min_values[3] = buffer[5];

    // values from my GC controller in Windows
    // 30 - 138 - 236
    // 20 - 124 - 225
    // 37 - 135 - 222
    // 34 - 126 - 216

    // this should be 127? i don't understand what i'm doing wrong yet
    #define JOYSTICK_SCALER 180.0

    int32_t lx_temp = (int16_t)buffer[2] - mid_values[0];
    if (lx_temp > 0)
        lx_temp *= JOYSTICK_SCALER / (max_values[0]-mid_values[0]);
    else
        lx_temp *= JOYSTICK_SCALER / (mid_values[0]-min_values[0]);
    lx_temp += STICK_CENTER;
    if (lx_temp > 255)
        lx_temp = 255;
    if (lx_temp < 0)
        lx_temp = 0;

    int32_t ly_temp = (int16_t)buffer[3] - mid_values[1];
    if (ly_temp > 0)
        ly_temp *= JOYSTICK_SCALER / (max_values[1]-mid_values[1]);
    else
        ly_temp *= JOYSTICK_SCALER / (mid_values[1]-min_values[1]);
    ly_temp += STICK_CENTER;
    if (ly_temp > 255)
        ly_temp = 255;
    if (ly_temp < 0)
        ly_temp = 0;

    int32_t rx_temp = (int16_t)buffer[4] - mid_values[2];
    if (rx_temp > 0)
        rx_temp *= JOYSTICK_SCALER / (max_values[2]-mid_values[2]);
    else
        rx_temp *= JOYSTICK_SCALER / (mid_values[2]-min_values[2]);
    rx_temp += STICK_CENTER;
    if (rx_temp > 255)
        rx_temp = 255;
    if (rx_temp < 0)
        rx_temp = 0;

    int32_t ry_temp = (int16_t)buffer[5] - mid_values[3];
    if (ry_temp > 0)
        ry_temp *= JOYSTICK_SCALER / (max_values[3]-mid_values[3]);
    else
        ry_temp *= JOYSTICK_SCALER / (mid_values[3]-min_values[3]);
    ry_temp += STICK_CENTER;
    if (ry_temp > 255)
        ry_temp = 255;
    if (ry_temp < 0)
        ry_temp = 0;

    // checks to avoid a data skip (0 values on input, which aren't possible, i think)
    if (buffer[2])
        joysticks[0] = lx_temp;
    if (buffer[3])
        joysticks[1] = ly_temp;
    if (buffer[4])
        joysticks[2] = rx_temp;
    if (buffer[5])
        joysticks[3] = ry_temp;
    if (buffer[6])
        joysticks[4] = buffer[6];
    if (buffer[7])
        joysticks[5] = buffer[7];
}
