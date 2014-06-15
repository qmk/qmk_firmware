#ifndef HIDKEYBOARD_H

#include "stdint.h"
#include "stdbool.h"
#include "USBHID.h"


typedef union {
    uint8_t raw[8];
    struct {
        uint8_t mods;
        uint8_t reserved;
        uint8_t keys[6];
    };
} __attribute__ ((packed)) report_keyboard_t;


class HIDKeyboard : public USBDevice {
public:
    HIDKeyboard(uint16_t vendor_id = 0xFEED, uint16_t product_id = 0xabed, uint16_t product_release = 0x0001);

    bool sendReport(report_keyboard_t report);
protected:
    uint16_t reportLength;
    virtual bool USBCallback_setConfiguration(uint8_t configuration);
    virtual uint8_t * stringImanufacturerDesc();
    virtual uint8_t * stringIproductDesc();
    virtual uint8_t * stringIserialDesc();
    virtual uint16_t reportDescLength();
    virtual uint8_t * reportDesc();
    virtual uint8_t * configurationDesc();
    //virtual uint8_t * deviceDesc();
    virtual bool USBCallback_request();
};

#endif
