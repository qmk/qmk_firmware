#include "badger_audio.h"

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
    default:
      break;
  }
  #endif
}
