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
#ifndef RPC_H
#define RPC_H

#include "mbed.h"
#include "Arguments.h"

namespace mbed {

#define RPC_MAX_STRING      128

struct rpc_function {
    const char *name;
    void (*function_caller)(Arguments*, Reply*);
};

struct rpc_class {
    const char *name;
    const rpc_function *static_functions;
    struct rpc_class *next;
};

/* Class RPC
 *  The RPC class for most things
 */
class RPC {

public:

    RPC(const char *name = NULL);

    virtual ~RPC();

    /* Function get_rpc_methods
     *  Returns a pointer to an array describing the rpc methods
     *  supported by this object, terminated by either
     *  RPC_METHOD_END or RPC_METHOD_SUPER(Superclass).
     *
     * Example
     * > class Example : public RPC {
     * >   int foo(int a, int b) { return a + b; }
     * >   virtual const struct rpc_method *get_rpc_methods() {
     * >     static const rpc_method rpc_methods[] = {
     * >       { "foo", generic_caller<int, Example, int, int, &Example::foo> },
     * >       RPC_METHOD_SUPER(RPC)
     * >     };
     * >     return rpc_methods;
     * >   }
     * > };
     */
    virtual const struct rpc_method *get_rpc_methods();

    static bool call(const char *buf, char *result);

    /* Function lookup
     *  Lookup and return the object that has the given name.
     *
     * Variables
     *  name - the name to lookup.
     */
    static RPC *lookup(const char *name);

protected:
    static RPC *_head;
    RPC *_next;
    char *_name;
    bool _from_construct;

private:
    static rpc_class *_classes;

    static const rpc_function _RPC_funcs[];
    static rpc_class _RPC_class;

    void delete_self();
    static void list_objs(Arguments *args, Reply *result);
    static void clear(Arguments *args, Reply *result);

public:
    /* Function add_rpc_class
     *  Add the class to the list of classes which can have static
     *  methods called via rpc (the static methods which can be called
     *  are defined by that class' get_rpc_class() static method).
     */
    template<class C>
    static void add_rpc_class() {
        rpc_class *c = C::get_rpc_class();
        c->next = _classes;
        _classes = c;
    }

    template<class C>
    static const char *construct() {
        RPC *p = new C();
        p->_from_construct = true;
        return p->_name;
    }

    template<class C, typename A1>
    static const char *construct(A1 arg1) {
        RPC *p = new C(arg1);
        p->_from_construct = true;
        return p->_name;
    }

    template<class C, typename A1, typename A2>
    static const char *construct(A1 arg1, A2 arg2) {
        RPC *p = new C(arg1, arg2);
        p->_from_construct = true;
        return p->_name;
    }

    template<class C, typename A1, typename A2, typename A3>
    static const char *construct(A1 arg1, A2 arg2, A3 arg3) {
        RPC *p = new C(arg1, arg2, arg3);
        p->_from_construct = true;
        return p->_name;
    }

    template<class C, typename A1, typename A2, typename A3, typename A4>
    static const char *construct(A1 arg1, A2 arg2, A3 arg3, A4 arg4) {
        RPC *p = new C(arg1, arg2, arg3, arg4);
        p->_from_construct = true;
        return p->_name;
    }
};

/* Macro MBED_OBJECT_NAME_MAX
 *  The maximum size of object name (including terminating null byte)
 *  that will be recognised when using fopen to open a FileLike
 *  object, or when using the rpc function.
 */
#define MBED_OBJECT_NAME_MAX 32

/* Macro MBED_METHOD_NAME_MAX
 *  The maximum size of rpc method name (including terminating null
 *  byte) that will be recognised by the rpc function (in rpc.h).
 */
#define MBED_METHOD_NAME_MAX 32

/* Function rpc_method_caller
 */
template<class T, void(T::*member)(const char *, char *)>
void rpc_method_caller(RPC *this_ptr, Arguments *arguments, Reply *result) {
    (static_cast<T*>(this_ptr)->*member)(arguments, result);
}

/* Function rpc_method_caller
 */
template<class T, void(T::*member)()>
void rpc_method_caller(RPC *this_ptr, Arguments *arguments, Reply *result) {
    (static_cast<T*>(this_ptr)->*member)();
}

/* Function rpc_method_caller
 */
template<class T, typename A1, void(T::*member)(A1)>
void rpc_method_caller(RPC *this_ptr, Arguments *arguments, Reply *result) {
    A1 arg1 = arguments->getArg<A1>();

    (static_cast<T*>(this_ptr)->*member)(arg1);
}

/* Function rpc_method_caller
 */
template<class T, typename A1, typename A2, void(T::*member)(A1, A2)>
void rpc_method_caller(RPC *this_ptr, Arguments *arguments, Reply *result) {
    A1 arg1 = arguments->getArg<A1>();
    A2 arg2 = arguments->getArg<A2>();

    (static_cast<T*>(this_ptr)->*member)(arg1, arg2);
}

/* Function rpc_method_caller
 */
template<class T, typename A1, typename A2, typename A3, void(T::*member)(A1, A2, A3)>
void rpc_method_caller(RPC *this_ptr, Arguments *arguments, Reply *result) {
    A1 arg1 = arguments->getArg<A1>();
    A2 arg2 = arguments->getArg<A2>();
    A3 arg3 = arguments->getArg<A3>();

    (static_cast<T*>(this_ptr)->*member)(arg1, arg2, arg3);
}

/* Function rpc_method_caller
 */
template<typename R, class T, R(T::*member)()>
void rpc_method_caller(RPC *this_ptr, Arguments *arguments, Reply *result) {
    R res = (static_cast<T*>(this_ptr)->*member)();
    result->putData<R>(res);
}

/* Function rpc_method_caller
 */
template<typename R, class T, typename A1, R(T::*member)(A1)>
void rpc_method_caller(RPC *this_ptr, Arguments *arguments, Reply *result) {
    A1 arg1 = arguments->getArg<A1>();

    R res = (static_cast<T*>(this_ptr)->*member)(arg1);
    result->putData<R>(res);
}

/* Function rpc_method_caller
 */
template<typename R, class T, typename A1, typename A2, R(T::*member)(A1, A2)>
void rpc_method_caller(RPC *this_ptr, Arguments *arguments, Reply *result) {
    A1 arg1 = arguments->getArg<A1>();
    A2 arg2 = arguments->getArg<A2>();

    R res = (static_cast<T*>(this_ptr)->*member)(arg1, arg2);
    result->putData<R>(res);
}

/* Function rpc_method_caller
 */
template<typename R, class T, typename A1, typename A2, typename A3, R(T::*member)(A1, A2, A3)>
void rpc_method_caller(RPC *this_ptr, Arguments *arguments, Reply *result) {
    A1 arg1 = arguments->getArg<A1>();
    A2 arg2 = arguments->getArg<A2>();
    A3 arg3 = arguments->getArg<A3>();

    R res = (static_cast<T*>(this_ptr)->*member)(arg1, arg2, arg3);
    result->putData<R>(res);
}

/* Function rpc_function caller
 */
template<typename R, R(*func)()>
void rpc_function_caller(Arguments *arguments, Reply *result) {
    R res = (*func)();
    result->putData<R>(res);
}

/* Function rpc_function caller
 */
template<typename R, typename A1, R(*func)(A1)>
void rpc_function_caller(Arguments *arguments, Reply *result) {
    A1 arg1 = arguments->getArg<A1>();
    R res = (*func)(arg1);
    result->putData<R>(res);
}

/* Function rpc_function caller
 */
template<typename R, typename A1, typename A2, R(*func)(A1, A2)>
void rpc_function_caller(Arguments *arguments, Reply *result) {
    A1 arg1 = arguments->getArg<A1>();
    A2 arg2 = arguments->getArg<A2>();

    R res = (*func)(arg1, arg2);
    result->putData<R>(res);
}

/* Function rpc_function caller
 */
template<typename R, typename A1, typename A2, typename A3, R(*func)(A1, A2, A3)>
void rpc_function_caller(Arguments *arguments, Reply *result) {
    A1 arg1 = arguments->getArg<A1>();
    A2 arg2 = arguments->getArg<A2>();
    A3 arg3 = arguments->getArg<A3>();

    R res = (*func)(arg1, arg2, arg3);
    result->putData<R>(res);
}

/* Function rpc_function caller
 */
template<typename R, typename A1, typename A2, typename A3, typename A4, R(*func)(A1, A2, A3, A4)>
void rpc_function_caller(Arguments *arguments, Reply *result) {
    A1 arg1 = arguments->getArg<A1>();
    A2 arg2 = arguments->getArg<A2>();
    A3 arg3 = arguments->getArg<A3>();
    A4 arg4 = arguments->getArg<A4>();

    R res = (*func)(arg1, arg2, arg3, arg4);
    result->putData<R>(res);
}

struct rpc_method {
    const char *name;
    typedef void (*method_caller_t)(RPC*, Arguments*, Reply*);
    typedef const struct rpc_method *(*super_t)(RPC*);
    union {
        method_caller_t method_caller;
        super_t super;
    };
};

template<class C>
const struct rpc_method *rpc_super(RPC *this_ptr) {
    return static_cast<C*>(this_ptr)->C::get_rpc_methods();
}

#define RPC_METHOD_END      { NULL, NULL }
#define RPC_METHOD_SUPER(C) { NULL, (rpc_method::method_caller_t)rpc_super<C> }

} // namespace mbed

#endif
