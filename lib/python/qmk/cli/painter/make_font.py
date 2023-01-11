"""This script automates the conversion of font files into a format QMK firmware understands.
"""

import re
import datetime
from io import BytesIO
from qmk.path import normpath
from qmk.painter_qff import QFFFont
from qmk.painter import render_header, render_source, render_license, render_bytes, valid_formats
from milc import cli


@cli.argument('-f', '--font', required=True, help='Specify input font file.')
@cli.argument('-o', '--output', required=True, help='Specify output image path.')
@cli.argument('-s', '--size', default=12, help='Specify font size. Default 12.')
@cli.argument('-n', '--no-ascii', arg_only=True, action='store_true', help='Disables output of the full ASCII character set (0x20..0x7E), exporting only the glyphs specified.')
@cli.argument('-u', '--unicode-glyphs', default='', help='Also generate the specified unicode glyphs.')
@cli.argument('-a', '--no-aa', arg_only=True, action='store_true', help='Disable anti-aliasing on fonts.')
@cli.subcommand('Converts an input font to something QMK understands')
def painter_make_font_image(cli):
    # Create the font object
    font = QFFFont(cli)
    # Read from the input file
    cli.args.font = normpath(cli.args.font)
    font.generate_image(cli.args.font, cli.args.size, include_ascii_glyphs=(not cli.args.no_ascii), unicode_glyphs=cli.args.unicode_glyphs, use_aa=(False if cli.args.no_aa else True))
    # Render out the data
    font.save_to_image(normpath(cli.args.output))


@cli.argument('-i', '--input', help='Specify input graphic file.')
@cli.argument('-o', '--output', default='', help='Specify output directory. Defaults to same directory as input.')
@cli.argument('-n', '--no-ascii', arg_only=True, action='store_true', help='Disables output of the full ASCII character set (0x20..0x7E), exporting only the glyphs specified.')
@cli.argument('-u', '--unicode-glyphs', default='', help='Also generate the specified unicode glyphs.')
@cli.argument('-f', '--format', required=True, help='Output format, valid types: %s' % (', '.join(valid_formats.keys())))
@cli.argument('-r', '--no-rle', arg_only=True, action='store_true', help='Disable the use of RLE to minimise converted image size.')
@cli.argument('-w', '--raw', arg_only=True, action='store_true', help='Writes out the QFF file as raw data instead of c/h combo.')
@cli.subcommand('Converts an input font image to something QMK firmware understands')
def painter_convert_font_image(cli):
    # Work out the format
    format = valid_formats[cli.args.format]

    # Create the font object
    font = QFFFont(cli.log)

    # Read from the input file
    cli.args.input = normpath(cli.args.input)
    font.read_from_image(cli.args.input, include_ascii_glyphs=(not cli.args.no_ascii), unicode_glyphs=cli.args.unicode_glyphs)

    # Work out the output directory
    if len(cli.args.output) == 0:
        cli.args.output = cli.args.input.parent
    cli.args.output = normpath(cli.args.output)

    # Render out the data
    out_data = BytesIO()
    font.save_to_qff(format, (False if cli.args.no_rle else True), out_data)
    out_bytes = out_data.getvalue()

    if cli.args.raw:
        raw_file = cli.args.output / (cli.args.input.stem + ".qff")
        with open(raw_file, 'wb') as raw:
            raw.write(out_bytes)
        return

    # Work out the text substitutions for rendering the output data
    subs = {
        'generated_type': 'font',
        'var_prefix': 'font',
        'generator_command': f'qmk painter-convert-font-image -i {cli.args.input.name} -f {cli.args.format}',
        'year': datetime.date.today().strftime("%Y"),
        'input_file': cli.args.input.name,
        'sane_name': re.sub(r"[^a-zA-Z0-9]", "_", cli.args.input.stem),
        'byte_count': len(out_bytes),
        'bytes_lines': render_bytes(out_bytes),
        'format': cli.args.format,
    }

    # Render the license
    subs.update({'license': render_license(subs)})

    # Render and write the header file
    header_text = render_header(subs)
    header_file = cli.args.output / (cli.args.input.stem + ".qff.h")
    with open(header_file, 'w') as header:
        print(f"Writing {header_file}...")
        header.write(header_text)
        header.close()

    # Render and write the source file
    source_text = render_source(subs)
    source_file = cli.args.output / (cli.args.input.stem + ".qff.c")
    with open(source_file, 'w') as source:
        print(f"Writing {source_file}...")
        source.write(source_text)
        source.close()
