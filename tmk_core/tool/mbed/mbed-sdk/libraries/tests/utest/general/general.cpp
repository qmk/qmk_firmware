#include "TestHarness.h"
#include <utility>
#include "mbed.h"

TEST_GROUP(Integer_Constant_Division)
{
    uint32_t test_64(uint64_t ticks) {
        ticks >>= 3; // divide by 8
        if (ticks > 0xFFFFFFFF) {
            ticks /= 3;
        } else {
            ticks = (ticks * 0x55555556) >> 32; // divide by 3
        }
        return (uint32_t)(0xFFFFFFFF & ticks);
    }
};

// 0xFFFFFFFF *  8 =  0x7fffffff8
TEST(Integer_Constant_Division, Divide_By_8)
{
    std::pair<uint32_t, uint64_t> values = std::make_pair(0x55555555, 0x7FFFFFFF8);
    uint32_t test_ret = test_64(values.second);
    CHECK_EQUAL(values.first, test_ret);
}

// 0xFFFFFFFF * 24 = 0x17ffffffe8
TEST(Integer_Constant_Division, Divide_By_24)
{
    std::pair<uint32_t, uint64_t> values = std::make_pair(0xFFFFFFFF, 0x17FFFFFFE8);
    uint32_t test_ret = test_64(values.second);
    CHECK_EQUAL(values.first, test_ret);
}

TEST_GROUP(RTC_Test)
{
    char buffer[32];
    const int CUSTOM_TIME = 1256729737;
};

TEST(RTC_Test, Check_Set_Time)
{
    set_time(CUSTOM_TIME);  // Set RTC time to Wed, 28 Oct 2009 11:35:37
    time_t seconds = time(NULL);
    strftime(buffer, 32, "%Y-%m-%d %H:%M:%S %p", localtime(&seconds));
    STRCMP_EQUAL(buffer, "2009-10-28 11:35:37 AM");
}

TEST_GROUP(C_String_Format)
{
    char buffer[256];
};

#define POSITIVE_INTEGERS 32768,3214,999,100,1,0,1,4231,999,4123,32760,99999
TEST(C_String_Format, Sprintf_Positive_Integers)
{
    sprintf(buffer, "%u %d %u %d %u %d %u %d %u %d %u %d", POSITIVE_INTEGERS);
    STRCMP_EQUAL(buffer, "32768 3214 999 100 1 0 1 4231 999 4123 32760 99999");
}

#define NEGATIVE_INTEGERS -32768,-3214,-999,-100,-1,0,-1,-4231,-999,-4123,-32760,-99999
TEST(C_String_Format, Sprintf_Negative_Integers)
{
    sprintf(buffer, "%i %d %i %d %i %d %i %d %i %d %i %i", NEGATIVE_INTEGERS);
    STRCMP_EQUAL(buffer, "-32768 -3214 -999 -100 -1 0 -1 -4231 -999 -4123 -32760 -99999");
}

#ifdef DEVICE_SEMIHOST
#include "semihost_api.h"

TEST_GROUP(Device_Semihost)
{
    char uid[48];
};

TEST(Device_Semihost, semihost_connected)
{
    CHECK(semihost_connected());
}

TEST(Device_Semihost, mbed_interface_connected)
{
    CHECK(mbed_interface_connected());
}

TEST(Device_Semihost, mbed_interface_uid)
{
    CHECK_EQUAL(mbed_interface_uid(uid), 0);
}

#endif
