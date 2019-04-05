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

// Bitfield representing the current chord and it's changes
uint32_t cChord = 0;				// Current Chord
uint32_t pChord = 0;				// Previous Chord
uint32_t chordState[32];			// Full Chord history
int		 chordIndex = 0;			// Keys in current chord
extern const uint32_t verticals[];	// Vertical pairs
extern size_t verticalCount;		// Len of verticals
extern size_t keymapsCount;			// Total keymaps
extern uint32_t vertMask;			// Mask of all vertical cols
#define QWERBUF	12					// Size of chords to buffer for output

// Function defs
uint32_t		processQwerty(void);
bool 			processFakeSteno(void);
void 			clickMouse(uint8_t kc);
void 			SEND(uint8_t kc);
uint32_t 		getLastCol(int depth);

// Mode state
enum MODE { STENO = 0, QWERTY, COMMAND };
enum MODE cMode = STENO;
enum MODE pMode;
bool QWERSTENO = false;

// Command State
#define MAX_CMD_BUF 20
uint8_t CMDBUF[MAX_CMD_BUF];
uint8_t CMDLEN = 0;

// Key Repeat state
bool     inChord  = false;
uint16_t repTimer = 0;
#define  REP_DELAY 250

// Mousekeys state
bool	inMouse = false;
int8_t	mousePress;

// See if a given chord is pressed. 
// P will return 
// PJ will continue processing, removing the found chord 
//#define PJ(chord, act) if ((cChord & (chord)) == (chord)) { cChord ^= chord; act; }
//#define P(chord, act)  if (cChord == (chord)) { act; cChord ^= chord; return true;}
//
#define P(chord, act) if ((cChord & (chord)) == (chord)) {act; return chord;}
#define PJ(chord, act) if ((cChord & (chord)) == (chord)) {act; return chord;}

//#define PJ(chord, act) if ((cChord & (chord)) == (chord)) { cChord ^= chord; act; return;}

// All Steno Codes
// Shift to internal representation
#define STN(n) (1L<<n)

//i.e) S(teno)R(ight)F
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


// All processing done at chordUp goes through here
bool send_steno_chord_user(steno_mode_t mode, uint8_t chord[6]) { 
	// Check for mousekeys, this is release
#ifdef MOUSEKEY_ENABLE
	if (inMouse) {
		inMouse = false;
		mousekey_off(mousePress);
		mousekey_send();
	}
#endif

	// Toggle Serial/QWERTY steno
	if (cChord == (PWR | FN | ST1 | ST2)) {
		uprintf("Fallback Toggle\n");
		QWERSTENO = !QWERSTENO;
		
		goto out;
	}

	// handle command mode
	if (cChord == (PWR | FN | RD | RZ)) {
		uprintf("COMMAND Toggle\n");
		if (cMode != COMMAND) {   // Entering Command Mode
			CMDLEN = 0;
			pMode = cMode;
			cMode = COMMAND;
		} else {                  // Exiting Command Mode
			cMode = pMode;

			// Press all and release all
			for (int i = 0; i < CMDLEN; i++) {
				register_code(CMDBUF[i]);
			}
			clear_keyboard();
		}

		goto out;
	}

	// Handle Gaming Toggle,
	if (cChord == (PWR | FN | ST4 | ST3) && keymapsCount > 1) {
		uprintf("Switching to QMK\n");
		layer_on(1);
		goto out;
	}

	// Lone FN press, toggle QWERTY
	if (cChord == FN) {
		(cMode == STENO) ? (cMode = QWERTY) : (cMode = STENO);
		goto out;
	}

	// Check for Plover momentary
	if (cMode == QWERTY && (cChord & FN)) {
		cChord ^= FN;
		goto steno;
	}

	// Do QWERTY and Momentary QWERTY
	if (cMode == QWERTY || (cMode == COMMAND) || (cChord & (FN | PWR))) {
		// Try to process entire chord, store leftovers
		if (cChord & FN)  cChord ^= FN;
		while (cChord != pChord) {
				pChord = cChord;
				cChord ^= processQwerty();
		}
	
		// Check if the entire chord has been processed
		// If not, walk back through the history trying to process columns
		// These get buffered and written in reverse order
		uint32_t bufChords[QWERBUF];
		int bufLen = 0;
		uint32_t pMask = 0;


		while (cChord != 0 && chordIndex > 0) {
				uint32_t mask = getLastCol(chordIndex-1);
				if ((pMask & mask) == 0) {
					bufChords[bufLen] = cChord & mask;
					bufLen++;
					pMask |= mask;
				}
				chordIndex--;
		}

		// Now that the buffer is populated, we run it
		for (int i = bufLen; i > 0; i--) {
			cChord = bufChords[i-1];
			processQwerty();
		}
	
		// In theory, we have a clean buffer here, otherwise
		// we say 'fuck it' and just hamfist the rest of the 
		// unprocessed chords after removing the cols
		cChord = pChord & ~vertMask;
		for (int i = 0; cChord != 0 && i < 10; i++)
			cChord ^= processQwerty();

		goto out;
	}

	// Fallback NKRO Steno
	if (cMode == STENO && QWERSTENO) {
		processFakeSteno();
		goto out;
	}

steno:
	// Hey that's a steno chord!
	inChord = false;
	chordIndex = 0;
	cChord = 0;
	return true; 

out:
	inChord = false;
	chordIndex = 0;
	clear_keyboard();
	cChord = 0;

	for (int i = 0; i < 32; i++) 
			chordState[i] = 0;
	return false;
}

// Update Chord State 
bool process_steno_user(uint16_t keycode, keyrecord_t *record) { 
	// Everything happens in here when steno keys come in.
	// Bail on keyup
	if (!record->event.pressed) return true;

	// Update key repeat timers
	repTimer = timer_read();
	inChord  = true;

	// Switch on the press adding to chord
	bool pr = record->event.pressed;
	switch (keycode) {
			// Mods and stuff
			case STN_ST1:			pr ? (cChord |= (ST1)): (cChord &= ~(ST1)); break;
			case STN_ST2:			pr ? (cChord |= (ST2)): (cChord &= ~(ST2)); break;
			case STN_ST3:			pr ? (cChord |= (ST3)): (cChord &= ~(ST3)); break;
			case STN_ST4:			pr ? (cChord |= (ST4)): (cChord &= ~(ST4)); break;
			case STN_FN:			pr ? (cChord |= (FN)) : (cChord &= ~(FN)); break;
			case STN_PWR:			pr ? (cChord |= (PWR)): (cChord &= ~(PWR)); break;
			case STN_N1...STN_N6:	pr ? (cChord |= (LNO)): (cChord &= ~(LNO)); break;
			case STN_N7...STN_NC:	pr ? (cChord |= (RNO)): (cChord &= ~(RNO)); break;

			// All the letter keys
			case STN_S1:			pr ? (cChord |= (LSU)) : (cChord &= ~(LSU));  break;
			case STN_S2:			pr ? (cChord |= (LSD)) : (cChord &= ~(LSD));  break;
			case STN_TL:			pr ? (cChord |= (LFT)) : (cChord &= ~(LFT)); break;
			case STN_KL:			pr ? (cChord |= (LK)) : (cChord &= ~(LK)); break;
			case STN_PL:			pr ? (cChord |= (LP)) : (cChord &= ~(LP)); break;
			case STN_WL:			pr ? (cChord |= (LW)) : (cChord &= ~(LW)); break;
			case STN_HL:			pr ? (cChord |= (LH)) : (cChord &= ~(LH)); break;
			case STN_RL:			pr ? (cChord |= (LR)) : (cChord &= ~(LR)); break;
			case STN_A:				pr ? (cChord |= (LA)) : (cChord &= ~(LA)); break;
			case STN_O:				pr ? (cChord |= (LO)) : (cChord &= ~(LO)); break;
			case STN_E:				pr ? (cChord |= (RE)) : (cChord &= ~(RE)); break;
			case STN_U:				pr ? (cChord |= (RU)) : (cChord &= ~(RU)); break;
			case STN_FR:			pr ? (cChord |= (RF)) : (cChord &= ~(RF)); break;
			case STN_RR:			pr ? (cChord |= (RR)) : (cChord &= ~(RR)); break;
			case STN_PR:			pr ? (cChord |= (RP)) : (cChord &= ~(RP)); break;
			case STN_BR:			pr ? (cChord |= (RB)) : (cChord &= ~(RB)); break;
			case STN_LR:			pr ? (cChord |= (RL)) : (cChord &= ~(RL)); break;
			case STN_GR:			pr ? (cChord |= (RG)) : (cChord &= ~(RG)); break;
			case STN_TR:			pr ? (cChord |= (RT)) : (cChord &= ~(RT)); break;
			case STN_SR:			pr ? (cChord |= (RS)) : (cChord &= ~(RS)); break;
			case STN_DR:			pr ? (cChord |= (RD)) : (cChord &= ~(RD)); break;
			case STN_ZR:			pr ? (cChord |= (RZ)) : (cChord &= ~(RZ)); break;
	}

	// Store previous state for fastQWER
	if (pr) {
		chordState[chordIndex] = cChord; 
		chordIndex++;
	}

	return true; 
}
void matrix_scan_user(void) {
	// We abuse this for early sending of key
	// Key repeat only on QWER/SYMB layers
	if (cMode != QWERTY) return;

	// Check timers
#ifndef NO_REPEAT
	if (timer_elapsed(repTimer) > REP_DELAY) {
		// Process Key for report
		processQwerty();

		// Send report to host
		send_keyboard_report();
		repTimer = timer_read();
	}
#endif
};

// Helpers
bool processFakeSteno(void) {
	PJ( LSU,			SEND(KC_Q););
	PJ( LSD,			SEND(KC_A););
	PJ( LFT,			SEND(KC_W););
	PJ( LP,				SEND(KC_E););
	PJ( LH,				SEND(KC_R););
	PJ( LK,				SEND(KC_S););
	PJ( LW,				SEND(KC_D););
	PJ( LR,				SEND(KC_F););
	PJ( ST1,			SEND(KC_T););
	PJ( ST2,			SEND(KC_G););
	PJ( LA,				SEND(KC_C););
	PJ( LO,				SEND(KC_V););
	PJ( RE,				SEND(KC_N););
	PJ( RU,				SEND(KC_M););
	PJ( ST3,			SEND(KC_Y););
	PJ( ST4,			SEND(KC_H););
	PJ( RF,				SEND(KC_U););
	PJ( RP,				SEND(KC_I););
	PJ( RL,				SEND(KC_O););
	PJ( RT,				SEND(KC_P););
	PJ( RD,				SEND(KC_LBRC););
	PJ( RR,				SEND(KC_J););
	PJ( RB,				SEND(KC_K););
	PJ( RG,				SEND(KC_L););
	PJ( RS,				SEND(KC_SCLN););
	PJ( RZ,				SEND(KC_COMM););
	PJ( LNO,			SEND(KC_1););
	PJ( RNO,			SEND(KC_1););

	return false;
}
void clickMouse(uint8_t kc) {
#ifdef MOUSEKEY_ENABLE
	mousekey_on(kc);
	mousekey_send();

	// Store state for later use
	inMouse = true;
	mousePress = kc;
#endif
}
void SEND(uint8_t kc) {
	// Send Keycode, Does not work for Quantum Codes
	if (cMode == COMMAND && CMDLEN < MAX_CMD_BUF) {
		uprintf("CMD LEN: %d BUF: %d\n", CMDLEN, MAX_CMD_BUF);
		CMDBUF[CMDLEN] = kc;
		CMDLEN++;
	} 

	if (cMode != COMMAND) register_code(kc);
	return;
}

// Traverse the chord history to a given point
// Returns the mask to use
uint32_t getLastCol(int depth) {
	for (int j = 0; j < verticalCount; j++) {
		if (depth == 0) { 
			if ((chordState[0] & verticals[j]) != 0) return verticals[j];
		} else {
			if (((chordState[depth] ^ chordState[depth-1]) & verticals[j]) != 0) 
				return verticals[j];
		}
	}
	return 0;
}
