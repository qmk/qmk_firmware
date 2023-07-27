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

#include "drv2605l.h"
#include "i2c_master.h"
#include <math.h>

uint8_t drv2605l_write_buffer[2];
uint8_t drv2605l_read_buffer;

void drv2605l_write(uint8_t reg_addr, uint8_t data) {
    drv2605l_write_buffer[0] = reg_addr;
    drv2605l_write_buffer[1] = data;
    i2c_transmit(DRV2605L_I2C_ADDRESS << 1, drv2605l_write_buffer, 2, 100);
}

uint8_t drv2605l_read(uint8_t reg_addr) {
    i2c_readReg(DRV2605L_I2C_ADDRESS << 1, reg_addr, &drv2605l_read_buffer, 1, 100);

    return drv2605l_read_buffer;
}

void drv2605l_init(void) {
    i2c_init();
    /* 0x07 sets DRV2605 into calibration mode */
    drv2605l_write(DRV2605L_REG_MODE, 0x07);

    //  drv2605l_write(DRV2605L_REG_FEEDBACK_CTRL,0xB6);

#if FB_ERM_LRA == 0
    /* ERM settings */
    drv2605l_write(DRV2605L_REG_RATED_VOLTAGE, (RATED_VOLTAGE / 21.33) * 1000);
#    if ERM_OPEN_LOOP == 0
    drv2605l_write(DRV2605L_REG_OVERDRIVE_CLAMP_VOLTAGE, (((V_PEAK * (DRIVE_TIME + BLANKING_TIME + IDISS_TIME)) / 0.02133) / (DRIVE_TIME - 0.0003)));
#    elif ERM_OPEN_LOOP == 1
    drv2605l_write(DRV2605L_REG_OVERDRIVE_CLAMP_VOLTAGE, (V_PEAK / 0.02196));
#    endif
#elif FB_ERM_LRA == 1
    drv2605l_write(DRV2605L_REG_RATED_VOLTAGE, ((V_RMS * sqrt(1 - ((4 * ((150 + (SAMPLE_TIME * 50)) * 0.000001)) + 0.0003) * F_LRA) / 0.02071)));
#    if LRA_OPEN_LOOP == 0
    drv2605l_write(DRV2605L_REG_OVERDRIVE_CLAMP_VOLTAGE, ((V_PEAK / sqrt(1 - (F_LRA * 0.0008)) / 0.02133)));
#    elif LRA_OPEN_LOOP == 1
    drv2605l_write(DRV2605L_REG_OVERDRIVE_CLAMP_VOLTAGE, (V_PEAK / 0.02196));
#    endif
#endif

    DRVREG_FBR FB_SET;
    FB_SET.Bits.ERM_LRA      = FB_ERM_LRA;
    FB_SET.Bits.BRAKE_FACTOR = FB_BRAKEFACTOR;
    FB_SET.Bits.LOOP_GAIN    = FB_LOOPGAIN;
    FB_SET.Bits.BEMF_GAIN    = 0; /* auto-calibration populates this field*/
    drv2605l_write(DRV2605L_REG_FEEDBACK_CTRL, (uint8_t)FB_SET.Byte);

    DRVREG_CTRL1 C1_SET;
    C1_SET.Bits.C1_DRIVE_TIME    = DRIVE_TIME;
    C1_SET.Bits.C1_AC_COUPLE     = AC_COUPLE;
    C1_SET.Bits.C1_STARTUP_BOOST = STARTUP_BOOST;
    drv2605l_write(DRV2605L_REG_CTRL1, (uint8_t)C1_SET.Byte);

    DRVREG_CTRL2 C2_SET;
    C2_SET.Bits.C2_BIDIR_INPUT   = BIDIR_INPUT;
    C2_SET.Bits.C2_BRAKE_STAB    = BRAKE_STAB;
    C2_SET.Bits.C2_SAMPLE_TIME   = SAMPLE_TIME;
    C2_SET.Bits.C2_BLANKING_TIME = BLANKING_TIME;
    C2_SET.Bits.C2_IDISS_TIME    = IDISS_TIME;
    drv2605l_write(DRV2605L_REG_CTRL2, (uint8_t)C2_SET.Byte);

    DRVREG_CTRL3 C3_SET;
    C3_SET.Bits.C3_LRA_OPEN_LOOP   = LRA_OPEN_LOOP;
    C3_SET.Bits.C3_N_PWM_ANALOG    = N_PWM_ANALOG;
    C3_SET.Bits.C3_LRA_DRIVE_MODE  = LRA_DRIVE_MODE;
    C3_SET.Bits.C3_DATA_FORMAT_RTO = DATA_FORMAT_RTO;
    C3_SET.Bits.C3_SUPPLY_COMP_DIS = SUPPLY_COMP_DIS;
    C3_SET.Bits.C3_ERM_OPEN_LOOP   = ERM_OPEN_LOOP;
    C3_SET.Bits.C3_NG_THRESH       = NG_THRESH;
    drv2605l_write(DRV2605L_REG_CTRL3, (uint8_t)C3_SET.Byte);

    DRVREG_CTRL4 C4_SET;
    C4_SET.Bits.C4_ZC_DET_TIME   = ZC_DET_TIME;
    C4_SET.Bits.C4_AUTO_CAL_TIME = AUTO_CAL_TIME;
    drv2605l_write(DRV2605L_REG_CTRL4, (uint8_t)C4_SET.Byte);

    drv2605l_write(DRV2605L_REG_LIBRARY_SELECTION, DRV2605L_LIBRARY);

    drv2605l_write(DRV2605L_REG_GO, 0x01);

    /* 0x00 sets DRV2605 out of standby and to use internal trigger
     * 0x01 sets DRV2605 out of standby and to use external trigger */
    drv2605l_write(DRV2605L_REG_MODE, 0x00);

    // Play greeting sequence
    drv2605l_write(DRV2605L_REG_GO, 0x00);
    drv2605l_write(DRV2605L_REG_WAVEFORM_SEQUENCER_1, DRV2605L_GREETING);
    drv2605l_write(DRV2605L_REG_GO, 0x01);
}

void drv2605l_rtp_init(void) {
    drv2605l_write(DRV2605L_REG_GO, 0x00);
    drv2605l_write(DRV2605L_REG_RTP_INPUT, 20); // 20 is the lowest value I've found where haptics can still be felt.
    drv2605l_write(DRV2605L_REG_MODE, 0x05);
    drv2605l_write(DRV2605L_REG_GO, 0x01);
}

void drv2605l_amplitude(uint8_t amplitude) {
    drv2605l_write(DRV2605L_REG_RTP_INPUT, amplitude);
}

void drv2605l_pulse(uint8_t sequence) {
    drv2605l_write(DRV2605L_REG_GO, 0x00);
    drv2605l_write(DRV2605L_REG_WAVEFORM_SEQUENCER_1, sequence);
    drv2605l_write(DRV2605L_REG_GO, 0x01);
}
