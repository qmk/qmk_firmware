#include QMK_KEYBOARD_H

enum custom_keycodes {
  RANDOM_STRING_MACRO = SAFE_RANGE
};

const int delay = 100;
const char *sentences[] = {
  "I hope you have a great day!\n",
  "You are an awesome person.\n",
  "I wish I knew you better, you seem nice!\n",
  "Your views restore my faith in humanity\n",
  "You are as cool as a norm-critical disney princess\n",
  "You have impeccable manners.\n",
  "You are making me smile\n",
  "You are making a difference\n",
  "You bring out the best in other people\n",
  "You are all that and a super-size bag of chips.\n",
  "You are not someone I pretend to not see in public.\n",
  "Are you a beaver, because damn.\n",
  "I bet you make babies smile.\n",
  "You are awkward, in a cute way. Like an elevator ride, but with puppies.\n",
  "Looking like a complete idiot with you is really fun.\n",
  "If you cooked something really bad, I would tell you instead of eating it.\n",
  "I love how passionate you are about your hobby.\n",
  "Our conversations always make me feel better.\n",
  "It is amazing how far out of your way you go to help people.\n",
  "I am so glad that you wrote something here.\n",
  "Hey you! How nice to see a friendly person in my feed!\n",
  "I hope we know each other for a long time.\n",
  "I bet if Britney Spears knew you, 2008 would have gone a lot differently.\n",
  "I would trust you with my passwords.\n",
  "You are a great problem solver\n",
  "I would love to hear you laugh!\n",
  "Please, have a monologue about your week, I just want to listen to you!\n",
  "You are very far from being Trump.\n",
  "I think my dog might like you more than me\n",
  "I feel like you would be a great person to do a group project with\n",
  "I bet animals love you\n",
  "I bet even Kanye would like you more than himself\n",
  "You are just doing a great job at life\n",
  "I like how you are challenging me.\n",
  "You would do be a great mother!\n",
  "I... Baked bread for you.\n",
  "Wow. You.\n",
  "You would not have let that balrog pass!\n",
  "Thank you.\n",
  "You would be standing out in a crowd\n",
  "Your sense of style is amazing.\n",
  "You have a beautiful mind.\n",
  "I like that big juicy brain of yours\n",
  "I would share my cinnamon bun with you\n",
  "I like you more than i like my moms apple pie\n",
  "You give me the same feeling as a summers night\n",
  "I enjoy you more than the click of my mechanical switch\n",
  "I would let you pop my bubble wrap\n",
  "Being near you is like being inside of a poem\n"
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    int sentences_size = sizeof(sentences) / sizeof(sentences[0]);
    int i = rand() % sentences_size;
    switch(keycode) {
      case RANDOM_STRING_MACRO:
        send_string_with_delay(sentences[i], delay);
        return false;
    }
  }
  return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  LAYOUT( RANDOM_STRING_MACRO )
};
