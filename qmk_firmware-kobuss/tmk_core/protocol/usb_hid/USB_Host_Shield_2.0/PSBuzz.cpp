/* Copyright (C) 2014 Kristian Lauszus, TKJ Electronics. All rights reserved.

 This software may be distributed and modified under the terms of the GNU
 General Public License version 2 (GPL2) as published by the Free Software
 Foundation and appearing in the file GPL2.TXT included in the packaging of
 this file. Please note that GPL2 Section 2[b] requires that all works based
 on this software must also be made publicly available under the terms of
 the GPL2 ("Copyleft").

 Contact information
 -------------------

 Kristian Lauszus, TKJ Electronics
 Web      :  http://www.tkjelectronics.com
 e-mail   :  kristianl@tkjelectronics.com
 */

#include "PSBuzz.h"

// To enable serial debugging see "settings.h"
//#define PRINTREPORT // Uncomment to print the report send by the PS Buzz Controllers

void PSBuzz::ParseHIDData(HID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf) {
        if (HIDUniversal::VID == PSBUZZ_VID && HIDUniversal::PID == PSBUZZ_PID && len > 2 && buf) {
#ifdef PRINTREPORT
                Notify(PSTR("\r\n"), 0x80);
                for (uint8_t i = 0; i < len; i++) {
                        D_PrintHex<uint8_t > (buf[i], 0x80);
                        Notify(PSTR(" "), 0x80);
                }
#endif
                memcpy(&psbuzzButtons, buf + 2, min((uint8_t)(len - 2), sizeof(psbuzzButtons)));

                if (psbuzzButtons.val != oldButtonState.val) { // Check if anything has changed
                        buttonClickState.val = psbuzzButtons.val & ~oldButtonState.val; // Update click state variable
                        oldButtonState.val = psbuzzButtons.val;
                }
        }
};

uint8_t PSBuzz::OnInitSuccessful() {
        if (HIDUniversal::VID == PSBUZZ_VID && HIDUniversal::PID == PSBUZZ_PID) {
                Reset();
                if (pFuncOnInit)
                        pFuncOnInit(); // Call the user function
                else
                        setLedOnAll(); // Turn the LED on, on all four controllers
        };
        return 0;
};

bool PSBuzz::getButtonPress(ButtonEnum b, uint8_t controller) {
        return psbuzzButtons.val & (1UL << (b + 5 * controller)); // Each controller uses 5 bits, so the value is shifted 5 for each controller
};

bool PSBuzz::getButtonClick(ButtonEnum b, uint8_t controller) {
        uint32_t mask = (1UL << (b + 5 * controller)); // Each controller uses 5 bits, so the value is shifted 5 for each controller
        bool click = buttonClickState.val & mask;
        buttonClickState.val &= ~mask; // Clear "click" event
        return click;
};

// Source: http://www.developerfusion.com/article/84338/making-usb-c-friendly/ and https://github.com/torvalds/linux/blob/master/drivers/hid/hid-sony.c
void PSBuzz::setLedRaw(bool value, uint8_t controller) {
        ledState[controller] = value; // Save value for next time it is called

        uint8_t buf[7];
        buf[0] = 0x00;
        buf[1] = ledState[0] ? 0xFF : 0x00;
        buf[2] = ledState[1] ? 0xFF : 0x00;
        buf[3] = ledState[2] ? 0xFF : 0x00;
        buf[4] = ledState[3] ? 0xFF : 0x00;
        buf[5] = 0x00;
        buf[6] = 0x00;

        PSBuzz_Command(buf, sizeof(buf));
};

void PSBuzz::PSBuzz_Command(uint8_t *data, uint16_t nbytes) {
        // bmRequest = Host to device (0x00) | Class (0x20) | Interface (0x01) = 0x21, bRequest = Set Report (0x09), Report ID (0x00), Report Type (Output 0x02), interface (0x00), datalength, datalength, data)
        pUsb->ctrlReq(bAddress, epInfo[0].epAddr, bmREQ_HID_OUT, HID_REQUEST_SET_REPORT, 0x00, 0x02, 0x00, nbytes, nbytes, data, NULL);
};
