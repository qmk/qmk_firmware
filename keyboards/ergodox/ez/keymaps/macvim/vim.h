#include "config.h"
#include "keycode.h"
#include "quantum.h"
#include "quantum_keycodes.h"

#define NOR_MOD TO(NORMAL_MODE)
#define INS_MOD TO(INSERT_MODE)

#define NORMAL_MODE 0
#define INSERT_MODE 1

#define PRESS(keycode) register_code16(keycode)
#define RELEASE(keycode) unregister_code16(keycode)
#define PREVENT_STUCK_MODIFIERS

uint16_t vim_queue;

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  VIM_A,
  VIM_B,
  VIM_D,
  VIM_E,
  VIM_O,
  VIM_P,
  VIM_S,
  VIM_U,
  VIM_V,
  VIM_W,
  VIM_X,
  VIM_Y,
  EPRM,
  VRSN,
  RGB_SLD,
};

void TAP(uint16_t keycode) {
    PRESS(keycode);
    RELEASE(keycode);
}

#define VIM_KEYS_LENGTH 11
#define VIM_LEADERS_LENGTH 4

static const uint16_t VIM_KEYS[VIM_KEYS_LENGTH] = {
  VIM_D, VIM_W, VIM_V,    VIM_B, KC_H,  KC_J,
  KC_K,  KC_L,  KC_X,     VIM_A, VIM_S
};

static const uint16_t VIM_LEADERS[VIM_LEADERS_LENGTH] = {
  VIM_D, VIM_V, KC_LSHIFT, KC_RSHIFT
};

/**
 * Returns true when the keycode is a member of the VIM_KEYS table
 * @param  keycode Keycode
 * @return bool
 */
bool is_vim_key(uint16_t keycode) {
  for (size_t i = 0; i < VIM_KEYS_LENGTH; i++) {
    if (VIM_KEYS[i] == keycode) { return true; }
  }
  return false;
}

/**
 * Returns true when the keycode is a member of the VIM_LEADERS table
 * @param  keycode Keycode
 * @return bool
 */
bool is_vim_leader(uint16_t keycode) {
  for (size_t i = 0; i < VIM_LEADERS_LENGTH; i++) {
    if (VIM_LEADERS[i] == keycode) { return true; }
  }
  return false;
}

/**
 * Sets the `vim_queue` variable to the incoming keycode.
 * Pass `KC_NO` to cancel the operation.
 * @param keycode
 */
void ENQUEUE_VIM_LEADER(uint16_t keycode) {
  vim_queue = keycode;
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
void VIM_COMMAND_A(void) {
  TAP(KC_RIGHT);
  TO(INSERT_MODE);
}

/**
 * Vim-like `back` command
 * Simulates vim's `b` command by sending ⌥←
 */
void VIM_COMMAND_B(void) {
  PRESS(KC_LALT);
    TAP(KC_LEFT);
  RELEASE(KC_LALT);
}

/**
 * Vim-like `end` command
 * Simulates vim's `e` command by sending ⌥→
 */
void VIM_COMMAND_E(void) {
  PRESS(KC_LALT);
    TAP(KC_RIGHT);
  RELEASE(KC_LALT);
}

/**
 * Vim-like `open` command.
 * Works by sending ⌘→ to move to the end of the line, `enter` to open a new line,
 * then switching to insert mode.
 */
void VIM_COMMAND_O(void) {
  PRESS(KC_LGUI);
    TAP(KC_RIGHT);
  RELEASE(KC_LGUI);
  TAP(KC_ENTER);
  TO(INSERT_MODE);
}

/**
 * Vim-like `put` command
 * Simulates vim's `p` command by sending ⌘V
 */
void VIM_COMMAND_P(void) {
  PRESS(KC_LGUI);
    TAP(KC_V);
  RELEASE(KC_LGUI);
}

/**
 * Vim-like `substitute` command
 * Simulates vim's `s` command by sending ⇧→ to select the next character, then
 * ⌘X to cut it, then entering insert mode.
 */
void VIM_COMMAND_S(void) {
  PRESS(KC_LSHIFT);
    TAP(KC_X);
  RELEASE(KC_LSHIFT);
  TO(INSERT_MODE);
}

/**
 * Vim-like `undo` command
 * Simulates vim's `u` command by sending ⌘Z
 */
void VIM_COMMAND_U(void) {
  PRESS(KC_LGUI);
    TAP(KC_Z);
  RELEASE(KC_LGUI);
}

/**
 * Vim-like `word` command
 * Simulates vim's `w` command by moving the cursor first to the
 * end of the current word, then to the end of the next word,
 * then to the beginning of that word.
 */
void VIM_COMMAND_W(void) {
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
void VIM_COMMAND_Y(void) {
  PRESS(KC_LGUI);
    TAP(KC_C);
  RELEASE(KC_LGUI);
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
void VIM_COMMAND_SHIFT_A(void) {
  PRESS(KC_LGUI);
    TAP(KC_RIGHT);
  RELEASE(KC_LGUI);
  TO(INSERT_MODE);
  ENQUEUE_VIM_LEADER(KC_NO);
}

/**
 * Vim-like 'delete line' command
 * Simulates vim's `D` command by sending ⌃K to kill the line
 */
void VIM_COMMAND_SHIFT_D(void) {
  PRESS(KC_LCTRL);
    TAP(KC_K);
  RELEASE(KC_LCTRL);
  ENQUEUE_VIM_LEADER(KC_NO);
}

/**
 * Vim-like 'join lines' command
 * Simulates vim's `J` command by sending ⌘→ to go to the end of the line, then
 * DELETE to join the lines
 */
void VIM_COMMAND_SHIFT_J(void) {
  PRESS(KC_LGUI);
    TAP(KC_RIGHT);
  RELEASE(KC_LGUI);
  TAP(KC_DELETE);
  ENQUEUE_VIM_LEADER(KC_NO);
}

/**
 * Vim-like 'open above' command
 * Simulates vim's `O` command by sending ⌘→ to go to the start of the line,
 * enter to move the line down, ↑ to move up to the new line, then switching to
 * insert mode.
 */
void VIM_COMMAND_SHIFT_O(void) {
  PRESS(KC_LGUI);
    TAP(KC_RIGHT);
  RELEASE(KC_LGUI);
  TAP(KC_ENTER);
  TAP(KC_UP);
  TO(INSERT_MODE);
  ENQUEUE_VIM_LEADER(KC_NO);
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
 * Vim-like `delete whole line` command
 * Simulates vim's `dd` command by sending ⌃A to move to start of line,
 * Then sending ⌃K to kill the line.
 * Finally, cancels the vim command queue.
 * alternate method: ⌘⌫, ⌃K
 */
void VIM_COMMAND_DD(void) {
  PRESS(KC_LCTRL);
    TAP(KC_A);
  RELEASE(KC_LCTRL);
  PRESS(KC_LCTRL);
    TAP(KC_K);
  RELEASE(KC_LCTRL);
  ENQUEUE_VIM_LEADER(KC_NO);
}

/**
 * Vim-like `delete word` command
 * Simulates vim's `dw` command by selecting to the end of the word then deleting.
 * Finally, cancels the vim command queue.
 */
void VIM_COMMAND_DW(void) {
  PRESS(KC_LALT);
    PRESS(KC_LSHIFT);
      TAP(KC_RIGHT); // select to end of word
      TAP(KC_DEL); // delete selection
    RELEASE(KC_LALT);
  RELEASE(KC_LSHIFT);
  ENQUEUE_VIM_LEADER(KC_NO);
}

/**
 * Vim-like `delete back` command
 * Simulates vim's `db` command by selecting to the end of the word then deleting.
 * Finally, cancels the vim command queue.
 */
void VIM_COMMAND_DB(void) {
  PRESS(KC_LALT);
    PRESS(KC_LSHIFT);
      TAP(KC_LEFT); // select to start of word
      TAP(KC_DEL); // delete selection
    RELEASE(KC_LALT);
  RELEASE(KC_LSHIFT);
  ENQUEUE_VIM_LEADER(KC_NO);
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
 * Simulates vim's `diw` command by first selecting to the start of the word,
 * then selecting to the end of the word, then yanking, then deleting.
 * Finally, cancels the vim command queue.
 */
void VIM_COMMAND_DIW(void) {
  VIM_COMMAND_B();
  PRESS(KC_LSHIFT);
    VIM_COMMAND_E(); // select inner word
  RELEASE(KC_LSHIFT);
  VIM_COMMAND_Y(); // yank the word
  TAP(KC_DEL); // delete selection
  ENQUEUE_VIM_LEADER(KC_NO);
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
 * Simulates vim's `ciw` command by first selecting to the start of the word,
 * then selecting to the end of the word, then yanking, then deleting,
 * then switching to insert mode.
 * Finally, cancels the vim command queue.
 */
void VIM_COMMAND_CIW(void) {
  VIM_COMMAND_B();
  PRESS(KC_LSHIFT);
    VIM_COMMAND_E(); // select inner word
  RELEASE(KC_LSHIFT);
  VIM_COMMAND_Y(); // yank the word
  TAP(KC_DEL); // delete selection
  TO(INSERT_MODE);
  ENQUEUE_VIM_LEADER(KC_NO);
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
 * Vim-like `visual select word` command
 * Simulates vim's `vw` command by selecting to the end of the word.
 * Finally, cancels the vim command queue.
 */
void VIM_COMMAND_VW(void) {
  PRESS(KC_LALT);
    PRESS(KC_LSHIFT);
      TAP(KC_RIGHT); // select to end of word
    RELEASE(KC_LALT);
  RELEASE(KC_LSHIFT);
  ENQUEUE_VIM_LEADER(KC_NO);
}

/**
 * Vim-like `visual select back` command
 * Simulates vim's `vb` command by selecting to the enc of the word.
 * Finally, cancels the vim command queue.
 */
void VIM_COMMAND_VB(void) {
  PRESS(KC_LALT);
    PRESS(KC_LSHIFT);
      TAP(KC_LEFT); // select to start of word
    RELEASE(KC_LALT);
  RELEASE(KC_LSHIFT);
  ENQUEUE_VIM_LEADER(KC_NO);
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
