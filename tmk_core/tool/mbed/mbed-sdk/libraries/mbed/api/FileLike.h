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
#ifndef MBED_FILELIKE_H
#define MBED_FILELIKE_H

#include "FileBase.h"
#include "FileHandle.h"

namespace mbed {

/* Class FileLike
 *  A file-like object is one that can be opened with fopen by
 *  fopen("/name", mode). It is intersection of the classes Base and
 *  FileHandle.
 */
class FileLike : public FileHandle, public FileBase {

public:
    /* Constructor FileLike
     *
     * Variables
     *  name - The name to use to open the file.
     */
    FileLike(const char *name);

    virtual ~FileLike();
};

} // namespace mbed

#endif
