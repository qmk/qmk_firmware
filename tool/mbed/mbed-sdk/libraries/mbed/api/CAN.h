/* mbed Microcontroller Library
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
#ifndef MBED_CAN_H
#define MBED_CAN_H

#include "platform.h"

#if DEVICE_CAN

#include "can_api.h"
#include "can_helper.h"
#include "FunctionPointer.h"

namespace mbed {

/** CANMessage class
 */
class CANMessage : public CAN_Message {

public:
    /** Creates empty CAN message.
     */
    CANMessage() : CAN_Message() {
        len    = 8;
        type   = CANData;
        format = CANStandard;
        id     = 0;
        memset(data, 0, 8);
    }

    /** Creates CAN message with specific content.
     */
    CANMessage(int _id, const char *_data, char _len = 8, CANType _type = CANData, CANFormat _format = CANStandard) {
      len    = _len & 0xF;
      type   = _type;
      format = _format;
      id     = _id;
      memcpy(data, _data, _len);
    }

    /** Creates CAN remote message.
     */
    CANMessage(int _id, CANFormat _format = CANStandard) {
      len    = 0;
      type   = CANRemote;
      format = _format;
      id     = _id;
      memset(data, 0, 8);
    }
};

/** A can bus client, used for communicating with can devices
 */
class CAN {

public:
    /** Creates an CAN interface connected to specific pins.
     *
     *  @param rd read from transmitter
     *  @param td transmit to transmitter
     *
     * Example:
     * @code
     * #include "mbed.h"
     *
     * Ticker ticker;
     * DigitalOut led1(LED1);
     * DigitalOut led2(LED2);
     * CAN can1(p9, p10);
     * CAN can2(p30, p29);
     *
     * char counter = 0;
     *
     * void send() {
     *     if(can1.write(CANMessage(1337, &counter, 1))) {
     *         printf("Message sent: %d\n", counter);
     *         counter++;
     *     }
     *     led1 = !led1;
     * }
     *
     * int main() {
     *     ticker.attach(&send, 1);
     *    CANMessage msg;
     *     while(1) {
     *         if(can2.read(msg)) {
     *             printf("Message received: %d\n\n", msg.data[0]);
     *             led2 = !led2;
     *         }
     *         wait(0.2);
     *     }
     * }
     * @endcode
     */
    CAN(PinName rd, PinName td);
    virtual ~CAN();

    /** Set the frequency of the CAN interface
     *
     *  @param hz The bus frequency in hertz
     *
     *  @returns
     *    1 if successful,
     *    0 otherwise
     */
    int frequency(int hz);

    /** Write a CANMessage to the bus.
     *
     *  @param msg The CANMessage to write.
     *
     *  @returns
     *    0 if write failed,
     *    1 if write was successful
     */
    int write(CANMessage msg);

    /** Read a CANMessage from the bus.
     *
     *  @param msg A CANMessage to read to.
     *  @param handle message filter handle (0 for any message)
     *
     *  @returns
     *    0 if no message arrived,
     *    1 if message arrived
     */
    int read(CANMessage &msg, int handle = 0);

    /** Reset CAN interface.
     *
     * To use after error overflow.
     */
    void reset();

    /** Puts or removes the CAN interface into silent monitoring mode
     *
     *  @param silent boolean indicating whether to go into silent mode or not
     */
    void monitor(bool silent);

    enum Mode {
        Reset = 0,
        Normal,
        Silent,
        LocalTest,
        GlobalTest,
        SilentTest
    };

    /** Change CAN operation to the specified mode
     *
     *  @param mode The new operation mode (CAN::Normal, CAN::Silent, CAN::LocalTest, CAN::GlobalTest, CAN::SilentTest)
     *
     *  @returns
     *    0 if mode change failed or unsupported,
     *    1 if mode change was successful
     */
    int mode(Mode mode);

    /** Filter out incomming messages
     *
     *  @param id the id to filter on
     *  @param mask the mask applied to the id
     *  @param format format to filter on (Default CANAny)
     *  @param handle message filter handle (Optional)
     *
     *  @returns
     *    0 if filter change failed or unsupported,
     *    new filter handle if successful
     */
    int filter(unsigned int id, unsigned int mask, CANFormat format = CANAny, int handle = 0);

    /** Returns number of read errors to detect read overflow errors.
     */
    unsigned char rderror();

    /** Returns number of write errors to detect write overflow errors.
     */
    unsigned char tderror();

    enum IrqType {
        RxIrq = 0,
        TxIrq,
        EwIrq,
        DoIrq,
        WuIrq,
        EpIrq,
        AlIrq,
        BeIrq,
        IdIrq
    };

    /** Attach a function to call whenever a CAN frame received interrupt is
     *  generated.
     *
     *  @param fptr A pointer to a void function, or 0 to set as none
     *  @param event Which CAN interrupt to attach the member function to (CAN::RxIrq for message received, CAN::TxIrq for transmitted or aborted, CAN::EwIrq for error warning, CAN::DoIrq for data overrun, CAN::WuIrq for wake-up, CAN::EpIrq for error passive, CAN::AlIrq for arbitration lost, CAN::BeIrq for bus error)
     */
    void attach(void (*fptr)(void), IrqType type=RxIrq);

   /** Attach a member function to call whenever a CAN frame received interrupt
    *  is generated.
    *
    *  @param tptr pointer to the object to call the member function on
    *  @param mptr pointer to the member function to be called
    *  @param event Which CAN interrupt to attach the member function to (CAN::RxIrq for message received, TxIrq for transmitted or aborted, EwIrq for error warning, DoIrq for data overrun, WuIrq for wake-up, EpIrq for error passive, AlIrq for arbitration lost, BeIrq for bus error)
    */
   template<typename T>
   void attach(T* tptr, void (T::*mptr)(void), IrqType type=RxIrq) {
        if((mptr != NULL) && (tptr != NULL)) {
            _irq[type].attach(tptr, mptr);
            can_irq_set(&_can, (CanIrqType)type, 1);
        }
        else {
            can_irq_set(&_can, (CanIrqType)type, 0);
        }
    }

    static void _irq_handler(uint32_t id, CanIrqType type);

protected:
    can_t           _can;
    FunctionPointer _irq[9];
};

} // namespace mbed

#endif

#endif    // MBED_CAN_H
