#include <stdint.h>
#include "USBHID.h"
#include "USBHID_Types.h"
#include "USBDescriptor.h"
#include "HIDKeyboard.h"

#define DEFAULT_CONFIGURATION (1)


HIDKeyboard::HIDKeyboard(uint16_t vendor_id, uint16_t product_id, uint16_t product_release): USBDevice(vendor_id, product_id, product_release)
{
    USBDevice::connect();
}

bool HIDKeyboard::sendReport(report_keyboard_t report) {
    USBDevice::write(EP1IN, report.raw, sizeof(report), MAX_PACKET_SIZE_EP1);
    return true;
}

uint8_t HIDKeyboard::leds() {
    return led_state;
}

bool HIDKeyboard::USBCallback_setConfiguration(uint8_t configuration) {
    if (configuration != DEFAULT_CONFIGURATION) {
        return false;
    }

    // Configure endpoints > 0
    addEndpoint(EPINT_IN, MAX_PACKET_SIZE_EPINT);
    //addEndpoint(EPINT_OUT, MAX_PACKET_SIZE_EPINT);

    // We activate the endpoint to be able to recceive data
    //readStart(EPINT_OUT, MAX_PACKET_SIZE_EPINT);
    return true;
}


uint8_t * HIDKeyboard::stringImanufacturerDesc() {
    static uint8_t stringImanufacturerDescriptor[] = {
        0x18,                                            /*bLength*/
        STRING_DESCRIPTOR,                               /*bDescriptorType 0x03*/
        't',0,'m',0,'k',0,'-',0,'k',0,'b',0,'d',0,'.',0,'c',0,'o',0,'m',0   /*bString iManufacturer*/
    };
    return stringImanufacturerDescriptor;
}

uint8_t * HIDKeyboard::stringIproductDesc() {
    static uint8_t stringIproductDescriptor[] = {
        0x0a,                                                       /*bLength*/
        STRING_DESCRIPTOR,                                          /*bDescriptorType 0x03*/
        'm',0,'b',0,'e',0,'d',0                                     /*bString iProduct*/
    };
    return stringIproductDescriptor;
}

uint8_t * HIDKeyboard::stringIserialDesc() {
    static uint8_t stringIserialDescriptor[] = {
        0x04,                                                           /*bLength*/
        STRING_DESCRIPTOR,                                              /*bDescriptorType 0x03*/
        '0',0                                                           /*bString iSerial*/
    };
    return stringIserialDescriptor;
}

uint8_t * HIDKeyboard::reportDesc() {
    static uint8_t reportDescriptor[] = {
        USAGE_PAGE(1), 0x01,                    // Generic Desktop
        USAGE(1), 0x06,                         // Keyboard
        COLLECTION(1), 0x01,                    // Application

        USAGE_PAGE(1), 0x07,                    // Key Codes
        USAGE_MINIMUM(1), 0xE0,
        USAGE_MAXIMUM(1), 0xE7,
        LOGICAL_MINIMUM(1), 0x00,
        LOGICAL_MAXIMUM(1), 0x01,
        REPORT_SIZE(1), 0x01,
        REPORT_COUNT(1), 0x08,
        INPUT(1), 0x02,                         // Data, Variable, Absolute

        REPORT_COUNT(1), 0x01,
        REPORT_SIZE(1), 0x08,
        INPUT(1), 0x01,                         // Constant

        REPORT_COUNT(1), 0x05,
        REPORT_SIZE(1), 0x01,
        USAGE_PAGE(1), 0x08,                    // LEDs
        USAGE_MINIMUM(1), 0x01,
        USAGE_MAXIMUM(1), 0x05,
        OUTPUT(1), 0x02,                        // Data, Variable, Absolute

        REPORT_COUNT(1), 0x01,
        REPORT_SIZE(1), 0x03,
        OUTPUT(1), 0x01,                        // Constant


        REPORT_COUNT(1), 0x06,
        REPORT_SIZE(1), 0x08,
        LOGICAL_MINIMUM(1), 0x00,
        LOGICAL_MAXIMUM(1), 0xFF,
        USAGE_PAGE(1), 0x07,                    // Key Codes
        USAGE_MINIMUM(1), 0x00,
        USAGE_MAXIMUM(1), 0xFF,
        INPUT(1), 0x00,                         // Data, Array
        END_COLLECTION(0),
    };
    reportLength = sizeof(reportDescriptor);
    return reportDescriptor;
}

uint16_t HIDKeyboard::reportDescLength() {
    reportDesc();
    return reportLength;
}

#define TOTAL_DESCRIPTOR_LENGTH ((1 * CONFIGURATION_DESCRIPTOR_LENGTH) \
                               + (1 * INTERFACE_DESCRIPTOR_LENGTH) \
                               + (1 * HID_DESCRIPTOR_LENGTH) \
                               + (1 * ENDPOINT_DESCRIPTOR_LENGTH))
uint8_t * HIDKeyboard::configurationDesc() {
    static uint8_t configurationDescriptor[] = {
        CONFIGURATION_DESCRIPTOR_LENGTH,// bLength
        CONFIGURATION_DESCRIPTOR,       // bDescriptorType
        LSB(TOTAL_DESCRIPTOR_LENGTH),   // wTotalLength (LSB)
        MSB(TOTAL_DESCRIPTOR_LENGTH),   // wTotalLength (MSB)
        0x01,                           // bNumInterfaces
        DEFAULT_CONFIGURATION,          // bConfigurationValue
        0x00,                           // iConfiguration
        C_RESERVED | C_REMOTE_WAKEUP,   // bmAttributes
        C_POWER(100),                   // bMaxPowerHello World from Mbed

        INTERFACE_DESCRIPTOR_LENGTH,    // bLength
        INTERFACE_DESCRIPTOR,           // bDescriptorType
        0x00,                           // bInterfaceNumber
        0x00,                           // bAlternateSetting
        0x01,                           // bNumEndpoints
        HID_CLASS,                      // bInterfaceClass
        1,                              // bInterfaceSubClass (boot)
        1,                              // bInterfaceProtocol (keyboard)
        0x00,                           // iInterface

        HID_DESCRIPTOR_LENGTH,          // bLength
        HID_DESCRIPTOR,                 // bDescriptorType
        LSB(HID_VERSION_1_11),          // bcdHID (LSB)
        MSB(HID_VERSION_1_11),          // bcdHID (MSB)
        0x00,                           // bCountryCode
        0x01,                           // bNumDescriptors
        REPORT_DESCRIPTOR,              // bDescriptorType
        (uint8_t)(LSB(reportDescLength())),  // wDescriptorLength (LSB)
        (uint8_t)(MSB(reportDescLength())),  // wDescriptorLength (MSB)

        ENDPOINT_DESCRIPTOR_LENGTH,     // bLength
        ENDPOINT_DESCRIPTOR,            // bDescriptorType
        PHY_TO_DESC(EP1IN),             // bEndpointAddress
        E_INTERRUPT,                    // bmAttributes
        LSB(MAX_PACKET_SIZE_EPINT),     // wMaxPacketSize (LSB)
        MSB(MAX_PACKET_SIZE_EPINT),     // wMaxPacketSize (MSB)
        1,                           // bInterval (milliseconds)
    };
    return configurationDescriptor;
}

#if 0
uint8_t * HIDKeyboard::deviceDesc() {
    static uint8_t deviceDescriptor[] = {
        DEVICE_DESCRIPTOR_LENGTH,       /* bLength */
        DEVICE_DESCRIPTOR,              /* bDescriptorType */
        LSB(USB_VERSION_2_0),           /* bcdUSB (LSB) */
        MSB(USB_VERSION_2_0),           /* bcdUSB (MSB) */
        0x00,                           /* bDeviceClass */
        0x00,                           /* bDeviceSubClass */
        0x00,                           /* bDeviceprotocol */
        MAX_PACKET_SIZE_EP0,            /* bMaxPacketSize0 */
        (uint8_t)(LSB(0xfeed)),                 /* idVendor (LSB) */
        (uint8_t)(MSB(0xfeed)),                 /* idVendor (MSB) */
        (uint8_t)(LSB(0x1bed)),                /* idProduct (LSB) */
        (uint8_t)(MSB(0x1bed)),                /* idProduct (MSB) */
        (uint8_t)(LSB(0x0002)),           /* bcdDevice (LSB) */
        (uint8_t)(MSB(0x0002)),           /* bcdDevice (MSB) */
        0,    /* iManufacturer */
        0,         /* iProduct */
        0,          /* iSerialNumber */
        0x01                            /* bNumConfigurations */
    };
    return deviceDescriptor;
}
#endif

bool HIDKeyboard::USBCallback_request() {
    bool success = false;
    CONTROL_TRANSFER * transfer = getTransferPtr();
    uint8_t *hidDescriptor;

    // Process additional standard requests

    if ((transfer->setup.bmRequestType.Type == STANDARD_TYPE))
    {
        switch (transfer->setup.bRequest)
        {
            case GET_DESCRIPTOR:
                switch (DESCRIPTOR_TYPE(transfer->setup.wValue))
                {
                    case REPORT_DESCRIPTOR:
                        if ((reportDesc() != NULL) \
                            && (reportDescLength() != 0))
                        {
                            transfer->remaining = reportDescLength();
                            transfer->ptr = reportDesc();
                            transfer->direction = DEVICE_TO_HOST;
                            success = true;
                        }
                        break;
                    case HID_DESCRIPTOR:
                            // Find the HID descriptor, after the configuration descriptor
                            hidDescriptor = findDescriptor(HID_DESCRIPTOR);
                            if (hidDescriptor != NULL)
                            {
                                transfer->remaining = HID_DESCRIPTOR_LENGTH;
                                transfer->ptr = hidDescriptor;
                                transfer->direction = DEVICE_TO_HOST;
                                success = true;
                            }
                            break;
                     
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }

    // Process class-specific requests
    if (transfer->setup.bmRequestType.Type == CLASS_TYPE)
    {
        switch (transfer->setup.bRequest) {
            case SET_REPORT:
                // LED indicator
                // TODO: check Interface and Report length?
                // if (transfer->setup.wIndex == INTERFACE_KEYBOAD) { }
                // if (transfer->setup.wLength == 1)

                transfer->remaining = 1;
                //transfer->ptr = ?? what ptr should be set when OUT(not used?)
                transfer->direction = HOST_TO_DEVICE;
                transfer->notify = true;    /* notify with USBCallback_requestCompleted */
                success = true;
            default:
                break;
        }
    }

    return success;
}

void HIDKeyboard::USBCallback_requestCompleted(uint8_t * buf, uint32_t length)
{
    if (length > 0) {
        CONTROL_TRANSFER *transfer = getTransferPtr();
        if (transfer->setup.bmRequestType.Type == CLASS_TYPE) {
            switch (transfer->setup.bRequest) {
                case SET_REPORT:
                    led_state = buf[0];
                    break;
                default:
                    break;
            }
        }
    }
}
