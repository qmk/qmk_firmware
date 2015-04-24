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
#ifndef MBED_LOCALFILESYSTEM_H
#define MBED_LOCALFILESYSTEM_H

#include "platform.h"

#if DEVICE_LOCALFILESYSTEM

#include "FileSystemLike.h"

namespace mbed {

FILEHANDLE local_file_open(const char* name, int flags);

class LocalFileHandle : public FileHandle {

public:
    LocalFileHandle(FILEHANDLE fh);

    virtual int close();

    virtual ssize_t write(const void *buffer, size_t length);

    virtual ssize_t read(void *buffer, size_t length);

    virtual int isatty();

    virtual off_t lseek(off_t position, int whence);

    virtual int fsync();

    virtual off_t flen();

protected:
    FILEHANDLE _fh;
    int pos;
};

/** A filesystem for accessing the local mbed Microcontroller USB disk drive
 *
 *  This allows programs to read and write files on the same disk drive that is used to program the
 *  mbed Microcontroller. Once created, the standard C file access functions are used to open,
 *  read and write files.
 *
 * Example:
 * @code
 * #include "mbed.h"
 *
 * LocalFileSystem local("local");               // Create the local filesystem under the name "local"
 *
 * int main() {
 *     FILE *fp = fopen("/local/out.txt", "w");  // Open "out.txt" on the local file system for writing
 *     fprintf(fp, "Hello World!");
 *     fclose(fp);
 *     remove("/local/out.txt");                 // Removes the file "out.txt" from the local file system
 *
 *     DIR *d = opendir("/local");               // Opens the root directory of the local file system
 *     struct dirent *p;
 *     while((p = readdir(d)) != NULL) {         // Print the names of the files in the local file system
 *       printf("%s\n", p->d_name);              // to stdout.
 *     }
 *     closedir(d);
 * }
 * @endcode
 *
 * @note
 *  If the microcontroller program makes an access to the local drive, it will be marked as "removed"
 *  on the Host computer. This means it is no longer accessible from the Host Computer.
 *
 *  The drive will only re-appear when the microcontroller program exists. Note that if the program does
 *  not exit, you will need to hold down reset on the mbed Microcontroller to be able to see the drive again!
 */
class LocalFileSystem : public FileSystemLike {

public:
    LocalFileSystem(const char* n) : FileSystemLike(n) {

    }

    virtual FileHandle *open(const char* name, int flags);
    virtual int remove(const char *filename);
    virtual DirHandle *opendir(const char *name);
};

} // namespace mbed

#endif

#endif
