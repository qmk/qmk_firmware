typedef struct { double x, y; } joystick_report_t;
void joystick_initialize (void);
joystick_report_t joystick_get_report (void);
