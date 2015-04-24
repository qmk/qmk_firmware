/* mbed USBHost Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "USBHostKeyboard.h"

#if USBHOST_KEYBOARD

static uint8_t keymap[4][0x39] = {
    { 0, 0, 0, 0, 'a', 'b' /*0x05*/,
      'c', 'd', 'e', 'f', 'g' /*0x0a*/,
      'h', 'i', 'j', 'k', 'l'/*0x0f*/,
      'm', 'n', 'o', 'p', 'q'/*0x14*/,
      'r', 's', 't', 'u', 'v'/*0x19*/,
      'w', 'x', 'y', 'z', '1'/*0x1E*/,
      '2', '3', '4', '5', '6'/*0x23*/,
      '7', '8', '9', '0', 0x0A /*enter*/, /*0x28*/
      0x1B /*escape*/, 0x08 /*backspace*/, 0x09/*tab*/, 0x20/*space*/, '-', /*0x2d*/
      '=', '[', ']', '\\', '#', /*0x32*/
      ';', '\'', 0, ',', '.', /*0x37*/
      '/'},

    /* CTRL MODIFIER */
    { 0, 0, 0, 0, 0, 0 /*0x05*/,
      0, 0, 0, 0, 0 /*0x0a*/,
      0, 0, 0, 0, 0/*0x0f*/,
      0, 0, 0, 0, 0/*0x14*/,
      0, 0, 0, 0, 0/*0x19*/,
      0, 0, 0, 0, 0/*0x1E*/,
      0, 0, 0, 0, 0/*0x23*/,
      0, 0, 0, 0, 0 /*enter*/, /*0x28*/
      0, 0, 0, 0, 0, /*0x2d*/
      0, 0, 0, 0, 0, /*0x32*/
      0, 0, 0, 0, 0, /*0x37*/
      0},

    /* SHIFT MODIFIER */
    { 0, 0, 0, 0, 'A', 'B' /*0x05*/,
      'C', 'D', 'E', 'F', 'G' /*0x0a*/,
      'H', 'I', 'J', 'K', 'L'/*0x0f*/,
      'M', 'N', 'O', 'P', 'Q'/*0x14*/,
      'R', 'S', 'T', 'U', 'V'/*0x19*/,
      'W', 'X', 'Y', 'Z', '!'/*0x1E*/,
      '@', '#', '$', '%', '^'/*0x23*/,
      '&', '*', '(', ')', 0, /*0x28*/
      0, 0, 0, 0, 0, /*0x2d*/
      '+', '{', '}', '|', '~', /*0x32*/
      ':', '"', 0, '<', '>', /*0x37*/
      '?'},

    /* ALT MODIFIER */
    { 0, 0, 0, 0, 0, 0 /*0x05*/,
      0, 0, 0, 0, 0 /*0x0a*/,
      0, 0, 0, 0, 0/*0x0f*/,
      0, 0, 0, 0, 0/*0x14*/,
      0, 0, 0, 0, 0/*0x19*/,
      0, 0, 0, 0, 0/*0x1E*/,
      0, 0, 0, 0, 0/*0x23*/,
      0, 0, 0, 0, 0 /*enter*/, /*0x28*/
      0, 0, 0, 0, 0, /*0x2d*/
      0, 0, 0, 0, 0, /*0x32*/
      0, 0, 0, 0, 0, /*0x37*/
      0}

};


USBHostKeyboard::USBHostKeyboard() {
    host = USBHost::getHostInst();
    init();
}


void USBHostKeyboard::init() {
    dev = NULL;
    int_in = NULL;
    report_id = 0;
    onKey = NULL;
    onKeyCode = NULL;
    dev_connected = false;
    keyboard_intf = -1;
    keyboard_device_found = false;
}

bool USBHostKeyboard::connected() {
    return dev_connected;
}


bool USBHostKeyboard::connect() {

    if (dev_connected) {
        return true;
    }

    for (uint8_t i = 0; i < MAX_DEVICE_CONNECTED; i++) {
        if ((dev = host->getDevice(i)) != NULL) {

            if (host->enumerate(dev, this))
                break;

            if (keyboard_device_found) {
                int_in = dev->getEndpoint(keyboard_intf, INTERRUPT_ENDPOINT, IN);

                if (!int_in)
                    break;

                USB_INFO("New Keyboard device: VID:%04x PID:%04x [dev: %p - intf: %d]", dev->getVid(), dev->getPid(), dev, keyboard_intf);
                dev->setName("Keyboard", keyboard_intf);
                host->registerDriver(dev, keyboard_intf, this, &USBHostKeyboard::init);

                int_in->attach(this, &USBHostKeyboard::rxHandler);
                host->interruptRead(dev, int_in, report, int_in->getSize(), false);

                dev_connected = true;
                return true;
            }
        }
    }
    init();
    return false;
}

void USBHostKeyboard::rxHandler() {
    int len = int_in->getLengthTransferred();
    int index = (len == 9) ? 1 : 0;
    int len_listen = int_in->getSize();
    uint8_t key = 0;
    if (len == 8 || len == 9) {
        uint8_t modifier = (report[index] == 4) ? 3 : report[index];
        len_listen = len;
        key = keymap[modifier][report[index + 2]];
        if (key && onKey) {
            (*onKey)(key);
        }
        if ((report[index + 2] || modifier) && onKeyCode) {
            (*onKeyCode)(report[index + 2], modifier);
        }
    }
    if (dev && int_in)
        host->interruptRead(dev, int_in, report, len_listen, false);
}

/*virtual*/ void USBHostKeyboard::setVidPid(uint16_t vid, uint16_t pid)
{
    // we don't check VID/PID for keyboard driver
}

/*virtual*/ bool USBHostKeyboard::parseInterface(uint8_t intf_nb, uint8_t intf_class, uint8_t intf_subclass, uint8_t intf_protocol) //Must return true if the interface should be parsed
{
    if ((keyboard_intf == -1) &&
        (intf_class == HID_CLASS) &&
        (intf_subclass == 0x01) &&
        (intf_protocol == 0x01)) {
        keyboard_intf = intf_nb;
        return true;
    }
    return false;
}

/*virtual*/ bool USBHostKeyboard::useEndpoint(uint8_t intf_nb, ENDPOINT_TYPE type, ENDPOINT_DIRECTION dir) //Must return true if the endpoint will be used
{
    if (intf_nb == keyboard_intf) {
        if (type == INTERRUPT_ENDPOINT && dir == IN) {
            keyboard_device_found = true;
            return true;
        }
    }
    return false;
}

#endif
