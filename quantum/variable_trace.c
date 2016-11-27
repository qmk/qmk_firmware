#include "variable_trace.h"
#include <stddef.h>
#include <string.h>

#ifdef NO_PRINT
#error "You need undef NO_PRINT to use the variable trace feature"
#endif

#ifndef CONSOLE_ENABLE
#error "The console needs to be enabled in the makefile to use the variable trace feature"
#endif


#define NUM_TRACED_VARIABLES 1
#ifndef MAX_VARIABLE_TRACE_SIZE
    #define MAX_VARIABLE_TRACE_SIZE 4
#endif

typedef struct {
    const char* name;
    void* addr;
    unsigned size;
    const char* func;
    int line;
    uint8_t last_value[MAX_VARIABLE_TRACE_SIZE];

} traced_variable_t;

static traced_variable_t traced_variables[NUM_TRACED_VARIABLES];

void add_traced_variable(const char* name, void* addr, unsigned size, const char* func, int line) {
    verify_traced_variables(func, line);
    if (size > MAX_VARIABLE_TRACE_SIZE) {
#if defined(__AVR__)
       xprintf("Traced variable \"%S\" exceeds the maximum size %d\n", name, size);
#else
       xprintf("Traced variable \"%s\" exceeds the maximum size %d\n", name, size);
#endif
       size = MAX_VARIABLE_TRACE_SIZE;
    }
    int index = -1;
    for (int i = 0; i < NUM_TRACED_VARIABLES; i++) {
        if (index == -1 && traced_variables[i].addr == NULL){
            index = i;
        }
        else if (strcmp_P(name, traced_variables[i].name)==0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        xprintf("You can only trace %d variables at the same time\n", NUM_TRACED_VARIABLES);
        return;
    }

    traced_variable_t* t = &traced_variables[index];
    t->name = name;
    t->addr = addr;
    t->size = size;
    t->func = func;
    t->line = line;
    memcpy(&t->last_value[0], addr, size);

}

void remove_traced_variable(const char* name, const char* func, int line) {
    verify_traced_variables(func, line);
    for (int i = 0; i < NUM_TRACED_VARIABLES; i++) {
        if (strcmp_P(name, traced_variables[i].name)==0) {
            traced_variables[i].name = 0;
            traced_variables[i].addr = NULL;
            break;
        }
    }
}

void verify_traced_variables(const char* func, int line) {
    for (int i = 0; i < NUM_TRACED_VARIABLES; i++) {
        traced_variable_t* t = &traced_variables[i];
        if (t->addr != NULL && t->name != NULL) {
            if (memcmp(t->last_value, t->addr, t->size)!=0){
#if defined(__AVR__)
               xprintf("Traced variable \"%S\" has been modified\n", t->name);
               xprintf("Between %S:%d\n", t->func, t->line);
               xprintf("And %S:%d\n", func, line);

#else
               xprintf("Traced variable \"%s\" has been modified\n", t->name);
               xprintf("Between %s:%d\n", t->func, t->line);
               xprintf("And %s:%d\n", func, line);
#endif
               xprintf("Previous value ");
               for (int j=0; j<t->size;j++) {
                   print_hex8(t->last_value[j]);
               }
               xprintf("\nNew value ");
               uint8_t* addr = (uint8_t*)(t->addr);
               for (int j=0; j<t->size;j++) {
                   print_hex8(addr[j]);
               }
               xprintf("\n");
               memcpy(t->last_value, addr, t->size);
           }
        }

        t->func = func;
        t->line = line;
    }
}
