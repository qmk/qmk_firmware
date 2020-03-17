#include "joystick.h"
#include "math.h"
#include "analog.h"

static inline double dabs (double x) { return x < 0 ? -x : x; }
static inline double dsgn (double x) { return x < 0 ? -1 : 1; }
static inline double signed_pow (double x, double y) { return dsgn(x) * pow(dabs(x), y); }

/* -1.0 ~ +1.0 */
joystick_report_t joystick_get_report (void) {
    int16_t x = analogRead(8) - 512, y = analogRead(9) - 512;

    return (joystick_report_t){
        .x = signed_pow(- x / 512.0, 3),
        .y = signed_pow(y / 512.0, 3)
    };
}
