"""This script tests QGF functionality.
"""
import re
import datetime
from io import BytesIO
from qmk.path import normpath
from qmk.painter import render_header, render_source, render_license, render_bytes, valid_formats
from milc import cli
from PIL import Image


@cli.argument('-v', '--verbose', arg_only=True, action='store_true', help='Turns on verbose output.')
@cli.argument('-i', '--input', required=True, help='Specify input graphic file.')
@cli.argument('-o', '--output', default='', help='Specify output directory. Defaults to same directory as input.')
@cli.argument('-f', '--format', required=True, help='Output format, valid types: %s' % (', '.join(valid_formats.keys())))
@cli.argument('-r', '--no-rle', arg_only=True, action='store_true', help='Disables the use of RLE when encoding images.')
@cli.argument('-d', '--no-deltas', arg_only=True, action='store_true', help='Disables the use of delta frames when encoding animations.')
@cli.subcommand('Converts an input image to something QMK understands')
def painter_convert_graphics(cli):
    """Converts an image file to a format that Quantum Painter understands.

    This command uses the `qmk.painter` module to generate a Quantum Painter image defintion from an image. The generated definitions are written to a files next to the input -- `INPUT.c` and `INPUT.h`.
    """
    # Work out the input file
    if cli.args.input != '-':
        cli.args.input = normpath(cli.args.input)

        # Error checking
        if not cli.args.input.exists():
            cli.log.error('Input image file does not exist!')
            cli.print_usage()
            return False

    # Work out the output directory
    if len(cli.args.output) == 0:
        cli.args.output = cli.args.input.parent
    cli.args.output = normpath(cli.args.output)

    # Ensure we have a valid format
    if cli.args.format not in valid_formats.keys():
        cli.log.error('Output format %s is invalid. Allowed values: %s' % (cli.args.format, ', '.join(valid_formats.keys())))
        cli.print_usage()
        return False

    # Work out the encoding parameters
    format = valid_formats[cli.args.format]

    # Load the input image
    input_img = Image.open(cli.args.input)

    # Convert the image to QGF using PIL
    out_data = BytesIO()
    input_img.save(out_data, "QGF", use_deltas=(not cli.args.no_deltas), use_rle=(not cli.args.no_rle), qmk_format=format, verbose=cli.args.verbose)
    out_bytes = out_data.getvalue()

    # Work out the text substitutions for rendering the output data
    subs = {
        'generated_type': 'image',
        'var_prefix': 'gfx',
        'generator_command': f'qmk painter-convert-graphics -i {cli.args.input.name} -f {cli.args.format}',
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
    header_file = cli.args.output / (cli.args.input.stem + ".qgf.h")
    with open(header_file, 'w') as header:
        print(f"Writing {header_file}...")
        header.write(header_text)
        header.close()

    # Render and write the source file
    source_text = render_source(subs)
    source_file = cli.args.output / (cli.args.input.stem + ".qgf.c")
    with open(source_file, 'w') as source:
        print(f"Writing {source_file}...")
        source.write(source_text)
        source.close()
