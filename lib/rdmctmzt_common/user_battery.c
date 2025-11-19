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

uint16_t User_Adc_Batt[USER_BATT_SCAN_COUNT] = {0};
uint16_t User_Scan_Batt[USER_BATT_SCAN_COUNT] = {0};
uint8_t User_Adc_Batt_Count = 0U;
uint8_t User_Batt_BaiFen = 0U;
uint8_t User_Batt_Old_BaiFen = 0U;
uint8_t User_Batt_10ms_Count = 0x00;
uint16_t User_Batt_Time_15S_Count = 0U;
bool User_Batt_Power_Up = false;
bool User_Batt_Send_Spi = false;
uint16_t User_Batt_Power_Up_Delay_100ms_Count = 0U;
bool User_Batt_Power_Up_Delay = false;

bool User_Power_Low = false;
uint8_t User_Power_Low_Count = 0U;
uint8_t es_stdby_pin_state = 0U;


const md_adc_initial adc_initStruct =    /**< ADC init structure */
{
    MD_ADC_CFG_ALIGN_RIGHT,     //Data alignment
    MD_ADC_CFG_RSEL_12BIT,      //Data resolution
    MD_ADC_MODE_NCHS,           //Regular or Injected
    MD_ADC_CFG_CM_SINGLE,       //Single mode
    MD_ADC_NCHS1_NSL_1CON,      //sample count
    MD_ADC_SMPT1_CKDIV_DIV6,    //ADC prescale
};

ErrorStatus rdmctmzt_adc_software_calibration(ADC_TypeDef *ADCx, md_adc_initial *ADC_InitStruct) {
    //ADC input APB clock 12MHz
    uint8_t clkdiv = 8;
    uint16_t adc_data_1 = 0;
    uint16_t adc_data_15 = 0;

    int16_t adc_offset = 0;
    uint16_t adc_gain = 0;

    float temp_adc_offset = 0.0f;

    md_syscfg_set_vref_source(SYSCFG, MD_SYSCFG_PWR_VDDA); // VRES choose VDDA
    md_syscfg_enable_vref(SYSCFG);

    //ADC Setting
    md_adc_set_convsersion_mode(ADC, MD_ADC_CFG_CM_SINGLE);                 // 1:Continuous
    md_adc_set_resolution_selection(ADC, MD_ADC_CFG_RSEL_12BIT);            // 12-bit resolution
    md_adc_set_normal_sequence_selection_1th(ADC, MD_ADC_NCHS1_NS1_CH18);   // channel number(16:Temperature)
    md_adc_set_adc_clock_predivider(ADC, ADC_InitStruct->CKDIV);

    if (ADC_InitStruct->CKDIV == MD_ADC_SMPT1_CKDIV_DIV1) {
        clkdiv = 1;
    } else if (ADC_InitStruct->CKDIV == MD_ADC_SMPT1_CKDIV_DIV2){
        clkdiv = 2;
    } else if (ADC_InitStruct->CKDIV == MD_ADC_SMPT1_CKDIV_DIV4){
        clkdiv = 4;
    } else if (ADC_InitStruct->CKDIV == MD_ADC_SMPT1_CKDIV_DIV6){
        clkdiv = 6;
    } else if (ADC_InitStruct->CKDIV == MD_ADC_SMPT1_CKDIV_DIV8){
        clkdiv = 8;
    }

    if ((SystemFrequency_APBClk / clkdiv) <= 12000000) {
        md_adc_set_sampletime_channel_18(ADCx, 0x40); //Sample Time Cycle
    } else {
        md_adc_set_sampletime_channel_18(ADCx, 0x80); //Sample Time Cycle
    }

    //CLEAR CALCR
    md_adc_set_gain_factor(ADCx, 1024);
    md_adc_set_offset_factor(ADCx, 0);

    //ADC ENABLE
    md_adc_enable_adcpower(ADCx);

    while (!md_adc_is_active_flag_adc_ready(ADCx));

    // --------------------------------------------------------
    // 1/16 Sample
    md_adc_set_vref_level(ADCx, MD_ADC_CCR_REFINTS_1DIV16);
    md_adc_set_start_normal(ADCx, MD_ADC_CON_NSTART_START_REGULAR);

    while (md_adc_is_active_flag_normal_status(ADCx));

    adc_data_1 = md_adc_get_normal_data(ADCx);

    // --------------------------------------------------------
    // 15/16 Sample
    md_adc_set_vref_level(ADCx, MD_ADC_CCR_REFINTS_15DIV16);
    md_adc_set_start_normal(ADCx, MD_ADC_CON_NSTART_START_REGULAR);

    while (md_adc_is_active_flag_normal_status(ADCx));

    adc_data_15 = md_adc_get_normal_data(ADCx);

    // --------------------------------------------------------
    temp_adc_offset = (float)((15 * adc_data_1) - adc_data_15) / 14;

    if (temp_adc_offset > 0) {
        adc_offset = (int16_t)(temp_adc_offset + 0.5);
    } else {
        adc_offset = (int16_t)(temp_adc_offset - 0.5);
    }

    adc_gain   = (uint16_t)((3584 * 1024) / (float)(adc_data_15 - adc_data_1) + 0.5);

    md_adc_set_gain_factor(ADCx, adc_gain);
    md_adc_set_offset_factor(ADCx, adc_offset);

    // --------------------------------------------------------
    md_adc_set_convsersion_mode(ADCx, 0);
    md_adc_set_resolution_selection(ADCx, MD_ADC_CFG_RSEL_6BIT);
    md_adc_set_normal_sequence_selection_1th(ADCx, MD_ADC_NCHS1_NS1_CH0);
    md_adc_set_adc_clock_predivider(ADCx, MD_ADC_SMPT1_CKDIV_DIV1);
    md_adc_set_sampletime_channel_18(ADCx, 0);
    md_adc_set_icr(ADCx, 0xFFFE);

    return SUCCESS;
}

// ErrorStatus md_adc_optionbyte_calibration(ADC_TypeDef *ADCx, md_adc_initial *ADC_InitStruct) {
//     int8_t              adc_offset = 0;
//     uint32_t            adc_gain = 1024;
//     uint32_t            cal_value = 0;
//     md_fc_read_info(ADC_CALIBRATION_ADDR, &cal_value);

//     adc_gain = (cal_value & 0xFFF);
//     adc_offset = (cal_value >> 16) & 0xFF;

//     //ADC ENABLE
//     md_adc_enable_adcpower(ADCx);
//     md_adc_set_gain_factor(ADCx, adc_gain);
//     md_adc_set_offset_factor(ADCx, adc_offset);
//     return SUCCESS;
// }

ErrorStatus rdmctmzt_adc_calibration(ADC_TypeDef *ADCx, md_adc_initial *ADC_InitStruct) {
    uint32_t            cal_value = 0;
    md_fc_read_info(ADC_CALIBRATION_ADDR, &cal_value);

    if (cal_value == 0xFFFFFFFF) {
        return rdmctmzt_adc_software_calibration(ADCx, ADC_InitStruct);
    } else {
        return md_adc_optionbyte_calibration(ADCx, ADC_InitStruct);
    }
}

// void md_adc_init(ADC_TypeDef *ADCx, md_adc_initial *ADC_InitStruct) {
//     while (md_adc_is_enabled_calibration(ADCx));

//     md_adc_set_adc_clock_predivider(ADC, ADC_InitStruct->CKDIV);

//     md_adc_enable_adcpower(ADCx);

//     while (!md_adc_is_active_flag_adc_ready(ADCx));

//     while ((md_adc_get_start_inj(ADCx) == MD_ADC_CON_ISTART_START_INJECTED));

//     while ((md_adc_get_start_normal(ADCx) == MD_ADC_CON_NSTART_START_REGULAR));

//     md_adc_set_data_alignment(ADCx, ADC_InitStruct->ALIGN);
//     md_adc_set_resolution_selection(ADCx, ADC_InitStruct->RSEL);
//     md_adc_set_convsersion_mode(ADCx, ADC_InitStruct->Regular_CM);

// #ifdef ADC_DMA
//     md_adc_enable_dma_access(ADCx);
// #else
//     md_adc_disable_dma_access(ADCx);
// #endif

// }

void User_Adc_Init(void) {  //ES_BATT_ADC_IO
    md_gpio_inittypedef gpiox;

    gpiox.OutputType = MD_GPIO_OUTPUT_PUSHPULL;
    gpiox.Pull = MD_GPIO_PULL_FLOATING;
    gpiox.OutDrive = MD_GPIO_DRIVING_8MA;
    gpiox.Function = MD_GPIO_AF0;
    gpiox.Mode = MD_GPIO_MODE_ANALOG;
    gpiox.Pin = MD_GPIO_PIN_4;
    md_gpio_init(GPIOC, &gpiox);
    
    md_rcu_enable_adc(RCU);
    rdmctmzt_adc_calibration(ADC, (md_adc_initial *)(&adc_initStruct));
    md_adc_set_sampletime_channel_14(ADC, 0x40);
    md_adc_init(ADC, (md_adc_initial *)(&adc_initStruct));

    while ((ADC->RIF & 0x1) == 0);

    md_adc_set_normal_sequence_length(ADC, adc_initStruct.Cnt);
    md_adc_set_normal_sequence_selection_1th(ADC, MD_ADC_NCHS1_NS1_CH14);
    md_adc_set_start_normal(ADC, MD_ADC_CON_NSTART_START_REGULAR);
}

void User_Adc_Deinit(void) {
    md_rcu_enable_adc_reset(RCU);
    md_rcu_disable_adc_reset(RCU);
    md_rcu_disable_adc(RCU);
}

void U16_Buff_Clear(uint16_t *Buff, uint8_t Len) {
    for(uint8_t i = 0; i < Len; i++) {
        Buff[i] = 0;
    }
}

void Init_Batt_Infomation(void) {
    if (gpio_read_pin(ES_USB_POWER_IO)) {
        User_Batt_BaiFen = Keyboard_Info.Batt_Number;
        User_Batt_Old_BaiFen = User_Batt_BaiFen;
        User_Batt_Power_Up = false;
    } else {
        User_Batt_Power_Up = true;
    }
    User_Batt_10ms_Count = 0;
    User_Adc_Batt_Count = 0;
    User_Batt_Time_15S_Count = 0;
    User_Power_Low = false;
    User_Power_Low_Count = 0;

    U16_Buff_Clear(User_Adc_Batt, USER_BATT_SCAN_COUNT);
    U16_Buff_Clear(User_Scan_Batt, USER_BATT_SCAN_COUNT);

    User_Batt_Power_Up_Delay_100ms_Count = 0;
    User_Batt_Power_Up_Delay = true;
}

void User_Adc_Batt_Power_Up_Init(void) {
    uint8_t Min_Batt = 0, Max_Batt = 0;
    for (uint8_t i = 0; i < USER_BATT_POWER_SCAN_COUNT; i++) {
        if (User_Scan_Batt[Min_Batt] < User_Scan_Batt[i]) {
            Min_Batt = i;
        }

        if (User_Scan_Batt[Max_Batt] > User_Scan_Batt[i]) {
            Max_Batt = i;
        }
    }

    uint16_t Temp_Batt_Sub = 0;
    if (Min_Batt == Max_Batt) {
        for (uint8_t i = 0; i < (USER_BATT_POWER_SCAN_COUNT - 2); i++) {
            Temp_Batt_Sub += User_Scan_Batt[i];
        }
    } else {
        for (uint8_t i = 0; i < USER_BATT_POWER_SCAN_COUNT; i++) {
            if ((Min_Batt == i) || (Max_Batt == i)) {
                continue;
            }
            Temp_Batt_Sub += User_Scan_Batt[i];
        }
    }

    uint16_t Temp_Average = (Temp_Batt_Sub / (USER_BATT_POWER_SCAN_COUNT - 2));

    uint8_t Temp_Batt_Number = 0;
    if (Temp_Average >= USER_BATT_HIGH_POWER) {
        Temp_Batt_Number = 100;
    } else if (Temp_Average <= USER_BATT_STDOWN_POWER) {
        Temp_Batt_Number = 0;
    } else {
        Temp_Batt_Number = (((Temp_Average - USER_BATT_STDOWN_POWER) * 100) / (USER_BATT_HIGH_POWER - USER_BATT_STDOWN_POWER));
    }

    if (Temp_Average <= USER_BATT_STDOWN_POWER) {
        User_Power_Low_Count++;
        if (User_Power_Low_Count >= 4) {
            User_Power_Low_Count = 0;
            User_Power_Low = true;
        }
    } else if (Temp_Average <= USER_BATT_LOW_POWER) {
        User_Power_Low_Count++;
        if (User_Power_Low_Count >= 10) {
            User_Power_Low_Count = 0;
            User_Power_Low = true;
        }
    } else {
        User_Power_Low_Count = 0;
    }

    User_Batt_BaiFen = Temp_Batt_Number;
    User_Batt_Old_BaiFen = User_Batt_BaiFen;

    if (User_Batt_BaiFen != Keyboard_Info.Batt_Number) {
        Keyboard_Info.Batt_Number = User_Batt_BaiFen;
        Save_Flash_Set();
    }

    User_Adc_Batt_Count = 0;
    User_Batt_10ms_Count = 0;
    User_Batt_Time_15S_Count = 0;
    User_Batt_Power_Up = false;
}

void User_Adc_Batt_Number(void) {
    if (es_stdby_pin_state == 2) {
        User_Batt_BaiFen = 100;
        User_Batt_Old_BaiFen = 100;
        if (Keyboard_Info.Batt_Number != User_Batt_BaiFen) {
            Keyboard_Info.Batt_Number = User_Batt_BaiFen;
            User_Batt_Send_Spi = true;
            Save_Flash_Set();
        }
        User_Power_Low = false;
        User_Power_Low_Count = 0;
        return;
    }

    uint8_t Min_Batt = 0, Max_Batt = 0;
    for (uint8_t i = 0; i < USER_BATT_SCAN_COUNT; i++) {
        if (User_Scan_Batt[Min_Batt] < User_Scan_Batt[i]) {
            Min_Batt = i;
        }

        if (User_Scan_Batt[Max_Batt] > User_Scan_Batt[i]) {
            Max_Batt = i;
        }
    }

    uint16_t Temp_Batt_Sub = 0;
    if (Min_Batt == Max_Batt) {
        for (uint8_t i = 0; i < (USER_BATT_SCAN_COUNT - 2); i++) {
            Temp_Batt_Sub += User_Scan_Batt[i];
        }
    } else {
        for (uint8_t i = 0; i < USER_BATT_SCAN_COUNT; i++) {
            if ((Min_Batt == i) || (Max_Batt == i)) {
                continue;
            }
            Temp_Batt_Sub += User_Scan_Batt[i];
        }
    }

    uint16_t Temp_Average = (Temp_Batt_Sub / (USER_BATT_SCAN_COUNT - 2));

    uint8_t Temp_Batt_Number = 0;
    if (Temp_Average >= USER_BATT_HIGH_POWER) {
        Temp_Batt_Number = 100;
    } else if (Temp_Average <= USER_BATT_STDOWN_POWER) {
        Temp_Batt_Number = 0;
    } else {
        Temp_Batt_Number = (((Temp_Average - USER_BATT_STDOWN_POWER) * 100) / (USER_BATT_HIGH_POWER - USER_BATT_STDOWN_POWER));
    }

    if (es_stdby_pin_state == 1) {
        if (Temp_Batt_Number >= 100) {
            Temp_Batt_Number = 99;
        } else if (Temp_Batt_Number <= 0) {
            Temp_Batt_Number = 1;
        }
    } else {
        if (Temp_Average <= USER_BATT_STDOWN_POWER) {
            User_Power_Low_Count++;
            if (User_Power_Low_Count >= 5) {
                User_Power_Low_Count = 0;
                User_Power_Low = true;
            }
        } else if (Temp_Average <= USER_BATT_LOW_POWER) {
            User_Power_Low_Count++;
            if (User_Power_Low_Count >= 10) {
                User_Power_Low_Count = 0;
                User_Power_Low = true;
            }
        } else {
            User_Power_Low_Count = 0;
        }
    }

    if (es_stdby_pin_state) {
        if (Temp_Batt_Number > User_Batt_Old_BaiFen) {
            if (User_Batt_Time_15S_Count >= USER_BATT_DELAY_TIME) {
                User_Batt_Time_15S_Count = 0;
                if (User_Batt_BaiFen <= 98) {
                    User_Batt_BaiFen++;
                } 
                User_Batt_Old_BaiFen = User_Batt_BaiFen;
            }
        } else {
            User_Batt_Time_15S_Count = 0;
        }
        User_Power_Low = false;
        User_Power_Low_Count = 0;
    } else {
        if (Temp_Batt_Number < User_Batt_Old_BaiFen) {
            if (User_Batt_Time_15S_Count >= USER_BATT_DELAY_TIME) {
                User_Batt_Time_15S_Count = 0;
                if (User_Batt_BaiFen) {
                    User_Batt_BaiFen--;
                }
                User_Batt_Old_BaiFen = User_Batt_BaiFen;
            }
        } else {
            User_Batt_Time_15S_Count = 0;
        }
    }

    if (Keyboard_Info.Batt_Number != User_Batt_BaiFen) {
        Keyboard_Info.Batt_Number = User_Batt_BaiFen;
        User_Batt_Send_Spi = true;
        Save_Flash_Set();
    }
}