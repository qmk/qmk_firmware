#include "host_driver.h"
#include "rf_driver.h"
#include "host.h"
#include "user_kb.h"

/* Variable declaration */
extern DEV_INFO_STRUCT dev_info;

/* Host driver */
static uint8_t rf_keyboard_leds(void);
static void    rf_send_keyboard(report_keyboard_t *report);
static void    rf_send_nkro(report_nkro_t *report);
static void    rf_send_mouse(report_mouse_t *report);
static void    rf_send_extra(report_extra_t *report);
host_driver_t  rf_host_driver = {rf_keyboard_leds, rf_send_keyboard, rf_send_nkro, rf_send_mouse, rf_send_extra};

/* defined in rf.c */
extern void uart_send_report_keyboard(report_keyboard_t *report);
extern void uart_send_report_nkro(report_nkro_t *report);
extern void uart_send_mouse_report(report_mouse_t *report);
extern void uart_send_consumer_report(report_extra_t *report);
extern void uart_send_system_report(report_extra_t *report);

static uint8_t rf_keyboard_leds(void) {
    return dev_info.rf_led;
}

static void rf_send_keyboard(report_keyboard_t *report) {
    keyboard_protocol = 1;
    uart_send_report_keyboard(report);
}

static void rf_send_nkro(report_nkro_t *report) {
    keyboard_protocol = 1;
    uart_send_report_nkro(report);
}

static void rf_send_mouse(report_mouse_t *report) {
    uart_send_mouse_report(report);
}

static void rf_send_extra(report_extra_t *report) {
    if (report->report_id == REPORT_ID_CONSUMER) {
        uart_send_consumer_report(report);
    } else if (report->report_id == REPORT_ID_SYSTEM) {
        uart_send_system_report(report);
    }
}
