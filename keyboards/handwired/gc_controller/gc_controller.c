#include "gc_controller.h"
#include "gc_read.h"
#include "gamepad.h"
#include <string.h>

uint16_t gamecube_buttons = 0;
uint8_t gamecube_joysticks[6] = {0};
bool z_button = false;

report_gamepad_t report = {
    .Button = 0,
    .LX = STICK_CENTER,
    .LY = STICK_CENTER,
    .RX = STICK_CENTER,
    .RY = STICK_CENTER,
    .HAT = HAT_CENTER
};

void board_init(void) {
    setPinOutput(C13);
    writePinLow(C13);
    gamecube_init();
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

    gamecube_scan(&gamecube_buttons, gamecube_joysticks);

    z_button = gamecube_buttons & GAMECUBE_Z;

    // Home & Capture
    if (gamecube_buttons & GAMECUBE_START) {
        if (z_button && !(report.Button & SWITCH_HOME))
            report.Button |= SWITCH_CAPTURE;
        else
            report.Button |= SWITCH_HOME;
    } else {
        report.Button &= ~SWITCH_HOME;
        report.Button &= ~SWITCH_CAPTURE;
    }
    // Y and L
    if (gamecube_buttons & GAMECUBE_Y) {
        if (z_button && !(report.Button & SWITCH_Y))
            report.Button |= SWITCH_L;
        else
            report.Button |= SWITCH_Y;
    } else {
        report.Button &= ~SWITCH_Y;
        report.Button &= ~SWITCH_L;
    }
    // X and R
    if (gamecube_buttons & GAMECUBE_X) {
        if (z_button && !(report.Button & SWITCH_X))
            report.Button |= SWITCH_R;
        else
            report.Button |= SWITCH_X;
    } else {
        report.Button &= ~SWITCH_X;
        report.Button &= ~SWITCH_R;
    }
    // B and -
    if (gamecube_buttons & GAMECUBE_B) {
        if (z_button && !(report.Button & SWITCH_B))
            report.Button |= SWITCH_MINUS;
        else
            report.Button |= SWITCH_B;
    } else {
        report.Button &= ~SWITCH_B;
        report.Button &= ~SWITCH_MINUS;
    }
    // A and +
    if (gamecube_buttons & GAMECUBE_A) {
        if (z_button && !(report.Button & SWITCH_A))
            report.Button |= SWITCH_PLUS;
        else
            report.Button |= SWITCH_A;
    } else {
        report.Button &= ~SWITCH_A;
        report.Button &= ~SWITCH_PLUS;
    }

    if (gamecube_buttons & GAMECUBE_L) {
        report.Button |= SWITCH_ZL;
    } else {
        report.Button &= ~SWITCH_ZL;
    }
    if (gamecube_buttons & GAMECUBE_R) {
        report.Button |= SWITCH_ZR;
    } else {
        report.Button &= ~SWITCH_ZR;
    }

    if ((gamecube_buttons & GAMECUBE_UP) && (gamecube_buttons & GAMECUBE_RIGHT))
        report.HAT = HAT_TOP_RIGHT;
    else if ((gamecube_buttons & GAMECUBE_UP) && (gamecube_buttons & GAMECUBE_LEFT))
        report.HAT = HAT_TOP_LEFT;
    else if ((gamecube_buttons & GAMECUBE_DOWN) && (gamecube_buttons & GAMECUBE_RIGHT))
        report.HAT = HAT_BOTTOM_RIGHT;
    else if ((gamecube_buttons & GAMECUBE_DOWN) && (gamecube_buttons & GAMECUBE_LEFT))
        report.HAT = HAT_BOTTOM_LEFT;
    else if (gamecube_buttons & GAMECUBE_UP)
        report.HAT = HAT_TOP;
    else if (gamecube_buttons & GAMECUBE_DOWN)
        report.HAT = HAT_BOTTOM;
    else if (gamecube_buttons & GAMECUBE_RIGHT)
        report.HAT = HAT_RIGHT;
    else if (gamecube_buttons & GAMECUBE_LEFT)
        report.HAT = HAT_LEFT;
    else
        report.HAT = HAT_CENTER;

    if (report.Button || report.HAT != HAT_CENTER)
        writePinHigh(C13);
    else
        writePinLow(C13);

    // joystick calculations
 
    report.LX = gamecube_joysticks[0];         
    report.LY = 255 - gamecube_joysticks[1];    
    report.RX = gamecube_joysticks[2];          
    report.RY = 255 - gamecube_joysticks[3];          

    send_gamepad(&report);

}