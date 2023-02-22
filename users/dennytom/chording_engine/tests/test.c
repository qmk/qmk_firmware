#include "minunit.h"
#include "test_keymap.c"

MAIN

// CLEAR_KB
TEST("clear")
    for (int i = 0; i < NUMBER_OF_CHORDS; i++) {
        struct Chord* chord_ptr = (struct Chord*) pgm_read_word (&list_of_chords[i]);
        struct Chord chord_storage;
        memcpy_P(&chord_storage, chord_ptr, sizeof(struct Chord));
        struct Chord* chord = &chord_storage;
        
        *chord->state = READY;
        
        if (chord->counter) {
            *chord->counter = 1;
        }
    }
    
    history_index++;
    for (int j = 0; j < SAFE_RANGE-1; j++) {
        keyboard_history[history_index][j] = 1;
    }
    
    current_pseudolayer = 5;
    lock_next = true;
    autoshift_mode = false;
    command_mode = 1;
    in_leader_mode = true;
    dynamic_macro_mode = true;
    a_key_went_through = true;

    for (int i = 0; i < DYNAMIC_MACRO_MAX_LENGTH; i++) {
        dynamic_macro_buffer[i] = 1;
    }
    
    uint8_t clear_state = ACTIVATED;
    struct Chord clear_chord PROGMEM = {0, QWERTY, &clear_state, NULL, 0, 0, clear};
    clear_chord.function(&clear_chord);
    
    for (int i = 0; i < NUMBER_OF_CHORDS; i++) {
        struct Chord* chord_ptr = (struct Chord*) pgm_read_word (&list_of_chords[i]);
        struct Chord chord_storage;
        memcpy_P(&chord_storage, chord_ptr, sizeof(struct Chord));
        struct Chord* chord = &chord_storage;
        
        ASSERT_EQ(UINT, *chord->state, IDLE);
        
        if (chord->counter) {
            ASSERT_EQ(UINT, *chord->counter, 0);
        }
    }
    
    for (int j = 0; j < SAFE_RANGE-1; j++) {
        ASSERT_EQ(UINT, keyboard_history[history_index][j], 0);
    }
    
    ASSERT_EQ(UINT, current_pseudolayer, 1);
    ASSERT_EQ(UINT, lock_next, false);
    ASSERT_EQ(UINT, autoshift_mode, true);
    ASSERT_EQ(UINT, command_mode, 0);
    ASSERT_EQ(UINT, in_leader_mode, false);
    ASSERT_EQ(UINT, leader_ind, 0);
    ASSERT_EQ(UINT, dynamic_macro_mode, false);
    ASSERT_EQ(UINT, a_key_went_through, false);

    for (int i = 0; i < DYNAMIC_MACRO_MAX_LENGTH; i++) {
        ASSERT_EQ(UINT, dynamic_macro_buffer[i], 0);
    }
END_TEST

TEST("pause_ms")
    pause_ms(500);
    ASSERT_EQ(UINT, current_time, 500);
END_TEST

// KC
TEST("single_dance_held_states")
    ASSERT_EQ(UINT, state_1, IDLE);
    process_record_user(TOP1, &pressed);
    pause_ms(CHORD_TIMEOUT);
    ASSERT_EQ(UINT, state_1, IDLE);
    pause_ms(1);
    ASSERT_EQ(UINT, state_1, ACTIVATED);
    pause_ms(DANCE_TIMEOUT);
    ASSERT_EQ(UINT, state_1, ACTIVATED);
    pause_ms(1);
    ASSERT_EQ(UINT, state_1, PRESS_FROM_ACTIVE);
    pause_ms(DANCE_TIMEOUT);
    ASSERT_EQ(UINT, state_1, PRESS_FROM_ACTIVE);
    pause_ms(1);
    ASSERT_EQ(UINT, state_1, FINISHED_FROM_ACTIVE);
    process_record_user(TOP1, &depressed);
    ASSERT_EQ(UINT, state_1, IDLE);
END_TEST

TEST("single_dance_held_codes")
    ASSERT_EQ(UINT, keyboard_history[history_index][KC_Q], 0);
    process_record_user(TOP1, &pressed);
    pause_ms(CHORD_TIMEOUT);
    ASSERT_EQ(UINT, keyboard_history[history_index][KC_Q], 0);
    pause_ms(1);
    ASSERT_EQ(UINT, keyboard_history[history_index][KC_Q], 1);
    pause_ms(DANCE_TIMEOUT);
    ASSERT_EQ(UINT, keyboard_history[history_index][KC_Q], 1);
    pause_ms(1);
    ASSERT_EQ(UINT, keyboard_history[history_index][KC_Q], 1);
    pause_ms(DANCE_TIMEOUT);
    ASSERT_EQ(UINT, keyboard_history[history_index][KC_Q], 1);
    pause_ms(1);
    ASSERT_EQ(UINT, keyboard_history[history_index][KC_Q], 1);
    process_record_user(TOP1, &depressed);
    ASSERT_EQ(UINT, keyboard_history[history_index][KC_Q], 0);
END_TEST

TEST("single_dance_tapped_states")
    ASSERT_EQ(UINT, state_1, IDLE);
    process_record_user(TOP1, &pressed);
    pause_ms(CHORD_TIMEOUT);
    ASSERT_EQ(UINT, state_1, IDLE);
    pause_ms(1);
    ASSERT_EQ(UINT, state_1, ACTIVATED);
    process_record_user(TOP1, &depressed);
    ASSERT_EQ(UINT, state_1, IDLE);
END_TEST

TEST("single_dance_tapped_codes")
    ASSERT_EQ(UINT, keyboard_history[history_index][KC_Q], 0);
    process_record_user(TOP1, &pressed);
    pause_ms(CHORD_TIMEOUT);
    ASSERT_EQ(UINT, keyboard_history[history_index][KC_Q], 0);
    pause_ms(1);
    ASSERT_EQ(UINT, keyboard_history[history_index][KC_Q], 1);
    process_record_user(TOP1, &depressed);
    ASSERT_EQ(UINT, keyboard_history[history_index][KC_Q], 0);
END_TEST

// I can not actually track the states if the tap is faster than chord timeout

TEST("single_dance_tapped_fast_codes")
    ASSERT_EQ(UINT, state_0, IDLE);
    process_record_user(TOP1, &pressed);
    pause_ms(1);
    process_record_user(TOP1, &depressed);
    ASSERT_EQ(UINT, keyboard_history[0][KC_Q], 0);
    ASSERT_EQ(UINT, keyboard_history[1][KC_Q], 1);
    ASSERT_EQ(UINT, keyboard_history[2][KC_Q], 0);
END_TEST

TEST("subchords_are_ignored")
    ASSERT_EQ(UINT, state_0, IDLE);
    process_record_user(TOP1, &pressed);
    pause_ms(1);
    process_record_user(TOP2, &pressed);
    pause_ms(CHORD_TIMEOUT + 1);
    ASSERT_EQ(UINT, keyboard_history[history_index][KC_Q], 0);
    ASSERT_EQ(UINT, keyboard_history[history_index][KC_W], 0);
    ASSERT_EQ(UINT, keyboard_history[history_index][KC_ESC], 1);
END_TEST

TEST("multiple_chords_at_once")
    ASSERT_EQ(UINT, state_0, IDLE);
    process_record_user(TOP1, &pressed);
    pause_ms(1);
    process_record_user(TOP3, &pressed);
    pause_ms(CHORD_TIMEOUT + 1);
    ASSERT_EQ(UINT, keyboard_history[history_index][KC_Q], 1);
    ASSERT_EQ(UINT, keyboard_history[history_index][KC_E], 1);
END_TEST

// MO
TEST("momentary_layer")
    ASSERT_EQ(UINT, current_pseudolayer, QWERTY);
    process_record_user(BOT7, &pressed);
    pause_ms(1);
    process_record_user(BOT8, &pressed);
    pause_ms(CHORD_TIMEOUT + 1);
    ASSERT_EQ(UINT, current_pseudolayer, NUM);
    process_record_user(BOT7, &depressed);
    pause_ms(1);
    process_record_user(BOT8, &depressed);
    ASSERT_EQ(UINT, current_pseudolayer, QWERTY);
END_TEST

TEST("momentary_layer_reset")
    ASSERT_EQ(UINT, current_pseudolayer, QWERTY);
    process_record_user(BOT7, &pressed);
    pause_ms(1);
    process_record_user(BOT8, &pressed);
    pause_ms(CHORD_TIMEOUT + 1);
    ASSERT_EQ(UINT, current_pseudolayer, NUM);
    pause_ms(DANCE_TIMEOUT + 1);
    ASSERT_EQ(UINT, current_pseudolayer, NUM);
    process_record_user(BOT7, &depressed);
    pause_ms(1);
    process_record_user(BOT8, &depressed);
    ASSERT_EQ(UINT, current_pseudolayer, QWERTY);
END_TEST

TEST("momentary_layer_alt")
    ASSERT_EQ(UINT, current_pseudolayer, QWERTY);
    
    process_record_user(TOP8, &pressed);
    pause_ms(1);
    process_record_user(TOP9, &pressed);
    pause_ms(1);
    process_record_user(TOP0, &pressed);
    pause_ms(1);
    process_record_user(BOT8, &pressed);
    pause_ms(1);
    process_record_user(BOT9, &pressed);
    pause_ms(1);
    process_record_user(BOT0, &pressed);
    pause_ms(CHORD_TIMEOUT + 1);
    
    ASSERT_EQ(UINT, current_pseudolayer, NUM);
    
    process_record_user(TOP8, &depressed);
    pause_ms(1);
    process_record_user(TOP9, &depressed);
    pause_ms(1);
    process_record_user(TOP0, &depressed);
    pause_ms(1);
    process_record_user(BOT8, &depressed);
    pause_ms(1);
    process_record_user(BOT9, &depressed);
    pause_ms(1);
    process_record_user(BOT0, &depressed);
    
    ASSERT_EQ(UINT, current_pseudolayer, FNC);
END_TEST

// DF
TEST("permanent_layer")
    ASSERT_EQ(UINT, current_pseudolayer, QWERTY);
    process_record_user(BOT9, &pressed);
    pause_ms(1);
    process_record_user(BOT0, &pressed);
    pause_ms(CHORD_TIMEOUT + 1);
    ASSERT_EQ(UINT, current_pseudolayer, NUM);
    process_record_user(BOT9, &depressed);
    pause_ms(1);
    process_record_user(BOT0, &depressed);
    ASSERT_EQ(UINT, current_pseudolayer, NUM);
    pause_ms(1000);
    ASSERT_EQ(UINT, current_pseudolayer, NUM);
END_TEST

// AT
TEST("autoshift_toggle")
    ASSERT_EQ(UINT, autoshift_mode, 1);
    uint8_t state = ACTIVATED;
    struct Chord chord PROGMEM = {0, QWERTY, &state, NULL, 0, 0, autoshift_toggle};
    chord.function(&chord);
    ASSERT_EQ(UINT, autoshift_mode, 0);
    state = ACTIVATED;
    chord.function(&chord);
    ASSERT_EQ(UINT, autoshift_mode, 1);
END_TEST

// AS
TEST("autoshift_tap")
    process_record_user(BOT1, &pressed);
    pause_ms(CHORD_TIMEOUT + 1);
    process_record_user(BOT1, &depressed);
    
    ASSERT_EQ(UINT, keyboard_history[0][KC_Z], 0);
    ASSERT_EQ(UINT, keyboard_history[0][KC_LSFT], 0);
    
    ASSERT_EQ(UINT, keyboard_history[1][KC_Z], 1);
    ASSERT_EQ(UINT, keyboard_history[1][KC_LSFT], 0);
    
    ASSERT_EQ(UINT, keyboard_history[2][KC_Z], 0);
    ASSERT_EQ(UINT, keyboard_history[2][KC_LSFT], 0);
END_TEST

TEST("autoshift_hold")
    process_record_user(BOT1, &pressed);
    pause_ms(CHORD_TIMEOUT + 1);
    pause_ms(LONG_PRESS_MULTIPLIER * (DANCE_TIMEOUT + 1));
    process_record_user(BOT1, &depressed);
    
    ASSERT_EQ(UINT, keyboard_history[0][KC_Z], 0);
    ASSERT_EQ(UINT, keyboard_history[0][KC_LSFT], 0);
    
    ASSERT_EQ(UINT, keyboard_history[1][KC_Z], 0);
    ASSERT_EQ(UINT, keyboard_history[1][KC_LSFT], 1);
    
    ASSERT_EQ(UINT, keyboard_history[2][KC_Z], 1);
    ASSERT_EQ(UINT, keyboard_history[2][KC_LSFT], 1);
    
    ASSERT_EQ(UINT, keyboard_history[3][KC_Z], 0);
    ASSERT_EQ(UINT, keyboard_history[3][KC_LSFT], 1);
    
    ASSERT_EQ(UINT, keyboard_history[4][KC_Z], 0);
    ASSERT_EQ(UINT, keyboard_history[4][KC_LSFT], 0);
END_TEST

TEST("autoshift_hold_off")
    autoshift_mode = 0;
    process_record_user(BOT1, &pressed);
    pause_ms(CHORD_TIMEOUT + 1);
    pause_ms(LONG_PRESS_MULTIPLIER * (DANCE_TIMEOUT + 1));
    process_record_user(BOT1, &depressed);
    
    ASSERT_EQ(UINT, keyboard_history[0][KC_Z], 0);
    ASSERT_EQ(UINT, keyboard_history[0][KC_LSFT], 0);
    
    ASSERT_EQ(UINT, keyboard_history[1][KC_Z], 1);
    ASSERT_EQ(UINT, keyboard_history[1][KC_LSFT], 0);
    
    ASSERT_EQ(UINT, keyboard_history[2][KC_Z], 0);
    ASSERT_EQ(UINT, keyboard_history[2][KC_LSFT], 0);
END_TEST

// LOCK
TEST("lock")
    ASSERT_EQ(UINT, keyboard_history[history_index][KC_LSFT], 0);
    process_record_user(BOT1, &pressed);
    process_record_user(BOT2, &pressed);
    pause_ms(CHORD_TIMEOUT + 1);
    ASSERT_EQ(UINT, keyboard_history[history_index][KC_LSFT], 1);
    process_record_user(BOT1, &depressed);
    ASSERT_EQ(UINT, keyboard_history[history_index][KC_LSFT], 0);
    pause_ms(1);
    process_record_user(BOT2, &depressed);
    pause_ms(1);
    process_record_user(TOP1, &pressed);
    process_record_user(TOP2, &pressed);
    process_record_user(BOT1, &pressed);
    process_record_user(BOT2, &pressed);
    pause_ms(CHORD_TIMEOUT + 1);
    process_record_user(TOP1, &depressed);
    pause_ms(1);
    process_record_user(TOP2, &depressed);
    process_record_user(BOT1, &depressed);
    process_record_user(BOT2, &depressed);
    pause_ms(1);
    process_record_user(BOT1, &pressed);
    process_record_user(BOT2, &pressed);
    pause_ms(CHORD_TIMEOUT + 1);
    ASSERT_EQ(UINT, keyboard_history[history_index][KC_LSFT], 1);
    process_record_user(BOT1, &depressed);
    ASSERT_EQ(UINT, keyboard_history[history_index][KC_LSFT], 1);
    pause_ms(1);
    process_record_user(BOT2, &depressed);
    pause_ms(1000);
    process_record_user(BOT1, &pressed);
    process_record_user(BOT2, &pressed);
    pause_ms(CHORD_TIMEOUT + 1);
    ASSERT_EQ(UINT, keyboard_history[history_index][KC_LSFT], 0);
    process_record_user(BOT1, &depressed);
    pause_ms(1);
    process_record_user(BOT2, &depressed);
    pause_ms(1000);
    ASSERT_EQ(UINT, keyboard_history[history_index][KC_LSFT], 0);
END_TEST

// OSK
TEST("one_shot_key_tap")
    ASSERT_EQ(UINT, keyboard_history[history_index][KC_LSFT], 0);
    process_record_user(BOT2, &pressed);
    process_record_user(BOT3, &pressed);
    pause_ms(CHORD_TIMEOUT + 1);
    ASSERT_EQ(UINT, keyboard_history[history_index][KC_LSFT], 0);
    process_record_user(BOT2, &depressed);
    pause_ms(1);
    process_record_user(BOT3, &depressed);
    ASSERT_EQ(UINT, keyboard_history[history_index][KC_LSFT], 1);
    pause_ms(1000);
    ASSERT_EQ(UINT, keyboard_history[history_index][KC_LSFT], 1);
    
    process_record_user(TOP1, &pressed);
    pause_ms(CHORD_TIMEOUT + 1);
    process_record_user(TOP1, &depressed);
    ASSERT_EQ(UINT, keyboard_history[history_index][KC_LSFT], 0);
END_TEST

TEST("one_shot_key_hold")
    ASSERT_EQ(UINT, keyboard_history[history_index][KC_LSFT], 0);
    process_record_user(BOT2, &pressed);
    process_record_user(BOT3, &pressed);
    pause_ms(CHORD_TIMEOUT + 1);
    pause_ms(DANCE_TIMEOUT + 1);
    ASSERT_EQ(UINT, keyboard_history[history_index][KC_LSFT], 1);
    
    process_record_user(TOP1, &pressed);
    pause_ms(CHORD_TIMEOUT + 1);
    process_record_user(TOP1, &depressed);
    ASSERT_EQ(UINT, keyboard_history[history_index][KC_LSFT], 1);
    
    process_record_user(BOT2, &depressed);
    ASSERT_EQ(UINT, keyboard_history[history_index][KC_LSFT], 0);
END_TEST

TEST("one_shot_key_retrotapping")
    ASSERT_EQ(UINT, keyboard_history[history_index][KC_LSFT], 0);
    process_record_user(BOT2, &pressed);
    process_record_user(BOT3, &pressed);
    pause_ms(CHORD_TIMEOUT + 1);
    pause_ms(DANCE_TIMEOUT + 1);
    ASSERT_EQ(UINT, keyboard_history[history_index][KC_LSFT], 1);
    
    pause_ms(1000);
    
    process_record_user(BOT2, &depressed);
    ASSERT_EQ(UINT, keyboard_history[history_index][KC_LSFT], 1);
END_TEST

// OSL
TEST("one_shot_layer_tap")
    ASSERT_EQ(UINT, current_pseudolayer, QWERTY);
    process_record_user(BOT6, &pressed);
    process_record_user(BOT7, &pressed);
    pause_ms(CHORD_TIMEOUT + 1);
    ASSERT_EQ(UINT, current_pseudolayer, QWERTY);
    process_record_user(BOT6, &depressed);
    pause_ms(1);
    process_record_user(BOT7, &depressed);
    ASSERT_EQ(UINT, current_pseudolayer, NUM);
    pause_ms(1000);
    ASSERT_EQ(UINT, current_pseudolayer, NUM);
    
    process_record_user(TOP1, &pressed);
    pause_ms(CHORD_TIMEOUT + 1);
    process_record_user(TOP1, &depressed);
    ASSERT_EQ(UINT, current_pseudolayer, QWERTY);
END_TEST

TEST("one_shot_layer_hold")
    ASSERT_EQ(UINT, current_pseudolayer, QWERTY);
    process_record_user(BOT6, &pressed);
    process_record_user(BOT7, &pressed);
    pause_ms(CHORD_TIMEOUT + 1);
    pause_ms(DANCE_TIMEOUT + 1);
    ASSERT_EQ(UINT, current_pseudolayer, NUM);
    
    process_record_user(TOP1, &pressed);
    pause_ms(CHORD_TIMEOUT + 1);
    process_record_user(TOP1, &depressed);
    ASSERT_EQ(UINT, current_pseudolayer, NUM);
    
    process_record_user(BOT6, &depressed);
    ASSERT_EQ(UINT, current_pseudolayer, QWERTY);
END_TEST

TEST("one_shot_layer_retrotapping")
    ASSERT_EQ(UINT, current_pseudolayer, QWERTY);
    process_record_user(BOT6, &pressed);
    process_record_user(BOT7, &pressed);
    pause_ms(CHORD_TIMEOUT + 1);
    pause_ms(DANCE_TIMEOUT + 1);
    ASSERT_EQ(UINT, current_pseudolayer, NUM);
    
    pause_ms(1000);
    
    process_record_user(BOT6, &depressed);
    ASSERT_EQ(UINT, current_pseudolayer, NUM);
END_TEST

// CMD
TEST("command_mode")
    // start recording
    process_record_user(TOP5, &pressed);
    process_record_user(TOP6, &pressed);
    process_record_user(BOT5, &pressed);
    process_record_user(BOT6, &pressed);
    pause_ms(1);
    process_record_user(TOP5, &depressed);
    process_record_user(TOP6, &depressed);
    process_record_user(BOT5, &depressed);
    process_record_user(BOT6, &depressed);
    
    ASSERT_EQ(UINT, command_mode, 1);
    
    // record shift+q
    process_record_user(BOT1, &pressed);
    process_record_user(BOT2, &pressed);
    pause_ms(CHORD_TIMEOUT + 1);
    ASSERT_EQ(UINT, keyboard_history[history_index][KC_Q], 0);
    ASSERT_EQ(UINT, keyboard_history[history_index][KC_LSFT], 0);
    process_record_user(BOT1, &depressed);
    process_record_user(BOT2, &depressed);
    pause_ms(1000);
    
    process_record_user(TOP1, &pressed);
    pause_ms(CHORD_TIMEOUT + 1);
    ASSERT_EQ(UINT, keyboard_history[history_index][KC_Q], 0);
    ASSERT_EQ(UINT, keyboard_history[history_index][KC_LSFT], 0);
    process_record_user(TOP1, &depressed);
    pause_ms(1000);
    
    
    ASSERT_EQ(UINT, keyboard_history[history_index][KC_Q], 0);
    ASSERT_EQ(UINT, keyboard_history[history_index][KC_LSFT], 0);
    // execute
    process_record_user(TOP5, &pressed);
    process_record_user(TOP6, &pressed);
    process_record_user(BOT5, &pressed);
    process_record_user(BOT6, &pressed);
    pause_ms(CHORD_TIMEOUT + 1);
    
    ASSERT_EQ(UINT, command_mode, 0);
    
    // test history
    ASSERT_EQ(UINT, keyboard_history[0][KC_Q], 0);
    ASSERT_EQ(UINT, keyboard_history[0][KC_LSFT], 0);
    
    ASSERT_EQ(UINT, keyboard_history[1][KC_Q], 0);
    ASSERT_EQ(UINT, keyboard_history[1][KC_LSFT], 1);
    
    ASSERT_EQ(UINT, keyboard_history[2][KC_Q], 1);
    ASSERT_EQ(UINT, keyboard_history[2][KC_LSFT], 1);
    
    ASSERT_EQ(UINT, keyboard_history[3][KC_Q], 1);
    ASSERT_EQ(UINT, keyboard_history[3][KC_LSFT], 0);
    
    ASSERT_EQ(UINT, keyboard_history[4][KC_Q], 0);
    ASSERT_EQ(UINT, keyboard_history[4][KC_LSFT], 0);
    
    ASSERT_EQ(UINT, keyboard_history[5][KC_Q], 255);
    ASSERT_EQ(UINT, keyboard_history[5][KC_LSFT], 255);
END_TEST

// KK
TEST("key_key_dance_tap")
    process_record_user(BOT2, &pressed);
    pause_ms(CHORD_TIMEOUT + 1);
    process_record_user(BOT2, &depressed);
    
    ASSERT_EQ(UINT, keyboard_history[0][KC_X], 0);
    ASSERT_EQ(UINT, keyboard_history[0][KC_LCTL], 0);
    
    ASSERT_EQ(UINT, keyboard_history[1][KC_X], 1);
    ASSERT_EQ(UINT, keyboard_history[1][KC_LCTL], 0);
    
    ASSERT_EQ(UINT, keyboard_history[2][KC_X], 0);
    ASSERT_EQ(UINT, keyboard_history[2][KC_LCTL], 0);
END_TEST

TEST("key_key_dance_hold")
    process_record_user(BOT2, &pressed);
    pause_ms(CHORD_TIMEOUT + 1);
    pause_ms(DANCE_TIMEOUT + 1);
    process_record_user(BOT2, &depressed);
    
    ASSERT_EQ(UINT, keyboard_history[0][KC_X], 0);
    ASSERT_EQ(UINT, keyboard_history[0][KC_LCTL], 0);
    
    ASSERT_EQ(UINT, keyboard_history[1][KC_X], 0);
    ASSERT_EQ(UINT, keyboard_history[1][KC_LCTL], 1);
    
    ASSERT_EQ(UINT, keyboard_history[2][KC_X], 0);
    ASSERT_EQ(UINT, keyboard_history[2][KC_LCTL], 0);
END_TEST

// KL
TEST("key_layer_tap")
    ASSERT_EQ(UINT, current_pseudolayer, QWERTY);
    process_record_user(BOT3, &pressed);
    pause_ms(CHORD_TIMEOUT + 1);
    ASSERT_EQ(UINT, current_pseudolayer, NUM);
    process_record_user(BOT3, &depressed);
    ASSERT_EQ(UINT, current_pseudolayer, QWERTY);
    pause_ms(1000);
    
    ASSERT_EQ(UINT, keyboard_history[0][KC_C], 0);
    ASSERT_EQ(UINT, keyboard_history[1][KC_C], 1);
    ASSERT_EQ(UINT, keyboard_history[2][KC_C], 0);
    ASSERT_EQ(UINT, keyboard_history[3][KC_C], 255);
END_TEST

TEST("key_layer_retrotapping")
    ASSERT_EQ(UINT, current_pseudolayer, QWERTY);
    process_record_user(BOT3, &pressed);
    pause_ms(1000);
    ASSERT_EQ(UINT, current_pseudolayer, NUM);
    process_record_user(BOT3, &depressed);
    ASSERT_EQ(UINT, current_pseudolayer, QWERTY);
    pause_ms(1000);
    
    ASSERT_EQ(UINT, keyboard_history[0][KC_C], 0);
    ASSERT_EQ(UINT, keyboard_history[1][KC_C], 1);
    ASSERT_EQ(UINT, keyboard_history[2][KC_C], 0);
    ASSERT_EQ(UINT, keyboard_history[3][KC_C], 255);
END_TEST

TEST("key_layer_hold_quick_typist")
    ASSERT_EQ(UINT, current_pseudolayer, QWERTY);
    process_record_user(BOT3, &pressed);
    pause_ms(CHORD_TIMEOUT + 1);
    ASSERT_EQ(UINT, current_pseudolayer, NUM);
    
    pause_ms(1);
    process_record_user(TOP1, &pressed);
    pause_ms(1);
    process_record_user(TOP1, &depressed);
    pause_ms(1);
    process_record_user(TOP1, &pressed);
    pause_ms(1);
    process_record_user(TOP1, &depressed);
    pause_ms(1);
    process_record_user(TOP1, &pressed);
    pause_ms(1);
    process_record_user(TOP1, &depressed);
    ASSERT_EQ(UINT, current_pseudolayer, NUM);
    pause_ms(1);
    
    process_record_user(BOT3, &depressed);
    ASSERT_EQ(UINT, current_pseudolayer, QWERTY);
    
    ASSERT_EQ(UINT, keyboard_history[0][KC_1], 0);
    ASSERT_EQ(UINT, keyboard_history[1][KC_1], 1);
    ASSERT_EQ(UINT, keyboard_history[2][KC_1], 0);
    ASSERT_EQ(UINT, keyboard_history[3][KC_1], 1);
    ASSERT_EQ(UINT, keyboard_history[4][KC_1], 0);
    ASSERT_EQ(UINT, keyboard_history[5][KC_1], 1);
    ASSERT_EQ(UINT, keyboard_history[6][KC_1], 0);
    ASSERT_EQ(UINT, keyboard_history[7][KC_1], 255);
END_TEST

TEST("key_layer_hold_slow_typist")
    ASSERT_EQ(UINT, current_pseudolayer, QWERTY);
    process_record_user(BOT3, &pressed);
    pause_ms(CHORD_TIMEOUT + 1);
    ASSERT_EQ(UINT, current_pseudolayer, NUM);
    
    pause_ms(1000);
    process_record_user(TOP1, &pressed);
    pause_ms(1000);
    process_record_user(TOP1, &depressed);
    pause_ms(1000);
    process_record_user(TOP1, &pressed);
    pause_ms(1000);
    process_record_user(TOP1, &depressed);
    pause_ms(1000);
    process_record_user(TOP1, &pressed);
    pause_ms(1000);
    process_record_user(TOP1, &depressed);
    ASSERT_EQ(UINT, current_pseudolayer, NUM);
    pause_ms(1);
    
    process_record_user(BOT3, &depressed);
    ASSERT_EQ(UINT, current_pseudolayer, QWERTY);
    
    ASSERT_EQ(UINT, keyboard_history[0][KC_1], 0);
    ASSERT_EQ(UINT, keyboard_history[1][KC_1], 1);
    ASSERT_EQ(UINT, keyboard_history[2][KC_1], 0);
    ASSERT_EQ(UINT, keyboard_history[3][KC_1], 1);
    ASSERT_EQ(UINT, keyboard_history[4][KC_1], 0);
    ASSERT_EQ(UINT, keyboard_history[5][KC_1], 1);
    ASSERT_EQ(UINT, keyboard_history[6][KC_1], 0);
    ASSERT_EQ(UINT, keyboard_history[7][KC_1], 255);
END_TEST

// KM
TEST("key_mod_tap")
    ASSERT_EQ(UINT, keyboard_history[0][KC_LALT], 0);
    ASSERT_EQ(UINT, keyboard_history[0][KC_V], 0);
    process_record_user(BOT4, &pressed);
    pause_ms(CHORD_TIMEOUT + 1);
    ASSERT_EQ(UINT, keyboard_history[1][KC_LALT], 1);
    ASSERT_EQ(UINT, keyboard_history[1][KC_V], 0);
    process_record_user(BOT4, &depressed);
    ASSERT_EQ(UINT, keyboard_history[2][KC_LALT], 0);
    ASSERT_EQ(UINT, keyboard_history[2][KC_V], 0);
    pause_ms(1000);
    
    ASSERT_EQ(UINT, keyboard_history[3][KC_LALT], 0);
    ASSERT_EQ(UINT, keyboard_history[3][KC_V], 1);
    ASSERT_EQ(UINT, keyboard_history[4][KC_LALT], 0);
    ASSERT_EQ(UINT, keyboard_history[4][KC_V], 0);
    ASSERT_EQ(UINT, keyboard_history[5][KC_LALT], 255);
    ASSERT_EQ(UINT, keyboard_history[5][KC_V], 255);
END_TEST

TEST("key_mod_retrotapping")
    ASSERT_EQ(UINT, keyboard_history[0][KC_LALT], 0);
    ASSERT_EQ(UINT, keyboard_history[0][KC_V], 0);
    process_record_user(BOT4, &pressed);
    pause_ms(1000);
    ASSERT_EQ(UINT, keyboard_history[1][KC_LALT], 1);
    ASSERT_EQ(UINT, keyboard_history[1][KC_V], 0);
    process_record_user(BOT4, &depressed);
    ASSERT_EQ(UINT, keyboard_history[2][KC_LALT], 0);
    ASSERT_EQ(UINT, keyboard_history[2][KC_V], 0);
    pause_ms(1000);
    
    ASSERT_EQ(UINT, keyboard_history[3][KC_LALT], 0);
    ASSERT_EQ(UINT, keyboard_history[3][KC_V], 1);
    ASSERT_EQ(UINT, keyboard_history[4][KC_LALT], 0);
    ASSERT_EQ(UINT, keyboard_history[4][KC_V], 0);
    ASSERT_EQ(UINT, keyboard_history[5][KC_LALT], 255);
    ASSERT_EQ(UINT, keyboard_history[5][KC_V], 255);
END_TEST

TEST("key_mod_hold_quick_typist")
    process_record_user(BOT4, &pressed);
    pause_ms(CHORD_TIMEOUT + 1);
    
    pause_ms(1);
    process_record_user(TOP1, &pressed);
    pause_ms(1);
    process_record_user(TOP1, &depressed);
    pause_ms(1);
    process_record_user(TOP1, &pressed);
    pause_ms(1);
    process_record_user(TOP1, &depressed);
    pause_ms(1);
    process_record_user(TOP1, &pressed);
    pause_ms(1);
    process_record_user(TOP1, &depressed);
    pause_ms(1);
    
    process_record_user(BOT4, &depressed);
    ASSERT_EQ(UINT, current_pseudolayer, QWERTY);
    
    ASSERT_EQ(UINT, keyboard_history[0][KC_LALT], 0);
    ASSERT_EQ(UINT, keyboard_history[0][KC_V], 0);
    ASSERT_EQ(UINT, keyboard_history[1][KC_LALT], 1);
    ASSERT_EQ(UINT, keyboard_history[1][KC_V], 0);
    ASSERT_EQ(UINT, keyboard_history[2][KC_LALT], 1);
    ASSERT_EQ(UINT, keyboard_history[2][KC_V], 0);
    ASSERT_EQ(UINT, keyboard_history[3][KC_LALT], 1);
    ASSERT_EQ(UINT, keyboard_history[3][KC_V], 0);
    ASSERT_EQ(UINT, keyboard_history[4][KC_LALT], 1);
    ASSERT_EQ(UINT, keyboard_history[4][KC_V], 0);
    ASSERT_EQ(UINT, keyboard_history[5][KC_LALT], 1);
    ASSERT_EQ(UINT, keyboard_history[5][KC_V], 0);
    ASSERT_EQ(UINT, keyboard_history[6][KC_LALT], 1);
    ASSERT_EQ(UINT, keyboard_history[6][KC_V], 0);
    ASSERT_EQ(UINT, keyboard_history[7][KC_LALT], 1);
    ASSERT_EQ(UINT, keyboard_history[7][KC_V], 0);
    ASSERT_EQ(UINT, keyboard_history[8][KC_LALT], 0);
    ASSERT_EQ(UINT, keyboard_history[8][KC_V], 0);
    ASSERT_EQ(UINT, keyboard_history[9][KC_LALT], 255);
    ASSERT_EQ(UINT, keyboard_history[9][KC_V], 255);
END_TEST

TEST("key_mod_hold_slow_typist")
    process_record_user(BOT4, &pressed);
    pause_ms(CHORD_TIMEOUT + 1);
    
    pause_ms(1000);
    process_record_user(TOP1, &pressed);
    pause_ms(1000);
    process_record_user(TOP1, &depressed);
    pause_ms(1000);
    process_record_user(TOP1, &pressed);
    pause_ms(1000);
    process_record_user(TOP1, &depressed);
    pause_ms(1000);
    process_record_user(TOP1, &pressed);
    pause_ms(1000);
    process_record_user(TOP1, &depressed);
    pause_ms(1000);
    
    process_record_user(BOT4, &depressed);
    ASSERT_EQ(UINT, current_pseudolayer, QWERTY);
    
    ASSERT_EQ(UINT, keyboard_history[0][KC_LALT], 0);
    ASSERT_EQ(UINT, keyboard_history[0][KC_V], 0);
    ASSERT_EQ(UINT, keyboard_history[0][KC_Q], 0);
    ASSERT_EQ(UINT, keyboard_history[1][KC_LALT], 1);
    ASSERT_EQ(UINT, keyboard_history[1][KC_V], 0);
    ASSERT_EQ(UINT, keyboard_history[1][KC_Q], 0);
    ASSERT_EQ(UINT, keyboard_history[2][KC_LALT], 1);
    ASSERT_EQ(UINT, keyboard_history[2][KC_V], 0);
    ASSERT_EQ(UINT, keyboard_history[2][KC_Q], 1);
    ASSERT_EQ(UINT, keyboard_history[3][KC_LALT], 1);
    ASSERT_EQ(UINT, keyboard_history[3][KC_V], 0);
    ASSERT_EQ(UINT, keyboard_history[3][KC_Q], 0);
    ASSERT_EQ(UINT, keyboard_history[4][KC_LALT], 1);
    ASSERT_EQ(UINT, keyboard_history[4][KC_V], 0);
    ASSERT_EQ(UINT, keyboard_history[4][KC_Q], 1);
    ASSERT_EQ(UINT, keyboard_history[5][KC_LALT], 1);
    ASSERT_EQ(UINT, keyboard_history[5][KC_V], 0);
    ASSERT_EQ(UINT, keyboard_history[5][KC_Q], 0);
    ASSERT_EQ(UINT, keyboard_history[6][KC_LALT], 1);
    ASSERT_EQ(UINT, keyboard_history[6][KC_V], 0);
    ASSERT_EQ(UINT, keyboard_history[6][KC_Q], 1);
    ASSERT_EQ(UINT, keyboard_history[7][KC_LALT], 1);
    ASSERT_EQ(UINT, keyboard_history[7][KC_V], 0);
    ASSERT_EQ(UINT, keyboard_history[7][KC_Q], 0);
    ASSERT_EQ(UINT, keyboard_history[8][KC_LALT], 0);
    ASSERT_EQ(UINT, keyboard_history[8][KC_V], 0);
    ASSERT_EQ(UINT, keyboard_history[8][KC_Q], 0);
    ASSERT_EQ(UINT, keyboard_history[9][KC_LALT], 255);
    ASSERT_EQ(UINT, keyboard_history[9][KC_V], 255);
    ASSERT_EQ(UINT, keyboard_history[9][KC_Q], 255);
END_TEST

// LEADER
TEST("leader_triggers_global")
    uint8_t state = ACTIVATED;
    struct Chord chord PROGMEM = {0, QWERTY, &state, NULL, 0, 0, leader};
    chord.function(&chord);

    ASSERT_EQ(UINT, in_leader_mode, 1);
END_TEST

TEST("leader_no_follow")
    uint8_t state = ACTIVATED;
    struct Chord chord PROGMEM = {0, QWERTY, &state, NULL, 0, 0, leader};
    chord.function(&chord);
    
    ASSERT_EQ(UINT, in_leader_mode, 1);

    pause_ms(1000);
    
    ASSERT_EQ(UINT, in_leader_mode, 0);
    ASSERT_EQ(UINT, keyboard_history[1][KC_O], 255);
END_TEST

TEST("leader_wrong_follow")
    process_record_user(TOP2, &pressed);
    process_record_user(TOP3, &pressed);
    process_record_user(BOT2, &pressed);
    process_record_user(BOT3, &pressed);
    pause_ms(1);
    process_record_user(TOP2, &depressed);
    process_record_user(TOP3, &depressed);
    process_record_user(BOT2, &depressed);
    process_record_user(BOT3, &depressed);

    ASSERT_EQ(UINT, in_leader_mode, 1);

    pause_ms(1);
    process_record_user(TOP1, &pressed);
    pause_ms(1);
    process_record_user(TOP1, &depressed);
    pause_ms(1);
    process_record_user(TOP2, &pressed);
    pause_ms(1);
    process_record_user(TOP2, &depressed);
    
    pause_ms(LEADER_TIMEOUT);
    pause_ms(1);
    
    ASSERT_EQ(UINT, in_leader_mode, 0);
    ASSERT_EQ(UINT, keyboard_history[1][KC_Q], 255);
END_TEST

TEST("leader_correct_follow")
    process_record_user(TOP2, &pressed);
    process_record_user(TOP3, &pressed);
    process_record_user(BOT2, &pressed);
    process_record_user(BOT3, &pressed);
    pause_ms(1);
    process_record_user(TOP2, &depressed);
    process_record_user(TOP3, &depressed);
    process_record_user(BOT2, &depressed);
    process_record_user(BOT3, &depressed);
    
    ASSERT_EQ(UINT, in_leader_mode, 1);

    pause_ms(1);
    process_record_user(TOP0, &pressed);
    pause_ms(1);
    process_record_user(TOP0, &depressed);
    pause_ms(1);
    process_record_user(TOP9, &pressed);
    pause_ms(1);
    process_record_user(TOP9, &depressed);
    
    pause_ms(LEADER_TIMEOUT);
    ASSERT_EQ(UINT, in_leader_mode, 1);
    
    pause_ms(1);    
    ASSERT_EQ(UINT, in_leader_mode, 0);
    
    ASSERT_EQ(UINT, keyboard_history[1][KC_O], 0);
    ASSERT_EQ(UINT, keyboard_history[1][KC_P], 0);
    ASSERT_EQ(UINT, keyboard_history[1][KC_A], 0);
    ASSERT_EQ(UINT, keyboard_history[1][KC_S], 1);
    
    ASSERT_EQ(UINT, keyboard_history[2][KC_O], 0);
    ASSERT_EQ(UINT, keyboard_history[2][KC_P], 0);
    ASSERT_EQ(UINT, keyboard_history[2][KC_A], 0);
    ASSERT_EQ(UINT, keyboard_history[2][KC_S], 0);
    
    ASSERT_EQ(UINT, keyboard_history[3][KC_O], 255);
    ASSERT_EQ(UINT, keyboard_history[3][KC_P], 255);
    ASSERT_EQ(UINT, keyboard_history[3][KC_A], 255);
    ASSERT_EQ(UINT, keyboard_history[3][KC_S], 255);
    
    ASSERT_EQ(UINT, keyboard_history[4][KC_O], 255);
    ASSERT_EQ(UINT, keyboard_history[4][KC_P], 255);
    ASSERT_EQ(UINT, keyboard_history[4][KC_A], 255);
    ASSERT_EQ(UINT, keyboard_history[4][KC_S], 255);
    
    ASSERT_EQ(UINT, keyboard_history[5][KC_Q], 255);
END_TEST

// DYNAMIC MACRO
TEST("dynamic_macro_record_mode")
    current_pseudolayer = NUM;
    
    // record
    ASSERT_EQ(UINT, dynamic_macro_mode, 0);
    process_record_user(BOT7, &pressed);
    process_record_user(BOT7, &depressed);
    ASSERT_EQ(UINT, dynamic_macro_mode, 1);
    pause_ms(1000);
    ASSERT_EQ(UINT, dynamic_macro_mode, 1);
END_TEST

TEST("dynamic_macro_record_mode_off")
    current_pseudolayer = NUM;
    
    process_record_user(BOT7, &pressed);
    process_record_user(BOT7, &depressed);
    ASSERT_EQ(UINT, dynamic_macro_mode, 1);
    
    process_record_user(BOT9, &pressed);
    process_record_user(BOT9, &depressed);
    ASSERT_EQ(UINT, dynamic_macro_mode, 0);
END_TEST

TEST("dynamic_macro_record_one")
    current_pseudolayer = NUM;
    
    process_record_user(BOT7, &pressed);
    process_record_user(BOT7, &depressed);
    ASSERT_EQ(UINT, dynamic_macro_mode, 1);
    
    process_record_user(TOP1, &pressed);
    process_record_user(TOP1, &depressed);
    
    ASSERT_EQ(UINT, keyboard_history[1][KC_1], 255);
    
    process_record_user(BOT9, &pressed);
    process_record_user(BOT9, &depressed);
    
    pause_ms(1000);
    
    process_record_user(BOT0, &pressed);
    process_record_user(BOT0, &depressed);
    
    ASSERT_EQ(UINT, keyboard_history[1][KC_1], 1);
    ASSERT_EQ(UINT, keyboard_history[2][KC_1], 0);
    ASSERT_EQ(UINT, keyboard_history[3][KC_1], 255);
    
    pause_ms(1000);
    
    process_record_user(BOT0, &pressed);
    process_record_user(BOT0, &depressed);
    
    ASSERT_EQ(UINT, keyboard_history[3][KC_1], 1);
    ASSERT_EQ(UINT, keyboard_history[4][KC_1], 0);
    ASSERT_EQ(UINT, keyboard_history[5][KC_1], 255);
END_TEST

TEST("dynamic_macro_record_two")
    current_pseudolayer = NUM;
    
    process_record_user(BOT7, &pressed);
    process_record_user(BOT7, &depressed);
    ASSERT_EQ(UINT, dynamic_macro_mode, 1);
    
    process_record_user(TOP1, &pressed);
    process_record_user(TOP1, &depressed);
    
    process_record_user(TOP2, &pressed);
    process_record_user(TOP2, &depressed);
    
    ASSERT_EQ(UINT, keyboard_history[1][KC_1], 255);
    
    process_record_user(BOT9, &pressed);
    process_record_user(BOT9, &depressed);
    
    pause_ms(1000);
    
    process_record_user(BOT0, &pressed);
    process_record_user(BOT0, &depressed);
    
    ASSERT_EQ(UINT, keyboard_history[1][KC_1], 1);
    ASSERT_EQ(UINT, keyboard_history[2][KC_2], 1);
    ASSERT_EQ(UINT, keyboard_history[3][KC_1], 0);
    ASSERT_EQ(UINT, keyboard_history[4][KC_2], 0);
    ASSERT_EQ(UINT, keyboard_history[5][KC_1], 255);
END_TEST

TEST("dynamic_macro_record_two_parts")
    current_pseudolayer = NUM;
    
    process_record_user(BOT7, &pressed);
    process_record_user(BOT7, &depressed);
    ASSERT_EQ(UINT, dynamic_macro_mode, 1);
    
    process_record_user(TOP1, &pressed);
    process_record_user(TOP1, &depressed);
    
    process_record_user(TOP2, &pressed);
    process_record_user(TOP2, &depressed);
    
    ASSERT_EQ(UINT, keyboard_history[1][KC_1], 255);
    
    process_record_user(BOT8, &pressed);
    process_record_user(BOT8, &depressed);
    
    process_record_user(TOP3, &pressed);
    process_record_user(TOP3, &depressed);
    
    process_record_user(BOT9, &pressed);
    process_record_user(BOT9, &depressed);
    
    pause_ms(1000);
    
    process_record_user(BOT0, &pressed);
    process_record_user(BOT0, &depressed);
    
    ASSERT_EQ(UINT, keyboard_history[1][KC_1], 1);
    ASSERT_EQ(UINT, keyboard_history[1][KC_2], 0);
    ASSERT_EQ(UINT, keyboard_history[1][KC_3], 0);
    
    ASSERT_EQ(UINT, keyboard_history[2][KC_1], 1);
    ASSERT_EQ(UINT, keyboard_history[2][KC_2], 1);
    ASSERT_EQ(UINT, keyboard_history[2][KC_3], 0);
    
    ASSERT_EQ(UINT, keyboard_history[3][KC_1], 0);
    ASSERT_EQ(UINT, keyboard_history[3][KC_2], 1);
    ASSERT_EQ(UINT, keyboard_history[3][KC_3], 0);
    
    ASSERT_EQ(UINT, keyboard_history[4][KC_1], 0);
    ASSERT_EQ(UINT, keyboard_history[4][KC_2], 0);
    ASSERT_EQ(UINT, keyboard_history[4][KC_3], 0);
    
    ASSERT_EQ(UINT, keyboard_history[5][KC_1], 0);
    ASSERT_EQ(UINT, keyboard_history[5][KC_2], 0);
    ASSERT_EQ(UINT, keyboard_history[5][KC_3], 1);
    
    ASSERT_EQ(UINT, keyboard_history[6][KC_1], 0);
    ASSERT_EQ(UINT, keyboard_history[6][KC_2], 0);
    ASSERT_EQ(UINT, keyboard_history[6][KC_3], 0);
    
    ASSERT_EQ(UINT, keyboard_history[7][KC_1], 255);
END_TEST

// dance + M()

TEST("dance_tap")
    process_record_user(BOT0, &pressed);
    process_record_user(BOT0, &depressed);
    
    pause_ms(1000);
    
    ASSERT_EQ(UINT, keyboard_history[1][KC_9], 1);
    ASSERT_EQ(UINT, keyboard_history[1][KC_0], 0);
    ASSERT_EQ(UINT, keyboard_history[2][KC_9], 0);
    ASSERT_EQ(UINT, keyboard_history[2][KC_0], 0);
    ASSERT_EQ(UINT, keyboard_history[3][KC_9], 255);
END_TEST

TEST("dance_hold")
    process_record_user(BOT0, &pressed);
    pause_ms(1000);
    
    ASSERT_EQ(UINT, keyboard_history[1][KC_9], 1);
    
    process_record_user(BOT0, &depressed);
    ASSERT_EQ(UINT, keyboard_history[2][KC_9], 0);
END_TEST

TEST("dance_tap_tap")
    process_record_user(BOT0, &pressed);
    process_record_user(BOT0, &depressed);
    process_record_user(BOT0, &pressed);
    process_record_user(BOT0, &depressed);
    
    pause_ms(1000);
    
    ASSERT_EQ(UINT, keyboard_history[1][KC_9], 0);
    ASSERT_EQ(UINT, keyboard_history[1][KC_0], 1);
    ASSERT_EQ(UINT, keyboard_history[2][KC_9], 0);
    ASSERT_EQ(UINT, keyboard_history[2][KC_0], 0);
    ASSERT_EQ(UINT, keyboard_history[3][KC_9], 255);
END_TEST

TEST("dance_tap_hold")
    process_record_user(BOT0, &pressed);
    process_record_user(BOT0, &depressed);
    pause_ms(1);
    process_record_user(BOT0, &pressed);
    pause_ms(1000);
    
    ASSERT_EQ(UINT, keyboard_history[1][KC_0], 1);
    
    process_record_user(BOT0, &depressed);
    ASSERT_EQ(UINT, keyboard_history[2][KC_0], 0);
END_TEST

// MK
TEST("multiple_keys")
    current_pseudolayer = NUM;
    
    process_record_user(BOT1, &pressed);
    process_record_user(BOT1, &depressed);
    
    ASSERT_EQ(UINT, keyboard_history[1][KC_LCTL], 1);
    ASSERT_EQ(UINT, keyboard_history[1][KC_LSFT], 0);
    
    ASSERT_EQ(UINT, keyboard_history[2][KC_LCTL], 1);
    ASSERT_EQ(UINT, keyboard_history[2][KC_LSFT], 1);
    
    ASSERT_EQ(UINT, keyboard_history[3][KC_LCTL], 0);
    ASSERT_EQ(UINT, keyboard_history[3][KC_LSFT], 1);
    
    ASSERT_EQ(UINT, keyboard_history[4][KC_LCTL], 0);
    ASSERT_EQ(UINT, keyboard_history[4][KC_LSFT], 0);
    
    ASSERT_EQ(UINT, keyboard_history[5][KC_LCTL], 255);
END_TEST

TEST("multiple_keys_interleaved")
    current_pseudolayer = NUM;
    
    process_record_user(BOT1, &pressed);
    pause_ms(CHORD_TIMEOUT+1);
    
    process_record_user(TOP1, &pressed);
    process_record_user(TOP1, &depressed);
    process_record_user(TOP1, &pressed);
    process_record_user(TOP1, &depressed);
    process_record_user(TOP1, &pressed);
    process_record_user(TOP1, &depressed);
    
    process_record_user(BOT1, &depressed);
    
    ASSERT_EQ(UINT, keyboard_history[1][KC_LCTL], 1);
    ASSERT_EQ(UINT, keyboard_history[1][KC_LSFT], 0);
    
    ASSERT_EQ(UINT, keyboard_history[2][KC_LCTL], 1);
    ASSERT_EQ(UINT, keyboard_history[2][KC_LSFT], 1);
    
    ASSERT_EQ(UINT, keyboard_history[3][KC_1], 1);
    ASSERT_EQ(UINT, keyboard_history[4][KC_1], 0);
    ASSERT_EQ(UINT, keyboard_history[5][KC_1], 1);
    ASSERT_EQ(UINT, keyboard_history[6][KC_1], 0);
    ASSERT_EQ(UINT, keyboard_history[7][KC_1], 1);
    ASSERT_EQ(UINT, keyboard_history[8][KC_1], 0);
    
    ASSERT_EQ(UINT, keyboard_history[9][KC_LCTL], 0);
    ASSERT_EQ(UINT, keyboard_history[9][KC_LSFT], 1);
    
    ASSERT_EQ(UINT, keyboard_history[10][KC_LCTL], 0);
    ASSERT_EQ(UINT, keyboard_history[10][KC_LSFT], 0);
    
    ASSERT_EQ(UINT, keyboard_history[11][KC_LCTL], 255);
END_TEST

// D
TEST("dance_one")
    current_pseudolayer = NUM;
    
    process_record_user(BOT3, &pressed);
    process_record_user(BOT3, &depressed);
    
    pause_ms(CHORD_TIMEOUT+DANCE_TIMEOUT+2);
    
    ASSERT_EQ(UINT, keyboard_history[1][KC_1], 1);
    ASSERT_EQ(UINT, keyboard_history[2][KC_1], 0);
    ASSERT_EQ(UINT, keyboard_history[3][KC_1], 255);
    
    process_record_user(BOT3, &pressed);
    process_record_user(BOT3, &depressed);
    
    pause_ms(CHORD_TIMEOUT+DANCE_TIMEOUT+2);
    
    ASSERT_EQ(UINT, keyboard_history[1][KC_1], 1);
    ASSERT_EQ(UINT, keyboard_history[2][KC_1], 0);
    ASSERT_EQ(UINT, keyboard_history[3][KC_1], 1);
    ASSERT_EQ(UINT, keyboard_history[4][KC_1], 0);
    ASSERT_EQ(UINT, keyboard_history[5][KC_1], 255);
END_TEST

TEST("dance_two")
    current_pseudolayer = NUM;
    
    process_record_user(BOT3, &pressed);
    process_record_user(BOT3, &depressed);
    process_record_user(BOT3, &pressed);
    process_record_user(BOT3, &depressed);
    
    pause_ms(CHORD_TIMEOUT+DANCE_TIMEOUT+2);
    
    ASSERT_EQ(UINT, keyboard_history[1][KC_2], 1);
    ASSERT_EQ(UINT, keyboard_history[2][KC_2], 0);
    ASSERT_EQ(UINT, keyboard_history[3][KC_2], 255);
    
    process_record_user(BOT3, &pressed);
    process_record_user(BOT3, &depressed);
    process_record_user(BOT3, &pressed);
    process_record_user(BOT3, &depressed);
    
    pause_ms(CHORD_TIMEOUT+DANCE_TIMEOUT+2);
    
    ASSERT_EQ(UINT, keyboard_history[1][KC_2], 1);
    ASSERT_EQ(UINT, keyboard_history[2][KC_2], 0);
    ASSERT_EQ(UINT, keyboard_history[3][KC_2], 1);
    ASSERT_EQ(UINT, keyboard_history[4][KC_2], 0);
    ASSERT_EQ(UINT, keyboard_history[5][KC_2], 255);
END_TEST

TEST("dance_three")
    current_pseudolayer = NUM;
    
    process_record_user(BOT3, &pressed);
    process_record_user(BOT3, &depressed);
    process_record_user(BOT3, &pressed);
    process_record_user(BOT3, &depressed);
    process_record_user(BOT3, &pressed);
    process_record_user(BOT3, &depressed);
    
    pause_ms(CHORD_TIMEOUT+DANCE_TIMEOUT+2);
    
    ASSERT_EQ(UINT, keyboard_history[1][KC_3], 1);
    ASSERT_EQ(UINT, keyboard_history[2][KC_3], 0);
    ASSERT_EQ(UINT, keyboard_history[3][KC_3], 255);
    
    process_record_user(BOT3, &pressed);
    process_record_user(BOT3, &depressed);
    process_record_user(BOT3, &pressed);
    process_record_user(BOT3, &depressed);
    process_record_user(BOT3, &pressed);
    process_record_user(BOT3, &depressed);
    
    pause_ms(CHORD_TIMEOUT+DANCE_TIMEOUT+2);
    
    ASSERT_EQ(UINT, keyboard_history[1][KC_3], 1);
    ASSERT_EQ(UINT, keyboard_history[2][KC_3], 0);
    ASSERT_EQ(UINT, keyboard_history[3][KC_3], 1);
    ASSERT_EQ(UINT, keyboard_history[4][KC_3], 0);
    ASSERT_EQ(UINT, keyboard_history[5][KC_3], 255);
END_TEST

TEST("dance_two_held")
    current_pseudolayer = NUM;
    
    process_record_user(BOT3, &pressed);
    process_record_user(BOT3, &depressed);
    process_record_user(BOT3, &pressed);
    
    pause_ms(CHORD_TIMEOUT+DANCE_TIMEOUT+2);
    
    ASSERT_EQ(UINT, keyboard_history[1][KC_2], 1);
    ASSERT_EQ(UINT, keyboard_history[2][KC_2], 255);
    
    process_record_user(BOT3, &depressed);
    ASSERT_EQ(UINT, keyboard_history[2][KC_2], 0);
    ASSERT_EQ(UINT, keyboard_history[3][KC_2], 255);
END_TEST

// These two are leaving the chording engine, they kinda have to be tested manually
// TO
// RESET

END
