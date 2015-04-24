#include <utility>      // std::pair
#include "mbed.h"
#include "test_env.h"

uint32_t test_64(uint64_t ticks) {
    ticks >>= 3; // divide by 8
    if (ticks > 0xFFFFFFFF) {
        ticks /= 3;
    } else {
        ticks = (ticks * 0x55555556) >> 32; // divide by 3
    }
    return (uint32_t)(0xFFFFFFFF & ticks);
}

const char *result_str(bool result) {
    return result ? "[OK]" : "[FAIL]";
}

int main() {
    MBED_HOSTTEST_TIMEOUT(20);
    MBED_HOSTTEST_SELECT(default_auto);
    MBED_HOSTTEST_DESCRIPTION(Integer constant division);
    MBED_HOSTTEST_START("MBED_26");

    bool result = true;

    {   // 0xFFFFFFFF *  8 =  0x7fffffff8
        std::pair<uint32_t, uint64_t> values = std::make_pair(0x55555555, 0x7FFFFFFF8);
        uint32_t test_ret = test_64(values.second);
        bool test_res = values.first == test_ret;
        result = result && test_res;
        printf("64bit: 0x7FFFFFFF8: expected 0x%lX got 0x%lX ... %s\r\n", values.first, test_ret, result_str(test_res));
    }

    {   // 0xFFFFFFFF * 24 = 0x17ffffffe8
        std::pair<uint32_t, uint64_t> values = std::make_pair(0xFFFFFFFF, 0x17FFFFFFE8);
        uint32_t test_ret = test_64(values.second);
        bool test_res = values.first == test_ret;
        result = result && test_res;
        printf("64bit: 0x17FFFFFFE8: expected 0x%lX got 0x%lX ... %s\r\n", values.first, test_ret, result_str(test_res));
    }

    MBED_HOSTTEST_RESULT(result);
}
