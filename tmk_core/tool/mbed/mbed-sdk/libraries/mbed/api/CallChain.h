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
#ifndef MBED_CALLCHAIN_H
#define MBED_CALLCHAIN_H

#include "FunctionPointer.h"
#include <string.h>

namespace mbed {

/** Group one or more functions in an instance of a CallChain, then call them in
 * sequence using CallChain::call(). Used mostly by the interrupt chaining code,
 * but can be used for other purposes.
 *
 * Example:
 * @code
 * #include "mbed.h"
 *
 * CallChain chain;
 *
 * void first(void) {
 *     printf("'first' function.\n");
 * }
 *
 * void second(void) {
 *     printf("'second' function.\n");
 * }
 *
 * class Test {
 * public:
 *     void f(void) {
 *         printf("A::f (class member).\n");
 *     }
 * };
 *
 * int main() {
 *     Test test;
 *
 *     chain.add(second);
 *     chain.add_front(first);
 *     chain.add(&test, &Test::f);
 *     chain.call();
 * }
 * @endcode
 */

typedef FunctionPointer* pFunctionPointer_t;

class CallChain {
public:
    /** Create an empty chain
     *
     *  @param size (optional) Initial size of the chain
     */
    CallChain(int size = 4);
    virtual ~CallChain();

    /** Add a function at the end of the chain
     *
     *  @param function A pointer to a void function
     *
     *  @returns
     *  The function object created for 'function'
     */
    pFunctionPointer_t add(void (*function)(void));

    /** Add a function at the end of the chain
     *
     *  @param tptr pointer to the object to call the member function on
     *  @param mptr pointer to the member function to be called
     *
     *  @returns
     *  The function object created for 'tptr' and 'mptr'
     */
    template<typename T>
    pFunctionPointer_t add(T *tptr, void (T::*mptr)(void)) {
        return common_add(new FunctionPointer(tptr, mptr));
    }

    /** Add a function at the beginning of the chain
     *
     *  @param function A pointer to a void function
     *
     *  @returns
     *  The function object created for 'function'
     */
    pFunctionPointer_t add_front(void (*function)(void));

    /** Add a function at the beginning of the chain
     *
     *  @param tptr pointer to the object to call the member function on
     *  @param mptr pointer to the member function to be called
     *
     *  @returns
     *  The function object created for 'tptr' and 'mptr'
     */
    template<typename T>
    pFunctionPointer_t add_front(T *tptr, void (T::*mptr)(void)) {
        return common_add_front(new FunctionPointer(tptr, mptr));
    }

    /** Get the number of functions in the chain
     */
    int size() const;

    /** Get a function object from the chain
     *
     *  @param i function object index
     *
     *  @returns
     *  The function object at position 'i' in the chain
     */
    pFunctionPointer_t get(int i) const;

    /** Look for a function object in the call chain
     *
     *  @param f the function object to search
     *
     *  @returns
     *  The index of the function object if found, -1 otherwise.
     */
    int find(pFunctionPointer_t f) const;

    /** Clear the call chain (remove all functions in the chain).
     */
    void clear();

    /** Remove a function object from the chain
     *
     *  @arg f the function object to remove
     *
     *  @returns
     *  true if the function object was found and removed, false otherwise.
     */
    bool remove(pFunctionPointer_t f);

    /** Call all the functions in the chain in sequence
     */
    void call();

#ifdef MBED_OPERATORS
    void operator ()(void) {
        call();
    }
    pFunctionPointer_t operator [](int i) const {
        return get(i);
    }
#endif

private:
    void _check_size();
    pFunctionPointer_t common_add(pFunctionPointer_t pf);
    pFunctionPointer_t common_add_front(pFunctionPointer_t pf);

    pFunctionPointer_t* _chain;
    int _size;
    int _elements;

    /* disallow copy constructor and assignment operators */
private:
    CallChain(const CallChain&);
    CallChain & operator = (const CallChain&);
};

} // namespace mbed

#endif

