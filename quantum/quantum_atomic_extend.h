#ifdef DUMMY_ATOMIC_BLOCK
  // do nothing sample
  #define ATOMIC_BLOCK for ( uint8_t __ToDo = 1; __ToDo ; __ToDo = 0 )
  #define ATOMIC_BLOCK_RESTORESTATE ATOMIC_BLOCK
  #define ATOMIC_BLOCK_FORCEON      ATOMIC_BLOCK

/* AVR atomic part */
#elif defined(__AVR__)
  #include <util/atomic.h>

  #define ATOMIC_BLOCK_RESTORESTATE ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
  #define ATOMIC_BLOCK_FORCEON      ATOMIC_BLOCK(ATOMIC_FORCEON)

/* ChibiOS atomic part */
#elif defined(PROTOCOL_CHIBIOS)

static __inline__ uint8_t __chSysLock(void) {
    chSysLock(); /* interrupt disable */
    return 1;
}

static __inline__ void __chSysUnlock(const uint8_t *__s) {
    chSysUnlock(); /* interrupt enable */
    __asm__ volatile ("" ::: "memory");
    (void)__s;
}

  #define ATOMIC_BLOCK(type) for ( type, __ToDo = __chSysLock(); \
                                   __ToDo ; __ToDo = 0 )
  #define ATOMIC_FORCEON uint8_t sreg_save \
                         __attribute__((__cleanup__(__chSysUnlock))) = 0

  #define ATOMIC_BLOCK_RESTORESTATE _Static_assert(0, "ATOMIC_BLOCK_RESTORESTATE dose not implement")
  #define ATOMIC_BLOCK_FORCEON      ATOMIC_BLOCK(ATOMIC_FORCEON)

/* Other platform part */
#else

#error "ATOMIC_BLOCK_xxxx dose not implement"
#define ATOMIC_BLOCK_RESTORESTATE _Static_assert(0, "ATOMIC_BLOCK_RESTORESTATE dose not implement")
#define ATOMIC_BLOCK_FORCEON _Static_assert(0, "ATOMIC_BLOCK_FORCEON dose not implement")

#endif
