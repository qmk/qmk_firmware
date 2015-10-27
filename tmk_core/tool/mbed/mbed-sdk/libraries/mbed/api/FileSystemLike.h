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
#ifndef MBED_FILESYSTEMLIKE_H
#define MBED_FILESYSTEMLIKE_H

#include "platform.h"

#include "FileBase.h"
#include "FileHandle.h"
#include "DirHandle.h"

namespace mbed {

/** A filesystem-like object is one that can be used to open files
 *  though it by fopen("/name/filename", mode)
 *
 *  Implementations must define at least open (the default definitions
 *  of the rest of the functions just return error values).
 */
class FileSystemLike : public FileBase {

public:
    /** FileSystemLike constructor
     *
     *  @param name The name to use for the filesystem.
     */
    FileSystemLike(const char *name);

    virtual ~FileSystemLike();

    static DirHandle *opendir();
    friend class BaseDirHandle;

    /** Opens a file from the filesystem
     *
     *  @param filename The name of the file to open.
     *  @param flags One of O_RDONLY, O_WRONLY, or O_RDWR, OR'd with
     *    zero or more of O_CREAT, O_TRUNC, or O_APPEND.
     *
     *  @returns
     *    A pointer to a FileHandle object representing the
     *   file on success, or NULL on failure.
     */
    virtual FileHandle *open(const char *filename, int flags) = 0;

    /** Remove a file from the filesystem.
     *
     *  @param filename the name of the file to remove.
     *  @param returns 0 on success, -1 on failure.
     */
    virtual int remove(const char *filename) { return -1; };

    /** Rename a file in the filesystem.
     *
     *  @param oldname the name of the file to rename.
     *  @param newname the name to rename it to.
     *
     *  @returns
     *    0 on success,
     *   -1 on failure.
     */
    virtual int rename(const char *oldname, const char *newname) { return -1; };

    /** Opens a directory in the filesystem and returns a DirHandle
     *   representing the directory stream.
     *
     *  @param name The name of the directory to open.
     *
     *  @returns
     *    A DirHandle representing the directory stream, or
     *   NULL on failure.
     */
    virtual DirHandle *opendir(const char *name) { return NULL; };

    /** Creates a directory in the filesystem.
     *
     *  @param name The name of the directory to create.
     *  @param mode The permissions to create the directory with.
     *
     *  @returns
     *    0 on success,
     *   -1 on failure.
     */
    virtual int mkdir(const char *name, mode_t mode) { return -1; }

    // TODO other filesystem functions (mkdir, rm, rn, ls etc)
};

} // namespace mbed

#endif
