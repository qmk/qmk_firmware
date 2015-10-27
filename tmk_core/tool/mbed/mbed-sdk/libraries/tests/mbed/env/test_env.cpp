#include "test_env.h"

// Const strings used in test_end
const char* TEST_ENV_START = "start";
const char* TEST_ENV_SUCCESS = "success";
const char* TEST_ENV_FAILURE = "failure";
const char* TEST_ENV_MEASURE = "measure";
const char* TEST_ENV_END = "end";


static void led_blink(PinName led, float delay)
{
    if (led != NC) {
        DigitalOut myled(led);
        while (1) {
            myled = !myled;
            wait(delay);
        }
    }
    while(1);
}

void notify_start()
{
    printf("{{%s}}" NL, TEST_ENV_START);
}

void notify_performance_coefficient(const char* measurement_name, const int value)
{
    printf("{{%s;%s;%d}}" RCNL, TEST_ENV_MEASURE, measurement_name, value);
}

void notify_performance_coefficient(const char* measurement_name, const unsigned int value)
{
    printf("{{%s;%s;%u}}" RCNL, TEST_ENV_MEASURE, measurement_name, value);
}

void notify_performance_coefficient(const char* measurement_name, const double value)
{
    printf("{{%s;%s;%f}}" RCNL, TEST_ENV_MEASURE, measurement_name, value);
}

void notify_completion(bool success)
{
    printf("{{%s}}" NL "{{%s}}" NL, success ? TEST_ENV_SUCCESS : TEST_ENV_FAILURE, TEST_ENV_END);
    led_blink(LED1, success ? 1.0 : 0.1);
}

bool notify_completion_str(bool success, char* buffer)
{
    bool result = false;
    if (buffer) {
        sprintf(buffer, "{{%s}}" NL "{{%s}}" NL, success ? TEST_ENV_SUCCESS : TEST_ENV_FAILURE, TEST_ENV_END);
        result = true;
    }
    return result;
}

// Host test auto-detection API
void notify_host_test_name(const char *host_test) {
    if (host_test) {
        printf("{{host_test_name;%s}}" NL, host_test);
    }
}

void notify_timeout(int timeout) {
    printf("{{timeout;%d}}" NL, timeout);
}

void notify_test_id(const char *test_id) {
    if (test_id) {
        printf("{{test_id;%s}}" NL, test_id);
    }
}

void notify_test_description(const char *description) {
    if (description) {
        printf("{{description;%s}}" NL, description);
    }
}


// -DMBED_BUILD_TIMESTAMP=1406208182.13
unsigned int testenv_randseed()
{
    unsigned int seed = 0;
#ifdef MBED_BUILD_TIMESTAMP
    long long_seed = static_cast<long>(MBED_BUILD_TIMESTAMP);
    seed = long_seed & 0xFFFFFFFF;
#endif /* MBED_BUILD_TIMESTAMP */
    return seed;
}
