#include "xprintf.h"
#include "sendchar.h"

void print_set_sendchar(SendcharFunc func) { xdev_out(func); }