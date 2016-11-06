#ifndef VARIABLE_TRACE_H
#define VARIABLE_TRACE_H

#include "print.h"

#ifdef NUM_TRACED_VARIABLES

#define ADD_TRACED_VARIABLE(name, addr, size) \
    add_traced_variable(PSTR(name), (void*)addr, size, PSTR(__FILE__), __LINE__)
#define REMOVE_TRACED_VARIABLE(name) remove_traced_variable(PSTR(name), PSTR(__FILE__), __LINE__)
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
