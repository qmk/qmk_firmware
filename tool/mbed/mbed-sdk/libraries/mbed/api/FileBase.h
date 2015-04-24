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
#ifndef MBED_FILEBASE_H
#define MBED_FILEBASE_H

typedef int FILEHANDLE;

#include <stdio.h>

#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
#    define O_RDONLY 0
#    define O_WRONLY 1
#    define O_RDWR   2
#    define O_CREAT  0x0200
#    define O_TRUNC  0x0400
#    define O_APPEND 0x0008

#    define NAME_MAX 255

typedef int mode_t;
typedef int ssize_t;
typedef long off_t;

#else
#    include <sys/fcntl.h>
#    include <sys/types.h>
#    include <sys/syslimits.h>
#endif

#include "platform.h"

namespace mbed {

typedef enum {
    FilePathType,
    FileSystemPathType
} PathType;

class FileBase {
public:
    FileBase(const char *name, PathType t);

    virtual ~FileBase();

    const char* getName(void);
    PathType    getPathType(void);

    static FileBase *lookup(const char *name, unsigned int len);

    static FileBase *get(int n);

protected:
    static FileBase *_head;

    FileBase   *_next;
    const char *_name;
    PathType    _path_type;

    /* disallow copy constructor and assignment operators */
private:
    FileBase(const FileBase&);
    FileBase & operator = (const FileBase&);
};

} // namespace mbed

#endif
