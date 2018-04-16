/* Copyright 2016 Fred Sundvik
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef VARIABLE_TRACE_H
#define VARIABLE_TRACE_H

// For more information about the variable tracing see the readme.

#include "print.h"

#ifdef NUM_TRACED_VARIABLES

// Start tracing a variable at the memory address addr
// The name can be anything and is used only for reporting
// The size should usually be the same size as the variable you are interested in
#define ADD_TRACED_VARIABLE(name, addr, size) \
    add_traced_variable(PSTR(name), (void*)addr, size, PSTR(__FILE__), __LINE__)

// Stop tracing the variable with the given name
#define REMOVE_TRACED_VARIABLE(name) remove_traced_variable(PSTR(name), PSTR(__FILE__), __LINE__)

// Call to get messages when the variable has been changed
#define VERIFY_TRACED_VARIABLES() verify_traced_variables(PSTR(__FILE__), __LINE__)

#else

#define ADD_TRACED_VARIABLE(name, addr, size)
#define REMOVE_TRACED_VARIABLE(name)
#define VERIFY_TRACED_VARIABLES()

#endif

// Don't call directly, use the macros instead
void add_traced_variable(const char* name, void* addr, unsigned size, const char* func, int line);
void remove_traced_variable(const char* name, const char* func, int line);
void verify_traced_variables(const char* func, int line);
#endif
