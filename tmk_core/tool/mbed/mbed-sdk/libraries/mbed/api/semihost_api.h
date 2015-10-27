/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef MBED_SEMIHOST_H
#define MBED_SEMIHOST_H

#include "device.h"
#include "toolchain.h"

#ifdef __cplusplus
extern "C" {
#endif

#if DEVICE_SEMIHOST

#ifndef __CC_ARM

#if defined(__ICCARM__)
inline int __semihost(int reason, const void *arg) {
    return __semihosting(reason, (void*)arg);
}
#else

#ifdef __thumb__
#   define AngelSWI            0xAB
#   define AngelSWIInsn        "bkpt"
#   define AngelSWIAsm          bkpt
#else
#   define AngelSWI            0x123456
#   define AngelSWIInsn        "swi"
#   define AngelSWIAsm          swi
#endif

static inline int __semihost(int reason, const void *arg) {
    int value;

    asm volatile (
       "mov r0, %1"          "\n\t"
       "mov r1, %2"          "\n\t"
       AngelSWIInsn " %a3"   "\n\t"
       "mov %0, r0"
       : "=r" (value)                                         /* output operands             */
       : "r" (reason), "r" (arg), "i" (AngelSWI)              /* input operands              */
       : "r0", "r1", "r2", "r3", "ip", "lr", "memory", "cc"   /* list of clobbered registers */
    );

    return value;
}
#endif
#endif

#if DEVICE_LOCALFILESYSTEM
FILEHANDLE semihost_open(const char* name, int openmode);
int semihost_close (FILEHANDLE fh);
int semihost_read  (FILEHANDLE fh, unsigned char* buffer, unsigned int length, int mode);
int semihost_write (FILEHANDLE fh, const unsigned char* buffer, unsigned int length, int mode);
int semihost_ensure(FILEHANDLE fh);
long semihost_flen (FILEHANDLE fh);
int semihost_seek  (FILEHANDLE fh, long position);
int semihost_istty (FILEHANDLE fh);

int semihost_remove(const char *name);
int semihost_rename(const char *old_name, const char *new_name);
#endif

int semihost_uid(char *uid);
int semihost_reset(void);
int semihost_vbus(void);
int semihost_powerdown(void);
int semihost_exit(void);

int semihost_connected(void);
int semihost_disabledebug(void);

#endif

#ifdef __cplusplus
}
#endif

#endif
