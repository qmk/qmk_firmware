#pragma once

#ifdef POINTING_DEVICE_DRIVER_digitizer
#include "digitizer.h"
#endif


bool bkpd_dispatch_command(const uint8_t command_id, uint8_t **command_data);
void bkpd_build_pointing_device_info_command_data(uint8_t **command_data);
uint16_t bkpd_get_pointer_default_dpi(void);
void bkpd_set_pointer_default_dpi(uint16_t new_dpi);
void bkpd_cycle_pointer_default_dpi(bool forward);
void bkpd_cycle_pointer_default_dpi_noeeprom(bool forward);
void bkpd_cycle_pointer_sniping_dpi(bool forward);
void bkpd_cycle_pointer_sniping_dpi_noeeprom(bool forward);
bool bkpd_get_pointer_sniping_enabled(void);
void bkpd_set_pointer_sniping_enabled(bool enable);
bool bkpd_get_pointer_dragscroll_enabled(void);
void bkpd_set_pointer_dragscroll_enabled(bool enable);
uint16_t bkpd_get_pointer_sniping_dpi(void);
void bkpd_set_pointer_sniping_dpi(uint16_t new_dpi);
void keyboard_post_init_bk_pointing_device(void);
void bkpd_set_auto_mouse_layer_enabled(bool enabled);
void bkpd_set_auto_precision_on_mouse_layer_enabled(bool enabled);
bool bkpd_get_auto_mouse_layer_enabled(void);
bool bkpd_get_auto_precision_on_mouse_layer_enabled(void);
void bkpd_set_dragscroll_axis_invert_x(bool invert);
void bkpd_set_dragscroll_axis_invert_y(bool invert);
void bkpd_set_dragscroll_dpi(uint16_t dpi);
bool bkpd_get_dragscroll_axis_invert_x(void);
bool bkpd_get_dragscroll_axis_invert_y(void);
uint16_t bkpd_get_dragscroll_dpi(void);
uint16_t bkpd_get_minimum_default_dpi(void);
uint16_t bkpd_get_default_dpi_config_step(void);
uint16_t bkpd_get_minimum_sniping_dpi(void);
uint16_t bkpd_get_sniping_dpi_config_step(void);
bool bkpd_is_changing_dpi_settings(void);

#ifdef POINTING_DEVICE_DRIVER_digitizer
bool digitizer_task_kb(digitizer_t *const digitizer_state);
#endif

// NOTE: made to work on branch bkb-pointing-device
