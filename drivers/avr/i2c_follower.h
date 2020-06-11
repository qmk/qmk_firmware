/*  Copyright (C) 2019 Elia Ritterbusch
 +
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
/* Library made by: g4lvanix
 * GitHub repository: https://github.com/g4lvanix/I2C-follower-lib

 Info: Inititate the library by giving the required address.
       Read or write to the necessary buffer according to the opperation.
 */

#ifndef I2C_follower_H
#define I2C_follower_H

#define I2C_follower_REG_COUNT 30

extern volatile uint8_t i2c_follower_reg[I2C_follower_REG_COUNT];

void i2c_follower_init(uint8_t address);
void i2c_follower_stop(void);

#endif  // I2C_follower_H
