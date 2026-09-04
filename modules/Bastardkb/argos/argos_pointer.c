#include QMK_KEYBOARD_H

#include "argos_pointer.h"
#include "argos.h"
#include <stdint.h>

// TODO dilemma v2 / cirque
#ifdef BK_HAS_POINTING_DEVICE
#include "bk_pointing_device.h"
#endif

void build_pointing_device_info_command_data(uint8_t **command_data) {
    (*command_data)[0] = pointing_device_type_unknown;
#ifdef BK_HAS_POINTING_DEVICE
#if defined(POINTING_DEVICE_DRIVER_pmw3360) // Charybdis / Dilemma trackball
    (*command_data)[0] = pointing_device_type_trackball;
#elif defined(POINTING_DEVICE_DRIVER_digitizer) // Dilemma v3 / procyon
    (*command_data)[0] = pointing_device_type_trackpad_procyon;
#elif defined(POINTING_DEVICE_DRIVER_cirque_pinnacle_spi) // Dilemma v2 / cirque
    (*command_data)[0] = pointing_device_type_trackpad_cirque;
#endif
    if((*command_data)[0] != pointing_device_type_unknown) {
        // pointing dpi is up to 400+16*200 = 3600, 2 bytes
        (*command_data)[1] = bkpd_get_pointer_default_dpi() & 0xFF;
        (*command_data)[2] = (bkpd_get_pointer_default_dpi() >> 8) & 0xFF;
        // minimum default DPI is 400, 2 bytes
        uint16_t minimum_default_dpi = bkpd_get_minimum_default_dpi();
        (*command_data)[3] = minimum_default_dpi & 0xFF;
        (*command_data)[4] = (minimum_default_dpi >> 8) & 0xFF;
        // default DPI config step is 200, so one byte, but we use 2 just in
        // case
        uint16_t default_dpi_config_step = bkpd_get_default_dpi_config_step();
        (*command_data)[5] = default_dpi_config_step & 0xFF;
        (*command_data)[6] = (default_dpi_config_step >> 8) & 0xFF;
        // sniping DPI is up to 200+4*100 = 600, 2 bytes
        (*command_data)[7] = bkpd_get_pointer_sniping_dpi() & 0xFF;
        (*command_data)[8] = (bkpd_get_pointer_sniping_dpi() >> 8) & 0xFF;
        // mininmum sniping dpi is 200, but ue use 2 bytes ju) in case
        uint16_t minimum_sniping_dpi = bkpd_get_minimum_sniping_dpi();
        (*command_data)[9] = minimum_sniping_dpi & 0xFF;
        (*command_data)[10] = (minimum_sniping_dpi >> 8) & 0xFF;
        // sniping DPI config step is 100, so one byte, but we use 2 just in
        // case
        uint16_t sniping_dpi_config_step = bkpd_get_sniping_dpi_config_step();
        (*command_data)[11] = sniping_dpi_config_step & 0xFF;
        (*command_data)[12] = (sniping_dpi_config_step >> 8) & 0xFF;
        // pointing DPI max steps is 16, so one byte is plenty
        // this is hardcoded here as we can't read it from dilemma.c (private
        // config structure dilemma_config_t)
        (*command_data)[13] = 16;
        // sniping DPI max steps is 4, so one byte is plenty
        // this is hardcoded here as we can't read it from dilemma.c (private
        // config structure dilemma_config_t)
        (*command_data)[14] = 4;
        (*command_data)[15] = bkpd_get_auto_mouse_layer_enabled();
        (*command_data)[16] = bkpd_get_auto_precision_on_mouse_layer_enabled();
        (*command_data)[17] = bkpd_get_dragscroll_axis_invert_x();
        (*command_data)[18] = bkpd_get_dragscroll_axis_invert_y();
        // TODO dragscroll DPI
    }
#endif
}

void argos_set_dpi(uint8_t *command_data) {
#ifdef BK_HAS_POINTING_DEVICE
        // new dpi is on 2 bytes:
        uint16_t new_dpi = command_data[0] | (command_data[1] << 8);
        // get the old DPI:
        uint16_t old_dpi = bkpd_get_pointer_default_dpi();
        // calculate the difference:
        int16_t difference = new_dpi - old_dpi;
        // calculate how many steps we need, it could be negative
        uint16_t default_dpi_config_step = bkpd_get_default_dpi_config_step();
        int8_t new_steps = difference / default_dpi_config_step;
        // apply the steps one by one
        bool forward = new_steps > 0;
        for (int i = 0; i < abs(new_steps); i++) {
            bkpd_cycle_pointer_default_dpi(forward);
        }
#endif
}

void argos_set_sniping_dpi(uint8_t *command_data) {
#ifdef BK_HAS_POINTING_DEVICE
        // new dpi is on 2 bytes:
        uint16_t new_dpi = command_data[0] | (command_data[1] << 8);
        // get the old DPI:
        uint16_t old_dpi = bkpd_get_pointer_sniping_dpi();
        // calculate the difference:
        int16_t difference = new_dpi - old_dpi;
        // calculate how many steps we need, it could be negative
        uint16_t sniping_dpi_config_step = bkpd_get_sniping_dpi_config_step();
        int8_t new_steps = difference / sniping_dpi_config_step;
        // apply the steps one by one
        bool forward = new_steps > 0;
        for (int i = 0; i < abs(new_steps); i++) {
            bkpd_cycle_pointer_sniping_dpi(forward);
        }
#endif
}