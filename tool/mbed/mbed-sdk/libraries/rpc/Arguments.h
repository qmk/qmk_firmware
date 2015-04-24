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
#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include "platform.h"
#include "parse_pins.h"

namespace mbed {

#define RPC_MAX_STRING  128
#define RPC_MAX_ARGS     16

class Arguments {
public:
    Arguments(const char* rqs);

    template<typename Arg>
    Arg   getArg(void);

    char *obj_name;
    char *method_name;

    int   argc;
    char* argv[RPC_MAX_ARGS];

private:
    // This copy can be removed if we can assume the request string is
    // persistent and writable for the duration of the call
    char  request[RPC_MAX_STRING];
    int index;
    char* search_arg(char **arg, char *p, char next_sep);
};

class Reply {
public:
    Reply(char* r);

    template<typename Data>
    void putData(Data d);

private:
    void separator(void);
    bool first;
    char* reply;
};


} // Namespace mbed

#endif
