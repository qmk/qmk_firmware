#include "mbed.h"
#include "test_env.h"

void ticker_callback_1(void);
void ticker_callback_2(void);

DigitalOut led0(LED1);
DigitalOut led1(LED2);
Ticker ticker;

void print_char(char c = '*')
{
    printf("%c", c);
    fflush(stdout);
}

void ticker_callback_2(void)
{
    ticker.detach();
    ticker.attach(ticker_callback_1, 1.0);
    led1 = !led1;
    print_char();
}

void ticker_callback_1(void)
{
    ticker.detach();
    ticker.attach(ticker_callback_2, 1.0);
    led0 = !led0;
    print_char();
}

int main(void)
{
    MBED_HOSTTEST_TIMEOUT(15);
    MBED_HOSTTEST_SELECT(wait_us_auto);
    MBED_HOSTTEST_DESCRIPTION(Ticker Two callbacks);
    MBED_HOSTTEST_START("MBED_34");

    ticker.attach(ticker_callback_1, 1.0);

    while(1);
}
