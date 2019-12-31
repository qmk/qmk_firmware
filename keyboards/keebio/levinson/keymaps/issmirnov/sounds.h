// ................................................................ Audio Sounds
#pragma once
#ifdef AUDIO_ENABLE
// Songs come from quantum/audio/song_list.h
float song_startup  [][2] = SONG(STARTUP_SOUND);
float song_goodbye  [][2] = SONG(GOODBYE_SOUND);
float song_overwatch[][2] = SONG(OVERWATCH_THEME);
#undef AUDIO_VOICES
#endif
