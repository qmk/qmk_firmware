"""Functions to convert to and from QMK formats
"""
from collections import OrderedDict


def kle2qmk(kle):
    """Convert a KLE layout to QMK's layout format.
    """
    layout = []

    for row in kle:
        for key in row:
            if key['decal']:
                continue

            qmk_key = OrderedDict(
                label="",
                x=key['column'],
                y=key['row'],
            )

            if key['width'] != 1:
                qmk_key['w'] = key['width']
            if key['height'] != 1:
                qmk_key['h'] = key['height']
            if 'r' in key and key['r'] != 0:
                qmk_key['r'] = key['r'];
                qmk_key['rx'] = key.get('rx', 0);
                qmk_key['ry'] = key.get('ry', 0);
            if 'name' in key and key['name']:
                qmk_key['label'] = key['name'].split('\n', 1)[0]
            else:
                del (qmk_key['label'])

            layout.append(qmk_key)

    return layout
