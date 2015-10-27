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
#ifndef MBED_STREAM_H
#define MBED_STREAM_H

#include "platform.h"
#include "FileLike.h"

namespace mbed {

extern void mbed_set_unbuffered_stream(FILE *_file);
extern int mbed_getc(FILE *_file);
extern char* mbed_gets(char *s, int size, FILE *_file);

class Stream : public FileLike {

public:
    Stream(const char *name=NULL);
    virtual ~Stream();

    int putc(int c);
    int puts(const char *s);
    int getc();
    char *gets(char *s, int size);
    int printf(const char* format, ...);
    int scanf(const char* format, ...);

    operator std::FILE*() {return _file;}

protected:
    virtual int close();
    virtual ssize_t write(const void* buffer, size_t length);
    virtual ssize_t read(void* buffer, size_t length);
    virtual off_t lseek(off_t offset, int whence);
    virtual int isatty();
    virtual int fsync();
    virtual off_t flen();

    virtual int _putc(int c) = 0;
    virtual int _getc() = 0;

    std::FILE *_file;

    /* disallow copy constructor and assignment operators */
private:
    Stream(const Stream&);
    Stream & operator = (const Stream&);
};

} // namespace mbed

#endif
