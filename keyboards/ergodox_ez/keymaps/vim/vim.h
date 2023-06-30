#include "config.h"
#include "print.h"
#include "keycode.h"
#include "quantum.h"
#include "quantum_keycodes.h"

#define NOR_MOD TO(NORMAL_MODE)
#define INS_MOD TO(INSERT_MODE)

#define PRESS(keycode) register_code16(keycode)
#define RELEASE(keycode) unregister_code16(keycode)

uint16_t VIM_QUEUE = KC_NO;

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  VIM_A,
  VIM_B,
  VIM_C,
  VIM_CI,
  VIM_D,
  VIM_DI,
  VIM_E,
  VIM_H,
  VIM_I,
  VIM_J,
  VIM_K,
  VIM_L,
  VIM_O,
  VIM_P,
  VIM_S,
  VIM_U,
  VIM_V,
  VIM_VI,
  VIM_W,
  VIM_X,
  VIM_Y,
  EPRM,
  VRSN,
  RGB_SLD,
};

void VIM_APPEND(void);
void VIM_APPEND_LINE(void);
void VIM_BACK(void);
void VIM_CHANGE_BACK(void);
void VIM_CHANGE_DOWN(void);
void VIM_CHANGE_END(void);
void VIM_CHANGE_INNER_WORD(void);
void VIM_CHANGE_LEFT(void);
void VIM_CHANGE_LINE(void);
void VIM_CHANGE_RIGHT(void);
void VIM_CHANGE_UP(void);
void VIM_CHANGE_WHOLE_LINE(void);
void VIM_CHANGE_WORD(void);
void VIM_CUT(void);
void VIM_DELETE_BACK(void);
void VIM_DELETE_DOWN(void);
void VIM_DELETE_END(void);
void VIM_DELETE_INNER_WORD(void);
void VIM_DELETE_LEFT(void);
void VIM_DELETE_LINE(void);
void VIM_DELETE_RIGHT(void);
void VIM_DELETE_UP(void);
void VIM_DELETE_WHOLE_LINE(void);
void VIM_DELETE_WORD(void);
void VIM_END(void);
void VIM_JOIN(void);
void VIM_OPEN(void);
void VIM_OPEN_ABOVE(void);
void VIM_PUT(void);
void VIM_SUBSTITUTE(void);
void VIM_UNDO(void);
void VIM_VISUAL_BACK(void);
void VIM_VISUAL_DOWN(void);
void VIM_VISUAL_END(void);
void VIM_VISUAL_INNER_WORD(void);
void VIM_VISUAL_LEFT(void);
void VIM_VISUAL_RIGHT(void);
void VIM_VISUAL_UP(void);
void VIM_VISUAL_WORD(void);
void VIM_WORD(void);
void VIM_YANK(void);

void TAP(uint16_t keycode) {
    PRESS(keycode);
    RELEASE(keycode);
}

void CMD(uint16_t keycode) {
  PRESS(KC_LGUI);
    TAP(keycode);
  RELEASE(KC_LGUI);
}

void CTRL(uint16_t keycode) {
  PRESS(KC_LCTL);
    TAP(keycode);
  RELEASE(KC_LCTL);
}

void SHIFT(uint16_t keycode) {
  PRESS(KC_LSFT);
    TAP(keycode);
  RELEASE(KC_LSFT);
}

void ALT(uint16_t keycode) {
  PRESS(KC_LALT);
    TAP(keycode);
  RELEASE(KC_LALT);
}

/**
 * Sets the `VIM_QUEUE` variable to the incoming keycode.
 * Pass `KC_NO` to cancel the operation.
 * @param keycode
 */
void VIM_LEADER(uint16_t keycode) {
  VIM_QUEUE = keycode;
  switch(keycode) {
    case VIM_C: print("\e[32mc\e[0m"); break;
    case VIM_CI: print("\e[32mi\e[0m"); break;
    case VIM_D: print("\e[32md\e[0m"); break;
    case VIM_DI: print("\e[32mi\e[0m"); break;
    case VIM_V: print("\e[32mv\e[0m"); break;
    case VIM_VI: print("\e[32mi\e[0m"); break;
    case KC_NO: print("❎"); break;
  }
}

/***
 *     #######  #     #  #######       #####   #     #  #######  #######
 *     #     #  ##    #  #            #     #  #     #  #     #     #
 *     #     #  # #   #  #            #        #     #  #     #     #
 *     #     #  #  #  #  #####         #####   #######  #     #     #
 *     #     #  #   # #  #                  #  #     #  #     #     #
 *     #     #  #    ##  #            #     #  #     #  #     #     #
 *     #######  #     #  #######       #####   #     #  #######     #
 *
 */

/**
 * Vim-like `append` command.
 * Works by sending →.
 */
void VIM_APPEND(void) {
  print("\e[31ma\e[0m");
  TAP(KC_RIGHT);
  layer_on(INSERT_MODE);
}

/**
 * Vim-like `back` command
 * Simulates vim's `b` command by sending ⌥←
 */
void VIM_BACK(void) {
  print("\e[31mb\e[0m");
  ALT(KC_LEFT);
}

/**
 * Vim-like `cut` command
 * Simulates vim's `x` command by sending ⇧→ then ⌘X.
 */
void VIM_CUT(void) {
  print("\e[31mx\e[0m");
  SHIFT(KC_RIGHT);
  CMD(KC_X);
}

/**
 * Vim-like `down` command
 * Sends ↓
 */
void VIM_DOWN(void) {
  print("\e[31mj\e[0m");
  TAP(KC_DOWN);
}

/**
 * Vim-like `end` command
 * Simulates vim's `e` command by sending ⌥→
 */
void VIM_END(void) {
  print("\e[31me\e[0m");
  ALT(KC_RIGHT);
}

/**
 * Vim-like `left` command
 * Sends ←
 */
void VIM_LEFT(void) {
  print("\e[31mh\e[0m");
  VIM_LEADER(KC_NO);
  TAP(KC_LEFT);
}

/**
 * Vim-like `open` command.
 * Works by sending ⌘→ to move to the end of the line, `enter` to open a new line,
 * then switching to insert mode.
 */
void VIM_OPEN(void) {
  print("\e[31mo\e[0m");
  VIM_LEADER(KC_NO);
  CMD(KC_RIGHT);
  TAP(KC_ENTER);
  layer_on(INSERT_MODE);
}

/**
 * Vim-like `put` command
 * Simulates vim's `p` command by sending ⌘V
 */
void VIM_PUT(void) {
  print("\e[31mp\e[0m");
  VIM_LEADER(KC_NO);
  CMD(KC_V);
}

/**
 * Vim-like `put before` command
 * Simulates vim's `P` command by sending ↑, ⌘←, then ⌘V
 */
void VIM_PUT_BEFORE(void) {
  print("\e[31mP\e[0m");
  VIM_LEADER(KC_NO);
  TAP(KC_UP);
  CMD(KC_LEFT);
  CMD(KC_V);
}

/**
 * Vim-like `right` command
 * Sends →
 */
void VIM_RIGHT(void) {
  print("\e[31ml\e[0m");
  VIM_LEADER(KC_NO);
  TAP(KC_RIGHT);
}

/**
 * Vim-like `substitute` command
 * Simulates vim's `s` command by sending ⇧→ to select the next character, then
 * ⌘X to cut it, then entering insert mode.
 */
void VIM_SUBSTITUTE(void) {
  print("\e[31ms\e[0m");
  VIM_LEADER(KC_NO);
  SHIFT(KC_RIGHT);
  CMD(KC_X);
  layer_on(INSERT_MODE);
}

/**
 * Vim-like `undo` command
 * Simulates vim's `u` command by sending ⌘Z
 */
void VIM_UNDO(void) {
  print("\e[31mu\e[0m");
  VIM_LEADER(KC_NO);
  CMD(KC_Z);
}

/**
 * Vim-like `up` command
 * Sends ↑
 */
void VIM_UP(void) {
  print("\e[31mk\e[0m");
  VIM_LEADER(KC_NO);
  TAP(KC_UP);
}

/**
 * Vim-like `word` command
 * Simulates vim's `w` command by moving the cursor first to the
 * end of the current word, then to the end of the next word,
 * then to the beginning of that word.
 */
void VIM_WORD(void) {
  print("\e[31mw\e[0m");
  VIM_LEADER(KC_NO);
  PRESS(KC_LALT);
    TAP(KC_RIGHT);
    TAP(KC_RIGHT);
    TAP(KC_LEFT);
  RELEASE(KC_LALT);
}

/**
 * Vim-like `yank` command
 * Simulates vim's `y` command by sending ⌘C
 */
void VIM_YANK(void) {
  print("\e[31my\e[0m");
  VIM_LEADER(KC_NO);
  CMD(KC_C);
}

/**
 * Vim-like `yank line` command
 * Simulates vim's `y` command by sending ⌘← then ⇧⌘→ then ⌘C
 */
void VIM_YANK_LINE(void) {
  print("\e[31mY\e[0m");
  VIM_LEADER(KC_NO);
  CMD(KC_LEFT);
  PRESS(KC_LSFT);
    CMD(KC_RIGHT);
  RELEASE(KC_LSFT);
  CMD(KC_C);
}

/***
 *      #####   #     #  ###  #######  #######  #######  ######
 *     #     #  #     #   #   #           #     #        #     #
 *     #        #     #   #   #           #     #        #     #
 *      #####   #######   #   #####       #     #####    #     #
 *           #  #     #   #   #           #     #        #     #
 *     #     #  #     #   #   #           #     #        #     #
 *      #####   #     #  ###  #           #     #######  ######
 *
 */

/**
 * Vim-like `append to line` command
 * Simulates vim's `A` command by sending ⌘→ then switching to insert mode.
 */
void VIM_APPEND_LINE(void) {
  print("\e[31mA\e[0m");
  VIM_LEADER(KC_NO);
  CMD(KC_RIGHT);
  layer_on(INSERT_MODE);
}

/**
 * Vim-like `change line` command
 * Simulates vim's `C` command by sending ⌃K then switching to insert mode.
 */
void VIM_CHANGE_LINE(void) {
  print("\e[31mC\e[0m");
  VIM_LEADER(KC_NO);
  VIM_DELETE_LINE();
  layer_on(INSERT_MODE);
}

/**
 * Vim-like 'delete line' command
 * Simulates vim's `D` command by sending ⌃K to kill the line
 */
void VIM_DELETE_LINE(void) {
  print("\e[31mD\e[0m");
  VIM_LEADER(KC_NO);
  CTRL(KC_K);
}

/**
 * Vim-like 'join lines' command
 * Simulates vim's `J` command by sending ⌘→ to go to the end of the line, then
 * DELETE to join the lines
 */
void VIM_JOIN(void) {
  print("\e[31mJ\e[0m");
  VIM_LEADER(KC_NO);
  CMD(KC_RIGHT);
  TAP(KC_DELETE);
  VIM_LEADER(KC_NO);
}

/**
 * Vim-like 'open above' command
 * Simulates vim's `O` command by sending ⌘→ to go to the start of the line,
 * enter to move the line down, ↑ to move up to the new line, then switching to
 * insert mode.
 */
void VIM_OPEN_ABOVE(void) {
  print("\e[31mO\e[0m");
  VIM_LEADER(KC_NO);
  CMD(KC_LEFT);
  TAP(KC_ENTER);
  TAP(KC_UP);
  layer_on(INSERT_MODE);
}

/**
 * Vim-like 'change whole line' command
 * Simulates vim's `S` `cc` or `c$` commands by sending ⌘← to go to the start of the line,
 * ⌃K to kill the line, then switching to insert mode.
 */
void VIM_CHANGE_WHOLE_LINE(void) {
  print("\e[31mS\e[0m");
  VIM_LEADER(KC_NO);
  CMD(KC_LEFT);
  VIM_CHANGE_LINE();
}

/***
 *     ######       ######   ######   #######  #######  ###  #     #  #######  ######
 *     #     #      #     #  #     #  #        #         #    #   #   #        #     #
 *     #     #      #     #  #     #  #        #         #     # #    #        #     #
 *     #     #      ######   ######   #####    #####     #      #     #####    #     #
 *     #     #      #        #   #    #        #         #     # #    #        #     #
 *     #     #      #        #    #   #        #         #    #   #   #        #     #
 *     ######       #        #     #  #######  #        ###  #     #  #######  ######
 *
 */

/**
 * Vim-like `delete to end` command
 * Simulates vim's `de` command by sending ⌥⇧→ then ⌘X.
 */
void VIM_DELETE_END(void) {
  print("\e[31me\e[0m");
  VIM_LEADER(KC_NO);
  PRESS(KC_LALT);
    SHIFT(KC_RIGHT); // select to end of this word
  RELEASE(KC_LALT);
  CMD(KC_X);
}

/**
 * Vim-like `delete whole line` command
 * Simulates vim's `dd` command by sending ⌘← to move to start of line,
 * selecting the whole line, then sending ⌘X to cut the line.
 * alternate method: ⌘⌫, ⌃K
 */
void VIM_DELETE_WHOLE_LINE(void) {
  print("\e[31md\e[0m");
  VIM_LEADER(KC_NO);
  CMD(KC_LEFT);
  PRESS(KC_LSFT);
    CMD(KC_RIGHT);
  RELEASE(KC_LSFT);
  CMD(KC_X);
}

/**
 * Vim-like `delete word` command
 * Simulates vim's `dw` command by sending ⌥⇧→→← then ⌘X to select to the start
 * of the next word then cut.
 */
void VIM_DELETE_WORD(void) {
  print("\e[31mw\e[0m");
  VIM_LEADER(KC_NO);
  PRESS(KC_LALT);
    SHIFT(KC_RIGHT); // select to end of this word
    SHIFT(KC_RIGHT); // select to end of next word
    SHIFT(KC_LEFT); // select to start of next word
  RELEASE(KC_LALT);
  CMD(KC_X); // delete selection
}

/**
 * Vim-like `delete back` command
 * Simulates vim's `db` command by selecting to the end of the word then deleting.
 */
void VIM_DELETE_BACK(void) {
  print("\e[31mb\e[0m");
  VIM_LEADER(KC_NO);
  PRESS(KC_LALT);
    SHIFT(KC_LEFT); // select to start of word
    SHIFT(KC_DEL); // delete selection
  RELEASE(KC_LSFT);
}

/**
 * Vim-like `delete left` command
 * Simulates vim's `dh` command by sending ⇧← then ⌘X.
 */
void VIM_DELETE_LEFT(void) {
  print("\e[31mh\e[0m");
  VIM_LEADER(KC_NO);
  SHIFT(KC_LEFT);
  CMD(KC_X);
}

/**
 * Vim-like `delete right` command
 * Simulates vim's `dl` command by sending ⇧→ then ⌘X.
 */
void VIM_DELETE_RIGHT(void) {
  print("\e[31ml\e[0m");
  VIM_LEADER(KC_NO);
  SHIFT(KC_RIGHT);
  CMD(KC_X);
}

/**
 * Vim-like `delete up` command
 * Simulates vim's `dk` command by sending ↑ then deleting the line.
 */
void VIM_DELETE_UP(void) {
  print("\e[31mk\e[0m");
  VIM_LEADER(KC_NO);
  TAP(KC_UP);
  VIM_DELETE_LINE();
}

/**
 * Vim-like `delete down` command
 * Simulates vim's `dj` command by sending ↓ then deleting the line.
 */
void VIM_DELETE_DOWN(void) {
  print("\e[31mj\e[0m");
  VIM_LEADER(KC_NO);
  TAP(KC_DOWN);
  VIM_DELETE_LINE();
}

/***
 *     ######   ###      ######   ######   #######  #######  ###  #     #  #######  ######
 *     #     #   #       #     #  #     #  #        #         #    #   #   #        #     #
 *     #     #   #       #     #  #     #  #        #         #     # #    #        #     #
 *     #     #   #       ######   ######   #####    #####     #      #     #####    #     #
 *     #     #   #       #        #   #    #        #         #     # #    #        #     #
 *     #     #   #       #        #    #   #        #         #    #   #   #        #     #
 *     ######   ###      #        #     #  #######  #        ###  #     #  #######  ######
 *
 */

/**
 * Vim-like `delete inner word` command
 * Simulates vim's `diw` command by moving back then cutting to the end of the word.
 */
void VIM_DELETE_INNER_WORD(void) {
  print("\e[31mw\e[0m");
  VIM_LEADER(KC_NO);
  VIM_BACK();
  VIM_DELETE_END();
}

/***
 *      #####        ######   ######   #######  #######  ###  #     #  #######  ######
 *     #     #       #     #  #     #  #        #         #    #   #   #        #     #
 *     #             #     #  #     #  #        #         #     # #    #        #     #
 *     #             ######   ######   #####    #####     #      #     #####    #     #
 *     #             #        #   #    #        #         #     # #    #        #     #
 *     #     #       #        #    #   #        #         #    #   #   #        #     #
 *      #####        #        #     #  #######  #        ###  #     #  #######  ######
 *
 */

/**
 * Vim-like `change back` command
 * Simulates vim's `cb` command by first deleting to the start of the word,
 * then switching to insert mode.
 */
void VIM_CHANGE_BACK(void) {
  print("\e[31mb\e[0m");
  VIM_LEADER(KC_NO);
  VIM_DELETE_BACK();
  layer_on(INSERT_MODE);
}

/**
 * Vim-like `change down` command
 * Simulates vim's `cj` command by sending ↓ then changing the line.
 */
void VIM_CHANGE_DOWN(void) {
  print("\e[31mj\e[0m");
  VIM_LEADER(KC_NO);
  VIM_DELETE_DOWN();
  layer_on(INSERT_MODE);
}

/**
 * Vim-like `change to end` command
 * Simulates vim's `ce` command by first deleting to the end of the word,
 * then switching to insert mode.
 */
void VIM_CHANGE_END(void) {
  print("\e[31mce\e[0m");
  VIM_LEADER(KC_NO);
  VIM_DELETE_END();
  layer_on(INSERT_MODE);
}

/**
 * Vim-like `change left` command
 * Simulates vim's `ch` command by deleting left then switching to insert mode.
 */
void VIM_CHANGE_LEFT(void) {
  print("\e[31mch\e[0m");
  VIM_LEADER(KC_NO);
  VIM_DELETE_LEFT();
  layer_on(INSERT_MODE);
}

/**
 * Vim-like `change right` command
 * Simulates vim's `cl` command by deleting right then switching to insert mode.
 */
void VIM_CHANGE_RIGHT(void) {
  print("\e[31mcl\e[0m");
  VIM_DELETE_RIGHT();
  layer_on(INSERT_MODE);
}

/**
 * Vim-like `change up` command
 * Simulates vim's `ck` command by deleting up then switching to insert mode.
 */
void VIM_CHANGE_UP(void) {
  print("\e[31mck\e[0m");
  VIM_DELETE_UP();
  layer_on(INSERT_MODE);
}

/**
 * Vim-like `change word` command
 * Simulates vim's `cw` command by first deleting to the end of the word,
 * then switching to insert mode.
 */
void VIM_CHANGE_WORD(void) {
  print("\e[31mcw\e[0m");
  VIM_LEADER(KC_NO);
  VIM_DELETE_WORD();
  layer_on(INSERT_MODE);
}

/***
 *      #####   ###      ######   ######   #######  #######  ###  #     #  #######  ######
 *     #     #   #       #     #  #     #  #        #         #    #   #   #        #     #
 *     #         #       #     #  #     #  #        #         #     # #    #        #     #
 *     #         #       ######   ######   #####    #####     #      #     #####    #     #
 *     #         #       #        #   #    #        #         #     # #    #        #     #
 *     #     #   #       #        #    #   #        #         #    #   #   #        #     #
 *      #####   ###      #        #     #  #######  #        ###  #     #  #######  ######
 *
 */

/**
 * Vim-like `change inner word` command
 * Simulates vim's `ciw` command by deleting the inner word then switching to insert mode.
 */
void VIM_CHANGE_INNER_WORD(void) {
  print("\e[31mciw\e[0m");
  VIM_DELETE_INNER_WORD();
  layer_on(INSERT_MODE);
}

/***
 *     #     #      ######   ######   #######  #######  ###  #     #  #######  ######
 *     #     #      #     #  #     #  #        #         #    #   #   #        #     #
 *     #     #      #     #  #     #  #        #         #     # #    #        #     #
 *     #     #      ######   ######   #####    #####     #      #     #####    #     #
 *      #   #       #        #   #    #        #         #     # #    #        #     #
 *       # #        #        #    #   #        #         #    #   #   #        #     #
 *        #         #        #     #  #######  #        ###  #     #  #######  ######
 *
 */

/**
 * Vim-like `visual select back` command
 * Simulates vim's `vb` command by selecting to the enc of the word.
 */
void VIM_VISUAL_BACK(void) {
  print("\e[31mvb\e[0m");
  VIM_LEADER(KC_NO);
  PRESS(KC_LALT);
    SHIFT(KC_LEFT); // select to start of word
  RELEASE(KC_LALT);
}

/**
 * Vim-like `visual select to end` command
 * Simulates vim's `ve` command by selecting to the end of the word.
 */
void VIM_VISUAL_END(void) {
  print("\e[31mve\e[0m");
  VIM_LEADER(KC_NO);
  PRESS(KC_LALT);
    SHIFT(KC_RIGHT); // select to end of this word
  RELEASE(KC_LALT);
}

/**
 * Vim-like `visual select word` command
 * Simulates vim's `vw` command by selecting to the end of the word.
 */
void VIM_VISUAL_WORD(void) {
  print("\e[31mvw\e[0m");
  VIM_LEADER(KC_NO);
  PRESS(KC_LALT);
    SHIFT(KC_RIGHT); // select to end of this word
    SHIFT(KC_RIGHT); // select to end of next word
    SHIFT(KC_LEFT); // select to start of next word
  RELEASE(KC_LALT);
}

/**
 * Vim-like `visual left` command
 * Simulates vim's `vh` command by sending ⇧←.
 */
void VIM_VISUAL_LEFT(void) {
  print("\e[31mvh\e[0m");
  VIM_LEADER(KC_NO);
  SHIFT(KC_LEFT);
}

/**
 * Vim-like `visual right` command
 * Simulates vim's `vl` command by sending ⇧→.
 */
void VIM_VISUAL_RIGHT(void) {
  print("\e[31mvl\e[0m");
  VIM_LEADER(KC_NO);
  SHIFT(KC_RIGHT);
}

/**
 * Vim-like `visual up` command
 * Simulates vim's `vk` command by sending ⇧↑.
 */
void VIM_VISUAL_UP(void) {
  print("\e[31mvk\e[0m");
  VIM_LEADER(KC_NO);
  SHIFT(KC_UP);
}

/**
 * Vim-like `visual down` command
 * Simulates vim's `vj` command by sending ⇧↓.
 */
void VIM_VISUAL_DOWN(void) {
  print("\e[31mdj\e[0m");
  VIM_LEADER(KC_NO);
  SHIFT(KC_DOWN);
}

/***
 *     #     #  ###      ######   ######   #######  #######  ###  #     #  #######  ######
 *     #     #   #       #     #  #     #  #        #         #    #   #   #        #     #
 *     #     #   #       #     #  #     #  #        #         #     # #    #        #     #
 *     #     #   #       ######   ######   #####    #####     #      #     #####    #     #
 *      #   #    #       #        #   #    #        #         #     # #    #        #     #
 *       # #     #       #        #    #   #        #         #    #   #   #        #     #
 *        #     ###      #        #     #  #######  #        ###  #     #  #######  ######
 *
 */

/**
 * Vim-like `visual inner word` command
 * Simulates vim's `viw` command by moving back then selecting to the end of the word.
 */
void VIM_VISUAL_INNER_WORD(void) {
  print("\e[31mviw\e[0m");
  VIM_LEADER(KC_NO);
  VIM_BACK();
  VIM_VISUAL_END();
}
