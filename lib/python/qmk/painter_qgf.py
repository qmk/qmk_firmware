# Copyright 2021 Nick Brassel (@tzarc)
# Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
# SPDX-License-Identifier: GPL-2.0-or-later

# Quantum Graphics File "QGF" Image File Format.
# See https://docs.qmk.fm/#/quantum_painter_qgf for more information.

import functools
from colorsys import rgb_to_hsv
from types import FunctionType
from PIL import Image, ImageFile, ImageChops
from PIL._binary import o8, o16le as o16, o32le as o32
import qmk.painter


def o24(i):
    return o16(i & 0xFFFF) + o8((i & 0xFF0000) >> 16)


# Helper to convert from RGB888 to the QMK "dialect" of HSV888
def rgb888_to_qmk_hsv888(e):
    hsv = rgb_to_hsv(e[0] / 255.0, e[1] / 255.0, e[2] / 255.0)
    return (int(hsv[0] * 255.0), int(hsv[1] * 255.0), int(hsv[2] * 255.0))


########################################################################################################################


class QGFBlockHeader:
    block_size = 5

    def write(self, fp):
        fp.write(b''  # start off with empty bytes...
                 + o8(self.type_id)  # block type id
                 + o8((~self.type_id) & 0xFF)  # negated block type id
                 + o24(self.length)  # blob length
                 )


########################################################################################################################


class QGFGraphicsDescriptor:
    type_id = 0x00
    length = 18
    magic = 0x464751

    def __init__(self):
        self.header = QGFBlockHeader()
        self.header.type_id = QGFGraphicsDescriptor.type_id
        self.header.length = QGFGraphicsDescriptor.length
        self.version = 1
        self.total_file_size = 0
        self.image_width = 0
        self.image_height = 0
        self.frame_count = 0

    def write(self, fp):
        self.header.write(fp)
        fp.write(
            b''  # start off with empty bytes...
            + o24(QGFGraphicsDescriptor.magic)  # magic
            + o8(self.version)  # version
            + o32(self.total_file_size)  # file size
            + o32((~self.total_file_size) & 0xFFFFFFFF)  # negated file size
            + o16(self.image_width)  # width
            + o16(self.image_height)  # height
            + o16(self.frame_count)  # frame count
        )

    @property
    def image_size(self):
        return self.image_width, self.image_height

    @image_size.setter
    def image_size(self, size):
        self.image_width, self.image_height = size


########################################################################################################################


class QGFFrameOffsetDescriptorV1:
    type_id = 0x01

    def __init__(self, frame_count):
        self.header = QGFBlockHeader()
        self.header.type_id = QGFFrameOffsetDescriptorV1.type_id
        self.frame_offsets = [0xFFFFFFFF] * frame_count
        self.frame_count = frame_count

    def write(self, fp):
        self.header.length = len(self.frame_offsets) * 4
        self.header.write(fp)
        for offset in self.frame_offsets:
            fp.write(b''  # start off with empty bytes...
                     + o32(offset)  # offset
                     )


########################################################################################################################


class QGFFrameDescriptorV1:
    type_id = 0x02
    length = 6

    def __init__(self):
        self.header = QGFBlockHeader()
        self.header.type_id = QGFFrameDescriptorV1.type_id
        self.header.length = QGFFrameDescriptorV1.length
        self.format = 0xFF
        self.flags = 0
        self.compression = 0xFF
        self.transparency_index = 0xFF  # TODO: Work out how to retrieve the transparent palette entry from the PIL gif loader
        self.delay = 1000  # Placeholder until it gets read from the animation

    def write(self, fp):
        self.header.write(fp)
        fp.write(b''  # start off with empty bytes...
                 + o8(self.format)  # format
                 + o8(self.flags)  # flags
                 + o8(self.compression)  # compression
                 + o8(self.transparency_index)  # transparency index
                 + o16(self.delay)  # delay
                 )

    @property
    def is_transparent(self):
        return (self.flags & 0x01) == 0x01

    @is_transparent.setter
    def is_transparent(self, val):
        if val:
            self.flags |= 0x01
        else:
            self.flags &= ~0x01

    @property
    def is_delta(self):
        return (self.flags & 0x02) == 0x02

    @is_delta.setter
    def is_delta(self, val):
        if val:
            self.flags |= 0x02
        else:
            self.flags &= ~0x02


########################################################################################################################


class QGFFramePaletteDescriptorV1:
    type_id = 0x03

    def __init__(self):
        self.header = QGFBlockHeader()
        self.header.type_id = QGFFramePaletteDescriptorV1.type_id
        self.header.length = 0
        self.palette_entries = [(0xFF, 0xFF, 0xFF)] * 4

    def write(self, fp):
        self.header.length = len(self.palette_entries) * 3
        self.header.write(fp)
        for entry in self.palette_entries:
            fp.write(b''  # start off with empty bytes...
                     + o8(entry[0])  # h
                     + o8(entry[1])  # s
                     + o8(entry[2])  # v
                     )


########################################################################################################################


class QGFFrameDeltaDescriptorV1:
    type_id = 0x04
    length = 8

    def __init__(self):
        self.header = QGFBlockHeader()
        self.header.type_id = QGFFrameDeltaDescriptorV1.type_id
        self.header.length = QGFFrameDeltaDescriptorV1.length
        self.left = 0
        self.top = 0
        self.right = 0
        self.bottom = 0

    def write(self, fp):
        self.header.write(fp)
        fp.write(b''  # start off with empty bytes...
                 + o16(self.left)  # left
                 + o16(self.top)  # top
                 + o16(self.right)  # right
                 + o16(self.bottom)  # bottom
                 )

    @property
    def bbox(self):
        return self.left, self.top, self.right, self.bottom

    @bbox.setter
    def bbox(self, bbox):
        self.left, self.top, self.right, self.bottom = bbox


########################################################################################################################


class QGFFrameDataDescriptorV1:
    type_id = 0x05

    def __init__(self):
        self.header = QGFBlockHeader()
        self.header.type_id = QGFFrameDataDescriptorV1.type_id
        self.data = []

    def write(self, fp):
        self.header.length = len(self.data)
        self.header.write(fp)
        fp.write(bytes(self.data))


########################################################################################################################


class QGFImageFile(ImageFile.ImageFile):

    format = "QGF"
    format_description = "Quantum Graphics File Format"

    def _open(self):
        raise NotImplementedError("Reading QGF files is not supported")


########################################################################################################################


def _accept(prefix):
    """Helper method used by PIL to work out if it can parse an input file.

    Currently unimplemented.
    """
    return False


def _for_all_frames(x: FunctionType, /, images):
    frame_num = 0
    last_frame = None
    for frame in images:
        # Get number of of frames in this image
        nfr = getattr(frame, "n_frames", 1)
        for idx in range(nfr):
            frame.seek(idx)
            frame.load()
            copy = frame.copy().convert("RGB")
            x(frame_num, copy, last_frame)
            last_frame = copy
            frame_num += 1


def _compress_image(frame, last_frame, *, use_rle, use_deltas, format_, **_kwargs):
    # Convert the original frame so we can do comparisons
    converted = qmk.painter.convert_requested_format(frame, format_)
    graphic_data = qmk.painter.convert_image_bytes(converted, format_)

    # Convert the raw data to RLE-encoded if requested
    raw_data = graphic_data[1]
    if use_rle:
        rle_data = qmk.painter.compress_bytes_qmk_rle(graphic_data[1])
    use_raw_this_frame = not use_rle or len(raw_data) <= len(rle_data)
    image_data = raw_data if use_raw_this_frame else rle_data

    # Work out if a delta frame is smaller than injecting it directly
    use_delta_this_frame = False
    bbox = None
    if use_deltas and last_frame is not None:
        # If we want to use deltas, then find the difference
        diff = ImageChops.difference(frame, last_frame)

        # Get the bounding box of those differences
        bbox = diff.getbbox()

        # If we have a valid bounding box...
        if bbox:
            # ...create the delta frame by cropping the original.
            delta_frame = frame.crop(bbox)

            # Convert the delta frame to the requested format
            delta_converted = qmk.painter.convert_requested_format(delta_frame, format_)
            delta_graphic_data = qmk.painter.convert_image_bytes(delta_converted, format_)

            # Work out how large the delta frame is going to be with compression etc.
            delta_raw_data = delta_graphic_data[1]
            if use_rle:
                delta_rle_data = qmk.painter.compress_bytes_qmk_rle(delta_graphic_data[1])
            delta_use_raw_this_frame = not use_rle or len(delta_raw_data) <= len(delta_rle_data)
            delta_image_data = delta_raw_data if delta_use_raw_this_frame else delta_rle_data

            # If the size of the delta frame (plus delta descriptor) is smaller than the original, use that instead
            # This ensures that if a non-delta is overall smaller in size, we use that in preference due to flash
            # sizing constraints.
            if (len(delta_image_data) + QGFFrameDeltaDescriptorV1.length) < len(image_data):
                # Copy across all the delta equivalents so that the rest of the processing acts on those
                graphic_data = delta_graphic_data
                raw_data = delta_raw_data
                rle_data = delta_rle_data
                use_raw_this_frame = delta_use_raw_this_frame
                image_data = delta_image_data
                use_delta_this_frame = True

        # Default to whole image
        bbox = bbox or [0, 0, *frame.size]
        # Fix sze (as per #20296), we need to cast first as tuples are inmutable
        bbox = list(bbox)
        bbox[2] -= 1
        bbox[3] -= 1

    return {
        "bbox": bbox,
        "graphic_data": graphic_data,
        "image_data": image_data,
        "use_delta_this_frame": use_delta_this_frame,
        "use_raw_this_frame": use_raw_this_frame,
    }


# Helper function to save each frame to the output file
def _write_frame(idx, frame, last_frame, *, fp, frame_offsets, **kwargs):
    # Not an argument of the function as it would consume from **kwargs
    format_ = kwargs["format_"]

    # (potentially) Apply RLE and/or delta, and work out output image's information
    outputs = _compress_image(frame, last_frame, **kwargs)
    bbox = outputs["bbox"]
    graphic_data = outputs["graphic_data"]
    image_data = outputs["image_data"]
    use_delta_this_frame = outputs["use_delta_this_frame"]
    use_raw_this_frame = outputs["use_raw_this_frame"]

    # Write out the frame descriptor
    frame_offsets.frame_offsets[idx] = fp.tell()
    vprint(f'{f"Frame {idx:3d} base":26s} {fp.tell():5d}d / {fp.tell():04X}h')
    frame_descriptor = QGFFrameDescriptorV1()
    frame_descriptor.is_delta = use_delta_this_frame
    frame_descriptor.is_transparent = False
    frame_descriptor.format = format_['image_format_byte']
    frame_descriptor.compression = 0x00 if use_raw_this_frame else 0x01  # See qp.h, painter_compression_t
    frame_descriptor.delay = frame.info.get('duration', 1000)  # If we're not an animation, just pretend we're delaying for 1000ms
    frame_descriptor.write(fp)

    # Write out the palette if required
    if format_['has_palette']:
        palette = graphic_data[0]
        palette_descriptor = QGFFramePaletteDescriptorV1()

        # Convert all palette entries to HSV888 and write to the output
        palette_descriptor.palette_entries = list(map(rgb888_to_qmk_hsv888, palette))
        vprint(f'{f"Frame {idx:3d} palette":26s} {fp.tell():5d}d / {fp.tell():04X}h')
        palette_descriptor.write(fp)

    # Write out the delta info if required
    if use_delta_this_frame:
        # Set up the rendering location of where the delta frame should be situated
        delta_descriptor = QGFFrameDeltaDescriptorV1()
        delta_descriptor.bbox = bbox

        # Write the delta frame to the output
        vprint(f'{f"Frame {idx:3d} delta":26s} {fp.tell():5d}d / {fp.tell():04X}h')
        delta_descriptor.write(fp)

    # Write out the data for this frame to the output
    data_descriptor = QGFFrameDataDescriptorV1()
    data_descriptor.data = image_data
    vprint(f'{f"Frame {idx:3d} data":26s} {fp.tell():5d}d / {fp.tell():04X}h')
    data_descriptor.write(fp)


def _save(im, fp, _filename):
    """Helper method used by PIL to write to an output file.
    """
    # Work out from the parameters if we need to do anything special
    encoderinfo = im.encoderinfo.copy()

    # Helper for prints, noop taking any args if not verbose
    global vprint
    verbose = encoderinfo.get("verbose", False)
    vprint = print if verbose else lambda *_args, **_kwargs: None

    # Helper to iterate through all frames in the input image
    append_images = list(encoderinfo.get("append_images", []))
    for_all_frames = functools.partial(_for_all_frames, images=[im, *append_images])

    # Collect all the frame sizes
    frame_sizes = []
    for_all_frames(lambda _idx, frame, _last_frame: frame_sizes.append(frame.size))

    # Make sure all frames are the same size
    if len(set(frame_sizes)) != 1:
        raise ValueError("Mismatching sizes on frames")

    # Write out the initial graphics descriptor (and write a dummy value), so that we can come back and fill in the
    # correct values once we've written all the frames to the output
    graphics_descriptor_location = fp.tell()
    graphics_descriptor = QGFGraphicsDescriptor()
    graphics_descriptor.frame_count = len(frame_sizes)
    graphics_descriptor.image_size = frame_sizes[0]
    vprint(f'{"Graphics descriptor block":26s} {fp.tell():5d}d / {fp.tell():04X}h')
    graphics_descriptor.write(fp)

    # Work out the frame offset descriptor location (and write a dummy value), so that we can come back and fill in the
    # correct offsets once we've written all the frames to the output
    frame_offset_location = fp.tell()
    frame_offsets = QGFFrameOffsetDescriptorV1(graphics_descriptor.frame_count)
    vprint(f'{"Frame offsets block":26s} {fp.tell():5d}d / {fp.tell():04X}h')
    frame_offsets.write(fp)

    # Iterate over each if the input frames, writing it to the output in the process
    write_frame = functools.partial(_write_frame, format_=encoderinfo["qmk_format"], fp=fp, use_deltas=encoderinfo.get("use_deltas", True), use_rle=encoderinfo.get("use_rle", True), frame_offsets=frame_offsets)
    for_all_frames(write_frame)

    # Go back and update the graphics descriptor now that we can determine the final file size
    graphics_descriptor.total_file_size = fp.tell()
    fp.seek(graphics_descriptor_location, 0)
    graphics_descriptor.write(fp)

    # Go back and update the frame offsets now that they're written to the file
    fp.seek(frame_offset_location, 0)
    frame_offsets.write(fp)


########################################################################################################################

# Register with PIL so that it knows about the QGF format
Image.register_open(QGFImageFile.format, QGFImageFile, _accept)
Image.register_save(QGFImageFile.format, _save)
Image.register_save_all(QGFImageFile.format, _save)
Image.register_extension(QGFImageFile.format, f".{QGFImageFile.format.lower()}")
Image.register_mime(QGFImageFile.format, f"image/{QGFImageFile.format.lower()}")
