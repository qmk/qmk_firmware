#ifndef RING_BUFFER_H
#define RING_BUFFER_H
/*--------------------------------------------------------------------
 * Ring buffer to store scan codes from keyboard
 *------------------------------------------------------------------*/
#define RBUF_SIZE 32
static uint8_t rbuf[RBUF_SIZE];
static uint8_t rbuf_head = 0;
static uint8_t rbuf_tail = 0;
static inline void rbuf_enqueue(uint8_t data)
{
    uint8_t sreg = SREG;
    cli();
    uint8_t next = (rbuf_head + 1) % RBUF_SIZE;
    if (next != rbuf_tail) {
        rbuf[rbuf_head] = data;
        rbuf_head = next;
    } else {
        print("rbuf: full\n");
    }
    SREG = sreg;
}
static inline uint8_t rbuf_dequeue(void)
{
    uint8_t val = 0;

    uint8_t sreg = SREG;
    cli();
    if (rbuf_head != rbuf_tail) {
        val = rbuf[rbuf_tail];
        rbuf_tail = (rbuf_tail + 1) % RBUF_SIZE;
    }
    SREG = sreg;

    return val;
}
static inline bool rbuf_has_data(void)
{
    uint8_t sreg = SREG;
    cli();
    bool has_data = (rbuf_head != rbuf_tail);
    SREG = sreg;
    return has_data;
}
static inline void rbuf_clear(void)
{
    uint8_t sreg = SREG;
    cli();
    rbuf_head = rbuf_tail = 0;
    SREG = sreg;
}

#endif  /* RING_BUFFER_H */
