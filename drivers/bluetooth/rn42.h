#include "report.h"

void rn42_init(void);

void rn42_send_keyboard(report_keyboard_t *report);

void rn42_send_mouse(report_mouse_t *report);

void rn42_send_consumer(uint16_t data);
