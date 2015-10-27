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
#include "FilePath.h"

namespace mbed {

FilePath::FilePath(const char* file_path) : file_name(NULL), fb(NULL) {
    if ((file_path[0] != '/') || (file_path[1] == 0)) return;

    const char* file_system = &file_path[1];
    file_name = file_system;
    int len = 0;
    while (true) {
        char c = *file_name;
        if (c == '/') { // end of object name
            file_name++; // point to one char after the '/'
            break;
        }
        if (c == 0) { // end of object name, with no filename
            break;
        }
        len++;
        file_name++;
    }

    fb = FileBase::lookup(file_system, len);
}

const char* FilePath::fileName(void) {
    return file_name;
}

bool FilePath::isFileSystem(void) {
    if (NULL == fb)
        return false;
    return (fb->getPathType() == FileSystemPathType);
}

FileSystemLike* FilePath::fileSystem(void) {
    if (isFileSystem()) {
        return (FileSystemLike*)fb;
    }
    return NULL;
}

bool FilePath::isFile(void) {
    if (NULL == fb)
        return false;
    return (fb->getPathType() == FilePathType);
}

FileLike* FilePath::file(void) {
    if (isFile()) {
        return (FileLike*)fb;
    }
    return NULL;
}

bool FilePath::exists(void) {
    return fb != NULL;
}

} // namespace mbed
