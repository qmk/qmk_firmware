#include "mbed.h"

Ticker tick;
DigitalOut led(LED1);

namespace {
    const int MS_INTERVALS = 1000;
}

class TickerHandler {
public:
    TickerHandler(const int _ms_intervals) : m_ticker_count(0), m_ms_intervals(_ms_intervals) {
    }

    void print_char(char c = '*')
    {
        printf("%c", c);
        fflush(stdout);
    }

    void togglePin(void)
    {
        if (ticker_count >= MS_INTERVALS) {
            print_char();
            ticker_count = 0;
            led = !led; // Blink
        }
        ticker_count++;
    }

protected:
    int m_ticker_count;
};

int main()
{
    TickerHandler th;

    tick.attach_us(th, TickerHandler::togglePin, 1000);
    while (1);
}
