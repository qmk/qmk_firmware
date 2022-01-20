// see https://github.com/pepaslabs/hexon38

#include QMK_KEYBOARD_H

#define A_ KC_A
#define B_ KC_B
#define C_ KC_C
#define D_ KC_D
#define E_ KC_E
#define F_ KC_F
#define G_ KC_G
#define H_ KC_H
#define I_ KC_I
#define J_ KC_J
#define K_ KC_K
#define L_ KC_L
#define M_ KC_M
#define N_ KC_N
#define O_ KC_O
#define P_ KC_P
#define Q_ KC_Q
#define R_ KC_R
#define S_ KC_S
#define T_ KC_T
#define U_ KC_U
#define V_ KC_V
#define W_ KC_W
#define X_ KC_X
#define Y_ KC_Y
#define Z_ KC_Z

// Dual-role keys: modifier when held, alpha when tapped.
#define A_CTL CTL_T(KC_A)
#define S_ALT ALT_T(KC_S)
#define D_GUI GUI_T(KC_D)
#define F_SFT SFT_T(KC_F)
#define J_SFT SFT_T(KC_J)
#define K_GUI GUI_T(KC_K)
#define L_ALT ALT_T(KC_L)
#define COLN_CTL CTL_T(KC_SCLN)

#define ______ KC_TRNS
#define LSHIFT KC_LSHIFT
#define RSHIFT KC_RSHIFT
#define COMMA KC_COMM
#define SLASH KC_SLSH
#define SPACE KC_SPC
#define TAB KC_TAB
#define BKSPC KC_BSPC
#define ENTER KC_ENT
#define PERIOD KC_DOT

#define BASE_LAYER LAYOUT
#define BLANK_LAYER LAYOUT


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    BASE_LAYER(
//                  ,--------+--------+--------+--------.    ,--------+--------+--------+--------.
                        W_   ,   E_   ,   R_   ,   T_   ,        Y_   ,   U_   ,   I_   ,   O_   ,
//|--------+--------+--------+--------+--------+--------|    |--------+--------+--------+--------+--------+--------.
      Q_   ,  A_CTL ,  S_ALT ,  D_GUI ,  F_SFT ,   G_   ,        H_   ,  J_SFT ,  K_GUI ,  L_ALT ,COLN_CTL,   P_   ,
//|--------+--------+--------+--------+--------+--------'    `--------+--------+--------+--------+--------+--------|
      B_   ,   Z_   ,   X_   ,   C_   ,   V_   ,                          M_   ,  COMMA , PERIOD ,  SLASH ,   N_   ,
//`--------+--------+--------+--------+--------'                      `--------+--------+--------+--------+--------'

//                  ,--------+--------+--------+--------.    ,--------+--------+--------+--------.
                      LSHIFT ,  SPACE ,   TAB  ,  DEBUG ,       SPACE ,  BKSPC ,  ENTER , RSHIFT
//                  `--------+--------+--------+--------'    `--------+--------+--------+--------'
),

    BLANK_LAYER(
//                  ,--------+--------+--------+--------.    ,--------+--------+--------+--------.
                      ______ , ______ , ______ , ______ ,      ______ , ______ , ______ , ______ ,
//|--------+--------+--------+--------+--------+--------|    |--------+--------+--------+--------+--------+--------.
    ______ , ______ , ______ , ______ , ______ , ______ ,      ______ , ______ , ______ , ______ , ______ , ______ ,
//|--------+--------+--------+--------+--------+--------'    `--------+--------+--------+--------+--------+--------|
    ______ , ______ , ______ , ______ , ______ ,                        ______ , ______ , ______ , ______ , ______ ,
//`--------+--------+--------+--------+--------'                      `--------+--------+--------+--------+--------'

//                  ,--------+--------+--------+--------.    ,--------+--------+--------+--------.
                      ______ , ______ , ______ , ______ ,      ______ , ______ , ______ , ______
//                  `--------+--------+--------+--------'    `--------+--------+--------+--------'
)

};

// a linked list of pending key events (press or release) which we haven't processed yet.
struct _pending_key_t {
    uint16_t keycode;
    keyrecord_t record;
    struct _pending_key_t *next;
};
typedef struct _pending_key_t pending_key_t;

// worst case is 10 down strokes and 1 up stroke before we can start disambiguating.
#define RINGSIZE 11

// a ring buffer and linked list to store pending key events (presses and releases).
// (basically, this is a fixed-allocation linked list.)
struct _kring_t {
    // the actual key events.
    pending_key_t items[RINGSIZE];
    // the index of the oldest item, or -1 if no items.
    int8_t ifirst;
    // the index of the most recently added item, or -1 if no items.
    int8_t ilast;
    // the number of items in the ring.
    uint8_t count;
    // the head of the linked list.
    pending_key_t *head;
};
typedef struct _kring_t kring_t;

// safe accessor to the i-th item of the linked list (returns pointer or NULL).
pending_key_t* kring_get(kring_t *ring, uint8_t i) {
    if (i >= ring->count) {
        return NULL;
    }
    uint8_t j = (ring->ifirst + i) % RINGSIZE;
    return &(ring->items[j]);
}

// return the last key in the list of buffered keys.
pending_key_t* kring_last(kring_t *ring) {
    if (ring->count == 0) {
        return NULL;
    }
    return kring_get(ring, ring->count - 1);
}

// remove the oldest item from the ring (the head of the list).
void kring_pop(kring_t *ring) {
    if (ring->count > 0) {
        ring->ifirst += 1;
        ring->ifirst %= RINGSIZE;
        ring->head = ring->head->next;
        ring->count -= 1;
    }
}

// add an item to the ring (append to the list).
void kring_append(kring_t *ring, uint16_t keycode, keyrecord_t *record) {
    if (ring->count >= RINGSIZE) {
        // uh oh, we overflowed the capacity of our buffer :(
        return;
    }

    // if the ring is empty, insert at index 0.
    if (ring->count == 0) {
        ring->count += 1;
        ring->ifirst = 0;
        ring->ilast = 0;
        ring->head = &(ring->items[0]);
    }
    // else, append it onto the end.
    else {
        ring->count += 1;
        ring->ilast += 1;
        ring->ilast %= RINGSIZE;
    }

    // the index at which we should insert this item.
    int8_t i = ring->ilast;

    // insert the item.
    ring->items[i].keycode = keycode;
    ring->items[i].record.event = record->event;
#ifndef NO_ACTION_TAPPING
    ring->items[i].record.tap = record->tap;
#endif
    ring->items[i].next = NULL;

    // update the previous item to point to this item.
    if (ring->count > 1) {
        kring_get(ring, ring->count - 2)->next = &(ring->items[i]);
    }
}

kring_t g_pending;

void matrix_init_user(void) {
    g_pending.ifirst = -1;
    g_pending.ilast = -1;
    g_pending.count = 0;
    g_pending.head = NULL;
}

/*
a_ a-: emit a
a_ b_ b- a-: emit SHIFT+b
a_ b_ a- b-: emit a, b
dual1down, dual1up -> norm1down, norm1up
dual1down, norm2down, norm2up -> mod1down, norm2down, norm2up
dual1down, norm2down, dual1up -> norm1down, norm2down, norm1up
dual1down, dual2down, norm3down, norm3up -> mod1down, mod2down, norm3down, norm3up
so, a dual key can't be disambiguated until the next keyup of a keydown (not including keyups from keys before it).
*/

bool is_ambiguous_kc(uint16_t kc) {
    // See the MT() define: https://github.com/qmk/qmk_firmware/blob/master/quantum/quantum_keycodes.h#L642
    // See the QK_MOD_TAP case: https://github.com/qmk/qmk_firmware/blob/master/quantum/keymap_common.c#L134
    uint8_t mod = mod_config((kc >> 0x8) & 0x1F);
    return mod != 0;
}

bool is_down(pending_key_t *k) {
    return k->record.event.pressed;
}

bool is_up(pending_key_t *k) {
    return !is_down(k);
}

bool keys_match(pending_key_t *a, pending_key_t *b) {
    return a->record.event.key.col == b->record.event.key.col
        && a->record.event.key.row == b->record.event.key.row;
}

// both the down and corresponding upstroke of a keypress.
struct _pending_pair_t {
    pending_key_t *down;
    pending_key_t *up;
};
typedef struct _pending_pair_t pending_pair_t;

// returns true if this keydown event has a corresponding keyup event in the
// list of buffered keys.  also fills out 'p'.
bool is_downup_pair(pending_key_t *k, pending_pair_t *p) {
    // first, make sure this event is keydown.
    if (!is_down(k)) {
        return false;
    }
    // now find its matching keyup.
    pending_key_t *next = k->next;
    while (next != NULL) {
        if (keys_match(k, next) && is_up(next)) {
            // found it.
            if (p != NULL) {
                p->down = k;
                p->up = next;
            }
            return true;
        }
        next = next->next;
    }
    // didn't find it.
    return false;
}

// given a QK_MOD_TAP keycode, return the KC_* version of the modifier keycode.
uint16_t get_mod_kc(uint16_t keycode) {
    uint8_t mod = mod_config((keycode >> 0x8) & 0x1F);
    switch (mod) {
    case MOD_LCTL:
        return KC_LCTL;
    case MOD_RCTL:
        return KC_RCTL;
    case MOD_LSFT:
        return KC_LSFT;
    case MOD_RSFT:
        return KC_RSFT;
    case MOD_LALT:
        return KC_LALT;
    case MOD_RALT:
        return KC_RALT;
    case MOD_LGUI:
        return KC_LGUI;
    case MOD_RGUI:
        return KC_RGUI;
    default:
        // shrug?  this shouldn't happen.
        return keycode;
    }
}

bool is_mod_kc(uint16_t keycode) {
    switch (keycode) {
    case QK_MODS ... QK_MODS_MAX:
        return true;
    default:
        return false;
    }
}

void interpret_as_mod(pending_pair_t *p) {
    // see https://github.com/qmk/qmk_firmware/issues/1503
    pending_key_t *k;
    k = p->down;
    if (k != NULL) {
        k->keycode = get_mod_kc(k->keycode);
    }
    k = p->up;
    if (k != NULL) {
        k->keycode = get_mod_kc(k->keycode);
    }
}

void interpret_as_normal(pending_pair_t *p) {
    pending_key_t *k;
    k = p->down;
    if (k != NULL) {
        k->keycode = k->keycode & 0xFF;
    }
    k = p->up;
    if (k != NULL) {
        k->keycode = k->keycode & 0xFF;
    }
}

void execute_head_and_pop(kring_t *ring) {
    pending_key_t *head = kring_get(ring, 0);
    uint16_t kc = head->keycode;
    if (is_mod_kc(kc)) {
        if (is_down(head)) {
            dprintf("  %s: mod down 0x%04X\n", __func__, kc);
            set_mods(get_mods() | MOD_BIT(kc));
        } else {
            dprintf("  %s: mod up 0x%04X\n", __func__, kc);
            set_mods(get_mods() & ~MOD_BIT(kc));
        }
    } else {
        if (is_down(head)) {
            dprintf("  %s: key down 0x%04X\n", __func__, kc);
            register_code16(kc);
        } else {
            dprintf("  %s: key up 0x%04X\n", __func__, kc);
            unregister_code16(kc);
        }
    }
    kring_pop(ring);
}

// try to figure out what the next pending keypress means.
bool parse_next(kring_t *pending) {
    pending_pair_t p;
    pending_key_t *first = kring_get(pending, 0);
    if (!is_ambiguous_kc(first->keycode)) {
        // this pending key isn't ambiguous, so execute it.
        dprintf(" %s: found unambiguous key\n", __func__);
        execute_head_and_pop(pending);
        return true;
    } else if (is_ambiguous_kc(first->keycode) && is_up(first)) {
        dprintf(" %s: interpreting keyup as mod\n", __func__);
        p.down = NULL;
        p.up = first;
        interpret_as_mod(&p);
        execute_head_and_pop(pending);
        return true;
    } else if (is_downup_pair(first, &p)) {
        // 'first' was released before any other pressed key, so treat this as
        // a rolling series of normal key taps.
        dprintf(" %s: found down-up pair, interpreting as normal key\n", __func__);
        interpret_as_normal(&p);
        execute_head_and_pop(pending);
        return true;
    } else {
        // if another key was pressed and released while 'first' was held, then we
        // should treat it like a modifier.
        pending_key_t *next = first->next;
        while (next != NULL) {
            if (is_downup_pair(next, NULL)) {
                dprintf(" %s: found subsequent downup pair, interpreting head as mod\n", __func__);
                p.down = first;
                p.up = NULL;
                interpret_as_mod(&p);
                execute_head_and_pop(pending);
                return true;
            }
            next = next->next;
        }

        // we can't disambiguate 'first' yet.  wait for another keypress.
        dprintf(" %s: can't disambiguate (yet)\n", __func__);
        return false;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == DEBUG) {
        return true;
    }

    if (g_pending.count == 0 && !is_ambiguous_kc(keycode)) {
        // we have no pending keys and this key isn't ambiguous, so we should
        // just let QMK take care of it.
        dprintf("%s: handled by qmk\n", __func__);
        return true;
    } else {
        dprintf("%s: got dual-role key\n", __func__);
        // append the keypress and then try parsing all pending keypresses.
        kring_append(&g_pending, keycode, record);
        while (g_pending.count > 0) {
            dprintf("%s: looping through %d keys...\n", __func__, g_pending.count);
            if (!parse_next(&g_pending)) {
                // one of our keypresses is ambiguous and we can't proceed until
                // we get further keypresses to disambiguate it.
                dprintf("%s: %d pending keys are ambiguous\n", __func__, g_pending.count);
                break;
            }
        }
        return false;
    }
}
