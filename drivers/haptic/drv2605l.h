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

#include <stdint.h>

/* Initialization settings

 * Feedback Control Settings */
#ifndef FB_ERM_LRA
#    define FB_ERM_LRA 1 /* For ERM:0 or LRA:1*/
#endif
#ifndef FB_BRAKEFACTOR
#    define FB_BRAKEFACTOR 3 /* For 1x:0, 2x:1, 3x:2, 4x:3, 6x:4, 8x:5, 16x:6, Disable Braking:7 */
#endif
#ifndef FB_LOOPGAIN
#    define FB_LOOPGAIN 1 /* For  Low:0, Medium:1, High:2, Very High:3 */
#endif

/* LRA specific settings */
#if FB_ERM_LRA == 1
#    ifndef V_RMS
#        define V_RMS 2.0
#    endif
#    ifndef V_PEAK
#        define V_PEAK 2.1
#    endif
#    ifndef F_LRA
#        define F_LRA 205
#    endif
#    ifndef RATED_VOLTAGE
#        define RATED_VOLTAGE 2 /* 2v as safe range in case device voltage is not set */
#    endif
#endif

#ifndef RATED_VOLTAGE
#    define RATED_VOLTAGE 2 /* 2v as safe range in case device voltage is not set */
#endif
#ifndef V_PEAK
#    define V_PEAK 2.8
#endif

/* Library Selection */
#ifndef DRV2605L_LIBRARY
#    if FB_ERM_LRA == 1
#        define DRV2605L_LIBRARY 6 /* For Empty:0' TS2200 library A to D:1-5, LRA Library: 6 */
#    else
#        define DRV2605L_LIBRARY 1
#    endif
#endif

#ifndef DRV2605L_GREETING
#    define DRV2605L_GREETING alert_750ms
#endif
#ifndef DRV2605L_DEFAULT_MODE
#    define DRV2605L_DEFAULT_MODE strong_click1
#endif

/* Control 1 register settings */
#ifndef DRIVE_TIME
#    define DRIVE_TIME 25
#endif
#ifndef AC_COUPLE
#    define AC_COUPLE 0
#endif
#ifndef STARTUP_BOOST
#    define STARTUP_BOOST 1
#endif

/* Control 2 Settings */
#ifndef BIDIR_INPUT
#    define BIDIR_INPUT 1
#endif
#ifndef BRAKE_STAB
#    define BRAKE_STAB 1 /* Loopgain is reduced when braking is almost complete to improve stability */
#endif
#ifndef SAMPLE_TIME
#    define SAMPLE_TIME 3
#endif
#ifndef BLANKING_TIME
#    define BLANKING_TIME 1
#endif
#ifndef IDISS_TIME
#    define IDISS_TIME 1
#endif

/* Control 3 settings */
#ifndef NG_THRESH
#    define NG_THRESH 2
#endif
#ifndef ERM_OPEN_LOOP
#    define ERM_OPEN_LOOP 1
#endif
#ifndef SUPPLY_COMP_DIS
#    define SUPPLY_COMP_DIS 0
#endif
#ifndef DATA_FORMAT_RTO
#    define DATA_FORMAT_RTO 0
#endif
#ifndef LRA_DRIVE_MODE
#    define LRA_DRIVE_MODE 0
#endif
#ifndef N_PWM_ANALOG
#    define N_PWM_ANALOG 0
#endif
#ifndef LRA_OPEN_LOOP
#    define LRA_OPEN_LOOP 0
#endif

/* Control 4 settings */
#ifndef ZC_DET_TIME
#    define ZC_DET_TIME 0
#endif
#ifndef AUTO_CAL_TIME
#    define AUTO_CAL_TIME 3
#endif

#define DRV2605L_I2C_ADDRESS 0x5A

#define DRV2605L_REG_STATUS 0x00
#define DRV2605L_REG_MODE 0x01
#define DRV2605L_REG_RTP_INPUT 0x02
#define DRV2605L_REG_LIBRARY_SELECTION 0x03
#define DRV2605L_REG_WAVEFORM_SEQUENCER_1 0x04
#define DRV2605L_REG_WAVEFORM_SEQUENCER_2 0x05
#define DRV2605L_REG_WAVEFORM_SEQUENCER_3 0x06
#define DRV2605L_REG_WAVEFORM_SEQUENCER_4 0x07
#define DRV2605L_REG_WAVEFORM_SEQUENCER_5 0x08
#define DRV2605L_REG_WAVEFORM_SEQUENCER_6 0x09
#define DRV2605L_REG_WAVEFORM_SEQUENCER_7 0x0A
#define DRV2605L_REG_WAVEFORM_SEQUENCER_8 0x0B
#define DRV2605L_REG_GO 0x0C
#define DRV2605L_REG_OVERDRIVE_TIME_OFFSET 0x0D
#define DRV2605L_REG_SUSTAIN_TIME_OFFSET_P 0x0E
#define DRV2605L_REG_SUSTAIN_TIME_OFFSET_N 0x0F
#define DRV2605L_REG_BRAKE_TIME_OFFSET 0x10
#define DRV2605L_REG_AUDIO_TO_VIBE_CTRL 0x11
#define DRV2605L_REG_AUDIO_TO_VIBE_MIN_INPUT 0x12
#define DRV2605L_REG_AUDIO_TO_VIBE_MAX_INPUT 0x13
#define DRV2605L_REG_AUDIO_TO_VIBE_MIN_OUTPUT_DRIVE 0x14
#define DRV2605L_REG_AUDIO_TO_VIBE_MAX_OUTPUT_DRIVE 0x15
#define DRV2605L_REG_RATED_VOLTAGE 0x16
#define DRV2605L_REG_OVERDRIVE_CLAMP_VOLTAGE 0x17
#define DRV2605L_REG_AUTO_CALIBRATION_COMPENSATION_RESULT 0x18
#define DRV2605L_REG_AUTO_CALIBRATION_BACK_EMF_RESULT 0x19
#define DRV2605L_REG_FEEDBACK_CTRL 0x1A
#define DRV2605L_REG_CTRL1 0x1B
#define DRV2605L_REG_CTRL2 0x1C
#define DRV2605L_REG_CTRL3 0x1D
#define DRV2605L_REG_CTRL4 0x1E
#define DRV2605L_REG_CTRL5 0x1F
#define DRV2605L_REG_LRA_OPEN_LOOP_PERIOD 0x20
#define DRV2605L_REG_VBAT_VOLTAGE_MONITOR 0x21
#define DRV2605L_REG_LRA_RESONANCE_PERIOD 0x22

void    drv2605l_init(void);
void    drv2605l_write(const uint8_t reg_addr, const uint8_t data);
uint8_t drv2605l_read(const uint8_t reg_addr);
void    drv2605l_rtp_init(void);
void    drv2605l_amplitude(const uint8_t amplitude);
void    drv2605l_pulse(const uint8_t sequence);

typedef enum DRV_EFFECT {
    clear_sequence,
    strong_click,
    strong_click_60,
    strong_click_30,
    sharp_click,
    sharp_click_60,
    sharp_click_30,
    soft_bump,
    soft_bump_60,
    soft_bump_30,
    dbl_click,
    dbl_click_60,
    trp_click,
    soft_fuzz,
    strong_buzz,
    alert_750ms,
    alert_1000ms,
    strong_click1,
    strong_click2_80,
    strong_click3_60,
    strong_click4_30,
    medium_click1,
    medium_click2_80,
    medium_click3_60,
    sharp_tick1,
    sharp_tick2_80,
    sharp_tick3_60,
    sh_dblclick_str,
    sh_dblclick_str_80,
    sh_dblclick_str_60,
    sh_dblclick_str_30,
    sh_dblclick_med,
    sh_dblclick_med_80,
    sh_dblclick_med_60,
    sh_dblsharp_tick,
    sh_dblsharp_tick_80,
    sh_dblsharp_tick_60,
    lg_dblclick_str,
    lg_dblclick_str_80,
    lg_dblclick_str_60,
    lg_dblclick_str_30,
    lg_dblclick_med,
    lg_dblclick_med_80,
    lg_dblclick_med_60,
    lg_dblsharp_tick,
    lg_dblsharp_tick_80,
    lg_dblsharp_tick_60,
    buzz,
    buzz_80,
    buzz_60,
    buzz_40,
    buzz_20,
    pulsing_strong,
    pulsing_strong_80,
    pulsing_medium,
    pulsing_medium_80,
    pulsing_sharp,
    pulsing_sharp_80,
    transition_click,
    transition_click_80,
    transition_click_60,
    transition_click_40,
    transition_click_20,
    transition_click_10,
    transition_hum,
    transition_hum_80,
    transition_hum_60,
    transition_hum_40,
    transition_hum_20,
    transition_hum_10,
    transition_rampdown_long_smooth1,
    transition_rampdown_long_smooth2,
    transition_rampdown_med_smooth1,
    transition_rampdown_med_smooth2,
    transition_rampdown_short_smooth1,
    transition_rampdown_short_smooth2,
    transition_rampdown_long_sharp1,
    transition_rampdown_long_sharp2,
    transition_rampdown_med_sharp1,
    transition_rampdown_med_sharp2,
    transition_rampdown_short_sharp1,
    transition_rampdown_short_sharp2,
    transition_rampup_long_smooth1,
    transition_rampup_long_smooth2,
    transition_rampup_med_smooth1,
    transition_rampup_med_smooth2,
    transition_rampup_short_smooth1,
    transition_rampup_short_smooth2,
    transition_rampup_long_sharp1,
    transition_rampup_long_sharp2,
    transition_rampup_med_sharp1,
    transition_rampup_med_sharp2,
    transition_rampup_short_sharp1,
    transition_rampup_short_sharp2,
    transition_rampdown_long_smooth1_50,
    transition_rampdown_long_smooth2_50,
    transition_rampdown_med_smooth1_50,
    transition_rampdown_med_smooth2_50,
    transition_rampdown_short_smooth1_50,
    transition_rampdown_short_smooth2_50,
    transition_rampdown_long_sharp1_50,
    transition_rampdown_long_sharp2_50,
    transition_rampdown_med_sharp1_50,
    transition_rampdown_med_sharp2_50,
    transition_rampdown_short_sharp1_50,
    transition_rampdown_short_sharp2_50,
    transition_rampup_long_smooth1_50,
    transition_rampup_long_smooth2_50,
    transition_rampup_med_smooth1_50,
    transition_rampup_med_smooth2_50,
    transition_rampup_short_smooth1_50,
    transition_rampup_short_smooth2_50,
    transition_rampup_long_sharp1_50,
    transition_rampup_long_sharp2_50,
    transition_rampup_med_sharp1_50,
    transition_rampup_med_sharp2_50,
    transition_rampup_short_sharp1_50,
    transition_rampup_short_sharp2_50,
    long_buzz_for_programmatic_stopping,
    smooth_hum1_50,
    smooth_hum2_40,
    smooth_hum3_30,
    smooth_hum4_20,
    smooth_hum5_10,
    drv_effect_max
} DRV_EFFECT;

/* Register bit array unions */

typedef union DRVREG_STATUS { /* register 0x00 */
    uint8_t Byte;
    struct {
        uint8_t OC_DETECT : 1; /* set to 1 when overcurrent event is detected */
        uint8_t OVER_TEMP : 1; /* set to 1 when device exceeds temp threshold */
        uint8_t FB_STS : 1;    /* set to 1 when feedback controller has timed out */
        /* auto-calibration routine and diagnostic result
         * result  |  auto-calibation  |      diagnostic       |
         *   0     |      passed       | actuator func normal  |
         *   1     |      failed       | actuator func fault*  |
         * * actuator is not present or is shorted, timing out, or giving out–of-range back-EMF */
        uint8_t DIAG_RESULT : 1;
        uint8_t : 1;
        uint8_t DEVICE_ID : 3; /* Device IDs 3: DRV2605  4: DRV2604  5: DRV2604L  6: DRV2605L */
    } Bits;
} DRVREG_STATUS;

typedef union DRVREG_MODE { /* register 0x01 */
    uint8_t Byte;
    struct {
        uint8_t MODE : 3; /* Mode setting */
        uint8_t : 3;
        uint8_t STANDBY : 1; /* 0:standby 1:ready */
    } Bits;
} DRVREG_MODE;

typedef union DRVREG_WAIT {
    uint8_t Byte;
    struct {
        uint8_t WAIT_MODE : 1; /* Set to 1 to interpret as wait for next 7 bits x10ms */
        uint8_t WAIT_TIME : 7;
    } Bits;
} DRVREG_WAIT;

typedef union DRVREG_FBR { /* register 0x1A */
    uint8_t Byte;
    struct {
        uint8_t BEMF_GAIN : 2;
        uint8_t LOOP_GAIN : 2;
        uint8_t BRAKE_FACTOR : 3;
        uint8_t ERM_LRA : 1;
    } Bits;
} DRVREG_FBR;

typedef union DRVREG_CTRL1 { /* register 0x1B */
    uint8_t Byte;
    struct {
        uint8_t C1_DRIVE_TIME : 5;
        uint8_t C1_AC_COUPLE : 1;
        uint8_t : 1;
        uint8_t C1_STARTUP_BOOST : 1;
    } Bits;
} DRVREG_CTRL1;

typedef union DRVREG_CTRL2 { /* register 0x1C */
    uint8_t Byte;
    struct {
        uint8_t C2_IDISS_TIME : 2;
        uint8_t C2_BLANKING_TIME : 2;
        uint8_t C2_SAMPLE_TIME : 2;
        uint8_t C2_BRAKE_STAB : 1;
        uint8_t C2_BIDIR_INPUT : 1;
    } Bits;
} DRVREG_CTRL2;

typedef union DRVREG_CTRL3 { /* register 0x1D */
    uint8_t Byte;
    struct {
        uint8_t C3_LRA_OPEN_LOOP : 1;
        uint8_t C3_N_PWM_ANALOG : 1;
        uint8_t C3_LRA_DRIVE_MODE : 1;
        uint8_t C3_DATA_FORMAT_RTO : 1;
        uint8_t C3_SUPPLY_COMP_DIS : 1;
        uint8_t C3_ERM_OPEN_LOOP : 1;
        uint8_t C3_NG_THRESH : 2;
    } Bits;
} DRVREG_CTRL3;

typedef union DRVREG_CTRL4 { /* register 0x1E */
    uint8_t Byte;
    struct {
        uint8_t C4_OTP_PROGRAM : 1;
        uint8_t : 1;
        uint8_t C4_OTP_STATUS : 1;
        uint8_t : 1;
        uint8_t C4_AUTO_CAL_TIME : 2;
        uint8_t C4_ZC_DET_TIME : 2;
    } Bits;
} DRVREG_CTRL4;

typedef union DRVREG_CTRL5 { /* register 0x1F */
    uint8_t Byte;
    struct {
        uint8_t C5_IDISS_TIME : 2;
        uint8_t C5_BLANKING_TIME : 2;
        uint8_t C5_PLAYBACK_INTERVAL : 1;
        uint8_t C5_LRA_AUTO_OPEN_LOOP : 1;
        uint8_t C5_AUTO_OL_CNT : 2;
    } Bits;
} DRVREG_CTRL5;
