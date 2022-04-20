/*
Copyright 2021 Thomas Weißschuh <thomas@t-8ch.de>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "programmable_button.h"
#include "host.h"

#define REPORT_BIT(index) (((uint32_t)1) << (index - 1))

static uint32_t programmable_button_report = 0;

void programmable_button_clear(void) {
    programmable_button_report = 0;
}

void programmable_button_send(void) {
    host_programmable_button_send(programmable_button_report);
}

void programmable_button_on(uint8_t index) {
    programmable_button_report |= REPORT_BIT(index);
}

void programmable_button_off(uint8_t index) {
    programmable_button_report &= ~REPORT_BIT(index);
}

bool programmable_button_is_on(uint8_t index) {
    return !!(programmable_button_report & REPORT_BIT(index));
};

uint32_t programmable_button_get_report(void) {
    return programmable_button_report;
};

void programmable_button_set_report(uint32_t report) {
    programmable_button_report = report;
}
