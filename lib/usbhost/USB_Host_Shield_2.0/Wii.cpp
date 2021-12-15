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

 IR camera support added by Allan Glover (adglover9.81@gmail.com) and Kristian Lauszus
 */

#include "Wii.h"
// To enable serial debugging see "settings.h"
//#define EXTRADEBUG // Uncomment to get even more debugging data
//#define PRINTREPORT // Uncomment to print the report send by the Wii controllers

const uint8_t WII_LEDS[] PROGMEM = {
        0x00, // OFF
        0x10, // LED1
        0x20, // LED2
        0x40, // LED3
        0x80, // LED4

        0x90, // LED5
        0xA0, // LED6
        0xC0, // LED7
        0xD0, // LED8
        0xE0, // LED9
        0xF0, // LED10
};

const uint32_t WII_BUTTONS[] PROGMEM = {
        0x00008, // UP
        0x00002, // RIGHT
        0x00004, // DOWN
        0x00001, // LEFT

        0, // Skip
        0x00010, // PLUS
        0x00100, // TWO
        0x00200, // ONE

        0x01000, // MINUS
        0x08000, // HOME
        0x10000, // Z
        0x20000, // C

        0x00400, // B
        0x00800, // A
};
const uint32_t WII_PROCONTROLLER_BUTTONS[] PROGMEM = {
        0x00100, // UP
        0x00080, // RIGHT
        0x00040, // DOWN
        0x00200, // LEFT

        0, // Skip
        0x00004, // PLUS
        0x20000, // L3
        0x10000, // R3

        0x00010, // MINUS
        0x00008, // HOME
        0, 0, // Skip

        0x04000, // B
        0x01000, // A
        0x00800, // X
        0x02000, // Y

        0x00020, // L
        0x00002, // R
        0x08000, // ZL
        0x00400, // ZR
};

WII::WII(BTD *p, bool pair) :
BluetoothService(p) // Pointer to USB class instance - mandatory
{
        pBtd->pairWithWii = pair;

        HIDBuffer[0] = 0xA2; // HID BT DATA_request (0xA0) | Report Type (Output 0x02)

        /* Set device cid for the control and intterrupt channelse - LSB */
        control_dcid[0] = 0x60; // 0x0060
        control_dcid[1] = 0x00;
        interrupt_dcid[0] = 0x61; // 0x0061
        interrupt_dcid[1] = 0x00;

        Reset();
}

void WII::Reset() {
        wiimoteConnected = false;
        nunchuckConnected = false;
        motionPlusConnected = false;
        activateNunchuck = false;
        motionValuesReset = false;
        activeConnection = false;
        motionPlusInside = false;
        pBtd->wiiUProController = false;
        wiiUProControllerConnected = false;
        wiiBalanceBoardConnected = false;
        l2cap_event_flag = 0; // Reset flags
        l2cap_state = L2CAP_WAIT;
}

void WII::disconnect() { // Use this void to disconnect any of the controllers
        if(!motionPlusInside) { // The old Wiimote needs a delay after the first command or it will automatically reconnect
                if(motionPlusConnected) {
#ifdef DEBUG_USB_HOST
                        Notify(PSTR("\r\nDeactivating Motion Plus"), 0x80);
#endif
                        initExtension1(); // This will disable the Motion Plus extension
                }
                timer = millis() + 1000; // We have to wait for the message before the rest of the channels can be deactivated
        } else
                timer = millis(); // Don't wait
        // First the HID interrupt channel has to be disconnected, then the HID control channel and finally the HCI connection
        pBtd->l2cap_disconnection_request(hci_handle, ++identifier, interrupt_scid, interrupt_dcid);
        Reset();
        l2cap_state = L2CAP_INTERRUPT_DISCONNECT;
}

void WII::ACLData(uint8_t* l2capinbuf) {
        if(!pBtd->l2capConnectionClaimed && pBtd->incomingWii && !wiimoteConnected && !activeConnection) {
                if(l2capinbuf[8] == L2CAP_CMD_CONNECTION_REQUEST) {
                        if((l2capinbuf[12] | (l2capinbuf[13] << 8)) == HID_CTRL_PSM) {
                                motionPlusInside = pBtd->motionPlusInside;
                                pBtd->incomingWii = false;
                                pBtd->l2capConnectionClaimed = true; // Claim that the incoming connection belongs to this service
                                activeConnection = true;
                                hci_handle = pBtd->hci_handle; // Store the HCI Handle for the connection
                                l2cap_state = L2CAP_WAIT;
                        }
                }
        }

        if(checkHciHandle(l2capinbuf, hci_handle)) { // acl_handle_ok
                if((l2capinbuf[6] | (l2capinbuf[7] << 8)) == 0x0001U) { // l2cap_control - Channel ID for ACL-U
                        if(l2capinbuf[8] == L2CAP_CMD_COMMAND_REJECT) {
#ifdef DEBUG_USB_HOST
                                Notify(PSTR("\r\nL2CAP Command Rejected - Reason: "), 0x80);
                                D_PrintHex<uint8_t > (l2capinbuf[13], 0x80);
                                Notify(PSTR(" "), 0x80);
                                D_PrintHex<uint8_t > (l2capinbuf[12], 0x80);
                                Notify(PSTR(" "), 0x80);
                                D_PrintHex<uint8_t > (l2capinbuf[17], 0x80);
                                Notify(PSTR(" "), 0x80);
                                D_PrintHex<uint8_t > (l2capinbuf[16], 0x80);
                                Notify(PSTR(" "), 0x80);
                                D_PrintHex<uint8_t > (l2capinbuf[15], 0x80);
                                Notify(PSTR(" "), 0x80);
                                D_PrintHex<uint8_t > (l2capinbuf[14], 0x80);
#endif
                        } else if(l2capinbuf[8] == L2CAP_CMD_CONNECTION_RESPONSE) {
                                if(((l2capinbuf[16] | (l2capinbuf[17] << 8)) == 0x0000) && ((l2capinbuf[18] | (l2capinbuf[19] << 8)) == SUCCESSFUL)) { // Success
                                        if(l2capinbuf[14] == control_dcid[0] && l2capinbuf[15] == control_dcid[1]) {
                                                //Notify(PSTR("\r\nHID Control Connection Complete"), 0x80);
                                                identifier = l2capinbuf[9];
                                                control_scid[0] = l2capinbuf[12];
                                                control_scid[1] = l2capinbuf[13];
                                                l2cap_set_flag(L2CAP_FLAG_CONTROL_CONNECTED);
                                        } else if(l2capinbuf[14] == interrupt_dcid[0] && l2capinbuf[15] == interrupt_dcid[1]) {
                                                //Notify(PSTR("\r\nHID Interrupt Connection Complete"), 0x80);
                                                identifier = l2capinbuf[9];
                                                interrupt_scid[0] = l2capinbuf[12];
                                                interrupt_scid[1] = l2capinbuf[13];
                                                l2cap_set_flag(L2CAP_FLAG_INTERRUPT_CONNECTED);
                                        }
                                }
                        } else if(l2capinbuf[8] == L2CAP_CMD_CONNECTION_REQUEST) {
#ifdef EXTRADEBUG
                                Notify(PSTR("\r\nL2CAP Connection Request - PSM: "), 0x80);
                                D_PrintHex<uint8_t > (l2capinbuf[13], 0x80);
                                Notify(PSTR(" "), 0x80);
                                D_PrintHex<uint8_t > (l2capinbuf[12], 0x80);
                                Notify(PSTR(" SCID: "), 0x80);
                                D_PrintHex<uint8_t > (l2capinbuf[15], 0x80);
                                Notify(PSTR(" "), 0x80);
                                D_PrintHex<uint8_t > (l2capinbuf[14], 0x80);
                                Notify(PSTR(" Identifier: "), 0x80);
                                D_PrintHex<uint8_t > (l2capinbuf[9], 0x80);
#endif
                                if((l2capinbuf[12] | (l2capinbuf[13] << 8)) == HID_CTRL_PSM) {
                                        identifier = l2capinbuf[9];
                                        control_scid[0] = l2capinbuf[14];
                                        control_scid[1] = l2capinbuf[15];
                                        l2cap_set_flag(L2CAP_FLAG_CONNECTION_CONTROL_REQUEST);
                                } else if((l2capinbuf[12] | (l2capinbuf[13] << 8)) == HID_INTR_PSM) {
                                        identifier = l2capinbuf[9];
                                        interrupt_scid[0] = l2capinbuf[14];
                                        interrupt_scid[1] = l2capinbuf[15];
                                        l2cap_set_flag(L2CAP_FLAG_CONNECTION_INTERRUPT_REQUEST);
                                }
                        } else if(l2capinbuf[8] == L2CAP_CMD_CONFIG_RESPONSE) {
                                if((l2capinbuf[16] | (l2capinbuf[17] << 8)) == 0x0000) { // Success
                                        if(l2capinbuf[12] == control_dcid[0] && l2capinbuf[13] == control_dcid[1]) {
                                                //Notify(PSTR("\r\nHID Control Configuration Complete"), 0x80);
                                                identifier = l2capinbuf[9];
                                                l2cap_set_flag(L2CAP_FLAG_CONFIG_CONTROL_SUCCESS);
                                        } else if(l2capinbuf[12] == interrupt_dcid[0] && l2capinbuf[13] == interrupt_dcid[1]) {
                                                //Notify(PSTR("\r\nHID Interrupt Configuration Complete"), 0x80);
                                                identifier = l2capinbuf[9];
                                                l2cap_set_flag(L2CAP_FLAG_CONFIG_INTERRUPT_SUCCESS);
                                        }
                                }
                        } else if(l2capinbuf[8] == L2CAP_CMD_CONFIG_REQUEST) {
                                if(l2capinbuf[12] == control_dcid[0] && l2capinbuf[13] == control_dcid[1]) {
                                        //Notify(PSTR("\r\nHID Control Configuration Request"), 0x80);
                                        pBtd->l2cap_config_response(hci_handle, l2capinbuf[9], control_scid);
                                } else if(l2capinbuf[12] == interrupt_dcid[0] && l2capinbuf[13] == interrupt_dcid[1]) {
                                        //Notify(PSTR("\r\nHID Interrupt Configuration Request"), 0x80);
                                        pBtd->l2cap_config_response(hci_handle, l2capinbuf[9], interrupt_scid);
                                }
                        } else if(l2capinbuf[8] == L2CAP_CMD_DISCONNECT_REQUEST) {
                                if(l2capinbuf[12] == control_dcid[0] && l2capinbuf[13] == control_dcid[1]) {
#ifdef DEBUG_USB_HOST
                                        Notify(PSTR("\r\nDisconnect Request: Control Channel"), 0x80);
#endif
                                        identifier = l2capinbuf[9];
                                        pBtd->l2cap_disconnection_response(hci_handle, identifier, control_dcid, control_scid);
                                        Reset();
                                } else if(l2capinbuf[12] == interrupt_dcid[0] && l2capinbuf[13] == interrupt_dcid[1]) {
#ifdef DEBUG_USB_HOST
                                        Notify(PSTR("\r\nDisconnect Request: Interrupt Channel"), 0x80);
#endif
                                        identifier = l2capinbuf[9];
                                        pBtd->l2cap_disconnection_response(hci_handle, identifier, interrupt_dcid, interrupt_scid);
                                        Reset();
                                }
                        } else if(l2capinbuf[8] == L2CAP_CMD_DISCONNECT_RESPONSE) {
                                if(l2capinbuf[12] == control_scid[0] && l2capinbuf[13] == control_scid[1]) {
                                        //Notify(PSTR("\r\nDisconnect Response: Control Channel"), 0x80);
                                        identifier = l2capinbuf[9];
                                        l2cap_set_flag(L2CAP_FLAG_DISCONNECT_CONTROL_RESPONSE);
                                } else if(l2capinbuf[12] == interrupt_scid[0] && l2capinbuf[13] == interrupt_scid[1]) {
                                        //Notify(PSTR("\r\nDisconnect Response: Interrupt Channel"), 0x80);
                                        identifier = l2capinbuf[9];
                                        l2cap_set_flag(L2CAP_FLAG_DISCONNECT_INTERRUPT_RESPONSE);
                                }
                        }
#ifdef EXTRADEBUG
                        else {
                                identifier = l2capinbuf[9];
                                Notify(PSTR("\r\nL2CAP Unknown Signaling Command: "), 0x80);
                                D_PrintHex<uint8_t > (l2capinbuf[8], 0x80);
                        }
#endif
                } else if(l2capinbuf[6] == interrupt_dcid[0] && l2capinbuf[7] == interrupt_dcid[1]) { // l2cap_interrupt
                        //Notify(PSTR("\r\nL2CAP Interrupt"), 0x80);
                        if(l2capinbuf[8] == 0xA1) { // HID_THDR_DATA_INPUT
                                if((l2capinbuf[9] >= 0x20 && l2capinbuf[9] <= 0x22) || (l2capinbuf[9] >= 0x30 && l2capinbuf[9] <= 0x37) || l2capinbuf[9] == 0x3e || l2capinbuf[9] == 0x3f) { // These reports include the buttons
                                        if((l2capinbuf[9] >= 0x20 && l2capinbuf[9] <= 0x22) || l2capinbuf[9] == 0x31 || l2capinbuf[9] == 0x33) // These reports have no extensions bytes
                                                ButtonState = (uint32_t)((l2capinbuf[10] & 0x1F) | ((uint16_t)(l2capinbuf[11] & 0x9F) << 8));
                                        else if(wiiUProControllerConnected)
                                                ButtonState = (uint32_t)(((~l2capinbuf[23]) & 0xFE) | ((uint16_t)(~l2capinbuf[24]) << 8) | ((uint32_t)((~l2capinbuf[25]) & 0x03) << 16));
                                        else if(motionPlusConnected) {
                                                if(l2capinbuf[20] & 0x02) // Only update the Wiimote buttons, since the extension bytes are from the Motion Plus
                                                        ButtonState = (uint32_t)((l2capinbuf[10] & 0x1F) | ((uint16_t)(l2capinbuf[11] & 0x9F) << 8) | ((uint32_t)(ButtonState & 0xFFFF0000)));
                                                else if(nunchuckConnected) // Update if it's a report from the Nunchuck
                                                        ButtonState = (uint32_t)((l2capinbuf[10] & 0x1F) | ((uint16_t)(l2capinbuf[11] & 0x9F) << 8) | ((uint32_t)((~l2capinbuf[20]) & 0x0C) << 14));
                                                //else if(classicControllerConnected) // Update if it's a report from the Classic Controller
                                        } else if(nunchuckConnected) // The Nunchuck is directly connected
                                                ButtonState = (uint32_t)((l2capinbuf[10] & 0x1F) | ((uint16_t)(l2capinbuf[11] & 0x9F) << 8) | ((uint32_t)((~l2capinbuf[20]) & 0x03) << 16));
                                                //else if(classicControllerConnected) // The Classic Controller is directly connected
                                        else if(!unknownExtensionConnected)
                                                ButtonState = (uint32_t)((l2capinbuf[10] & 0x1F) | ((uint16_t)(l2capinbuf[11] & 0x9F) << 8));
#ifdef PRINTREPORT
                                        Notify(PSTR("ButtonState: "), 0x80);
                                        D_PrintHex<uint32_t > (ButtonState, 0x80);
                                        Notify(PSTR("\r\n"), 0x80);
#endif
                                        if(ButtonState != OldButtonState) {
                                                ButtonClickState = ButtonState & ~OldButtonState; // Update click state variable
                                                OldButtonState = ButtonState;
                                        }
                                }
                                if(l2capinbuf[9] == 0x31 || l2capinbuf[9] == 0x33 || l2capinbuf[9] == 0x35 || l2capinbuf[9] == 0x37) { // Read the accelerometer
                                        accXwiimote = ((l2capinbuf[12] << 2) | (l2capinbuf[10] & 0x60 >> 5)) - 500;
                                        accYwiimote = ((l2capinbuf[13] << 2) | (l2capinbuf[11] & 0x20 >> 4)) - 500;
                                        accZwiimote = ((l2capinbuf[14] << 2) | (l2capinbuf[11] & 0x40 >> 5)) - 500;
                                }
                                switch(l2capinbuf[9]) {
                                        case 0x20: // Status Information - (a1) 20 BB BB LF 00 00 VV
#ifdef EXTRADEBUG
                                                Notify(PSTR("\r\nStatus report was received"), 0x80);
#endif
                                                wiiState = l2capinbuf[12]; // (0x01: Battery is nearly empty), (0x02:  An Extension Controller is connected), (0x04: Speaker enabled), (0x08: IR enabled), (0x10: LED1, 0x20: LED2, 0x40: LED3, 0x80: LED4)
                                                batteryLevel = l2capinbuf[15]; // Update battery level

                                                if(!checkBatteryLevel) { // If this is true it means that the user must have called getBatteryLevel()
                                                        if(l2capinbuf[12] & 0x02) { // Check if a extension is connected
#ifdef DEBUG_USB_HOST
                                                                if(!unknownExtensionConnected)
                                                                        Notify(PSTR("\r\nExtension connected"), 0x80);
#endif
                                                                unknownExtensionConnected = true;
#ifdef WIICAMERA
                                                                if(!isIRCameraEnabled()) // Don't activate the Motion Plus if we are trying to initialize the IR camera
#endif
                                                                        setReportMode(false, 0x35); // Also read the extension
                                                        } else {
#ifdef DEBUG_USB_HOST
                                                                Notify(PSTR("\r\nExtension disconnected"), 0x80);
#endif
                                                                if(motionPlusConnected) {
#ifdef DEBUG_USB_HOST
                                                                        Notify(PSTR(" - from Motion Plus"), 0x80);
#endif
                                                                        wii_clear_flag(WII_FLAG_NUNCHUCK_CONNECTED);
                                                                        if(!activateNunchuck) // If it's already trying to initialize the Nunchuck don't set it to false
                                                                                nunchuckConnected = false;
                                                                        //else if(classicControllerConnected)
                                                                } else if(nunchuckConnected) {
#ifdef DEBUG_USB_HOST
                                                                        Notify(PSTR(" - Nunchuck"), 0x80);
#endif
                                                                        nunchuckConnected = false; // It must be the Nunchuck controller then
                                                                        wii_clear_flag(WII_FLAG_NUNCHUCK_CONNECTED);
                                                                        onInit();
                                                                        setReportMode(false, 0x31); // If there is no extension connected we will read the buttons and accelerometer
                                                                } else
                                                                        setReportMode(false, 0x31); // If there is no extension connected we will read the buttons and accelerometer
                                                        }
                                                }
                                                else {
#ifdef EXTRADEBUG
                                                        Notify(PSTR("\r\nChecking battery level"), 0x80);
#endif
                                                        checkBatteryLevel = false; // Check for extensions by default
                                                }
#ifdef DEBUG_USB_HOST
                                                if(l2capinbuf[12] & 0x01)
                                                        Notify(PSTR("\r\nWARNING: Battery is nearly empty"), 0x80);
#endif

                                                break;
                                        case 0x21: // Read Memory Data
                                                if((l2capinbuf[12] & 0x0F) == 0) { // No error
                                                        uint8_t reportLength = (l2capinbuf[12] >> 4) + 1; // // Bit 4-7 is the length - 1
                                                        // See: http://wiibrew.org/wiki/Wiimote/Extension_Controllers
                                                        if(l2capinbuf[16] == 0x00 && l2capinbuf[17] == 0xA4 && l2capinbuf[18] == 0x20 && l2capinbuf[19] == 0x00 && l2capinbuf[20] == 0x00) {
#ifdef DEBUG_USB_HOST
                                                                Notify(PSTR("\r\nNunchuck connected"), 0x80);
#endif
                                                                wii_set_flag(WII_FLAG_NUNCHUCK_CONNECTED);
                                                        } else if(l2capinbuf[16] == 0x00 && (l2capinbuf[17] == 0xA6 || l2capinbuf[17] == 0xA4) && l2capinbuf[18] == 0x20 && l2capinbuf[19] == 0x00 && l2capinbuf[20] == 0x05) {
#ifdef DEBUG_USB_HOST
                                                                Notify(PSTR("\r\nMotion Plus connected"), 0x80);
#endif
                                                                wii_set_flag(WII_FLAG_MOTION_PLUS_CONNECTED);
                                                        } else if(l2capinbuf[16] == 0x00 && l2capinbuf[17] == 0xA4 && l2capinbuf[18] == 0x20 && l2capinbuf[19] == 0x04 && l2capinbuf[20] == 0x05) {
#ifdef DEBUG_USB_HOST
                                                                Notify(PSTR("\r\nMotion Plus activated in normal mode"), 0x80);
#endif
                                                                motionPlusConnected = true;
#ifdef WIICAMERA
                                                                if(!isIRCameraEnabled()) // Don't activate the Motion Plus if we are trying to initialize the IR camera
#endif
                                                                        setReportMode(false, 0x35); // Also read the extension
                                                        } else if(l2capinbuf[16] == 0x00 && l2capinbuf[17] == 0xA4 && l2capinbuf[18] == 0x20 && l2capinbuf[19] == 0x05 && l2capinbuf[20] == 0x05) {
#ifdef DEBUG_USB_HOST
                                                                Notify(PSTR("\r\nMotion Plus activated in Nunchuck pass-through mode"), 0x80);
#endif
                                                                activateNunchuck = false;
                                                                motionPlusConnected = true;
                                                                nunchuckConnected = true;
#ifdef WIICAMERA
                                                                if(!isIRCameraEnabled()) // Don't activate the Motion Plus if we are trying to initialize the IR camera
#endif
                                                                        setReportMode(false, 0x35); // Also read the extension
                                                        } else if(l2capinbuf[16] == 0x00 && l2capinbuf[17] == 0xA6 && l2capinbuf[18] == 0x20 && (l2capinbuf[19] == 0x00 || l2capinbuf[19] == 0x04 || l2capinbuf[19] == 0x05 || l2capinbuf[19] == 0x07) && l2capinbuf[20] == 0x05) {
#ifdef DEBUG_USB_HOST
                                                                Notify(PSTR("\r\nInactive Wii Motion Plus"), 0x80);
                                                                Notify(PSTR("\r\nPlease unplug the Motion Plus, disconnect the Wiimote and then replug the Motion Plus Extension"), 0x80);
#endif
                                                                stateCounter = 300; // Skip the rest in "WII_CHECK_MOTION_PLUS_STATE"
                                                        } else if(l2capinbuf[16] == 0x00 && l2capinbuf[17] == 0xA4 && l2capinbuf[18] == 0x20 && l2capinbuf[19] == 0x01 && l2capinbuf[20] == 0x20) {
#ifdef DEBUG_USB_HOST
                                                                Notify(PSTR("\r\nWii U Pro Controller connected"), 0x80);
#endif
                                                                wiiUProControllerConnected = true;
                                                        } else if(l2capinbuf[16] == 0x00 && l2capinbuf[17] == 0xA4 && l2capinbuf[18] == 0x20 && l2capinbuf[19] == 0x04 && l2capinbuf[20] == 0x02) {
#ifdef DEBUG_USB_HOST
                                                                Notify(PSTR("\r\nWii Balance Board connected"), 0x80);
#endif
                                                                setReportMode(false, 0x32); // Read the Wii Balance Board extension
                                                                wii_set_flag(WII_FLAG_CALIBRATE_BALANCE_BOARD);
                                                        }
                                                        // Wii Balance Board calibration reports (24 bits in total)
                                                        else if(l2capinbuf[13] == 0x00 && l2capinbuf[14] == 0x24 && reportLength == 16) { // First 16-bit
                                                                for(uint8_t i = 0; i < 2; i++) {
                                                                        for(uint8_t j = 0; j < 4; j++)
                                                                                wiiBalanceBoardCal[i][j] = l2capinbuf[16 + 8 * i + 2 * j] | l2capinbuf[15 + 8 * i + 2 * j] << 8;
                                                                }
                                                        } else if(l2capinbuf[13] == 0x00 && l2capinbuf[14] == 0x34 && reportLength == 8) { // Last 8-bit
                                                                for(uint8_t j = 0; j < 4; j++)
                                                                        wiiBalanceBoardCal[2][j] = l2capinbuf[16 + 2 * j] | l2capinbuf[15 + 2 * j] << 8;
#ifdef DEBUG_USB_HOST
                                                                Notify(PSTR("\r\nWii Balance Board calibration values read successfully"), 0x80);
#endif
                                                                wii_clear_flag(WII_FLAG_CALIBRATE_BALANCE_BOARD);
                                                                wiiBalanceBoardConnected = true;
                                                        }
#ifdef DEBUG_USB_HOST
                                                        else {
                                                                Notify(PSTR("\r\nUnknown Device: "), 0x80);
                                                                D_PrintHex<uint8_t > (l2capinbuf[13], 0x80);
                                                                D_PrintHex<uint8_t > (l2capinbuf[14], 0x80);
                                                                Notify(PSTR("\r\nData: "), 0x80);
                                                                for(uint8_t i = 0; i < reportLength; i++) {
                                                                        D_PrintHex<uint8_t > (l2capinbuf[15 + i], 0x80);
                                                                        Notify(PSTR(" "), 0x80);
                                                                }
                                                        }
#endif
                                                }
#ifdef EXTRADEBUG
                                                else {
                                                        Notify(PSTR("\r\nReport Error: "), 0x80);
                                                        D_PrintHex<uint8_t > (l2capinbuf[13], 0x80);
                                                        D_PrintHex<uint8_t > (l2capinbuf[14], 0x80);
                                                }
#endif
                                                break;
                                        case 0x22: // Acknowledge output report, return function result
#ifdef DEBUG_USB_HOST
                                                if(l2capinbuf[13] != 0x00) { // Check if there is an error
                                                        Notify(PSTR("\r\nCommand failed: "), 0x80);
                                                        D_PrintHex<uint8_t > (l2capinbuf[12], 0x80);
                                                }
#endif
                                                break;
                                        case 0x30: // Core buttons - (a1) 30 BB BB
                                                break;
                                        case 0x31: // Core Buttons and Accelerometer - (a1) 31 BB BB AA AA AA
                                                break;
                                        case 0x32: // Core Buttons with 8 Extension bytes - (a1) 32 BB BB EE EE EE EE EE EE EE EE
                                                // See: http://wiibrew.org/wiki/Wii_Balance_Board#Data_Format
                                                wiiBalanceBoardRaw[TopRight] = l2capinbuf[13] | l2capinbuf[12] << 8; // Top right
                                                wiiBalanceBoardRaw[BotRight] = l2capinbuf[15] | l2capinbuf[14] << 8; // Bottom right
                                                wiiBalanceBoardRaw[TopLeft] = l2capinbuf[17] | l2capinbuf[16] << 8; // Top left
                                                wiiBalanceBoardRaw[BotLeft] = l2capinbuf[19] | l2capinbuf[18] << 8; // Bottom left
                                                break;
                                        case 0x33: // Core Buttons with Accelerometer and 12 IR bytes - (a1) 33 BB BB AA AA AA II II II II II II II II II II II II
#ifdef WIICAMERA
                                                // Read the IR data
                                                IR_object_x1 = (l2capinbuf[15] | ((uint16_t)(l2capinbuf[17] & 0x30) << 4)); // x position
                                                IR_object_y1 = (l2capinbuf[16] | ((uint16_t)(l2capinbuf[17] & 0xC0) << 2)); // y position
                                                IR_object_s1 = (l2capinbuf[17] & 0x0F); // Size value, 0-15

                                                IR_object_x2 = (l2capinbuf[18] | ((uint16_t)(l2capinbuf[20] & 0x30) << 4));
                                                IR_object_y2 = (l2capinbuf[19] | ((uint16_t)(l2capinbuf[20] & 0xC0) << 2));
                                                IR_object_s2 = (l2capinbuf[20] & 0x0F);

                                                IR_object_x3 = (l2capinbuf[21] | ((uint16_t)(l2capinbuf[23] & 0x30) << 4));
                                                IR_object_y3 = (l2capinbuf[22] | ((uint16_t)(l2capinbuf[23] & 0xC0) << 2));
                                                IR_object_s3 = (l2capinbuf[23] & 0x0F);

                                                IR_object_x4 = (l2capinbuf[24] | ((uint16_t)(l2capinbuf[26] & 0x30) << 4));
                                                IR_object_y4 = (l2capinbuf[25] | ((uint16_t)(l2capinbuf[26] & 0xC0) << 2));
                                                IR_object_s4 = (l2capinbuf[26] & 0x0F);
#endif
                                                break;
                                        case 0x34: // Core Buttons with 19 Extension bytes - (a1) 34 BB BB EE EE EE EE EE EE EE EE EE EE EE EE EE EE EE EE EE EE EE
                                                break;
                                                /* 0x3e and 0x3f both give unknown report types when report mode is 0x3e or 0x3f with mode number 0x05 */
                                        case 0x3E: // Core Buttons with Accelerometer and 32 IR bytes
                                                // (a1) 31 BB BB AA AA AA II II II II II II II II II II II II II II II II II II II II II II II II II II II II II II II II
                                                // corresponds to output report mode 0x3e

                                                /**** for reading in full mode: DOES NOT WORK YET ****/
                                                /* When it works it will also have intensity and bounding box data */
                                                /*
                                                IR_object_x1 = (l2capinbuf[13] | ((uint16_t)(l2capinbuf[15] & 0x30) << 4));
                                                IR_object_y1 = (l2capinbuf[14] | ((uint16_t)(l2capinbuf[15] & 0xC0) << 2));
                                                IR_object_s1 = (l2capinbuf[15] & 0x0F);
                                                 */
                                                break;
                                        case 0x3F:
                                                /*
                                                IR_object_x1 = (l2capinbuf[13] | ((uint16_t)(l2capinbuf[15] & 0x30) << 4));
                                                IR_object_y1 = (l2capinbuf[14] | ((uint16_t)(l2capinbuf[15] & 0xC0) << 2));
                                                IR_object_s1 = (l2capinbuf[15] & 0x0F);
                                                 */
                                                break;
                                        case 0x35: // Core Buttons and Accelerometer with 16 Extension Bytes
                                                // (a1) 35 BB BB AA AA AA EE EE EE EE EE EE EE EE EE EE EE EE EE EE EE EE
#if 1 // Set this to 0 if you don't want to use an extension, this reduceds the size of the library a lot!
                                                if(motionPlusConnected) {
                                                        if(l2capinbuf[20] & 0x02) { // Check if it's a report from the Motion controller or the extension
                                                                if(motionValuesReset) { // We will only use the values when the gyro value has been set
                                                                        gyroYawRaw = ((l2capinbuf[15] | ((l2capinbuf[18] & 0xFC) << 6)) - gyroYawZero);
                                                                        gyroRollRaw = ((l2capinbuf[16] | ((l2capinbuf[19] & 0xFC) << 6)) - gyroRollZero);
                                                                        gyroPitchRaw = ((l2capinbuf[17] | ((l2capinbuf[20] & 0xFC) << 6)) - gyroPitchZero);

                                                                        yawGyroSpeed = (double)gyroYawRaw / ((double)gyroYawZero / yawGyroScale);
                                                                        rollGyroSpeed = -(double)gyroRollRaw / ((double)gyroRollZero / rollGyroScale); // We invert these values so they will fit the acc values
                                                                        pitchGyroSpeed = (double)gyroPitchRaw / ((double)gyroPitchZero / pitchGyroScale);

                                                                        /* The onboard gyro has two ranges for slow and fast mode */
                                                                        if(!(l2capinbuf[18] & 0x02)) // Check if fast mode is used
                                                                                yawGyroSpeed *= 4.545;
                                                                        if(!(l2capinbuf[18] & 0x01)) // Check if fast mode is used
                                                                                pitchGyroSpeed *= 4.545;
                                                                        if(!(l2capinbuf[19] & 0x02)) // Check if fast mode is used
                                                                                rollGyroSpeed *= 4.545;

                                                                        compPitch = (0.93 * (compPitch + (pitchGyroSpeed * (double)(micros() - timer) / 1000000)))+(0.07 * getWiimotePitch()); // Use a complimentary filter to calculate the angle
                                                                        compRoll = (0.93 * (compRoll + (rollGyroSpeed * (double)(micros() - timer) / 1000000)))+(0.07 * getWiimoteRoll());

                                                                        gyroYaw += (yawGyroSpeed * ((double)(micros() - timer) / 1000000));
                                                                        gyroRoll += (rollGyroSpeed * ((double)(micros() - timer) / 1000000));
                                                                        gyroPitch += (pitchGyroSpeed * ((double)(micros() - timer) / 1000000));
                                                                        timer = micros();
                                                                        /*
                                                                        // Uncomment these lines to tune the gyro scale variabels
                                                                        Notify(PSTR("\r\ngyroYaw: "), 0x80);
                                                                        Notify(gyroYaw, 0x80);
                                                                        Notify(PSTR("\tgyroRoll: "), 0x80);
                                                                        Notify(gyroRoll, 0x80);
                                                                        Notify(PSTR("\tgyroPitch: "), 0x80);
                                                                        Notify(gyroPitch, 0x80);
                                                                         */
                                                                        /*
                                                                        Notify(PSTR("\twiimoteRoll: "), 0x80);
                                                                        Notify(wiimoteRoll, 0x80);
                                                                        Notify(PSTR("\twiimotePitch: "), 0x80);
                                                                        Notify(wiimotePitch, 0x80);
                                                                         */
                                                                } else {
                                                                        if((micros() - timer) > 1000000) { // Loop for 1 sec before resetting the values
#ifdef DEBUG_USB_HOST
                                                                                Notify(PSTR("\r\nThe gyro values has been reset"), 0x80);
#endif
                                                                                gyroYawZero = (l2capinbuf[15] | ((l2capinbuf[18] & 0xFC) << 6));
                                                                                gyroRollZero = (l2capinbuf[16] | ((l2capinbuf[19] & 0xFC) << 6));
                                                                                gyroPitchZero = (l2capinbuf[17] | ((l2capinbuf[20] & 0xFC) << 6));

                                                                                rollGyroScale = 500; // You might need to adjust these
                                                                                pitchGyroScale = 400;
                                                                                yawGyroScale = 415;

                                                                                gyroYaw = 0;
                                                                                gyroRoll = 0;
                                                                                gyroPitch = 0;

                                                                                motionValuesReset = true;
                                                                                timer = micros();
                                                                        }
                                                                }
                                                        } else {
                                                                if(nunchuckConnected) {
                                                                        hatValues[HatX] = l2capinbuf[15];
                                                                        hatValues[HatY] = l2capinbuf[16];
                                                                        accXnunchuck = ((l2capinbuf[17] << 2) | (l2capinbuf[20] & 0x10 >> 3)) - 416;
                                                                        accYnunchuck = ((l2capinbuf[18] << 2) | (l2capinbuf[20] & 0x20 >> 4)) - 416;
                                                                        accZnunchuck = (((l2capinbuf[19] & 0xFE) << 2) | (l2capinbuf[20] & 0xC0 >> 5)) - 416;
                                                                }
                                                                //else if(classicControllerConnected) { }
                                                        }
                                                        if(l2capinbuf[19] & 0x01) {
                                                                if(!extensionConnected) {
                                                                        extensionConnected = true;
                                                                        unknownExtensionConnected = true;
#ifdef DEBUG_USB_HOST
                                                                        Notify(PSTR("\r\nExtension connected to Motion Plus"), 0x80);
#endif
                                                                }
                                                        } else {
                                                                if(extensionConnected && !unknownExtensionConnected) {
                                                                        extensionConnected = false;
                                                                        unknownExtensionConnected = true;
#ifdef DEBUG_USB_HOST
                                                                        Notify(PSTR("\r\nExtension disconnected from Motion Plus"), 0x80);
#endif
                                                                        nunchuckConnected = false; // There is no extension connected to the Motion Plus if this report is sent
                                                                }
                                                        }

                                                } else if(nunchuckConnected) {
                                                        hatValues[HatX] = l2capinbuf[15];
                                                        hatValues[HatY] = l2capinbuf[16];
                                                        accXnunchuck = ((l2capinbuf[17] << 2) | (l2capinbuf[20] & 0x0C >> 2)) - 416;
                                                        accYnunchuck = ((l2capinbuf[18] << 2) | (l2capinbuf[20] & 0x30 >> 4)) - 416;
                                                        accZnunchuck = ((l2capinbuf[19] << 2) | (l2capinbuf[20] & 0xC0 >> 6)) - 416;
                                                } else if(wiiUProControllerConnected) {
                                                        hatValues[LeftHatX] = (l2capinbuf[15] | l2capinbuf[16] << 8);
                                                        hatValues[RightHatX] = (l2capinbuf[17] | l2capinbuf[18] << 8);
                                                        hatValues[LeftHatY] = (l2capinbuf[19] | l2capinbuf[20] << 8);
                                                        hatValues[RightHatY] = (l2capinbuf[21] | l2capinbuf[22] << 8);
                                                }
#endif
                                                break;
#ifdef DEBUG_USB_HOST
                                        default:
                                                Notify(PSTR("\r\nUnknown Report type: "), 0x80);
                                                D_PrintHex<uint8_t > (l2capinbuf[9], 0x80);
                                                break;
#endif
                                }
                        }
                }
                L2CAP_task();
        }
}

void WII::L2CAP_task() {
        switch(l2cap_state) {
                        /* These states are used if the Wiimote is the host */
                case L2CAP_CONTROL_SUCCESS:
                        if(l2cap_check_flag(L2CAP_FLAG_CONFIG_CONTROL_SUCCESS)) {
#ifdef DEBUG_USB_HOST
                                Notify(PSTR("\r\nHID Control Successfully Configured"), 0x80);
#endif
                                l2cap_state = L2CAP_INTERRUPT_SETUP;
                        }
                        break;

                case L2CAP_INTERRUPT_SETUP:
                        if(l2cap_check_flag(L2CAP_FLAG_CONNECTION_INTERRUPT_REQUEST)) {
#ifdef DEBUG_USB_HOST
                                Notify(PSTR("\r\nHID Interrupt Incoming Connection Request"), 0x80);
#endif
                                pBtd->l2cap_connection_response(hci_handle, identifier, interrupt_dcid, interrupt_scid, PENDING);
                                delay(1);
                                pBtd->l2cap_connection_response(hci_handle, identifier, interrupt_dcid, interrupt_scid, SUCCESSFUL);
                                identifier++;
                                delay(1);
                                pBtd->l2cap_config_request(hci_handle, identifier, interrupt_scid);

                                l2cap_state = L2CAP_INTERRUPT_CONFIG_REQUEST;
                        }
                        break;

                        /* These states are used if the Arduino is the host */
                case L2CAP_CONTROL_CONNECT_REQUEST:
                        if(l2cap_check_flag(L2CAP_FLAG_CONTROL_CONNECTED)) {
#ifdef DEBUG_USB_HOST
                                Notify(PSTR("\r\nSend HID Control Config Request"), 0x80);
#endif
                                identifier++;
                                pBtd->l2cap_config_request(hci_handle, identifier, control_scid);
                                l2cap_state = L2CAP_CONTROL_CONFIG_REQUEST;
                        }
                        break;

                case L2CAP_CONTROL_CONFIG_REQUEST:
                        if(l2cap_check_flag(L2CAP_FLAG_CONFIG_CONTROL_SUCCESS)) {
#ifdef DEBUG_USB_HOST
                                Notify(PSTR("\r\nSend HID Interrupt Connection Request"), 0x80);
#endif
                                identifier++;
                                pBtd->l2cap_connection_request(hci_handle, identifier, interrupt_dcid, HID_INTR_PSM);
                                l2cap_state = L2CAP_INTERRUPT_CONNECT_REQUEST;
                        }
                        break;

                case L2CAP_INTERRUPT_CONNECT_REQUEST:
                        if(l2cap_check_flag(L2CAP_FLAG_INTERRUPT_CONNECTED)) {
#ifdef DEBUG_USB_HOST
                                Notify(PSTR("\r\nSend HID Interrupt Config Request"), 0x80);
#endif
                                identifier++;
                                pBtd->l2cap_config_request(hci_handle, identifier, interrupt_scid);
                                l2cap_state = L2CAP_INTERRUPT_CONFIG_REQUEST;
                        }
                        break;

                case L2CAP_INTERRUPT_CONFIG_REQUEST:
                        if(l2cap_check_flag(L2CAP_FLAG_CONFIG_INTERRUPT_SUCCESS)) { // Now the HID channels is established
#ifdef DEBUG_USB_HOST
                                Notify(PSTR("\r\nHID Channels Established"), 0x80);
#endif
                                pBtd->connectToWii = false;
                                pBtd->pairWithWii = false;
                                stateCounter = 0;
                                l2cap_state = WII_CHECK_MOTION_PLUS_STATE;
                        }
                        break;

                        /* The next states are in run() */

                case L2CAP_INTERRUPT_DISCONNECT:
                        if(l2cap_check_flag(L2CAP_FLAG_DISCONNECT_INTERRUPT_RESPONSE) && ((long)(millis() - timer) >= 0L)) {
#ifdef DEBUG_USB_HOST
                                Notify(PSTR("\r\nDisconnected Interrupt Channel"), 0x80);
#endif
                                identifier++;
                                pBtd->l2cap_disconnection_request(hci_handle, identifier, control_scid, control_dcid);
                                l2cap_state = L2CAP_CONTROL_DISCONNECT;
                        }
                        break;

                case L2CAP_CONTROL_DISCONNECT:
                        if(l2cap_check_flag(L2CAP_FLAG_DISCONNECT_CONTROL_RESPONSE)) {
#ifdef DEBUG_USB_HOST
                                Notify(PSTR("\r\nDisconnected Control Channel"), 0x80);
#endif
                                pBtd->hci_disconnect(hci_handle);
                                hci_handle = -1; // Reset handle
                                l2cap_event_flag = 0; // Reset flags
                                l2cap_state = L2CAP_WAIT;
                        }
                        break;
        }
}

void WII::Run() {
        if(l2cap_state == L2CAP_INTERRUPT_DISCONNECT && ((long)(millis() - timer) >= 0L))
                L2CAP_task(); // Call the rest of the disconnection routine after we have waited long enough

        switch(l2cap_state) {
                case L2CAP_WAIT:
                        if(pBtd->connectToWii && !pBtd->l2capConnectionClaimed && !wiimoteConnected && !activeConnection) {
                                pBtd->l2capConnectionClaimed = true;
                                activeConnection = true;
                                motionPlusInside = pBtd->motionPlusInside;
#ifdef DEBUG_USB_HOST
                                Notify(PSTR("\r\nSend HID Control Connection Request"), 0x80);
#endif
                                hci_handle = pBtd->hci_handle; // Store the HCI Handle for the connection
                                l2cap_event_flag = 0; // Reset flags
                                identifier = 0;
                                pBtd->l2cap_connection_request(hci_handle, identifier, control_dcid, HID_CTRL_PSM);
                                l2cap_state = L2CAP_CONTROL_CONNECT_REQUEST;
                        } else if(l2cap_check_flag(L2CAP_FLAG_CONNECTION_CONTROL_REQUEST)) {
#ifdef DEBUG_USB_HOST
                                Notify(PSTR("\r\nHID Control Incoming Connection Request"), 0x80);
#endif
                                pBtd->l2cap_connection_response(hci_handle, identifier, control_dcid, control_scid, PENDING);
                                delay(1);
                                pBtd->l2cap_connection_response(hci_handle, identifier, control_dcid, control_scid, SUCCESSFUL);
                                identifier++;
                                delay(1);
                                pBtd->l2cap_config_request(hci_handle, identifier, control_scid);
                                l2cap_state = L2CAP_CONTROL_SUCCESS;
                        }
                        break;

                case WII_CHECK_MOTION_PLUS_STATE:
#ifdef DEBUG_USB_HOST
                        if(stateCounter == 0) // Only print onnce
                                Notify(PSTR("\r\nChecking if a Motion Plus is connected"), 0x80);
#endif
                        stateCounter++;
                        if(stateCounter % 200 == 0)
                                checkMotionPresent(); // Check if there is a motion plus connected
                        if(wii_check_flag(WII_FLAG_MOTION_PLUS_CONNECTED)) {
                                stateCounter = 0;
                                l2cap_state = WII_INIT_MOTION_PLUS_STATE;
                                timer = micros();

                                if(unknownExtensionConnected) {
#ifdef DEBUG_USB_HOST
                                        Notify(PSTR("\r\nA extension is also connected"), 0x80);
#endif
                                        activateNunchuck = true; // For we will just set this to true as this the only extension supported so far
                                }

                        } else if(stateCounter == 601) { // We will try three times to check for the motion plus
#ifdef DEBUG_USB_HOST
                                Notify(PSTR("\r\nNo Motion Plus was detected"), 0x80);
#endif
                                stateCounter = 0;
                                l2cap_state = WII_CHECK_EXTENSION_STATE;
                        }
                        break;

                case WII_CHECK_EXTENSION_STATE: // This is used to check if there is anything plugged in to the extension port
#ifdef DEBUG_USB_HOST
                        if(stateCounter == 0) // Only print onnce
                                Notify(PSTR("\r\nChecking if there is any extension connected"), 0x80);
#endif
                        stateCounter++; // We use this counter as there has to be a short delay between the commands
                        if(stateCounter == 1)
                                statusRequest(); // See if a new device has connected
                        if(stateCounter == 100) {
                                if(unknownExtensionConnected) // Check if there is a extension is connected to the port
                                        initExtension1();
                                else
                                        stateCounter = 499;
                        } else if(stateCounter == 200)
                                initExtension2();
                        else if(stateCounter == 300) {
                                readExtensionType();
                                unknownExtensionConnected = false;
                        } else if(stateCounter == 400) {
                                if(wii_check_flag(WII_FLAG_CALIBRATE_BALANCE_BOARD)) {
#ifdef DEBUG_USB_HOST
                                        Notify(PSTR("\r\nReading Wii Balance Board calibration values"), 0x80);
#endif
                                        readWiiBalanceBoardCalibration();
                                } else
                                        stateCounter = 499;
                        } else if(stateCounter == 500) {
                                stateCounter = 0;
                                l2cap_state = TURN_ON_LED;
                        }
                        break;

                case WII_INIT_MOTION_PLUS_STATE:
                        stateCounter++;
                        if(stateCounter == 1)
                                initMotionPlus();
                        else if(stateCounter == 100)
                                activateMotionPlus();
                        else if(stateCounter == 200)
                                readExtensionType(); // Check if it has been activated
                        else if(stateCounter == 300) {
                                stateCounter = 0;
                                unknownExtensionConnected = false; // The motion plus will send a status report when it's activated, we will set this to false so it doesn't reinitialize the Motion Plus
                                l2cap_state = TURN_ON_LED;
                        }
                        break;

                case TURN_ON_LED:
                        if(wii_check_flag(WII_FLAG_NUNCHUCK_CONNECTED))
                                nunchuckConnected = true;
                        wiimoteConnected = true;
                        onInit();
                        l2cap_state = L2CAP_DONE;
                        break;

                case L2CAP_DONE:
                        if(unknownExtensionConnected) {
#ifdef DEBUG_USB_HOST
                                if(stateCounter == 0) // Only print once
                                        Notify(PSTR("\r\nChecking extension port"), 0x80);
#endif
                                stateCounter++; // We will use this counter as there has to be a short delay between the commands
                                if(stateCounter == 50)
                                        statusRequest();
                                else if(stateCounter == 100)
                                        initExtension1();
                                else if(stateCounter == 150)
                                        if((extensionConnected && motionPlusConnected) || (unknownExtensionConnected && !motionPlusConnected))
                                                initExtension2();
                                        else
                                                stateCounter = 299; // There is no extension connected
                                else if(stateCounter == 200)
                                        readExtensionType();
                                else if(stateCounter == 250) {
                                        if(wii_check_flag(WII_FLAG_NUNCHUCK_CONNECTED)) {
#ifdef DEBUG_USB_HOST
                                                Notify(PSTR("\r\nNunchuck was reconnected"), 0x80);
#endif
                                                activateNunchuck = true;
                                                nunchuckConnected = true;
                                        }
                                        if(!motionPlusConnected)
                                                stateCounter = 449;
                                } else if(stateCounter == 300) {
                                        if(motionPlusConnected) {
#ifdef DEBUG_USB_HOST
                                                Notify(PSTR("\r\nReactivating the Motion Plus"), 0x80);
#endif
                                                initMotionPlus();
                                        } else
                                                stateCounter = 449;
                                } else if(stateCounter == 350)
                                        activateMotionPlus();
                                else if(stateCounter == 400)
                                        readExtensionType(); // Check if it has been activated
                                else if(stateCounter == 450) {
                                        onInit();
                                        stateCounter = 0;
                                        unknownExtensionConnected = false;
                                }
                        } else
                                stateCounter = 0;
                        break;
        }
}

/************************************************************/
/*                    HID Commands                          */
/************************************************************/

void WII::HID_Command(uint8_t* data, uint8_t nbytes) {
        if(motionPlusInside)
                pBtd->L2CAP_Command(hci_handle, data, nbytes, interrupt_scid[0], interrupt_scid[1]); // It's the new Wiimote with the Motion Plus Inside or Wii U Pro controller
        else
                pBtd->L2CAP_Command(hci_handle, data, nbytes, control_scid[0], control_scid[1]);
}

void WII::setAllOff() {
        HIDBuffer[1] = 0x11;
        HIDBuffer[2] = 0x00;
        HID_Command(HIDBuffer, 3);
}

void WII::setRumbleOff() {
        HIDBuffer[1] = 0x11;
        HIDBuffer[2] &= ~0x01; // Bit 0 control the rumble
        HID_Command(HIDBuffer, 3);
}

void WII::setRumbleOn() {
        HIDBuffer[1] = 0x11;
        HIDBuffer[2] |= 0x01; // Bit 0 control the rumble
        HID_Command(HIDBuffer, 3);
}

void WII::setRumbleToggle() {
        HIDBuffer[1] = 0x11;
        HIDBuffer[2] ^= 0x01; // Bit 0 control the rumble
        HID_Command(HIDBuffer, 3);
}

void WII::setLedRaw(uint8_t value) {
        HIDBuffer[1] = 0x11;
        HIDBuffer[2] = value | (HIDBuffer[2] & 0x01); // Keep the rumble bit
        HID_Command(HIDBuffer, 3);
}

void WII::setLedOff(LEDEnum a) {
        HIDBuffer[1] = 0x11;
        HIDBuffer[2] &= ~(pgm_read_byte(&WII_LEDS[(uint8_t)a]));
        HID_Command(HIDBuffer, 3);
}

void WII::setLedOn(LEDEnum a) {
        if(a == OFF)
                setLedRaw(0);
        else {
                HIDBuffer[1] = 0x11;
                HIDBuffer[2] |= pgm_read_byte(&WII_LEDS[(uint8_t)a]);
                HID_Command(HIDBuffer, 3);
        }
}

void WII::setLedToggle(LEDEnum a) {
        HIDBuffer[1] = 0x11;
        HIDBuffer[2] ^= pgm_read_byte(&WII_LEDS[(uint8_t)a]);
        HID_Command(HIDBuffer, 3);
}

void WII::setLedStatus() {
        HIDBuffer[1] = 0x11;
        HIDBuffer[2] = (HIDBuffer[2] & 0x01); // Keep the rumble bit
        if(wiimoteConnected)
                HIDBuffer[2] |= 0x10; // If it's connected LED1 will light up
        if(motionPlusConnected)
                HIDBuffer[2] |= 0x20; // If it's connected LED2 will light up
        if(nunchuckConnected)
                HIDBuffer[2] |= 0x40; // If it's connected LED3 will light up

        HID_Command(HIDBuffer, 3);
}

uint8_t WII::getBatteryLevel() {
        checkBatteryLevel = true; // This is needed so the library knows that the status response is a response to this function
        statusRequest(); // This will update the battery level
        return batteryLevel;
};

void WII::setReportMode(bool continuous, uint8_t mode) {
        uint8_t cmd_buf[4];
        cmd_buf[0] = 0xA2; // HID BT DATA_request (0xA0) | Report Type (Output 0x02)
        cmd_buf[1] = 0x12;
        if(continuous)
                cmd_buf[2] = 0x04 | (HIDBuffer[2] & 0x01); // Keep the rumble bit
        else
                cmd_buf[2] = 0x00 | (HIDBuffer[2] & 0x01); // Keep the rumble bit
        cmd_buf[3] = mode;
        HID_Command(cmd_buf, 4);
}

void WII::statusRequest() {
        uint8_t cmd_buf[3];
        cmd_buf[0] = 0xA2; // HID BT DATA_request (0xA0) | Report Type (Output 0x02)
        cmd_buf[1] = 0x15;
        cmd_buf[2] = (HIDBuffer[2] & 0x01); // Keep the rumble bit
        HID_Command(cmd_buf, 3);
}

/************************************************************/
/*                    Memmory Commands                      */
/************************************************************/

void WII::writeData(uint32_t offset, uint8_t size, uint8_t* data) {
        uint8_t cmd_buf[23];
        cmd_buf[0] = 0xA2; // HID BT DATA_request (0xA0) | Report Type (Output 0x02)
        cmd_buf[1] = 0x16; // Write data
        cmd_buf[2] = 0x04 | (HIDBuffer[2] & 0x01); // Write to memory, clear bit 2 to write to EEPROM
        cmd_buf[3] = (uint8_t)((offset & 0xFF0000) >> 16);
        cmd_buf[4] = (uint8_t)((offset & 0xFF00) >> 8);
        cmd_buf[5] = (uint8_t)(offset & 0xFF);
        cmd_buf[6] = size;
        uint8_t i = 0;
        for(; i < size; i++)
                cmd_buf[7 + i] = data[i];
        for(; i < 16; i++) // Set the rest to zero
                cmd_buf[7 + i] = 0x00;
        HID_Command(cmd_buf, 23);
}

void WII::initExtension1() {
        uint8_t buf[1];
        buf[0] = 0x55;
        writeData(0xA400F0, 1, buf);
}

void WII::initExtension2() {
        uint8_t buf[1];
        buf[0] = 0x00;
        writeData(0xA400FB, 1, buf);
}

void WII::initMotionPlus() {
        uint8_t buf[1];
        buf[0] = 0x55;
        writeData(0xA600F0, 1, buf);
}

void WII::activateMotionPlus() {
        uint8_t buf[1];
        if(pBtd->wiiUProController) {
#ifdef DEBUG_USB_HOST
                Notify(PSTR("\r\nActivating Wii U Pro Controller"), 0x80);
#endif
                buf[0] = 0x00; // It seems like you can send anything but 0x04, 0x05, and 0x07
        } else if(activateNunchuck) {
#ifdef DEBUG_USB_HOST
                Notify(PSTR("\r\nActivating Motion Plus in pass-through mode"), 0x80);
#endif
                buf[0] = 0x05; // Activate nunchuck pass-through mode
        }//else if(classicControllerConnected && extensionConnected)
                //buf[0] = 0x07;
        else {
#ifdef DEBUG_USB_HOST
                Notify(PSTR("\r\nActivating Motion Plus in normal mode"), 0x80);
#endif
                buf[0] = 0x04; // Don't use any extension
        }
        writeData(0xA600FE, 1, buf);
}

void WII::readData(uint32_t offset, uint16_t size, bool EEPROM) {
        uint8_t cmd_buf[8];
        cmd_buf[0] = 0xA2; // HID BT DATA_request (0xA0) | Report Type (Output 0x02)
        cmd_buf[1] = 0x17; // Read data
        if(EEPROM)
                cmd_buf[2] = 0x00 | (HIDBuffer[2] & 0x01); // Read from EEPROM
        else
                cmd_buf[2] = 0x04 | (HIDBuffer[2] & 0x01); // Read from memory
        cmd_buf[3] = (uint8_t)((offset & 0xFF0000) >> 16);
        cmd_buf[4] = (uint8_t)((offset & 0xFF00) >> 8);
        cmd_buf[5] = (uint8_t)(offset & 0xFF);
        cmd_buf[6] = (uint8_t)((size & 0xFF00) >> 8);
        cmd_buf[7] = (uint8_t)(size & 0xFF);

        HID_Command(cmd_buf, 8);
}

void WII::readExtensionType() {
        readData(0xA400FA, 6, false);
}

void WII::readCalData() {
        readData(0x0016, 8, true);
}

void WII::checkMotionPresent() {
        readData(0xA600FA, 6, false);
}

void WII::readWiiBalanceBoardCalibration() {
        readData(0xA40024, 24, false);
}

/************************************************************/
/*                    WII Commands                          */
/************************************************************/

bool WII::getButtonPress(ButtonEnum b) { // Return true when a button is pressed
        if(wiiUProControllerConnected)
                return (ButtonState & pgm_read_dword(&WII_PROCONTROLLER_BUTTONS[(uint8_t)b]));
        else
                return (ButtonState & pgm_read_dword(&WII_BUTTONS[(uint8_t)b]));
}

bool WII::getButtonClick(ButtonEnum b) { // Only return true when a button is clicked
        uint32_t button;
        if(wiiUProControllerConnected)
                button = pgm_read_dword(&WII_PROCONTROLLER_BUTTONS[(uint8_t)b]);
        else
                button = pgm_read_dword(&WII_BUTTONS[(uint8_t)b]);
        bool click = (ButtonClickState & button);
        ButtonClickState &= ~button; // clear "click" event
        return click;
}

uint8_t WII::getAnalogHat(HatEnum a) {
        if(!nunchuckConnected)
                return 127; // Return center position
        else {
                uint8_t output = hatValues[(uint8_t)a];
                if(output == 0xFF || output == 0x00) // The joystick will only read 255 or 0 when the cable is unplugged or initializing, so we will just return the center position
                        return 127;
                else
                        return output;
        }
}

uint16_t WII::getAnalogHat(AnalogHatEnum a) {
        if(!wiiUProControllerConnected)
                return 2000;
        else {
                uint16_t output = hatValues[(uint8_t)a];
                if(output == 0x00) // The joystick will only read 0 when it is first initializing, so we will just return the center position
                        return 2000;
                else
                        return output;
        }
}

void WII::onInit() {
        if(pFuncOnInit)
                pFuncOnInit(); // Call the user function
        else
                setLedStatus();
}

/************************************************************/
/*                 Wii Balance Board Commands               */
/************************************************************/

float WII::getWeight(BalanceBoardEnum pos) {
        // Use interpolating between two points - based on: https://github.com/skorokithakis/gr8w8upd8m8/blob/master/gr8w8upd8m8.py
        // wiiBalanceBoardCal[pos][0] is calibration values for 0 kg
        // wiiBalanceBoardCal[pos][1] is calibration values for 17 kg
        // wiiBalanceBoardCal[pos][2] is calibration values for 34 kg
        if(wiiBalanceBoardRaw[pos] < wiiBalanceBoardCal[0][pos])
            return 0.0f; // Below 0 kg
        else if(wiiBalanceBoardRaw[pos] < wiiBalanceBoardCal[1][pos]) // Between 0 and 17 kg
            return 17.0f * (float)(wiiBalanceBoardRaw[pos] - wiiBalanceBoardCal[0][pos]) / (float)(wiiBalanceBoardCal[1][pos] - wiiBalanceBoardCal[0][pos]);
        else // More than 17 kg
            return 17.0f + 17.0f * (float)(wiiBalanceBoardRaw[pos] - wiiBalanceBoardCal[1][pos]) / (float)(wiiBalanceBoardCal[2][pos] - wiiBalanceBoardCal[1][pos]);
};

float WII::getTotalWeight() {
        return getWeight(TopRight) + getWeight(BotRight) + getWeight(TopLeft) + getWeight(BotLeft);
};

/************************************************************/
/*       The following functions are for the IR camera      */
/************************************************************/

#ifdef WIICAMERA

void WII::IRinitialize() { // Turns on and initialises the IR camera

        enableIRCamera1();
#ifdef DEBUG_USB_HOST
        Notify(PSTR("\r\nEnable IR Camera1 Complete"), 0x80);
#endif
        delay(80);

        enableIRCamera2();
#ifdef DEBUG_USB_HOST
        Notify(PSTR("\r\nEnable IR Camera2 Complete"), 0x80);
#endif
        delay(80);

        write0x08Value();
#ifdef DEBUG_USB_HOST
        Notify(PSTR("\r\nWrote hex number 0x08"), 0x80);
#endif
        delay(80);

        writeSensitivityBlock1();
#ifdef DEBUG_USB_HOST
        Notify(PSTR("\r\nWrote Sensitivity Block 1"), 0x80);
#endif
        delay(80);

        writeSensitivityBlock2();
#ifdef DEBUG_USB_HOST
        Notify(PSTR("\r\nWrote Sensitivity Block 2"), 0x80);
#endif
        delay(80);

        uint8_t mode_num = 0x03;
        setWiiModeNumber(mode_num); // Change input for whatever mode you want i.e. 0x01, 0x03, or 0x05
#ifdef DEBUG_USB_HOST
        Notify(PSTR("\r\nSet Wii Mode Number To 0x"), 0x80);
        D_PrintHex<uint8_t > (mode_num, 0x80);
#endif
        delay(80);

        write0x08Value();
#ifdef DEBUG_USB_HOST
        Notify(PSTR("\r\nWrote Hex Number 0x08"), 0x80);
#endif
        delay(80);

        setReportMode(false, 0x33);
        //setReportMode(false, 0x3f); // For full reporting mode, doesn't work yet
#ifdef DEBUG_USB_HOST
        Notify(PSTR("\r\nSet Report Mode to 0x33"), 0x80);
#endif
        delay(80);

        statusRequest(); // Used to update wiiState - call isIRCameraEnabled() afterwards to check if it actually worked
#ifdef DEBUG_USB_HOST
        Notify(PSTR("\r\nIR Initialized"), 0x80);
#endif
}

void WII::enableIRCamera1() {
        uint8_t cmd_buf[3];
        cmd_buf[0] = 0xA2; // HID BT DATA_request (0xA0) | Report Type (Output 0x02)
        cmd_buf[1] = 0x13; // Output report 13
        cmd_buf[2] = 0x04 | (HIDBuffer[2] & 0x01); // Keep the rumble bit and sets bit 2
        HID_Command(cmd_buf, 3);
}

void WII::enableIRCamera2() {
        uint8_t cmd_buf[3];
        cmd_buf[0] = 0xA2; // HID BT DATA_request (0xA0) | Report Type (Output 0x02)
        cmd_buf[1] = 0x1A; // Output report 1A
        cmd_buf[2] = 0x04 | (HIDBuffer[2] & 0x01); // Keep the rumble bit and sets bit 2
        HID_Command(cmd_buf, 3);
}

void WII::writeSensitivityBlock1() {
        uint8_t buf[9];
        buf[0] = 0x00;
        buf[1] = 0x00;
        buf[2] = 0x00;
        buf[3] = 0x00;
        buf[4] = 0x00;
        buf[5] = 0x00;
        buf[6] = 0x90;
        buf[7] = 0x00;
        buf[8] = 0x41;

        writeData(0xB00000, 9, buf);
}

void WII::writeSensitivityBlock2() {
        uint8_t buf[2];
        buf[0] = 0x40;
        buf[1] = 0x00;

        writeData(0xB0001A, 2, buf);
}

void WII::write0x08Value() {
        uint8_t cmd = 0x08;
        writeData(0xb00030, 1, &cmd);
}

void WII::setWiiModeNumber(uint8_t mode_number) { // mode_number in hex i.e. 0x03 for extended mode
        writeData(0xb00033, 1, &mode_number);
}
#endif
