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
#ifndef MBED_DIRHANDLE_H
#define MBED_DIRHANDLE_H

#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
#   define NAME_MAX 255
typedef int mode_t;

#else
#   include <sys/syslimits.h>
#endif

#include "FileHandle.h"

struct dirent {
    char d_name[NAME_MAX+1];
};

namespace mbed {

/** Represents a directory stream. Objects of this type are returned
 *  by a FileSystemLike's opendir method. Implementations must define
 *  at least closedir, readdir and rewinddir.
 *
 *  If a FileSystemLike class defines the opendir method, then the
 *  directories of an object of that type can be accessed by
 *  DIR *d = opendir("/example/directory") (or opendir("/example")
 *  to open the root of the filesystem), and then using readdir(d) etc.
 *
 *  The root directory is considered to contain all FileLike and
 *  FileSystemLike objects, so the DIR* returned by opendir("/") will
 *  reflect this.
 */
class DirHandle {

public:
    /** Closes the directory.
     *
     *  @returns
     *    0 on success,
     *   -1 on error.
     */
    virtual int closedir()=0;

    /** Return the directory entry at the current position, and
     *  advances the position to the next entry.
     *
     * @returns
     *  A pointer to a dirent structure representing the
     *  directory entry at the current position, or NULL on reaching
     *  end of directory or error.
     */
    virtual struct dirent *readdir()=0;

    /** Resets the position to the beginning of the directory.
     */
    virtual void rewinddir()=0;

    /** Returns the current position of the DirHandle.
     *
     * @returns
     *   the current position,
     *  -1 on error.
     */
    virtual off_t telldir() { return -1; }

    /** Sets the position of the DirHandle.
     *
     *  @param location The location to seek to. Must be a value returned by telldir.
     */
    virtual void seekdir(off_t location) { }

    virtual ~DirHandle() {}
};

} // namespace mbed

typedef mbed::DirHandle DIR;

extern "C" {
    DIR *opendir(const char*);
    struct dirent *readdir(DIR *);
    int closedir(DIR*);
    void rewinddir(DIR*);
    long telldir(DIR*);
    void seekdir(DIR*, long);
    int mkdir(const char *name, mode_t n);
};

#endif /* MBED_DIRHANDLE_H */
