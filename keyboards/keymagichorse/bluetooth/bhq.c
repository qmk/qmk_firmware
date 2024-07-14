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
#include "report_buffer.h"

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

void bhq_Disable(void)
{
    // 停止串行驱动器
    sdStop(&BT_DRIVER);
    
    // 配置引脚为模拟输入以降低功耗
    palSetPadMode(BT_DRIVER_UART_TX_BANK, BT_DRIVER_UART_TX, PAL_MODE_INPUT_ANALOG);
    palSetPadMode(BT_DRIVER_UART_RX_BANK, BT_DRIVER_UART_RX, PAL_MODE_INPUT_ANALOG);

}













uint8_t bhkVerify(uint8_t *dat, uint16_t length);
uint16_t bhkSumCrc(uint8_t *data, uint16_t length) ;

// bhq model send uart data
void BHQ_SendData(uint8_t *dat, uint16_t length)
{
    sdWrite(&BT_DRIVER,dat, length);
}


void BHQ_SendCmd(uint8_t isack, uint8_t *dat, uint8_t datLength)
{
    uint8_t index = 0;
    uint16_t crc = 0;
    uint8_t i = 0;
    uint8_t pkt[128] = {0};
    memset(pkt, 0, 128);

    pkt[index++] = BHQ_FRAME_HEADER_1;          
    pkt[index++] = BHQ_FRAME_HEADER_2;          
    pkt[index++] = isack;            
    pkt[index++] = datLength;                  
    for(i = 0; i < datLength; i++) 
    {
        pkt[index++] = dat[i];    
    }
    crc = bhkSumCrc(pkt, index);
    pkt[index++] = BHQ_L_UINT16(crc);           // crc 
    pkt[index++] = BHQ_H_UINT16(crc);           // crc 
    pkt[index++] = BHQ_FRAME_END_1;
    BHQ_SendData(pkt, index);
}



// common Not data Ack
void ackCommonNotData(uint8_t cmdid, uint8_t sta)
{
    uint8_t index = 0;

    bhkBuff[index++] = BHQ_CMD_TO_ACKCMD(cmdid);    
    bhkBuff[index++] = sta;                        

    BHQ_SendCmd(BHQ_NOT_ACK, bhkBuff,index);
}

void bhq_SetPairingMode(uint8_t host_index, uint8_t timeout_10s)
{
    uint8_t index = 0;

    bhkBuff[index++] = 0x14;
    bhkBuff[index++] = host_index;                        
    bhkBuff[index++] = timeout_10s;      

    BHQ_SendCmd(BHQ_NOT_ACK, bhkBuff,index);
}


void bhq_send_keyboard(uint8_t* report) {
    uint8_t index = 0;
    memset(bhkBuff, 0, PACKET_MAX_LEN);

    bhkBuff[index++] = 0x21;
    memcpy(bhkBuff + index, report, 8);
    index += 8;

    BHQ_SendCmd(BHQ_NOT_ACK, bhkBuff,index);
}

void bhq_send_nkro(uint8_t* report) {
    uint8_t index = 0;
    memset(bhkBuff, 0, PACKET_MAX_LEN);

    bhkBuff[index++] = 0x22;
    memcpy(bhkBuff + index, report, NKRO_REPORT_BITS + 1); // NKRO report lenght is limited to 31 bytes
    index += NKRO_REPORT_BITS + 1;
    
    BHQ_SendCmd(BHQ_NOT_ACK, bhkBuff,index);
}

void bhq_send_consumer(uint16_t report) {
    uint8_t index = 0;
    memset(bhkBuff, 0, PACKET_MAX_LEN);

    bhkBuff[index++] = 0x23;
    bhkBuff[index++] = report & 0xFF;
    bhkBuff[index++] = ((report) >> 8) & 0xFF;

    BHQ_SendCmd(BHQ_NOT_ACK, bhkBuff,index);
}

void bhq_send_system(uint16_t report) {

    uint8_t index = 0;
    memset(bhkBuff, 0, PACKET_MAX_LEN);

    bhkBuff[index++] = 0x24;
    bhkBuff[index++] = report & 0xFF;
    bhkBuff[index++] = ((report) >> 8) & 0xFF;

    BHQ_SendCmd(BHQ_NOT_ACK, bhkBuff,index);
}

void bhq_send_mouse(uint8_t* report) {
    uint8_t index = 0;
    memset(bhkBuff, 0, PACKET_MAX_LEN);

    bhkBuff[index++] = 0x25;            // Cmd type
    bhkBuff[index++] = report[1];                        // Button
    bhkBuff[index++] = report[2];                        // X
    bhkBuff[index++] = (report[2] & 0x80) ? 0xff : 0x00; // BHQ use 16bit report, set high byte
    bhkBuff[index++] = report[3];                        // Y
    bhkBuff[index++] = (report[3] & 0x80) ? 0xff : 0x00; // BHQ use 16bit report, set high byte
    bhkBuff[index++] = report[4];                        // V wheel
    bhkBuff[index++] = report[5];                        // H wheel

    BHQ_SendCmd(BHQ_NOT_ACK, bhkBuff,index);
}




// BHQ_Protocol_Process
void BHQ_Protocol_Process(uint8_t *dat, uint16_t length)
{
    uint8_t cmdid = 0;
    cmdid = dat[4];
    switch(cmdid)
    {
        case 0x26:  // ble model return hid led lock sta
            dat[5] = dat[5];    // led lock sta
            ackCommonNotData(cmdid,0);
            break;

        case 0xA1:
        case 0xA2:
        case 0xA3:
        case 0xA4:
        case 0xA5:
            report_buffer_set_inverval(DEFAULT_REPORT_INVERVAL_MS);
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
