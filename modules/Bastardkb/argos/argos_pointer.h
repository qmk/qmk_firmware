#include QMK_KEYBOARD_H

#include <stdint.h>

void build_pointing_device_info_command_data(uint8_t **command_data);
void argos_set_dpi(uint8_t *command_data);
void argos_set_sniping_dpi(uint8_t *command_data);