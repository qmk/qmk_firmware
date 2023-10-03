/* Copyright 2021 Nick Brassel (@tzarc)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "qp_internal.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Stream API

typedef struct qp_stream_t qp_stream_t;

#define qp_stream_get(stream_ptr) (((qp_stream_t *)(stream_ptr))->get((qp_stream_t *)(stream_ptr)))
#define qp_stream_put(stream_ptr, c) (((qp_stream_t *)(stream_ptr))->put((qp_stream_t *)(stream_ptr), (c)))
#define qp_stream_seek(stream_ptr, offset, origin) (((qp_stream_t *)(stream_ptr))->seek((qp_stream_t *)(stream_ptr), (offset), (origin)))
#define qp_stream_tell(stream_ptr) (((qp_stream_t *)(stream_ptr))->tell((qp_stream_t *)(stream_ptr)))
#define qp_stream_eof(stream_ptr) (((qp_stream_t *)(stream_ptr))->is_eof((qp_stream_t *)(stream_ptr)))
#define qp_stream_setpos(stream_ptr, offset) qp_stream_seek((stream_ptr), (offset), SEEK_SET)
#define qp_stream_getpos(stream_ptr) qp_stream_tell((stream_ptr))
#define qp_stream_read(output_buf, member_size, num_members, stream_ptr) qp_stream_read_impl((output_buf), (member_size), (num_members), (qp_stream_t *)(stream_ptr))
#define qp_stream_write(input_buf, member_size, num_members, stream_ptr) qp_stream_write_impl((input_buf), (member_size), (num_members), (qp_stream_t *)(stream_ptr))

uint32_t qp_stream_read_impl(void *output_buf, uint32_t member_size, uint32_t num_members, qp_stream_t *stream);
uint32_t qp_stream_write_impl(const void *input_buf, uint32_t member_size, uint32_t num_members, qp_stream_t *stream);

#define qp_stream_close(stream_ptr) (((qp_stream_t *)(stream_ptr))->close((qp_stream_t *)(stream_ptr)))

#define STREAM_EOF ((int16_t)(-1))

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Stream definition

typedef struct qp_stream_t {
    int16_t (*get)(qp_stream_t *stream);
    bool (*put)(qp_stream_t *stream, uint8_t c);
    int (*seek)(qp_stream_t *stream, int32_t offset, int origin);
    int32_t (*tell)(qp_stream_t *stream);
    bool (*is_eof)(qp_stream_t *stream);
    void (*close)(qp_stream_t *stream);
} qp_stream_t;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Memory streams

typedef struct qp_memory_stream_t {
    qp_stream_t base;
    uint8_t *   buffer;
    int32_t     length;
    int32_t     position;
    bool        is_eof;
} qp_memory_stream_t;

qp_memory_stream_t qp_make_memory_stream(void *buffer, int32_t length);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FILE streams

#ifdef QP_STREAM_HAS_FILE_IO

typedef struct qp_file_stream_t {
    qp_stream_t base;
    FILE *      file;
} qp_file_stream_t;

qp_file_stream_t qp_make_file_stream(FILE *f);

#endif // QP_STREAM_HAS_FILE_IO
