#include "d51_util.h"

//Display unsigned 32-bit number through m15
//Read as follows: 1230 = || ||| |||| |  (note always ending toggle)
void m15_print(uint32_t x)
{
    int8_t t;
    uint32_t n;
    uint32_t p, p2;

    if      (x < 10) t = 0;
    else if (x < 100) t = 1;
    else if (x < 1000) t = 2;
    else if (x < 10000) t = 3;
    else if (x < 100000) t = 4;
    else if (x < 1000000) t = 5;
    else if (x < 10000000) t = 6;
    else if (x < 100000000) t = 7;
    else if (x < 1000000000) t = 8;
    else t = 9;

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
