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
#include "ortho.h"
#include "badger.h"

int       _currentLayer;
bool      _capsLock;

#ifdef AUDIO_ENABLE
float capsOnSong[][2]                  = SONG(CAPS_ON);
float capsOffSong[][2]                 = SONG(CAPS_OFF);
float defaultLayerSong[][2]            = SONG(QWERTY_LAYER_SONG);
float moveLayerSong[][2]               = SONG(MOVE_LAYER_SONG);
float macLayerSong[][2]                = SONG(MAC_LAYER_SONG);
float raiseLayerSong[][2]              = SONG(RAISE_LAYER_SONG);
float lowerLayerSong[][2]              = SONG(LOWER_LAYER_SONG);
float agSwapSong[][2]                  = SONG(LONG_AG_SWAP);
float agNormSong[][2]                  = SONG(LONG_AG_NORM);
#endif 

__attribute__ ((weak))
void keyboard_post_init_user(void) {
  _capsLock = false;
  _currentLayer = _QWERTY_MAC_ORTHO;
  layer_on(_currentLayer);
}

__attribute__ ((weak))
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  dprintf("Key event recorded. KEYCODE: %u , event: %u\n", keycode, record->event.pressed);
  switch (keycode) {
    case CS_RIGHT:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT(SS_TAP(X_B)SS_TAP(X_ENTER)));
        return false;
      }
      break;
    case CS_DOWN:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT(SS_TAP(X_V)SS_TAP(X_ENTER)));
        return false;
      }
      break;
    case KC_CAPS:
      if (record->event.pressed) {
        dprintf("CAPS_LOCK state: %u\n", _capsLock);
        _capsLock = !_capsLock;
        #ifdef AUDIO_ENABLE
          _capsLock ? PLAY_SONG(capsOnSong) : PLAY_SONG(capsOffSong);
        #endif
        return true;
      }
      break;
    case AG_SWAP:
      #ifdef AUDIO_ENABLE
        PLAY_SONG(agSwapSong);
      #endif
      return true;
      break;
    case AG_NORM:
      #ifdef AUDIO_ENABLE
        PLAY_SONG(agNormSong);
      #endif
      return true;
      break;
    case KC_MAC2:
      if (record->event.pressed) {
        SEND_STRING("ll\n");
        return false;
      }
      break;
    case KC_MAC1:
      if (record->event.pressed) {
        SEND_STRING("open https://www.reddit.com/r/mechanicalkeyboards\n");
        return false;
      }
      break;
    case KC_FIRST:
      if (record->event.pressed) {
        // don't turn off the QWERTY layer
        if (_currentLayer != _QWERTY_MAC_ORTHO) {
          layer_off(_currentLayer);
        }
        _currentLayer = _QWERTY_MAC_ORTHO;
        layer_on(_currentLayer);
        playSongForLayer(_currentLayer);
        return false;
      }
      break;
    case KC_LYRC:
      if (record->event.pressed) {
        dprintf("LYR CYCLE pressed %u, CURRENT_LAYER: %u\n", keycode, _currentLayer);
        // don't turn off the QWERTY layer or the ADJUST layer
        if (_currentLayer != _QWERTY_MAC_ORTHO) {
          layer_off(_currentLayer);
        }
        // don't lock the ADJUST layer
        // since this key is accessible via the ADJUST
        // layer, as it will require tricky state management
        if (++_currentLayer == _ADJUST_ORTHO) {
          _currentLayer = _QWERTY_MAC_ORTHO;
        } else {
          layer_on(_currentLayer);
        }

        playSongForLayer(_currentLayer);
        return false;
      }
      break;
  }
  return true;
}

void playSongForLayer(int currentLayer) {
  #ifdef AUDIO_ENABLE
  switch (currentLayer) {
    case   _QWERTY_LINUX:
      PLAY_SONG(defaultLayerSong);
      break;
    case  _MOVE_LINUX:
      PLAY_SONG(moveLayerSong);
      break;
    case  _QWERTY_MAC:
      PLAY_SONG(macLayerSong);
      break;
    case  _MOVE_MAC:
      PLAY_SONG(moveLayerSong);
      break;
    case  _RAISE:
      PLAY_SONG(raiseLayerSong);
      break;
    case  _LOWER:
      PLAY_SONG(lowerLayerSong);
      break;
    default:
      break;
  }
  #endif
}