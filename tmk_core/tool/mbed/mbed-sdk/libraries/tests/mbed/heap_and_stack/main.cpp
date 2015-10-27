#include "test_env.h"

static char *initial_stack_p;
static char *initial_heap_p;

static char line[256];
static unsigned int iterations = 0;

void report_iterations(void) {
    unsigned int tot = (0x100 * iterations)*2;
    printf("\nAllocated (%d)Kb in (%u) iterations\n", tot/1024, iterations);
#if !defined(TOOLCHAIN_GCC_CR)
    // EA: This causes a crash when compiling with GCC_CR???
    printf("%.2f\n", ((float)(tot)/(float)(initial_stack_p - initial_heap_p))*100.);
#endif
#ifdef TOOLCHAIN_ARM
#ifndef __MICROLIB
    __heapvalid((__heapprt) fprintf, stdout, 1);
#endif
#endif
}

void stack_test(char *latest_heap_pointer) {
    char stack_line[256];
    iterations++;

    sprintf(stack_line, "\nstack pointer: %p", &stack_line[255]);
    puts(stack_line);

    char *heap_pointer = (char*)malloc(0x100);

    if (heap_pointer == NULL) {
        int diff = (&stack_line[255] - latest_heap_pointer);
        if (diff > 0x200) {
            sprintf(stack_line, "\n[WARNING] Malloc failed to allocate memory too soon. There are (0x%x) free bytes", diff);
            report_iterations();
            puts(stack_line);
        } else {
            puts("\n[SUCCESS] Stack/Heap collision detected");
            report_iterations();
        }
        return;
    } else {
        heap_pointer += 0x100;
        sprintf(line, "heap pointer: %p", heap_pointer);
        puts(line);
    }

    if ((&stack_line[255]) > heap_pointer) {
        stack_test(heap_pointer);
    } else {
        puts("\n[WARNING] The Stack/Heap collision was not detected");
        report_iterations();
    }
}


int main (void) {
    char c;
    initial_stack_p = &c;

    initial_heap_p = (char*)malloc(1);
    if (initial_heap_p == NULL) {
        printf("Unable to malloc a single byte\n");
        notify_completion(false);
    }

    printf("Initial stack/heap geometry:\n");
    printf("   stack pointer:V %p\n", initial_stack_p);
    printf("   heap pointer :^ %p\n", initial_heap_p);

    initial_heap_p++;
    stack_test(initial_heap_p);

    notify_completion(true);
}
