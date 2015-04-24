/* mbed Microcontroller Library - stackheap
 * Copyright (C) 2009-2011 ARM Limited. All rights reserved.
 *
 * Setup a fixed single stack/heap memory model,
 *  between the top of the RW/ZI region and the stackpointer
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>
#include <errno.h>

extern void exit(int return_code);

int _kill(int pid, int sig) {
    errno = EINVAL;
    return -1;
}

void _exit(int status) {
  exit(status);
}

int _getpid(void) {
  return 1;
}

#ifdef __cplusplus
}
#endif
