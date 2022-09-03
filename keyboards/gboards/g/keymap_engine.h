/* If for some reason you're still here, maybe due to horror, shock or
 * some other godforsaken reason. Meet X Macros.
 *
 * The we abuse the include system to generate data structures that are
 * used by the internal chording engine. The alternative to this is
 * using a external generator (Like is done for the ASETNIOP base keymaps)
 * With this disgusting bodge, you can just edit your .defs and compile!
 */
#include "g/engine.h"

// Clear all X Macros
#define PRES BLANK
#define KEYS BLANK
#define SUBS BLANK
#define EXEC BLANK
#define SPEC BLANK

// Process single key pushes
#undef PRES
#define PRES P_KEYMAP
const struct keyEntry keyDict[] = {
#include "dicts.def"
};
#undef PRES
#define PRES BLANK

// Process Combos
#undef KEYS
#define KEYS K_ACTION
#include "dicts.def"
#undef KEYS
#define KEYS BLANK

#undef KEYS
#define KEYS K_KEYMAP
const struct comboEntry PROGMEM cmbDict[] = {
#include "dicts.def"
};
#undef KEYS
#define KEYS BLANK

// Process String stubs
#undef SUBS
#define SUBS S_ACTION
#include "dicts.def"
#undef SUBS
#define SUBS BLANK

// Generate dict for strings
#undef SUBS
#define SUBS S_KEYMAP
const struct stringEntry PROGMEM strDict[] = {
#include "dicts.def"
};
#undef SUBS
#define SUBS BLANK

// Generate function stubs
#undef EXEC
#define EXEC X_ACTION
#include "dicts.def"
#undef EXEC
#define EXEC BLANK

// Process the function structure
#undef EXEC
#define EXEC X_KEYMAP
const struct funcEntry funDict[] = {
#include "dicts.def"
};
#undef EXEC
#define EXEC BLANK

// Handle Special calls
#undef SPEC
#define SPEC Z_KEYMAP
const struct specialEntry spcDict[] = {
#include "dicts.def"
};
#undef SPEC
#define SPEC BLANK

// Test for collisions!
// Switch statement will explode on duplicate
// chords. This will be optimized out
#undef PRES
#undef KEYS
#undef SUBS
#undef EXEC
#undef SPEC
#define PRES TEST_COLLISION
#define KEYS TEST_COLLISION
#define SUBS TEST_COLLISION
#define EXEC TEST_COLLISION
#define SPEC TEST_COLLISION
void testCollisions(void) {
    C_SIZE bomb = 0;
    switch (bomb) {
#include "dicts.def"
    }
}

// Test for unexpected input
// Should return blank lines for all valid input
#undef PRES
#undef KEYS
#undef SUBS
#undef EXEC
#undef SPEC
#define PRES BLANK
#define KEYS BLANK
#define SUBS BLANK
#define EXEC BLANK
#define SPEC BLANK
#include "dicts.def"

// Get size data back into the engine
size_t funcsLen   = ARRAY_SIZE(funDict);
size_t stringLen  = ARRAY_SIZE(strDict);
size_t keyLen     = ARRAY_SIZE(keyDict);
size_t comboLen   = ARRAY_SIZE(cmbDict);
size_t specialLen = ARRAY_SIZE(spcDict);
