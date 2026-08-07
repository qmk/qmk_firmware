# Copyright 2021 Nick Brassel (@tzarc)
# SPDX-License-Identifier: GPL-2.0-or-later

# Quantum Font File "QFF" Font File Format.
# See https://docs.qmk.fm/#/quantum_painter_qff for more information.

from pathlib import Path
from typing import Dict, Any
from colorsys import rgb_to_hsv
from PIL import Image, ImageDraw, ImageFont, ImageChops
from PIL._binary import o8, o16le as o16, o32le as o32
from qmk.painter_qgf import QGFBlockHeader, QGFFramePaletteDescriptorV1
from milc.attrdict import AttrDict
import qmk.painter


def o24(i):
    return o16(i & 0xFFFF) + o8((i & 0xFF0000) >> 16)


########################################################################################################################


class QFFGlyphInfo(AttrDict):
    def __init__(self, *args, **kwargs):
        super().__init__()

        for n, value in enumerate(args):
            self[f'arg:{n}'] = value

        for key, value in kwargs.items():
            self[key] = value

    def write(self, fp, include_code_point):
        if include_code_point is True:
            fp.write(o24(ord(self.code_point)))

        value = ((self.data_offset << 6) & 0xFFFFC0) | (self.w & 0x3F)
        fp.write(o24(value))


########################################################################################################################


class QFFFontDescriptor:
    type_id = 0x00
    length = 20
    magic = 0x464651

    def __init__(self):
        self.header = QGFBlockHeader()
        self.header.type_id = QFFFontDescriptor.type_id
        self.header.length = QFFFontDescriptor.length
        self.version = 1
        self.total_file_size = 0
        self.line_height = 0
        self.has_ascii_table = False
        self.unicode_glyph_count = 0
        self.format = 0xFF
        self.flags = 0
        self.compression = 0xFF
        self.transparency_index = 0xFF  # TODO: Work out how to retrieve the transparent palette entry from the PIL gif loader

    def write(self, fp):
        self.header.write(fp)
        fp.write(
            b''  # start off with empty bytes...
            + o24(QFFFontDescriptor.magic)  # magic
            + o8(self.version)  # version
            + o32(self.total_file_size)  # file size
            + o32((~self.total_file_size) & 0xFFFFFFFF)  # negated file size
            + o8(self.line_height)  # line height
            + o8(1 if self.has_ascii_table is True else 0)  # whether or not we have an ascii table present
            + o16(self.unicode_glyph_count & 0xFFFF)  # number of unicode glyphs present
            + o8(self.format)  # format
            + o8(self.flags)  # flags
            + o8(self.compression)  # compression
            + o8(self.transparency_index)  # transparency index
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


########################################################################################################################


class QFFAsciiGlyphTableV1:
    type_id = 0x01
    length = 95 * 3  # We have 95 glyphs: [0x20...0x7E]

    def __init__(self):
        self.header = QGFBlockHeader()
        self.header.type_id = QFFAsciiGlyphTableV1.type_id
        self.header.length = QFFAsciiGlyphTableV1.length

        # Each glyph is key=code_point, value=QFFGlyphInfo
        self.glyphs = {}

    def add_glyph(self, glyph: QFFGlyphInfo):
        self.glyphs[ord(glyph.code_point)] = glyph

    def write(self, fp):
        self.header.write(fp)

        for n in range(0x20, 0x7F):
            self.glyphs[n].write(fp, False)


########################################################################################################################


class QFFUnicodeGlyphTableV1:
    type_id = 0x02

    def __init__(self):
        self.header = QGFBlockHeader()
        self.header.type_id = QFFUnicodeGlyphTableV1.type_id
        self.header.length = 0

        # Each glyph is key=code_point, value=QFFGlyphInfo
        self.glyphs = {}

    def add_glyph(self, glyph: QFFGlyphInfo):
        self.glyphs[ord(glyph.code_point)] = glyph

    def write(self, fp):
        self.header.length = len(self.glyphs.keys()) * 6
        self.header.write(fp)

        for n in sorted(self.glyphs.keys()):
            self.glyphs[n].write(fp, True)


########################################################################################################################


class QFFFontDataDescriptorV1:
    type_id = 0x04

    def __init__(self):
        self.header = QGFBlockHeader()
        self.header.type_id = QFFFontDataDescriptorV1.type_id
        self.data = []

    def write(self, fp):
        self.header.length = len(self.data)
        self.header.write(fp)
        fp.write(bytes(self.data))


########################################################################################################################


def _generate_font_glyphs_list(use_ascii, unicode_glyphs):
    # The set of glyphs that we want to generate images for
    glyphs = {}

    # Add ascii charset if requested
    if use_ascii is True:
        for c in range(0x20, 0x7F):  # does not include 0x7F!
            glyphs[chr(c)] = True

    # Append any extra unicode glyphs
    unicode_glyphs = list(unicode_glyphs)
    for c in unicode_glyphs:
        glyphs[c] = True

    return sorted(glyphs.keys())


class QFFFont:
    def __init__(self, logger):
        self.logger = logger
        self.image = None
        self.glyph_data = {}
        self.glyph_height = 0
        return

    def _extract_glyphs(self, format):
        total_data_size = 0
        total_rle_data_size = 0

        converted_img = qmk.painter.convert_requested_format(self.image, format)
        (self.palette, _) = qmk.painter.convert_image_bytes(converted_img, format)

        # Work out how many bytes used for RLE vs. non-RLE
        for _, glyph_entry in self.glyph_data.items():
            glyph_img = converted_img.crop((glyph_entry.x, 1, glyph_entry.x + glyph_entry.w, 1 + self.glyph_height))
            (_, this_glyph_image_bytes) = qmk.painter.convert_image_bytes(glyph_img, format)
            this_glyph_rle_bytes = qmk.painter.compress_bytes_qmk_rle(this_glyph_image_bytes)
            total_data_size += len(this_glyph_image_bytes)
            total_rle_data_size += len(this_glyph_rle_bytes)
            glyph_entry['image_uncompressed_bytes'] = this_glyph_image_bytes
            glyph_entry['image_compressed_bytes'] = this_glyph_rle_bytes

        return (total_data_size, total_rle_data_size)

    def _parse_image(self, img, include_ascii_glyphs: bool = True, unicode_glyphs: str = ''):
        # Clear out any existing font metadata
        self.image = None
        # Each glyph is key=code_point, value={ x: ?, w: ? }
        self.glyph_data = {}
        self.glyph_height = 0

        # Work out the list of glyphs required
        glyphs = _generate_font_glyphs_list(include_ascii_glyphs, unicode_glyphs)

        # Work out the geometry
        (width, height) = img.size

        # Work out the glyph offsets/widths
        glyph_pixel_offsets = []
        glyph_pixel_widths = []
        pixels = img.load()

        # Run through the markers and work out where each glyph starts/stops
        glyph_split_color = pixels[0, 0]  # top left pixel is the marker color we're going to use to split each glyph
        glyph_pixel_offsets.append(0)
        last_offset = 0
        for x in range(1, width):
            if pixels[x, 0] == glyph_split_color:
                glyph_pixel_offsets.append(x)
                glyph_pixel_widths.append(x - last_offset)
                last_offset = x
        glyph_pixel_widths.append(width - last_offset)

        # Make sure the number of glyphs we're attempting to generate matches the input image
        if len(glyph_pixel_offsets) != len(glyphs):
            self.logger.error('The number of glyphs to generate doesn\'t match the number of detected glyphs in the input image.')
            return

        # Set up the required metadata for each glyph
        for n in range(0, len(glyph_pixel_offsets)):
            self.glyph_data[glyphs[n]] = QFFGlyphInfo(code_point=glyphs[n], x=glyph_pixel_offsets[n], w=glyph_pixel_widths[n])

        # Parsing was successful, keep the image in this instance
        self.image = img
        self.glyph_height = height - 1  # subtract the line with the markers

    def generate_image(self, ttf_file: Path, font_size: int, include_ascii_glyphs: bool = True, unicode_glyphs: str = '', include_before_left: bool = False, use_aa: bool = True):
        # Load the font
        font = ImageFont.truetype(str(ttf_file), int(font_size))
        # Work out the max font size
        max_font_size = font.font.ascent + abs(font.font.descent)
        # Work out the list of glyphs required
        glyphs = _generate_font_glyphs_list(include_ascii_glyphs, unicode_glyphs)

        baseline_offset = 9999999
        total_glyph_width = 0
        max_glyph_height = -1

        # Measure each glyph to determine the overall baseline offset required
        for glyph in glyphs:
            (ls_l, ls_t, ls_r, ls_b) = font.getbbox(glyph, anchor='ls')
            glyph_width = (ls_r - ls_l) if include_before_left else (ls_r)
            glyph_height = font.getbbox(glyph, anchor='la')[3]
            if max_glyph_height < glyph_height:
                max_glyph_height = glyph_height
            total_glyph_width += glyph_width
            if baseline_offset > ls_t:
                baseline_offset = ls_t

        # Create the output image
        img = Image.new("RGB", (total_glyph_width + 1, max_font_size * 2 + 1), (0, 0, 0, 255))
        cur_x_pos = 0

        # Loop through each glyph...
        for glyph in glyphs:
            # Work out this glyph's bounding box
            (ls_l, ls_t, ls_r, ls_b) = font.getbbox(glyph, anchor='ls')
            glyph_width = (ls_r - ls_l) if include_before_left else (ls_r)
            glyph_height = ls_b - ls_t
            x_offset = -ls_l
            y_offset = ls_t - baseline_offset

            # Draw each glyph to its own image so we don't get anti-aliasing applied to the final image when straddling edges
            glyph_img = Image.new("RGB", (glyph_width, max_font_size), (0, 0, 0, 255))
            glyph_draw = ImageDraw.Draw(glyph_img)
            if not use_aa:
                glyph_draw.fontmode = "1"
            glyph_draw.text((x_offset, y_offset), glyph, font=font, anchor='lt')

            # Place the glyph-specific image in the correct location overall
            img.paste(glyph_img, (cur_x_pos, 1))

            # Set up the marker for start of each glyph
            pixels = img.load()
            pixels[cur_x_pos, 0] = (255, 0, 255)

            # Increment for the next glyph's position
            cur_x_pos += glyph_width

        # Add the ending marker so that the difference/crop works
        pixels = img.load()
        pixels[cur_x_pos, 0] = (255, 0, 255)

        # Determine the usable font area
        dummy_img = Image.new("RGB", (total_glyph_width + 1, max_font_size + 1), (0, 0, 0, 255))
        bbox = ImageChops.difference(img, dummy_img).getbbox()
        bbox = (bbox[0], bbox[1], bbox[2] - 1, bbox[3])  # remove the unused end-marker

        # Crop and re-parse the resulting image to ensure we're generating the correct format
        self._parse_image(img.crop(bbox), include_ascii_glyphs, unicode_glyphs)

    def save_to_image(self, img_file: Path):
        # Drop out if there's no image loaded
        if self.image is None:
            self.logger.error('No image is loaded.')
            return

        # Save the image to the supplied file
        self.image.save(str(img_file))

    def read_from_image(self, img_file: Path, include_ascii_glyphs: bool = True, unicode_glyphs: str = ''):
        # Load and parse the supplied image file
        self._parse_image(Image.open(str(img_file)), include_ascii_glyphs, unicode_glyphs)
        return

    def save_to_qff(self, format: Dict[str, Any], use_rle: bool, fp):
        # Drop out if there's no image loaded
        if self.image is None:
            self.logger.error('No image is loaded.')
            return

        # Work out if we want to use RLE at all, skipping it if it's not any smaller (it's applied per-glyph)
        (total_data_size, total_rle_data_size) = self._extract_glyphs(format)
        if use_rle:
            use_rle = (total_rle_data_size < total_data_size)

        # For each glyph, work out which image data we want to use and append it to the image buffer, recording the byte-wise offset
        img_buffer = bytes()
        for _, glyph_entry in self.glyph_data.items():
            glyph_entry['data_offset'] = len(img_buffer)
            glyph_img_bytes = glyph_entry.image_compressed_bytes if use_rle else glyph_entry.image_uncompressed_bytes
            img_buffer += bytes(glyph_img_bytes)

        font_descriptor = QFFFontDescriptor()
        ascii_table = QFFAsciiGlyphTableV1()
        unicode_table = QFFUnicodeGlyphTableV1()
        data_descriptor = QFFFontDataDescriptorV1()
        data_descriptor.data = img_buffer

        # Check if we have all the ASCII glyphs present
        include_ascii_glyphs = all([chr(n) in self.glyph_data for n in range(0x20, 0x7F)])

        # Helper for populating the blocks
        for code_point, glyph_entry in self.glyph_data.items():
            if ord(code_point) >= 0x20 and ord(code_point) <= 0x7E and include_ascii_glyphs:
                ascii_table.add_glyph(glyph_entry)
            else:
                unicode_table.add_glyph(glyph_entry)

        # Configure the font descriptor
        font_descriptor.line_height = self.glyph_height
        font_descriptor.has_ascii_table = include_ascii_glyphs
        font_descriptor.unicode_glyph_count = len(unicode_table.glyphs.keys())
        font_descriptor.is_transparent = False
        font_descriptor.format = format['image_format_byte']
        font_descriptor.compression = 0x01 if use_rle else 0x00

        # Write a dummy font descriptor -- we'll have to come back and write it properly once we've rendered out everything else
        font_descriptor_location = fp.tell()
        font_descriptor.write(fp)

        # Write out the ASCII table if required
        if font_descriptor.has_ascii_table:
            ascii_table.write(fp)

        # Write out the unicode table if required
        if font_descriptor.unicode_glyph_count > 0:
            unicode_table.write(fp)

        # Write out the palette if required
        if format['has_palette']:
            palette_descriptor = QGFFramePaletteDescriptorV1()

            # Helper to convert from RGB888 to the QMK "dialect" of HSV888
            def rgb888_to_qmk_hsv888(e):
                hsv = rgb_to_hsv(e[0] / 255.0, e[1] / 255.0, e[2] / 255.0)
                return (int(hsv[0] * 255.0), int(hsv[1] * 255.0), int(hsv[2] * 255.0))

            # Convert all palette entries to HSV888 and write to the output
            palette_descriptor.palette_entries = list(map(rgb888_to_qmk_hsv888, self.palette))
            palette_descriptor.write(fp)

        # Write out the image data
        data_descriptor.write(fp)

        # Now fix up the overall font descriptor, then write it in the correct location
        font_descriptor.total_file_size = fp.tell()
        fp.seek(font_descriptor_location, 0)
        font_descriptor.write(fp)
