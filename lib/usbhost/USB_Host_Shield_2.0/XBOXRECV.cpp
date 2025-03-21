/* Copyright (C) 2012 Kristian Lauszus, TKJ Electronics. All rights reserved.

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

 getBatteryLevel and checkStatus functions made by timstamp.co.uk found using BusHound from Perisoft.net
 */

#include "XBOXRECV.h"
// To enable serial debugging see "settings.h"
//#define EXTRADEBUG // Uncomment to get even more debugging data
//#define PRINTREPORT // Uncomment to print the report send by the Xbox 360 Controller

XBOXRECV::XBOXRECV(USB *p) :
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

uint8_t XBOXRECV::ConfigureDevice(uint8_t parent, uint8_t port, bool lowspeed) {
        const uint8_t constBufSize = sizeof (USB_DEVICE_DESCRIPTOR);
        uint8_t buf[constBufSize];
        USB_DEVICE_DESCRIPTOR * udd = reinterpret_cast<USB_DEVICE_DESCRIPTOR*>(buf);
        uint8_t rcode;
        UsbDevice *p = NULL;
        EpInfo *oldep_ptr = NULL;
        uint16_t PID, VID;

        AddressPool &addrPool = pUsb->GetAddressPool(); // Get memory address of USB device address pool
#ifdef EXTRADEBUG
        Notify(PSTR("\r\nXBOXRECV Init"), 0x80);
#endif

        if(bAddress) { // Check if address has already been assigned to an instance
#ifdef DEBUG_USB_HOST
                Notify(PSTR("\r\nAddress in use"), 0x80);
#endif
                return USB_ERROR_CLASS_INSTANCE_ALREADY_IN_USE;
        }

        p = addrPool.GetUsbDevicePtr(0); // Get pointer to pseudo device with address 0 assigned

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

        oldep_ptr = p->epinfo; // Save old pointer to EP_RECORD of address 0
        p->epinfo = epInfo; // Temporary assign new pointer to epInfo to p->epinfo in order to avoid toggle inconsistence
        p->lowspeed = lowspeed;

        rcode = pUsb->getDevDescr(0, 0, constBufSize, (uint8_t*)buf); // Get device descriptor - addr, ep, nbytes, data

        p->epinfo = oldep_ptr; // Restore p->epinfo

        if(rcode)
                goto FailGetDevDescr;

        VID = udd->idVendor;
        PID = udd->idProduct;

        if((VID != XBOX_VID && VID != MADCATZ_VID && VID != JOYTECH_VID) || (PID != XBOX_WIRELESS_RECEIVER_PID && PID != XBOX_WIRELESS_RECEIVER_THIRD_PARTY_PID)) { // Check if it's a Xbox receiver using the Vendor ID and Product ID
#ifdef DEBUG_USB_HOST
                Notify(PSTR("\r\nYou'll need a wireless receiver for this libary to work"), 0x80);
#endif
                goto FailUnknownDevice;
        }

        bAddress = addrPool.AllocAddress(parent, false, port); // Allocate new address according to device class

        if(!bAddress) {
#ifdef DEBUG_USB_HOST
                Notify(PSTR("\r\nOut of address space"), 0x80);
#endif
                return USB_ERROR_OUT_OF_ADDRESS_SPACE_IN_POOL;
        }

        epInfo[0].maxPktSize = udd->bMaxPacketSize0; // Extract Max Packet Size from device descriptor

        delay(20); // Wait a little before resetting device

        return USB_ERROR_CONFIG_REQUIRES_ADDITIONAL_RESET;

        /* Diagnostic messages */
FailGetDevDescr:
#ifdef DEBUG_USB_HOST
        NotifyFailGetDevDescr(rcode);
#endif
        if(rcode != hrJERR)
                rcode = USB_ERROR_FailGetDevDescr;
        goto Fail;

FailUnknownDevice:
#ifdef DEBUG_USB_HOST
        NotifyFailUnknownDevice(VID, PID);
#endif
        rcode = USB_DEV_CONFIG_ERROR_DEVICE_NOT_SUPPORTED;

Fail:
#ifdef DEBUG_USB_HOST
        Notify(PSTR("\r\nXbox 360 Init Failed, error code: "), 0x80);
        NotifyFail(rcode);
#endif
        Release();
        return rcode;
};

uint8_t XBOXRECV::Init(uint8_t parent, uint8_t port, bool lowspeed) {
        uint8_t rcode;

        AddressPool &addrPool = pUsb->GetAddressPool();
#ifdef EXTRADEBUG
        Notify(PSTR("\r\nBTD Init"), 0x80);
#endif
        UsbDevice *p = addrPool.GetUsbDevicePtr(bAddress); // Get pointer to assigned address record

        if(!p) {
#ifdef DEBUG_USB_HOST
                Notify(PSTR("\r\nAddress not found"), 0x80);
#endif
                return USB_ERROR_ADDRESS_NOT_FOUND_IN_POOL;
        }

        delay(300); // Assign new address to the device

        rcode = pUsb->setAddr(0, 0, bAddress); // Assign new address to the device
        if(rcode) {
#ifdef DEBUG_USB_HOST
                Notify(PSTR("\r\nsetAddr: "), 0x80);
                D_PrintHex<uint8_t > (rcode, 0x80);
#endif
                p->lowspeed = false;
                goto Fail;
        }
#ifdef EXTRADEBUG
        Notify(PSTR("\r\nAddr: "), 0x80);
        D_PrintHex<uint8_t > (bAddress, 0x80);
#endif

        p->lowspeed = false;

        p = addrPool.GetUsbDevicePtr(bAddress); // Get pointer to assigned address record
        if(!p) {
#ifdef DEBUG_USB_HOST
                Notify(PSTR("\r\nAddress not found"), 0x80);
#endif
                return USB_ERROR_ADDRESS_NOT_FOUND_IN_POOL;
        }

        p->lowspeed = lowspeed;

        rcode = pUsb->setEpInfoEntry(bAddress, 1, epInfo); // Assign epInfo to epinfo pointer - only EP0 is known
        if(rcode)
                goto FailSetDevTblEntry;

        /* The application will work in reduced host mode, so we can save program and data
           memory space. After verifying the VID we will use known values for the
           configuration values for device, interface, endpoints and HID for the XBOX360 Wireless receiver */

        /* Initialize data structures for endpoints of device */
        epInfo[ XBOX_INPUT_PIPE_1 ].epAddr = 0x01; // XBOX 360 report endpoint - poll interval 1ms
        epInfo[ XBOX_INPUT_PIPE_1 ].epAttribs = USB_TRANSFER_TYPE_INTERRUPT;
        epInfo[ XBOX_INPUT_PIPE_1 ].bmNakPower = USB_NAK_NOWAIT; // Only poll once for interrupt endpoints
        epInfo[ XBOX_INPUT_PIPE_1 ].maxPktSize = EP_MAXPKTSIZE;
        epInfo[ XBOX_INPUT_PIPE_1 ].bmSndToggle = 0;
        epInfo[ XBOX_INPUT_PIPE_1 ].bmRcvToggle = 0;
        epInfo[ XBOX_OUTPUT_PIPE_1 ].epAddr = 0x01; // XBOX 360 output endpoint - poll interval 8ms
        epInfo[ XBOX_OUTPUT_PIPE_1 ].epAttribs = USB_TRANSFER_TYPE_INTERRUPT;
        epInfo[ XBOX_OUTPUT_PIPE_1 ].bmNakPower = USB_NAK_NOWAIT; // Only poll once for interrupt endpoints
        epInfo[ XBOX_OUTPUT_PIPE_1 ].maxPktSize = EP_MAXPKTSIZE;
        epInfo[ XBOX_OUTPUT_PIPE_1 ].bmSndToggle = 0;
        epInfo[ XBOX_OUTPUT_PIPE_1 ].bmRcvToggle = 0;

        epInfo[ XBOX_INPUT_PIPE_2 ].epAddr = 0x03; // XBOX 360 report endpoint - poll interval 1ms
        epInfo[ XBOX_INPUT_PIPE_2 ].epAttribs = USB_TRANSFER_TYPE_INTERRUPT;
        epInfo[ XBOX_INPUT_PIPE_2 ].bmNakPower = USB_NAK_NOWAIT; // Only poll once for interrupt endpoints
        epInfo[ XBOX_INPUT_PIPE_2 ].maxPktSize = EP_MAXPKTSIZE;
        epInfo[ XBOX_INPUT_PIPE_2 ].bmSndToggle = 0;
        epInfo[ XBOX_INPUT_PIPE_2 ].bmRcvToggle = 0;
        epInfo[ XBOX_OUTPUT_PIPE_2 ].epAddr = 0x03; // XBOX 360 output endpoint - poll interval 8ms
        epInfo[ XBOX_OUTPUT_PIPE_2 ].epAttribs = USB_TRANSFER_TYPE_INTERRUPT;
        epInfo[ XBOX_OUTPUT_PIPE_2 ].bmNakPower = USB_NAK_NOWAIT; // Only poll once for interrupt endpoints
        epInfo[ XBOX_OUTPUT_PIPE_2 ].maxPktSize = EP_MAXPKTSIZE;
        epInfo[ XBOX_OUTPUT_PIPE_2 ].bmSndToggle = 0;
        epInfo[ XBOX_OUTPUT_PIPE_2 ].bmRcvToggle = 0;

        epInfo[ XBOX_INPUT_PIPE_3 ].epAddr = 0x05; // XBOX 360 report endpoint - poll interval 1ms
        epInfo[ XBOX_INPUT_PIPE_3 ].epAttribs = USB_TRANSFER_TYPE_INTERRUPT;
        epInfo[ XBOX_INPUT_PIPE_3 ].bmNakPower = USB_NAK_NOWAIT; // Only poll once for interrupt endpoints
        epInfo[ XBOX_INPUT_PIPE_3 ].maxPktSize = EP_MAXPKTSIZE;
        epInfo[ XBOX_INPUT_PIPE_3 ].bmSndToggle = 0;
        epInfo[ XBOX_INPUT_PIPE_3 ].bmRcvToggle = 0;
        epInfo[ XBOX_OUTPUT_PIPE_3 ].epAddr = 0x05; // XBOX 360 output endpoint - poll interval 8ms
        epInfo[ XBOX_OUTPUT_PIPE_3 ].epAttribs = USB_TRANSFER_TYPE_INTERRUPT;
        epInfo[ XBOX_OUTPUT_PIPE_3 ].bmNakPower = USB_NAK_NOWAIT; // Only poll once for interrupt endpoints
        epInfo[ XBOX_OUTPUT_PIPE_3 ].maxPktSize = EP_MAXPKTSIZE;
        epInfo[ XBOX_OUTPUT_PIPE_3 ].bmSndToggle = 0;
        epInfo[ XBOX_OUTPUT_PIPE_3 ].bmRcvToggle = 0;

        epInfo[ XBOX_INPUT_PIPE_4 ].epAddr = 0x07; // XBOX 360 report endpoint - poll interval 1ms
        epInfo[ XBOX_INPUT_PIPE_4 ].epAttribs = USB_TRANSFER_TYPE_INTERRUPT;
        epInfo[ XBOX_INPUT_PIPE_4 ].bmNakPower = USB_NAK_NOWAIT; // Only poll once for interrupt endpoints
        epInfo[ XBOX_INPUT_PIPE_4 ].maxPktSize = EP_MAXPKTSIZE;
        epInfo[ XBOX_INPUT_PIPE_4 ].bmSndToggle = 0;
        epInfo[ XBOX_INPUT_PIPE_4 ].bmRcvToggle = 0;
        epInfo[ XBOX_OUTPUT_PIPE_4 ].epAddr = 0x07; // XBOX 360 output endpoint - poll interval 8ms
        epInfo[ XBOX_OUTPUT_PIPE_4 ].epAttribs = USB_TRANSFER_TYPE_INTERRUPT;
        epInfo[ XBOX_OUTPUT_PIPE_4 ].bmNakPower = USB_NAK_NOWAIT; // Only poll once for interrupt endpoints
        epInfo[ XBOX_OUTPUT_PIPE_4 ].maxPktSize = EP_MAXPKTSIZE;
        epInfo[ XBOX_OUTPUT_PIPE_4 ].bmSndToggle = 0;
        epInfo[ XBOX_OUTPUT_PIPE_4 ].bmRcvToggle = 0;

        rcode = pUsb->setEpInfoEntry(bAddress, 9, epInfo);
        if(rcode)
                goto FailSetDevTblEntry;

        delay(200); //Give time for address change

        rcode = pUsb->setConf(bAddress, epInfo[ XBOX_CONTROL_PIPE ].epAddr, 1);
        if(rcode)
                goto FailSetConfDescr;

#ifdef DEBUG_USB_HOST
        Notify(PSTR("\r\nXbox Wireless Receiver Connected\r\n"), 0x80);
#endif
        XboxReceiverConnected = true;
        bPollEnable = true;
        checkStatusTimer = 0; // Reset timer
        return 0; // Successful configuration

        /* Diagnostic messages */
FailSetDevTblEntry:
#ifdef DEBUG_USB_HOST
        NotifyFailSetDevTblEntry();
        goto Fail;
#endif

FailSetConfDescr:
#ifdef DEBUG_USB_HOST
        NotifyFailSetConfDescr();
#endif

Fail:
#ifdef DEBUG_USB_HOST
        Notify(PSTR("\r\nXbox 360 Init Failed, error code: "), 0x80);
        NotifyFail(rcode);
#endif
        Release();
        return rcode;
}

/* Performs a cleanup after failed Init() attempt */
uint8_t XBOXRECV::Release() {
        XboxReceiverConnected = false;
        for(uint8_t i = 0; i < 4; i++)
                Xbox360Connected[i] = 0x00;
        pUsb->GetAddressPool().FreeAddress(bAddress);
        bAddress = 0;
        bPollEnable = false;
        return 0;
}

uint8_t XBOXRECV::Poll() {
        if(!bPollEnable)
                return 0;
        if(!checkStatusTimer || ((millis() - checkStatusTimer) > 3000)) { // Run checkStatus every 3 seconds
                checkStatusTimer = millis();
                checkStatus();
        }

        uint8_t inputPipe;
        uint16_t bufferSize;
        for(uint8_t i = 0; i < 4; i++) {
                if(i == 0)
                        inputPipe = XBOX_INPUT_PIPE_1;
                else if(i == 1)
                        inputPipe = XBOX_INPUT_PIPE_2;
                else if(i == 2)
                        inputPipe = XBOX_INPUT_PIPE_3;
                else
                        inputPipe = XBOX_INPUT_PIPE_4;

                bufferSize = EP_MAXPKTSIZE; // This is the maximum number of bytes we want to receive
                pUsb->inTransfer(bAddress, epInfo[ inputPipe ].epAddr, &bufferSize, readBuf);
                if(bufferSize > 0) { // The number of received bytes
#ifdef EXTRADEBUG
                        Notify(PSTR("Bytes Received: "), 0x80);
                        D_PrintHex<uint16_t > (bufferSize, 0x80);
                        Notify(PSTR("\r\n"), 0x80);
#endif
                        readReport(i);
#ifdef PRINTREPORT
                        printReport(i, bufferSize); // Uncomment "#define PRINTREPORT" to print the report send by the Xbox 360 Controller
#endif
                }
        }
        return 0;
}

void XBOXRECV::readReport(uint8_t controller) {
        if(readBuf == NULL)
                return;
        // This report is send when a controller is connected and disconnected
        if(readBuf[0] == 0x08 && readBuf[1] != Xbox360Connected[controller]) {
                Xbox360Connected[controller] = readBuf[1];
#ifdef DEBUG_USB_HOST
                Notify(PSTR("Controller "), 0x80);
                Notify(controller, 0x80);
#endif
                if(Xbox360Connected[controller]) {
#ifdef DEBUG_USB_HOST
                        const char* str = 0;
                        switch(readBuf[1]) {
                                case 0x80: str = PSTR(" as controller\r\n");
                                        break;
                                case 0x40: str = PSTR(" as headset\r\n");
                                        break;
                                case 0xC0: str = PSTR(" as controller+headset\r\n");
                                        break;
                        }
                        Notify(PSTR(": connected"), 0x80);
                        Notify(str, 0x80);
#endif
                        onInit(controller);
                }
#ifdef DEBUG_USB_HOST
                else
                        Notify(PSTR(": disconnected\r\n"), 0x80);
#endif
                return;
        }
        // Controller status report
        if(readBuf[1] == 0x00 && readBuf[3] & 0x13 && readBuf[4] >= 0x22) {
                controllerStatus[controller] = ((uint16_t)readBuf[3] << 8) | readBuf[4];
                return;
        }
        if(readBuf[1] != 0x01) // Check if it's the correct report - the receiver also sends different status reports
                return;

        // A controller must be connected if it's sending data
        if(!Xbox360Connected[controller])
                Xbox360Connected[controller] |= 0x80;

        ButtonState[controller] = (uint32_t)(readBuf[9] | ((uint16_t)readBuf[8] << 8) | ((uint32_t)readBuf[7] << 16) | ((uint32_t)readBuf[6] << 24));

        hatValue[controller][LeftHatX] = (int16_t)(((uint16_t)readBuf[11] << 8) | readBuf[10]);
        hatValue[controller][LeftHatY] = (int16_t)(((uint16_t)readBuf[13] << 8) | readBuf[12]);
        hatValue[controller][RightHatX] = (int16_t)(((uint16_t)readBuf[15] << 8) | readBuf[14]);
        hatValue[controller][RightHatY] = (int16_t)(((uint16_t)readBuf[17] << 8) | readBuf[16]);

        //Notify(PSTR("\r\nButtonState: "), 0x80);
        //PrintHex<uint32_t>(ButtonState[controller], 0x80);

        if(ButtonState[controller] != OldButtonState[controller]) {
                buttonStateChanged[controller] = true;
                ButtonClickState[controller] = (ButtonState[controller] >> 16) & ((~OldButtonState[controller]) >> 16); // Update click state variable, but don't include the two trigger buttons L2 and R2
                if(((uint8_t)OldButtonState[controller]) == 0 && ((uint8_t)ButtonState[controller]) != 0) // The L2 and R2 buttons are special as they are analog buttons
                        R2Clicked[controller] = true;
                if((uint8_t)(OldButtonState[controller] >> 8) == 0 && (uint8_t)(ButtonState[controller] >> 8) != 0)
                        L2Clicked[controller] = true;
                OldButtonState[controller] = ButtonState[controller];
        }
}

void XBOXRECV::printReport(uint8_t controller, uint8_t nBytes) { //Uncomment "#define PRINTREPORT" to print the report send by the Xbox 360 Controller
#ifdef PRINTREPORT
        if(readBuf == NULL)
                return;
        Notify(PSTR("Controller "), 0x80);
        Notify(controller, 0x80);
        Notify(PSTR(": "), 0x80);
        for(uint8_t i = 0; i < nBytes; i++) {
                D_PrintHex<uint8_t > (readBuf[i], 0x80);
                Notify(PSTR(" "), 0x80);
        }
        Notify(PSTR("\r\n"), 0x80);
#endif
}

uint8_t XBOXRECV::getButtonPress(ButtonEnum b, uint8_t controller) {
        if(b == L2) // These are analog buttons
                return (uint8_t)(ButtonState[controller] >> 8);
        else if(b == R2)
                return (uint8_t)ButtonState[controller];
        return (bool)(ButtonState[controller] & ((uint32_t)pgm_read_word(&XBOX_BUTTONS[(uint8_t)b]) << 16));
}

bool XBOXRECV::getButtonClick(ButtonEnum b, uint8_t controller) {
        if(b == L2) {
                if(L2Clicked[controller]) {
                        L2Clicked[controller] = false;
                        return true;
                }
                return false;
        } else if(b == R2) {
                if(R2Clicked[controller]) {
                        R2Clicked[controller] = false;
                        return true;
                }
                return false;
        }
        uint16_t button = pgm_read_word(&XBOX_BUTTONS[(uint8_t)b]);
        bool click = (ButtonClickState[controller] & button);
        ButtonClickState[controller] &= ~button; // clear "click" event
        return click;
}

int16_t XBOXRECV::getAnalogHat(AnalogHatEnum a, uint8_t controller) {
        return hatValue[controller][a];
}

bool XBOXRECV::buttonChanged(uint8_t controller) {
        bool state = buttonStateChanged[controller];
        buttonStateChanged[controller] = false;
        return state;
}

/*
ControllerStatus Breakdown
ControllerStatus[controller] & 0x0001   // 0
ControllerStatus[controller] & 0x0002   // normal batteries, no rechargeable battery pack
ControllerStatus[controller] & 0x0004   // controller starting up / settling
ControllerStatus[controller] & 0x0008   // headset adapter plugged in, but no headphones connected (mute?)
ControllerStatus[controller] & 0x0010   // 0
ControllerStatus[controller] & 0x0020   // 1
ControllerStatus[controller] & 0x0040   // battery level (high bit)
ControllerStatus[controller] & 0x0080   // battery level (low bit)
ControllerStatus[controller] & 0x0100   // 1
ControllerStatus[controller] & 0x0200   // 1
ControllerStatus[controller] & 0x0400   // headset adapter plugged in
ControllerStatus[controller] & 0x0800   // 0
ControllerStatus[controller] & 0x1000   // 1
ControllerStatus[controller] & 0x2000   // 0
ControllerStatus[controller] & 0x4000   // 0
ControllerStatus[controller] & 0x8000   // 0
 */
uint8_t XBOXRECV::getBatteryLevel(uint8_t controller) {
        return ((controllerStatus[controller] & 0x00C0) >> 6);
}

void XBOXRECV::XboxCommand(uint8_t controller, uint8_t* data, uint16_t nbytes) {
#ifdef EXTRADEBUG
        uint8_t rcode;
#endif
        uint8_t outputPipe;
        switch(controller) {
                case 0: outputPipe = XBOX_OUTPUT_PIPE_1;
                        break;
                case 1: outputPipe = XBOX_OUTPUT_PIPE_2;
                        break;
                case 2: outputPipe = XBOX_OUTPUT_PIPE_3;
                        break;
                case 3: outputPipe = XBOX_OUTPUT_PIPE_4;
                        break;
                default:
                        return;
        }
#ifdef EXTRADEBUG
        rcode =
#endif
                pUsb->outTransfer(bAddress, epInfo[ outputPipe ].epAddr, nbytes, data);
#ifdef EXTRADEBUG
        if(rcode)
                Notify(PSTR("Error sending Xbox message\r\n"), 0x80);
#endif
}

void XBOXRECV::disconnect(uint8_t controller) {
        writeBuf[0] = 0x00;
        writeBuf[1] = 0x00;
        writeBuf[2] = 0x08;
        writeBuf[3] = 0xC0;

        XboxCommand(controller, writeBuf, 4);
}

void XBOXRECV::setLedRaw(uint8_t value, uint8_t controller) {
        writeBuf[0] = 0x00;
        writeBuf[1] = 0x00;
        writeBuf[2] = 0x08;
        writeBuf[3] = value | 0x40;

        XboxCommand(controller, writeBuf, 4);
}

void XBOXRECV::setLedOn(LEDEnum led, uint8_t controller) {
        if(led == OFF)
                setLedRaw(0, controller);
        else if(led != ALL) // All LEDs can't be on a the same time
                setLedRaw(pgm_read_byte(&XBOX_LEDS[(uint8_t)led]) + 4, controller);
}

void XBOXRECV::setLedBlink(LEDEnum led, uint8_t controller) {
        setLedRaw(pgm_read_byte(&XBOX_LEDS[(uint8_t)led]), controller);
}

void XBOXRECV::setLedMode(LEDModeEnum ledMode, uint8_t controller) { // This function is used to do some speciel LED stuff the controller supports
        setLedRaw((uint8_t)ledMode, controller);
}

/* PC runs this at interval of approx 2 seconds
Thanks to BusHound from Perisoft.net for the Windows USB Analysis output
Found by timstamp.co.uk
 */
void XBOXRECV::checkStatus() {
        if(!bPollEnable)
                return;
        // Get controller info
        writeBuf[0] = 0x08;
        writeBuf[1] = 0x00;
        writeBuf[2] = 0x0f;
        writeBuf[3] = 0xc0;
        for(uint8_t i = 0; i < 4; i++) {
                XboxCommand(i, writeBuf, 4);
        }
        // Get battery status
        writeBuf[0] = 0x00;
        writeBuf[1] = 0x00;
        writeBuf[2] = 0x00;
        writeBuf[3] = 0x40;
        for(uint8_t i = 0; i < 4; i++) {
                if(Xbox360Connected[i])
                        XboxCommand(i, writeBuf, 4);
        }
}

void XBOXRECV::setRumbleOn(uint8_t lValue, uint8_t rValue, uint8_t controller) {
        writeBuf[0] = 0x00;
        writeBuf[1] = 0x01;
        writeBuf[2] = 0x0f;
        writeBuf[3] = 0xc0;
        writeBuf[4] = 0x00;
        writeBuf[5] = lValue; // big weight
        writeBuf[6] = rValue; // small weight

        XboxCommand(controller, writeBuf, 7);
}

void XBOXRECV::onInit(uint8_t controller) {
        if(pFuncOnInit)
                pFuncOnInit(); // Call the user function
        else {
                LEDEnum led;
                if(controller == 0)
                        led = LED1;
                else if(controller == 1)
                        led = LED2;
                else if(controller == 2)
                        led = LED3;
                else
                        led = LED4;
                setLedOn(led, controller);
        }
}
