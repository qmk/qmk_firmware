/*
Copyright 2017 Truong Hoang Tung <mnpq.raven@gmail.com> @mnpqraven

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
#include "quantum.h"
#include "eeprom.h"

//i don't think i need this ?
//TODO: test rgb without this snippet
//#ifdef RGBLIGHT_ENABLE
//#include "rgblight.h"
//#endif

//Layers Definition
#define CL 0
#define NM_MODE 2
#define VI_MODE 3
#define FN3 4
#define ACCENT 5
#define ACCENT_CAP 6

//Unicode Definitions
#define DE_AE     UC(0x00E4)
#define DE_SS     UC(0x00DF)
#define DE_OE     UC(0x00F6)
#define DE_UE     UC(0x00FC)
#define DE_AE_CAP UC(0x00C4)
#define DE_OE_CAP UC(0x00D6)
#define DE_UE_CAP UC(0x00DC)
enum tap_dancers {
  CTL_NM = 0,
  GUI_NM = 1,
  ALT_NM = 2,
  SFT_NM = 3,
};
