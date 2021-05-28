/* Copyright 2021
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "digitizer.h"

digitizer_t digitizerReport = {.tipswitch = 0, .inrange = 0, .id = 0, .x = 0, .y = 0, .status = DZ_INITIALIZED};

__attribute__((weak)) void digitizer_send(void) {
    if (digitizerReport.status & DZ_UPDATED) {
        host_digitizer_send(&digitizerReport);
        digitizerReport.status &= ~DZ_UPDATED;
    }
}

__attribute__((weak)) void digitizer_task(void) { digitizer_send(); }

digitizer_t digitizer_get_report(void) { return digitizerReport; }

void digitizer_set_report(digitizer_t newDigitizerReport) {
    digitizerReport = newDigitizerReport;
    digitizerReport.status |= DZ_UPDATED;
}