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

#if DRV2605L_FB_ERM_LRA == 0
    /* ERM settings */
    drv2605l_write(DRV2605L_REG_RATED_VOLTAGE, (DRV2605L_RATED_VOLTAGE / 21.33) * 1000);
#    if DRV2605L_ERM_OPEN_LOOP == 0
    drv2605l_write(DRV2605L_REG_OVERDRIVE_CLAMP_VOLTAGE, (((DRV2605L_V_PEAK * (DRV2605L_DRIVE_TIME + DRV2605L_BLANKING_TIME + DRV2605L_IDISS_TIME)) / 0.02133) / (DRV2605L_DRIVE_TIME - 0.0003)));
#    elif DRV2605L_ERM_OPEN_LOOP == 1
    drv2605l_write(DRV2605L_REG_OVERDRIVE_CLAMP_VOLTAGE, (DRV2605L_V_PEAK / 0.02196));
#    endif
#elif DRV2605L_FB_ERM_LRA == 1
    drv2605l_write(DRV2605L_REG_RATED_VOLTAGE, ((DRV2605L_V_RMS * sqrt(1 - ((4 * ((150 + (DRV2605L_SAMPLE_TIME * 50)) * 0.000001)) + 0.0003) * DRV2605L_F_LRA) / 0.02071)));
#    if DRV2605L_LRA_OPEN_LOOP == 0
    drv2605l_write(DRV2605L_REG_OVERDRIVE_CLAMP_VOLTAGE, ((DRV2605L_V_PEAK / sqrt(1 - (DRV2605L_F_LRA * 0.0008)) / 0.02133)));
#    elif DRV2605L_LRA_OPEN_LOOP == 1
    drv2605l_write(DRV2605L_REG_OVERDRIVE_CLAMP_VOLTAGE, (DRV2605L_V_PEAK / 0.02196));
#    endif
#endif

    drv2605l_reg_feedback_ctrl_t reg_feedback_ctrl;
    reg_feedback_ctrl.bits.ERM_LRA      = DRV2605L_FB_ERM_LRA;
    reg_feedback_ctrl.bits.BRAKE_FACTOR = DRV2605L_FB_BRAKEFACTOR;
    reg_feedback_ctrl.bits.LOOP_GAIN    = DRV2605L_FB_LOOPGAIN;
    reg_feedback_ctrl.bits.BEMF_GAIN    = 0; /* auto-calibration populates this field*/
    drv2605l_write(DRV2605L_REG_FEEDBACK_CTRL, (uint8_t)reg_feedback_ctrl.raw);

    drv2605l_reg_ctrl1_t reg_ctrl1;
    reg_ctrl1.bits.C1_DRIVE_TIME    = DRV2605L_DRIVE_TIME;
    reg_ctrl1.bits.C1_AC_COUPLE     = DRV2605L_AC_COUPLE;
    reg_ctrl1.bits.C1_STARTUP_BOOST = DRV2605L_STARTUP_BOOST;
    drv2605l_write(DRV2605L_REG_CTRL1, (uint8_t)reg_ctrl1.raw);

    drv2605l_reg_ctrl2_t reg_ctrl2;
    reg_ctrl2.bits.C2_BIDIR_INPUT   = DRV2605L_BIDIR_INPUT;
    reg_ctrl2.bits.C2_BRAKE_STAB    = DRV2605L_BRAKE_STAB;
    reg_ctrl2.bits.C2_SAMPLE_TIME   = DRV2605L_SAMPLE_TIME;
    reg_ctrl2.bits.C2_BLANKING_TIME = DRV2605L_BLANKING_TIME;
    reg_ctrl2.bits.C2_IDISS_TIME    = DRV2605L_IDISS_TIME;
    drv2605l_write(DRV2605L_REG_CTRL2, (uint8_t)reg_ctrl2.raw);

    drv2605l_reg_ctrl3_t reg_ctrl3;
    reg_ctrl3.bits.C3_LRA_OPEN_LOOP   = DRV2605L_LRA_OPEN_LOOP;
    reg_ctrl3.bits.C3_N_PWM_ANALOG    = DRV2605L_N_PWM_ANALOG;
    reg_ctrl3.bits.C3_LRA_DRIVE_MODE  = DRV2605L_LRA_DRIVE_MODE;
    reg_ctrl3.bits.C3_DATA_FORMAT_RTO = DRV2605L_DATA_FORMAT_RTO;
    reg_ctrl3.bits.C3_SUPPLY_COMP_DIS = DRV2605L_SUPPLY_COMP_DIS;
    reg_ctrl3.bits.C3_ERM_OPEN_LOOP   = DRV2605L_ERM_OPEN_LOOP;
    reg_ctrl3.bits.C3_NG_THRESH       = DRV2605L_NG_THRESH;
    drv2605l_write(DRV2605L_REG_CTRL3, (uint8_t)reg_ctrl3.raw);

    drv2605l_reg_ctrl4_t reg_ctrl4;
    reg_ctrl4.bits.C4_ZC_DET_TIME   = DRV2605L_ZC_DET_TIME;
    reg_ctrl4.bits.C4_AUTO_CAL_TIME = DRV2605L_AUTO_CAL_TIME;
    drv2605l_write(DRV2605L_REG_CTRL4, (uint8_t)reg_ctrl4.raw);

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
