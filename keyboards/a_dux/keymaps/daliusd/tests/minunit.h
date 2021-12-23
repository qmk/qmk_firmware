#define mu_assert(message, test) \
    do { \
        if (!(test)) { \
            return message; \
        } \
    } while (0)

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define NC "\033[0m"

enum ASSERT_TYPES {
    UINT,
    INT
};

#define BUFF_SIZE 1024
char buffer[BUFF_SIZE];

#define ASSERT_EQ(type, actual, expected) \
    do { \
        if (actual != expected) { \
            switch (type) { \
                case UINT: \
                    snprintf(buffer, BUFF_SIZE, "\nline %d\nvar %s\nactual = %u\nexpected = %u\n", __LINE__, #actual, actual, expected); \
                    break; \
                case INT: \
                    snprintf(buffer, BUFF_SIZE, "\nline %d\nvar %s\nactual = %d\nexpected = %d\n", __LINE__, #actual, actual, expected); \
                    break; \
                default: \
                    snprintf(buffer, BUFF_SIZE, "\nline %d\nunsupported ASSERT_EQ type\n", __LINE__); \
                    break; \
            } \
            printf("%s\n", buffer); \
            passed = false; \
            all_passed = false; \
        } \
    } while (0)

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

#define PROGMEM

#define TEST(name) \
    do { \
        printf("%s\n", name); \
        passed = true; \

#define END_TEST \
        if (passed) { \
            printf(GREEN"PASSED"NC"\n"); \
        } else { \
            printf(RED"FAILED"NC"\n"); \
        } \
    } while(0);

#define MAIN \
int main(int argc, char **argv) { \
    bool passed = true; \
    bool all_passed = true;

#define END \
    printf("\n"); \
    if (all_passed) { \
        printf(GREEN"ALL TESTS PASSED"NC"\n"); \
    } else { \
        printf(RED"TESTS FAILED"NC"\n"); \
    } \
    return 1 - all_passed; \
}
