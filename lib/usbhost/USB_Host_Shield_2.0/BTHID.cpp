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

#include "BTHID.h"
// To enable serial debugging see "settings.h"
//#define EXTRADEBUG // Uncomment to get even more debugging data
//#define PRINTREPORT // Uncomment to print the report send by the HID device

BTHID::BTHID(BTD *p, bool pair, const char *pin) :
BluetoothService(p), // Pointer to USB class instance - mandatory
protocolMode(HID_BOOT_PROTOCOL) {
        for(uint8_t i = 0; i < NUM_PARSERS; i++)
                pRptParser[i] = NULL;

        pBtd->pairWithHIDDevice = pair;
        pBtd->btdPin = pin;

        /* Set device cid for the control and intterrupt channelse - LSB */
        control_dcid[0] = 0x70; // 0x0070
        control_dcid[1] = 0x00;
        interrupt_dcid[0] = 0x71; // 0x0071
        interrupt_dcid[1] = 0x00;

        Reset();
}

void BTHID::Reset() {
        connected = false;
        activeConnection = false;
        l2cap_event_flag = 0; // Reset flags
        l2cap_state = L2CAP_WAIT;
        ResetBTHID();
}

void BTHID::disconnect() { // Use this void to disconnect the device
        // First the HID interrupt channel has to be disconnected, then the HID control channel and finally the HCI connection
        pBtd->l2cap_disconnection_request(hci_handle, ++identifier, interrupt_scid, interrupt_dcid);
        Reset();
        l2cap_state = L2CAP_INTERRUPT_DISCONNECT;
}

void BTHID::ACLData(uint8_t* l2capinbuf) {
        if(!pBtd->l2capConnectionClaimed && pBtd->incomingHIDDevice && !connected && !activeConnection) {
                if(l2capinbuf[8] == L2CAP_CMD_CONNECTION_REQUEST) {
                        if((l2capinbuf[12] | (l2capinbuf[13] << 8)) == HID_CTRL_PSM) {
                                pBtd->incomingHIDDevice = false;
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
#ifdef PRINTREPORT
                        Notify(PSTR("\r\nL2CAP Interrupt: "), 0x80);
                        for(uint16_t i = 0; i < ((uint16_t)l2capinbuf[5] << 8 | l2capinbuf[4]); i++) {
                                D_PrintHex<uint8_t > (l2capinbuf[i + 8], 0x80);
                                Notify(PSTR(" "), 0x80);
                        }
#endif
                        if(l2capinbuf[8] == 0xA1) { // HID_THDR_DATA_INPUT
                                uint16_t length = ((uint16_t)l2capinbuf[5] << 8 | l2capinbuf[4]);
                                ParseBTHIDData((uint8_t)(length - 1), &l2capinbuf[9]);

                                switch(l2capinbuf[9]) {
                                        case 0x01: // Keyboard or Joystick events
                                                if(pRptParser[KEYBOARD_PARSER_ID])
                                                        pRptParser[KEYBOARD_PARSER_ID]->Parse(reinterpret_cast<HID *>(this), 0, (uint8_t)(length - 2), &l2capinbuf[10]); // Use reinterpret_cast again to extract the instance
                                                break;

                                        case 0x02: // Mouse events
                                                if(pRptParser[MOUSE_PARSER_ID])
                                                        pRptParser[MOUSE_PARSER_ID]->Parse(reinterpret_cast<HID *>(this), 0, (uint8_t)(length - 2), &l2capinbuf[10]); // Use reinterpret_cast again to extract the instance
                                                break;
#ifdef EXTRADEBUG
                                        default:
                                                Notify(PSTR("\r\nUnknown Report type: "), 0x80);
                                                D_PrintHex<uint8_t > (l2capinbuf[9], 0x80);
                                                break;
#endif
                                }
                        }
                } else if(l2capinbuf[6] == control_dcid[0] && l2capinbuf[7] == control_dcid[1]) { // l2cap_control
#ifdef PRINTREPORT
                        Notify(PSTR("\r\nL2CAP Control: "), 0x80);
                        for(uint16_t i = 0; i < ((uint16_t)l2capinbuf[5] << 8 | l2capinbuf[4]); i++) {
                                D_PrintHex<uint8_t > (l2capinbuf[i + 8], 0x80);
                                Notify(PSTR(" "), 0x80);
                        }
#endif
                }
#ifdef EXTRADEBUG
                else {
                        Notify(PSTR("\r\nUnsupported L2CAP Data - Channel ID: "), 0x80);
                        D_PrintHex<uint8_t > (l2capinbuf[7], 0x80);
                        Notify(PSTR(" "), 0x80);
                        D_PrintHex<uint8_t > (l2capinbuf[6], 0x80);

                        Notify(PSTR("\r\nData: "), 0x80);
                        Notify(PSTR("\r\n"), 0x80);
                        for(uint16_t i = 0; i < ((uint16_t)l2capinbuf[5] << 8 | l2capinbuf[4]); i++) {
                                D_PrintHex<uint8_t > (l2capinbuf[i + 8], 0x80);
                                Notify(PSTR(" "), 0x80);
                        }
                }
#endif
                L2CAP_task();
        }
}

void BTHID::L2CAP_task() {
        switch(l2cap_state) {
                        /* These states are used if the HID device is the host */
                case L2CAP_CONTROL_SUCCESS:
                        if(l2cap_check_flag(L2CAP_FLAG_CONFIG_CONTROL_SUCCESS)) {
#ifdef DEBUG_USB_HOST
                                Notify(PSTR("\r\nHID Control Successfully Configured"), 0x80);
#endif
                                setProtocol(); // Set protocol before establishing HID interrupt channel
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
                                setProtocol(); // Set protocol before establishing HID interrupt channel
                                delay(1); // Short delay between commands - just to be sure
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
                                pBtd->connectToHIDDevice = false;
                                pBtd->pairWithHIDDevice = false;
                                connected = true;
                                onInit();
                                l2cap_state = L2CAP_DONE;
                        }
                        break;

                case L2CAP_DONE:
                        break;

                case L2CAP_INTERRUPT_DISCONNECT:
                        if(l2cap_check_flag(L2CAP_FLAG_DISCONNECT_INTERRUPT_RESPONSE)) {
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

void BTHID::Run() {
        switch(l2cap_state) {
                case L2CAP_WAIT:
                        if(pBtd->connectToHIDDevice && !pBtd->l2capConnectionClaimed && !connected && !activeConnection) {
                                pBtd->l2capConnectionClaimed = true;
                                activeConnection = true;
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
        }
}

/************************************************************/
/*                    HID Commands                          */

/************************************************************/
void BTHID::setProtocol() {
#ifdef DEBUG_USB_HOST
        Notify(PSTR("\r\nSet protocol mode: "), 0x80);
        D_PrintHex<uint8_t > (protocolMode, 0x80);
#endif
        if (protocolMode != HID_BOOT_PROTOCOL && protocolMode != HID_RPT_PROTOCOL) {
#ifdef DEBUG_USB_HOST
                Notify(PSTR("\r\nNot a valid protocol mode. Using Boot protocol instead."), 0x80);
#endif
                protocolMode = HID_BOOT_PROTOCOL; // Use Boot Protocol by default
        }
        uint8_t command = 0x70 | protocolMode; // Set Protocol, see Bluetooth HID specs page 33
        pBtd->L2CAP_Command(hci_handle, &command, 1, control_scid[0], control_scid[1]);
}

void BTHID::setLeds(uint8_t data) {
        uint8_t buf[3];
        buf[0] = 0xA2; // HID BT DATA_request (0xA0) | Report Type (Output 0x02)
        buf[1] = 0x01; // Report ID
        buf[2] = data;
        pBtd->L2CAP_Command(hci_handle, buf, 3, interrupt_scid[0], interrupt_scid[1]);
}
