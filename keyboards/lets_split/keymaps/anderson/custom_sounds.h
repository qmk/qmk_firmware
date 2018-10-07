#include "musical_notes.h"

#ifndef CUSTOM_SOUNDS_H
#define CUSTOM_SOUNDS_H

#ifdef KEY_SOUNDS

float ALPHA_SND[][2] = {
    S__NOTE(_C5), S__NOTE(_G4), S__NOTE(_C4)
};
float BETA_SND[][2] = {
    S__NOTE(_C5), S__NOTE(_G5), S__NOTE(_C6)
};
float SHIFT_SND[][2] = {
    E__NOTE(_E3)
};
float ALT_SND[][2] = {
    E__NOTE(_G3)
};
float CTRL_SND[][2] = {
    E__NOTE(_B3)
};
float ESC_SND[][2] = {
    S__NOTE(_D5), S__NOTE(_D6)
};
float LANG_SWITCH_SOUND[][2] = {
    S__NOTE(_C6), S__NOTE(_C5), S__NOTE(_C6)
};
float LOCK_SND[][2] = {
    E__NOTE(_C5), E__NOTE(_G5), E__NOTE(_C6), E__NOTE(_G6), E__NOTE(_C7)
};
float CTRL_BREAK_SND[][2] = {
    S__NOTE(_A4), S__NOTE(_REST), S__NOTE(_GS4), S__NOTE(_REST), S__NOTE(_G4)
};

#endif

#endif

