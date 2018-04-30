#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"

#define NO_ACTION_ONESHOT
#define NO_ACTION_MACRO

#define MODS_SHIFT_MASK (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))

#define CALC_LAYER 2
#define FORCE_NUM_LOCK

#define BUFFER_SIZE 32

/*-----
  Special
-----*/

#define CHAR_BEG '('
#define CHAR_END ')'

/*-----
  Operators
-----*/

#define CHAR_ADD '+'
#define PRIO_ADD 1

#define CHAR_SUB '-'
#define PRIO_SUB 1

#define CHAR_MUL '*'
#define PRIO_MUL 2

#define CHAR_DIV '/'
#define PRIO_DIV 2

#define CHAR_EXP '^'
#define PRIO_EXP 3

/*-----
  Functions
-----*/

#define CHAR_SIN 's'
#define CHAR_COS 'c'
#define CHAR_TAN 't'

#define CHAR_ASN 'S'
#define CHAR_ACS 'C'
#define CHAR_ATN 'T'

#define CHAR_LGE 'l'
#define CHAR_LOG 'L'

#define CHAR_SQT 'q'

struct OP // Operator/function
{
  char c;
  unsigned char priority;
  bool ltr;
};

union TokenRaw // A token after the input has been processed, can either be a number or an operator/function
{
  double num;
  struct OP op;
};

struct Token // Encapsulator
{
  bool isNum;
  union TokenRaw raw;
};

enum CalcFunctions // Hardware calculator key functionality
{
  CALC = SAFE_RANGE,
  ENDCALC
};

extern char backspaceText[BUFFER_SIZE + 1]; // Pretty dumb waste of memory because only backspace characters, used with send_string to backspace and remove input
extern char text[BUFFER_SIZE + 1]; // Used to store input and then output when ready to print
extern unsigned char inputLocation; // Current index in text input

double calc(char input[]);

#endif