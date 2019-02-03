#include QMK_KEYBOARD_H

// Bitfield representing the current chord
uint32_t cChord = 0;
enum MODE { STENO = 0, QWERTY, COMMAND };
enum MODE cMode = STENO;


// See if a given chord is pressed. 
// P will return, PJ will continue processing
//
// chord: The keys OR'd together
// act:   code to eval if pressed
// jmp:   bool to jump to out
#define PROCESS(jmp, chord, act) if ((cChord & (chord)) == (chord)) { act; if (jmp) return; }
#define P(chord, act)  PROCESS(true,  (chord), act)
#define PJ(chord, act) PROCESS(false, (chord), act)

// Defs for hooks
void processQwerty(void);
void processSymbol(void);

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
#define FN 	STN(SFN)
#define PWR	STN(SPWR)
#define ST1 STN(SST1)
#define ST2 STN(SST2)
#define ST3 STN(SST3)
#define ST4 STN(SST4)
#define NUM STN(SNUM)

#define LSU STN(SLSU)
#define LSD STN(SLSD)
#define LFT STN(SLT) // (L)e(F)t (T), preprocessor conflict
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

// Intercept for send
bool send_steno_chord_user(steno_mode_t mode, uint8_t chord[6]) { 
	// Lone FN press, toggle QWERTY
	if (cChord == STN(FN)) {
		uprintf("Switching to QWER\n");
		(cMode == STENO) ? (cMode = QWERTY) : (cMode = STENO);

		clear_keyboard();
		cChord = 0;
		return false;
	}

	// Check for Symbol combo
	if ((cChord & PWR) && !(cChord & FN)) {
		processSymbol();

		clear_keyboard();
		cChord = 0;
		return false; 
	}

	// Do pseudoQWERTY
	if (cMode == QWERTY) {
		processQwerty();

		clear_keyboard();
		cChord = 0;
		return false;
	}

	// TODO: Do command mode
	// Hey that's a steno chord!
	cChord = 0;
	return true; 
}

// Update the current chord as keys come in
bool process_steno_user(uint16_t keycode, keyrecord_t *record) { 
	// Bail on keyup, TODO: Find a way to keep this together
	bool pr = record->event.pressed;
	if (pr == false) return true;

	// Switch on the press adding to chord
	switch (keycode) {
			// Mods and stuff
			case STN_ST1:			pr ? (cChord |= (ST1)): (cChord &= ~(ST1)); break;
			case STN_ST2:			pr ? (cChord |= (ST2)): (cChord &= ~(ST2)); break;
			case STN_ST3:			pr ? (cChord |= (ST3)): (cChord &= ~(ST3)); break;
			case STN_ST4:			pr ? (cChord |= (ST4)): (cChord &= ~(ST4)); break;
			case STN_PWR:			pr ? (cChord |= (PWR)): (cChord &= ~(PWR)); break;
			case STN_N1...STN_N6: 
			case STN_N7...STN_NC: 	pr ? (cChord |= (NUM)): (cChord &= ~(NUM)); break;
			case STN_FN:			pr ? (cChord |= (FN)) : (cChord &= ~(FN)); break;

			// All the letter keys
			case STN_S1: 			pr ? (cChord |= (LSU)) : (cChord &= ~(LSU));  break;
			case STN_S2: 			pr ? (cChord |= (LSD)) : (cChord &= ~(LSD));  break;
			case STN_TL: 			pr ? (cChord |= (LFT)) : (cChord &= ~(LFT)); break;
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
			case STN_GR: 			pr ? (cChord |= (RG)) : (cChord &= ~(RG)); break;
			case STN_TR:			pr ? (cChord |= (RT)) : (cChord &= ~(RT)); break;
			case STN_SR:			pr ? (cChord |= (RS)) : (cChord &= ~(RS)); break;
			case STN_DR:			pr ? (cChord |= (RD)) : (cChord &= ~(RD)); break;
			case STN_ZR:			pr ? (cChord |= (RZ)) : (cChord &= ~(RZ)); break;
	}
	return true; 
}
