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
#ifndef RPCFUNCTION_RPC
#define RPCFUNCTION_RPC

#include "rpc.h"
#define STR_LEN 64

namespace mbed {

/**
 *
 *Class to call custom functions over RPC
 *
 */
class RPCFunction: public RPC {
public:
    /**
     * Constructor
     *
     *@param f Pointer to the function to call. the function must be of the form void foo(char * input, char * output)
     *@param name The name of this object
     */
    RPCFunction(void (*f)(Arguments*, Reply*), const char* = NULL);

    /**
     *run
     *
     *Calls the attached function passing the string in but doesn't return the result.
     *@param str The string to be passed into the attached function. This string can consist of any ASCII characters apart from escape codes. The usual limtations on argument content for RPC strings has been removed
     *@return A string output from the function
     */
    void run(Arguments* args, Reply* r);

    virtual const struct rpc_method *get_rpc_methods();

private:
    void (*_ftr)(Arguments*, Reply*);

    char _input[STR_LEN];
    char _output[STR_LEN];
};

}

#endif
