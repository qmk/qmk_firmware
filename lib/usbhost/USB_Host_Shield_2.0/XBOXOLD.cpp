/* Copyright (C) 2013 Kristian Lauszus, TKJ Electronics. All rights reserved.

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

#include "XBOXOLD.h"
// To enable serial debugging see "settings.h"
//#define EXTRADEBUG // Uncomment to get even more debugging data
//#define PRINTREPORT // Uncomment to print the report send by the Xbox controller

/** Buttons on the controllers */
const uint8_t XBOXOLD_BUTTONS[] PROGMEM = {
        0x01, // UP
        0x08, // RIGHT
        0x02, // DOWN
        0x04, // LEFT

        0x20, // BACK
        0x10, // START
        0x40, // L3
        0x80, // R3

        // A, B, X, Y, BLACK, WHITE, L1, and R1 are analog buttons
        4, // BLACK
        5, // WHTIE
        6, // L1
        7, // R1

        1, // B
        0, // A
        2, // X
        3, // Y
};

XBOXOLD::XBOXOLD(USB *p) :
pUsb(p), // pointer to USB class instance - mandatory
bAddress(0), // device address - mandatory
bPollEnable(false) { // don't start polling before dongle is connected
        for(uint8_t i = 0; i < XBOX_MAX_ENDPOINTS; i++) {
                epInfo[i].epAddr = 0;
                epInfo[i].maxPktSize = (i) ? 0 : 8;
                epInfo[i].epAttribs = 0;
                epInfo[i].bmNakPower = (i) ? USB_NAK_NOWAIT : USB_NAK_MAX_POWER;
        }

        if(pUsb) // register in USB subsystem
                pUsb->RegisterDeviceClass(this); //set devConfig[] entry
}

uint8_t XBOXOLD::Init(uint8_t parent, uint8_t port, bool lowspeed) {
        uint8_t buf[sizeof (USB_DEVICE_DESCRIPTOR)];
        USB_DEVICE_DESCRIPTOR * udd = reinterpret_cast<USB_DEVICE_DESCRIPTOR*>(buf);
        uint8_t rcode;
        UsbDevice *p = NULL;
        EpInfo *oldep_ptr = NULL;
        uint16_t PID;
        uint16_t VID;

        // get memory address of USB device address pool
        AddressPool &addrPool = pUsb->GetAddressPool();
#ifdef EXTRADEBUG
        Notify(PSTR("\r\nXBOXUSB Init"), 0x80);
#endif
        // check if address has already been assigned to an instance
        if(bAddress) {
#ifdef DEBUG_USB_HOST
                Notify(PSTR("\r\nAddress in use"), 0x80);
#endif
                return USB_ERROR_CLASS_INSTANCE_ALREADY_IN_USE;
        }

        // Get pointer to pseudo device with address 0 assigned
        p = addrPool.GetUsbDevicePtr(0);

        if(!p) {
#ifdef DEBUG_USB_HOST
                Notify(PSTR("\r\nAddress not found"), 0x80);
#endif
                return USB_ERROR_ADDRESS_NOT_FOUND_IN_POOL;
        }

        if(!p->epinfo) {
#ifdef DEBUG_USB_HOST
                Notify(PSTR("\r\nepinfo is null"), 0x80);
#endif
                return USB_ERROR_EPINFO_IS_NULL;
        }

        // Save old pointer to EP_RECORD of address 0
        oldep_ptr = p->epinfo;

        // Temporary assign new pointer to epInfo to p->epinfo in order to avoid toggle inconsistence
        p->epinfo = epInfo;

        p->lowspeed = lowspeed;

        // Get device descriptor
        rcode = pUsb->getDevDescr(0, 0, sizeof (USB_DEVICE_DESCRIPTOR), (uint8_t*)buf); // Get device descriptor - addr, ep, nbytes, data
        // Restore p->epinfo
        p->epinfo = oldep_ptr;

        if(rcode)
                goto FailGetDevDescr;

        VID = udd->idVendor;
        PID = udd->idProduct;

        if((VID != XBOX_VID && VID != MADCATZ_VID && VID != JOYTECH_VID) || (PID != XBOX_OLD_PID1 && PID != XBOX_OLD_PID2 && PID != XBOX_OLD_PID3 && PID != XBOX_OLD_PID4)) // Check if VID and PID match
                goto FailUnknownDevice;

        // Allocate new address according to device class
        bAddress = addrPool.AllocAddress(parent, false, port);

        if(!bAddress)
                return USB_ERROR_OUT_OF_ADDRESS_SPACE_IN_POOL;

        // Extract Max Packet Size from device descriptor
        epInfo[0].maxPktSize = udd->bMaxPacketSize0;

        // Assign new address to the device
        rcode = pUsb->setAddr(0, 0, bAddress);
        if(rcode) {
                p->lowspeed = false;
                addrPool.FreeAddress(bAddress);
                bAddress = 0;
#ifdef DEBUG_USB_HOST
                Notify(PSTR("\r\nsetAddr: "), 0x80);
                D_PrintHex<uint8_t > (rcode, 0x80);
#endif
                return rcode;
        }
#ifdef EXTRADEBUG
        Notify(PSTR("\r\nAddr: "), 0x80);
        D_PrintHex<uint8_t > (bAddress, 0x80);
#endif
        //delay(300); // Spec says you should wait at least 200ms

        p->lowspeed = false;

        //get pointer to assigned address record
        p = addrPool.GetUsbDevicePtr(bAddress);
        if(!p)
                return USB_ERROR_ADDRESS_NOT_FOUND_IN_POOL;

        p->lowspeed = lowspeed;

        // Assign epInfo to epinfo pointer - only EP0 is known
        rcode = pUsb->setEpInfoEntry(bAddress, 1, epInfo);
        if(rcode)
                goto FailSetDevTblEntry;

        /* The application will work in reduced host mode, so we can save program and data
           memory space. After verifying the VID we will use known values for the
           configuration values for device, interface, endpoints and HID for the XBOX controllers */

        /* Initialize data structures for endpoints of device */
        epInfo[ XBOX_INPUT_PIPE ].epAddr = 0x01; // XBOX report endpoint
        epInfo[ XBOX_INPUT_PIPE ].epAttribs = USB_TRANSFER_TYPE_INTERRUPT;
        epInfo[ XBOX_INPUT_PIPE ].bmNakPower = USB_NAK_NOWAIT; // Only poll once for interrupt endpoints
        epInfo[ XBOX_INPUT_PIPE ].maxPktSize = EP_MAXPKTSIZE;
        epInfo[ XBOX_INPUT_PIPE ].bmSndToggle = 0;
        epInfo[ XBOX_INPUT_PIPE ].bmRcvToggle = 0;
        epInfo[ XBOX_OUTPUT_PIPE ].epAddr = 0x02; // XBOX output endpoint
        epInfo[ XBOX_OUTPUT_PIPE ].epAttribs = USB_TRANSFER_TYPE_INTERRUPT;
        epInfo[ XBOX_OUTPUT_PIPE ].bmNakPower = USB_NAK_NOWAIT; // Only poll once for interrupt endpoints
        epInfo[ XBOX_OUTPUT_PIPE ].maxPktSize = EP_MAXPKTSIZE;
        epInfo[ XBOX_OUTPUT_PIPE ].bmSndToggle = 0;
        epInfo[ XBOX_OUTPUT_PIPE ].bmRcvToggle = 0;

        rcode = pUsb->setEpInfoEntry(bAddress, 3, epInfo);
        if(rcode)
                goto FailSetDevTblEntry;

        delay(200); // Give time for address change

        rcode = pUsb->setConf(bAddress, epInfo[ XBOX_CONTROL_PIPE ].epAddr, 1);
        if(rcode)
                goto FailSetConfDescr;

#ifdef DEBUG_USB_HOST
        Notify(PSTR("\r\nXbox Controller Connected\r\n"), 0x80);
#endif
        if(pFuncOnInit)
                pFuncOnInit(); // Call the user function
        XboxConnected = true;
        bPollEnable = true;
        return 0; // Successful configuration

        /* Diagnostic messages */
FailGetDevDescr:
#ifdef DEBUG_USB_HOST
        NotifyFailGetDevDescr();
        goto Fail;
#endif

FailSetDevTblEntry:
#ifdef DEBUG_USB_HOST
        NotifyFailSetDevTblEntry();
        goto Fail;
#endif

FailSetConfDescr:
#ifdef DEBUG_USB_HOST
        NotifyFailSetConfDescr();
#endif
        goto Fail;

FailUnknownDevice:
#ifdef DEBUG_USB_HOST
        NotifyFailUnknownDevice(VID, PID);
#endif
        rcode = USB_DEV_CONFIG_ERROR_DEVICE_NOT_SUPPORTED;

Fail:
#ifdef DEBUG_USB_HOST
        Notify(PSTR("\r\nXbox Init Failed, error code: "), 0x80);
        NotifyFail(rcode);
#endif
        Release();
        return rcode;
}

/* Performs a cleanup after failed Init() attempt */
uint8_t XBOXOLD::Release() {
        XboxConnected = false;
        pUsb->GetAddressPool().FreeAddress(bAddress);
        bAddress = 0;
        bPollEnable = false;
        return 0;
}

uint8_t XBOXOLD::Poll() {
        if(!bPollEnable)
                return 0;
        uint16_t BUFFER_SIZE = EP_MAXPKTSIZE;
        pUsb->inTransfer(bAddress, epInfo[ XBOX_INPUT_PIPE ].epAddr, &BUFFER_SIZE, readBuf); // input on endpoint 1
        readReport();
#ifdef PRINTREPORT
        printReport(BUFFER_SIZE); // Uncomment "#define PRINTREPORT" to print the report send by the Xbox controller
#endif
        return 0;
}

void XBOXOLD::readReport() {
        ButtonState = readBuf[2];

        for(uint8_t i = 0; i < sizeof (buttonValues); i++)
                buttonValues[i] = readBuf[i + 4]; // A, B, X, Y, BLACK, WHITE, L1, and R1

        hatValue[LeftHatX] = (int16_t)(((uint16_t)readBuf[12] << 8) | readBuf[13]);
        hatValue[LeftHatY] = (int16_t)(((uint16_t)readBuf[14] << 8) | readBuf[15]);
        hatValue[RightHatX] = (int16_t)(((uint16_t)readBuf[16] << 8) | readBuf[17]);
        hatValue[RightHatY] = (int16_t)(((uint16_t)readBuf[18] << 8) | readBuf[19]);

        //Notify(PSTR("\r\nButtonState"), 0x80);
        //PrintHex<uint8_t>(ButtonState, 0x80);

        if(ButtonState != OldButtonState || memcmp(buttonValues, oldButtonValues, sizeof (buttonValues)) != 0) {
                ButtonClickState = ButtonState & ~OldButtonState; // Update click state variable
                OldButtonState = ButtonState;

                for(uint8_t i = 0; i < sizeof (buttonValues); i++) {
                        if(oldButtonValues[i] == 0 && buttonValues[i] != 0)
                                buttonClicked[i] = true; // Update A, B, X, Y, BLACK, WHITE, L1, and R1 click state
                        oldButtonValues[i] = buttonValues[i];
                }
        }
}

void XBOXOLD::printReport(uint16_t length) { //Uncomment "#define PRINTREPORT" to print the report send by the Xbox controller
#ifdef PRINTREPORT
        if(readBuf == NULL)
                return;
        for(uint8_t i = 0; i < length; i++) {
                D_PrintHex<uint8_t > (readBuf[i], 0x80);
                Notify(PSTR(" "), 0x80);
        }
        Notify(PSTR("\r\n"), 0x80);
#endif
}

uint8_t XBOXOLD::getButtonPress(ButtonEnum b) {
        uint8_t button = pgm_read_byte(&XBOXOLD_BUTTONS[(uint8_t)b]);
        if(b == A || b == B || b == X || b == Y || b == BLACK || b == WHITE || b == L1 || b == R1) // A, B, X, Y, BLACK, WHITE, L1, and R1 are analog buttons
                return buttonValues[button]; // Analog buttons
        return (ButtonState & button); // Digital buttons
}

bool XBOXOLD::getButtonClick(ButtonEnum b) {
        uint8_t button = pgm_read_byte(&XBOXOLD_BUTTONS[(uint8_t)b]);
        if(b == A || b == B || b == X || b == Y || b == BLACK || b == WHITE || b == L1 || b == R1) { // A, B, X, Y, BLACK, WHITE, L1, and R1 are analog buttons
                if(buttonClicked[button]) {
                        buttonClicked[button] = false;
                        return true;
                }
                return false;
        }

        bool click = (ButtonClickState & button);
        ButtonClickState &= ~button; // clear "click" event
        return click;
}

int16_t XBOXOLD::getAnalogHat(AnalogHatEnum a) {
        return hatValue[a];
}

/* Xbox Controller commands */
void XBOXOLD::XboxCommand(uint8_t* data, uint16_t nbytes) {
        //bmRequest = Host to device (0x00) | Class (0x20) | Interface (0x01) = 0x21, bRequest = Set Report (0x09), Report ID (0x00), Report Type (Output 0x02), interface (0x00), datalength, datalength, data)
        pUsb->ctrlReq(bAddress, epInfo[XBOX_CONTROL_PIPE].epAddr, bmREQ_HID_OUT, HID_REQUEST_SET_REPORT, 0x00, 0x02, 0x00, nbytes, nbytes, data, NULL);
}

void XBOXOLD::setRumbleOn(uint8_t lValue, uint8_t rValue) {
        uint8_t writeBuf[6];

        writeBuf[0] = 0x00;
        writeBuf[1] = 0x06;
        writeBuf[2] = 0x00;
        writeBuf[3] = rValue; // small weight
        writeBuf[4] = 0x00;
        writeBuf[5] = lValue; // big weight

        XboxCommand(writeBuf, 6);
}
