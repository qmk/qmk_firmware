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

enum outputs {
    OUTPUT_AUTO,

    OUTPUT_NONE,
    OUTPUT_USB,
    OUTPUT_BLUETOOTH,

    // backward compatibility
    OUTPUT_USB_AND_BT
};

/**
 * backward compatibility for BLUETOOTH_ENABLE, send to BT and USB by default
 */
#ifndef OUTPUT_DEFAULT
    #ifdef BLUETOOTH_ENABLE
        #define OUTPUT_DEFAULT OUTPUT_USB_AND_BT
    #else
        #define OUTPUT_DEFAULT OUTPUT_AUTO
    #endif
#endif

void set_output(uint8_t output);
void set_output_user(uint8_t output);
uint8_t auto_detect_output(void);
uint8_t where_to_send(void);