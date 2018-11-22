/* Copyright 2018 ishtob
 * Driver for DRV2605L written for QMK
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

#pragma once
#include "i2c_master.h"

//register defines --------------------------------------------------------
#define DRV2605L_BASE_ADDRESS 		0x5A		//!< DRV2605L Base address
#define DRV_STATUS 					0x00
#define DRV_MODE 					0x01
#define DRV_RTP_INPUT 				0x02
#define DRV_LIB_SELECTION 			0x03
#define DRV_WAVEFORM_SEQ_1 			0x04
#define DRV_WAVEFORM_SEQ_2 			0x05
#define DRV_WAVEFORM_SEQ_3 			0x06
#define DRV_WAVEFORM_SEQ_4 			0x07
#define DRV_WAVEFORM_SEQ_5 			0x08
#define DRV_WAVEFORM_SEQ_6 			0x09
#define DRV_WAVEFORM_SEQ_7 			0x0A
#define DRV_WAVEFORM_SEQ_8 			0x0B
#define DRV_GO	 					0x0C
#define DRV_OVERDRIVE_TIME_OFFSET 	0x0D
#define DRV_SUSTAIN_TIME_OFFSET_P   0x0E
#define DRV_SUSTAIN_TIME_OFFSET_N 	0x0F
#define DRV_BRAKE_TIME_OFFSET 		0x10
#define DRV_AUDIO_2_VIBE_CTRL		0x11
#define DRV_AUDIO_2_VIBE_MIN_IN		0x12
#define DRV_AUDIO_2_VIBE_MAX_IN		0x13
#define DRV_AUDIO_2_VIBE_MIN_OUTDRV	0x14
#define DRV_AUDIO_2_VIBE_MAX_OUTDRV	0x15
#define DRV_RATED_VOLT 				0x16
#define DRV_OVERDRIVE_CLAMP_VOLT 	0x17
#define DRV_AUTO_CALIB_COMP_RESULT	0x18 
#define DRV_AUTO_CALIB_BEMF_RESULT	0x19
#define DRV_FEEDBACK_CTRL 			0x1A
#define DRV_CTRL_1 					0x1B
#define DRV_CTRL_2 					0x1C
#define DRV_CTRL_3 					0x1D
#define DRV_CTRL_4 					0x1E
#define DRV_CTRL_5 					0x1F
#define DRV_OPEN_LOOP_PERIOD 		0x20
#define DRV_VBAT_VOLT_MONITOR 		0x21
#define DRV_LRA_RESONANCE_PERIOD 	0x22

void DRV_init(void);
void DRV_write(const uint8_t drv_register, const uint8_t settings);
//void DRV_read(const uint8_t drv_register, const uint8_t settings);
void DRV_pulse(const uint8_t sequence);

