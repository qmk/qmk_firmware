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
#include "DRV2605L.h"
#include "print.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


uint8_t DRV2605L_transfer_buffer[2];
uint8_t DRV2605L_tx_register[0];
uint8_t DRV2605L_read_buffer[0];
uint8_t DRV2605L_read_register;


void DRV_write(uint8_t drv_register, uint8_t settings) {
  DRV2605L_transfer_buffer[0] = drv_register;
  DRV2605L_transfer_buffer[1] = settings;
  i2c_transmit(DRV2605L_BASE_ADDRESS << 1, DRV2605L_transfer_buffer, 2, 100);
}

uint8_t DRV_read(uint8_t regaddress) {
#ifdef __AVR__
  i2c_readReg(DRV2605L_BASE_ADDRESS << 1,
    regaddress, DRV2605L_read_buffer, 1, 100);
  DRV2605L_read_register = (uint8_t)DRV2605L_read_buffer[0];
#else
  DRV2605L_tx_register[0] = regaddress;
  if (MSG_OK != i2c_transmit_receive(DRV2605L_BASE_ADDRESS << 1,
    DRV2605L_tx_register, 1,
    DRV2605L_read_buffer, 1
)){
    printf("err reading reg \n");
  }
  DRV2605L_read_register = (uint8_t)DRV2605L_read_buffer[0];
#endif
return DRV2605L_read_register;
}

void DRV_init(void)
{
  i2c_init();
  /* 0x07 sets DRV2605 into calibration mode */
  DRV_write(DRV_MODE,0x07); 

//  DRV_write(DRV_FEEDBACK_CTRL,0xB6);
    
  #if FB_ERM_LRA == 0
    /* ERM settings */
  DRV_write(DRV_RATED_VOLT, (RATED_VOLTAGE/21.33)*1000);
  #if ERM_OPEN_LOOP == 0
  DRV_write(DRV_OVERDRIVE_CLAMP_VOLT, (((V_PEAK*(DRIVE_TIME+BLANKING_TIME+IDISS_TIME))/0.02133)/(DRIVE_TIME-0.0003))); 
  #elif ERM_OPEN_LOOP == 1
  DRV_write(DRV_OVERDRIVE_CLAMP_VOLT, (V_PEAK/0.02196));
  #endif
  #elif FB_ERM_LRA == 1
  DRV_write(DRV_RATED_VOLT, ((V_RMS * sqrt(1 - ((4 * ((150+(SAMPLE_TIME*50))*0.000001)) + 0.0003)* F_LRA)/0.02071)));
  #if LRA_OPEN_LOOP == 0
    DRV_write(DRV_OVERDRIVE_CLAMP_VOLT, ((V_PEAK/sqrt(1-(F_LRA*0.0008))/0.02133)));
  #elif LRA_OPEN_LOOP == 1
    DRV_write(DRV_OVERDRIVE_CLAMP_VOLT, (V_PEAK/0.02196));
  #endif
  #endif
      
  DRVREG_FBR FB_SET;
    FB_SET.Bits.ERM_LRA = FB_ERM_LRA;
    FB_SET.Bits.BRAKE_FACTOR = FB_BRAKEFACTOR;
    FB_SET.Bits.LOOP_GAIN =FB_LOOPGAIN;
    FB_SET.Bits.BEMF_GAIN = 0; /* auto-calibration populates this field*/
    DRV_write(DRV_FEEDBACK_CTRL, (uint8_t) FB_SET.Byte);
  DRVREG_CTRL1 C1_SET;
    C1_SET.Bits.C1_DRIVE_TIME = DRIVE_TIME;
    C1_SET.Bits.C1_AC_COUPLE = AC_COUPLE;
    C1_SET.Bits.C1_STARTUP_BOOST = STARTUP_BOOST;
    DRV_write(DRV_CTRL_1, (uint8_t) C1_SET.Byte);
  DRVREG_CTRL2 C2_SET;
    C2_SET.Bits.C2_BIDIR_INPUT = BIDIR_INPUT;
    C2_SET.Bits.C2_BRAKE_STAB = BRAKE_STAB;
    C2_SET.Bits.C2_SAMPLE_TIME = SAMPLE_TIME;
    C2_SET.Bits.C2_BLANKING_TIME = BLANKING_TIME;
    C2_SET.Bits.C2_IDISS_TIME = IDISS_TIME;
    DRV_write(DRV_CTRL_2, (uint8_t) C2_SET.Byte);
  DRVREG_CTRL3 C3_SET;
    C3_SET.Bits.C3_LRA_OPEN_LOOP = LRA_OPEN_LOOP;
    C3_SET.Bits.C3_N_PWM_ANALOG = N_PWM_ANALOG;
    C3_SET.Bits.C3_LRA_DRIVE_MODE = LRA_DRIVE_MODE;
    C3_SET.Bits.C3_DATA_FORMAT_RTO = DATA_FORMAT_RTO;
    C3_SET.Bits.C3_SUPPLY_COMP_DIS = SUPPLY_COMP_DIS;
    C3_SET.Bits.C3_ERM_OPEN_LOOP = ERM_OPEN_LOOP;
    C3_SET.Bits.C3_NG_THRESH = NG_THRESH;
    DRV_write(DRV_CTRL_3, (uint8_t) C3_SET.Byte);
  DRVREG_CTRL4 C4_SET;
    C4_SET.Bits.C4_ZC_DET_TIME = ZC_DET_TIME;
    C4_SET.Bits.C4_AUTO_CAL_TIME = AUTO_CAL_TIME;
    DRV_write(DRV_CTRL_4, (uint8_t) C4_SET.Byte);
  DRV_write(DRV_LIB_SELECTION,LIB_SELECTION);

  DRV_write(DRV_GO, 0x01);

  /* 0x00 sets DRV2605 out of standby and to use internal trigger
   * 0x01 sets DRV2605 out of standby and to use external trigger */
  DRV_write(DRV_MODE,0x00); 

//Play greeting sequence
  DRV_write(DRV_GO, 0x00);
  DRV_write(DRV_WAVEFORM_SEQ_1, DRV_GREETING);
  DRV_write(DRV_GO, 0x01);
}

void DRV_pulse(uint8_t sequence)
{
  DRV_write(DRV_GO, 0x00);
  DRV_write(DRV_WAVEFORM_SEQ_1, sequence);
  DRV_write(DRV_GO, 0x01);
}