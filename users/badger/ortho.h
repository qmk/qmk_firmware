/*
Copyright 2020 Dan White <opensource@bluetufa.com>

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

#include "badger.h"

enum OrthoLayers {
  _QWERTY_MAC_ORTHO,
  _MOVE_MAC_ORTHO,
  _QWERTY_LINUX_ORTHO,
  _MOVE_LINUX_ORTHO,
  _RAISE,
  _LOWER,
  _ADJUST_ORTHO
};

enum OrthoKeys {
  KC_MAC1 = CS_DOWN + 1,
  KC_MAC2,
  KC_LYRC,
  KC_FIRST
};

#define P_ADJ LT(_ADJUST_ORTHO, KC_BSPC)
#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)
#define MOMAC LT(_MOVE_MAC_ORTHO, KC_ESC)
#define MOLNX LT(_MOVE_LINUX_ORTHO, KC_ESC)

void playSongForLayer(int currentLayer);

#ifdef AUDIO_ENABLE
#define QWERTY_LAYER_SONG H__NOTE(_G6),  H__NOTE(_D6),  Q__NOTE(_A5),   Q__NOTE(_E5), 
#define MAC_LAYER_SONG    H__NOTE(_E5),  H__NOTE(_A5),  Q__NOTE(_D6),   Q__NOTE(_G6), \
        ED_NOTE(_E7),     E__NOTE(_CS7), E__NOTE(_E6),  E__NOTE(_A6),   M__NOTE(_CS7, 20),
#define LONG_AG_SWAP      Q__NOTE(_G5),  Q__NOTE(_D6),  Q__NOTE(_A6),   Q__NOTE(_E7), \
        SD_NOTE(_B5),     SD_NOTE(_A5),  SD_NOTE(_B5),  SD_NOTE(_A5),
#define LONG_AG_NORM      Q__NOTE(_DS4), Q__NOTE(_DS4), B__NOTE(_C5),
#define MOVE_LAYER_SONG   E__NOTE(_GS6), E__NOTE(_A6),  S__NOTE(_REST), ED_NOTE(_E7), \
        S__NOTE(_REST),   ED_NOTE(_GS7),
#define RAISE_LAYER_SONG  W__NOTE(_BF5), Q__NOTE(_A5),  W__NOTE(_BF5),  Q__NOTE(_A5),  W__NOTE(_E6), Q__NOTE(_B5),
#define LOWER_LAYER_SONG  Q__NOTE(_DS4), E__NOTE(_DS4), E__NOTE(_DS6),  Q__NOTE(_DS5), \
        E__NOTE(_DS5),    E__NOTE(_DS6), Q__NOTE(_E5),  E__NOTE(_E5),   E__NOTE(_DS6), Q__NOTE(_DS5),
#define CAPS_ON           W__NOTE(_E5),  Q__NOTE(_BF5), W__NOTE(_E5),   Q__NOTE(_BF5), W__NOTE(_E5), Q__NOTE(_BF5),
#define CAPS_OFF          W__NOTE(_E5),  Q__NOTE(_BF5),
#endif
