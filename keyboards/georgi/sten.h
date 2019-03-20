// 2019, g Heavy Industries

#include QMK_KEYBOARD_H
#include "mousekey.h"
#include "keymap.h"
#include "keymap_steno.h"

// Bitfield representing the current chord
uint32_t cChord = 0;

// See if a given chord is pressed. 
// P will return 
// PJ will continue processing, removing the found chord 
#define P(chord, act)  if (cChord == (chord)) { act; return true; }
#define PJ(chord, act) if ((cChord & (chord)) == (chord)) { cChord ^= chord; act; }

// All Steno Codes
// Shift to internal representation
#define STN(n) (1L<<n)

//i.e) S(teno)R(ight)F
enum ORDER { 
		SFN = 0, SPWR, SST1, SST2, SST3, SST4, SNUM,
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
#define NUM STN(SNUM) // No distinction between left and right

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

bool 		processQwerty(void);
bool 		processFakeSteno(void);
void 		clickMouse(uint8_t kc);
void 		SEND(uint8_t kc);
extern int 	getKeymapCount(void);

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
#define  REP_DELAY 300

// Mousekeys state
bool	inMouse = false;
int8_t	mousePress;

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
	if (cChord == (PWR | FN | ST2 | ST3) && getKeymapCount() > 1) {
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
		if (cChord & FN)  cChord ^= FN;
		processQwerty();
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
	cChord = 0;
	return true; 

out:
	inChord = false;
	clear_keyboard();
	cChord = 0;
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
			case STN_N1...STN_N6: 
			case STN_N7...STN_NC:	pr ? (cChord |= (NUM)): (cChord &= ~(NUM)); break;

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

	// Check for key repeat in QWERTY mode
	return true; 
}
void matrix_scan_user(void) {
	// We abuse this for early sending of key
	// Key repeat only on QWER/SYMB layers
	if (cMode != QWERTY) return;

	// Check timers
	if (timer_elapsed(repTimer) > REP_DELAY) {
		// Process Key for report
		processQwerty();

		// Send report to host
		send_keyboard_report();
		repTimer = timer_read();
	}
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
	PJ( NUM,			SEND(KC_1););

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
