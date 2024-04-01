#ifndef QMK_FIRMWARE_KEYLOGGER_H
#define QMK_FIRMWARE_KEYLOGGER_H

#define KEY_LOGGER_BUF_SIZE 256

typedef struct {
    uint16_t keycodes[KEY_LOGGER_BUF_SIZE];
    uint16_t pos;
    uint16_t written;
} keylogger_t;

void keylogger_initialize(keylogger_t *logger);

void keylogger_record_keycode(keylogger_t *logger, uint16_t keycode);

uint16_t keylogger_query_keycode(keylogger_t *logger, uint16_t pos);

uint16_t keylogger_cycle_pos(keylogger_t *logger);

#endif // QMK_FIRMWARE_KEYLOGGER_H
