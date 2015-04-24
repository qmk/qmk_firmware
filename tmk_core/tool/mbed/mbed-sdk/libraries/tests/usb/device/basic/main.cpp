#include <math.h>

#include "mbed.h"
#include "USBMouse.h"

USBMouse mouse(ABS_MOUSE);

int main(void) {
    int x_center = (X_MAX_ABS - X_MIN_ABS)/2;
    int y_center = (Y_MAX_ABS - Y_MIN_ABS)/2;
    int16_t x_screen = 0;
    int16_t y_screen = 0;

    int32_t x_origin = x_center;
    int32_t y_origin = y_center;
    int32_t radius = 5000;
    int32_t angle = 0;

    while (1) {
        x_screen = x_origin + cos((double)angle*3.14/180.0)*radius;
        y_screen = y_origin + sin((double)angle*3.14/180.0)*radius;
        printf("cos: %f, sin: %f\r\n", cos((double)angle*3.14/180.0)*radius, sin((double)angle)*radius);

        mouse.move(x_screen, y_screen);
        angle += 3;
        wait(0.01);
    }
}
