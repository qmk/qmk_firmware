#include "ortho.h"
#include "badger_audio.h"

#ifndef BADGER_ORTHO_H
#define BADGER_ORTHO_H

const int _layerCount = 7;

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
        dprintf("CAPS_LOCK state: %u\n", _capsLockState);
        _capsLockState = !_capsLockState;
        _capsLockState ? PLAY_SONG(capsOnSong) : PLAY_SONG(capsOffSong);
        return true;
      }
      break;
    case AG_SWAP:
      PLAY_SONG(agSwapSong);
      return true;
      break;
    case AG_NORM:
      PLAY_SONG(agNormSong);
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
        if (_currentLayer != _QWERTY_MAC) {
          layer_off(_currentLayer);
        }
        _currentLayer = _QWERTY_MAC;
        layer_on(_currentLayer);
        playSongForLayer(_currentLayer);
        return false;
      }
      break;
    case KC_LYRC:
      if (record->event.pressed) {
        dprintf("LYR CYCLE pressed %u, CURRENT_LAYER: %u\n", keycode, _currentLayer);
        // don't turn off the QWERTY layer
        if (_currentLayer != _QWERTY_MAC) {
          layer_off(_currentLayer);
        }
        // don't lock the ADJUST layer
        // since this is accessible via the ADJUST
        // layer, that will require tricky state management
        if (++_currentLayer == _ADJUST) {
          _currentLayer = _QWERTY_MAC;
        }
        layer_on(_currentLayer);
        playSongForLayer(_currentLayer);
        return false;
      }
      break;
  }
  return true;
}

#endif