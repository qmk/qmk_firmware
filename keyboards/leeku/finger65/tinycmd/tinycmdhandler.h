#ifndef TINYCMDHANDLER_H
#define TINYCMDHANDLER_H

#include "tinycmdpkt.h"

typedef uint8_t (*tinycmd_handler_func)(tinycmd_pkt_req_type *);

typedef struct {
    uint8_t cmd;
    tinycmd_handler_func p_func;
}tinycmd_handler_array_type;

#endif // TINYCMDHANDLER_H

