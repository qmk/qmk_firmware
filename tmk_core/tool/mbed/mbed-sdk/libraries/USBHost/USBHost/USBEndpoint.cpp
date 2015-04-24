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


#include "dbg.h"
#include "USBEndpoint.h"

void USBEndpoint::init(HCED * hced_, ENDPOINT_TYPE type_, ENDPOINT_DIRECTION dir_, uint32_t size, uint8_t ep_number, HCTD* td_list_[2])
{
    hced = hced_;
    type = type_;
    dir = dir_;
    setup = (type == CONTROL_ENDPOINT) ? true : false;

    //TDs have been allocated by the host
    memcpy((HCTD**)td_list, td_list_, sizeof(HCTD*)*2); //TODO: Maybe should add a param for td_list size... at least a define
    memset(td_list_[0], 0, sizeof(HCTD));
    memset(td_list_[1], 0, sizeof(HCTD));

    td_list[0]->ep = this;
    td_list[1]->ep = this;

    hced->control = 0;
    //Empty queue
    hced->tailTD = td_list[0];
    hced->headTD = td_list[0];
    hced->nextED = 0;

    address = (ep_number & 0x7F) | ((dir - 1) << 7);

    hced->control = ((ep_number & 0x7F) << 7)                         // Endpoint address
                    | (type != CONTROL_ENDPOINT ? ( dir << 11) : 0 )  // direction : Out = 1, 2 = In
                    | ((size & 0x3ff) << 16);                         // MaxPkt Size

    transfer_len = 0;
    transferred = 0;
    buf_start = 0;
    nextEp = NULL;

    td_current = td_list[0];
    td_next = td_list[1];

    intf_nb = 0;

    state = USB_TYPE_IDLE;
}

void USBEndpoint::setSize(uint32_t size)
{
    hced->control &= ~(0x3ff << 16);
    hced->control |= (size << 16);
}


void USBEndpoint::setDeviceAddress(uint8_t addr)
{
    hced->control &= ~(0x7f);
    hced->control |= (addr & 0x7F);
}

void USBEndpoint::setSpeed(uint8_t speed)
{
    hced->control &= ~(1 << 13);
    hced->control |= (speed << 13);
}

//Only for control Eps
void USBEndpoint::setNextToken(uint32_t token)
{
    switch (token) {
        case TD_SETUP:
            dir = OUT;
            setup = true;
            break;
        case TD_IN:
            dir = IN;
            setup = false;
            break;
        case TD_OUT:
            dir = OUT;
            setup = false;
            break;
    }
}

struct {
    USB_TYPE type;
    const char * str;
} static type_string[] = {
/*0*/   {USB_TYPE_OK, "USB_TYPE_OK"},
        {USB_TYPE_CRC_ERROR, "USB_TYPE_CRC_ERROR"},
        {USB_TYPE_BIT_STUFFING_ERROR, "USB_TYPE_BIT_STUFFING_ERROR"},
        {USB_TYPE_DATA_TOGGLE_MISMATCH_ERROR, "USB_TYPE_DATA_TOGGLE_MISMATCH_ERROR"},
        {USB_TYPE_STALL_ERROR, "USB_TYPE_STALL_ERROR"},
/*5*/   {USB_TYPE_DEVICE_NOT_RESPONDING_ERROR, "USB_TYPE_DEVICE_NOT_RESPONDING_ERROR"},
        {USB_TYPE_PID_CHECK_FAILURE_ERROR, "USB_TYPE_PID_CHECK_FAILURE_ERROR"},
        {USB_TYPE_UNEXPECTED_PID_ERROR, "USB_TYPE_UNEXPECTED_PID_ERROR"},
        {USB_TYPE_DATA_OVERRUN_ERROR, "USB_TYPE_DATA_OVERRUN_ERROR"},
        {USB_TYPE_DATA_UNDERRUN_ERROR, "USB_TYPE_DATA_UNDERRUN_ERROR"},
/*10*/  {USB_TYPE_ERROR, "USB_TYPE_ERROR"},
        {USB_TYPE_ERROR, "USB_TYPE_ERROR"},
        {USB_TYPE_BUFFER_OVERRUN_ERROR, "USB_TYPE_BUFFER_OVERRUN_ERROR"},
        {USB_TYPE_BUFFER_UNDERRUN_ERROR, "USB_TYPE_BUFFER_UNDERRUN_ERROR"},
        {USB_TYPE_DISCONNECTED, "USB_TYPE_DISCONNECTED"},
/*15*/  {USB_TYPE_FREE, "USB_TYPE_FREE"},
        {USB_TYPE_IDLE, "USB_TYPE_IDLE"},
        {USB_TYPE_PROCESSING, "USB_TYPE_PROCESSING"},
        {USB_TYPE_ERROR, "USB_TYPE_ERROR"}
};

void USBEndpoint::setState(uint8_t st) {
    if (st > 18)
        return;
    state = type_string[st].type;
}


const char * USBEndpoint::getStateString() {
    return type_string[state].str;
}

void USBEndpoint::queueTransfer()
{
    transfer_len = (uint32_t)td_current->bufEnd - (uint32_t)td_current->currBufPtr + 1;
    transferred = transfer_len;
    buf_start = (uint8_t *)td_current->currBufPtr;

    //Now add this free TD at this end of the queue
    state = USB_TYPE_PROCESSING;
    td_current->nextTD = td_next;
    hced->tailTD = td_next;
}

void USBEndpoint::unqueueTransfer(volatile HCTD * td)
{
    td->control=0;
    td->currBufPtr=0;
    td->bufEnd=0;
    td->nextTD=0;
    hced->headTD = (HCTD *)((uint32_t)hced->tailTD | ((uint32_t)hced->headTD & 0x2)); //Carry bit
    td_current = td_next;
    td_next = td;
}

void USBEndpoint::queueEndpoint(USBEndpoint * ed)
{
    nextEp = ed;
    hced->nextED = (ed == NULL) ? 0 : ed->getHCED();
}
