"""This script automates the conversion of font files into a format QMK firmware understands.
"""

from io import BytesIO
from qmk.path import normpath
from qmk.painter_qff import _generate_font_glyphs_list, QFFFont
from qmk.painter import generate_subs, render_header, render_source, valid_formats
from milc import cli


def _font_to_image(cli, output):
    """
    This function converts a font, eg .ttf, into an image, eg .png

    Uses cli to work out how to make the conversion, and writes to the provided file
    """

    # Create the font object
    font = QFFFont(cli)
    # Read from the input file
    font.generate_image(
        normpath(cli.args.input),
        cli.args.size,
        include_ascii_glyphs=not cli.args.no_ascii,
        unicode_glyphs=cli.args.unicode_glyphs,
        use_aa=not cli.args.no_aa,
    )
    # Render out the data
    font.save_to_image(output)


def _image_to_qff(cli, input_):
    """
    This function converts an image, eg .png, into its QFF representation

    Uses cli to work out how to make the conversion, and reads from the provided file
    """

    # Work out the format
    format = valid_formats[cli.args.format]

    # Create the font object
    font = QFFFont(cli.log)

    # Read from the input
    font.read_from_image(input_, include_ascii_glyphs=(not cli.args.no_ascii), unicode_glyphs=cli.args.unicode_glyphs)

    # Render out the data
    out_data = BytesIO()
    font.save_to_qff(format, not cli.args.no_rle, out_data)
    out_bytes = out_data.getvalue()

    if cli.args.raw:
        raw_file = cli.args.output / f"{cli.args.input.stem}.qff"
        with open(raw_file, 'wb') as raw:
            raw.write(out_bytes)
        return

    # Work out the text substitutions for rendering the output data
    metadata = {"glyphs": _generate_font_glyphs_list(not cli.args.no_ascii, cli.args.unicode_glyphs)}
    subs = generate_subs(cli, out_bytes, font_metadata=metadata)

    # Render and write the header file
    header_text = render_header(subs)
    header_file = cli.args.output / f"{cli.args.input.stem}.qff.h"
    with open(header_file, 'w') as header:
        print(f"Writing {header_file} ...")
        header.write(header_text)

    # Render and write the source file
    source_text = render_source(subs)
    source_file = cli.args.output / f"{cli.args.input.stem}.qff.c"
    with open(source_file, 'w') as source:
        print(f"Writing {source_file} ...")
        source.write(source_text)


def _sanitize_paths(cli):
    cli.args.input = normpath(cli.args.input)
    if len(cli.args.output) == 0:
        cli.args.output = cli.args.input.parent
    cli.args.output = normpath(cli.args.output)


@cli.argument('-i', '--input', required=True, help='Specify input font file.')
@cli.argument('-o', '--output', required=True, help='Specify output image path.')
@cli.argument('-s', '--size', default=12, help='Specify font size. Default 12.')
@cli.argument('-n', '--no-ascii', arg_only=True, action='store_true', help='Disables output of the full ASCII character set (0x20..0x7E), exporting only the glyphs specified.')
@cli.argument('-u', '--unicode-glyphs', default='', help='Also generate the specified unicode glyphs.')
@cli.argument('-a', '--no-aa', arg_only=True, action='store_true', help='Disable anti-aliasing on fonts.')
@cli.subcommand('Converts an input font to something QMK understands')
def painter_make_font_image(cli):
    _sanitize_paths(cli)
    _font_to_image(cli, cli.args.output)
    print(f"Writing {cli.args.output} ...")



@cli.argument('-i', '--input', help='Specify input graphic file.')
@cli.argument('-o', '--output', default='', help='Specify output directory. Defaults to same directory as input.')
@cli.argument('-n', '--no-ascii', arg_only=True, action='store_true', help='Disables output of the full ASCII character set (0x20..0x7E), exporting only the glyphs specified.')
@cli.argument('-u', '--unicode-glyphs', default='', help='Also generate the specified unicode glyphs.')
@cli.argument('-f', '--format', required=True, help=f"Output format, valid types: {', '.join(valid_formats.keys())}")
@cli.argument('-r', '--no-rle', arg_only=True, action='store_true', help='Disable the use of RLE to minimise converted image size.')
@cli.argument('-w', '--raw', arg_only=True, action='store_true', help='Writes out the QFF file as raw data instead of c/h combo.')
@cli.subcommand('Converts an input font image to something QMK firmware understands')
def painter_convert_font_image(cli):
    _sanitize_paths(cli)
    _image_to_qff(cli, cli.args.input)


@cli.argument('-a', '--no-aa', arg_only=True, action='store_true', help='Disable anti-aliasing on fonts.')
@cli.argument('-n', '--no-ascii', arg_only=True, action='store_true', help='Disables output of the full ASCII character set (0x20..0x7E), exporting only the glyphs specified.')
@cli.argument('-r', '--no-rle', arg_only=True, action='store_true', help='Disable the use of RLE to minimise converted image size.')
@cli.argument('-f', '--format', required=True, help=f"Output format, valid types: {', '.join(valid_formats.keys())}")
@cli.argument('-i', '--input', help='Specify input font file.')
@cli.argument('-o', '--output', default='', help='Specify output directory. Defaults to same directory as input.')
@cli.argument('-s', '--size', default=12, help='Specify font size. Default 12.')
@cli.argument('-u', '--unicode-glyphs', default='', help='Also generate the specified unicode glyphs.')
@cli.argument('-w', '--raw', arg_only=True, action='store_true', help='Writes out the QFF file as raw data instead of c/h combo.')
@cli.subcommand('Converts an input font file to something QMK firmware understands')
def painter_convert_font(cli):
    _sanitize_paths(cli)

    with BytesIO() as file:
        _font_to_image(cli, file)
        _image_to_qff(cli, file)
