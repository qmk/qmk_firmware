

uint8_t mod_state;

/*
 * default HHKB Layout
 */
#include QMK_KEYBOARD_H


//void pointing_device_init_kb(void) {
//    pmw33xx_init(1);         // index 1 is the second device.
//    pmw33xx_set_cpi(0, 800); // applies to first sensor
//    pmw33xx_set_cpi(1, 800); // applies to second sensor
//    pointing_device_init_user();
//}
//
//void keyboard_post_init_user(void) {
////    Customise these values to desired behaviour
//    debug_enable=true;
//    debug_matrix=true;
//    debug_keyboard=true;
//    debug_mouse=true;
//}
//
//bool set_scrolling = false;

//void pointing_device_driver_init(void) {}
//    return mouse_report;
//}
//uint16_t pointing_device_driver_get_cpi(void) { return 0; }
//void pointing_device_driver_set_cpi(uint16_t cpi) {}


//report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
//    if (set_scrolling) {
//        if (has_mouse_report_changed(mouse_report, old_report)) {
//        report_mouse_t currentReport = pointing_device_get_report();
//            currentReport.v = 1;
//            currentReport.h = 1;
//            currentReport.buttons |= MOUSE_BTN1;  // this is defined in report.h
//        pointing_device_set_report(currentReport);
//        pointing_device_send();
//        }
//        report_mouse_t old_report = mouse_report;
//    }
//    return mouse_report;
//}

#include QMK_KEYBOARD_H
#include "keychron_common.h"
#include "custom_codes.c"
#include "french_codes.c"
#include "utf8_codes.c"
#include "layers_order.c"
#include "layers_keymaps.c"
#include "layers_macros.c"
#include "process_record.c"
#include "matrix_scan.c"
//#include "print.h"


