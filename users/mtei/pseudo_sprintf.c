// Copyright 2022 Takeshi Ishii (@mtei)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "pseudo_sprintf.h"

static char *sprint_decimal(char *buf, int data) {
    if (data > 9) {
        buf = sprint_decimal(buf, data/10);
    }
    *buf++ = "0123456789"[data%10];
    *buf = '\0';
    return buf;
}

static char *sprint_hex(char *buf, uint32_t data) {
    if (data > 0xf) {
        buf = sprint_hex(buf, data/0x10);
    }
    *buf++ = "0123456789abcdef"[data & 0xf];
    *buf = '\0';
    return buf;
}

char *sprints(char *buf, char *src) {
    while (*src) {
        *buf++ = *src++;
    }
    *buf = '\0';
    return buf;
}

char *sprintx(char *buf, char *leadstr, uint32_t data) {
    buf = sprints(buf, leadstr);
    buf = sprint_hex(buf, data);
    return buf;
}

char *sprintd(char *buf, char *leadstr, int data) {
    buf = sprints(buf, leadstr);
    buf = sprint_decimal(buf, data);
    return buf;
}

char *sprint2d(char *buf, char *leadstr, int data) {
    buf = sprints(buf, leadstr);
    if (data > 99) {
        return sprint_decimal(buf, data);
    }
    if (data < 10) {
        *buf++ = ' ';
    }
    return sprint_decimal(buf, data);
}
