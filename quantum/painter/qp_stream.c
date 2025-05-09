// Copyright 2021 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "qp_stream.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Stream API

uint32_t qp_stream_read_impl(void *output_buf, uint32_t member_size, uint32_t num_members, qp_stream_t *stream) {
    uint8_t *output_ptr = (uint8_t *)output_buf;

    uint32_t i;
    for (i = 0; i < (num_members * member_size); ++i) {
        int16_t c = qp_stream_get(stream);
        if (c < 0) {
            break;
        }

        output_ptr[i] = (uint8_t)(c & 0xFF);
    }

    return i / member_size;
}

uint32_t qp_stream_write_impl(const void *input_buf, uint32_t member_size, uint32_t num_members, qp_stream_t *stream) {
    uint8_t *input_ptr = (uint8_t *)input_buf;

    uint32_t i;
    for (i = 0; i < (num_members * member_size); ++i) {
        if (!qp_stream_put(stream, input_ptr[i])) {
            break;
        }
    }

    return i / member_size;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Memory streams

static inline int16_t mem_get(qp_stream_t *stream) {
    qp_memory_stream_t *s = (qp_memory_stream_t *)stream;
    if (s->position >= s->length) {
        s->is_eof = true;
        return STREAM_EOF;
    }
    return s->buffer[s->position++];
}

static inline bool mem_put(qp_stream_t *stream, uint8_t c) {
    qp_memory_stream_t *s = (qp_memory_stream_t *)stream;
    if (s->position >= s->length) {
        s->is_eof = true;
        return false;
    }
    s->buffer[s->position++] = c;
    return true;
}

static inline int mem_seek(qp_stream_t *stream, int32_t offset, int origin) {
    qp_memory_stream_t *s = (qp_memory_stream_t *)stream;

    // Handle as per fseek
    int32_t position = s->position;
    switch (origin) {
        case SEEK_SET:
            position = offset;
            break;
        case SEEK_CUR:
            position += offset;
            break;
        case SEEK_END:
            position = s->length + offset;
            break;
        default:
            return -1;
    }

    // If we're before the start, ignore it.
    if (position < 0) {
        return -1;
    }

    // If we're at the end it's okay, we only care if we're after the end for failure purposes -- as per lseek()
    if (position > s->length) {
        return -1;
    }

    // Update the offset
    s->position = position;

    // Successful invocation of fseek() results in clearing of the EOF flag by default, mirror the same functionality
    s->is_eof = false;

    return 0;
}

static inline int32_t mem_tell(qp_stream_t *stream) {
    qp_memory_stream_t *s = (qp_memory_stream_t *)stream;
    return s->position;
}

static inline bool mem_is_eof(qp_stream_t *stream) {
    qp_memory_stream_t *s = (qp_memory_stream_t *)stream;
    return s->is_eof;
}

static inline void mem_close(qp_stream_t *stream) {
    // No-op.
}

qp_memory_stream_t qp_make_memory_stream(void *buffer, int32_t length) {
    qp_memory_stream_t stream = {
        .base     = {.get = mem_get, .put = mem_put, .seek = mem_seek, .tell = mem_tell, .is_eof = mem_is_eof, .close = mem_close},
        .buffer   = (uint8_t *)buffer,
        .length   = length,
        .position = 0,
    };
    return stream;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FILE streams

#ifdef QP_STREAM_HAS_FILE_IO

static inline int16_t file_get(qp_stream_t *stream) {
    qp_file_stream_t *s = (qp_file_stream_t *)stream;
    int               c = fgetc(s->file);
    if (c < 0 || feof(s->file)) return STREAM_EOF;
    return (uint16_t)c;
}

static inline bool file_put(qp_stream_t *stream, uint8_t c) {
    qp_file_stream_t *s = (qp_file_stream_t *)stream;
    return fputc(c, s->file) == c;
}

static inline int file_seek(qp_stream_t *stream, int32_t offset, int origin) {
    qp_file_stream_t *s = (qp_file_stream_t *)stream;
    return fseek(s->file, offset, origin);
}

static inline int32_t file_tell(qp_stream_t *stream) {
    qp_file_stream_t *s = (qp_file_stream_t *)stream;
    return (int32_t)ftell(s->file);
}

static inline bool file_is_eof(qp_stream_t *stream) {
    qp_file_stream_t *s = (qp_file_stream_t *)stream;
    return (bool)feof(s->file);
}

static inline void file_close(qp_stream_t *stream) {
    qp_file_stream_t *s = (qp_file_stream_t *)stream;
    fclose(s->file);
}

qp_file_stream_t qp_make_file_stream(FILE *f) {
    qp_file_stream_t stream = {
        .base = {.get = file_get, .put = file_put, .seek = file_seek, .tell = file_tell, .is_eof = file_is_eof, .close = file_close},
        .file = f,
    };
    return stream;
}
#endif // QP_STREAM_HAS_FILE_IO
