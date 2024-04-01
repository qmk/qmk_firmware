#include <string.h>
#include <stdint.h>

#include "keylogger.h"

void keylogger_initialize(keylogger_t *logger) {
    memset(logger, 0x00, sizeof(keylogger_t));
}

void keylogger_record_keycode(keylogger_t *logger, uint16_t keycode) {
    logger->keycodes[logger->pos] = keycode;
    logger->pos = (logger->pos + 1) % KEY_LOGGER_BUF_SIZE;

    if (logger->written < KEY_LOGGER_BUF_SIZE) {
        logger->written++;
    }
}

uint16_t keylogger_query_keycode(keylogger_t *logger, uint16_t pos) {
    return 0;
}

uint16_t keylogger_cycle_pos(keylogger_t *logger) {
    return (KEY_LOGGER_BUF_SIZE - logger->written + logger->pos) % KEY_LOGGER_BUF_SIZE;
}

// TODO: graceful print logged keycodes