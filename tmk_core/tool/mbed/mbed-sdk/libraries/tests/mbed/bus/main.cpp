#include "mbed.h"
#include "test_env.h"

BusOut bus1(D0, D1, D2, D3, D4, D5, D6, D7, D8, D9, D10, D11, D12, D13, D14, D15);
BusOut bus2(A5, A4, A3, A2, A1, A0);
int i;
 
int main()
{
    notify_start();
    
    for (i=0; i<=65535; i++) {
        bus1 = i;
        bus2 = i;
        wait(0.0001);
    }
    
    notify_completion(true);
}