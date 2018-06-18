#include "d51_util.h"

//Print out up to 3 digit number through m15
void m15_print(uint8_t x)
{
    int8_t t;
    uint8_t n;
    uint8_t p, p2;

    if (x >= 100) t = 2;
    else if (x >= 10) t = 1;
    else t = 0;

    while (t >= 0)
    {
        p2 = t;
        p = 1;
        while (p2--) p *= 10;
        n = x / p;
        x -= n * p;
        while (n > 0)
        {
            m15_on;
            n--;
            m15_off;
        }
        //Will always end with an extra toggle
        m15_on;
        t--;
        m15_off;
    }
}
