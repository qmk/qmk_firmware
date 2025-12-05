/* Copyright 2024 Finalkey
 * Copyright 2024 LiWenLiu <https://github.com/LiuLiuQMK>
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
#include "rdmctmzt_common.h"

uint8_t Led_Colour_Tab[9][3] = {{255, 0, 0}, {255, 128, 0}, {255, 255, 0}, {0, 255, 0}, {0, 255, 255}, {0, 0, 255}, {128, 0, 255}, {255, 255, 255}};

uint8_t Led_Wave_Pwm_Tab[128] = {
    0,   4,   8,   12,  16,  20,  24,  28,  32,  36,  40,  44,  48,  52,  56,  60,  64,  68,  72,  76,  80,  84,  88,  92,  96,  100, 104, 108, 112, 116, 120, 124, 128, 132, 136, 140, 144, 148, 152, 156, 160, 164, 168, 172, 176, 180, 184, 188, 192, 196, 200, 204, 208, 212, 216, 220, 224, 228, 232, 236, 240, 244, 248, 255,

    255, 248, 244, 240, 236, 232, 228, 224, 220, 216, 212, 208, 204, 200, 196, 192, 188, 184, 180, 176, 172, 168, 164, 160, 156, 152, 148, 144, 140, 136, 132, 128, 124, 120, 116, 112, 108, 104, 100, 96,  92,  88,  84,  80,  76,  72,  68,  64,  60,  56,  52,  48,  44,  40,  36,  32,  28,  24,  20,  16,  12,  8,   4,   0,
};

#define ES_PWM_LED_SIZE (42)
#define ES_PWM_LED_BYTE (24)
#define ES_PWM_DMA_SIZE (ES_PWM_LED_SIZE * ES_PWM_LED_BYTE)

#define ES_PWM_WS2812_H_VALUE (43)
#define ES_PWM_WS2812_L_VALUE (17)

rgb_led_t                     rgb_matrix_ws2812_array[RGB_MATRIX_LED_COUNT];
uint8_t                       g_es_pwm_rgb_matrix_array_dma_buf[(RGB_MATRIX_LED_COUNT * ES_PWM_LED_BYTE) + 2] = {0};
md_dma_channel_config_typedef DMA_list[5]                                                                     = {0};

void rgb_matrix_driver_init(void) {
    md_rcu_enable_dma1(RCU);
    md_dma_set_configuration(DMA1, ENABLE);

    md_rcu_enable_gp16c2t1(RCU);
    md_timer_set_auto_reload_value_arrv(GP16C2T1, 60);
    md_timer_set_output_compare1_mode_ch1mod(GP16C2T1, MD_TIMER_OUTPUTMODE_PWMMODE1);
    md_timer_set_capture_compare1_value_ccrv1(GP16C2T1, 0);
    md_timer_enable_cc1_output_cc1en(GP16C2T1);
    md_timer_enable_main_output_goen(GP16C2T1);

    md_timer_enable_output_compare1_preload_ch1pen(GP16C2T1);
    md_timer_enable_dma_upd(GP16C2T1);
    md_timer_enable_counter_cnten(GP16C2T1);

    gpio_set_pin_output(ES_PWM_DMA_IO);

    GPIOA->AFL &= 0xFFFFF0FF;
    GPIOA->AFL |= 0x00000500;

    GPIOA->MOD &= 0xFFFFFFCF;
    GPIOA->MOD |= 0x00000020;

    md_dma_set_request_peripherals(DMA1, MD_DMA_CHANNEL2, MD_DMA_PRS_GP16C2T1_UP);

    if (rgb_matrix_get_val() <= 0) {
        memset((void *)g_es_pwm_rgb_matrix_array_dma_buf, ES_PWM_WS2812_L_VALUE, (RGB_MATRIX_LED_COUNT * ES_PWM_LED_BYTE) + 2);
    }
}

void User_Pwm_Deinit(void) {
    md_rcu_enable_gp16c2t1_reset(RCU);
    md_rcu_disable_gp16c2t1_reset(RCU);
    md_rcu_disable_gp16c2t1(RCU);
    md_rcu_enable_dma1_reset(RCU);
    md_rcu_disable_dma1_reset(RCU);
    md_rcu_disable_dma1(RCU);

    gpio_set_pin_output(ES_PWM_DMA_IO);
    gpio_write_pin_low(ES_PWM_DMA_IO);
}

void rgb_matrix_driver_flush_pwm_dma_start(void) {
    while ((DMA1->CHENSET) & 0x4)
        ;

    if (Keyboard_Status.System_Sleep_Mode || ((Keyboard_Info.Key_Mode != QMK_USB_MODE) && Usb_Change_Mode_Wakeup && Keyboard_Status.System_Work_Status) || (!Led_Power_Up)) {
        Led_Off_Start = true;
        gpio_write_pin_low(ES_LED_POWER_IO);
        return;
    }

    // Keep LED power on if either RGB matrix OR logo LEDs are enabled
    bool leds_active = rgb_matrix_is_enabled();
#if LOGO_LED_ENABLE
    leds_active = leds_active || Keyboard_Info.Logo_On_Off;
#endif

    if (leds_active) {
        gpio_write_pin_high(ES_LED_POWER_IO);
        if (Led_Off_Start) {
            Led_Off_Start = false;
            wait_ms(3);
        }
    } else {
        Led_Off_Start = true;
        gpio_write_pin_low(ES_LED_POWER_IO);
    }

    md_timer_disable_dma_upd(GP16C2T1);

    g_es_pwm_rgb_matrix_array_dma_buf[(RGB_MATRIX_LED_COUNT * ES_PWM_LED_BYTE)]     = 0;
    g_es_pwm_rgb_matrix_array_dma_buf[(RGB_MATRIX_LED_COUNT * ES_PWM_LED_BYTE) + 1] = 0;

#if (RGB_MATRIX_LED_COUNT <= 42)
    uint16_t Data_Size                       = ((RGB_MATRIX_LED_COUNT * ES_PWM_LED_BYTE) + 2);
    DMA_list[0].control.word                 = ((Data_Size - 1) << 4) | g_es_dma_ch2alt_cfg;
    DMA_list[0].source_data_end_address      = (uint32_t)(g_es_pwm_rgb_matrix_array_dma_buf + (Data_Size - 1));
    DMA_list[0].destination_data_end_address = (uint32_t)(&(GP16C2T1->CCVAL1));

    DMA1->PRI_CH02_SRC_DATA_END_PTR = ((uint32_t)(DMA_list)) + ((16 - 4));
    DMA1->PRI_CH02_CHANNEL_CFG      = ((4 - 1) << 4) | g_es_dma_ch2pri_cfg;
#elif (RGB_MATRIX_LED_COUNT <= 84)
    DMA_list[0].control.word                 = ((ES_PWM_DMA_SIZE - 1) << 4) | g_es_dma_ch2alt_cfg;
    DMA_list[0].source_data_end_address      = (uint32_t)(g_es_pwm_rgb_matrix_array_dma_buf + (ES_PWM_DMA_SIZE - 1));
    DMA_list[0].destination_data_end_address = (uint32_t)(&(GP16C2T1->CCVAL1));

    uint16_t Data_Size                       = (((RGB_MATRIX_LED_COUNT - ES_PWM_LED_SIZE) * ES_PWM_LED_BYTE) + 2);
    DMA_list[1].control.word                 = ((Data_Size - 1) << 4) | g_es_dma_ch2alt_cfg;
    DMA_list[1].source_data_end_address      = (uint32_t)(g_es_pwm_rgb_matrix_array_dma_buf + (ES_PWM_DMA_SIZE + Data_Size - 1));
    DMA_list[1].destination_data_end_address = (uint32_t)(&(GP16C2T1->CCVAL1));

    DMA1->PRI_CH02_SRC_DATA_END_PTR = ((uint32_t)(DMA_list)) + ((32 - 4));
    DMA1->PRI_CH02_CHANNEL_CFG      = ((8 - 1) << 4) | g_es_dma_ch2pri_cfg;
#elif (RGB_MATRIX_LED_COUNT <= 126)
    DMA_list[0].control.word                 = ((ES_PWM_DMA_SIZE - 1) << 4) | g_es_dma_ch2alt_cfg;
    DMA_list[0].source_data_end_address      = (uint32_t)(g_es_pwm_rgb_matrix_array_dma_buf + (ES_PWM_DMA_SIZE - 1));
    DMA_list[0].destination_data_end_address = (uint32_t)(&(GP16C2T1->CCVAL1));

    DMA_list[1].control.word                 = ((ES_PWM_DMA_SIZE - 1) << 4) | g_es_dma_ch2alt_cfg;
    DMA_list[1].source_data_end_address      = (uint32_t)(g_es_pwm_rgb_matrix_array_dma_buf + ((ES_PWM_DMA_SIZE * 2) - 1));
    DMA_list[1].destination_data_end_address = (uint32_t)(&(GP16C2T1->CCVAL1));

    uint16_t Data_Size                       = (((RGB_MATRIX_LED_COUNT - (ES_PWM_LED_SIZE * 2)) * ES_PWM_LED_BYTE) + 2);
    DMA_list[2].control.word                 = ((Data_Size - 1) << 4) | g_es_dma_ch2alt_cfg;
    DMA_list[2].source_data_end_address      = (uint32_t)(g_es_pwm_rgb_matrix_array_dma_buf + ((ES_PWM_DMA_SIZE * 2) + Data_Size - 1));
    DMA_list[2].destination_data_end_address = (uint32_t)(&(GP16C2T1->CCVAL1));

    DMA1->PRI_CH02_SRC_DATA_END_PTR = ((uint32_t)(DMA_list)) + ((48 - 4));
    DMA1->PRI_CH02_CHANNEL_CFG      = ((12 - 1) << 4) | g_es_dma_ch2pri_cfg;
#elif (RGB_MATRIX_LED_COUNT <= 168)
    DMA_list[0].control.word                 = ((ES_PWM_DMA_SIZE - 1) << 4) | g_es_dma_ch2alt_cfg;
    DMA_list[0].source_data_end_address      = (uint32_t)(g_es_pwm_rgb_matrix_array_dma_buf + (ES_PWM_DMA_SIZE - 1));
    DMA_list[0].destination_data_end_address = (uint32_t)(&(GP16C2T1->CCVAL1));

    DMA_list[1].control.word                 = ((ES_PWM_DMA_SIZE - 1) << 4) | g_es_dma_ch2alt_cfg;
    DMA_list[1].source_data_end_address      = (uint32_t)(g_es_pwm_rgb_matrix_array_dma_buf + ((ES_PWM_DMA_SIZE * 2) - 1));
    DMA_list[1].destination_data_end_address = (uint32_t)(&(GP16C2T1->CCVAL1));

    DMA_list[2].control.word                 = ((ES_PWM_DMA_SIZE - 1) << 4) | g_es_dma_ch2alt_cfg;
    DMA_list[2].source_data_end_address      = (uint32_t)(g_es_pwm_rgb_matrix_array_dma_buf + ((ES_PWM_DMA_SIZE * 3) - 1));
    DMA_list[2].destination_data_end_address = (uint32_t)(&(GP16C2T1->CCVAL1));

    uint16_t Data_Size                       = (((RGB_MATRIX_LED_COUNT - (ES_PWM_LED_SIZE * 3)) * ES_PWM_LED_BYTE) + 2);
    DMA_list[3].control.word                 = ((Data_Size - 1) << 4) | g_es_dma_ch2alt_cfg;
    DMA_list[3].source_data_end_address      = (uint32_t)(g_es_pwm_rgb_matrix_array_dma_buf + ((ES_PWM_DMA_SIZE * 3) + Data_Size - 1));
    DMA_list[3].destination_data_end_address = (uint32_t)(&(GP16C2T1->CCVAL1));

    DMA1->PRI_CH02_SRC_DATA_END_PTR = ((uint32_t)(DMA_list)) + ((64 - 4));
    DMA1->PRI_CH02_CHANNEL_CFG      = ((16 - 1) << 4) | g_es_dma_ch2pri_cfg;
#endif

    DMA1->PRI_CH02_DST_DATA_END_PTR = ((uint32_t)(&(DMA1->ALT_CH02_SRC_DATA_END_PTR))) + 16 - 4;
    DMA1->CHENSET                   = 0x4;
    md_timer_enable_dma_upd(GP16C2T1);
}

void rgb_matrix_driver_flush(void) {
    Led_Flash_Busy = false;
    if ((GP16C2T1->AR) != 60) {
        rgb_matrix_driver_init();
    }

    rgb_matrix_driver_flush_pwm_dma_start();
}

void rgb_matrix_driver_set_color(int index, uint8_t r, uint8_t g, uint8_t b) {
    uint8_t *buf;

    if (index == (RGB_MATRIX_LED_COUNT - 1)) {
        Led_Flash_Busy = false;
    } else if (index == 0) {
        Led_Flash_Busy = true;
    }

    if (rgb_matrix_ws2812_array[index].r == r && rgb_matrix_ws2812_array[index].g == g && rgb_matrix_ws2812_array[index].b == b) {
        return;
    }

    rgb_matrix_ws2812_array[index].r = r;
    rgb_matrix_ws2812_array[index].g = g;
    rgb_matrix_ws2812_array[index].b = b;

    buf = g_es_pwm_rgb_matrix_array_dma_buf + (index * 24);

    for (unsigned char bit = 0; bit < 8; bit++) {
        bool is_one = g & (1 << (7 - bit));
        // using something like wait_ns(is_one ? T1L : T0L) here throws off timings

        *buf = (is_one) ? ES_PWM_WS2812_H_VALUE : ES_PWM_WS2812_L_VALUE;
        buf++;
    }

    for (unsigned char bit = 0; bit < 8; bit++) {
        bool is_one = r & (1 << (7 - bit));
        // using something like wait_ns(is_one ? T1L : T0L) here throws off timings

        *buf = (is_one) ? ES_PWM_WS2812_H_VALUE : ES_PWM_WS2812_L_VALUE;
        buf++;
    }

    for (unsigned char bit = 0; bit < 8; bit++) {
        bool is_one = b & (1 << (7 - bit));
        // using something like wait_ns(is_one ? T1L : T0L) here throws off timings

        *buf = (is_one) ? ES_PWM_WS2812_H_VALUE : ES_PWM_WS2812_L_VALUE;
        buf++;
    }
}

void rgb_matrix_driver_set_color_all(uint8_t r, uint8_t g, uint8_t b) {
    for (uint32_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        rgb_matrix_driver_set_color(i, r, g, b);
    }
}

// clang-format off
const rgb_matrix_driver_t rgb_matrix_driver = {
    .init          = rgb_matrix_driver_init,
    .flush         = rgb_matrix_driver_flush,
    .set_color     = rgb_matrix_driver_set_color,
    .set_color_all = rgb_matrix_driver_set_color_all,
};
