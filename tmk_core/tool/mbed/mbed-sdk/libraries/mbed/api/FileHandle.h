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
#ifndef MBED_FILEHANDLE_H
#define MBED_FILEHANDLE_H

typedef int FILEHANDLE;

#include <stdio.h>

#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
typedef int ssize_t;
typedef long off_t;

#else
#   include <sys/types.h>
#endif

namespace mbed {

/** An OO equivalent of the internal FILEHANDLE variable
 *  and associated _sys_* functions.
 *
 * FileHandle is an abstract class, needing at least sys_write and
 *  sys_read to be implmented for a simple interactive device.
 *
 * No one ever directly tals to/instanciates a FileHandle - it gets
 *  created by FileSystem, and wrapped up by stdio.
 */
class FileHandle {

public:
    /** Write the contents of a buffer to the file
     *
     *  @param buffer the buffer to write from
     *  @param length the number of characters to write
     *
     *  @returns
     *  The number of characters written (possibly 0) on success, -1 on error.
     */
    virtual ssize_t write(const void* buffer, size_t length) = 0;

    /** Close the file
     *
     *  @returns
     *  Zero on success, -1 on error.
     */
    virtual int close() = 0;

    /** Function read
     *  Reads the contents of the file into a buffer
     *
     *  @param buffer the buffer to read in to
     *  @param length the number of characters to read
     *
     *  @returns
     *  The number of characters read (zero at end of file) on success, -1 on error.
     */
    virtual ssize_t read(void* buffer, size_t length) = 0;

    /** Check if the handle is for a interactive terminal device.
     * If so, line buffered behaviour is used by default
     *
     *  @returns
     *    1 if it is a terminal,
     *    0 otherwise
     */
    virtual int isatty() = 0;

    /** Move the file position to a given offset from a given location.
     *
     *  @param offset The offset from whence to move to
     *  @param whence SEEK_SET for the start of the file, SEEK_CUR for the
     *   current file position, or SEEK_END for the end of the file.
     *
     *  @returns
     *    new file position on success,
     *    -1 on failure or unsupported
     */
    virtual off_t lseek(off_t offset, int whence) = 0;

    /** Flush any buffers associated with the FileHandle, ensuring it
     *  is up to date on disk
     *
     *  @returns
     *    0 on success or un-needed,
     *   -1 on error
     */
    virtual int fsync() = 0;

    virtual off_t flen() {
        /* remember our current position */
        off_t pos = lseek(0, SEEK_CUR);
        if(pos == -1) return -1;
        /* seek to the end to get the file length */
        off_t res = lseek(0, SEEK_END);
        /* return to our old position */
        lseek(pos, SEEK_SET);
        return res;
    }

    virtual ~FileHandle();
};

} // namespace mbed

#endif
