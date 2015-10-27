#include "mbed.h"
#include "test_env.h"

#define SIZE (10)
#define ADDR (0x90)

#if defined(TARGET_KL25Z)
I2CSlave slave(PTE0, PTE1);
#elif defined(TARGET_LPC4088)
I2CSlave slave(p9, p10);
#else
I2CSlave slave(p28, p27);
#endif

 int main() {
     char buf[SIZE];

     slave.address(ADDR);

     while (1) {
         int i = slave.receive();
         switch (i) {
             case I2CSlave::ReadAddressed:
                 slave.write(buf, SIZE);
				 for(int i = 0; i < SIZE; i++){
				}
                 break;
             case I2CSlave::WriteAddressed:
                 slave.read(buf, SIZE);
                 for(int i = 0; i < SIZE; i++){
					buf[i]++;
				}
                 break;
         }
     }
 }
