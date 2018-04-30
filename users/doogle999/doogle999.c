#include "doogle999.h"

char backspaceText[BUFFER_SIZE + 1]; // Pretty dumb waste of memory because only backspace characters, used with send_string to backspace and remove input
char text[BUFFER_SIZE + 1]; // Used to store input and then output when ready to print
unsigned char inputLocation = 0; // Current index in text input

double calc(char input[]) // Finds value of input char array, relatively small and fast I think
{
  char inputToken[BUFFER_SIZE + 1]; // Input buffer, used when a single token (generally a number) takes up more
  unsigned char inputTokenLocation = 0, inputLocation = 0; // Keep track of indices

  struct Token tokens[BUFFER_SIZE + 1]; // Input, converted to tokens, one extra large to accomodate for possible negative sign then open parenthesis as first character
  unsigned char tokenCount = 0; // Keep track of index

  bool dashAsMinus = false; // Kind of a hacky solution to determining whether to treat a dash as a minus sign or a negative sign

  while(inputLocation < BUFFER_SIZE)
  {
    short number = input[inputLocation] - '0'; // Using a short here because both signed char and unsigned char would overflow, potentially
    if(inputLocation == 0 && input[inputLocation] == CHAR_SUB && input[inputLocation + 1] == CHAR_BEG)
    {
      tokens[tokenCount].raw.num = 0;
      tokens[tokenCount].isNum = true;

      tokenCount++;
      dashAsMinus = true;
    }
    if((number < 10 && number >= 0) || (inputTokenLocation != 0 && input[inputLocation] == '.') || (!dashAsMinus && inputTokenLocation == 0 && input[inputLocation] == '-'))
    {
      inputToken[inputTokenLocation] = input[inputLocation];
      inputTokenLocation++;
      inputLocation++;
    }
    else
    {
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
      }
      tokens[tokenCount].isNum = false;
      tokens[tokenCount].raw.op.c = input[inputLocation];
      tokens[tokenCount].raw.op.priority = 0;
      tokens[tokenCount].raw.op.ltr = true;
      dashAsMinus = false;
      
      switch(input[inputLocation])
      {
      case CHAR_BEG:
        break;
      case CHAR_END:
        dashAsMinus = true;
        break;
      case CHAR_ADD:
        tokens[tokenCount].raw.op.priority = PRIO_ADD;
        break;
      case CHAR_SUB:
        tokens[tokenCount].raw.op.priority = PRIO_SUB;
        break;
      case CHAR_MUL:
        tokens[tokenCount].raw.op.priority = PRIO_MUL;
        break;
      case CHAR_DIV:
        tokens[tokenCount].raw.op.priority = PRIO_DIV;
        break;
      case CHAR_EXP:
        tokens[tokenCount].raw.op.priority = PRIO_EXP;
        tokens[tokenCount].raw.op.ltr = false;
        break;
      case CHAR_SIN:
        break;
      case CHAR_COS:
        break;
      case CHAR_TAN:
        break;
      case CHAR_ASN:
        break;
      case CHAR_ACS:
        break;
      case CHAR_ATN:
        break;
      case CHAR_LGE:
        break;
      case CHAR_LOG:
        break;
      case CHAR_SQT:
        break;
      case '\0':
        tokenCount--;
        inputLocation = BUFFER_SIZE;
        break;
      default:
        tokenCount--;
        break;
      }
      tokenCount++;
      inputLocation++;
    }
  }
  
  struct Token output[BUFFER_SIZE + 1]; // Final output tokens before evaluation
  struct Token opstack[BUFFER_SIZE + 1]; // Stack of operators
  unsigned char outputLocation = 0, opstackLocation = 0; // Keep track of indices

  unsigned char numBrackets = 0; // The number of parenthesis

  for(unsigned char i = 0; i < tokenCount; i++)
  {
    if(tokens[i].isNum)
    {
      output[outputLocation] = tokens[i];
      outputLocation++;
    }
    else if(tokens[i].raw.op.c == CHAR_BEG)
    {
      opstack[opstackLocation] = tokens[i];
      opstackLocation++;
    }
    else if(tokens[i].raw.op.c == CHAR_END)
    {
      while(opstack[opstackLocation - 1].raw.op.c != CHAR_BEG)
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
        && opstack[opstackLocation - 1].raw.op.c != CHAR_BEG)
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

  double answer[BUFFER_SIZE];
  unsigned char answerLocation = 0;

  for(unsigned char i = 0; i < tokenCount; i++)
  {
    if(output[i].isNum)
    {
      answer[answerLocation] = output[i].raw.num;
      answerLocation++;
    }
    else
    {
      if(output[i].raw.op.priority == 0)
      {
        if(answerLocation >= 1)
        {
          switch(output[i].raw.op.c)
          {
          case CHAR_SIN:
            answer[answerLocation - 1] = sin(answer[answerLocation - 1]);
            break;
          case CHAR_COS:
            answer[answerLocation - 1] = cos(answer[answerLocation - 1]);
            break;
          case CHAR_TAN:
            answer[answerLocation - 1] = tan(answer[answerLocation - 1]);
            break;
          case CHAR_ASN:
            answer[answerLocation - 1] = asin(answer[answerLocation - 1]);
            break;
          case CHAR_ACS:
            answer[answerLocation - 1] = acos(answer[answerLocation - 1]);
            break;
          case CHAR_ATN:
            answer[answerLocation - 1] = atan(answer[answerLocation - 1]);
            break;
          case CHAR_LGE:
            answer[answerLocation - 1] = log(answer[answerLocation - 1]);
            break;
          case CHAR_LOG:
            answer[answerLocation - 1] = log10(answer[answerLocation - 1]);
            break;
          case CHAR_SQT:
            answer[answerLocation - 1] = sqrt(answer[answerLocation - 1]);
            break;
          }
        }
      }
      else if(answerLocation >= 2)
      {
        switch(output[i].raw.op.c)
        {
        case CHAR_ADD:
          answer[answerLocation - 2] += answer[answerLocation - 1];
          break;
        case CHAR_SUB:
          answer[answerLocation - 2] -= answer[answerLocation - 1];
          break;
        case CHAR_MUL:
          answer[answerLocation - 2] *= answer[answerLocation - 1];
          break;
        case CHAR_DIV:
          answer[answerLocation - 2] /= answer[answerLocation - 1];
          break;
        case CHAR_EXP:
          answer[answerLocation - 2] = pow(answer[answerLocation - 2], answer[answerLocation - 1]);
          break;
        }

        answerLocation--;
      }
    }
  }

  return answer[0];
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  bool numpadKeyPressed = false;

  if(record->event.pressed)
  {
    if(!(get_mods() & MODS_SHIFT_MASK))
    {
      switch(keycode)
      {
      case KC_KP_0:
        numpadKeyPressed = true;
        break;
      case KC_KP_1:
        numpadKeyPressed = true;
        break;
      case KC_KP_2:
        numpadKeyPressed = true;
        break;
      case KC_KP_3:
        numpadKeyPressed = true;
        break;
      case KC_KP_4:
        numpadKeyPressed = true;
        break;
      case KC_KP_5:
        numpadKeyPressed = true;
        break;
      case KC_KP_6:
        numpadKeyPressed = true;
        break;
      case KC_KP_7:
        numpadKeyPressed = true;
        break;
      case KC_KP_8:
        numpadKeyPressed = true;
        break;
      case KC_KP_9:
        numpadKeyPressed = true;
        break;
      }
    }
  }
  if(numpadKeyPressed && !(host_keyboard_leds() & (1 << USB_LED_NUM_LOCK)))
  {
    add_key(KC_NLCK);
    send_keyboard_report();
  }

  if(biton32(layer_state) == 2)
  {
    char characterPressed = '\0';

    bool forceReturnTrue = false;

    if(record->event.pressed)
    {
      if(!(get_mods() & MODS_SHIFT_MASK))
      {
        switch(keycode)
        {
        case KC_0:
          characterPressed = '0';
          break;
        case KC_1:
          characterPressed = '1';
          break;
        case KC_2:
          characterPressed = '2';
          break;
        case KC_3:
          characterPressed = '3';
          break;
        case KC_4:
          characterPressed = '4';
          break;
        case KC_5:
          characterPressed = '5';
          break;
        case KC_6:
          characterPressed = '6';
          break;
        case KC_7:
          characterPressed = '7';
          break;
        case KC_8:
          characterPressed = '8';
          break;
        case KC_9:
          characterPressed = '9';
          break;
        case KC_MINUS:
          characterPressed = CHAR_SUB;
          break;
        case KC_SLASH:
          characterPressed = CHAR_DIV;
          break;
        case KC_S:
          characterPressed = CHAR_SIN;
          break;
        case KC_C:
          characterPressed = CHAR_COS;
          break;
        case KC_T:
          characterPressed = CHAR_TAN;
          break;
        case KC_Q:
          characterPressed = CHAR_SQT;
          break;
        case KC_L:
          characterPressed = CHAR_LGE;
          break;
        case KC_DOT:
          characterPressed = '.';
          break;
        case KC_BSPC:
          if(inputLocation > 0)
          {
            inputLocation--;
          }
          forceReturnTrue = true;
          break;
        case KC_RSFT:
          forceReturnTrue = true;
          break;
        case KC_LSFT:
          forceReturnTrue = true;
          break;
        case CALC:
          for(int i = 0; i < inputLocation; i++)
          {
            backspaceText[i] = (char)8;
          }
          send_string(backspaceText);
          dtostrf(calc(text), 6, 6, text);
          send_string(text);
          for(unsigned char i = 0; i < BUFFER_SIZE; i++)
          {
            text[i] = '\0';
            backspaceText[i] = '\0';
          }
          inputLocation = 0;
          break;
        case ENDCALC:
          layer_state = 0;
          break;
        default:
          break;
        }
      }
      else
      {
        switch(keycode)
        {
        case KC_9:
          characterPressed = CHAR_BEG;
          break;
        case KC_0:
          characterPressed = CHAR_END;
          break;
        case KC_EQUAL:
          characterPressed = CHAR_ADD;
          break;
        case KC_6:
          characterPressed = CHAR_EXP;
          break;
        case KC_8:
          characterPressed = CHAR_MUL;
          break;
        case KC_S:
          characterPressed = CHAR_ASN;
          break;
        case KC_C:
          characterPressed = CHAR_ACS;
          break;
        case KC_T:
          characterPressed = CHAR_ATN;
          break;
        case KC_L:
          characterPressed = CHAR_LOG;
          break;
        default:
          break;
        }
      }
    }

    if(inputLocation < BUFFER_SIZE && characterPressed != '\0')
    {
      text[inputLocation] = characterPressed;
      inputLocation++;
    }

    return (!record->event.pressed || (record->event.pressed && (characterPressed != '\0' || forceReturnTrue)));
  }
  else
  {
    return true;
  }
}