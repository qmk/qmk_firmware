/* Copyright 2024 keymagichorse
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "bhq.h"


#include <stdbool.h>
#include "quantum.h"
#include "bluetooth.h"
#include "raw_hid.h"

// **************************** uart io  define ****************************
// uart2: Tx:A2 Rx:A3
#ifndef BT_DRIVER_UART_TX_BANK
#    define BT_DRIVER_UART_TX_BANK GPIOA
#endif
#ifndef BT_DRIVER_UART_RX_BANK
#    define BT_DRIVER_UART_RX_BANK GPIOA
#endif

#ifndef BT_DRIVER_UART_TX
#    define BT_DRIVER_UART_TX 2
#endif

#ifndef BT_DRIVER_UART_RX
#    define BT_DRIVER_UART_RX 3
#endif
// select uart2
#ifndef BT_DRIVER
#    define BT_DRIVER SD2
#endif

#ifdef USE_GPIOV1
#    ifndef BT_DRIVER_UART_TX_PAL_MODE
#        define BT_DRIVER_UART_TX_PAL_MODE PAL_MODE_STM32_ALTERNATE_PUSHPULL
#    endif
#    ifndef BT_DRIVER_UART_RX_PAL_MODE
#        define BT_DRIVER_UART_RX_PAL_MODE PAL_MODE_STM32_ALTERNATE_PUSHPULL
#    endif
#else
// The default PAL alternate modes are used to signal that the pins are used for I2C
#    ifndef BT_DRIVER_UART_TX_PAL_MODE
#        define BT_DRIVER_UART_TX_PAL_MODE 7
#    endif
#    ifndef BT_DRIVER_UART_RX_PAL_MODE
#        define BT_DRIVER_UART_RX_PAL_MODE 7
#    endif
#endif
// **************************** uart io  define ****************************

uint8_t bhkBuff[PACKET_MAX_LEN] = {0};

void bhq_init(bool wakeup_from_low_power_mode) {
    uint8_t        pkt[] = "hello qmk uart2 dev config success!\r\n";

    SerialConfig config = {
        .speed = 115200,
    };
    if (wakeup_from_low_power_mode) {
        sdInit();
        sdStart(&BT_DRIVER, &config);

        return;
    }
    sdStart(&BT_DRIVER, &config);
    palSetPadMode(BT_DRIVER_UART_TX_BANK, BT_DRIVER_UART_TX, PAL_MODE_ALTERNATE(BT_DRIVER_UART_TX_PAL_MODE));
    palSetPadMode(BT_DRIVER_UART_RX_BANK, BT_DRIVER_UART_RX, PAL_MODE_ALTERNATE(BT_DRIVER_UART_RX_PAL_MODE));

    sdWrite(&BT_DRIVER,pkt, sizeof(pkt)-1);
}















uint8_t bhkVerify(uint8_t *dat, uint16_t length);
uint16_t bhkSumCrc(uint8_t *data, uint16_t length) ;

// bhq model send uart data
void BHQ_SendData(uint8_t *dat, uint16_t length)
{
    sdWrite(&BT_DRIVER,dat, length);
}

// common Not data Ack
void ackCommonNotData(uint8_t cmdid, uint8_t sta)
{
    uint8_t index = 0;
    uint16_t crc = 0;

    bhkBuff[index++] = BHQ_FRAME_HEADER_1;          // frame header 1
    bhkBuff[index++] = BHQ_FRAME_HEADER_2;          // frame header 2
    bhkBuff[index++] = BHQ_NOT_ACK;                 // ack enabled

    bhkBuff[index++] = 0x02;                        // length
    bhkBuff[index++] = BHQ_CMD_TO_ACKCMD(cmdid);    // ack cmdid
    bhkBuff[index++] = sta;                         // is success

    crc = bhkSumCrc(bhkBuff, index);
    bhkBuff[index++] = BHQ_L_UINT16(crc);           // crc low
    bhkBuff[index++] = BHQ_H_UINT16(crc);           // crc high
    bhkBuff[index++] = BHQ_FRAME_END_1;
    BHQ_SendData(bhkBuff, index);
}
void BHQ_Protocol_Process(uint8_t *dat, uint16_t length)
{
    uint8_t cmdid = 0;
    cmdid = dat[4];
    switch(cmdid)
    {
        case 0x26:
            ackCommonNotData(cmdid,0);
            break;
    }
}



void bhq_task(void)
{
    static uint8_t buf[PACKET_MAX_LEN] = {0};
    static uint8_t index = 0;
    static uint8_t dataLength = 0;
    static uint8_t u_sta = 0;
    uint8_t bytedata = 0;
    static bool    wait_for_new_pkt = false;
    msg_t msg  = 0;
    if(BT_DRIVER.iqueue.q_counter > 0)
    {
        // 检查是否有数据可用
        msg = sdGetTimeout(&BT_DRIVER, TIME_IMMEDIATE);
        bytedata = (uint8_t)msg;
        if (msg == Q_TIMEOUT) 
        {
            // 处理超时，没有数据可用
            while (true)
            {
                // 检查输入队列是否为空
                if (BT_DRIVER.iqueue.q_counter > 0) 
                {
                    // 队列中有数据，处理数据
                    msg = sdGetTimeout(&BT_DRIVER, TIME_IMMEDIATE);
                    // 处理数据的代码
                    if (msg == Q_TIMEOUT) 
                    {
                        // 队列为空，退出循环
                        break;
                    }
                } 
                else 
                {
                    // 队列为空，退出循环
                    break;
                }

            }
            index = 0;
            u_sta = 0;
            dataLength = 0;
            memset(buf, 0, PACKET_MAX_LEN);
        } 
        else 
        {
            wait_for_new_pkt = true;
        }
    }
    else
    {
        if(index > 0)
        {
            index = 0;
            u_sta = 0;
            dataLength = 0;
            memset(buf, 0, PACKET_MAX_LEN);
        }
       
    }


    if(wait_for_new_pkt == false)
    {
        return;
    }
    wait_for_new_pkt = false;



    switch (u_sta)
    {
        case 0:
            if(bytedata == 0x5D)
            {
                index = 0;
                buf[index++] = bytedata;
                u_sta++;  
            }
            break;
        case 1:
            if(bytedata == 0x7E)
            {
                buf[index++] = bytedata;
                u_sta++;  
            }
            break;
        case 2:
            if(bytedata == 0x50 || bytedata == 0x51)
            {
                buf[index++] = bytedata;
                u_sta++;  
            }
            break;
        case 3:
            buf[index++] = bytedata;
            dataLength = 2 + 1 + 1 + bytedata + 2 + 1;  //  Frame Header2 + isack1 + length1 + dataN + crc2 + Frame end1
            u_sta++;  
            break;
        case 4:
            buf[index++] = bytedata;
            if(index == dataLength && buf[dataLength - 1] == 0x5E)
            {
                // this full of data package
                if(bhkVerify(buf, index) == 0x00)
                {
                    BHQ_Protocol_Process(buf, index) ;
                }
                index = 0;
                u_sta = 0;
                dataLength = 0;
                memset(buf, 0, PACKET_MAX_LEN);
            }
            break;
    }
}


// 验证数据是否有效
uint8_t bhkVerify(uint8_t *dat, uint16_t length)
{
    uint8_t dataRead_length = 4 + dat[3];    // 两个帧头 一个应答使能 一个长度 = 4 不包括帧头的长度
//    PRINT("dataRead_length:%d \r\n",dataRead_length);

    uint16_t dataReadCrc = BHQ_BUILD_UINT16(dat[dataRead_length],dat[dataRead_length + 1]);
//    PRINT("readCRCL %02x  readCRCH %02x \r\n",dat[dataRead_length],dat[dataRead_length + 1]);

    uint16_t dataSumCrc = bhkSumCrc(dat,dataRead_length) ;
//    PRINT("readCRC %04x    sumCRC %04x \r\n", dataReadCrc, dataSumCrc);
//    PRINT("readCRC %d    sumCRC %d \r\n", dataReadCrc, dataSumCrc);


    if(dat[0] != BHQ_FRAME_HEADER_1 || dat[1] != BHQ_FRAME_HEADER_2)
    {
//        PRINT("Verify: FRAME_HEADER error !! \r\n");
        return 0x01;
    }

    if(dataReadCrc != dataSumCrc)
    {
//        PRINT("Verify: CRC error !! \r\n");

        return 0x02;
    }

    if(dat[dataRead_length + 2] != BHQ_FRAME_END_1)  // 跳过两个校验和就到帧尾了
    {
//        PRINT("Verify: FRAME_END error !! \r\n");
        return 0x03;
    }
//    PRINT("Verify: data success !! \r\n");
    return 0;
}



// calculate CRCCRC-16/MODBUS
uint16_t bhkSumCrc(uint8_t *data, uint16_t length) {
    uint16_t i;
    uint16_t crc = 0xFFFF; 
    while(length--)
    {
        crc ^= *data++;
        for (i = 0; i < 8; ++i)
        {
            if (crc & 1)
            {
                crc = (crc >> 1) ^ 0xA001; 
            }
            else
            {
                crc = (crc >> 1);
            }
        }
    }
    return crc;
}
