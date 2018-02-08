char* morse[] = {
  [KC_A] = ".-",
  [KC_B] = "-...",
  [KC_C] = "-.-.",
  [KC_D] = "-..",
  [KC_E] = ".",
  [KC_F] = "..-.",
  [KC_G] = "--.",
  [KC_H] = "....",
  [KC_I] = "..",
  [KC_J] = ".---",
  [KC_K] = "-.-",
  [KC_L] = ".-..",
  [KC_M] = "--",
  [KC_N] = "-.",
  [KC_O] = "---",
  [KC_P] = ".--.",
  [KC_Q] = "--.-",
  [KC_R] = ".-.",
  [KC_S] = "...",
  [KC_T] = "-",
  [KC_U] = "..-",
  [KC_V] = "...-",
  [KC_W] = ".--",
  [KC_X] = "-..-",
  [KC_Y] = "-.--",
  [KC_Z] = "--..",
  [KC_1] = ".----",
  [KC_2] = "..---",
  [KC_3] = "...--",
  [KC_4] = "....-",
  [KC_5] = ".....",
  [KC_6] = "-....",
  [KC_7] = "--...",
  [KC_8] = "---..",
  [KC_9] = "----.",
  [KC_0] = "-----",
  [KC_SPACE] = " "
};

#define MORSE_UNIT 16.0

float dot_unit[][2] = SONG(M__NOTE(_A4, MORSE_UNIT));
float dash_unit[][2] = SONG(M__NOTE(_A4, MORSE_UNIT * 3));
float space_unit[][2] = SONG(M__NOTE(_A4, MORSE_UNIT * 7));

bool record_morse = false;
char morse_text[5 * 64] = "\0";

bool check_morse(uint16_t keycode) {
  if(record_morse) {
    if(keycode == KC_ENTER) {
      record_morse = false;

      for(int x = 0; x < strlen(morse_text); x++) {
        char c = morse_text[x];
        xprintf("%c\n", c);
        switch(c) {
          case '.': PLAY_SONG(dot_unit); break;
          case '-': PLAY_SONG(dash_unit); break;
          case ' ': PLAY_SONG(space_unit); break;
        }

        wait_ms(500);
      }

      strcpy(morse_text, "\0");

      return true;
    } else {
      strcat(morse_text, morse[keycode]);
      xprintf("%s\n", morse_text);
      return true;
    }
  }

  return false;
}
