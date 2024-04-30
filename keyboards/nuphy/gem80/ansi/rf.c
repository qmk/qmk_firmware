/*
Copyright 2023 @ Nuphy <https://nuphy.com/>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdint.h>
#include "user_kb.h"
#include "uart.h" // qmk uart.h
#include "rf_queue.h"

USART_MGR_STRUCT Usart_Mgr;
// clang-format off
#define RX_SBYTE Usart_Mgr.RXDBuf[0]
#define RX_CMD   Usart_Mgr.RXDBuf[1]
#define RX_ACK   Usart_Mgr.RXDBuf[2]
#define RX_LEN   Usart_Mgr.RXDBuf[3]
#define RX_DAT   Usart_Mgr.RXDBuf[4]
// clang-format on

bool f_uart_ack        = 0;
bool f_rf_read_data_ok = 0;
bool f_rf_sts_sysc_ok  = 0;
bool f_rf_new_adv_ok   = 0;
bool f_rf_reset        = 0;
bool f_rf_hand_ok      = 0;
bool f_goto_sleep      = 0;
bool f_wakeup_prepare  = 0;

uint8_t  func_tab[32]     = {0};
uint8_t  sync_lost        = 0;
uint8_t  disconnect_delay = 0;
uint32_t uart_rpt_timer   = 0;

report_buffer_t report_buff_a = {0};
report_buffer_t report_buff_b = {0};

extern DEV_INFO_STRUCT dev_info;
extern host_driver_t  *m_host_driver;
extern host_driver_t   rf_host_driver;
extern rf_queue_t      rf_queue;
extern uint8_t         host_mode;
extern uint8_t         rf_blink_cnt;
extern uint16_t        rf_link_show_time;
extern uint16_t        rf_linking_time;
extern uint32_t        no_act_time;
extern bool            f_send_channel;
extern bool            f_dial_sw_init_ok;

void    uart_init(uint32_t baud); // qmk uart.c
void    uart_send_report(uint8_t report_type, uint8_t *report_buf, uint8_t report_size);
void    uart_send_bytes(uint8_t *Buffer, uint32_t Length);
uint8_t get_checksum(uint8_t *buf, uint8_t len);
void    uart_receive_pro(void);
void    break_all_key(void);

/**
 * @brief Get variable uart key send repeat interval.
 */
static uint8_t get_repeat_interval(void) {
    uint8_t interval = MAX(report_buff_a.repeat, report_buff_b.repeat);
    if (interval == 0) {
        return 50;
    } else if (interval <= 4) {
        return 8;
    } else if (interval <= 7) {
        return 12;
    } else if (interval <= 10) {
        return 14;
    }
    return 25;
}

/**
 * @brief Reset report buffers.
 */
void clear_report_buffer(void) {
    if (report_buff_a.cmd) memset(&report_buff_a.cmd, 0, sizeof(report_buffer_t));
    if (report_buff_b.cmd) memset(&report_buff_b.cmd, 0, sizeof(report_buffer_t));
    rf_queue.clear();
}

/**
 * @brief Reset report buffers and clear the queue
 */
void clear_report_buffer_and_queue(void) {
    clear_report_buffer();
    rf_queue.clear();
}

/**
 * @brief Repeating reports from queue.
 */
void uart_send_repeat_from_queue(void) {
    static uint32_t        dequeue_timer = 0;
    static uint32_t        repeat_timer  = 0;
    static report_buffer_t report_buff   = {0};
    static bool            do_repeat     = true;
    if (timer_elapsed32(dequeue_timer) > 25 && !rf_queue.is_empty()) {
        rf_queue.dequeue(&report_buff);
        dequeue_timer = timer_read32();
        // Repeat only keyboard reports. Extra reports actually repeat the keys.
        do_repeat = (report_buff.cmd == CMD_RPT_BYTE_KB || report_buff.cmd == CMD_RPT_BIT_KB);
    }

    // queue is empty, continue sending from standard process.
    if (rf_queue.is_empty()) {
        clear_report_buffer_and_queue();
        if (do_repeat) report_buff_a = report_buff;
    }

    if (report_buff.repeat == 0 || (do_repeat && timer_elapsed32(repeat_timer) > 3)) {
        uart_send_report(report_buff.cmd, report_buff.buffer, report_buff.length);
        // report_buff.repeat++; // FIXME: probably cause of non sleeping on conn timeout
        repeat_timer = timer_read32();
    }
}

/**
 * @brief  Uart send keys report.
 * @note   Repeats the last sent key reports periodically to reduce stuck keys.
 */
void uart_send_report_repeat(void) {
    if (dev_info.link_mode == LINK_USB) return;

    if (dev_info.rf_state != RF_CONNECT) {
        // toss away queue after some time if disconnected to prevent sending random keys
        if (no_act_time > 100) clear_report_buffer_and_queue(); // 1 second
        return;
    }

    // queue is not empty, send from queue.
    if (!rf_queue.is_empty()) {
        uart_send_repeat_from_queue();
        return;
    }

    uint8_t interval = get_repeat_interval();
    if (timer_elapsed32(uart_rpt_timer) >= interval) {
        if (no_act_time <= 25) { // increments every 10ms
            if (report_buff_a.cmd) {
                uart_send_report(report_buff_a.cmd, report_buff_a.buffer, report_buff_a.length);
                report_buff_a.repeat++;
            }

            if (report_buff_b.cmd) {
                uart_send_report(report_buff_b.cmd, report_buff_b.buffer, report_buff_b.length);
                report_buff_b.repeat++;
            }
        } else { // clear the report buffer
            clear_report_buffer_and_queue();
        }
        uart_rpt_timer = timer_read32();
    }
}

/**
 * @brief  Parsing the data received from the RF module.
 */
void rf_protocol_receive(void) {
    uint8_t i, check_sum = 0;

    if (Usart_Mgr.RXDState == RX_Done) {
        sync_lost = 0;

        if (RX_LEN >= UART_MAX_LEN - 4) { // is this possible? Playing it safe for undefined behaviour.
            Usart_Mgr.RXDState = RX_DATA_ERR;
            return;
        } else if (Usart_Mgr.RXDLen > 4) {
            for (i = 0; i < RX_LEN; i++)
                check_sum += Usart_Mgr.RXDBuf[4 + i];

            if (check_sum != Usart_Mgr.RXDBuf[4 + i]) {
                Usart_Mgr.RXDState = RX_SUM_ERR;
                return;
            }
        } else if (Usart_Mgr.RXDLen == 3) {
            if (Usart_Mgr.RXDBuf[2] == 0xA0) { // Only some commands send an ACK.
                f_uart_ack = 1;
            }
        }

        Usart_Mgr.RXCmd = RX_CMD;

        switch (RX_CMD) {
            case CMD_HAND: {
                f_rf_hand_ok = 1;
                break;
            }

            case CMD_24G_SUSPEND: {
                f_goto_sleep = 1;
                break;
            }

            case CMD_NEW_ADV: {
                f_rf_new_adv_ok = 1;
                break;
            }

            case CMD_RF_STS_SYSC: {
                static uint8_t error_cnt = 0;

                if (dev_info.link_mode == Usart_Mgr.RXDBuf[4]) {
                    error_cnt = 0;

                    dev_info.rf_state = Usart_Mgr.RXDBuf[5];

                    if ((dev_info.rf_state == RF_CONNECT) && ((Usart_Mgr.RXDBuf[6] & 0xf8) == 0)) {
                        dev_info.rf_led = Usart_Mgr.RXDBuf[6];
                    }

                    if ((Usart_Mgr.RXDBuf[7] & 0xfc) == 0) dev_info.rf_charge = Usart_Mgr.RXDBuf[7];

                    if (Usart_Mgr.RXDBuf[8] <= 100) dev_info.rf_battery = Usart_Mgr.RXDBuf[8];
                    // dev_info.rf_charge = Usart_Mgr.RXDBuf[7];
                    if (dev_info.rf_battery > 0 && dev_info.rf_battery <= 100) {
                        update_bat_pct_rgb();
                    }

                } else {
                    if (dev_info.rf_state != RF_INVAILD) {
                        if (error_cnt >= 5) {
                            error_cnt      = 0;
                            f_send_channel = 1;
                        } else {
                            error_cnt++;
                        }
                    }
                }

                f_rf_sts_sysc_ok = 1;
                break;
            }

            case CMD_READ_DATA: {
                memcpy(func_tab, &Usart_Mgr.RXDBuf[4], 32);

                if (func_tab[4] <= LINK_USB) {
                    dev_info.link_mode = func_tab[4];
                }

                if (func_tab[5] < LINK_USB) {
                    dev_info.rf_channel = func_tab[5];
                }

                if ((func_tab[6] <= LINK_BT_3) && (func_tab[6] >= LINK_BT_1)) {
                    dev_info.ble_channel = func_tab[6];
                }

                f_rf_read_data_ok = 1;
                break;
            }
            default:
                Usart_Mgr.RXDState = RX_CMD_ERR;
                return;
        }

        Usart_Mgr.RXDLen      = 0;
        Usart_Mgr.RXDState    = RX_Idle;
        Usart_Mgr.RXDOverTime = 0;
    }
}

/**
 * @brief  Uart send cmd.
 * @param  cmd: cmd.
 * @param  wait_ack: wait time for ack after sending.
 * @param  delayms: delay before sending.
 */
uint8_t uart_send_cmd(uint8_t cmd, uint8_t wait_ack, uint8_t delayms) {
    uint8_t i;
    wait_ms(delayms);

    memset(&Usart_Mgr.TXDBuf[0], 0, UART_MAX_LEN);

    Usart_Mgr.TXDBuf[0] = UART_HEAD;
    Usart_Mgr.TXDBuf[1] = cmd;
    Usart_Mgr.TXDBuf[2] = 0x00;

    switch (cmd) {
        case CMD_POWER_UP: {
            Usart_Mgr.TXDBuf[3] = 1;
            Usart_Mgr.TXDBuf[4] = 0;
            Usart_Mgr.TXDBuf[5] = 0;
            break;
        }
        case CMD_SNIF: {
            Usart_Mgr.TXDBuf[3] = 1;
            Usart_Mgr.TXDBuf[4] = 0;
            Usart_Mgr.TXDBuf[5] = 0;
            break;
        }
        case CMD_SLEEP: {
            Usart_Mgr.TXDBuf[3] = 1;
            Usart_Mgr.TXDBuf[4] = 0;
            Usart_Mgr.TXDBuf[5] = 0;
            break;
        }

        case CMD_HAND: {
            Usart_Mgr.TXDBuf[3] = 1;
            Usart_Mgr.TXDBuf[4] = 0;
            Usart_Mgr.TXDBuf[5] = 0;
            break;
        }

        case CMD_RF_STS_SYSC: {
            Usart_Mgr.TXDBuf[3] = 1;
            Usart_Mgr.TXDBuf[4] = dev_info.link_mode;
            Usart_Mgr.TXDBuf[5] = dev_info.link_mode;
            break;
        }

        case CMD_SET_LINK: {
            dev_info.rf_state   = RF_LINKING;
            Usart_Mgr.TXDBuf[3] = 1;
            Usart_Mgr.TXDBuf[4] = dev_info.link_mode;
            Usart_Mgr.TXDBuf[5] = dev_info.link_mode;

            rf_linking_time  = 0;
            disconnect_delay = 0xff;
            break;
        }

        case CMD_NEW_ADV: {
            dev_info.rf_state   = RF_PAIRING;
            Usart_Mgr.TXDBuf[3] = 2;
            Usart_Mgr.TXDBuf[4] = dev_info.link_mode;
            Usart_Mgr.TXDBuf[5] = 1;
            Usart_Mgr.TXDBuf[6] = dev_info.link_mode + 1;

            rf_linking_time  = 0;
            disconnect_delay = 0xff;
            f_rf_new_adv_ok  = 0;
            break;
        }

        case CMD_CLR_DEVICE: {
            Usart_Mgr.TXDBuf[3] = 1;
            Usart_Mgr.TXDBuf[4] = 0;
            Usart_Mgr.TXDBuf[5] = 0;
            break;
        }

        case CMD_SET_CONFIG: {
            Usart_Mgr.TXDBuf[3] = 1;
            Usart_Mgr.TXDBuf[4] = POWER_DOWN_DELAY;
            Usart_Mgr.TXDBuf[5] = POWER_DOWN_DELAY;
            break;
        }

        case CMD_SET_NAME: {
            Usart_Mgr.TXDBuf[3]  = 14;                                                      // data len
            Usart_Mgr.TXDBuf[4]  = 1;                                                       // type
            Usart_Mgr.TXDBuf[5]  = 12;                                                      // data: ble name len
            Usart_Mgr.TXDBuf[6]  = 'N';                                                     // data: ble name
            Usart_Mgr.TXDBuf[7]  = 'u';                                                     // data: ble name
            Usart_Mgr.TXDBuf[8]  = 'P';                                                     // data: ble name
            Usart_Mgr.TXDBuf[9]  = 'h';                                                     // data: ble name
            Usart_Mgr.TXDBuf[10] = 'y';                                                     // data: ble name
            Usart_Mgr.TXDBuf[11] = ' ';                                                     // data: ble name
            Usart_Mgr.TXDBuf[12] = 'G';                                                     // data: ble name
            Usart_Mgr.TXDBuf[13] = 'e';                                                     // data: ble name
            Usart_Mgr.TXDBuf[14] = 'm';                                                     // data: ble name
            Usart_Mgr.TXDBuf[15] = '8';                                                     // data: ble name
            Usart_Mgr.TXDBuf[16] = '0';                                                     // data: ble name
            Usart_Mgr.TXDBuf[17] = '-';                                                     // data: ble name
            Usart_Mgr.TXDBuf[18] = get_checksum(Usart_Mgr.TXDBuf + 4, Usart_Mgr.TXDBuf[3]); // sum
            break;
        }

        case CMD_SET_24G_NAME: {
            Usart_Mgr.TXDBuf[3]  = 38;
            Usart_Mgr.TXDBuf[4]  = 38;
            Usart_Mgr.TXDBuf[5]  = 3;
            Usart_Mgr.TXDBuf[6]  = 'N';
            Usart_Mgr.TXDBuf[8]  = 'u';
            Usart_Mgr.TXDBuf[10] = 'P';
            Usart_Mgr.TXDBuf[12] = 'h';
            Usart_Mgr.TXDBuf[14] = 'y';
            Usart_Mgr.TXDBuf[16] = ' ';
            Usart_Mgr.TXDBuf[18] = 'G';
            Usart_Mgr.TXDBuf[20] = 'e';
            Usart_Mgr.TXDBuf[22] = 'm';
            Usart_Mgr.TXDBuf[24] = '8';
            Usart_Mgr.TXDBuf[26] = '0';
            Usart_Mgr.TXDBuf[28] = ' ';
            Usart_Mgr.TXDBuf[30] = 'D';
            Usart_Mgr.TXDBuf[32] = 'o';
            Usart_Mgr.TXDBuf[34] = 'n';
            Usart_Mgr.TXDBuf[36] = 'g';
            Usart_Mgr.TXDBuf[38] = 'l';
            Usart_Mgr.TXDBuf[40] = 'e';
            Usart_Mgr.TXDBuf[42] = get_checksum(Usart_Mgr.TXDBuf + 4, Usart_Mgr.TXDBuf[3]); // sum
            break;
        }

        case CMD_READ_DATA: {
            Usart_Mgr.TXDBuf[3] = 2;
            Usart_Mgr.TXDBuf[4] = 0x00;
            Usart_Mgr.TXDBuf[5] = FUNC_VALID_LEN;
            Usart_Mgr.TXDBuf[6] = FUNC_VALID_LEN;
            break;
        }

        case CMD_WRITE_DATA: {
            func_tab[4] = dev_info.link_mode;
            func_tab[5] = dev_info.rf_channel;
            func_tab[6] = dev_info.ble_channel;

            Usart_Mgr.TXDBuf[3] = FUNC_VALID_LEN + 2;
            Usart_Mgr.TXDBuf[4] = 0;
            Usart_Mgr.TXDBuf[5] = FUNC_VALID_LEN;

            for (i = 0; i < FUNC_VALID_LEN; i++) {
                Usart_Mgr.TXDBuf[6 + i] = func_tab[i];
            }
            Usart_Mgr.TXDBuf[6 + i] = get_checksum(func_tab, FUNC_VALID_LEN);
            Usart_Mgr.TXDBuf[6 + i] += 0;
            Usart_Mgr.TXDBuf[6 + i] += FUNC_VALID_LEN;
            break;
        }

        case CMD_RF_DFU: {
            Usart_Mgr.TXDBuf[3] = 1;
            Usart_Mgr.TXDBuf[4] = 0;
            Usart_Mgr.TXDBuf[5] = 0;
            break;
        }

        default:
            break;
    }

    f_uart_ack = 0;
    uart_send_bytes(Usart_Mgr.TXDBuf, Usart_Mgr.TXDBuf[3] + 5);

    if (wait_ack) {
        while (wait_ack--) {
            wait_ms(1);
            uart_receive_pro();
            if (f_uart_ack || Usart_Mgr.RXCmd == cmd) return TX_OK;
        }
    } else {
        return TX_OK;
    }

    return TX_TIMEOUT;
}

/**
 * @brief RF module state sync.
 */
void dev_sts_sync(void) {
    static uint32_t interval_timer  = 0;
    static uint8_t  link_state_temp = RF_DISCONNECT;

    if (timer_elapsed32(interval_timer) < 200) return;
    interval_timer = timer_read32();

    if (f_rf_reset) {
        f_rf_reset = 0;
        wait_ms(100);
        writePinLow(NRF_RESET_PIN);
        wait_ms(50);
        writePinHigh(NRF_RESET_PIN);
        wait_ms(50);
    } else if (f_send_channel) {
        f_send_channel = 0;
        uart_send_cmd(CMD_SET_LINK, 10, 10);
    }

    if (dev_info.link_mode == LINK_USB) {
        if (host_mode != HOST_USB_TYPE) {
            host_mode = HOST_USB_TYPE;
            break_all_key();
            host_set_driver(m_host_driver);
        }
        rf_blink_cnt = 0;
    } else {
        if (host_mode != HOST_RF_TYPE) {
            host_mode = HOST_RF_TYPE;
            break_all_key();
            host_set_driver(&rf_host_driver);
        }

        if (dev_info.rf_state != RF_CONNECT) {
            if (disconnect_delay >= 10) {
                rf_blink_cnt      = 3;
                rf_link_show_time = 0;
                link_state_temp   = dev_info.rf_state;
            } else {
                disconnect_delay++;
            }
        } else if (dev_info.rf_state == RF_CONNECT) {
            rf_linking_time  = 0;
            disconnect_delay = 0;
            rf_blink_cnt     = 0;

            if (link_state_temp != RF_CONNECT) {
                link_state_temp   = RF_CONNECT;
                rf_link_show_time = 0;
            }
        }
    }

    uart_send_cmd(CMD_RF_STS_SYSC, 1, 0);

    /* reset report repeat timer, might reduce repeat keys? */
    uart_rpt_timer = timer_read32();

    if (dev_info.link_mode != LINK_USB) {
        if (++sync_lost >= 5) {
            sync_lost  = 0;
            f_rf_reset = 1;
        }
    }
}

/**
 * @brief Uart send bytes.
 * @param Buffer data buf
 * @param Length data length
 */
void uart_send_bytes(uint8_t *Buffer, uint32_t Length) {
    Usart_Mgr.RXCmd = CMD_NULL; // reset before command sends.
    // Restrict to one command per ms for stability?
    if (timer_elapsed32(Usart_Mgr.TXLastCmdTm) < 1) {
        wait_ms(1);
    }
    writePinLow(NRF_WAKEUP_PIN);
    wait_us(50);
    uart_transmit(Buffer, Length);
    wait_us(50 + Length * 30);
    writePinHigh(NRF_WAKEUP_PIN);
    wait_us(200);
    Usart_Mgr.TXLastCmdTm = timer_read32();
}

/**
 * @brief get checksum.
 * @param buf data buf
 * @param len data length
 */
uint8_t get_checksum(uint8_t *buf, uint8_t len) {
    uint8_t i;
    uint8_t checksum = 0;

    for (i = 0; i < len; i++)
        checksum += *buf++;

    checksum ^= UART_HEAD;

    return checksum;
}

/**
 * @brief Uart send report.
 * @param report_type  report_type
 * @param report_buf  report_buf
 * @param report_size  report_size
 */
void uart_send_report(uint8_t report_type, uint8_t *report_buf, uint8_t report_size) {
    if (f_dial_sw_init_ok == 0) return;
    if (dev_info.link_mode == LINK_USB) return;
    if (dev_info.rf_state != RF_CONNECT) return;

    Usart_Mgr.TXDBuf[0] = UART_HEAD;
    Usart_Mgr.TXDBuf[1] = report_type;
    Usart_Mgr.TXDBuf[2] = 0x01;
    Usart_Mgr.TXDBuf[3] = report_size;

    memcpy(&Usart_Mgr.TXDBuf[4], report_buf, report_size);
    Usart_Mgr.TXDBuf[4 + report_size] = get_checksum(&Usart_Mgr.TXDBuf[4], report_size);

    uart_send_bytes(&Usart_Mgr.TXDBuf[0], report_size + 5);

    uart_rpt_timer = timer_read32(); // reset uart repeat timer.
}

/**
 * @brief Uart receives data and processes it after completion,.
 */
void uart_receive_pro(void) {
    static bool     rcv_start = false;
    static uint32_t rcv_timer = 0;

    // Process at most once every ms between last iteration/transaction sent.
    if (timer_elapsed32(Usart_Mgr.TXLastCmdTm) < 1 || timer_elapsed32(rcv_timer) < 1) return;

    // If there's any data, wait a bit first then process it all.
    // If you don't do this, you may lose sync, and crash the board.
    if (uart_available()) {
        wait_us(200);
        // Receiving serial data from RF module
        while (uart_available()) {
            uint8_t byte = uart_read();
            if (byte == UART_HEAD) { // valid UART transaction always begins with 0x5A
                rcv_start = true;
            }
            // only read in what's valid. and drop the rest.
            if (rcv_start && Usart_Mgr.RXDLen < UART_MAX_LEN) {
                Usart_Mgr.RXDBuf[Usart_Mgr.RXDLen++] = byte;
            }

            // don't do any waits in here, board seems to crash.
        }

        // Processing received serial port protocol
        if (rcv_start) {
            rcv_start          = false;
            Usart_Mgr.RXDState = RX_Done;
            rf_protocol_receive();
            Usart_Mgr.RXDLen = 0;
        }
    }
    rcv_timer = timer_read32();
}

/**
 * @brief  RF uart initial.
 */
void rf_uart_init(void) {
    /* set uart buad as 460800 */
    uart_init(460800);

    /* Enable parity check */
    USART1->CR1 &= ~((uint32_t)USART_CR1_UE);
    USART1->CR1 |= USART_CR1_M0 | USART_CR1_PCE;
    USART1->CR1 |= USART_CR1_UE;

    /* set Rx and Tx pin pull up */
    GPIOB->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR6 | GPIO_OSPEEDER_OSPEEDR7);
    GPIOB->PUPDR |= (GPIO_PUPDR_PUPDR6_0 | GPIO_PUPDR_PUPDR7_0);
}

/**
 * @brief RF module initial.
 */
void rf_device_init(void) {
    uint8_t timeout = 10;

    f_rf_hand_ok = 0;
    while (timeout--) {
        uart_send_cmd(CMD_HAND, 0, 20);
        wait_ms(5);
        uart_receive_pro();
        // uart_receive_pro();
        if (f_rf_hand_ok) break;
    }

    timeout           = 10;
    f_rf_read_data_ok = 0;
    while (timeout--) {
        uart_send_cmd(CMD_READ_DATA, 0, 20);
        wait_ms(5);
        uart_receive_pro();
        // uart_receive_pro();
        if (f_rf_read_data_ok) break;
    }

    timeout          = 10;
    f_rf_sts_sysc_ok = 0;
    while (timeout--) {
        uart_send_cmd(CMD_RF_STS_SYSC, 0, 20);
        wait_ms(5);
        uart_receive_pro();
        // uart_receive_pro();
        if (f_rf_sts_sysc_ok) break;
    }

    uart_send_cmd(CMD_SET_NAME, 10, 20);
    uart_send_cmd(CMD_SET_24G_NAME, 10, 20);
}
