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
#ifndef RPCVARIABLE_H_
#define RPCVARIABLE_H_

#include "rpc.h"

namespace mbed {

/**
 *Class to read and set an attached variable using the RPC
 *
 */
template<class T>
class RPCVariable: public RPC {
public:
    /**
     * Constructor
     *
     *@param ptr Pointer to the variable to make accessible over RPC. Any type of
     *variable can be connected
     *@param name The name of that this object will be over RPC
     */
    template<class A>
    RPCVariable(A * ptr, const char * name) : RPC(name) {
        _ptr = ptr;
    }
    /**
     *Read the variable over RPC.
     *
     *@return The value of the variable
     */
    T read() {
        return (*_ptr);
    }
    /**
     *Write a value to the variable over RPC
     *
     *@param The value to be written to the attached variable.
     */
    void write(T value) {
        *_ptr = value;
    }

    virtual const struct rpc_method *get_rpc_methods();
    static struct rpc_class *get_rpc_class();

private:
    T * _ptr;
};

template<class T>
const rpc_method *RPCVariable<T>::get_rpc_methods() {
    static const rpc_method rpc_methods[] = {
        {"read" , rpc_method_caller<T, RPCVariable, &RPCVariable::read> },
        {"write", rpc_method_caller<RPCVariable, T, &RPCVariable::write> },
        RPC_METHOD_SUPER(RPC)
    };
    return rpc_methods;
}

template<class T>
rpc_class *RPCVariable<T>::get_rpc_class() {
    static const rpc_function funcs[] = {
            "new", rpc_function_caller<const char*, T, const char*, &RPC::construct<RPCVariable, T, const char*> > ,
            RPC_METHOD_END
    };
    static rpc_class c = {"RPCVariable", funcs, NULL};
    return &c;
}

}

#endif  //RPCVARIABLE_H_
