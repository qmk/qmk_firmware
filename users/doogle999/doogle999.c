#include "doogle999.h"

static unsigned char inputLocation = 0; // Current index in text input

static double calc(const char input[CALC_BUFFER_SIZE +1]) // Finds value of input char array, relatively small and fast I think
{
  char inputToken[CALC_BUFFER_SIZE + 1]; // Input buffer, used when a single token (generally a number) takes up more
  unsigned char inputTokenLocation = 0, inputLocation = 0; // Keep track of indices

  struct Token tokens[CALC_BUFFER_SIZE + 1]; // Input, converted to tokens, one extra large to accomodate for possible negative sign then open parenthesis as first character
  unsigned char tokenCount = 0; // Keep track of index

  bool dashAsMinus = false; // Kind of a hacky solution to determining whether to treat a dash as a minus sign or a negative sign

  while(inputLocation < CALC_BUFFER_SIZE + 1)
  {
    char digit = input[inputLocation];

    if(inputLocation == 0 && input[inputLocation] == CALC_CHAR_SUB && input[inputLocation + 1] == CALC_CHAR_BEG)
    {
      tokens[tokenCount].raw.num = 0;
      tokens[tokenCount].isNum = true;

      tokenCount++;
      dashAsMinus = true;
    }

    if ((digit >= '0' && digit <= '9') || /* valid digit */
        (inputTokenLocation != 0 && input[inputLocation] == CALC_CHAR_DEC) || /* valid floating point */
        (!dashAsMinus && inputTokenLocation == 0 && input[inputLocation] == CALC_CHAR_SUB)) /* - is negative sign */
    {
      inputToken[inputTokenLocation] = input[inputLocation];
      inputTokenLocation++;
      inputLocation++;
      continue;
    }

    if(inputTokenLocation != 0)
    {
      // sscanf(inputToken, "%lf", &tokens[tokenCount].raw.num); // I would like to use sscanf here, but the small version of stdio.h on the chip doesn't allow sscanf or its sister functions to be used to process floats
      tokens[tokenCount].raw.num = atof(inputToken);
      tokens[tokenCount].isNum = true;
      for(unsigned char i = 0; i < inputTokenLocation + 1; i++)
      {
        inputToken[i] = '\0';
      }
      inputTokenLocation = 0;
      tokenCount++;
      dashAsMinus = true;
      continue;
    }

    /* inputTokenLocation == 0 */
    tokens[tokenCount].isNum = false;
    tokens[tokenCount].raw.op.c = input[inputLocation];
    tokens[tokenCount].raw.op.priority = 0;
    tokens[tokenCount].raw.op.ltr = true;
    dashAsMinus = false;

    switch(input[inputLocation])
    {
      case CALC_CHAR_BEG:
        break;
      case CALC_CHAR_END:
        dashAsMinus = true;
        break;
      case CALC_CHAR_ADD:
        tokens[tokenCount].raw.op.priority = CALC_PRIO_ADD;
        break;
      case CALC_CHAR_SUB:
        tokens[tokenCount].raw.op.priority = CALC_PRIO_SUB;
        break;
      case CALC_CHAR_MUL:
        tokens[tokenCount].raw.op.priority = CALC_PRIO_MUL;
        break;
      case CALC_CHAR_DIV:
        tokens[tokenCount].raw.op.priority = CALC_PRIO_DIV;
        break;
      case CALC_CHAR_EXP:
        tokens[tokenCount].raw.op.priority = CALC_PRIO_EXP;
        tokens[tokenCount].raw.op.ltr = false;
        break;
      case CALC_CHAR_SIN:
      case CALC_CHAR_COS:
      case CALC_CHAR_TAN:
      case CALC_CHAR_ASN:
      case CALC_CHAR_ACS:
      case CALC_CHAR_ATN:
      case CALC_CHAR_LGE:
      case CALC_CHAR_LOG:
      case CALC_CHAR_SQT:
        break;
      case CALC_CHAR_EUL:
        tokens[tokenCount].isNum = true;
        tokens[tokenCount].raw.num = CALC_VALU_EUL;
        dashAsMinus = true;
        break;
      case CALC_CHAR_PI:
        tokens[tokenCount].isNum = true;
        tokens[tokenCount].raw.num = CALC_VALU_PI;
        dashAsMinus = true;
        break;
      case '\0':
        tokenCount--;
        inputLocation = CALC_BUFFER_SIZE;
        break;
      default:
        tokenCount--;
        break;
    }
    tokenCount++;
    inputLocation++;
  }

  struct Token output[CALC_BUFFER_SIZE + 1]; // Final output tokens before evaluation
  struct Token opstack[CALC_BUFFER_SIZE + 1]; // Stack of operators
  unsigned char outputLocation = 0, opstackLocation = 0; // Keep track of indices

  unsigned char numBrackets = 0; // The number of parenthesis

  for(unsigned char i = 0; i < tokenCount; i++)
  {
    if(tokens[i].isNum)
    {
      output[outputLocation] = tokens[i];
      outputLocation++;
    }
    else if(tokens[i].raw.op.c == CALC_CHAR_BEG)
    {
      opstack[opstackLocation] = tokens[i];
      opstackLocation++;
    }
    else if(tokens[i].raw.op.c == CALC_CHAR_END)
    {
      while(opstack[opstackLocation - 1].raw.op.c != CALC_CHAR_BEG)
      {
        output[outputLocation] = opstack[opstackLocation - 1];
        outputLocation++;
        opstackLocation--;
      }
      opstackLocation--;

      numBrackets += 2;
    }
    else if(tokens[i].raw.op.priority == 0)
    {
      opstack[opstackLocation] = tokens[i];
      opstackLocation++;
    }
    else
    {
      while(opstackLocation != 0
        && (opstack[opstackLocation - 1].raw.op.priority == 0
          || tokens[i].raw.op.priority < opstack[opstackLocation - 1].raw.op.priority
          || (tokens[i].raw.op.priority == opstack[opstackLocation - 1].raw.op.priority && opstack[opstackLocation - 1].raw.op.ltr))
        && opstack[opstackLocation - 1].raw.op.c != CALC_CHAR_BEG)
      {
        output[outputLocation] = opstack[opstackLocation - 1];
        outputLocation++;
        opstackLocation--;
      }
      opstack[opstackLocation] = tokens[i];
      opstackLocation++;
    }
  }

  tokenCount -= numBrackets;

  for(signed char i = opstackLocation - 1; i >= 0; i--)
  {
    output[outputLocation] = opstack[i];
    outputLocation++;
    opstackLocation--;
  }

  double answer[CALC_BUFFER_SIZE];
  unsigned char answerLocation = 0;

  for(unsigned char i = 0; i < tokenCount; i++)
  {
    if(output[i].isNum)
    {
      answer[answerLocation] = output[i].raw.num;
      answerLocation++;
      continue;
    }

    if(output[i].raw.op.priority == 0)
    {
      if (answerLocation < 1) { /* not handled here -- ERROR? */ } else
      if(answerLocation >= 1)
      {
        double (*op)(double);
        switch(output[i].raw.op.c)
        {
        case CALC_CHAR_SIN:
          op = sin;
          break;
        case CALC_CHAR_COS:
          op = cos;
          break;
        case CALC_CHAR_TAN:
          op = tan;
          break;
        case CALC_CHAR_ASN:
          op = asin;
          break;
        case CALC_CHAR_ACS:
          op = acos;
          break;
        case CALC_CHAR_ATN:
          op = atan;
          break;
        case CALC_CHAR_LGE:
          op = log;
          break;
        case CALC_CHAR_LOG:
          op = log10;
          break;
        case CALC_CHAR_SQT:
          op = sqrt;
          break;
        default:
          continue; /* invalid input */
        }
        answer[answerLocation - 1] = op(answer[answerLocation - 1]);
      }
    }
    /* priority != 0 */
    else if(answerLocation >= 2)
    {
      switch(output[i].raw.op.c)
      {
      case CALC_CHAR_ADD:
        answer[answerLocation - 2] += answer[answerLocation - 1];
        break;
      case CALC_CHAR_SUB:
        answer[answerLocation - 2] -= answer[answerLocation - 1];
        break;
      case CALC_CHAR_MUL:
        answer[answerLocation - 2] *= answer[answerLocation - 1];
        break;
      case CALC_CHAR_DIV:
        answer[answerLocation - 2] /= answer[answerLocation - 1];
        break;
      case CALC_CHAR_EXP:
        answer[answerLocation - 2] = pow(answer[answerLocation - 2], answer[answerLocation - 1]);
        break;
      }

      answerLocation--;
    }
  }

  return answer[0];
}

/*
 * @returns  0 when nothing should happen and QMK should work as usual
 * @returns -1 when invalid input was given, QMK should ignore it
 * @returns -2 when BSP should be done
 * @returns -3 when CALC should be done
 * @returns -4 when ENDCALC should be done
 * @returns positive value of CALC_* when normal input was processed
 */
static int process_input(const uint16_t keycode, const uint8_t mods, const keyevent_t event)
{
  /* handle even when no key was pressed */
  if(!event.pressed)
  {
    switch(keycode)
    {
      /* QMK should handle those */
      case KC_RSFT:
      case KC_LSFT:
        return 0;
        break;
    }
    /* ??? ignore */
    return -1;
  }

  /* when shift key is pressed handle characters differently */
  char characterPressed;
  if((get_mods() & MODS_SHIFT_MASK))
  {
    switch(keycode)
    {
      case KC_9:
        characterPressed = CALC_CHAR_BEG;
        break;
      case KC_0:
        characterPressed = CALC_CHAR_END;
        break;
      case KC_EQUAL:
        characterPressed = CALC_CHAR_ADD;
        break;
      case KC_KP_PLUS:
        characterPressed = CALC_CHAR_ADD;
        break;
      case KC_6:
        characterPressed = CALC_CHAR_EXP;
        break;
      case KC_8:
        characterPressed = CALC_CHAR_MUL;
        break;
      case KC_KP_ASTERISK:
        characterPressed = CALC_CHAR_MUL;
        break;
      case KC_S:
        characterPressed = CALC_CHAR_ASN;
        break;
      case KC_C:
        characterPressed = CALC_CHAR_ACS;
        break;
      case KC_T:
        characterPressed = CALC_CHAR_ATN;
        break;
      case KC_L:
        characterPressed = CALC_CHAR_LOG;
        break;
      default:
        return -1;
        break;
    }
    return characterPressed;
  }

  /* normal key handling:  shift not pressed */

  /* digits */
  if (keycode == KC_KP_0 || keycode == KC_0) {
    return '0';
  } else if (keycode >= KC_KP_1 && keycode <= KC_KP_9) {
    return keycode - KC_KP_1 +1 + '0';
  } else if (keycode >= KC_1 && keycode <= KC_9) {
    return keycode - KC_1 +1 + '0';
  }

  /* other tokens */
  switch (keycode) {
    case KC_MINUS:
    case KC_KP_MINUS:
      return characterPressed = CALC_CHAR_SUB;
    case KC_SLASH:
    case KC_KP_SLASH:
      return characterPressed = CALC_CHAR_DIV;
    case KC_S:
      return characterPressed = CALC_CHAR_SIN;
    case KC_C:
      return characterPressed = CALC_CHAR_COS;
    case KC_T:
      return characterPressed = CALC_CHAR_TAN;
    case KC_Q:
      return characterPressed = CALC_CHAR_SQT;
    case KC_L:
      return characterPressed = CALC_CHAR_LGE;
    case KC_DOT:
    case KC_KP_DOT:
      return characterPressed = CALC_CHAR_DEC;
    case KC_P:
      return characterPressed = CALC_CHAR_PI;
    case KC_E:
      return characterPressed = CALC_CHAR_EUL;
    case KC_BSPC:
      return -2;
    case KC_RSFT:
      return 0;
    case KC_LSFT:
      return 0;
    case CALC:
      return -3;
    case ENDCALC:
      return -4;
    default:
      return -1;
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t* record)
{
	static char text[CALC_BUFFER_SIZE + 1]; // Used to store input and then output when ready to print
	static char backspaceText[CALC_BUFFER_SIZE + 1]; // Pretty dumb waste of memory because only backspace characters, used with send_string to backspace and remove input

	if((get_highest_layer(layer_state) == CALC_LAYER && CALC_FORCE_NUM_LOCK_INSIDE_CALC) || (get_highest_layer(layer_state) != CALC_LAYER && CALC_FORCE_NUM_LOCK_OUTSIDE_CALC))
	{
		bool numpadKeyPressed = record->event.pressed &&
			!(get_mods() & MODS_SHIFT_MASK) &&
			/* KC_KP_1, KC_KP_2, ..., KC_KP_0, KC_KP_DOT */
			(keycode >= KC_KP_1 && keycode <= KC_KP_DOT);

		if(numpadKeyPressed && !host_keyboard_led_state().num_lock)
		{
			add_key(KC_NUM_LOCK);
			send_keyboard_report();
			del_key(KC_NUM_LOCK);
		}
	}

	if(get_highest_layer(layer_state) != CALC_LAYER) { return true; }

	int action = process_input(keycode, get_mods(), record->event);
	switch(action)
	{
	case 0:
		return true;
	case -1:
		return false;
	case -2:
		if(inputLocation > 0)
		{
			inputLocation--;
			text[inputLocation] = '\0';
			backspaceText[0] = (char)8;
			backspaceText[1] = '\0';
			send_string(backspaceText);
		}
		return false;
	case -3:
		for(int i = 0; i < inputLocation; i++)
		{
			backspaceText[i] = (char)8;
		}
		send_string(backspaceText);
		dtostrf(calc(text), CALC_PRINT_SIZE, CALC_PRINT_SIZE, text);
		send_string(text);
		for(unsigned char i = 0; i < CALC_BUFFER_SIZE; i++)
		{
			text[i] = '\0';
			backspaceText[i] = '\0';
		}
		inputLocation = 0;
		return false;
	case -4:
		for(unsigned char i = 0; i < CALC_BUFFER_SIZE; i++)
		{
			text[i] = '\0';
			backspaceText[i] = '\0';
		}
		inputLocation = 0;
		layer_off(CALC_LAYER);
		return false;
	default:
		break;
	}
	char characterPressed = (char)action;

	if(inputLocation < CALC_BUFFER_SIZE)
	{
		text[inputLocation] = characterPressed;
		inputLocation++;

		char characterToSend[2];
		characterToSend[0] = characterPressed;
		characterToSend[1] = '\0';

		send_string(characterToSend);
	}
	return false;
}
