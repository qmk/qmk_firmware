#include "mbed.h"
#include "test_env.h"
#include <stdio.h>

#define ADDR (0xA0)
#define FREQ 100000

// ********************************************************
// This tests data transfer between two I2C interfaces on
// the same chip, one configured as master, the other as
// slave. Works on the LPC1768 mbed.
//
// Wiring:
//   p28 <-> p9
//   p27 <-> p10
//   pull-up resistors on both lines
// ********************************************************

I2CSlave slave(p9, p10);
I2C master(p28, p27);

int main()
{
    char sent = 'T', received;

    master.frequency(FREQ);
    slave.frequency(FREQ);
    slave.address(ADDR);

    // First transfer: master to slave
    master.start();
    master.write(ADDR);
    master.write(sent);
    if(slave.receive() != I2CSlave::WriteAddressed)
    {
        notify_completion(false);
        return 1;
    }
    slave.read(&received, 1);
    if(sent != received)
    {
        notify_completion(false);
        return 1;
    }
    master.stop();

    // Second transfer: slave to master
    master.start();
    master.write(ADDR | 1);
    if(slave.receive() != I2CSlave::ReadAddressed)
    {
        notify_completion(false);
        return 1;
    }
    slave.write(received);
    received = master.read(0);
    slave.stop();
    notify_completion(received == sent);
}

