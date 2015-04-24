/* mbed Microcontroller Library - stackheap
 * Copyright (C) 2009-2011 ARM Limited. All rights reserved.
 *
 */

#include "sys_helper.h"

/* This function specifies the amount of memory of the internal RAM to
   reserve for the stack. The default implementation will reserve 0 bytes
   which gives the normal behaviour where the stack and heap share all the
   internal RAM.

   You can override this function in your code to reserve a number of bytes
   for the stack.
*/
extern "C" __attribute__((weak)) uint32_t __reserved_stack_size();
extern "C" __attribute__((weak)) uint32_t __reserved_stack_size() {
    return 0; // return 0 to indicate that nothing is reserved
}
