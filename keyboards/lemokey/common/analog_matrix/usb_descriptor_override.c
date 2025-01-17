/* Copyright 2024 @ Keychron (https://www.keychron.com)
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

#include "quantum.h"
#include "analog_matrix.h"
#include "raw_hid.h"
#include "usb_main.h"
#include <stdio.h>
#include "game_controller_common.h"

extern USB_Descriptor_Configuration_t PROGMEM            ConfigurationDescriptor[];
extern const USB_Descriptor_HIDReport_Datatype_t PROGMEM SharedReport[];

bool get_joy_stick_report_descriptor_info(uint16_t *pos_begin, uint16_t *pos_end) {
    uint16_t share_report_len             = ConfigurationDescriptor->Shared_HID.HIDReportLength;
    uint8_t  joystick_report_key_begin[4] = {0x05, 0x01, 0x09, 0x04};
    bool     find                         = false;

    for (uint16_t i = 0; i < share_report_len - 4; i++) {
        if (memcmp(SharedReport + i, joystick_report_key_begin, 4) == 0) {
            // Search joystick report descriptor end position starting from pos_begin
            for (uint16_t j = i; j < share_report_len - 2; j++) {
                if (SharedReport[j] == 0xC0 && SharedReport[j + 1] == 0xC0) {
                    *pos_begin = i;
                    *pos_end   = j + 2;
                    find       = true;
                    break;
                }
            }
            break;
        }
    }

    return find;
}

void get_usb_descriptor_kb(const uint16_t wValue, const uint16_t wIndex, const uint16_t wLength, const void **const DescriptorAddress, uint16_t *size) {
#if defined(JOYSTICK_ENABLE) && defined(XINPUT_ENABLE)

    const uint8_t   DescriptorType  = (wValue >> 8);
    const uint8_t   DescriptorIndex = (wValue & 0xFF);
    static bool     recal           = false;
    static uint16_t pos_begin, pos_end;
    static uint16_t original_hid_rpt_len = 0;

    if (original_hid_rpt_len == 0) original_hid_rpt_len = ConfigurationDescriptor->Shared_HID.HIDReportLength;

    switch (DescriptorType) {
        case DTYPE_String:
#    if defined(XINPUT_ENABLE)
            if (!game_controller_xinput_enabled() && DescriptorIndex == 0xEE) *size = 0;
#    endif
            break;

        case DTYPE_Configuration:
#    if defined(JOYSTICK_SHARED_EP)
        {
            if (game_controller_xinput_enabled()) {
                if (!recal && get_joy_stick_report_descriptor_info(&pos_begin, &pos_end)) {
                    ConfigurationDescriptor->Shared_HID.HIDReportLength -= (pos_end - pos_begin);
                    recal = true;
                }
            } else {
                uint8_t xinput_desc_len                                = sizeof(USB_Descriptor_Interface_t) + 0x11 + sizeof(USB_Descriptor_Endpoint_t) * 2;
                ConfigurationDescriptor->Config.TotalInterfaces        = TOTAL_INTERFACES - 1;
                ConfigurationDescriptor->Config.TotalConfigurationSize = sizeof(USB_Descriptor_Configuration_t) - xinput_desc_len;
                *size                                                  = sizeof(USB_Descriptor_Configuration_t) - xinput_desc_len;
                    }
        }
#    else
//  TODO:
//            uint8_t xinput_desc_len = sizeof(USB_Descriptor_Interface_t) + 0x11 + sizeof(USB_Descriptor_Endpoint_t) * 2;
//            uint8_t joy_desc_len    = sizeof(USB_Descriptor_Interface_t) + sizeof(USB_HID_Descriptor_HID_t) + sizeof(USB_Descriptor_Endpoint_t);
//            if (xinput_mode) {
//                static USB_Descriptor_Configuration_t *xinput_mode_desc = NULL;

//                if (xinput_mode_desc == NULL) {
//                    xinput_mode_desc = (void *)malloc(sizeof(USB_Descriptor_Configuration_t));
//                    memcpy(xinput_mode_desc, &ConfigurationDescriptor, sizeof(USB_Descriptor_Configuration_t));
//                    // Move xinput descriptor
//                    memcpy(&xinput_mode_desc->Joystick_Interface, &xinput_mode_desc->Xinput_Interface, xinput_desc_len);
//                }
//                *DescriptorAddress = xinput_mode_desc;
//                *Size -= joy_desc_len;
//            } else {
//                *Size -= xinput_desc_len;
//            }

#    endif
        break;
        case HID_DTYPE_Report:
            switch (wIndex) {
#    ifdef SHARED_EP_ENABLE
                case SHARED_INTERFACE:

                    *DescriptorAddress = &SharedReport;
                    uint16_t len       = ConfigurationDescriptor->Shared_HID.HIDReportLength;

                    if (game_controller_xinput_enabled()) {
                        static uint8_t *input_mode_rpt_desc = NULL;
                        if (input_mode_rpt_desc == NULL) {
                            input_mode_rpt_desc = (uint8_t *)malloc(original_hid_rpt_len);

                            memcpy(input_mode_rpt_desc, &SharedReport, original_hid_rpt_len);

                            if (pos_begin < original_hid_rpt_len - 4 && pos_end < original_hid_rpt_len - 2) {
                                // Move xinput descriptor
                                memcpy(input_mode_rpt_desc + pos_begin, input_mode_rpt_desc + pos_end, original_hid_rpt_len - pos_end);
                            }
                        }
                        *DescriptorAddress = input_mode_rpt_desc;
                        *size              = len;
                    }
                    break;
#    endif
            }
    }
#endif
}

void get_usb_vendor_descriptor_kb(uint8_t recipient, uint8_t reqeuest, const uint16_t wValue, const uint16_t wIndex, const uint16_t wLength, const void **const DescriptorAddress, uint16_t *size) {
#if XINPUT_ENABLE
    if (!game_controller_xinput_enabled()) {
        *size = 0;
        usb_lld_stall_in(&USBD1, 0);
    }
#endif
}
