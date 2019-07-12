/*
Copyright 2019 Massdrop Inc.

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

#pragma once

//Macros to Enable, Disable, and Update USB 5V bus connections
#define USBC_CFG_5V1_VAR                    sr_exp_data.bit.E_VBUS_1    //Variable storing USBC-1 5V Bus state
#define USBC_CFG_5V1_ENA                    1                           //Value to enable USBC-1 5V Bus
#define USBC_CFG_5V1_DIS                    0                           //Value to disable USBC-1 5V Bus
#define USBC_CFG_5V1_UPDATE                 SR_EXP_WriteData()          //Command to run to update value
#define USBC_CFG_5V2_VAR                    sr_exp_data.bit.E_VBUS_2    //Variable storing USBC-2 5V Bus state
#define USBC_CFG_5V2_ENA                    1                           //Value to enable USBC-1 5V Bus
#define USBC_CFG_5V2_DIS                    0                           //Value to disable USBC-1 5V Bus
#define USBC_CFG_5V2_UPDATE                 SR_EXP_WriteData()          //Command to run to update value
