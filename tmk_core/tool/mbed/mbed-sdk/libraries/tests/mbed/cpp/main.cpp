#include "test_env.h"

#define PATTERN_CHECK_VALUE  0xF0F0ADAD

class Test {

private:
    const char* name;
    const int pattern;

public:
    Test(const char* _name) : name(_name), pattern(PATTERN_CHECK_VALUE)  {
        print("init");
    }

    void print(const char *message) {
        printf("%s::%s\n", name, message);
    }

    bool check_init(void) {
        bool result = (pattern == PATTERN_CHECK_VALUE);
        print(result ? "check_init: OK" : "check_init: ERROR");
        return result;
    }

    void stack_test(void) {
        print("stack_test");
        Test t("Stack");
        t.hello();
    }

    void hello(void) {
        print("hello");
    }

    ~Test() {
        print("destroy");
    }
};

/* Check C++ startup initialisation */
Test s("Static");

/* EXPECTED OUTPUT:
*******************
Static::init
Static::stack_test
Stack::init
Stack::hello
Stack::destroy
Static::check_init: OK
Heap::init
Heap::hello
Heap::destroy
*******************/
int main (void) {
    MBED_HOSTTEST_TIMEOUT(10);
    MBED_HOSTTEST_SELECT(default_auto);
    MBED_HOSTTEST_DESCRIPTION(C++);
    MBED_HOSTTEST_START("MBED_12");

    bool result = true;
    for (;;)
    {
        // Global stack object simple test
        s.stack_test();
        if (s.check_init() == false)
        {
            result = false;
            break;
        }

        // Heap test object simple test
        Test *m = new Test("Heap");
        m->hello();

        if (m->check_init() == false)
        {
            result = false;
        }
        delete m;
        break;
    }

    MBED_HOSTTEST_RESULT(result);
}
