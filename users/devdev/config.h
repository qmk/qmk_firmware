 /* Copyright 2021 Dane Evans
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

/* Disable unused and unneeded features to reduce on firmware size */
#if defined(LOCKING_SUPPORT_ENABLE)
#    undef LOCKING_SUPPORT_ENABLE
#endif

#if defined(OLED_FONT_H)
#    undef OLED_FONT_H
#endif


#define OLED_FONT_H "users/devdev/glcdfont.c"
