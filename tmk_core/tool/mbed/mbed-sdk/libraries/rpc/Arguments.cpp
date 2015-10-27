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
#include "Arguments.h"
#include "pinmap.h"

using namespace std;

namespace mbed {

Arguments::Arguments(const char* rqs) {
    obj_name = NULL;
    method_name = NULL;
    argc = 0;

    // This copy can be removed if we can assume the request string is
    // persistent and writable for the duration of the call
    strcpy(request, rqs);

    // Initial '/'
    char* p = request;
    if (*p != '/') return;
    p++;

    // Object Name
    p = search_arg(&obj_name, p, '/');
    if (p == NULL) return;

    // Method Name
    p = search_arg(&method_name, p, ' ');
    if (p == NULL) return;

    // Arguments
    while (true) {
        argv[argc] = NULL;
        p = search_arg(&argv[argc], p, ' ');
        if (argv[argc] != NULL) argc++;
        if (p == NULL) break;
    }

    index = -1;
}

char* Arguments::search_arg(char **arg, char *p, char next_sep) {
    char *s = p;
    while (true) {
        if ((*p == '/') || (*p == ' ') || (*p == '\n') || (*p == '\0')) break;
        p++;
    }
    if (p == s) return NULL;
    *arg = s;
    char separator = *p;
    *p = '\0';
    p++;
    return (separator == next_sep) ? (p) : (NULL);
}

template<> PinName Arguments::getArg<PinName>(void) {
    index++;
    return parse_pins(argv[index]);
}

template<> int Arguments::getArg<int>(void) {
    index++;
    char *pEnd;
    return strtol(argv[index], &pEnd, 10);
}

template<> const char* Arguments::getArg<const char*>(void) {
    index++;
    return argv[index];
}

template<> char Arguments::getArg<char>(void) {
    index++;
    return *argv[index];
}

template<> double Arguments::getArg<double>(void) {
    index++;
    return atof(argv[index]);
}

template<> float Arguments::getArg<float>(void) {
    index++;
    return atof(argv[index]);
}

Reply::Reply(char* r) {
    first = true;
    *r = '\0';
    reply = r;
}

void Reply::separator(void) {
    if (first) {
        first = false;
    } else {
        *reply = ' '; reply++;
    }
}

template<> void Reply::putData<const char*>(const char* s) {
    separator();
    reply += sprintf(reply, "%s", s);
}

template<> void Reply::putData<char*>(char* s) {
    separator();
    reply += sprintf(reply, "%s", s);
}

template<> void Reply::putData<char>(char c) {
    separator();
    reply += sprintf(reply, "%c", c);
}

template<> void Reply::putData<int>(int v) {
    separator();
    reply += sprintf(reply, "%d", v);
}

template<> void Reply::putData<float>(float f) {
    separator();
    reply += sprintf(reply, "%.17g", f);
}

} // namespace mbed
