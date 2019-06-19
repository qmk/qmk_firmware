#!/bin/env python
"""Parse RawData from KeyboardLayoutGenerator and generate RGB position matrix."""

import argparse
import sys
import json
import re

class Key:
    """Define key class."""
    ORIGIN_CENTER = 1
    ORIGIN_TOP_LEFT = 2
    ORIGIN_BOTTOM_RIGHT = 3

    def __init__(self, label, x=0.0, y=0.0, w=1.0, h=1.0, origin=None):
        """Init key."""
        self.x = x
        self.y = y
        self.w = w
        self.h = h
        self.label = label
        self.origin = origin if origin else self.ORIGIN_CENTER

    @property
    def origin_x(self):
        """Calculate X origin ."""
        if self.origin == self.ORIGIN_CENTER:
            value = self.x + (self.w / 2.0)
        elif self.origin == self.ORIGIN_TOP_LEFT:
            value = self.x
        elif self.origin == self.ORIGIN_BOTTOM_RIGHT:
            value = self.x + self.w

        return value

    @property
    def origin_y(self):
        """Calculate Y origin ."""
        if self.origin == self.ORIGIN_CENTER:
            value = self.y + (self.h / 2.0)
        elif self.origin == self.ORIGIN_TOP_LEFT:
            value = self.y
        elif self.origin == self.ORIGIN_BOTTOM_RIGHT:
            value = self.y + self.h

        return value

    def __str__(self):
        """.Dump out string"""
        return u"{0.x}, {0.y}   {0.w}, {0.h}".format(self)

    def get_matrix_position(self, width, height):
        """Calculate x/y."""
        return [self.origin_x * width, self.origin_y * height]

def get_key(row, x=0.0, y=0.0, origin=Key.ORIGIN_CENTER):
    """Column iterator for kle data."""
    w = 1.0
    h = 1.0

    for i in row:
        if isinstance(i, unicode):
            k = Key(i, x, y, w, h, origin)
            x += w
            w = 1.0
            h = 1.0
            yield k
        elif isinstance(i, dict):
            if "w" in i:
                w = i["w"]
            if "h" in i:
                h = i["h"]
            if "y" in i:
                y += i["y"]
            if "x" in i:
                x += i["x"]


class Keyboard:
    """Define keyboard."""
    def __init__(self, data, origin=Key.ORIGIN_CENTER):
        """Init keyboard."""
        self.rows = []
        self.width = 0.0
        self.height = 0.0
        self.origin = origin
        self.columns = 0

        y = 0.0
        for row in data:
            x = 0.0
            key_row=[]
            c = 0
            for key in get_key(row, x=x, y=y, origin=self.origin):
                c += 1
                if (key.x + key.w) > self.width:
                    self.width = key.x + key.w

                if (key.y + key.h) > self.height:
                    self.height = key.y + key.h

                if key.y > y:
                    y = key.y

                key_row.append(key)
            if c > self.columns:
                self.columns = c
            self.rows.append(key_row)
            y += 1.0


    def __len__(self):
        """Count keys."""
        return sum([len(x) for x in self.rows])

    def get_matrix_positions(self, width, height):
        """Generate list of lists."""
        cellx = float(width) / (self.width - 1.0)
        celly = float(height) / (self.height - 1.0)
        rows = []
        for r in self.rows:
            row = []
            for c in r:
                x, y = c.get_matrix_position(cellx, celly)
                if self.origin == Key.ORIGIN_CENTER:
                    row.append([int((x-(cellx/2))+0.5), int((y-(celly/2))+0.5)])
                elif self.origin == Key.ORIGIN_TOP_LEFT:
                    row.append([int(x+0.5), int(y+0.5)])
                elif self.origin == Key.ORIGIN_BOTTOM_RIGHT:
                    row.append([int((x-cellx)+0.5), int((y-celly)+0.5)])
            rows.append(row)

        return rows

def as_cpp(pos):
    """Format as cpp header."""
    return "{{ {0:3}, {1:3} }},".format(*pos)

def main():# pylint: disable=R0914,R0915,R1260
    """Do main function."""
    parser = argparse.ArgumentParser(
        description=__doc__,
        formatter_class=argparse.ArgumentDefaultsHelpFormatter
    )

    parser.add_argument(
        "path",
        type=str,
        nargs="*",
        default=[],
        help="Path to rawdata, read stdin otherwise."
    )

    parser.add_argument(
        "--width",
        type=int,
        default=224,
        action="store",
        help="Structure max X."
    )

    parser.add_argument(
        "--height",
        type=int,
        default=64,
        action="store",
        help="Structure max Y."
    )

    parser.add_argument(
        "--origin",
        choices=[
            "CENTER",
            "TOP_LEFT",
            "BOTTOM_RIGHT",
        ],
        help="Origin of key, for positioning",
        default="CENTER"
    )

    parser.add_argument(
        "-d", "--debug",
        default=False,
        action="store_true",
        help="Debug mode."
    )

    args = parser.parse_args()

    data = ""

    if args.path:
        with open(args.path[0], "r") as o:
            data = o.read()
    else:
        # try stdin
        while True:
            try:
                line = sys.stdin.readline()
            except KeyboardInterrupt:
                break

            if not line:
                break

            line = line.strip()

            if line:
                data += line

    # massage into JSON.. WHY doesn't KLE use JSON!
    data = re.sub("([a-z0-9]+):", "\"\\1\":", data)

    data = json.loads("[" + data + "]")
    if args.debug:
        for d in data:
            print d

    if args.origin == "CENTER":
        origin = Key.ORIGIN_CENTER
    elif args.origin == "TOP_LEFT":
        origin = Key.ORIGIN_TOP_LEFT
    elif args.origin == "BOTTOM_RIGHT":
        origin = Key.ORIGIN_BOTTOM_RIGHT
    kb = Keyboard(data, origin)

    print "Keyboard dimension:", kb.width, "x", kb.height
    print "Keyboard key count:", len(kb)
    print
    row_i = 0
    print "        ",
    for c in range(kb.columns):
        print "/* {0:^7} */".format(c),
    print
    for r in kb.get_matrix_positions(args.width, args.height):
        print "/* {0:2} */".format(row_i),
        for c in r:
            print as_cpp(c),
        print
        row_i += 1

    return 0

if __name__ == "__main__":
    sys.exit(main())
