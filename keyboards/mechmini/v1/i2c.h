/*
Copyright 2016 Luiz Ribeiro <luizribeiro@gmail.com>
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __I2C_H__
#define __I2C_H__

void i2c_init(void);
void i2c_set_bitrate(uint16_t bitrate_khz);
uint8_t i2c_send(uint8_t address, uint8_t *data, uint16_t length);

#endif
