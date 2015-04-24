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
#ifndef MBED_FUNCTIONPOINTER_H
#define MBED_FUNCTIONPOINTER_H

#include <string.h>

namespace mbed {

typedef void (*pvoidf_t)(void);

/** A class for storing and calling a pointer to a static or member void function
 */
class FunctionPointer {
public:

    /** Create a FunctionPointer, attaching a static function
     *
     *  @param function The void static function to attach (default is none)
     */
    FunctionPointer(void (*function)(void) = 0);

    /** Create a FunctionPointer, attaching a member function
     *
     *  @param object The object pointer to invoke the member function on (i.e. the this pointer)
     *  @param function The address of the void member function to attach
     */
    template<typename T>
    FunctionPointer(T *object, void (T::*member)(void)) {
        attach(object, member);
    }

    /** Attach a static function
     *
     *  @param function The void static function to attach (default is none)
     */
    void attach(void (*function)(void) = 0);

    /** Attach a member function
     *
     *  @param object The object pointer to invoke the member function on (i.e. the this pointer)
     *  @param function The address of the void member function to attach
     */
    template<typename T>
    void attach(T *object, void (T::*member)(void)) {
        _object = static_cast<void*>(object);
        memcpy(_member, (char*)&member, sizeof(member));
        _membercaller = &FunctionPointer::membercaller<T>;
        _function = 0;
    }

    /** Call the attached static or member function
     */
    void call();

    pvoidf_t get_function() const {
        return (pvoidf_t)_function;
    }

#ifdef MBED_OPERATORS
    void operator ()(void);
#endif

private:
    template<typename T>
    static void membercaller(void *object, char *member) {
        T* o = static_cast<T*>(object);
        void (T::*m)(void);
        memcpy((char*)&m, member, sizeof(m));
        (o->*m)();
    }

    void (*_function)(void);             // static function pointer - 0 if none attached
    void *_object;                       // object this pointer - 0 if none attached
    char _member[16];                    // raw member function pointer storage - converted back by registered _membercaller
    void (*_membercaller)(void*, char*); // registered membercaller function to convert back and call _member on _object
};

} // namespace mbed

#endif
