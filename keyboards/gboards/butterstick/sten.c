#include "sten.h"

// Chord state
uint32_t cChord 		= 0;		// Current Chord
int		 chordIndex 	= 0;		// Keys in previousachord
int32_t  chordState[32];			// Full Chord history
#define  QWERBUF		24			// Size of chords to buffer for output

bool	 repeatFlag 	= false;	// Should we repeat?
uint32_t pChord 		= 0;		// Previous Chord
int		 pChordIndex 	= 0;		// Keys in previousachord
uint32_t pChordState[32];			// Previous chord sate 
uint32_t stickyBits = 0;			// Or'd with every incoming press
#ifndef NO_DEBUG
char debugMsg[32];
#endif

// StenoLayer
uint32_t releasedChord	= 0;		// Keys released from current chord
uint32_t tChord			= 0;		// Protects state of cChord

#ifndef STENOLAYERS
uint32_t stenoLayers[] = { PWR };
size_t 	 stenoLayerCount = ARRAY_SIZE(stenoLayers);
#endif

// Mode state
enum MODE { STENO = 0, QWERTY, COMMAND };
enum MODE pMode;
bool QWERSTENO = false;
#ifdef ONLYQWERTY
enum MODE cMode = QWERTY;
#else
enum MODE cMode = STENO;
#endif

// Command State
#define MAX_CMD_BUF   20
uint8_t	 CMDLEN 	= 0;
uint8_t	 CMDBUF[MAX_CMD_BUF];

// Key Repeat state
bool     inChord  		= false;
bool	 repEngaged 	= false;
uint16_t repTimer 		= 0;
#define  REP_INIT_DELAY 750
#define  REP_DELAY 		25

// Mousekeys state
bool	inMouse 		= false;
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
#ifndef NO_DEBUG
		uprintf("Fallback Toggle\n");
#endif
		QWERSTENO = !QWERSTENO;
		
		goto out;
	}

	// handle command mode
	if (cChord == (PWR | FN | RD | RZ)) {
#ifndef NO_DEBUG
		uprintf("COMMAND Toggle\n");
#endif
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
#ifndef NO_DEBUG
		uprintf("Switching to QMK\n");
#endif
		layer_on(1);
		goto out;
	}

	// Lone FN press, toggle QWERTY
#ifndef ONLYQWERTY
	if (cChord == FN) {
		(cMode == STENO) ? (cMode = QWERTY) : (cMode = STENO);
		goto out;
	}
#endif

	// Check for Plover momentary
	if (cMode == QWERTY && (cChord & FN)) {
		cChord ^= FN;
		goto steno;
	}

	// Do QWERTY and Momentary QWERTY
	if (cMode == QWERTY || (cMode == COMMAND) || (cChord & (FN | PWR))) {
		processChord(false);
		goto out;
	}

	// Fallback NKRO Steno
	if (cMode == STENO && QWERSTENO) {
		processChord(true);
		goto out;
	}

steno:
	// Hey that's a steno chord!
	inChord = false;
	chordIndex = 0;
	cChord = 0;
	return true; 

out:
	cChord = 0;
	inChord = false;
	chordIndex = 0;
	clear_keyboard();
	repEngaged  = false;
	for (int i = 0; i < 32; i++)
		chordState[i] = 0xFFFF;

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
	if (cMode != QWERTY || !inChord) return;

	// Check timers
#ifndef NO_REPEAT
	if (repEngaged && timer_elapsed(repTimer) > REP_DELAY) {
		// Process Key for report
		processChord(false);

		// Send report to host
		send_keyboard_report();
		clear_keyboard();
		repTimer = timer_read();
	}

	if (!repEngaged && timer_elapsed(repTimer) > REP_INIT_DELAY) {
		repEngaged = true;
	}
#endif
};

// For Plover NKRO
uint32_t processFakeSteno(bool lookup) { 
	P( LSU,				SEND(KC_Q););
	P( LSD,				SEND(KC_A););
	P( LFT,				SEND(KC_W););
	P( LP,				SEND(KC_E););
	P( LH,				SEND(KC_R););
	P( LK,				SEND(KC_S););
	P( LW,				SEND(KC_D););
	P( LR,				SEND(KC_F););
	P( ST1,				SEND(KC_T););
	P( ST2,				SEND(KC_G););
	P( LA,				SEND(KC_C););
	P( LO,				SEND(KC_V););
	P( RE,				SEND(KC_N););
	P( RU,				SEND(KC_M););
	P( ST3,				SEND(KC_Y););
	P( ST4,				SEND(KC_H););
	P( RF,				SEND(KC_U););
	P( RP,				SEND(KC_I););
	P( RL,				SEND(KC_O););
	P( RT,				SEND(KC_P););
	P( RD,				SEND(KC_LBRC););
	P( RR,				SEND(KC_J););
	P( RB,				SEND(KC_K););
	P( RG,				SEND(KC_L););
	P( RS,				SEND(KC_SCLN););
	P( RZ,				SEND(KC_COMM););
	P( LNO,				SEND(KC_1););
	P( RNO,				SEND(KC_1););

	return 0;
}

// Traverse the chord history to a given point
// Returns the mask to use
void processChord(bool useFakeSteno) {
	// Save the clean chord state
	uint32_t savedChord = cChord;

	// Apply Stick Bits if needed
	if (stickyBits != 0) {
		cChord |= stickyBits;
		for (int i = 0; i <= chordIndex; i++)
			chordState[i] |= stickyBits;
	}

	// Strip FN
	if (cChord & FN) cChord ^= FN;

	// First we test if a whole chord was passsed
	// If so we just run it handling repeat logic
	if (useFakeSteno && processFakeSteno(true) == cChord) {
		processFakeSteno(false);
		return;
	} else if (processQwerty(true) == cChord) {
		processQwerty(false);
		// Repeat logic
		if (repeatFlag) {
			restoreState();
			repeatFlag = false;
			processChord(false);
		} else {
			saveState(cChord);
		}
		return;
	}

	// Iterate through chord picking out the individual 
	// and longest chords
	uint32_t bufChords[QWERBUF];
	int 	 bufLen		= 0;
	uint32_t mask		= 0;

	// We iterate over it multiple times to catch the longest
	// chord. Then that gets addded to the mask and re run.
	while (savedChord != mask) {
		uint32_t test  	 		= 0;
		uint32_t longestChord	= 0;

		for (int i = 0; i <= chordIndex; i++) {
			cChord = chordState[i] & ~mask;
			if (cChord == 0)
				continue;

			// Assume mid parse Sym is new chord
			if (i != 0 && test != 0 && (cChord ^ test) == PWR) {
				longestChord = test;
				break;
			}

			// Lock SYM layer in once detected
			if (mask & PWR)
				cChord |= PWR;


			// Testing for keycodes
			if (useFakeSteno) {
				test = processFakeSteno(true);
			} else {
				test = processQwerty(true);
			}
		 
			if (test != 0) {
				longestChord = test;
			}
		}
		
		mask |= longestChord;
		bufChords[bufLen] = longestChord;
		bufLen++;

		// That's a loop of sorts, halt processing
		if (bufLen >= QWERBUF) {
			return;
		}
	}
	
	// Now that the buffer is populated, we run it
	for (int i = 0; i < bufLen ; i++) {
		cChord = bufChords[i];
		if (useFakeSteno) {
			processFakeSteno(false);
		} else {
			processQwerty(false);
		}
	}

	// Save state in case of repeat
	if (!repeatFlag) {			
		saveState(savedChord);
	}

	// Restore cChord for held repeat
	cChord = savedChord;

	return;
}
void saveState(uint32_t cleanChord) {
	pChord = cleanChord;
	pChordIndex = chordIndex;
	for (int i = 0; i < 32; i++) 
		pChordState[i] = chordState[i];
}
void restoreState(void) {
	cChord = pChord;
	chordIndex = pChordIndex;
	for (int i = 0; i < 32; i++) 
		chordState[i] = pChordState[i];
}

// Macros for calling from keymap.c
void SEND(uint8_t kc) {
	// Send Keycode, Does not work for Quantum Codes
	if (cMode == COMMAND && CMDLEN < MAX_CMD_BUF) {
#ifndef NO_DEBUG
		uprintf("CMD LEN: %d BUF: %d\n", CMDLEN, MAX_CMD_BUF);
#endif
		CMDBUF[CMDLEN] = kc;
		CMDLEN++;
	} 

	if (cMode != COMMAND) register_code(kc);
	return;
}
void REPEAT(void) {
	if (cMode != QWERTY)
		return;

	repeatFlag = true;
	return;
}
void SET_STICKY(uint32_t stick) {
	stickyBits = stick;
	return;
}
void SWITCH_LAYER(int layer) {
	if (keymapsCount >= layer) 
		layer_on(layer);
}
void CLICK_MOUSE(uint8_t kc) {
#ifdef MOUSEKEY_ENABLE
	mousekey_on(kc);
	mousekey_send();

	// Store state for later use
	inMouse = true;
	mousePress = kc;
#endif
}
