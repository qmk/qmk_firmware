/*
Copyright 2017 Priyadi Iman Nurcahyo
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

#include "outputselect.h"
#include "usb_util.h"

#ifdef BLUETOOTH_BLUEFRUIT_LE
#    include "bluefruit_le.h"
#endif

uint8_t desired_output = OUTPUT_DEFAULT;

/** \brief Set Output
 *
 * FIXME: Needs doc
 */
void set_output(uint8_t output) {
    set_output_user(output);
    desired_output = output;
}

/** \brief Set Output User
 *
 * FIXME: Needs doc
 */
__attribute__((weak)) void set_output_user(uint8_t output) {}

/** \brief Auto Detect Output
 *
 * FIXME: Needs doc
 */
uint8_t auto_detect_output(void) {
    if (usb_connected_state()) {
        return OUTPUT_USB;
    }

#ifdef BLUETOOTH_BLUEFRUIT_LE
    if (bluefruit_le_is_connected()) {
        return OUTPUT_BLUETOOTH;
    }
#endif

#ifdef BLUETOOTH_ENABLE
    return OUTPUT_BLUETOOTH;  // should check if BT is connected here
#endif

    return OUTPUT_NONE;
}

/** \brief Where To Send
 *
 * FIXME: Needs doc
 */
uint8_t where_to_send(void) {
    if (desired_output == OUTPUT_AUTO) {
        return auto_detect_output();
    }
    return desired_output;
}
