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
#include "RPCFunction.h"

namespace mbed {

//Custom rpc method caller for execute so that the string will not be delimited by anything
void rpc_method_caller_run(RPC *this_ptr, Arguments *arguments, Reply *result) {
    ((static_cast<RPCFunction*>(this_ptr))->run)(arguments, result);
}

RPCFunction::RPCFunction(void (*f)(Arguments*, Reply*), const char* name) : RPC(name) {
    _ftr = f;
}

//Just run the attached function using the string thats in private memory - or just using null values,
void RPCFunction::run(Arguments* args, Reply* r) {
    (*_ftr)(args, r);
}

const rpc_method *RPCFunction::get_rpc_methods() {
    static const rpc_method rpc_methods[] = {
        {"run", rpc_method_caller_run }, //Run using custom caller, all characters accepted in string
        RPC_METHOD_SUPER(RPC)
    };
    return rpc_methods;
}

}
