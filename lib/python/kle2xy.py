""" Original code from https://github.com/skullydazed/kle2xy
"""

import hjson
from decimal import Decimal


class KLE2xy(list):
    """Abstract interface for interacting with a KLE layout.
    """
    def __init__(self, layout=None, name='', invert_y=True):
        super(KLE2xy, self).__init__()

        self.name = name
        self.invert_y = invert_y
        self.key_width = Decimal('19.05')
        self.key_skel = {'decal': False, 'border_color': 'none', 'keycap_profile': '', 'keycap_color': 'grey', 'label_color': 'black', 'label_size': 3, 'label_style': 4, 'width': Decimal('1'), 'height': Decimal('1'), 'x': Decimal('0'), 'y': Decimal('0')}
        self.rows = Decimal(0)
        self.columns = Decimal(0)

        if layout:
            self.parse_layout(layout)

    @property
    def width(self):
        """Returns the width of the keyboard plate.
        """
        return (Decimal(self.columns) * self.key_width) + self.key_width / 2

    @property
    def height(self):
        """Returns the height of the keyboard plate.
        """
        return (self.rows * self.key_width) + self.key_width / 2

    @property
    def size(self):
        """Returns the size of the keyboard plate.
        """
        return (self.width, self.height)

    def attrs(self, properties):
        """Parse the keyboard properties dictionary.
        """
        # FIXME: Store more than just the keyboard name.
        if 'name' in properties:
            self.name = properties['name']

    def parse_layout(self, layout):  # noqa  FIXME(skullydazed): flake8 says this has a complexity of 25, it should be refactored.
        # Wrap this in a dictionary so hjson will parse KLE raw data
        layout = '{"layout": [' + layout + ']}'
        layout = hjson.loads(layout)['layout']

        # Initialize our state machine
        current_key = self.key_skel.copy()
        current_row = Decimal(0)
        current_col = Decimal(0)
        current_x = 0
        current_y = self.key_width / 2

        if isinstance(layout[0], dict):
            self.attrs(layout[0])
            layout = layout[1:]

        for row_num, row in enumerate(layout):
            self.append([])

            # Process the current row
            for key in row:
                if isinstance(key, dict):
                    if 'w' in key and key['w'] != Decimal(1):
                        current_key['width'] = Decimal(key['w'])
                    if 'w2' in key and 'h2' in key and key['w2'] == 1.5 and key['h2'] == 1:
                        # FIXME: ISO Key uses these params: {x:0.25,w:1.25,h:2,w2:1.5,h2:1,x2:-0.25}
                        current_key['isoenter'] = True
                    if 'h' in key and key['h'] != Decimal(1):
                        current_key['height'] = Decimal(key['h'])
                    if 'a' in key:
                        current_key['label_style'] = self.key_skel['label_style'] = int(key['a'])
                        if current_key['label_style'] < 0:
                            current_key['label_style'] = 0
                        elif current_key['label_style'] > 9:
                            current_key['label_style'] = 9
                    if 'f' in key:
                        font_size = int(key['f'])
                        if font_size > 9:
                            font_size = 9
                        elif font_size < 1:
                            font_size = 1
                        current_key['label_size'] = self.key_skel['label_size'] = font_size
                    if 'p' in key:
                        current_key['keycap_profile'] = self.key_skel['keycap_profile'] = key['p']
                    if 'c' in key:
                        current_key['keycap_color'] = self.key_skel['keycap_color'] = key['c']
                    if 't' in key:
                        # FIXME: Need to do better validation, plus figure out how to support multiple colors
                        if '\n' in key['t']:
                            key['t'] = key['t'].split('\n')[0]
                        if key['t'] == "0":
                            key['t'] = "#000000"
                        current_key['label_color'] = self.key_skel['label_color'] = key['t']
                    if 'x' in key:
                        current_col += Decimal(key['x'])
                        current_x += Decimal(key['x']) * self.key_width
                    if 'y' in key:
                        current_row += Decimal(key['y'])
                        current_y += Decimal(key['y']) * self.key_width
                    if 'd' in key:
                        current_key['decal'] = True

                else:
                    current_key['name'] = key
                    current_key['row'] = round(current_row, 2)
                    current_key['column'] = round(current_col, 2)

                    # Determine the X center
                    x_center = (current_key['width'] * self.key_width) / 2
                    current_x += x_center
                    current_key['x'] = current_x
                    current_x += x_center

                    # Determine the Y center
                    y_center = (current_key['height'] * self.key_width) / 2
                    y_offset = y_center - (self.key_width / 2)
                    current_key['y'] = (current_y + y_offset)

                    # Tend to our row/col count
                    current_col += current_key['width']
                    if current_col > self.columns:
                        self.columns = current_col

                    # Invert the y-axis if neccesary
                    if self.invert_y:
                        current_key['y'] = -current_key['y']

                    # Store this key
                    self[-1].append(current_key)
                    current_key = self.key_skel.copy()

            # Move to the next row
            current_x = 0
            current_y += self.key_width
            current_col = Decimal(0)
            current_row += Decimal(1)
            if current_row > self.rows:
                self.rows = Decimal(current_row)
