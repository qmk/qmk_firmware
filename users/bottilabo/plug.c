#include QMK_KEYBOARD_H
#include <stdio.h>
#include <string.h>
#include "plug.h"

bool plug_process_record_user(uint16_t keycode, keyrecord_t *record) {
    PLUG1_process_record_user;
    PLUG2_process_record_user;
    PLUG3_process_record_user;
    PLUG4_process_record_user;
    PLUG5_process_record_user;
    return true;
}

void plug_matrix_init_user(void) {
    PLUG1_matrix_init_user;
    PLUG2_matrix_init_user;
    PLUG3_matrix_init_user;
    PLUG4_matrix_init_user;
    PLUG5_matrix_init_user;
}

void plug_matrix_scan_user(void) {
    PLUG1_matrix_scan_user;
    PLUG2_matrix_scan_user;
    PLUG3_matrix_scan_user;
    PLUG4_matrix_scan_user;
    PLUG5_matrix_scan_user;
}

