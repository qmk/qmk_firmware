// Copyright 2021 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

#include <qp_internal.h>
#include <qp_draw.h>
#include <qgf.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QGF image handles

typedef struct qgf_image_handle_t {
    painter_image_desc_t base;
    bool                 validate_ok;
    union {
        qp_stream_t        stream;
        qp_memory_stream_t mem_stream;
#ifdef QP_STREAM_HAS_FILE_IO
        qp_file_stream_t file_stream;
#endif  // QP_STREAM_HAS_FILE_IO
    };
} qgf_image_handle_t;

static qgf_image_handle_t image_descriptors[QUANTUM_PAINTER_NUM_IMAGES] = {0};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter External API: qp_load_image_mem

painter_image_handle_t qp_load_image_mem(const void QP_RESIDENT_FLASH_OR_RAM *buffer) {
    qp_dprintf("qp_load_image_mem: entry\n");
    qgf_image_handle_t *image = NULL;

    // Find a free slot
    for (int i = 0; i < QUANTUM_PAINTER_NUM_IMAGES; ++i) {
        if (!image_descriptors[i].validate_ok) {
            image = &image_descriptors[i];
            break;
        }
    }

    // Drop out if not found
    if (!image) {
        qp_dprintf("qp_load_image_mem: fail (no free slot)\n");
        return NULL;
    }

    // Assume we can read the graphics descriptor
    image->mem_stream = qp_make_memory_stream((void QP_RESIDENT_FLASH_OR_RAM *)buffer, sizeof(qgf_graphics_descriptor_v1_t));

    // Update the length of the stream to match, and rewind to the start
    image->mem_stream.length   = qgf_get_total_size(&image->stream);
    image->mem_stream.position = 0;

    // Now that we know the length, validate the input data
    if (!qgf_validate_stream(&image->stream)) {
        qp_dprintf("qp_load_image_mem: fail (failed validation)\n");
        return NULL;
    }

    // Fill out the QP image descriptor
    qgf_read_graphics_descriptor(&image->stream, &image->base.width, &image->base.height, &image->base.frame_count, NULL);

    // Validation success, we can return the handle
    image->validate_ok = true;
    qp_dprintf("qp_load_image_mem: ok\n");
    return (painter_image_handle_t)image;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter External API: qp_close_image

bool qp_close_image(painter_image_handle_t image) {
    qgf_image_handle_t *qgf_image = (qgf_image_handle_t *)image;
    if (!qgf_image->validate_ok) {
        qp_dprintf("qp_close_image: fail (invalid image)\n");
        return false;
    }

    // Free up this image for use elsewhere.
    qgf_image->validate_ok = false;
    return true;
}
