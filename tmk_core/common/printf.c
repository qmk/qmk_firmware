#include <stddef.h>
#include "sendchar.h"

// bind lib/printf to console interface - sendchar

static SendcharFunc func = NULL;

void print_set_sendchar(SendcharFunc send) { func = send; }

void _putchar(char character) {
    if (func) func(character);
}
