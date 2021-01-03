"""Functions to convert to and from QMK formats
"""
from pprint import pprint

from milc import cli


def kle2qmk(kle):
    """Convert a KLE layout to QMK's layout format.
    """
    layout = []
    layout_alternatives = {}
    top_left_corner = None

    # Iterate through the KLE classifying keys by layout
    for row in kle:
        for key in row:
            if key['decal']:
                continue

            if key['label_style'] in [0, 4]:
                matrix, _, _, alt_layout, layout_name, _, keycode = key['name'].split('\n')
            else:
                cli.log.error('Unknown label style: %s', key['label_style'])
                continue

            matrix = list(map(int, matrix.split(',', 1)))

            qmk_key = {
                'label': keycode,
                'x': key['column'],
                'y': key['row'],
                'matrix': matrix,
            }

            if not top_left_corner and (not alt_layout or alt_layout.endswith(',0')):
                top_left_corner = key['column'], key['row']

            # Figure out what layout this key is part of
            # FIXME(skullydazed): In the future this will populate `layout_options` in info.json
            if alt_layout:
                alt_group, layout_index = map(int, alt_layout.split(',', 1))
                if layout_index != 0:
                    continue

            # Set the key size
            if key['width'] != 1:
                qmk_key['w'] = key['width']
            if key['height'] != 1:
                qmk_key['h'] = key['height']

            layout.append(qmk_key)

    # Adjust the keys to account for the top-left corner
    for key in layout:
        key['x'] -= top_left_corner[0]
        key['y'] -= top_left_corner[1]

    return layout
