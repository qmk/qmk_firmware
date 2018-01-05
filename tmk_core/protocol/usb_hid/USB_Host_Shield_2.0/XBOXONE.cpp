/* Copyright (C) 2012 Kristian Lauszus, TKJ Electronics. All rights reserved.
   Copyright (C) 2015 guruthree

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

 guruthree
 Web      :  https://github.com/guruthree/
 */

#include "XBOXONE.h"
// To enable serial debugging see "settings.h"
//#define EXTRADEBUG // Uncomment to get even more debugging data
//#define PRINTREPORT // Uncomment to print the report send by the Xbox ONE Controller

XBOXONE::XBOXONE(USB *p) :
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

uint8_t XBOXONE::Init(uint8_t parent, uint8_t port, bool lowspeed) {
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
        Notify(PSTR("\r\nXBOXONE Init"), 0x80);
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

        if(!VIDPIDOK(VID, PID)) // Check VID
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
           configuration values for device, interface, endpoints and HID for the XBOXONE Controllers */

        /* Initialize data structures for endpoints of device */
        epInfo[ XBOX_OUTPUT_PIPE ].epAddr = 0x01; // XBOX one output endpoint
        epInfo[ XBOX_OUTPUT_PIPE ].epAttribs = USB_TRANSFER_TYPE_INTERRUPT;
        epInfo[ XBOX_OUTPUT_PIPE ].bmNakPower = USB_NAK_NOWAIT; // Only poll once for interrupt endpoints
        epInfo[ XBOX_OUTPUT_PIPE ].maxPktSize = EP_MAXPKTSIZE;
        epInfo[ XBOX_OUTPUT_PIPE ].bmSndToggle = 0;
        epInfo[ XBOX_OUTPUT_PIPE ].bmRcvToggle = 0;
        epInfo[ XBOX_INPUT_PIPE ].epAddr = 0x01; // XBOX one input endpoint
        epInfo[ XBOX_INPUT_PIPE ].epAttribs = USB_TRANSFER_TYPE_INTERRUPT;
        epInfo[ XBOX_INPUT_PIPE ].bmNakPower = USB_NAK_NOWAIT; // Only poll once for interrupt endpoints
        epInfo[ XBOX_INPUT_PIPE ].maxPktSize = EP_MAXPKTSIZE;
        epInfo[ XBOX_INPUT_PIPE ].bmSndToggle = 0;
        epInfo[ XBOX_INPUT_PIPE ].bmRcvToggle = 0;

        rcode = pUsb->setEpInfoEntry(bAddress, 3, epInfo);
        if(rcode)
                goto FailSetDevTblEntry;

        delay(200); // Give time for address change

        rcode = pUsb->setConf(bAddress, epInfo[ XBOX_CONTROL_PIPE ].epAddr, 1);
        if(rcode)
                goto FailSetConfDescr;

#ifdef DEBUG_USB_HOST
        Notify(PSTR("\r\nXbox One Controller Connected\r\n"), 0x80);
#endif

        delay(200); // let things settle

        // initialize the controller for input
        writeBuf[0] = 0x05;
        writeBuf[1] = 0x20;
        rcode = XboxCommand(writeBuf, 2);
        if (rcode)
                goto Fail;

        onInit();
        XboxOneConnected = true;
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
        Notify(PSTR("\r\nXbox One Init Failed, error code: "), 0x80);
        NotifyFail(rcode);
#endif
        Release();
        return rcode;
}

/* Performs a cleanup after failed Init() attempt */
uint8_t XBOXONE::Release() {
        XboxOneConnected = false;
        pUsb->GetAddressPool().FreeAddress(bAddress);
        bAddress = 0;
        bPollEnable = false;
#ifdef DEBUG_USB_HOST
        Notify(PSTR("\r\nXbox One Controller Disconnected\r\n"), 0x80);
#endif
        return 0;
}

uint8_t XBOXONE::Poll() {
        if(!bPollEnable)
                return 0;
        uint16_t BUFFER_SIZE = EP_MAXPKTSIZE;
        uint8_t rcode = pUsb->inTransfer(bAddress, epInfo[ XBOX_INPUT_PIPE ].epAddr, &BUFFER_SIZE, readBuf);
        if (!rcode) {
                readReport();
#ifdef PRINTREPORT
                printReport(); // Uncomment "#define PRINTREPORT" to print the report send by the Xbox ONE Controller
#endif
        }
#ifdef DEBUG_USB_HOST
                else if (rcode != 0x04) { // not a matter of no update to send
                Notify(PSTR("\r\nXbox One Poll Failed, error code: "), 0x80);
                NotifyFail(rcode);
                }
#endif
        return rcode;
}

void XBOXONE::readReport() {
        if(readBuf == NULL)
                return;
        if(readBuf[0] == 0x07) {
                // The XBOX button has a separate message
                if(readBuf[4] == 1)
                        ButtonState |= XBOX_BUTTONS[XBOX];
                else
                        ButtonState &= ~XBOX_BUTTONS[XBOX];
        }
        if(readBuf[0] != 0x20) { // Check if it's the correct report, otherwise return - the controller also sends different status reports
#ifdef EXTRADEBUG
                Notify(PSTR("\r\nXbox Poll: "), 0x80);
                D_PrintHex<uint8_t > (readBuf[0], 0x80); // 0x03 is a heart beat report!
#endif
                return;
        }

        uint16_t xbox = ButtonState & XBOX_BUTTONS[XBOX]; // Since the XBOX button is separate, save it and add it back in
        // xbox button from before, dpad, abxy, start/back, sync, stick click, shoulder buttons
        ButtonState = xbox | (((uint16_t)readBuf[5] & 0xF) << 8) | (readBuf[4] & 0xF0)  | (((uint16_t)readBuf[4] & 0x0C) << 10) | ((readBuf[4] & 0x01) << 3) | (((uint16_t)readBuf[5] & 0xC0) << 8) | ((readBuf[5] & 0x30) >> 4);

        triggerValue[0] = (uint16_t)(((uint16_t)readBuf[7] << 8) | readBuf[6]);
        triggerValue[1] = (uint16_t)(((uint16_t)readBuf[9] << 8) | readBuf[8]);

        hatValue[LeftHatX] = (int16_t)(((uint16_t)readBuf[11] << 8) | readBuf[10]);
        hatValue[LeftHatY] = (int16_t)(((uint16_t)readBuf[13] << 8) | readBuf[12]);
        hatValue[RightHatX] = (int16_t)(((uint16_t)readBuf[15] << 8) | readBuf[14]);
        hatValue[RightHatY] = (int16_t)(((uint16_t)readBuf[17] << 8) | readBuf[16]);

        //Notify(PSTR("\r\nButtonState"), 0x80);
        //PrintHex<uint16_t>(ButtonState, 0x80);

        if(ButtonState != OldButtonState) {
                ButtonClickState = ButtonState & ~OldButtonState; // Update click state variable
                OldButtonState = ButtonState;
        }

        // Handle click detection for triggers
        if(triggerValue[0] != 0 && triggerValueOld[0] == 0)
            L2Clicked = true;
        triggerValueOld[0] = triggerValue[0];
        if(triggerValue[1] != 0 && triggerValueOld[1] == 0)
            R2Clicked = true;
        triggerValueOld[1] = triggerValue[1];
}

void XBOXONE::printReport() { //Uncomment "#define PRINTREPORT" to print the report send by the Xbox ONE Controller
#ifdef PRINTREPORT
        if(readBuf == NULL)
                return;
        for(uint8_t i = 0; i < XBOX_REPORT_BUFFER_SIZE; i++) {
                D_PrintHex<uint8_t > (readBuf[i], 0x80);
                Notify(PSTR(" "), 0x80);
        }
        Notify(PSTR("\r\n"), 0x80);
#endif
}

uint16_t XBOXONE::getButtonPress(ButtonEnum b) {
        if(b == L2) // These are analog buttons
                return triggerValue[0];
        else if(b == R2)
                return triggerValue[1];
        return (bool)(ButtonState & ((uint16_t)pgm_read_word(&XBOX_BUTTONS[(uint8_t)b])));
}

bool XBOXONE::getButtonClick(ButtonEnum b) {
        if(b == L2) {
                if(L2Clicked) {
                        L2Clicked = false;
                        return true;
                }
                return false;
        } else if(b == R2) {
                if(R2Clicked) {
                        R2Clicked = false;
                        return true;
                }
                return false;
        }
        uint16_t button = pgm_read_word(&XBOX_BUTTONS[(uint8_t)b]);
        bool click = (ButtonClickState & button);
        ButtonClickState &= ~button; // clear "click" event
        return click;
}

int16_t XBOXONE::getAnalogHat(AnalogHatEnum a) {
        return hatValue[a];
}

/* Xbox Controller commands */
uint8_t XBOXONE::XboxCommand(uint8_t* data, uint16_t nbytes) {
        uint8_t rcode = pUsb->outTransfer(bAddress, epInfo[ XBOX_OUTPUT_PIPE ].epAddr, nbytes, data);
#ifdef DEBUG_USB_HOST
        Notify(PSTR("\r\nXboxCommand, Return: "), 0x80);
        D_PrintHex<uint8_t > (rcode, 0x80);
#endif
        return rcode;
}

void XBOXONE::onInit() {
        // a short buzz to show the controller is active
        writeBuf[0] = 0x09;
        writeBuf[1] = 0x08;
        writeBuf[2] = 0x00;
        writeBuf[3] = 0x09;
        writeBuf[4] = 0x00;
        writeBuf[5] = 0x0f;
        writeBuf[6] = 0x04;
        writeBuf[7] = 0x04;
        writeBuf[8] = 0x20;
        writeBuf[9] = 0x20;
        writeBuf[10] = 0x80;
        XboxCommand(writeBuf, 11);

        if(pFuncOnInit)
                pFuncOnInit(); // Call the user function
}
