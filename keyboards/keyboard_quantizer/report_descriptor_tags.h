
#pragma once

#ifdef __AVR__
#    define __INCLUDE_FROM_USB_DRIVER
#    define __INCLUDE_FROM_HID_DRIVER
#    include <LUFA/Drivers/USB/Class/Common/HIDParser.h>
#else
#    define HID_RI_TYPE_MASK 0x0C
#    define HID_RI_TAG_MASK 0xF0
#    define HID_RI_COLLECTION(x) 0xA0
#    define HID_RI_END_COLLECTION(x) 0xC0
#    define HID_RI_END_COLLECTION(x) 0xC0
#    define HID_RI_REPORT_ID(x) 0x84
#    define HID_RI_USAGE_PAGE(x) 0x04
#    define HID_RI_USAGE(x) 0x08
#    define HID_RI_USAGE_MINIMUM(x) 0x18
#    define HID_RI_USAGE_MAXIMUM(x) 0x28
#    define HID_RI_LOGICAL_MINIMUM(x) 0x14
#    define HID_RI_LOGICAL_MAXIMUM(x) 0x24
#    define HID_RI_REPORT_SIZE(x) 0x74
#    define HID_RI_REPORT_COUNT(x) 0x94
#    define HID_RI_INPUT(x) 0x80
#    define HID_RI_OUTPUT(x) 0x90
#endif
