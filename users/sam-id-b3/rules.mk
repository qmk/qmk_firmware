 /* Copyright 2021 id-b3
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

WPM_ENABLE = yes # Enable words per minute counting

SRC += sam-id-b3.c
SRC += process_records.c

ifeq ($(strip $(OLED_DRIVER_ENABLE)), yes)
    SRC += oled_stuff.c
endif

ifeq ($(strip $(ENCODER_ENABLE)), yes)
    SRC += encoder_stuff.c
endif

ifeq ($(strip $(PIMORONI_TRACKBALL_ENABLE)), yes)
    SRC += pimoroni_trackball.c
endif