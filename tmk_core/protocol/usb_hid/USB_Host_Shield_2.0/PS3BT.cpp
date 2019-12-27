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
 */

#include "PS3BT.h"
// To enable serial debugging see "settings.h"
//#define EXTRADEBUG // Uncomment to get even more debugging data
//#define PRINTREPORT // Uncomment to print the report send by the PS3 Controllers

PS3BT::PS3BT(BTD *p, uint8_t btadr5, uint8_t btadr4, uint8_t btadr3, uint8_t btadr2, uint8_t btadr1, uint8_t btadr0) :
BluetoothService(p) // Pointer to USB class instance - mandatory
{
        pBtd->my_bdaddr[5] = btadr5; // Change to your dongle's Bluetooth address instead
        pBtd->my_bdaddr[4] = btadr4;
        pBtd->my_bdaddr[3] = btadr3;
        pBtd->my_bdaddr[2] = btadr2;
        pBtd->my_bdaddr[1] = btadr1;
        pBtd->my_bdaddr[0] = btadr0;

        HIDBuffer[0] = 0x52; // HID BT Set_report (0x50) | Report Type (Output 0x02)
        HIDBuffer[1] = 0x01; // Report ID

        // Needed for PS3 Move Controller commands to work via bluetooth
        HIDMoveBuffer[0] = 0xA2; // HID BT DATA_request (0xA0) | Report Type (Output 0x02)
        HIDMoveBuffer[1] = 0x02; // Report ID

        /* Set device cid for the control and intterrupt channelse - LSB */
        control_dcid[0] = 0x40; // 0x0040
        control_dcid[1] = 0x00;
        interrupt_dcid[0] = 0x41; // 0x0041
        interrupt_dcid[1] = 0x00;

        Reset();
}

bool PS3BT::getButtonPress(ButtonEnum b) {
        return (ButtonState & pgm_read_dword(&PS3_BUTTONS[(uint8_t)b]));
}

bool PS3BT::getButtonClick(ButtonEnum b) {
        uint32_t button = pgm_read_dword(&PS3_BUTTONS[(uint8_t)b]);
        bool click = (ButtonClickState & button);
        ButtonClickState &= ~button; // Clear "click" event
        return click;
}

uint8_t PS3BT::getAnalogButton(ButtonEnum a) {
        return (uint8_t)(l2capinbuf[pgm_read_byte(&PS3_ANALOG_BUTTONS[(uint8_t)a])]);
}

uint8_t PS3BT::getAnalogHat(AnalogHatEnum a) {
        return (uint8_t)(l2capinbuf[(uint8_t)a + 15]);
}

int16_t PS3BT::getSensor(SensorEnum a) {
        if(PS3Connected) {
                if(a == aX || a == aY || a == aZ || a == gZ)
                        return ((l2capinbuf[(uint16_t)a] << 8) | l2capinbuf[(uint16_t)a + 1]);
                else
                        return 0;
        } else if(PS3MoveConnected) {
                if(a == mXmove || a == mYmove) // These are all 12-bits long
                        return (((l2capinbuf[(uint16_t)a] & 0x0F) << 8) | (l2capinbuf[(uint16_t)a + 1]));
                else if(a == mZmove || a == tempMove) // The tempearature is also 12 bits long
                        return ((l2capinbuf[(uint16_t)a] << 4) | ((l2capinbuf[(uint16_t)a + 1] & 0xF0) >> 4));
                else // aXmove, aYmove, aZmove, gXmove, gYmove and gZmove
                        return (l2capinbuf[(uint16_t)a] | (l2capinbuf[(uint16_t)a + 1] << 8));
        } else
                return 0;
}

double PS3BT::getAngle(AngleEnum a) {
        double accXval, accYval, accZval;

        if(PS3Connected) {
                // Data for the Kionix KXPC4 used in the DualShock 3
                const double zeroG = 511.5; // 1.65/3.3*1023 (1.65V)
                accXval = -((double)getSensor(aX) - zeroG);
                accYval = -((double)getSensor(aY) - zeroG);
                accZval = -((double)getSensor(aZ) - zeroG);
        } else if(PS3MoveConnected) {
                // It's a Kionix KXSC4 inside the Motion controller
                const uint16_t zeroG = 0x8000;
                accXval = -(int16_t)(getSensor(aXmove) - zeroG);
                accYval = (int16_t)(getSensor(aYmove) - zeroG);
                accZval = (int16_t)(getSensor(aZmove) - zeroG);
        } else
                return 0;

        // Convert to 360 degrees resolution
        // atan2 outputs the value of -π to π (radians)
        // We are then converting it to 0 to 2π and then to degrees
        if(a == Pitch)
                return (atan2(accYval, accZval) + PI) * RAD_TO_DEG;
        else
                return (atan2(accXval, accZval) + PI) * RAD_TO_DEG;
}

double PS3BT::get9DOFValues(SensorEnum a) { // Thanks to Manfred Piendl
        if(!PS3MoveConnected)
                return 0;
        int16_t value = getSensor(a);
        if(a == mXmove || a == mYmove || a == mZmove) {
                if(value > 2047)
                        value -= 0x1000;
                return (double)value / 3.2; // unit: muT = 10^(-6) Tesla
        } else if(a == aXmove || a == aYmove || a == aZmove) {
                if(value < 0)
                        value += 0x8000;
                else
                        value -= 0x8000;
                return (double)value / 442.0; // unit: m/(s^2)
        } else if(a == gXmove || a == gYmove || a == gZmove) {
                if(value < 0)
                        value += 0x8000;
                else
                        value -= 0x8000;
                if(a == gXmove)
                        return (double)value / 11.6; // unit: deg/s
                else if(a == gYmove)
                        return (double)value / 11.2; // unit: deg/s
                else // gZmove
                        return (double)value / 9.6; // unit: deg/s
        } else
                return 0;
}

String PS3BT::getTemperature() {
        if(PS3MoveConnected) {
                int16_t input = getSensor(tempMove);

                String output = String(input / 100);
                output += ".";
                if(input % 100 < 10)
                        output += "0";
                output += String(input % 100);

                return output;
        } else
                return "Error";
}

bool PS3BT::getStatus(StatusEnum c) {
        return (l2capinbuf[(uint16_t)c >> 8] == ((uint8_t)c & 0xff));
}

void PS3BT::printStatusString() {
        char statusOutput[100]; // Max string length plus null character
        if(PS3Connected || PS3NavigationConnected) {
                strcpy_P(statusOutput, PSTR("ConnectionStatus: "));

                if(getStatus(Plugged)) strcat_P(statusOutput, PSTR("Plugged"));
                else if(getStatus(Unplugged)) strcat_P(statusOutput, PSTR("Unplugged"));
                else strcat_P(statusOutput, PSTR("Error"));

                strcat_P(statusOutput, PSTR(" - PowerRating: "));

                if(getStatus(Charging)) strcat_P(statusOutput, PSTR("Charging"));
                else if(getStatus(NotCharging)) strcat_P(statusOutput, PSTR("Not Charging"));
                else if(getStatus(Shutdown)) strcat_P(statusOutput, PSTR("Shutdown"));
                else if(getStatus(Dying)) strcat_P(statusOutput, PSTR("Dying"));
                else if(getStatus(Low)) strcat_P(statusOutput, PSTR("Low"));
                else if(getStatus(High)) strcat_P(statusOutput, PSTR("High"));
                else if(getStatus(Full)) strcat_P(statusOutput, PSTR("Full"));
                else strcat_P(statusOutput, PSTR("Error"));

                strcat_P(statusOutput, PSTR(" - WirelessStatus: "));

                if(getStatus(CableRumble)) strcat_P(statusOutput, PSTR("Cable - Rumble is on"));
                else if(getStatus(Cable)) strcat_P(statusOutput, PSTR("Cable - Rumble is off"));
                else if(getStatus(BluetoothRumble)) strcat_P(statusOutput, PSTR("Bluetooth - Rumble is on"));
                else if(getStatus(Bluetooth)) strcat_P(statusOutput, PSTR("Bluetooth - Rumble is off"));
                else strcat_P(statusOutput, PSTR("Error"));
        } else if(PS3MoveConnected) {
                strcpy_P(statusOutput, PSTR("PowerRating: "));

                if(getStatus(MoveCharging)) strcat_P(statusOutput, PSTR("Charging"));
                else if(getStatus(MoveNotCharging)) strcat_P(statusOutput, PSTR("Not Charging"));
                else if(getStatus(MoveShutdown)) strcat_P(statusOutput, PSTR("Shutdown"));
                else if(getStatus(MoveDying)) strcat_P(statusOutput, PSTR("Dying"));
                else if(getStatus(MoveLow)) strcat_P(statusOutput, PSTR("Low"));
                else if(getStatus(MoveHigh)) strcat_P(statusOutput, PSTR("High"));
                else if(getStatus(MoveFull)) strcat_P(statusOutput, PSTR("Full"));
                else strcat_P(statusOutput, PSTR("Error"));
        } else
                strcpy_P(statusOutput, PSTR("Error"));

        USB_HOST_SERIAL.write(statusOutput);
}

void PS3BT::Reset() {
        PS3Connected = false;
        PS3MoveConnected = false;
        PS3NavigationConnected = false;
        activeConnection = false;
        l2cap_event_flag = 0; // Reset flags
        l2cap_state = L2CAP_WAIT;

        // Needed for PS3 Dualshock Controller commands to work via Bluetooth
        for(uint8_t i = 0; i < PS3_REPORT_BUFFER_SIZE; i++)
                HIDBuffer[i + 2] = pgm_read_byte(&PS3_REPORT_BUFFER[i]); // First two bytes reserved for report type and ID
}

void PS3BT::disconnect() { // Use this void to disconnect any of the controllers
        // First the HID interrupt channel has to be disconnected, then the HID control channel and finally the HCI connection
        pBtd->l2cap_disconnection_request(hci_handle, ++identifier, interrupt_scid, interrupt_dcid);
        Reset();
        l2cap_state = L2CAP_INTERRUPT_DISCONNECT;
}

void PS3BT::ACLData(uint8_t* ACLData) {
        if(!pBtd->l2capConnectionClaimed && !PS3Connected && !PS3MoveConnected && !PS3NavigationConnected && !activeConnection && !pBtd->connectToWii && !pBtd->incomingWii && !pBtd->pairWithWii) {
                if(ACLData[8] == L2CAP_CMD_CONNECTION_REQUEST) {
                        if((ACLData[12] | (ACLData[13] << 8)) == HID_CTRL_PSM) {
                                pBtd->l2capConnectionClaimed = true; // Claim that the incoming connection belongs to this service
                                activeConnection = true;
                                hci_handle = pBtd->hci_handle; // Store the HCI Handle for the connection
                                l2cap_state = L2CAP_WAIT;
                                remote_name_first = pBtd->remote_name[0]; // Store the first letter in remote name for the connection
#ifdef DEBUG_USB_HOST
                                if(pBtd->hci_version < 3) { // Check the HCI Version of the Bluetooth dongle
                                        Notify(PSTR("\r\nYour dongle may not support reading the analog buttons, sensors and status\r\nYour HCI Version is: "), 0x80);
                                        Notify(pBtd->hci_version, 0x80);
                                        Notify(PSTR("\r\nBut should be at least 3\r\nThis means that it doesn't support Bluetooth Version 2.0+EDR"), 0x80);
                                }
#endif
                        }
                }
        }

        if(checkHciHandle(ACLData, hci_handle)) { // acl_handle_ok
                memcpy(l2capinbuf, ACLData, BULK_MAXPKTSIZE);
                if((l2capinbuf[6] | (l2capinbuf[7] << 8)) == 0x0001U) { // l2cap_control - Channel ID for ACL-U
                        if(l2capinbuf[8] == L2CAP_CMD_COMMAND_REJECT) {
#ifdef DEBUG_USB_HOST
                                Notify(PSTR("\r\nL2CAP Command Rejected - Reason: "), 0x80);
                                D_PrintHex<uint8_t > (l2capinbuf[13], 0x80);
                                Notify(PSTR(" "), 0x80);
                                D_PrintHex<uint8_t > (l2capinbuf[12], 0x80);
                                Notify(PSTR(" Data: "), 0x80);
                                D_PrintHex<uint8_t > (l2capinbuf[17], 0x80);
                                Notify(PSTR(" "), 0x80);
                                D_PrintHex<uint8_t > (l2capinbuf[16], 0x80);
                                Notify(PSTR(" "), 0x80);
                                D_PrintHex<uint8_t > (l2capinbuf[15], 0x80);
                                Notify(PSTR(" "), 0x80);
                                D_PrintHex<uint8_t > (l2capinbuf[14], 0x80);
#endif
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
                                                l2cap_set_flag(L2CAP_FLAG_CONFIG_CONTROL_SUCCESS);
                                        } else if(l2capinbuf[12] == interrupt_dcid[0] && l2capinbuf[13] == interrupt_dcid[1]) {
                                                //Notify(PSTR("\r\nHID Interrupt Configuration Complete"), 0x80);
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
                                Notify(PSTR("\r\nL2CAP Unknown Signaling Command: "), 0x80);
                                D_PrintHex<uint8_t > (l2capinbuf[8], 0x80);
                        }
#endif
                } else if(l2capinbuf[6] == interrupt_dcid[0] && l2capinbuf[7] == interrupt_dcid[1]) { // l2cap_interrupt
                        //Notify(PSTR("\r\nL2CAP Interrupt"), 0x80);
                        if(PS3Connected || PS3MoveConnected || PS3NavigationConnected) {
                                /* Read Report */
                                if(l2capinbuf[8] == 0xA1) { // HID_THDR_DATA_INPUT
                                        lastMessageTime = millis(); // Store the last message time

                                        if(PS3Connected || PS3NavigationConnected)
                                                ButtonState = (uint32_t)(l2capinbuf[11] | ((uint16_t)l2capinbuf[12] << 8) | ((uint32_t)l2capinbuf[13] << 16));
                                        else if(PS3MoveConnected)
                                                ButtonState = (uint32_t)(l2capinbuf[10] | ((uint16_t)l2capinbuf[11] << 8) | ((uint32_t)l2capinbuf[12] << 16));

                                        //Notify(PSTR("\r\nButtonState", 0x80);
                                        //PrintHex<uint32_t>(ButtonState, 0x80);

                                        if(ButtonState != OldButtonState) {
                                                ButtonClickState = ButtonState & ~OldButtonState; // Update click state variable
                                                OldButtonState = ButtonState;
                                        }

#ifdef PRINTREPORT // Uncomment "#define PRINTREPORT" to print the report send by the PS3 Controllers
                                        for(uint8_t i = 10; i < 58; i++) {
                                                D_PrintHex<uint8_t > (l2capinbuf[i], 0x80);
                                                Notify(PSTR(" "), 0x80);
                                        }
                                        Notify(PSTR("\r\n"), 0x80);
#endif
                                }
                        }
                }
                L2CAP_task();
        }
}

void PS3BT::L2CAP_task() {
        switch(l2cap_state) {
                case L2CAP_WAIT:
                        if(l2cap_check_flag(L2CAP_FLAG_CONNECTION_CONTROL_REQUEST)) {
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

                case L2CAP_INTERRUPT_CONFIG_REQUEST:
                        if(l2cap_check_flag(L2CAP_FLAG_CONFIG_INTERRUPT_SUCCESS)) { // Now the HID channels is established
#ifdef DEBUG_USB_HOST
                                Notify(PSTR("\r\nHID Interrupt Successfully Configured"), 0x80);
#endif
                                if(remote_name_first == 'M') { // First letter in Motion Controller ('M')
                                        memset(l2capinbuf, 0, BULK_MAXPKTSIZE); // Reset l2cap in buffer as it sometimes read it as a button has been pressed
                                        l2cap_state = TURN_ON_LED;
                                } else
                                        l2cap_state = PS3_ENABLE_SIXAXIS;
                                timer = millis();
                        }
                        break;

                        /* These states are handled in Run() */

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

void PS3BT::Run() {
        switch(l2cap_state) {
                case PS3_ENABLE_SIXAXIS:
                        if(millis() - timer > 1000) { // loop 1 second before sending the command
                                memset(l2capinbuf, 0, BULK_MAXPKTSIZE); // Reset l2cap in buffer as it sometimes read it as a button has been pressed
                                for(uint8_t i = 15; i < 19; i++)
                                        l2capinbuf[i] = 0x7F; // Set the analog joystick values to center position
                                enable_sixaxis();
                                l2cap_state = TURN_ON_LED;
                                timer = millis();
                        }
                        break;

                case TURN_ON_LED:
                        if(millis() - timer > 1000) { // loop 1 second before sending the command
                                if(remote_name_first == 'P') { // First letter in PLAYSTATION(R)3 Controller ('P')
#ifdef DEBUG_USB_HOST
                                        Notify(PSTR("\r\nDualshock 3 Controller Enabled\r\n"), 0x80);
#endif
                                        PS3Connected = true;
                                } else if(remote_name_first == 'N') { // First letter in Navigation Controller ('N')
#ifdef DEBUG_USB_HOST
                                        Notify(PSTR("\r\nNavigation Controller Enabled\r\n"), 0x80);
#endif
                                        PS3NavigationConnected = true;
                                } else if(remote_name_first == 'M') { // First letter in Motion Controller ('M')
                                        timer = millis();
#ifdef DEBUG_USB_HOST
                                        Notify(PSTR("\r\nMotion Controller Enabled\r\n"), 0x80);
#endif
                                        PS3MoveConnected = true;
                                }
                                ButtonState = 0; // Clear all values
                                OldButtonState = 0;
                                ButtonClickState = 0;

                                onInit(); // Turn on the LED on the controller
                                l2cap_state = L2CAP_DONE;
                        }
                        break;

                case L2CAP_DONE:
                        if(PS3MoveConnected) { // The Bulb and rumble values, has to be send at approximately every 5th second for it to stay on
                                if(millis() - timer > 4000) { // Send at least every 4th second
                                        HIDMove_Command(HIDMoveBuffer, HID_BUFFERSIZE); // The Bulb and rumble values, has to be written again and again, for it to stay turned on
                                        timer = millis();
                                }
                        }
                        break;
        }
}

/************************************************************/
/*                    HID Commands                          */
/************************************************************/

// Playstation Sixaxis Dualshock and Navigation Controller commands

void PS3BT::HID_Command(uint8_t* data, uint8_t nbytes) {
        if(millis() - timerHID <= 150) // Check if is has been more than 150ms since last command
                delay((uint32_t)(150 - (millis() - timerHID))); // There have to be a delay between commands
        pBtd->L2CAP_Command(hci_handle, data, nbytes, control_scid[0], control_scid[1]); // Both the Navigation and Dualshock controller sends data via the control channel
        timerHID = millis();
}

void PS3BT::setAllOff() {
        HIDBuffer[3] = 0x00; // Rumble bytes
        HIDBuffer[4] = 0x00;
        HIDBuffer[5] = 0x00;
        HIDBuffer[6] = 0x00;

        HIDBuffer[11] = 0x00; // LED byte

        HID_Command(HIDBuffer, HID_BUFFERSIZE);
}

void PS3BT::setRumbleOff() {
        HIDBuffer[3] = 0x00;
        HIDBuffer[4] = 0x00;
        HIDBuffer[5] = 0x00;
        HIDBuffer[6] = 0x00;

        HID_Command(HIDBuffer, HID_BUFFERSIZE);
}

void PS3BT::setRumbleOn(RumbleEnum mode) {
        uint8_t power[2] = {0xff, 0x00}; // Defaults to RumbleLow
        if(mode == RumbleHigh) {
                power[0] = 0x00;
                power[1] = 0xff;
        }
        setRumbleOn(0xfe, power[0], 0xfe, power[1]);
}

void PS3BT::setRumbleOn(uint8_t rightDuration, uint8_t rightPower, uint8_t leftDuration, uint8_t leftPower) {
        HIDBuffer[3] = rightDuration;
        HIDBuffer[4] = rightPower;
        HIDBuffer[5] = leftDuration;
        HIDBuffer[6] = leftPower;
        HID_Command(HIDBuffer, HID_BUFFERSIZE);
}

void PS3BT::setLedRaw(uint8_t value) {
        HIDBuffer[11] = value << 1;
        HID_Command(HIDBuffer, HID_BUFFERSIZE);
}

void PS3BT::setLedOff(LEDEnum a) {
        HIDBuffer[11] &= ~((uint8_t)((pgm_read_byte(&PS3_LEDS[(uint8_t)a]) & 0x0f) << 1));
        HID_Command(HIDBuffer, HID_BUFFERSIZE);
}

void PS3BT::setLedOn(LEDEnum a) {
        if(a == OFF)
                setLedRaw(0);
        else {
                HIDBuffer[11] |= (uint8_t)((pgm_read_byte(&PS3_LEDS[(uint8_t)a]) & 0x0f) << 1);
                HID_Command(HIDBuffer, HID_BUFFERSIZE);
        }
}

void PS3BT::setLedToggle(LEDEnum a) {
        HIDBuffer[11] ^= (uint8_t)((pgm_read_byte(&PS3_LEDS[(uint8_t)a]) & 0x0f) << 1);
        HID_Command(HIDBuffer, HID_BUFFERSIZE);
}

void PS3BT::enable_sixaxis() { // Command used to enable the Dualshock 3 and Navigation controller to send data via Bluetooth
        uint8_t cmd_buf[6];
        cmd_buf[0] = 0x53; // HID BT Set_report (0x50) | Report Type (Feature 0x03)
        cmd_buf[1] = 0xF4; // Report ID
        cmd_buf[2] = 0x42; // Special PS3 Controller enable commands
        cmd_buf[3] = 0x03;
        cmd_buf[4] = 0x00;
        cmd_buf[5] = 0x00;

        HID_Command(cmd_buf, 6);
}

// Playstation Move Controller commands

void PS3BT::HIDMove_Command(uint8_t* data, uint8_t nbytes) {
        if(millis() - timerHID <= 150)// Check if is has been less than 150ms since last command
                delay((uint32_t)(150 - (millis() - timerHID))); // There have to be a delay between commands
        pBtd->L2CAP_Command(hci_handle, data, nbytes, interrupt_scid[0], interrupt_scid[1]); // The Move controller sends it's data via the intterrupt channel
        timerHID = millis();
}

void PS3BT::moveSetBulb(uint8_t r, uint8_t g, uint8_t b) { // Use this to set the Color using RGB values
        // Set the Bulb's values into the write buffer
        HIDMoveBuffer[3] = r;
        HIDMoveBuffer[4] = g;
        HIDMoveBuffer[5] = b;

        HIDMove_Command(HIDMoveBuffer, HID_BUFFERSIZE);
}

void PS3BT::moveSetBulb(ColorsEnum color) { // Use this to set the Color using the predefined colors in enum
        moveSetBulb((uint8_t)(color >> 16), (uint8_t)(color >> 8), (uint8_t)(color));
}

void PS3BT::moveSetRumble(uint8_t rumble) {
#ifdef DEBUG_USB_HOST
        if(rumble < 64 && rumble != 0) // The rumble value has to at least 64, or approximately 25% (64/255*100)
                Notify(PSTR("\r\nThe rumble value has to at least 64, or approximately 25%"), 0x80);
#endif
        // Set the rumble value into the write buffer
        HIDMoveBuffer[7] = rumble;

        HIDMove_Command(HIDMoveBuffer, HID_BUFFERSIZE);
}

void PS3BT::onInit() {
        if(pFuncOnInit)
                pFuncOnInit(); // Call the user function
        else {
                if(PS3MoveConnected)
                        moveSetBulb(Red);
                else // Dualshock 3 or Navigation controller
                        setLedOn(LED1);
        }
}
