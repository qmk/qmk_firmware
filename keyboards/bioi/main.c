/* Copyright 2022 Basic I/O Instruments (Scott Wei)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdint.h>
#include <stdbool.h>

#include <avr/interrupt.h>
#include <avr/power.h>
#include <avr/wdt.h>
#include <avr/sleep.h>

#include "suspend.h"
#include "action.h"
#include "timer.h"

#include "report.h"
#include "host.h"
#include "host_driver.h"

#include "quantum.h"
#include "keyboard.h"
#include "matrix.h"
#include "debounce.h"
#include "keymap.h"
#include "magic.h"
#include "led.h"
#include "keycode.h"
#include "timer.h"
#include "sync_timer.h"
#include "print.h"
#include "debug.h"
#include "command.h"
#include "util.h"
#include "sendchar.h"
#include "eeconfig.h"
#include "action_layer.h"

#include "lufa.h"
#include <util/atomic.h>
#include "usb_descriptor.h"
#include "usb_device_state.h"

#ifdef BACKLIGHT_ENABLE
#    include "backlight.h"
#endif
#ifdef MOUSEKEY_ENABLE
#    include "mousekey.h"
#endif
#ifdef PS2_MOUSE_ENABLE
#    include "ps2_mouse.h"
#endif
#ifdef RGBLIGHT_ENABLE
#    include "rgblight.h"
#endif
#ifdef LED_MATRIX_ENABLE
#    include "led_matrix.h"
#endif
#ifdef RGB_MATRIX_ENABLE
#    include "rgb_matrix.h"
#endif
#ifdef ENCODER_ENABLE
#    include "encoder.h"
#endif
#ifdef STENO_ENABLE
#    include "process_steno.h"
#endif
#ifdef POINTING_DEVICE_ENABLE
#    include "pointing_device.h"
#endif
#ifdef MIDI_ENABLE
#    include "qmk_midi.h"
#endif
#ifdef JOYSTICK_ENABLE
#    include "process_joystick.h"
#endif
#ifdef HD44780_ENABLE
#    include "hd44780.h"
#endif
#ifdef OLED_ENABLE
#    include "oled_driver.h"
#endif
#ifdef ST7565_ENABLE
#    include "st7565.h"
#endif
#ifdef VELOCIKEY_ENABLE
#    include "velocikey.h"
#endif
#ifdef VIA_ENABLE
#    include "via.h"
#endif
#ifdef DIP_SWITCH_ENABLE
#    include "dip_switch.h"
#endif
#ifdef EEPROM_DRIVER
#    include "eeprom_driver.h"
#endif
#if defined(CRC_ENABLE)
#    include "crc.h"
#endif
#ifdef VIRTSER_ENABLE
#    include "virtser.h"
#endif
#ifdef SLEEP_LED_ENABLE
#    include "sleep_led.h"
#endif
#ifdef SPLIT_KEYBOARD
#    include "split_util.h"
#endif
#ifdef BLUETOOTH_ENABLE
#    include "bluetooth.h"
#endif
#ifdef CAPS_WORD_ENABLE
#    include "caps_word.h"
#endif
#ifdef LEADER_ENABLE
#    include "leader.h"
#endif
#ifdef RAW_ENABLE
#    include "raw_hid.h"
#endif

#include "ble.h"
#include "usart.h"

#define ROW_SHIFTER ((uint16_t)1)

#define BUFF_SIZE 32

#define DEEP_IDLE_TIME 1000
#define IDLE_TIME 5000

pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

bool force_usb = false;

bool usb_connected = false;
bool ble_enabled   = false;

bool ble_on;

uint32_t kb_idle_timer    = 0;
uint32_t kb_napping_timer = 0;

bool napping  = false;
bool sleeping = false;
bool no_sleep = false;

bool key_pressed = false;

#ifdef BLE_DEBUG
bool usb_state_sent = false;
#endif

matrix_row_t raw_matrix[MATRIX_ROWS];
matrix_row_t matrix[MATRIX_ROWS];
matrix_row_t matrix_debouncing[MATRIX_ROWS];
uint16_t     debouncing_time;
bool         debouncing = false;

uint8_t USB_DeviceLastState = 0;

#ifdef ENCODER_ENABLE

#    ifndef ENCODER_DIRECTION_FLIP
#        define ENCODER_CLOCKWISE true
#        define ENCODER_COUNTER_CLOCKWISE false
#    else
#        define ENCODER_CLOCKWISE false
#        define ENCODER_COUNTER_CLOCKWISE true
#    endif

#    define NUMBER_OF_ENCODERS (sizeof(encoders_pad_a) / sizeof(pin_t))
static pin_t encoders_pad_a[] = ENCODERS_PAD_A;
static pin_t encoders_pad_b[] = ENCODERS_PAD_B;

#    ifdef SPLIT_KEYBOARD
// right half encoders come over as second set of encoders
static uint8_t encoder_value[NUMBER_OF_ENCODERS * 2] = {0};
// row offsets for each hand
static uint8_t thisHand, thatHand;
#    else
static uint8_t encoder_value[NUMBER_OF_ENCODERS] = {0};
#    endif

static int8_t  encoder_LUT[]                      = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};
static uint8_t encoder_state[NUMBER_OF_ENCODERS]  = {0};
static int8_t  encoder_pulses[NUMBER_OF_ENCODERS] = {0};
#endif

#ifdef RAW_ENABLE

/** \brief Raw HID Task
 *
 * FIXME: Needs doc
 */
static void raw_hid_task(void) {
    // Create a temporary buffer to hold the read in data from the host
    uint8_t data[RAW_EPSIZE];
    bool    data_read = false;

    // Device must be connected and configured for the task to run
    if (USB_DeviceState != DEVICE_STATE_Configured) return;

    Endpoint_SelectEndpoint(RAW_OUT_EPNUM);

    // Check to see if a packet has been sent from the host
    if (Endpoint_IsOUTReceived()) {
        // Check to see if the packet contains data
        if (Endpoint_IsReadWriteAllowed()) {
            /* Read data */
            Endpoint_Read_Stream_LE(data, sizeof(data), NULL);
            data_read = true;
        }

        // Finalize the stream transfer to receive the last packet
        Endpoint_ClearOUT();

        if (data_read) {
            raw_hid_receive(data, sizeof(data));
        }
    }
}
#endif

void bootmagic_lite(void) {
    matrix_scan();
#if defined(DEBOUNCE) && DEBOUNCE > 0
    wait_ms(DEBOUNCE * 2);
#else
    wait_ms(2000);
#endif
    matrix_scan();

    if (matrix_get_row(BOOTMAGIC_LITE_ROW) & (1 << BOOTMAGIC_LITE_COLUMN)) {
        // Jump to bootloader.
        clear_keyboard();
        ble_clear_keyboard();
        bootloader_jump();
    }
}

static void setup_mcu(void) {
    /* Disable watchdog if enabled by bootloader/fuses */
    MCUSR &= ~(1 << WDRF);
    wdt_disable();

    /* Disable clock division */
    clock_prescale_set(clock_div_1);

    CLKPR = (1 << CLKPCE);
    CLKPR = (0 << CLKPS3) | (0 << CLKPS2) | (0 << CLKPS1) | (0 << CLKPS0);
}

static void setup_usb(void) {
    // Leonardo needs. Without this USB device is not recognized.
    USB_Disable();

    USB_Init();

    // for Console_Task
    USB_Device_EnableSOFEvents();
    // print_set_sendchar(sendchar);
}

// Shut down unnecessary modules to reduce the power consumption in BLE mode.
void power_saving(void) {
#if defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB1286__)
    power_adc_disable();
    power_spi_disable();

    if (!rgb_matrix_is_enabled() && !rgblight_is_enabled()) {
        power_twi_disable();
    } else {
        power_twi_enable();
    }
#else
    // These modules can be close for ATmega32u4
    power_adc_disable();
    power_twi_disable();
    power_spi_disable();
    power_usart0_disable();
#endif

    // Freeze the USB Clock
    USBCON |= (1 << FRZCLK);
    // Disable the USB Clock (PPL)
    PLLCSR &= ~(1 << PLLE);
    USBCON &= ~(1 << USBE);
}

// Shutdown RGB lighting for further reduce of the power consumption.
void deep_power_saving(void) {
#if (defined(RGB_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLE))
    rgb_power_off();
#endif

#ifdef BACKLIGHT_ENABLE
    backlight_set(0);
#endif

    power_timer1_disable();
    power_timer2_disable();
    power_timer3_disable();

// Turn off the power LED for Command65
#if (defined(BIOI_CMD65))
    writePinHigh(E2);
#endif
}

// Turn modules back on for those shut down in BLE mode.
void power_recover(void) {
    power_timer1_enable();
    power_timer2_enable();
    power_timer3_enable();

    USBCON |= (1 << USBE);
    // Enable the USB Clock (PPL)
    PLLCSR |= (1 << PLLE);
    // Run the USB Clock
    USBCON &= ~(1 << FRZCLK);

#if defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB1286__)
    power_adc_enable();
    power_spi_enable();
    power_twi_enable();
#else
    power_adc_enable();
    power_twi_enable();
    power_spi_enable();
    power_usart0_enable();
#endif

#ifdef BACKLIGHT_ENABLE
    backlight_set(is_backlight_enabled() ? get_backlight_level() : 0);
#endif
}

void mcu_slow_down(void) {
    clock_prescale_set(clock_div_64);
}

void mcu_speed_up(void) {
    clock_prescale_set(clock_div_1);
#ifdef AUDIO_ENABLE
#    if AUDIO_PIN == C4
    power_timer3_enable();
#    elif AUDIO_PIN == C5
    power_timer3_enable();
#    elif AUDIO_PIN == C6
    power_timer3_enable();
#    elif AUDIO_PIN == B5
    power_timer1_enable();
#    elif AUDIO_PIN == B6
    power_timer1_enable();
#    elif AUDIO_PIN == B7
    power_timer1_enable();
#    endif
#endif
// Turn on the power LED for Command65
#if (defined(BIOI_CMD65))
    writePinLow(E2);
#endif
#ifdef BLE_CONTROL_PIN
    setPinOutput(BLE_CONTROL_PIN);
    writePinLow(BLE_CONTROL_PIN);
#endif

#ifdef RGBLIGHT_ENABLE
    rgblight_init();
    rgblight_timer_init();
    rgblight_timer_enable();
    rgblight_reload_from_eeprom();
#endif

#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_reload_from_eeprom();
#endif
}

void ble_task_init(void) {
    // Mark the time once the keyboard is running in BLE mode.
    kb_idle_timer = timer_read32();
}

// Synchronizing the lighting power status to its logical status.
void lighting_sync_task(void) {
#ifdef RGBLIGHT_ENABLE
    if (rgblight_is_enabled()) {
#    ifdef RGB_UG_CONTROL_PIN
        setPinOutput(RGB_UG_CONTROL_PIN);
        writePinLow(RGB_UG_CONTROL_PIN);
#    endif
        rgblight_set();
    } else {
#    ifdef RGB_UG_CONTROL_PIN
        setPinOutput(RGB_UG_CONTROL_PIN);
        writePinHigh(RGB_UG_CONTROL_PIN);
#    endif
    }
#endif

#ifdef RGB_MATRIX_ENABLE
    if (rgb_matrix_is_enabled() == 1) {
        // rgb_matrix_is_enabled() is a unit8_t
#    ifdef RGB_BL_CONTROL_PIN
        writePinHigh(RGB_BL_CONTROL_PIN);
#    endif
#    if defined RGB_UG_CONTROL_PIN && !defined RGBLIGHT_ENABLE
        writePinLow(RGB_UG_CONTROL_PIN);
#    endif
    } else {
#    ifdef RGB_BL_CONTROL_PIN
        writePinLow(RGB_BL_CONTROL_PIN);
#    endif
#    if defined RGB_UG_CONTROL_PIN && !defined RGBLIGHT_ENABLE
        writePinHigh(RGB_UG_CONTROL_PIN);
#    endif
    }
#endif
}

#ifdef ENCODER_ENABLE

static void ble_encoder_update(int8_t index, uint8_t state) {
    uint8_t i = index;
#    ifdef SPLIT_KEYBOARD
    index += thisHand;
#    endif
    encoder_pulses[i] += encoder_LUT[state & 0xF];
    if (encoder_pulses[i] >= ENCODER_RESOLUTION) {
        napping = 0;
        mcu_speed_up();
        encoder_value[index]++;
        encoder_update_kb(index, ENCODER_COUNTER_CLOCKWISE);
        ble_task_init();
    }
    if (encoder_pulses[i] <= -ENCODER_RESOLUTION) {
        // direction is arbitrary here, but this clockwise
        napping = 0;
        mcu_speed_up();
        encoder_value[index]--;
        encoder_update_kb(index, ENCODER_CLOCKWISE);
        ble_task_init();
    }
    encoder_pulses[i] %= ENCODER_RESOLUTION;
}

void ble_encoder_read(void) {
    for (uint8_t i = 0; i < NUMBER_OF_ENCODERS; i++) {
        encoder_state[i] <<= 2;
        encoder_state[i] |= (readPin(encoders_pad_a[i]) << 0) | (readPin(encoders_pad_b[i]) << 1);
        ble_encoder_update(i, encoder_state[i]);
    }
}
#endif

void select_row(uint8_t row) {
    uint8_t pin = row_pins[row];
    _SFR_IO8((pin >> 4) + 1) |= _BV(pin & 0xF);  // OUT
    _SFR_IO8((pin >> 4) + 2) &= ~_BV(pin & 0xF); // LOW
}

void unselect_row(uint8_t row) {
    uint8_t pin = row_pins[row];
    _SFR_IO8((pin >> 4) + 1) &= ~_BV(pin & 0xF); // IN
    _SFR_IO8((pin >> 4) + 2) |= _BV(pin & 0xF);  // HI
}

bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    // Start with a clear matrix row
    matrix_row_t current_row_value = 0;

    // Select row and wait for row selecton to stabilize
    select_row(current_row);
    // matrix_io_delay();
    _delay_us(1);

    // For each col...
    for (uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++) {
        // Select the col pin to read (active low)
        uint8_t pin_state = readPin(col_pins[col_index]);

        // Populate the matrix row with the state of the col pin
        current_row_value |= pin_state ? 0 : (MATRIX_ROW_SHIFTER << col_index);
    }

    // Unselect row
    unselect_row(current_row);

    // If the row has changed, store the row and return the changed flag.
    if (current_matrix[current_row] != current_row_value) {
        current_matrix[current_row] = current_row_value;
        return true;
    }
    return false;
}

// Keep scanning the matrix for any keypress in low power status.
uint8_t low_power_matrix_scan(void) {
    bool matrix_changed = false;

#if defined(DIRECT_PINS) || (DIODE_DIRECTION == COL2ROW)
    // Set row, read cols
    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        matrix_changed |= read_cols_on_row(raw_matrix, current_row);
        if (matrix_changed) {
            // Wake the controller up once the matrix is changed(some key was
            // pressed).
            mcu_speed_up();
            napping = 0;
            ble_task_init();
        }
    }
#elif (DIODE_DIRECTION == ROW2COL)
    // Set col, read rows
    for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
        matrix_changed |= read_rows_on_col(raw_matrix, current_col);
        if (matrix_changed) {
            mcu_speed_up();
            napping = 0;
            ble_task_init();
        }
    }
#endif

    debounce(raw_matrix, matrix, MATRIX_ROWS, matrix_changed);
    return (uint8_t)matrix_changed;
}

// Keyboard loop task while napping.
void low_power_keyboard_task(void) {
    static matrix_row_t matrix_prev[MATRIX_ROWS];
    matrix_row_t        matrix_row    = 0;
    matrix_row_t        matrix_change = 0;

    // Turn into deeper power saving status while napping for enougth time.
    if (timer_elapsed32(kb_napping_timer) > DEEP_IDLE_TIME) {
        deep_power_saving();
    }

#ifdef BLE_CONTROL_PIN
    if (timer_elapsed32(kb_napping_timer) > DEEP_IDLE_TIME * 10) {
        setPinOutput(BLE_CONTROL_PIN);
        writePinHigh(BLE_CONTROL_PIN);
    }
#endif

    low_power_matrix_scan();

#ifdef ENCODER_ENABLE
    ble_encoder_read();
#endif

    for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
        matrix_row    = matrix_get_row(r);
        matrix_change = matrix_row ^ matrix_prev[r];
        if (matrix_change) {
            mcu_speed_up();

            // Send the pressed key immediately when awake from napping.
            for (uint8_t c = 0; c < MATRIX_COLS; c++) {
                if (matrix_change & ((matrix_row_t)1 << c)) {
                    action_exec((keyevent_t){
                        .key = (keypos_t){.row = r, .col = c}, .pressed = (matrix_row & ((matrix_row_t)1 << c)), .time = (timer_read() | 1) /* time should not be 0 */
                    });

                    matrix_prev[r] ^= ((matrix_row_t)1 << c);

                    goto MATRIX_LOOP_END;
                }
            }
        }
    }

    action_exec(TICK_EVENT);
MATRIX_LOOP_END:;
}

void keyboard_pre_task(void) {
#if !defined(NO_USB_STARTUP_CHECK)
    if (USB_DeviceState == DEVICE_STATE_Suspended) {
        print("[s]");
        while (USB_DeviceState == DEVICE_STATE_Suspended) {
            suspend_power_down();
            if (USB_Device_RemoteWakeupEnabled && suspend_wakeup_condition()) {
                USB_Device_SendRemoteWakeup();
                clear_keyboard();

#    if USB_SUSPEND_WAKEUP_DELAY > 0
                // Some hubs, kvm switches, and monitors do
                // weird things, with USB device state bouncing
                // around wildly on wakeup, yielding race
                // conditions that can corrupt the keyboard state.
                //
                // Pause for a while to let things settle...
                wait_ms(USB_SUSPEND_WAKEUP_DELAY);
#    endif
            }
        }
        suspend_wakeup_init();
    }
#endif
}

void keyboard_post_task(void) {
#ifdef MIDI_ENABLE
    MIDI_Device_USBTask(&USB_MIDI_Interface);
#endif

#ifdef VIRTSER_ENABLE
    virtser_task();
    CDC_Device_USBTask(&cdc_device);
#endif

#ifdef RAW_ENABLE
    raw_hid_task();
#endif

#if !defined(INTERRUPT_CONTROL_ENDPOINT)
    USB_USBTask();
#endif
}

/* Keyboard loop task in BLE mode. */

void ble_task(void) {
    // Reset idle timer when any key is pressed.
    matrix_row_t matrix_row = 0;
    for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
        matrix_row  = matrix_get_row(r);
        key_pressed = 0 ^ matrix_row;
        if (key_pressed) {
            ble_task_init();
            break;
        }
    }

    if (USB_DeviceLastState != USB_DeviceState) {
        // Keyboard USB status just changed.

#ifdef BLE_DEBUG
        usb_state_sent = false;

        send_str(PSTR("USB State Changed\r\n"));

        if (USB_DeviceState == DEVICE_STATE_Unattached) {
            send_str(PSTR("USB State Unattached\r\n"));
        }
#endif
        if (USB_DeviceState == DEVICE_STATE_Powered) {
            // Keyboard in USB powered only(power bank connected).
#ifdef BLE_DEBUG
            send_str(PSTR("USB State Powered\r\n"));
#endif
            napping       = 0;
            no_sleep      = 1;
            force_usb     = 0;
            usb_connected = 0;

            power_recover();
            mcu_speed_up();

            USB_Init();
            USB_Detach();
            USB_Attach();

            clear_keyboard();
            host_set_driver(&bluefruit_driver);
            ble_on = true;

            clear_keyboard();
        }
#ifdef BLE_DEBUG
        if ((USB_DeviceState == DEVICE_STATE_Default)) {
            send_str(PSTR("USB State Default\r\n"));
        }
        if ((USB_DeviceState == DEVICE_STATE_Addressed)) {
            send_str(PSTR("USB State Addressed\r\n"));
        }
        if (USB_DeviceState == DEVICE_STATE_Configured) {
            send_str(PSTR("USB State Configured\r\n"));
        }
        if (USB_DeviceState > DEVICE_STATE_Unattached) {
        } else {
            //
        }
#endif

    } else {
        // Keyboard USB status is stable.

#ifdef BLE_DEBUG
        if (!usb_state_sent) {
            if (USB_DeviceState == DEVICE_STATE_Unattached) {
                send_str(PSTR("USB State Stopped at Unattached\r\n"));
            }
            if (USB_DeviceState == DEVICE_STATE_Powered) {
                send_str(PSTR("USB State Stopped at Powered\r\n"));
            }
            if ((USB_DeviceState == DEVICE_STATE_Default)) {
                send_str(PSTR("USB State Stopped at Default\r\n"));
            }
            if ((USB_DeviceState == DEVICE_STATE_Addressed)) {
                send_str(PSTR("USB State Stopped at Addressed\r\n"));
            }
            if (USB_DeviceState == DEVICE_STATE_Configured) {
                send_str(PSTR("USB State Stopped at Configured\r\n"));
            }
        }
#endif
        if (USB_DeviceState == DEVICE_STATE_Powered) {
            //
        }
        if (USB_DeviceState == DEVICE_STATE_Unattached) {
            no_sleep = 0;

            if (host_get_driver() && host_get_driver() != &bluefruit_driver) {
                // Keyboard just changed to BLE mode from USB mode.
#ifdef BLE_DEBUG
                send_str(PSTR("USB State stopped at Unattached\r\n"));
#endif
                ble_task_init();

                no_sleep      = 0;
                force_usb     = 0;
                usb_connected = 0;

                USB_Init();
                USB_Detach();
                USB_Attach();
#ifdef BLE_DEBUG
                send_str(PSTR("Loading &bluefruit_driver\r\n"));
#endif

                clear_keyboard();
                host_set_driver(&bluefruit_driver);
                ble_on = true;
                // We can try update the battery level here, when this function is more accrate.
                // update_ble_batt();
                clear_keyboard();
                power_saving();

            } else {
                // Keyboard keeps running in BLE mode.
                if (!key_pressed && (!no_sleep && (!napping && (timer_elapsed32(kb_idle_timer) > IDLE_TIME)))) {
                    // Keyboard is idle for a time.
                    // Turn keyboard into napping.
                    napping = 1;
                    power_saving();
                    mcu_slow_down();
                    kb_napping_timer = timer_read32();
                }
            }
        }
        if (USB_DeviceState == DEVICE_STATE_Configured) {
            // Keyboard USB is stabled and conected to a USB host.
            if (host_get_driver() && (host_get_driver() != &lufa_driver) && !force_ble) {
                // Keyboard just changed to USB mode from BLE mode.
#ifdef BLE_DEBUG
                send_str(PSTR("USB State stopped at Configured\r\n"));
#endif
                mcu_speed_up();
                power_recover();

                usb_connected = 1;
                no_sleep      = 1;
                ble_enabled   = 0;
#ifdef BLE_DEBUG
                send_str(PSTR("Loading &lufa_driver\r\n"));
#endif
                clear_keyboard();
                host_set_driver(&lufa_driver);
                ble_on = false;
                clear_keyboard();

            } else if (host_get_driver() && (host_get_driver() == &lufa_driver) && force_ble) {
                // Keyboard manually switch to BLE interface.
                clear_keyboard();
                host_set_driver(&bluefruit_driver);
                ble_on = true;
                clear_keyboard();
            } else {
                // Keyboard keeps running in USB mode.
            }
        }
#ifdef BLE_DEBUG
        usb_state_sent = true;
#endif
    }

    USB_DeviceLastState = USB_DeviceState;
}

// Main function overriding the one in LUFA.
int main(void) {
#ifdef MIDI_ENABLE
    setup_midi();
#endif

    setup_mcu();

    keyboard_setup();

    setup_usb();
    sei();

#ifdef WAIT_FOR_USB
    while (USB_DeviceState != DEVICE_STATE_Configured) {
#    if defined(INTERRUPT_CONTROL_ENDPOINT)
        ;
#    else
        USB_USBTask();
#    endif
    }
    print("USB configured.\n");
#else
    USB_USBTask();
#endif

    print("\nUSB init\n");

    keyboard_init();
    ble_task_init();

    host_set_driver(&lufa_driver);

    lighting_sync_task();

#ifdef BACKLIGHT_ENABLE
    backlight_disable();
#endif

    print("Keyboard initialized.\n");

    usart_init();

#ifdef BLE_DEBUG
    send_str(PSTR("Keyboard has been setup up\r\n"));

    if (usb_connected) {
        send_str(PSTR("usb_connected=1\r\n"));
    } else {
        send_str(PSTR("usb_connected=0\r\n"));
    }
#endif

    while (1) {
        ble_task();
        if (napping) {
            low_power_keyboard_task();
        }
        if (!napping) {
            keyboard_pre_task();
            lighting_sync_task();
            keyboard_task();
            keyboard_post_task();
            housekeeping_task();
        }
    }
}