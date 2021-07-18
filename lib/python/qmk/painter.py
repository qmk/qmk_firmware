"""Functions that help us work with Quantum Painter's file formats.
"""
import math
import re
from PIL import Image, ImageOps

valid_formats = {
    'rgb565': {
        'image_format': 'IMAGE_FORMAT_RGB565',
        'bpp': 16,
        'num_colors': 65536,
    },
    'pal256': {
        'image_format': 'IMAGE_FORMAT_PALETTE',
        'bpp': 8,
        'has_palette': True,
        'num_colors': 256,
    },
    'pal16': {
        'image_format': 'IMAGE_FORMAT_PALETTE',
        'bpp': 4,
        'has_palette': True,
        'num_colors': 16,
    },
    'pal4': {
        'image_format': 'IMAGE_FORMAT_PALETTE',
        'bpp': 2,
        'has_palette': True,
        'num_colors': 4,
    },
    'pal2': {
        'image_format': 'IMAGE_FORMAT_PALETTE',
        'bpp': 1,
        'has_palette': True,
        'num_colors': 2,
    },
    'mono256': {
        'image_format': 'IMAGE_FORMAT_GRAYSCALE',
        'bpp': 8,
        'has_palette': False,
        'num_colors': 256,
    },
    'mono16': {
        'image_format': 'IMAGE_FORMAT_GRAYSCALE',
        'bpp': 4,
        'has_palette': False,
        'num_colors': 16,
    },
    'mono4': {
        'image_format': 'IMAGE_FORMAT_GRAYSCALE',
        'bpp': 2,
        'has_palette': False,
        'num_colors': 4,
    },
    'mono2': {
        'image_format': 'IMAGE_FORMAT_GRAYSCALE',
        'bpp': 1,
        'has_palette': False,
        'num_colors': 2,
    }
}


def clean_output(str):
    str = re.sub(r'\r', '', str)
    str = re.sub(r'[\n]{3,}', r'\n\n', str)
    return str


def rescale_byte(val, maxval):
    """Rescales a byte value to the supplied range, i.e. [0,255] -> [0,maxval].
    """
    return int(round(val * maxval / 255.0))


def rgb888_to_rgb565(r, g, b):
    """Convert an rgb triplet to the equivalent rgb565 integer.
    """
    rgb565 = (rescale_byte(r, 31) << 11 | rescale_byte(g, 63) << 5 | rescale_byte(b, 31))
    return rgb565


def convert_requested_format(im, format):
    """Convert an image to the requested format.
    """

    # Work out the requested format
    ncolors = format["num_colors"]
    image_format = format["image_format"]

    # Ensure we have a valid number of colors for the palette
    if (ncolors <= 0 or ncolors > 256 or (ncolors & (ncolors - 1) != 0)) and image_format != 'IMAGE_FORMAT_RGB565':
        raise ValueError("Number of colors must be 2, 4, 16, or 256.")

    # Work out where we're getting the bytes from
    if image_format == 'IMAGE_FORMAT_RGB565':
        # If we want RGB565, make sure we've got an RGB image
        im = im.convert("RGB")
    elif image_format == 'IMAGE_FORMAT_GRAYSCALE':
        # If mono, convert input to grayscale, then to RGB, then grab the raw bytes corresponding to the intensity of the red channel
        im = ImageOps.grayscale(im)
        im = im.convert("RGB")
    elif image_format == 'IMAGE_FORMAT_PALETTE':
        # If color, convert input to RGB, palettize based on the supplied number of colors, then get the raw palette bytes
        im = im.convert("RGB")
        im = im.convert("P", palette=Image.ADAPTIVE, colors=ncolors)

    return im


def convert_image_bytes(im, format):
    """Convert the supplied image to the equivalent bytes required by the QMK firmware.
    """

    # Work out the requested format
    ncolors = format["num_colors"]
    image_format = format["image_format"]
    shifter = int(math.log2(ncolors))
    pixels_per_byte = int(8 / math.log2(ncolors))

    if image_format == 'IMAGE_FORMAT_RGB565':
        # If we want RGB565, just get the RGB bytes
        image_bytes = im.tobytes("raw", "RGB")
        image_bytes_len = len(image_bytes)
        palette = None

        # Convert 24-bit RGB to 16-bit rgb565
        bytearray = []
        for x in range(int(image_bytes_len / 3)):
            r = image_bytes[x * 3 + 0]
            g = image_bytes[x * 3 + 1]
            b = image_bytes[x * 3 + 2]
            rgb565 = rgb888_to_rgb565(r, g, b)
            bytearray.append((rgb565 >> 8) & 0xFF)
            bytearray.append(rgb565 & 0xFF)

    elif image_format == 'IMAGE_FORMAT_GRAYSCALE':
        # Take the red channel
        image_bytes = im.tobytes("raw", "R")
        image_bytes_len = len(image_bytes)

        # No palette
        palette = None

        bytearray = []
        for x in range(int(image_bytes_len / pixels_per_byte)):
            byte = 0
            for n in range(pixels_per_byte):
                byte_offset = x * pixels_per_byte + n
                if byte_offset < image_bytes_len:
                    # If mono, each input byte is a grayscale [0,255] pixel -- rescale to the range we want then pack together
                    byte = byte | (rescale_byte(image_bytes[byte_offset], ncolors - 1) << int(n * shifter))
            bytearray.append(byte)

    elif image_format == 'IMAGE_FORMAT_PALETTE':
        # Convert each pixel to the palette bytes
        image_bytes = im.tobytes("raw", "P")
        image_bytes_len = len(image_bytes)

        # Export the palette
        palette = []
        pal = im.getpalette()
        for n in range(0, ncolors * 3, 3):
            palette.append([pal[n + 0], pal[n + 1], pal[n + 2]])

        bytearray = []
        for x in range(int(image_bytes_len / pixels_per_byte)):
            byte = 0
            for n in range(pixels_per_byte):
                byte_offset = x * pixels_per_byte + n
                if byte_offset < image_bytes_len:
                    # If color, each input byte is the index into the color palette -- pack them together
                    byte = byte | ((image_bytes[byte_offset] & (ncolors - 1)) << int(n * shifter))
            bytearray.append(byte)

    return (palette, bytearray)


def generate_font_glyphs_list(no_ascii, unicode_glyphs):
    # The set of glyphs that we want to generate images for
    glyphs = {}

    # Add ascii charset if we haven't explicitly been told to disable it
    if not no_ascii:
        for c in range(0x20, 0x7F):  # does not include 0x7F!
            glyphs[chr(c)] = True

    # Append any extra unicode glyphs
    unicode_glyphs = list(unicode_glyphs)
    for c in unicode_glyphs:
        glyphs[c] = True

    return sorted(glyphs.keys())
