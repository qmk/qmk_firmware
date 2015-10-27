#include "mbed.h"
#include "InterruptManager.h"
#include "cmsis.h"
#include "test_env.h"

#if defined(TARGET_LPC1768) || defined(TARGET_LPC4088)
#define TIMER_IRQ       TIMER3_IRQn
#elif defined(TARGET_LPC11U24) || defined(TARGET_LPC1114)
#define TIMER_IRQ       TIMER_32_1_IRQn
#elif defined(TARGET_KL25Z)
#define TIMER_IRQ       LPTimer_IRQn
#elif defined(TARGET_LPC2368)
#define TIMER_IRQ       TIMER3_IRQn
#else
#error This test can't run on this target.
#endif

Serial pc(USBTX, USBRX);

Ticker flipper_1;
DigitalOut led1(LED1);
int led1_state = 0;
void flip_1() {
    if (led1_state) {
        led1 = 0; led1_state = 0;
    } else {
        led1 = 1; led1_state = 1;
    }
}

class Sender {
public:
    Sender(Serial&s, char c): _s(s), _c(c) {}
    void send() { _s.putc(_c); }
private:
    Serial& _s;
    char _c;
};
Ticker flipper_2;
Sender s1(pc, '1');
Sender s2(pc, '2');

#if defined(TARGET_LPC1768) || defined(TARGET_LPC11U24) || defined(TARGET_LPC4088) || defined(TARGET_LPC2368) || defined(TARGET_LPC1114)
#   define LED_NAME LED2
#elif defined(TARGET_KL05Z)
#   define LED_NAME LED2
#else
#   define LED_NAME PTE31
#endif

DigitalOut led2(LED_NAME);
int led2_state = 0;
void flip_2() {
    if (led2_state) {
        led2 = 0; led2_state = 0;
    } else {
        led2 = 1; led2_state = 1;
    }
}

void testme(void) {
    pc.putc('!');
}

class Counter {
public:
    void inc(void) {
        count ++;
    }
    int get_count(void) const {
        return count;
    }
private:
    static int count;
};

int Counter::count = 0;

int main() {
    led1 = 0;
    led2 = 0;
    uint32_t initial_handler, final_handler;
    Counter c;

    // Test chaining inside Serial class
    flipper_1.attach(&flip_1, 1.0); // the address of the function to be attached (flip) and the interval (1 second)
    flipper_2.attach(&flip_2, 2.0); // the address of the function to be attached (flip) and the interval (2 seconds)

    // Test global chaining (InterruptManager)
    printf("Handler initially: %08X\n", initial_handler = NVIC_GetVector(TIMER_IRQ));
    InterruptManager *pManager = InterruptManager::get();
    pFunctionPointer_t ptm = pManager->add_handler(testme, TIMER_IRQ);
    pFunctionPointer_t pinc = pManager->add_handler_front(&c, &Counter::inc, TIMER_IRQ);
    printf("Handler after calling InterruptManager: %08X\n", NVIC_GetVector(TIMER_IRQ));

    wait(4.0);

    if (!pManager->remove_handler(ptm, TIMER_IRQ) || !pManager->remove_handler(pinc, TIMER_IRQ)) {
        printf ("remove handler failed.\n");
        notify_completion(false);
    }
    printf("Interrupt handler calls: %d\n", c.get_count());
    printf("Handler after removing previously added functions: %08X\n", final_handler = NVIC_GetVector(TIMER_IRQ));

    if (initial_handler != final_handler) {
        printf( "InteruptManager test failed.\n");
        notify_completion(false);
    }

    while(1);
}
