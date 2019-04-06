#include "keymap_steno.h"
#include "ergodox_ez.h"
#include <string.h>

static char chords[3][9] = { "         ", "         ", "         " };
/* #TPH FPLTD  ABCDEFGHIJ
 * SKWR*RBGSZ  KLMNOPQRST
 *   AO?EU       UVWXY
 * A = position 1...
 * position Z isn't displayed, it's there for "don't display this"
 */
static const char display_data[] PROGMEM    = "?######SSTKPWHRAO**???**EUFRPBLGTSD######Z";
static const char ndisplay_data[] PROGMEM   = "?######112K3W4R50**???**EU6R7B8G9SD######Z";
static const char displaypos_data[] PROGMEM = "WAAAAAAKKBLCMDNUVOOWWWOOXYFPGQHRISJAAAAAAT";
static const char stenopos_data[] PROGMEM   = "XAAAAAABBCDEFGHIJKKXXXKKLMNOPQRSTUVAAAAAAW";

static inline uint8_t
display(uint8_t key) {
    return pgm_read_byte(display_data + key);
}

static inline uint8_t
ndisplay(uint8_t key) {
    return pgm_read_byte(ndisplay_data + key);
}

static inline uint8_t
displaypos(uint8_t key) {
    return pgm_read_byte(displaypos_data + key) - 'A';
}

static inline uint8_t
stenopos(uint8_t key) {
    return pgm_read_byte(stenopos_data + key) - 'A';
}

static void lcd_goto(int pos) {
    if (pos >= 20) {
      pos += 2;
    }
    lcd_move(pos / 10, pos % 10);
}

// update key display for a key that's been changed
bool
postprocess_steno_user(uint16_t keycode, keyrecord_t *record, steno_mode_t mode, uint8_t chord[6], int8_t pressed) {
    if (keycode < STN__MIN || keycode > STN__MAX) {
        return true;
    }
    uint8_t key = (keycode - QK_STENO);
    uint8_t idx = (key / 7);
    uint8_t bit = 1 << (6 - (key % 7));
    uint8_t pos = displaypos(key);
    lcd_goto(pos);
    if (IS_PRESSED(record->event)) {
	lcd_char(display(key));
    } else {
	if (chord[idx] & bit) {
            uint8_t ch = display(key);
	    if (ch == '#' || ch == '*') {
	        lcd_char('+');
	    } else {
		// tolower() for cheapskates
	        lcd_char(ch | 0x20);
	    }
	} else {
	    lcd_char(' ');
	}
    }
    return true;
}

bool
send_steno_chord_user(steno_mode_t mode, uint8_t chord[6]) {
    bool numbering = false;
    bool vowel = false;
    char keys[26];
    memset(keys, ' ', 25);
    keys[25] = '\0';
    /* the first key is FN, the next six are N1 through N6,
     * so that's all but the first bit of the 7 bits in the
     * first byte. Last key is ZR, with N7 through NC before
     * it, same deal.
     */
    if ((chord[0] & 0x3F) || (chord[5] & 0x7E)) {
        numbering = true;
    }
    if ((chord[2] & 0x30) || (chord[3] & 0x0C)) {
	vowel = true;
    }
    for (int i = 0; i < 6; ++i) {
	if (!chord[i])
	    continue;
	for (int j = 0; j < 7; ++j) {
	    uint8_t bit = 1 << j;
	    uint8_t idx = (i * 7) + (6 - j);
	    if (chord[i] & bit) {
		// write in steno order now
		uint8_t pos = stenopos(idx);
		uint8_t ch = numbering ? ndisplay(idx) : display(idx);
		keys[pos] = ch;
	    }
	}
    }
    if (!vowel && keys[10] == ' ') {
	keys[10] = '-';
    }
    char *k = keys;
    for (int i = 0; i < 25; ++i) {
	if (keys[i] != ' ') {
	    *k++ = keys[i];
	}
    }
    *k = '\0';
    uint8_t len = k - keys;
    // help my family is dying
    // push fewer keys at once
    // no
    if (len > 20) {
	keys[17] = '.';
	keys[18] = '.';
	keys[19] = '.';
	len = 20;
    }
    lcd_move(3, 0);
    for (int i = 0; i < 20 - len; ++i) {
	lcd_char(' ');
    }
    lcd_string(keys, len);
    for (int i = 0; i < 3; ++i) {
	lcd_move(i, 11);
	lcd_string(chords[i], 9);
    }
    memcpy(chords[0], chords[1], 9);
    memcpy(chords[1], chords[2], 9);
    if (len > 9) {
	memcpy(chords[2], keys, 6);
	chords[2][6] = '.';
	chords[2][7] = '.';
	chords[2][8] = '.';
    } else {
	memcpy(chords[2] + (9 - len), keys, len);
	for (int i = 0; i < (9 - len); ++i) {
	    chords[2][i] = ' ';
	}
    }
    lcd_move(0, 0);
    lcd_string("          ", 10);
    lcd_move(1, 0);
    lcd_string("          ", 10);
    lcd_move(2, 2);
    lcd_string("     ", 5);
    return true;
}
