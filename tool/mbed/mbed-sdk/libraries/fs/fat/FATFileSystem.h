/* mbed Microcontroller Library
 * Copyright (c) 2006-2012 ARM Limited
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef MBED_FATFILESYSTEM_H
#define MBED_FATFILESYSTEM_H

#include "FileSystemLike.h"
#include "FileHandle.h"
#include "ff.h"
#include <stdint.h>

using namespace mbed;

/**
 * FATFileSystem based on ChaN's Fat Filesystem library v0.8 
 */
class FATFileSystem : public FileSystemLike {
public:

    FATFileSystem(const char* n);
    virtual ~FATFileSystem();

    static FATFileSystem * _ffs[_VOLUMES];   // FATFileSystem objects, as parallel to FatFs drives array
    FATFS _fs;                               // Work area (file system object) for logical drive
    int _fsid;

    /**
     * Opens a file on the filesystem
     */
    virtual FileHandle *open(const char* name, int flags);
    
    /**
     * Removes a file path
     */
    virtual int remove(const char *filename);
    
    /**
     * Renames a file
     */
    virtual int rename(const char *oldname, const char *newname);
    
    /**
     * Formats a logical drive, FDISK artitioning rule, 512 bytes per cluster
     */
    virtual int format();
    
    /**
     * Opens a directory on the filesystem
     */
    virtual DirHandle *opendir(const char *name);
    
    /**
     * Creates a directory path
     */
    virtual int mkdir(const char *name, mode_t mode);
    
    /**
     * Mounts the filesystem
     */
    virtual int mount();
    
    /**
     * Unmounts the filesystem
     */
    virtual int unmount();

    virtual int disk_initialize() { return 0; }
    virtual int disk_status() { return 0; }
    virtual int disk_read(uint8_t * buffer, uint64_t sector, uint8_t count) = 0;
    virtual int disk_write(const uint8_t * buffer, uint64_t sector, uint8_t count) = 0;
    virtual int disk_sync() { return 0; }
    virtual uint64_t disk_sectors() = 0;

};

#endif
