// Copyright 2026 Mauro DiBenedetto
// Copyright 2026 Antonio SJ Musumeci (@trapexit)
// SPDX-License-Identifier: GPL-2.0-or-later
//
// Bluetooth through TEX's BLE5 add-on board, an nRF52810 on USART0. Frames are a
// CRC-16/CCITT-checked header plus a 0x7C-marked body. The module polls with status
// frames and acknowledges each sent frame by sequence number; key events go out as
// press/release codes and the module builds the HID reports.

#include QMK_KEYBOARD_H

#include "bluetooth.h"
#include "connection.h"

#include <string.h>

#define BLE_SD SD0
#define BLE_RETRANSMIT_MS 128
#define BLE_PAIR_HOLD_MS 3000
#define BLE_POLL_MS 250
#define BLE_HOLD_MS 5000
#define BLE_KEY_GAP_MS 20
#define BLE_FLUSH_MS 250
#define BLE_PAIR_BLINK_MS 100
#define BLE_CONTROL_LOW_US 10
#define BLE_CONTROL_HIGH_US 20
#define FRAME_MARK 0x7C
#define TYPE_CONFIG '1'
#define TYPE_STATUS '4'
#define TYPE_KEYS '5'
#define TYPE_MOUSE '6'
#define CMD_WAKE 0x40
#define CMD_SLOT 0xC0
#define CMD_PAIR 0xE0
#define LINK_PAIRING 3
#define LINK_CONNECTED 4
#define FLAG_MOUSE 0x80
#define FLAG_BATTERY 0x40
#define FLAG_REPLY 0x20
#define FLAG_STATUS 0x02
#define FLAG_LEDS 0x01
#define KEY_PRESSED 0x8000
#define KEYS_PER_FRAME 30
#define KEY_RING_SIZE 32
#define CODE_SYSTEM_FIRST 0xE9
#define CODE_CONSUMER_FIRST 0xEC
#define CODE_MOUSE_BUTTON1 0x1F0
#define FRAME_HEADER_BYTES 6
#define INNER_HEADER_BYTES 4
#define INNER_MAX_BYTES 64
#define STATUS_BYTES 14
#define CRC_POLYNOMIAL 0x1021
#define CRC_HIGH_BIT 0x8000
#define LENGTH_MARK 0xA800
#define LENGTH_MASK 0x07FF
#define BYTE_BITS 8
#define BYTE_MASK 0xFF
#define MODIFIER_COUNT 8
#define MOUSE_AXES 4

// The configuration frame body, as sent by the stock firmware.
static const uint8_t      g_CONFIG_BLOCK[32]  = SHURA_BLE_CONFIG_BLOCK;
static const uint16_t     g_CONSUMER_USAGES[] = {AL_CC_CONFIG, AL_EMAIL, AL_CALCULATOR, AL_LOCAL_BROWSER, TRANSPORT_PLAY_PAUSE, TRANSPORT_STOP, TRANSPORT_PREV_TRACK, TRANSPORT_NEXT_TRACK, AUDIO_MUTE, AUDIO_VOL_DOWN, AUDIO_VOL_UP, AC_SEARCH, AC_HOME, AC_BACK, AC_FORWARD, AC_STOP, AC_REFRESH, AC_BOOKMARKS};
static const SerialConfig g_SERIAL_CONFIG     = {.speed = SHURA_BLE_BAUD};

static uint8_t  g_SEQ;
static uint8_t  g_INFLIGHT;
static uint8_t  g_INFLIGHT_KEYS;
static int16_t  g_INFLIGHT_MOUSE[MOUSE_AXES];
static uint16_t g_SENT_AT;
static uint8_t  g_COMMANDS[8];
static uint8_t  g_COMMAND_HEAD;
static uint8_t  g_COMMAND_COUNT;
static uint16_t g_KEYS[KEY_RING_SIZE];
static uint8_t  g_KEY_TAIL;
static uint8_t  g_KEY_COUNT;
static int16_t  g_MOUSE[MOUSE_AXES];
static uint8_t  g_FLAGS;
static uint8_t  g_BATTERY = 100;
static uint8_t  g_HOST_LEDS;
static uint8_t  g_STATUS_SPARE[2];
// Link state, as reported by the module: [0] is LINK_PAIRING or LINK_CONNECTED.
static uint8_t           g_STATUS[6];
static bool              g_STATUS_SEEN;
static uint16_t          g_LINK_DOWN_AT;
static uint32_t          g_KEYS_ACKED_AT;
static report_keyboard_t g_LAST_KEYBOARD;
static report_nkro_t     g_LAST_NKRO;
static uint8_t           g_LAST_BUTTONS;
static uint8_t           g_LAST_CONSUMER;
static uint8_t           g_LAST_SYSTEM;
static uint16_t          g_SLOT_KEY;
static uint16_t          g_SLOT_SINCE;
static bool              g_SLOT_PAIRED;
static bool              g_BLINKING;
static uint16_t          g_BLINK_AT;
static uint8_t           g_RX[FRAME_HEADER_BYTES + INNER_MAX_BYTES];
static uint8_t           g_RX_COUNT;

static uint16_t _crc16(const uint8_t *data_, uint8_t length_, uint16_t crc_) {
    for (uint8_t n = 0; n < length_; n++) {
        crc_ ^= ((uint16_t)data_[n] << BYTE_BITS);
        for (uint8_t bit = 0; bit < BYTE_BITS; bit++) {
            crc_ = (crc_ & CRC_HIGH_BIT) ? ((crc_ << 1) ^ CRC_POLYNOMIAL) : (crc_ << 1);
        }
    }

    return crc_;
}

static void _send_frame(const uint8_t *inner_, uint8_t length_) {
    uint8_t  header[FRAME_HEADER_BYTES];
    uint16_t length = (LENGTH_MARK | length_);
    uint16_t crc;

    header[4] = (length & BYTE_MASK);
    header[5] = (length >> BYTE_BITS);
    crc       = _crc16(inner_, length_, _crc16((header + 4), 2, 0));
    header[0] = (crc & BYTE_MASK);
    header[1] = (crc >> BYTE_BITS);
    header[2] = ((~crc) & BYTE_MASK);
    header[3] = (((uint16_t)(~crc)) >> BYTE_BITS);
    sdWrite(&BLE_SD, header, sizeof(header));
    sdWrite(&BLE_SD, inner_, length_);
}

static void _queue_command(uint8_t command_) {
    if (g_COMMAND_COUNT >= sizeof(g_COMMANDS)) {
        return;
    }
    g_COMMANDS[((g_COMMAND_HEAD + g_COMMAND_COUNT) % sizeof(g_COMMANDS))] = command_;
    g_COMMAND_COUNT++;
}

static void _queue_key(uint16_t code_, bool pressed_) {
    // Preserve stock's bounded event ring and drop-on-full policy.
    if ((code_ == 0) || (g_KEY_COUNT >= KEY_RING_SIZE)) {
        return;
    }
    g_KEYS[((g_KEY_TAIL + g_KEY_COUNT) % KEY_RING_SIZE)] = (code_ | (pressed_ ? KEY_PRESSED : 0));
    g_KEY_COUNT++;
}

static bool _is_link_up(void) {
    return (g_STATUS_SEEN && (g_STATUS[0] == LINK_CONNECTED));
}

static uint8_t _build_keys(uint8_t *frame_) {
    uint8_t length = INNER_HEADER_BYTES;

    g_INFLIGHT_KEYS = 0;
    while ((g_INFLIGHT_KEYS < g_KEY_COUNT) && (g_INFLIGHT_KEYS < KEYS_PER_FRAME)) {
        uint16_t entry    = g_KEYS[((g_KEY_TAIL + g_INFLIGHT_KEYS) % KEY_RING_SIZE)];
        bool     repeated = false;

        // A press and release in one frame cancel at the BLE HID builder.
        for (uint8_t i = INNER_HEADER_BYTES; i < length; i += 2) {
            uint16_t previous = (frame_[i] | (frame_[(i + 1)] << BYTE_BITS));
            if (((previous ^ entry) & (~KEY_PRESSED)) == 0) {
                repeated = true;
            }
        }

        if (repeated) {
            break;
        }
        frame_[length++] = (entry & BYTE_MASK);
        frame_[length++] = (entry >> BYTE_BITS);
        g_INFLIGHT_KEYS++;
    }

    frame_[3] = g_INFLIGHT_KEYS;
    return length;
}

static void _build(uint8_t type_) {
    uint8_t frame[INNER_MAX_BYTES] = {FRAME_MARK, type_, g_SEQ, 0};
    uint8_t length                 = INNER_HEADER_BYTES;

    switch (type_) {
        case TYPE_CONFIG:
            memcpy((frame + INNER_HEADER_BYTES), g_CONFIG_BLOCK, sizeof(g_CONFIG_BLOCK));
            length += sizeof(g_CONFIG_BLOCK);
            break;
        case TYPE_STATUS:
            frame[4] = g_BATTERY;
            frame[5] = g_HOST_LEDS;
            memcpy((frame + 6), g_STATUS_SPARE, sizeof(g_STATUS_SPARE));
            memcpy((frame + 8), g_STATUS, sizeof(g_STATUS));
            length = STATUS_BYTES;
            break;
        case TYPE_KEYS:
            length = _build_keys(frame);
            break;
        case TYPE_MOUSE:
            memcpy(g_INFLIGHT_MOUSE, g_MOUSE, sizeof(g_INFLIGHT_MOUSE));
            frame[4] = (g_INFLIGHT_MOUSE[0] & BYTE_MASK);
            frame[5] = (g_INFLIGHT_MOUSE[0] >> BYTE_BITS);
            frame[6] = (g_INFLIGHT_MOUSE[1] & BYTE_MASK);
            frame[7] = (g_INFLIGHT_MOUSE[1] >> BYTE_BITS);
            frame[8] = (int8_t)g_INFLIGHT_MOUSE[2];
            frame[9] = (int8_t)g_INFLIGHT_MOUSE[3];
            length   = 10;
            break;
        default:
            break;
    }

    _send_frame(frame, length);
    g_SENT_AT = timer_read();
}

static void _send_next(void) {
    bool    link_up;
    uint8_t type;

    if (g_INFLIGHT != 0) {
        _build(g_INFLIGHT);
        return;
    }

    link_up = _is_link_up();
    if (link_up || (g_KEY_COUNT == 0)) {
        g_LINK_DOWN_AT = timer_read();
    }
    if (!link_up) {
        memset(g_MOUSE, 0, sizeof(g_MOUSE));
        g_FLAGS &= (~FLAG_MOUSE);
        if (timer_elapsed(g_LINK_DOWN_AT) >= BLE_HOLD_MS) {
            g_KEY_TAIL = g_KEY_COUNT = 0;
        }
    }

    if (g_COMMAND_COUNT != 0) {
        type = g_COMMANDS[g_COMMAND_HEAD];
    } else if ((g_FLAGS & FLAG_MOUSE) != 0) {
        type = TYPE_MOUSE;
    } else if (g_FLAGS != 0) {
        g_FLAGS = 0;
        _build(TYPE_STATUS);
        return;
    } else if ((g_KEY_COUNT != 0) && link_up && (timer_elapsed32(g_KEYS_ACKED_AT) >= BLE_KEY_GAP_MS)) {
        type = TYPE_KEYS;
    } else {
        if (timer_elapsed(g_SENT_AT) >= BLE_POLL_MS) {
            _build(TYPE_STATUS);
        }
        return;
    }

    g_SEQ++;
    g_INFLIGHT = type;
    _build(type);
}

static void _acknowledge(void) {
    switch (g_INFLIGHT) {
        case TYPE_KEYS:
            g_KEY_TAIL = ((g_KEY_TAIL + g_INFLIGHT_KEYS) % KEY_RING_SIZE);
            g_KEY_COUNT -= g_INFLIGHT_KEYS;
            g_KEYS_ACKED_AT = timer_read32();
            break;
        case TYPE_MOUSE:
            for (uint8_t i = 0; i < MOUSE_AXES; i++) {
                g_MOUSE[i] -= g_INFLIGHT_MOUSE[i];
            }
            if ((g_MOUSE[0] == 0) && (g_MOUSE[1] == 0) && (g_MOUSE[2] == 0) && (g_MOUSE[3] == 0)) {
                g_FLAGS &= (~FLAG_MOUSE);
            }
            break;
        default:
            if ((g_COMMAND_COUNT != 0) && (g_COMMANDS[g_COMMAND_HEAD] == g_INFLIGHT)) {
                g_COMMAND_HEAD = ((g_COMMAND_HEAD + 1) % sizeof(g_COMMANDS));
                g_COMMAND_COUNT--;
            }
            break;
    }

    g_INFLIGHT = 0;
}

static void _handle_status(const uint8_t *frame_, uint8_t length_) {
    if (length_ < STATUS_BYTES) {
        return;
    }
    if ((g_INFLIGHT == 0) && (g_FLAGS == 0)) {
        g_FLAGS = FLAG_REPLY;
    } else {
        g_FLAGS &= FLAG_MOUSE;
    }
    if (frame_[4] != g_BATTERY) {
        g_FLAGS |= FLAG_BATTERY;
    }
    if (frame_[5] != g_HOST_LEDS) {
        g_HOST_LEDS = frame_[5];
        g_FLAGS |= FLAG_LEDS;
    }

    memcpy(g_STATUS_SPARE, (frame_ + 6), sizeof(g_STATUS_SPARE));
    if (!g_STATUS_SEEN || (memcmp(g_STATUS, (frame_ + 8), sizeof(g_STATUS)) != 0)) {
        memcpy(g_STATUS, (frame_ + 8), sizeof(g_STATUS));
        g_STATUS_SEEN = true;
        g_FLAGS |= FLAG_STATUS;
    }

    if ((g_INFLIGHT != 0) && (frame_[2] == g_SEQ)) {
        _acknowledge();
    }
    _send_next();
}

static void _receive_byte(uint8_t byte_) {
    g_RX[g_RX_COUNT++] = byte_;
    while (g_RX_COUNT >= FRAME_HEADER_BYTES) {
        uint16_t crc     = (g_RX[0] | (g_RX[1] << BYTE_BITS));
        uint16_t inverse = (g_RX[2] | (g_RX[3] << BYTE_BITS));
        uint16_t word    = (g_RX[4] | (g_RX[5] << BYTE_BITS));
        uint16_t length  = (word & LENGTH_MASK);

        if (((uint16_t)(crc + inverse) == UINT16_MAX) && ((word & (~LENGTH_MASK)) == LENGTH_MARK) && (length <= INNER_MAX_BYTES)) {
            if (g_RX_COUNT < (FRAME_HEADER_BYTES + length)) {
                return;
            }
            if (_crc16((g_RX + FRAME_HEADER_BYTES), length, _crc16((g_RX + 4), 2, 0)) == crc) {
                if ((length >= 2) && (g_RX[6] == FRAME_MARK) && (g_RX[7] == TYPE_STATUS)) {
                    _handle_status((g_RX + FRAME_HEADER_BYTES), length);
                }
                g_RX_COUNT = 0;
                return;
            }
        }

        g_RX_COUNT--;
        memmove(g_RX, (g_RX + 1), g_RX_COUNT);
    }
}

void bluetooth_init(void) {
    // Pulse the module's control line before talking to it, as the stock firmware does.
    palSetLineMode(SHURA_BLE_RESET_PIN, (PAL_HT32_MODE_AF(AFIO_GPIO) | PAL_MODE_OUTPUT_PUSHPULL));
    gpio_write_pin_low(SHURA_BLE_RESET_PIN);
    wait_us(BLE_CONTROL_LOW_US);
    gpio_write_pin_high(SHURA_BLE_RESET_PIN);
    wait_us(BLE_CONTROL_HIGH_US);
    // Route the pins to the USART and explicitly enable the HT32 RX input buffer.
    palSetLineMode(SHURA_BLE_TX_PIN, PAL_MODE_HT32_AF(SHURA_BLE_AF));
    palSetLineMode(SHURA_BLE_RX_PIN, (PAL_MODE_HT32_AF(SHURA_BLE_AF) | PAL_HT32_MODE_INE));
    sdStart(&BLE_SD, &g_SERIAL_CONFIG);
    _queue_command(TYPE_CONFIG);
    _queue_command(CMD_WAKE);
    _queue_command(CMD_WAKE);
    _queue_command(CMD_WAKE);
}

void bluetooth_task(void) {
    msg_t byte;

    // Bound a pass even if the radio continuously fills the UART queue.
    for (uint8_t i = 0; i < sizeof(g_RX); i++) {
        byte = sdGetTimeout(&BLE_SD, TIME_IMMEDIATE);
        if (byte < 0) {
            break;
        }
        _receive_byte(byte);
    }

    if ((g_INFLIGHT == 0) || (timer_elapsed(g_SENT_AT) >= BLE_RETRANSMIT_MS)) {
        _send_next();
    }
}

void ble_flush_keys(uint8_t settle_ms_) {
    uint16_t start = timer_read();

    while (((g_KEY_COUNT != 0) || (g_INFLIGHT != 0)) && (timer_elapsed(start) < BLE_FLUSH_MS)) {
        bluetooth_task();
    }
    start = timer_read();
    while (timer_elapsed(start) < settle_ms_) {
        bluetooth_task();
    }
}

bool ble_pairing(void) {
    return (g_STATUS_SEEN && (g_STATUS[0] == LINK_PAIRING));
}

void ble_set_battery(uint8_t percent_) {
    if (percent_ == g_BATTERY) {
        return;
    }
    g_BATTERY = percent_;
    g_FLAGS |= FLAG_BATTERY;
}

void ble_sleep(void) {
    sdStop(&BLE_SD);
    palSetLineMode(SHURA_BLE_TX_PIN, (PAL_HT32_MODE_AF(AFIO_GPIO) | PAL_MODE_OUTPUT_PUSHPULL));
    gpio_write_pin_high(SHURA_BLE_TX_PIN);
}

void ble_wake(void) {
    palSetLineMode(SHURA_BLE_TX_PIN, PAL_MODE_HT32_AF(SHURA_BLE_AF));
    sdStart(&BLE_SD, &g_SERIAL_CONFIG);
    _queue_command(CMD_WAKE);
    g_STATUS_SEEN = false;
}

bool bluetooth_is_connected(void) {
    // QMK AUTO prefers USB. Keep BLE selected while it wakes without USB.
    return !ble_pairing();
}

uint8_t bluetooth_keyboard_leds(void) {
    return g_HOST_LEDS;
}

static bool _has_key(const report_keyboard_t *report_, uint8_t code_) {
    for (uint8_t i = 0; i < KEYBOARD_REPORT_KEYS; i++) {
        if (report_->keys[i] == code_) {
            return true;
        }
    }

    return false;
}

static void _queue_modifiers(uint8_t current_, uint8_t previous_) {
    uint8_t changed = (current_ ^ previous_);

    for (uint8_t i = 0; i < MODIFIER_COUNT; i++) {
        if (((changed >> i) & 1) != 0) {
            _queue_key((KC_LEFT_CTRL + i), ((current_ >> i) & 1));
        }
    }
}

void bluetooth_send_keyboard(report_keyboard_t *report_) {
    _queue_modifiers(report_->mods, g_LAST_KEYBOARD.mods);
    for (uint8_t i = 0; i < KEYBOARD_REPORT_KEYS; i++) {
        if ((g_LAST_KEYBOARD.keys[i] != 0) && !_has_key(report_, g_LAST_KEYBOARD.keys[i])) {
            _queue_key(g_LAST_KEYBOARD.keys[i], false);
        }
    }

    for (uint8_t i = 0; i < KEYBOARD_REPORT_KEYS; i++) {
        if ((report_->keys[i] != 0) && !_has_key(&g_LAST_KEYBOARD, report_->keys[i])) {
            _queue_key(report_->keys[i], true);
        }
    }

    g_LAST_KEYBOARD = *report_;
}

bool bluetooth_can_send_nkro(void) {
    return true;
}

void bluetooth_send_nkro(report_nkro_t *report_) {
    _queue_modifiers(report_->mods, g_LAST_NKRO.mods);
    for (uint8_t i = 0; i < NKRO_REPORT_BITS; i++) {
        uint8_t changed = (report_->bits[i] ^ g_LAST_NKRO.bits[i]);
        for (uint8_t bit = 0; bit < BYTE_BITS; bit++) {
            if (((changed >> bit) & 1) != 0) {
                _queue_key(((i * BYTE_BITS) + bit), ((report_->bits[i] >> bit) & 1));
            }
        }
    }

    g_LAST_NKRO = *report_;
}

void bluetooth_send_mouse(report_mouse_t *report_) {
    uint8_t       changed           = (report_->buttons ^ g_LAST_BUTTONS);
    const int16_t delta[MOUSE_AXES] = {report_->x, report_->y, report_->v, report_->h};

    for (uint8_t i = 0; i < BYTE_BITS; i++) {
        if (((changed >> i) & 1) != 0) {
            _queue_key((CODE_MOUSE_BUTTON1 + i), ((report_->buttons >> i) & 1));
        }
    }

    g_LAST_BUTTONS = report_->buttons;
    for (uint8_t i = 0; i < MOUSE_AXES; i++) {
        g_MOUSE[i] += delta[i];
        if (delta[i] != 0) {
            g_FLAGS |= FLAG_MOUSE;
        }
    }
}

void bluetooth_send_consumer(uint16_t usage_) {
    uint8_t code = 0;

    for (uint8_t i = 0; i < ARRAY_SIZE(g_CONSUMER_USAGES); i++) {
        if (g_CONSUMER_USAGES[i] == usage_) {
            code = (CODE_CONSUMER_FIRST + i);
        }
    }

    if (code == g_LAST_CONSUMER) {
        return;
    }
    _queue_key(g_LAST_CONSUMER, false);
    _queue_key(code, true);
    g_LAST_CONSUMER = code;
}

void bluetooth_send_system(uint16_t usage_) {
    uint8_t code = 0;

    if ((usage_ >= SYSTEM_POWER_DOWN) && (usage_ <= SYSTEM_WAKE_UP)) {
        code = (CODE_SYSTEM_FIRST + (usage_ - SYSTEM_POWER_DOWN));
    }
    if (code == g_LAST_SYSTEM) {
        return;
    }
    _queue_key(g_LAST_SYSTEM, false);
    _queue_key(code, true);
    g_LAST_SYSTEM = code;
}

bool ble_process_record(uint16_t keycode_, keyrecord_t *record_) {
    if (keycode_ == BLE_USB) {
        if (record_->event.pressed) {
            connection_set_host_noeeprom(CONNECTION_HOST_AUTO);
        }
        return false;
    }

    if ((keycode_ < BLE_SLOT1) || (keycode_ > BLE_PAIR)) {
        return true;
    }
    if (record_->event.pressed) {
        if (g_SLOT_KEY != 0) {
            return false;
        }
        g_SLOT_KEY    = keycode_;
        g_SLOT_SINCE  = timer_read();
        g_SLOT_PAIRED = false;
    } else if (g_SLOT_KEY == keycode_) {
        if (!g_SLOT_PAIRED && (keycode_ != BLE_PAIR)) {
            _queue_command((CMD_SLOT + (keycode_ - BLE_SLOT1)));
            connection_set_host_noeeprom(CONNECTION_HOST_BLUETOOTH);
        }

        g_SLOT_KEY = 0;
    }

    return false;
}

void ble_housekeeping(void) {
    bool pairing = ble_pairing();

    if ((g_SLOT_KEY != 0) && !g_SLOT_PAIRED && (timer_elapsed(g_SLOT_SINCE) >= BLE_PAIR_HOLD_MS)) {
        uint8_t slot  = (g_SLOT_KEY == BLE_PAIR) ? 0 : (g_SLOT_KEY - BLE_SLOT1);
        g_SLOT_PAIRED = true;
        _queue_command((CMD_PAIR + slot));
        connection_set_host_noeeprom(CONNECTION_HOST_BLUETOOTH);
    }

    if (pairing && (timer_elapsed(g_BLINK_AT) >= BLE_PAIR_BLINK_MS)) {
        g_BLINK_AT = timer_read();
        gpio_toggle_pin(SHURA_CAPS_LED_PIN);
    } else if (!pairing && g_BLINKING) {
        led_update_ports(host_keyboard_led_state());
    }
    g_BLINKING = pairing;
}
