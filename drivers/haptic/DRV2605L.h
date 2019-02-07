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

/* Initialization settings

 * Feedback Control Settings */
#ifndef FB_ERM_LRA
#define FB_ERM_LRA 1 /* For ERM:0 or LRA:1*/
#endif
#ifndef FB_BRAKEFACTOR
#define FB_BRAKEFACTOR 3 /* For 1x:0, 2x:1, 3x:2, 4x:3, 6x:4, 8x:5, 16x:6, Disable Braking:7 */
#endif
#ifndef FB_LOOPGAIN
#define FB_LOOPGAIN 1 /* For  Low:0, Medium:1, High:2, Very High:3 */
#endif

#ifndef RATED_VOLTAGE
#define RATED_VOLTAGE 2 /* 2v as safe range in case device voltage is not set */
#ifndef V_PEAK
#define V_PEAK 2.8
#endif
#endif

/* LRA specific settings */
#if FB_ERM_LRA == 1
#ifndef V_RMS
#define V_RMS 2.0
#endif
#ifndef V_PEAK
#define V_PEAK 2.1
#endif
#ifndef F_LRA
#define F_LRA 205
#endif
#endif

/* Library Selection */
#ifndef LIB_SELECTION
#if FB_ERM_LRA == 1
#define LIB_SELECTION 6 /* For Empty:0' TS2200 library A to D:1-5, LRA Library: 6 */
#else
#define LIB_SELECTION 1
#endif
#endif

/* Control 1 register settings */
#ifndef DRIVE_TIME
#define DRIVE_TIME 25
#endif
#ifndef AC_COUPLE
#define AC_COUPLE 0
#endif
#ifndef STARTUP_BOOST
#define STARTUP_BOOST 1
#endif

/* Control 2 Settings */
#ifndef BIDIR_INPUT
#define BIDIR_INPUT 1
#endif
#ifndef BRAKE_STAB
#define BRAKE_STAB 1 /* Loopgain is reduced when braking is almost complete to improve stability */
#endif
#ifndef SAMPLE_TIME 
#define SAMPLE_TIME 3
#endif
#ifndef BLANKING_TIME
#define BLANKING_TIME 1
#endif
#ifndef IDISS_TIME
#define IDISS_TIME 1
#endif

/* Control 3 settings */
#ifndef NG_THRESH
#define NG_THRESH 2
#endif
#ifndef ERM_OPEN_LOOP
#define ERM_OPEN_LOOP 1
#endif
#ifndef SUPPLY_COMP_DIS
#define SUPPLY_COMP_DIS 0
#endif
#ifndef DATA_FORMAT_RTO
#define DATA_FORMAT_RTO 0
#endif
#ifndef LRA_DRIVE_MODE
#define LRA_DRIVE_MODE 0
#endif
#ifndef N_PWM_ANALOG
#define N_PWM_ANALOG 0
#endif
#ifndef LRA_OPEN_LOOP
#define LRA_OPEN_LOOP 0
#endif

/* Control 4 settings */
#ifndef ZC_DET_TIME
#define ZC_DET_TIME 0
#endif
#ifndef AUTO_CAL_TIME
#define AUTO_CAL_TIME 3
#endif

/* register defines -------------------------------------------------------- */
#define DRV2605L_BASE_ADDRESS       0x5A		/* DRV2605L Base address */
#define DRV_STATUS                  0x00
#define DRV_MODE                    0x01
#define DRV_RTP_INPUT               0x02
#define DRV_LIB_SELECTION           0x03
#define DRV_WAVEFORM_SEQ_1          0x04
#define DRV_WAVEFORM_SEQ_2          0x05
#define DRV_WAVEFORM_SEQ_3          0x06
#define DRV_WAVEFORM_SEQ_4          0x07
#define DRV_WAVEFORM_SEQ_5          0x08
#define DRV_WAVEFORM_SEQ_6          0x09
#define DRV_WAVEFORM_SEQ_7          0x0A
#define DRV_WAVEFORM_SEQ_8          0x0B
#define DRV_GO                      0x0C
#define DRV_OVERDRIVE_TIME_OFFSET   0x0D
#define DRV_SUSTAIN_TIME_OFFSET_P   0x0E
#define DRV_SUSTAIN_TIME_OFFSET_N   0x0F
#define DRV_BRAKE_TIME_OFFSET       0x10
#define DRV_AUDIO_2_VIBE_CTRL       0x11
#define DRV_AUDIO_2_VIBE_MIN_IN     0x12
#define DRV_AUDIO_2_VIBE_MAX_IN     0x13
#define DRV_AUDIO_2_VIBE_MIN_OUTDRV	0x14
#define DRV_AUDIO_2_VIBE_MAX_OUTDRV	0x15
#define DRV_RATED_VOLT              0x16
#define DRV_OVERDRIVE_CLAMP_VOLT    0x17
#define DRV_AUTO_CALIB_COMP_RESULT  0x18 
#define DRV_AUTO_CALIB_BEMF_RESULT  0x19
#define DRV_FEEDBACK_CTRL           0x1A
#define DRV_CTRL_1                  0x1B
#define DRV_CTRL_2                  0x1C
#define DRV_CTRL_3                  0x1D
#define DRV_CTRL_4                  0x1E
#define DRV_CTRL_5                  0x1F
#define DRV_OPEN_LOOP_PERIOD        0x20
#define DRV_VBAT_VOLT_MONITOR       0x21
#define DRV_LRA_RESONANCE_PERIOD    0x22

void DRV_init(void);
void DRV_write(const uint8_t drv_register, const uint8_t settings);
uint8_t DRV_read(const uint8_t regaddress);
void DRV_pulse(const uint8_t sequence);


typedef enum DRV_EFFECT{
  clear_sequence      = 0,
  strong_click 		    = 1,
  strong_click_60 		= 2,
  strong_click_30 		= 3,
  sharp_click 		    = 4,
  sharp_click_60      = 5,
  sharp_click_30      = 6,
  soft_bump           = 7,
  soft_bump_60        = 8,
  soft_bump_30        = 9,
  dbl_click           = 10,
  dbl_click_60        = 11,
  trp_click           = 12,
  soft_fuzz           = 13,
  strong_buzz         = 14,
  alert_750ms         = 15,
  alert_1000ms        = 16,
  strong_click1       = 17,
  strong_click2_80    = 18,
  strong_click3_60    = 19,
  strong_click4_30    = 20,
  medium_click1       = 21,
  medium_click2_80    = 22,
  medium_click3_60    = 23,
  sharp_tick1         = 24,
  sharp_tick2_80      = 25,
  sharp_tick3_60      = 26,
  sh_dblclick_str     = 27,
  sh_dblclick_str_80  = 28,
  sh_dblclick_str_60  = 29,
  sh_dblclick_str_30  = 30,
  sh_dblclick_med     = 31,
  sh_dblclick_med_80  = 32,
  sh_dblclick_med_60  = 33,
  sh_dblsharp_tick    = 34,
  sh_dblsharp_tick_80 = 35,
  sh_dblsharp_tick_60 = 36,
  lg_dblclick_str     = 37,
  lg_dblclick_str_80  = 38,
  lg_dblclick_str_60  = 39,
  lg_dblclick_str_30  = 40,
  lg_dblclick_med     = 41,
  lg_dblclick_med_80  = 42,
  lg_dblclick_med_60  = 43,
  lg_dblsharp_tick    = 44,
  lg_dblsharp_tick_80 = 45,
  lg_dblsharp_tick_60 = 46,
  buzz 					= 47,
  buzz_80				= 48,
  buzz_60				= 49,
  buzz_40				= 50,
  buzz_20				= 51,
  pulsing_strong      = 52,
  pulsing_strong_80   = 53,
  pulsing_medium      = 54,
  pulsing_medium_80   = 55,
  pulsing_sharp       = 56,
  pulsing_sharp_80    = 57,
  transition_click		= 58,
  transition_click_80 = 59,
  transition_click_60	= 60,
  transition_click_40	= 61,
  transition_click_20	= 62,
  transition_click_10	= 63,
  transition_hum      = 64,
  transition_hum_80   = 65,
  transition_hum_60   = 66,
  transition_hum_40   = 67,
  transition_hum_20   = 68,
  transition_hum_10   = 69,
  transition_rampdown_long_smooth1  = 70,
  transition_rampdown_long_smooth2  = 71,
  transition_rampdown_med_smooth1   = 72,
  transition_rampdown_med_smooth2   = 73,
  transition_rampdown_short_smooth1 = 74,
  transition_rampdown_short_smooth2 = 75,
  transition_rampdown_long_sharp1   = 76,
  transition_rampdown_long_sharp2   = 77,
  transition_rampdown_med_sharp1    = 78,
  transition_rampdown_med_sharp2    = 79,
  transition_rampdown_short_sharp1  = 80,
  transition_rampdown_short_sharp2  = 81,
  transition_rampup_long_smooth1    = 82,
  transition_rampup_long_smooth2    = 83,
  transition_rampup_med_smooth1     = 84,
  transition_rampup_med_smooth2     = 85,
  transition_rampup_short_smooth1   = 86,
  transition_rampup_short_smooth2   = 87,
  transition_rampup_long_sharp1     = 88,
  transition_rampup_long_sharp2     = 89,
  transition_rampup_med_sharp1      = 90,
  transition_rampup_med_sharp2      = 91,
  transition_rampup_short_sharp1    = 92,
  transition_rampup_short_sharp2    = 93,
  transition_rampdown_long_smooth1_50  = 94,
  transition_rampdown_long_smooth2_50  = 95,
  transition_rampdown_med_smooth1_50   = 96,
  transition_rampdown_med_smooth2_50   = 97,
  transition_rampdown_short_smooth1_50 = 98,
  transition_rampdown_short_smooth2_50 = 99,
  transition_rampdown_long_sharp1_50   = 100,
  transition_rampdown_long_sharp2_50   = 101,
  transition_rampdown_med_sharp1_50    = 102,
  transition_rampdown_med_sharp2_50    = 103,
  transition_rampdown_short_sharp1_50  = 104,
  transition_rampdown_short_sharp2_50  = 105,
  transition_rampup_long_smooth1_50    = 106,
  transition_rampup_long_smooth2_50    = 107,
  transition_rampup_med_smooth1_50     = 108,
  transition_rampup_med_smooth2_50     = 109,
  transition_rampup_short_smooth1_50   = 110,
  transition_rampup_short_smooth2_50   = 111,
  transition_rampup_long_sharp1_50     = 112,
  transition_rampup_long_sharp2_50     = 113,
  transition_rampup_med_sharp1_50      = 114,
  transition_rampup_med_sharp2_50      = 115,
  transition_rampup_short_sharp1_50    = 116,
  transition_rampup_short_sharp2_50    = 117,
  long_buzz_for_programmatic_stopping  = 118,
  smooth_hum1_50 = 119,
  smooth_hum2_40 = 120,
  smooth_hum3_30 = 121,
  smooth_hum4_20 = 122,
  smooth_hum5_10 = 123,
} DRV_EFFECT;

/* Register bit array unions */

typedef union DRVREG_STATUS { /* register 0x00 */
  uint8_t Byte;
  struct {
    uint8_t OC_DETECT   :1; /* set to 1 when overcurrent event is detected */
    uint8_t OVER_TEMP   :1; /* set to 1 when device exceeds temp threshold */
    uint8_t FB_STS      :1; /* set to 1 when feedback controller has timed out */
    /* auto-calibration routine and diagnostic result
     * result  |  auto-calibation  |      diagnostic       |
     *   0     |      passed       | actuator func normal  |
     *   1     |      failed       | actuator func fault*  |
     * * actuator is not present or is shorted, timing out, or giving out–of-range back-EMF */
    uint8_t DIAG_RESULT :1;
    uint8_t             :1;
    uint8_t DEVICE_ID   :3; /* Device IDs 3: DRV2605  4: DRV2604  5: DRV2604L  6: DRV2605L */
  } Bits;
} DRVREG_STATUS;

typedef union DRVREG_MODE { /* register 0x01 */
  uint8_t Byte;
  struct {
    uint8_t MODE        :3; /* Mode setting */
    uint8_t             :3;
    uint8_t STANDBY     :1; /* 0:standby 1:ready */
  } Bits;
} DRVREG_MODE;

typedef union DRVREG_WAIT {
  uint8_t Byte;
  struct {
    uint8_t WAIT_MODE   :1; /* Set to 1 to interpret as wait for next 7 bits x10ms */
    uint8_t WAIT_TIME   :7;
  } Bits;
} DRVREG_WAIT;

typedef union DRVREG_FBR{ /* register 0x1A */
  uint8_t Byte;
  struct {
    uint8_t BEMF_GAIN    :2;
    uint8_t LOOP_GAIN    :2;
    uint8_t BRAKE_FACTOR :3;
    uint8_t ERM_LRA      :1;
  } Bits;
} DRVREG_FBR;

typedef union DRVREG_CTRL1{ /* register 0x1B */
  uint8_t Byte;
  struct {
    uint8_t C1_DRIVE_TIME    :5;
    uint8_t C1_AC_COUPLE     :1;
    uint8_t                  :1;
    uint8_t C1_STARTUP_BOOST :1;
  } Bits;
} DRVREG_CTRL1;

typedef union DRVREG_CTRL2{ /* register 0x1C */
  uint8_t Byte;
  struct {
    uint8_t C2_IDISS_TIME    :2;
    uint8_t C2_BLANKING_TIME :2;
    uint8_t C2_SAMPLE_TIME   :2;
    uint8_t C2_BRAKE_STAB    :1;
    uint8_t C2_BIDIR_INPUT   :1;
  } Bits;
} DRVREG_CTRL2;

typedef union DRVREG_CTRL3{ /* register 0x1D */
  uint8_t Byte;
  struct {
    uint8_t C3_LRA_OPEN_LOOP   :1;
    uint8_t C3_N_PWM_ANALOG    :1;
    uint8_t C3_LRA_DRIVE_MODE  :1;
    uint8_t C3_DATA_FORMAT_RTO :1;
    uint8_t C3_SUPPLY_COMP_DIS :1;
    uint8_t C3_ERM_OPEN_LOOP   :1;
    uint8_t C3_NG_THRESH       :2;
  } Bits;
} DRVREG_CTRL3;

typedef union DRVREG_CTRL4{ /* register 0x1E */
  uint8_t Byte;
  struct {
    uint8_t C4_OTP_PROGRAM     :1;
    uint8_t                    :1;
    uint8_t C4_OTP_STATUS      :1;
    uint8_t                    :1;
    uint8_t C4_AUTO_CAL_TIME   :2;
    uint8_t C4_ZC_DET_TIME     :2;
  } Bits;
} DRVREG_CTRL4;

typedef union DRVREG_CTRL5{ /* register 0x1F */
  uint8_t Byte;
  struct {
    uint8_t C5_IDISS_TIME         :2;
    uint8_t C5_BLANKING_TIME      :2;
    uint8_t C5_PLAYBACK_INTERVAL  :1;
    uint8_t C5_LRA_AUTO_OPEN_LOOP :1;
    uint8_t C5_AUTO_OL_CNT        :2;
  } Bits;
} DRVREG_CTRL5;