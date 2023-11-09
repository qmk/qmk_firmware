from enum import IntFlag, auto
from math import ceil


class BoxChar(IntFlag):
    LEFT = auto()
    RIGHT = auto()
    UP = auto()
    DOWN = auto()


CHARSET_ASCII = '   - \'\'- ..-|||+'
CHARSET_UNICODE = '   ─ ┘└┴ ┐┌┬│┤├┼'


class LayoutRenderer():
    def __init__(self, layout, use_ascii=False, legends='label'):
        self._layout = layout
        self._legends = legends
        self._charset = CHARSET_ASCII if use_ascii else CHARSET_UNICODE

        width = max([key.get('x', 0) + key.get('w', 1) for key in layout])
        height = max([key.get('y', 0) + key.get('h', 1) for key in layout])

        canvas_width = ceil(width * 4) + 1
        canvas_height = ceil(height * 2) + 1
        self._canvas = [[' '] * canvas_width for _ in range(canvas_height)]

    def _render(self, x, y, val):
        if type(self._canvas[y][x]) is BoxChar and type(val) is BoxChar:
            self._canvas[y][x] |= val
        else:
            self._canvas[y][x] = val

    def _render_key_rect(self, left, top, right, bottom):
        # Top left corner
        self._render(left, top, BoxChar.RIGHT | BoxChar.DOWN)
        # Top right corner
        self._render(right, top, BoxChar.LEFT | BoxChar.DOWN)
        # Bottom left corner
        self._render(left, bottom, BoxChar.RIGHT | BoxChar.UP)
        # Bottom right corner
        self._render(right, bottom, BoxChar.LEFT | BoxChar.UP)

        # Top and bottom
        for i in range(left + 1, right):
            self._render(i, top, BoxChar.LEFT | BoxChar.RIGHT)
            self._render(i, bottom, BoxChar.LEFT | BoxChar.RIGHT)

        # Left and right
        for i in range(top + 1, bottom):
            self._render(left, i, BoxChar.UP | BoxChar.DOWN)
            self._render(right, i, BoxChar.UP | BoxChar.DOWN)

    def _render_key_nonrect(self, left_top, left_bottom, top, right, bottom):
        # Top left corner
        self._render(left_top, top, BoxChar.RIGHT | BoxChar.DOWN)
        # Top right corner
        self._render(right, top, BoxChar.LEFT | BoxChar.DOWN)
        # Bottom left corner
        self._render(left_bottom, bottom, BoxChar.RIGHT | BoxChar.UP)
        # Bottom right corner
        self._render(right, bottom, BoxChar.LEFT | BoxChar.UP)

        # Top
        for i in range(left_top + 1, right):
            self._render(i, top, BoxChar.LEFT | BoxChar.RIGHT)
        # Bottom
        for i in range(left_bottom + 1, right):
            self._render(i, bottom, BoxChar.LEFT | BoxChar.RIGHT)

        # Step
        self._render(right, top + 2, BoxChar.UP | BoxChar.DOWN)
        self._render(left_top, top + 2, BoxChar.UP)
        self._render(left_bottom, top + 2, BoxChar.DOWN)
        if left_top != left_bottom:
            self._render(left_top, top + 2, BoxChar.RIGHT if left_top < left_bottom else BoxChar.LEFT)
            self._render(left_bottom, top + 2, BoxChar.RIGHT if left_top > left_bottom else BoxChar.LEFT)

        offset = abs(left_top - left_bottom) - 1
        leftmost = min(left_top, left_bottom)
        for i in range(offset):
            self._render(leftmost + i + 1, top + 2, BoxChar.LEFT | BoxChar.RIGHT)

        # Left and right
        self._render(left_top, top + 1, BoxChar.UP | BoxChar.DOWN)
        self._render(right, top + 1, BoxChar.UP | BoxChar.DOWN)
        self._render(left_bottom, top + 3, BoxChar.UP | BoxChar.DOWN)
        self._render(right, top + 3, BoxChar.UP | BoxChar.DOWN)

    def _render_key_legend(self, left, top, length, legend):
        legend_centered = legend.center(length)

        for i in range(length):
            self._render(left + 1 + i, top + 1, legend_centered[i])

    def _render_key(self, key, index):
        x = key.get('x', 0)
        y = key.get('y', 0)
        w = key.get('w', 1)
        h = key.get('h', 1)
        matrix = key.get('matrix')

        canvas_left = ceil(x * 4)
        canvas_top = ceil(y * 2)
        canvas_right = canvas_left + ceil(w * 4)
        canvas_bottom = canvas_top + ceil(h * 2)

        if self._legends == 'matrix' and matrix is not None:
            legend = f'{matrix[0]},{matrix[1]}'
        elif self._legends == 'index':
            legend = f'{index}'
        elif self._legends == 'width':
            legend = f'{w}'
        else:
            legend = key.get('label', '')

        legend_length = ceil(w * 4) - 1

        if x >= 0.25 and w == 1.25 and h == 2:
            # ISO Enter
            self._render_key_nonrect(canvas_left - 1, canvas_left, canvas_top, canvas_right, canvas_bottom)
            self._render_key_legend(canvas_left - 1, canvas_top, legend_length + 1, legend)
        elif w == 1.5 and h == 2:
            # Big Enter
            self._render_key_nonrect(canvas_left, canvas_left - 3, canvas_top, canvas_right, canvas_bottom)
            self._render_key_legend(canvas_left - 3, canvas_top + 2, legend_length, legend)
        else:
            self._render_key_rect(canvas_left, canvas_top, canvas_right, canvas_bottom)
            if h >= 1 and w >= 0.25:
                self._render_key_legend(canvas_left, canvas_top, legend_length, legend)

    def __str__(self):
        for index, key in enumerate(self._layout):
            self._render_key(key, index)

        canvas_rows = []
        for row in self._canvas:
            row_str = ''
            for col in row:
                if type(col) is str:
                    row_str += col
                else:
                    row_str += self._charset[col]
            canvas_rows.append(row_str)

        return '\n'.join(canvas_rows)
