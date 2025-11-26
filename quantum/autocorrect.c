// Copyright 2025 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "autocorrect.h"
#include "process_autocorrect.h"
#include "util.h"

autocorrect_config_t autocorrect_config;

extern const uint8_t number_dicts;
extern uint8_t typo_buffer_size;

void autocorrect_init_dict(void);

/**
 * @brief function for querying the enabled state of autocorrect
 *
 * @return true if enabled
 * @return false if disabled
 */
bool autocorrect_is_enabled(void) {
    return autocorrect_config.enabled;
}

/**
 * @brief Enables autocorrect and saves state to eeprom
 *
 */
void autocorrect_enable(void) {
    autocorrect_config.enabled = true;
    eeconfig_update_autocorrect(&autocorrect_config);
}

/**
 * @brief Disables autocorrect and saves state to eeprom
 *
 */
void autocorrect_disable(void) {
    autocorrect_config.enabled = false;
    typo_buffer_size                      = 0;
    eeconfig_update_autocorrect(&autocorrect_config);
}

/**
 * @brief Toggles autocorrect's status and save state to eeprom
 *
 */
void autocorrect_toggle(void) {
    autocorrect_config.enabled = !autocorrect_config.enabled;
    typo_buffer_size                      = 0;
    eeconfig_update_autocorrect(&autocorrect_config);
}

/**
 * @brief Gets the current dictionary index
 *
 * @return uint8_t current dictionary index
 */
uint8_t autocorrect_get_current_dictionary(void) {
    return autocorrect_config.current_dict;
}

void autocorrect_set_current_dictionary(uint8_t dict_index) {
    if (dict_index < number_dicts) {
        autocorrect_config.current_dict = dict_index;
        eeconfig_update_autocorrect(&autocorrect_config);
        autocorrect_init_dict();
    }
}

/**
 * @brief Gets the number of available dictionaries
 *
 * @return uint8_t number of dictionaries
 */
uint8_t autocorrect_get_number_of_dictionaries(void) {
    return number_dicts;
}

/**
 * @brief Cycles autocorrect's selected dict and save state to eeprom
 *
 */
void autocorrect_dict_cycle(bool forward) {
    if (forward) {
        autocorrect_config.current_dict = (autocorrect_config.current_dict + 1) % number_dicts;
    } else {
        autocorrect_config.current_dict = MIN(autocorrect_config.current_dict - 1, (uint8_t)(number_dicts - 1));
    }
    eeconfig_update_autocorrect(&autocorrect_config);
    autocorrect_init_dict();
}

/**
 * @brief Initializes autocorrect configuration from eeprom
 *
 */
void autocorrect_init(void) {
    eeconfig_read_autocorrect(&autocorrect_config);
    autocorrect_init_dict();
}

/**
 * @brief handling for when autocorrection has been triggered
 *
 * @param backspaces number of characters to remove
 * @param str pointer to PROGMEM string to replace mistyped seletion with
 * @param typo the wrong string that triggered a correction
 * @param correct what it would become after the changes
 * @return true apply correction
 * @return false user handled replacement
 */
__attribute__((weak)) bool apply_autocorrect(uint8_t backspaces, const char *str, char *typo, char *correct) {
    return true;
}
