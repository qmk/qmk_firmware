#ifndef HIDKEYBOARD_H

#include "stdint.h"
#include "stdbool.h"
#include "USBHID.h"
#include "report.h"


class HIDKeyboard : public USBDevice {
public:
    HIDKeyboard(uint16_t vendor_id = 0xFEED, uint16_t product_id = 0xabed, uint16_t product_release = 0x0001);

    bool sendReport(report_keyboard_t report);
    uint8_t leds(void);
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
    virtual void USBCallback_requestCompleted(uint8_t * buf, uint32_t length);
private:
    uint8_t led_state;
};

#endif
