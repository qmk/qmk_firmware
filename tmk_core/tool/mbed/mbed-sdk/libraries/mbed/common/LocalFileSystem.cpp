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
#include "LocalFileSystem.h"

#if DEVICE_LOCALFILESYSTEM

#include "semihost_api.h"
#include <string.h>
#include <stdio.h>

namespace mbed {

/* Extension to FINFO type defined in RTL.h (in Keil RL) - adds 'create time'. */
typedef struct {
    unsigned char  hr;   /* Hours    [0..23]                  */
    unsigned char  min;  /* Minutes  [0..59]                  */
    unsigned char  sec;  /* Seconds  [0..59]                  */
    unsigned char  day;  /* Day      [1..31]                  */
    unsigned char  mon;  /* Month    [1..12]                  */
    unsigned short year; /* Year     [1980..2107]             */
} FTIME;

typedef struct {         /* File Search info record           */
    char  name[32];      /* File name                         */
    long  size;          /* File size in bytes                */
    int   fileID;        /* System File Identification        */
    FTIME create_time;   /* Date & time file was created      */
    FTIME write_time;    /* Date & time of last write         */
} XFINFO;

#define RESERVED_FOR_USER_APPLICATIONS (0x100) /* 0x100 - 0x1ff */
#define USR_XFFIND (RESERVED_FOR_USER_APPLICATIONS + 0)

static int xffind (const char *pattern, XFINFO *info) {
    unsigned param[4];

    param[0] = (unsigned long)pattern;
    param[1] = (unsigned long)strlen(pattern);
    param[2] = (unsigned long)info;
    param[3] = (unsigned long)sizeof(XFINFO);

    return __semihost(USR_XFFIND, param);
}

#define OPEN_R          0
#define OPEN_B          1
#define OPEN_PLUS       2
#define OPEN_W          4
#define OPEN_A          8
#define OPEN_INVALID   -1

int posix_to_semihost_open_flags(int flags) {
    /* POSIX flags -> semihosting open mode */
    int openmode;
    if (flags & O_RDWR) {
        /* a plus mode */
        openmode = OPEN_PLUS;
        if (flags & O_APPEND) {
            openmode |= OPEN_A;
        } else if (flags & O_TRUNC) {
            openmode |= OPEN_W;
        } else {
            openmode |= OPEN_R;
        }
    } else if (flags & O_WRONLY) {
        /* write or append */
        if (flags & O_APPEND) {
            openmode = OPEN_A;
        } else {
            openmode = OPEN_W;
        }
    } else if (flags == O_RDONLY) {
        /* read mode */
        openmode = OPEN_R;
    } else {
        /* invalid flags */
        openmode = OPEN_INVALID;
    }

    return openmode;
}

FILEHANDLE local_file_open(const char* name, int flags) {
    int openmode = posix_to_semihost_open_flags(flags);
    if (openmode == OPEN_INVALID) {
        return (FILEHANDLE)NULL;
    }

    FILEHANDLE fh = semihost_open(name, openmode);
    if (fh == -1) {
        return (FILEHANDLE)NULL;
    }

    return fh;
}

LocalFileHandle::LocalFileHandle(FILEHANDLE fh) : _fh(fh), pos(0) {
}

int LocalFileHandle::close() {
    int retval = semihost_close(_fh);
    delete this;
    return retval;
}

ssize_t LocalFileHandle::write(const void *buffer, size_t length) {
    ssize_t n = semihost_write(_fh, (const unsigned char*)buffer, length, 0); // number of characters not written
    n = length - n; // number of characters written
    pos += n;
    return n;
}

ssize_t LocalFileHandle::read(void *buffer, size_t length) {
    ssize_t n = semihost_read(_fh, (unsigned char*)buffer, length, 0); // number of characters not read
    n = length - n; // number of characters read
    pos += n;
    return n;
}

int LocalFileHandle::isatty() {
    return semihost_istty(_fh);
}

off_t LocalFileHandle::lseek(off_t position, int whence) {
    if (whence == SEEK_CUR) {
        position += pos;
    } else if (whence == SEEK_END) {
        position += semihost_flen(_fh);
    } /* otherwise SEEK_SET, so position is fine */

    /* Always seems to return -1, so just ignore for now. */
    semihost_seek(_fh, position);
    pos = position;
    return position;
}

int LocalFileHandle::fsync() {
    return semihost_ensure(_fh);
}

off_t LocalFileHandle::flen() {
    return semihost_flen(_fh);
}

class LocalDirHandle : public DirHandle {

public:
    struct dirent cur_entry;
    XFINFO info;

    LocalDirHandle() : cur_entry(), info() {
    }

    virtual int closedir() {
        delete this;
        return 0;
    }

    virtual struct dirent *readdir() {
        if (xffind("*", &info)!=0) {
            return NULL;
        }
        memcpy(cur_entry.d_name, info.name, sizeof(info.name));
        return &cur_entry;
    }

    virtual void rewinddir() {
        info.fileID = 0;
    }

    virtual off_t telldir() {
        return info.fileID;
    }

    virtual void seekdir(off_t offset) {
        info.fileID = offset;
    }
};

FileHandle *LocalFileSystem::open(const char* name, int flags) {
    /* reject filenames with / in them */
    for (const char *tmp = name; *tmp; tmp++) {
        if (*tmp == '/') {
            return NULL;
        }
    }

    int openmode = posix_to_semihost_open_flags(flags);
    if (openmode == OPEN_INVALID) {
        return NULL;
    }

    FILEHANDLE fh = semihost_open(name, openmode);
    if (fh == -1) {
        return NULL;
    }
    return new LocalFileHandle(fh);
}

int LocalFileSystem::remove(const char *filename) {
    return semihost_remove(filename);
}

DirHandle *LocalFileSystem::opendir(const char *name) {
    return new LocalDirHandle();
}

} // namespace mbed

#endif
