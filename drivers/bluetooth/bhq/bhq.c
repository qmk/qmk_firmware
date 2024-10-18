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
#include "bluetooth.h"
#include "bluetooth_bhq.h"

#include "raw_hid.h"
#include "report_buffer.h"
#include "config.h"

#include "uart.h"
#include "quantum.h"

#include "km_printf.h"
uint8_t bhkBuff[PACKET_MAX_LEN] = {0};
uint32_t uartTimeoutBuffer = 0;         // uart timeout 

void bhq_init(void) 
{
    uart_init(128000);
    gpio_set_pin_input_low(BHQ_RUN_STATE_INPUT_PIN);    // Module operating status. 
    gpio_set_pin_output(QMK_RUN_OUTPUT_PIN);            // The qmk has a data request.
}

void bhq_Disable(void)
{
    palSetLineMode(UART_TX_PIN, PAL_MODE_INPUT_ANALOG);
    palSetLineMode(UART_RX_PIN, PAL_MODE_INPUT_ANALOG);
    sdStop(&UART_DRIVER);
}


uint8_t bhkVerify(uint8_t *dat, uint16_t length);
uint16_t bhkSumCrc(uint8_t *data, uint16_t length) ;
// bhq model send uart data
void BHQ_SendData(uint8_t *dat, uint16_t length)
{
    uint16_t i = 0;
    uint32_t wait_bhq_ack_timeout = 0;
    uint32_t last_toggle_time = 0;
    uint32_t bhq_wakeup = 0;
    if(gpio_read_pin(BHQ_RUN_STATE_INPUT_PIN) != BHQ_RUN_OR_INT_LEVEL)
    {
        wait_bhq_ack_timeout = sync_timer_read32();
        last_toggle_time = sync_timer_read32();
        while(1)
        {
            // Flip the level to wake the module
            gpio_write_pin_high(QMK_RUN_OUTPUT_PIN);
            if(sync_timer_elapsed32(last_toggle_time) >= 20)
            {
                gpio_write_pin_low(QMK_RUN_OUTPUT_PIN);
                last_toggle_time = sync_timer_read32();
            }
            // After the high and low level jump, the module wakes up, then you need to wait 10ms for the module to stabilize
            if(gpio_read_pin(BHQ_RUN_STATE_INPUT_PIN) == BHQ_RUN_OR_INT_LEVEL && bhq_wakeup == 0)
            {
                bhq_wakeup = sync_timer_read32();
            }
            if(gpio_read_pin(BHQ_RUN_STATE_INPUT_PIN) == BHQ_RUN_OR_INT_LEVEL && sync_timer_elapsed32(last_toggle_time) >= 5)
            {
                break;
            }

            if(sync_timer_elapsed32(wait_bhq_ack_timeout) > 100) 
            {
                gpio_write_pin_high(QMK_RUN_OUTPUT_PIN);
                return;
            }
        }
    }
    gpio_write_pin_high(QMK_RUN_OUTPUT_PIN);
    uart_transmit(dat, length);

    km_printf("mcu send data:");
    for (i = 0; i < length; i++)
    {
        km_printf("%02x ",dat[i]);
    }
    km_printf("\r\n");
}
int16_t BHQ_ReadData(void) {
    if (uart_available()) {
        return uart_read();
    } else {
        return -1;
    }
}

void BHQ_SendCmd(uint8_t isack, uint8_t *dat, uint8_t datLength)
{
    uint8_t index = 0;
    uint16_t crc = 0;
    uint8_t i = 0;
    uint8_t pkt[128] = {0};
    memset(pkt, 0, 128);
    isack = isack;

    pkt[index++] = BHQ_FRAME_HEADER_1;          
    pkt[index++] = BHQ_FRAME_HEADER_2;          
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

void bhq_ConfigRunParam(bhkDevConfigInfo_t parma)
{
    uint8_t i = 0;
    uint8_t index = 0;
    bhkBuff[index++] = 0x11;    
    bhkBuff[index++] = parma.vendor_id_source;    
    bhkBuff[index++] = BHQ_L_UINT16(parma.verndor_id);  
    bhkBuff[index++] = BHQ_H_UINT16(parma.verndor_id);  

    bhkBuff[index++] = BHQ_L_UINT16(parma.product_id);  
    bhkBuff[index++] = BHQ_H_UINT16(parma.product_id);  

    bhkBuff[index++] = BHQ_L_UINT16(parma.le_connection_interval_min);  
    bhkBuff[index++] = BHQ_H_UINT16(parma.le_connection_interval_min);  

    bhkBuff[index++] = BHQ_L_UINT16(parma.le_connection_interval_max);  
    bhkBuff[index++] = BHQ_H_UINT16(parma.le_connection_interval_max); 

    bhkBuff[index++] = BHQ_L_UINT16(parma.le_connection_interval_timeout);  
    bhkBuff[index++] = BHQ_H_UINT16(parma.le_connection_interval_timeout); 

    bhkBuff[index++] = parma.tx_poweer; 
    bhkBuff[index++] = parma.mk_is_read_battery_voltage; 
    bhkBuff[index++] = parma.mk_adc_pga; 

    bhkBuff[index++] = BHQ_L_UINT16(parma.mk_rvd_r1);  
    bhkBuff[index++] = BHQ_H_UINT16(parma.mk_rvd_r1); 

    bhkBuff[index++] = BHQ_L_UINT16(parma.mk_rvd_r2);  
    bhkBuff[index++] = BHQ_H_UINT16(parma.mk_rvd_r2); 
    
    bhkBuff[index++] = parma.bleNameStrLength; 

    for(i= 0; i < parma.bleNameStrLength; i++)
    {
        bhkBuff[index++] = parma.bleNameStr[i]; 
    }

    BHQ_SendCmd(BHQ_NOT_ACK, bhkBuff,index);
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
void bhq_OpenBleAdvertising(uint8_t host_index, uint8_t timeout_10s)
{
    uint8_t index = 0;

    bhkBuff[index++] = 0x15;
    bhkBuff[index++] = host_index;                        
    bhkBuff[index++] = timeout_10s;      

    BHQ_SendCmd(BHQ_NOT_ACK, bhkBuff,index);
}
void bhq_CloseBleAdvertising(void)
{
    uint8_t index = 0;

    bhkBuff[index++] = 0x16;
    bhkBuff[index++] = 0;
    BHQ_SendCmd(BHQ_NOT_ACK, bhkBuff,index);
}
void bhq_update_battery_percent(uint8_t percent) {
    uint8_t index = 0;
    memset(bhkBuff, 0, PACKET_MAX_LEN);

    bhkBuff[index++] = 0x18;
    bhkBuff[index++] = percent;

    BHQ_SendCmd(BHQ_ACK, bhkBuff,index);
}


void bhq_send_keyboard(uint8_t* report) {
    uint8_t index = 0;
    memset(bhkBuff, 0, PACKET_MAX_LEN);

    bhkBuff[index++] = 0x21;
    memcpy(bhkBuff + index, report, 8);
    index += 8;

    BHQ_SendCmd(BHQ_ACK, bhkBuff,index);
}

void bhq_send_nkro(uint8_t* report) {
    uint8_t index = 0;
    memset(bhkBuff, 0, PACKET_MAX_LEN);

    bhkBuff[index++] = 0x22;
    memcpy(bhkBuff + index, report, NKRO_REPORT_BITS + 1); // NKRO report lenght is limited to 31 bytes
    index += NKRO_REPORT_BITS + 1;
    
    BHQ_SendCmd(BHQ_ACK, bhkBuff,index);
}

void bhq_send_consumer(uint16_t report) {
    uint8_t index = 0;
    memset(bhkBuff, 0, PACKET_MAX_LEN);

    bhkBuff[index++] = 0x23;
    bhkBuff[index++] = report & 0xFF;
    bhkBuff[index++] = ((report) >> 8) & 0xFF;

    BHQ_SendCmd(BHQ_ACK, bhkBuff,index);
}

void bhq_send_system(uint16_t report) {

    uint8_t index = 0;
    memset(bhkBuff, 0, PACKET_MAX_LEN);

    bhkBuff[index++] = 0x24;
    bhkBuff[index++] = report & 0xFF;
    bhkBuff[index++] = ((report) >> 8) & 0xFF;

    BHQ_SendCmd(BHQ_ACK, bhkBuff,index);
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

    BHQ_SendCmd(BHQ_ACK, bhkBuff,index);
}

void bhq_send_hid_raw(uint8_t *data, uint8_t length)
{
    km_printf("mcu send hid raw length:%d\r\n",length);
    uint8_t index = 0;
    memset(bhkBuff, 0, PACKET_MAX_LEN);

    bhkBuff[index++] = 0x27;
    bhkBuff[index++] = length;
    memcpy(bhkBuff + index, data, length);
    index += length;
    BHQ_SendCmd(BHQ_ACK, bhkBuff,index);
}

// BHQ Status callback
__attribute__((weak)) void BHQ_State_Call(uint8_t cmdid, uint8_t *dat) {

    uint8_t advertSta = BHQ_GET_BLE_ADVERT_STA(dat[1]);
    uint8_t connectSta = BHQ_GET_BLE_CONNECT_STA(dat[1]);
    uint8_t pairingSta = BHQ_GET_BLE_PAIRING_STA(dat[1]);

    advertSta = BHQ_GET_BLE_ADVERT_STA(dat[1]);
    connectSta = BHQ_GET_BLE_CONNECT_STA(dat[1]);
    pairingSta = BHQ_GET_BLE_PAIRING_STA(dat[1]);

    km_printf("cmdid:%d",cmdid);
    if(cmdid == BHQ_ACK_RUN_STA_CMDID)
    {
        km_printf("[RSSI:%d]\t",dat[0]);
        km_printf("[advertSta: %d]\t", advertSta);
        km_printf("[connectSta: %d]\t", connectSta); // 0 = 断开, 1 = 已连接, 2 = 超时
        km_printf("[pairingSta: %d]\t", pairingSta);
        km_printf("[host_index:%d]\n",dat[2]);
    }
}

void BHQ_Led_Lock(uint8_t led_sta)
{
    km_printf("[%s] Num Lock\t", (led_sta & (1<<0)) ? "*" : " ");
    km_printf("[%s] Caps Lock\t", (led_sta & (1<<1)) ? "*" : " ");
    km_printf("[%s] Scroll Lock\n", (led_sta & (1<<2)) ? "*" : " ");
    bluetooth_bhq_set_keyboard_leds(led_sta);
    km_printf("bhq led sta:%d\n",led_sta);
}
void BHQ_Sta_Handel(uint8_t cmdid, uint8_t *dat) 
{
    uint8_t connectSta = BHQ_GET_BLE_CONNECT_STA(dat[1]);
    if(connectSta == 0)
    {
        BHQ_Led_Lock(0);
    }
    if(cmdid == BHQ_ACK_LED_LOCK_CMDID)
    {
        BHQ_Led_Lock(dat[0]);
    }
    BHQ_State_Call(cmdid, dat);
}
// BHQ_Protocol_Process
void BHQ_Protocol_Process(uint8_t *dat, uint16_t length)
{
    uint8_t cmdid = 0;
    uint8_t buff_sta = 0;
    cmdid = dat[3];
    uint8_t i = 0 ;
    km_printf("BHQ_Protocol_Process: cmdid:%d\r\n",cmdid);
    uint8_t hid_data[32] = {0};

    switch(cmdid)
    {
        case 0x26:  // BHQ model return hid led lock sta
            dat[4] = dat[4];    // led lock sta
            ackCommonNotData(cmdid,0);
            BHQ_Sta_Handel(cmdid,&dat[4]);
            break;
        case 0x27:  // BHQ model return hid raw data 
            // data and length
            raw_hid_receive(&dat[5],dat[4]);  
            // km_printf("bhq return hid raw data:length:%d[%02x %02x %02x]\r\n",dat[5],dat[6],dat[7],dat[8]);
            // for (i = 0; i < length; i++)
            // {
            //     km_printf("%02x ",dat[i]);
            // }
            // km_printf("\r\n");
            break;
        case 0xA1:
        case 0xA2:
        case 0xA3:
        case 0xA4:
        case 0xA5:
        case 0xA7:
            buff_sta = dat[4];
            switch(buff_sta)
            {
                case 0:
                    report_buffer_set_retry(0);
                    report_buffer_set_inverval(DEFAULT_REPORT_INVERVAL_MS);
                break;
                case 1:
                    report_buffer_set_retry(0);
                    report_buffer_set_inverval(DEFAULT_REPORT_INVERVAL_MS + 5);
                break;
                case 2:
                    report_buffer_set_inverval(DEFAULT_REPORT_INVERVAL_MS + 10);
                break;
            }
            break;

        case 0x93:  //  BHQ model return [ble connect sta , ble pair sta...]
            BHQ_Sta_Handel(cmdid, &dat[4]);
            for (i = 0; i < length; i++)
            {
                km_printf("%02x ",dat[i]);
            }
            km_printf("\r\n");
            break;
        case 0x92:  // read module Info
        case 0xB1:
        case 0xB2:
            km_printf("ota:[");
            for (i = 0; i < length; i++)
            {
                hid_data[i] = dat[i];
                km_printf("%02x ",dat[i]);
            }
            km_printf("]\r\n");
            raw_hid_send(hid_data, 32);
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

    int16_t temp = BHQ_ReadData();
    if(temp == -1)
    {
        if(sync_timer_elapsed32(uartTimeoutBuffer) > 1500)
        {
            uartTimeoutBuffer = sync_timer_read32();
            if(index > 0)
            {
                index = 0;
                u_sta = 0;
                dataLength = 0;
                memset(buf, 0, PACKET_MAX_LEN);
            }
        }
        else
        {
            uartTimeoutBuffer = sync_timer_read32();
        }
        
    }
    else
    {
        wait_for_new_pkt = true;
    }

    if(wait_for_new_pkt == false)
    {
        return;
    }
    wait_for_new_pkt = false;
    bytedata = (uint8_t)temp;
    uartTimeoutBuffer = sync_timer_read32();
    km_printf("%02x ",bytedata);
    switch (u_sta)
    {
        case 0:
            if(bytedata == 0x5D)
            {
                index = 0;
                buf[index++] = bytedata;
                u_sta++;  
                km_printf("read 0x5d\r\n");
            }
            break;
        case 1:
            if(bytedata == 0x7E)
            {
                buf[index++] = bytedata;
                u_sta++;  
                km_printf("read 0x7E\r\n");
            }
            break;
        case 2:
            buf[index++] = bytedata;
            dataLength = 2 + 1 + bytedata + 2 + 1;  //  Frame Header2  + length1 + dataN + crc2 + Frame end1
            u_sta++;  
            km_printf("read bytedata:%d\r\n",dataLength);
            break;
        case 3:
            buf[index++] = bytedata;
            km_printf("%02x ",bytedata);
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
                km_printf("\r\n");
            }
            break;
    }
}


// 验证数据是否有效
uint8_t bhkVerify(uint8_t *dat, uint16_t length)
{
    uint8_t dataRead_length = 3 + dat[2];    // 两个帧头  一个长度 = 4 不包括帧头的长度
   km_printf("dataRead_length:%d \r\n",dataRead_length);

    uint16_t dataReadCrc = BHQ_BUILD_UINT16(dat[dataRead_length],dat[dataRead_length + 1]);
   km_printf("readCRCL %02x  readCRCH %02x \r\n",dat[dataRead_length],dat[dataRead_length + 1]);

    uint16_t dataSumCrc = bhkSumCrc(dat,dataRead_length) ;
   km_printf("readCRC %04x    sumCRC %04x \r\n", dataReadCrc, dataSumCrc);
   km_printf("readCRC %d    sumCRC %d \r\n", dataReadCrc, dataSumCrc);


    if(dat[0] != BHQ_FRAME_HEADER_1 || dat[1] != BHQ_FRAME_HEADER_2)
    {
       km_printf("Verify: FRAME_HEADER error !! \r\n");
        return 0x01;
    }

    if(dataReadCrc != dataSumCrc)
    {
       km_printf("Verify: CRC error !! \r\n");

        return 0x02;
    }

    if(dat[dataRead_length + 2] != BHQ_FRAME_END_1)  // 跳过两个校验和就到帧尾了
    {
       km_printf("Verify: FRAME_END error !! \r\n");
        return 0x03;
    }
   km_printf("Verify: data success !! \r\n");
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
