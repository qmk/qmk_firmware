/* Copyright 2022 Se1enLiang(@skyjun)
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

/**
 * 适用于两定位一脉冲编码器
 * the encoder model is ALPS SRGP 200200
 * two positioning only one pulse
 */

#include "tp_encoder.h"

// only one encoder, move index
__attribute__((weak)) bool encoder_update_user(bool clockwise) { return true; }

__attribute__((weak)) bool encoder_update_kb(bool clockwise) { return encoder_update_user(clockwise); }

static pin_t EC_A_Pin       = ENCODER_PAD_A;
static pin_t EC_B_Pin       = ENCODER_PAD_B;
static uint8_t EC_A_Now     = 0;
static uint8_t EC_B_Now     = 0;
static uint8_t EC_A_Last    = 0;
static uint8_t EC_B_Last    = 0;

void encoder_init(void)
{
    setPinInputHigh(EC_A_Pin);
    setPinInputHigh(EC_B_Pin);
}

bool encoder_scan(void)
{
    bool changed        = false;
    int8_t scan_result  = 0;

    EC_A_Now            = readPin(EC_A_Pin);
    EC_B_Now            = readPin(EC_B_Pin);

    // 判断当前电平是否等于上一次的电平
    // 正转，A 0>1 B 1>0，A 1>0 B 0>1
    // 反转，A 0>1 B 0>1，A 1>0 B 1>0
    if (EC_A_Now != EC_A_Last)
    {
        // 旋转后，电平为高时
        if (EC_A_Now == 1)
        {
            if (EC_B_Last && !EC_B_Now) scan_result = 1;                // 上次高，本次低，正转
            else if (!EC_B_Last && EC_B_Now) scan_result = -1;          // 上次低，本次高，反转
            else if (EC_B_Now == EC_B_Last)                             // 两次电平相等，转动后接着反转
            {
                if (!EC_B_Now) scan_result = 1;                         // 当前低，正转
                else scan_result = -1;                                  // 当前高，反转
            }
        }
        // 转动后，电平为低时
        else
        {
            if (EC_B_Last && !EC_B_Now) scan_result = -1;               // 上次高，本次低，反转
            else if (!EC_B_Last && EC_B_Now) scan_result = 1;           // 上次低，本次高，正转
            else if (EC_B_Now == EC_B_Last)                             // 转动后接着反转，两次电平相等
            {
                if (!EC_B_Now) scan_result = -1;                        // 当前低，反转
                else scan_result = 1;                                   // 当前高，正转
            }
        }

        // 更新 Last 值
        EC_A_Last   = EC_A_Now;
        EC_B_Last   = EC_B_Now;

        if (scan_result == 1)
        {
            changed = encoder_update_kb(true);
        }
        else if (scan_result == -1)
        {
            changed = encoder_update_kb(false);
        }
    }
    
    return changed;
}
