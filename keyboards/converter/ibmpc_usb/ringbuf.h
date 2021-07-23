#ifndef RINGBUF_H
#define RINGBUF_H

#include <stdint.h>
#include <stdbool.h>

// NOTE: buffer size must be 2^n and up to 255. size_mask should be 2^n - 1 due to using &(AND) instead of %(modulo)
typedef struct {
    uint8_t *buffer;
    uint8_t head;
    uint8_t tail;
    uint8_t size_mask;
} ringbuf_t;

static inline void ringbuf_init(ringbuf_t *buf, uint8_t *array, uint8_t size);
static inline int16_t ringbuf_get(ringbuf_t *buf);
static inline bool ringbuf_put(ringbuf_t *buf, uint8_t data);
static inline void ringbuf_write(ringbuf_t *buf, uint8_t data);
static inline bool ringbuf_is_empty(ringbuf_t *buf);
static inline bool ringbuf_is_full(ringbuf_t *buf);
static inline void ringbuf_reset(ringbuf_t *buf);
static inline void ringbuf_push(ringbuf_t *buf, uint8_t data);

static inline void ringbuf_init(ringbuf_t *buf, uint8_t *array, uint8_t size)
{
    buf->buffer = array;
    buf->head = 0;
    buf->tail = 0;
    buf->size_mask = size - 1;
}
static inline int16_t ringbuf_get(ringbuf_t *buf)
{
    if (ringbuf_is_empty(buf)) return -1;
    uint8_t data = buf->buffer[buf->tail];
    buf->tail++;
    buf->tail &= buf->size_mask;
    return  data;
}
static inline bool ringbuf_put(ringbuf_t *buf, uint8_t data)
{
    if (ringbuf_is_full(buf)) {
        return false;
    }
    buf->buffer[buf->head] = data;
    buf->head++;
    buf->head &= buf->size_mask;
    return true;
}
// this overrides data in buffer when it is full
static inline void ringbuf_write(ringbuf_t *buf, uint8_t data)
{
    buf->buffer[buf->head] = data;
    buf->head++;
    buf->head &= buf->size_mask;
    // eat tail: override data yet to be consumed
    if (buf->head == buf->tail) {
        buf->tail++;
        buf->tail &= buf->size_mask;
    }
}
static inline bool ringbuf_is_empty(ringbuf_t *buf)
{
    return (buf->head == buf->tail);
}
static inline bool ringbuf_is_full(ringbuf_t *buf)
{
    return (((buf->head + 1) & buf->size_mask) == buf->tail);
}
static inline void ringbuf_reset(ringbuf_t *buf)
{
    buf->head = 0;
    buf->tail = 0;
}
static inline void ringbuf_push(ringbuf_t *buf, uint8_t data)
{
    buf->buffer[buf->head] = data;
    buf->head++;
    buf->head &= buf->size_mask;
}
#endif
