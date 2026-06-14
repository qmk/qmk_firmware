/* Copyright 2021 dnaq
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

#include <limits.h>

#include "plover_hid.h"
#include "report.h"
#include "host.h"
#include "compiler_support.h"

// The button index handed to plover_hid_update() is `keycode - QK_PLOVER_HID`, so the report's
// data field must hold a bit for every keycode in the range or the bit-packing below overflows.
STATIC_ASSERT(sizeof(((report_plover_hid_t *)0)->data) * CHAR_BIT >= (QK_PLOVER_HID_MAX - QK_PLOVER_HID + 1), "Plover HID report data too small for the QK_PLOVER_HID keycode range");

static report_plover_hid_t plover_hid_report         = {.report_id = REPORT_ID_PLOVER_HID};
static bool                plover_hid_report_updated = false;

void plover_hid_update(uint8_t button, bool pressed) {
    if (pressed) {
        plover_hid_report.data[button / 8] |= (1 << (7 - (button % 8)));
    } else {
        plover_hid_report.data[button / 8] &= ~(1 << (7 - (button % 8)));
    }
    plover_hid_report_updated = true;
}

void plover_hid_task(void) {
    if (!plover_hid_report_updated) {
        return;
    }
    host_plover_hid_send(&plover_hid_report);
    plover_hid_report_updated = false;
}
