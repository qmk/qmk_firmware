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
#include <stdlib.h>

uint8_t DRV2605L_transfer_buffer[20];

void DRV_write(uint8_t drv_register, uint8_t settings) {
  DRV2605L_transfer_buffer[0] = drv_register;
  DRV2605L_transfer_buffer[1] = settings;
  i2c_transmit(DRV2605L_BASE_ADDRESS << 1, DRV2605L_transfer_buffer, 2, 100);
}

/*void DRV_read()
{
//TODO
} */

void DRV_init(void)
{
  i2c_init();
  i2c_start(DRV2605L_BASE_ADDRESS);

  //0x07 sets DRV2605 into calibration mode
  DRV_write(DRV_FEEDBACK_CTRL,0xB6);
  DRV_write(DRV_RATED_VOLT, 0x53); 
  DRV_write(DRV_OVERDRIVE_CLAMP_VOLT, 0x60); 
  DRV_write(DRV_CTRL_1,0x93);
  DRV_write(DRV_CTRL_2,0xF5);
  DRV_write(DRV_CTRL_3,0x80);
  DRV_write(DRV_LIB_SELECTION,0x06);
  DRV_write(DRV_MODE,0x07); 
  //start autocalibration
  DRV_write(DRV_GO, 0x01);

  //0x00 sets DRV2605 out of standby and to use internal trigger
  //0x01 sets DRV2605 out of standby and to use external trigger
  DRV_write(DRV_MODE,0x00); 
  
  //0x06: LRA library
  DRV_write(DRV_WAVEFORM_SEQ_1, 0x01);

  // 0xB9: LRA, 4x brake factor, medium gain, 7.5x back EMF
  // 0x39: ERM, 4x brake factor, medium gain, 1.365x back EMF
  
  //TODO: set rest of initiation

}

void DRV_pulse(uint8_t sequence)
{
  DRV_write(DRV_GO, 0x00);
  DRV_write(DRV_WAVEFORM_SEQ_1, sequence);
  DRV_write(DRV_GO, 0x01);
}