//
//  WinXP.h
//  
//
//  Created by Peter Mai on 7/3/20.
//

#ifndef WinXP_h
#define WinXP_h

#ifdef AUDIO_ENABLE
//  Creating eighth note triplet values to work with in the clarinet opening of Brahms 1
#define EIGHTH_NOTE_TRIPLET(note) MUSICAL_NOTE(note, 5.3)
#define ET_NOTE(n) EIGHTH_NOTE_TRIPLET(n)

float Brahms_Opening[][2] = {
    Q__NOTE(C4), Q__NOTE(F4), Q__NOTE(EF4), QD_NOTE(DF4), E__NOTE(C4), E__NOTE(EF4), E__NOTE(DF4), E__NOTE(BF3), E__NOTE(D4), E__NOTE(C4), E__NOTE(AF3), E__NOTE(BF3), E__NOTE(F3), H__NOTE(AF3), Q__NOTE(GF3)
}

float Brahms_Clarinet1[][2] = {
    H__NOTE(C5), Q__NOTE(AF4), H__NOTE(F4), Q__NOTE(AF5), QD_NOTE(F5), E__NOTE(DF5), E__NOTE(F5), E__NOTE(DF5), H__NOTE(BF4), Q__NOTE(DF6), H__NOTE(E5), Q__NOTE(G5), H__NOTE(AF4), Q__NOTE(F5), H__NOTE(G4), ET_NOTE(BF4), ET_NOTE(AF4), ET_NOTE(G4), Q__NOTE(G4)
}

float Win_XP_start[][2] = {
    E__NOTE(EF6), S__NOTE(EF5), ED_NOTE(BF5), E__NOTE(AF5), E__NOTE(EF5), E__NOTE(EF6), QD_NOTE(BF5)
}
#define STARTUP_SONG SONG(Brahms_Opening)

#endif


#endif
/* WinXP_h */
