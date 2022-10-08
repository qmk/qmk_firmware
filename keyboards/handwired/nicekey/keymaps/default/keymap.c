#include QMK_KEYBOARD_H

#define RANDOM_STRING_DELAY 100

enum custom_keycodes {
    RANDOM_STRING_MACRO = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT(
        RANDOM_STRING_MACRO
    )
};

const char sentence_01[] PROGMEM = "I hope you have a great day!";
const char sentence_02[] PROGMEM = "You are an awesome person.";
const char sentence_03[] PROGMEM = "I wish I knew you better, you seem nice!";
const char sentence_04[] PROGMEM = "Your views restore my faith in humanity";
const char sentence_05[] PROGMEM = "You are as cool as a norm-critical disney princess";
const char sentence_06[] PROGMEM = "You have impeccable manners.";
const char sentence_07[] PROGMEM = "You are making me smile";
const char sentence_08[] PROGMEM = "You are making a difference";
const char sentence_09[] PROGMEM = "You bring out the best in other people";
const char sentence_10[] PROGMEM = "You are all that and a super-size bag of chips.";
const char sentence_11[] PROGMEM = "You are not someone I pretend to not see in public.";
const char sentence_12[] PROGMEM = "Are you a beaver, because damn.";
const char sentence_13[] PROGMEM = "I bet you make babies smile.";
const char sentence_14[] PROGMEM = "You are awkward, in a cute way. Like an elevator ride, but with puppies.";
const char sentence_15[] PROGMEM = "Looking like a complete idiot with you is really fun.";
const char sentence_16[] PROGMEM = "If you cooked something really bad, I would tell you instead of eating it.";
const char sentence_17[] PROGMEM = "I love how passionate you are about your hobby.";
const char sentence_18[] PROGMEM = "Our conversations always make me feel better.";
const char sentence_19[] PROGMEM = "It is amazing how far out of your way you go to help people.";
const char sentence_20[] PROGMEM = "I am so glad that you wrote something here.";
const char sentence_21[] PROGMEM = "Hey you! How nice to see a friendly person in my feed!";
const char sentence_22[] PROGMEM = "I hope we know each other for a long time.";
const char sentence_23[] PROGMEM = "I bet if Britney Spears knew you, 2008 would have gone a lot differently.";
const char sentence_24[] PROGMEM = "I would trust you with my passwords.";
const char sentence_25[] PROGMEM = "You are a great problem solver";
const char sentence_26[] PROGMEM = "I would love to hear you laugh!";
const char sentence_27[] PROGMEM = "Please, have a monologue about your week, I just want to listen to you!";
const char sentence_28[] PROGMEM = "You are very far from being Trump.";
const char sentence_29[] PROGMEM = "I think my dog might like you more than me";
const char sentence_30[] PROGMEM = "I feel like you would be a great person to do a group project with";
const char sentence_31[] PROGMEM = "I bet animals love you";
const char sentence_32[] PROGMEM = "I bet even Kanye would like you more than himself";
const char sentence_33[] PROGMEM = "You are just doing a great job at life";
const char sentence_34[] PROGMEM = "I like how you are challenging me.";
const char sentence_35[] PROGMEM = "You would do be a great mother!";
const char sentence_36[] PROGMEM = "I... Baked bread for you.";
const char sentence_37[] PROGMEM = "Wow. You.";
const char sentence_38[] PROGMEM = "You would not have let that balrog pass!";
const char sentence_39[] PROGMEM = "Thank you.";
const char sentence_40[] PROGMEM = "You would be standing out in a crowd";
const char sentence_41[] PROGMEM = "Your sense of style is amazing.";
const char sentence_42[] PROGMEM = "You have a beautiful mind.";
const char sentence_43[] PROGMEM = "I like that big juicy brain of yours";
const char sentence_44[] PROGMEM = "I would share my cinnamon bun with you";
const char sentence_45[] PROGMEM = "I like you more than i like my moms apple pie";
const char sentence_46[] PROGMEM = "You give me the same feeling as a summers night";
const char sentence_47[] PROGMEM = "I enjoy you more than the click of my mechanical switch";
const char sentence_48[] PROGMEM = "I would let you pop my bubble wrap";
const char sentence_49[] PROGMEM = "Being near you is like being inside of a poem";

PGM_P const sentences[] PROGMEM = {
    sentence_01,
    sentence_02,
    sentence_03,
    sentence_04,
    sentence_05,
    sentence_06,
    sentence_07,
    sentence_08,
    sentence_09,
    sentence_10,
    sentence_11,
    sentence_12,
    sentence_13,
    sentence_14,
    sentence_15,
    sentence_16,
    sentence_17,
    sentence_18,
    sentence_19,
    sentence_20,
    sentence_21,
    sentence_22,
    sentence_23,
    sentence_24,
    sentence_25,
    sentence_26,
    sentence_27,
    sentence_28,
    sentence_29,
    sentence_30,
    sentence_31,
    sentence_32,
    sentence_33,
    sentence_34,
    sentence_35,
    sentence_36,
    sentence_37,
    sentence_38,
    sentence_39,
    sentence_40,
    sentence_41,
    sentence_42,
    sentence_43,
    sentence_44,
    sentence_45,
    sentence_46,
    sentence_47,
    sentence_48,
    sentence_49
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        int sentences_size = sizeof(sentences) / sizeof(sentences[0]);
        int i = rand() % sentences_size;

        switch (keycode) {
            case RANDOM_STRING_MACRO:
                send_string_with_delay_P((PGM_P)pgm_read_word(&(sentences[i])), RANDOM_STRING_DELAY);
                tap_code(KC_ENT);

                return false;
        }
    }

    return true;
}
