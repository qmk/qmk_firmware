// 2019, g Heavy Industries
// Blessed mother of Christ, please keep this readable
// and protect us from segfaults. For thine is the clock,
// the slave and the master. Until we return from main.
//
// Amen.

#include QMK_KEYBOARD_H
#include "mousekey.h"
#include "keymap.h"
#include "keymap_steno.h"
#include "wait.h"

extern size_t keymapsCount;			// Total keymaps
extern uint32_t cChord;				// Current Chord

// Function defs
void 			processChord(bool useFakeSteno);
uint32_t		processQwerty(bool lookup);
uint32_t 		processFakeSteno(bool lookup);
void 			clickMouse(uint8_t kc);
void 			SEND(uint8_t kc);
void 			REPEAT(void);
void 			saveState(uint32_t cChord);
void 			restoreState(void);

// Keymap helper
#define P(chord, act) if (cChord == (chord)) { if (!lookup) {act;} return chord;}

// Shift to internal representation
// i.e) S(teno)R(ight)F
#define STN(n) (1L<<n)
enum ORDER { 
		SFN = 0, SPWR, SST1, SST2, SST3, SST4, SNUML, SNUMR,
		SLSU, SLSD, SLT, SLK, SLP, SLW, SLH, SLR, SLA, SLO, 
		SRE, SRU, SRF, SRR, SRP, SRB, SRL, SRG, SRT, SRS, SRD, SRZ
};

// Break it all out
#define FN	STN(SFN)
#define PWR	STN(SPWR)
#define ST1 STN(SST1)
#define ST2 STN(SST2)
#define ST3 STN(SST3)
#define ST4 STN(SST4)
#define LNO STN(SNUML) // STN1-6
#define RNO STN(SNUMR) // STN7-C

#define LSU STN(SLSU)
#define LSD STN(SLSD)
#define LFT STN(SLT)  // (L)e(F)t (T), preprocessor conflict
#define LK  STN(SLK)
#define LP  STN(SLP)
#define LW  STN(SLW)
#define LH  STN(SLH)
#define LR  STN(SLR)
#define LA  STN(SLA)
#define LO  STN(SLO)

#define RE  STN(SRE)
#define RU  STN(SRU)
#define RF  STN(SRF)
#define RR  STN(SRR)
#define RP  STN(SRP)
#define RB  STN(SRB)
#define RL  STN(SRL)
#define RG  STN(SRG)
#define RT  STN(SRT)
#define RS  STN(SRS)
#define RD  STN(SRD)
#define RZ  STN(SRZ)
