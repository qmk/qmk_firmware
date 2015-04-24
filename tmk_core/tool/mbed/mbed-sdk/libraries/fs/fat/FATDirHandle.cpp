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
#include <string.h>
#include "ff.h"
#include "FATDirHandle.h"

using namespace mbed;

FATDirHandle::FATDirHandle(const FATFS_DIR &the_dir) {
    dir = the_dir;
}

int FATDirHandle::closedir() {
    delete this;
    return 0;
}

struct dirent *FATDirHandle::readdir() {
    FILINFO finfo;

#if _USE_LFN
    finfo.lfname = cur_entry.d_name;
    finfo.lfsize = sizeof(cur_entry.d_name);
#endif // _USE_LFN

    FRESULT res = f_readdir(&dir, &finfo);

#if _USE_LFN
    if(res != 0 || finfo.fname[0]==0) {
        return NULL;
    } else {
        if(cur_entry.d_name[0]==0) {
            // No long filename so use short filename.
            memcpy(cur_entry.d_name, finfo.fname, sizeof(finfo.fname));
        }
        return &cur_entry;
    }
#else
    if(res != 0 || finfo.fname[0]==0) {
        return NULL;
    } else {
        memcpy(cur_entry.d_name, finfo.fname, sizeof(finfo.fname));
        return &cur_entry;
    }
#endif /* _USE_LFN */
}

void FATDirHandle::rewinddir() {
    dir.index = 0;
}

off_t FATDirHandle::telldir() {
    return dir.index;
}

void FATDirHandle::seekdir(off_t location) {
    dir.index = location;
}

