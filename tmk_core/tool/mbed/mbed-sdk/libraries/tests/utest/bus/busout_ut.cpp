#include "TestHarness.h"
#include <utility>
#include "mbed.h"

TEST_GROUP(BusOut_mask)
{
};

TEST(BusOut_mask, led_1_2_3)
{
    BusOut bus_data(LED1, LED2, LED3);
    CHECK_EQUAL(0x07, bus_data.mask());
}

TEST(BusOut_mask, led_nc_nc_nc_nc)
{
    BusOut bus_data(NC, NC, NC, NC);
    CHECK_EQUAL(0x00, bus_data.mask());
}

TEST(BusOut_mask, led_1_2_3_nc_nc)
{
    BusOut bus_data(LED1, LED2, LED3, NC, NC);
    CHECK_EQUAL(0x07, bus_data.mask());
}

TEST(BusOut_mask, led_1_nc_2_nc_nc_3)
{
    BusOut bus_data(LED1, NC, LED2, NC, NC, LED3);
    CHECK_EQUAL(0x25, bus_data.mask());
}

///////////////////////////////////////////////////////////////////////////////

TEST_GROUP(BusOut_dummy)
{
};

TEST(BusOut_dummy, dummy)
{
}

#ifdef MBED_OPERATORS
TEST_GROUP(BusOut_digitalout_write)
{
};

TEST(BusOut_digitalout_write, led_nc)
{
    BusOut bus_data(NC);
    CHECK_EQUAL(false, bus_data[0].is_connected())
}


TEST(BusOut_digitalout_write, led_1_2_3)
{
    BusOut bus_data(LED1, LED2, LED3);
    bus_data[0].write(1);
    bus_data[1].write(1);
    bus_data[2].write(1);
    CHECK(bus_data[0].read());
    CHECK(bus_data[1].read());
    CHECK(bus_data[2].read());
}

TEST(BusOut_digitalout_write, led_1_2_3_nc_nc)
{
    BusOut bus_data(LED1, LED2, LED3, NC, NC);
    bus_data[0].write(0);
    bus_data[1].write(0);
    bus_data[2].write(0);
    CHECK(bus_data[0].read() == 0);
    CHECK(bus_data[1].read() == 0);
    CHECK(bus_data[2].read() == 0);
}

TEST(BusOut_digitalout_write, led_1_nc_2_nc_nc_3)
{
    BusOut bus_data(LED1, NC, LED2, NC, NC, LED3);
    bus_data[0].write(1);
    bus_data[2].write(0);
    bus_data[5].write(0);
    CHECK(bus_data[0].read());
    CHECK(bus_data[2].read() == 0);
    CHECK(bus_data[5].read() == 0);
}
#endif
