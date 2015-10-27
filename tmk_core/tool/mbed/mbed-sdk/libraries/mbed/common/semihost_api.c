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
#include "cmsis.h"
#include "semihost_api.h"

#include <stdint.h>
#include <string.h>

#if DEVICE_SEMIHOST

// ARM Semihosting Commands
#define SYS_OPEN   (0x1)
#define SYS_CLOSE  (0x2)
#define SYS_WRITE  (0x5)
#define SYS_READ   (0x6)
#define SYS_ISTTY  (0x9)
#define SYS_SEEK   (0xa)
#define SYS_ENSURE (0xb)
#define SYS_FLEN   (0xc)
#define SYS_REMOVE (0xe)
#define SYS_RENAME (0xf)
#define SYS_EXIT   (0x18)

// mbed Semihosting Commands
#define RESERVED_FOR_USER_APPLICATIONS (0x100) // 0x100 - 0x1ff
#define USR_XFFIND      (RESERVED_FOR_USER_APPLICATIONS + 0)
#define USR_UID      (RESERVED_FOR_USER_APPLICATIONS + 1)
#define USR_RESET     (RESERVED_FOR_USER_APPLICATIONS + 2)
#define USR_VBUS     (RESERVED_FOR_USER_APPLICATIONS + 3)
#define USR_POWERDOWN     (RESERVED_FOR_USER_APPLICATIONS + 4)
#define USR_DISABLEDEBUG (RESERVED_FOR_USER_APPLICATIONS + 5)

#if DEVICE_LOCALFILESYSTEM
FILEHANDLE semihost_open(const char* name, int openmode) {
    uint32_t args[3];
    args[0] = (uint32_t)name;
    args[1] = (uint32_t)openmode;
    args[2] = (uint32_t)strlen(name);
    return __semihost(SYS_OPEN, args);
}

int semihost_close(FILEHANDLE fh) {
    return __semihost(SYS_CLOSE, &fh);
}

int semihost_write(FILEHANDLE fh, const unsigned char* buffer, unsigned int length, int mode) {
    if (length == 0) return 0;

    uint32_t args[3];
    args[0] = (uint32_t)fh;
    args[1] = (uint32_t)buffer;
    args[2] = (uint32_t)length;
    return __semihost(SYS_WRITE, args);
}

int semihost_read(FILEHANDLE fh, unsigned char* buffer, unsigned int length, int mode) {
    uint32_t args[3];
    args[0] = (uint32_t)fh;
    args[1] = (uint32_t)buffer;
    args[2] = (uint32_t)length;
    return __semihost(SYS_READ, args);
}

int semihost_istty(FILEHANDLE fh) {
    return __semihost(SYS_ISTTY, &fh);
}

int semihost_seek(FILEHANDLE fh, long position) {
    uint32_t args[2];
    args[0] = (uint32_t)fh;
    args[1] = (uint32_t)position;
    return __semihost(SYS_SEEK, args);
}

int semihost_ensure(FILEHANDLE fh) {
    return __semihost(SYS_ENSURE, &fh);
}

long semihost_flen(FILEHANDLE fh) {
    return __semihost(SYS_FLEN, &fh);
}

int semihost_remove(const char *name) {
    uint32_t args[2];
    args[0] = (uint32_t)name;
    args[1] = (uint32_t)strlen(name);
    return __semihost(SYS_REMOVE, args);
}

int semihost_rename(const char *old_name, const char *new_name) {
    uint32_t args[4];
    args[0] = (uint32_t)old_name;
    args[1] = (uint32_t)strlen(old_name);
    args[0] = (uint32_t)new_name;
    args[1] = (uint32_t)strlen(new_name);
    return __semihost(SYS_RENAME, args);
}
#endif

int semihost_exit(void) {
    uint32_t args[4];
    return __semihost(SYS_EXIT, args);
}

int semihost_uid(char *uid) {
    uint32_t args[2];
    args[0] = (uint32_t)uid;
    args[1] = DEVICE_ID_LENGTH + 1;
    return __semihost(USR_UID, &args);
}

int semihost_reset(void) {
    // Does not normally return, however if used with older firmware versions
    // that do not support this call it will return -1.
    return __semihost(USR_RESET, NULL);
}

int semihost_vbus(void) {
    return __semihost(USR_VBUS, NULL);
}

int semihost_powerdown(void) {
    return __semihost(USR_POWERDOWN, NULL);
}

#if DEVICE_DEBUG_AWARENESS

int semihost_connected(void) {
    return (CoreDebug->DHCSR & CoreDebug_DHCSR_C_DEBUGEN_Msk) ? 1 : 0;
}

#else
// These processors cannot know if the interface is connect, assume so:
static int is_debugger_attached = 1;

int semihost_connected(void) {
    return is_debugger_attached;
}
#endif

int semihost_disabledebug(void) {
#if !(DEVICE_DEBUG_AWARENESS)
    is_debugger_attached = 0;
#endif
    return __semihost(USR_DISABLEDEBUG, NULL);
}

#endif

