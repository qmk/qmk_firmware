#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"

#define NO_ACTION_ONESHOT
#define NO_ACTION_MACRO

#define MODS_SHIFT_MASK (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))

// Layer the calculator is on
#define CALC_LAYER 2

// Inside is whether when you are in calc mode it should automatically force numlock, outside is whether it should do it outside of calculator mode
#define CALC_FORCE_NUM_LOCK_INSIDE_CALC true
#define CALC_FORCE_NUM_LOCK_OUTSIDE_CALC true

// Maximum number of characters the calculator can have
#define CALC_BUFFER_SIZE 32

// Minimum width of the printed text / the number of decimal places
#define CALC_PRINT_SIZE 6

/*-----
  Special
-----*/
#define CALC_CHAR_BEG '('
#define CALC_CHAR_END ')'
#define CALC_CHAR_DEC '.'

/*-----
  Operators - Can add more here such as modulo %, factorial !
-----*/
#define CALC_CHAR_ADD '+'
#define CALC_PRIO_ADD 1

#define CALC_CHAR_SUB '-'
#define CALC_PRIO_SUB 1

#define CALC_CHAR_MUL '*'
#define CALC_PRIO_MUL 2

#define CALC_CHAR_DIV '/'
#define CALC_PRIO_DIV 2

#define CALC_CHAR_EXP '^'
#define CALC_PRIO_EXP 3

/*-----
  Functions
-----*/
#define CALC_CHAR_SIN 's'
#define CALC_CHAR_COS 'c'
#define CALC_CHAR_TAN 't'

#define CALC_CHAR_ASN 'S'
#define CALC_CHAR_ACS 'C'
#define CALC_CHAR_ATN 'T'

#define CALC_CHAR_LGE 'l'
#define CALC_CHAR_LOG 'L'

#define CALC_CHAR_SQT 'q'

/*-----
  Constants
-----*/
#define CALC_CHAR_EUL 'e'
#define CALC_VALU_EUL 2.71828182845904523536

#define CALC_CHAR_PI 'p'
#define CALC_VALU_PI 3.14159265358979323846

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

#endif
