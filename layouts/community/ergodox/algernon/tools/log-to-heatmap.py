#! /usr/bin/env python3
import json
import os
import sys
import re
import argparse
import time

from math import floor
from os.path import dirname
from blessings import Terminal

class Heatmap(object):
    coords = [
        [
            # Row 0
            [ 4,  0], [ 4,  2], [ 2,  0], [ 1,  0], [ 2,  2], [ 3,  0], [ 3,  2],
            [ 3,  4], [ 3,  6], [ 2,  4], [ 1,  2], [ 2,  6], [ 4,  4], [ 4,  6],
        ],
        [
            # Row 1
            [ 8,  0], [ 8,  2], [ 6,  0], [ 5,  0], [ 6,  2], [ 7,  0], [ 7,  2],
            [ 7,  4], [ 7,  6], [ 6,  4], [ 5,  2], [ 6,  6], [ 8,  4], [ 8,  6],
        ],
        [
            # Row 2
            [12,  0], [12,  2], [10,  0], [ 9,  0], [10,  2], [11, 0], [     ],
            [      ], [11,  2], [10,  4], [ 9,  2], [10,  6], [12, 4], [12, 6],
        ],
        [
            # Row 3
            [17,  0], [17,  2], [15,  0], [14,  0], [15,  2], [16,  0], [13,  0],
            [13,  2], [16,  2], [15,  4], [14,  2], [15,  6], [17,  4], [17,  6],
        ],
        [
            # Row 4
            [20,  0], [20,  2], [19,  0], [18,  0], [19,  2], [], [], [], [],
            [19,  4], [18,  2], [19,  6], [20,  4], [20,  6], [], [], [], []
        ],
        [
            # Row 5
            [     ], [23,  0], [22,  2], [22,  0], [22,  4], [21,  0], [21,  2],
            [24, 0], [24,  2], [25,  0], [25,  4], [25,  2], [26,  0], [      ],
        ],
    ]

    def set_attr_at(self, block, n, attr, fn, val):
        blk = self.heatmap[block][n]
        if attr in blk:
            blk[attr] = fn(blk[attr], val)
        else:
            blk[attr] = fn(None, val)

    def coord(self, col, row):
        return self.coords[row][col]

    @staticmethod
    def set_attr(orig, new):
        return new

    def set_bg(self, coords, color):
        (block, n) = coords
        self.set_attr_at(block, n, "c", self.set_attr, color)
        #self.set_attr_at(block, n, "g", self.set_attr, False)

    def set_tap_info(self, coords, count, cap):
        (block, n) = coords
        def _set_tap_info(o, _count, _cap):
            ns = 4 - o.count ("\n")
            return o + "\n" * ns + "%.02f%%" % (float(_count) / float(_cap) * 100)

        if not cap:
            cap = 1
        self.heatmap[block][n + 1] = _set_tap_info (self.heatmap[block][n + 1], count, cap)

    @staticmethod
    def heatmap_color (v):
        colors = [ [0.3, 0.3, 1], [0.3, 1, 0.3], [1, 1, 0.3], [1, 0.3, 0.3]]
        fb = 0
        if v <= 0:
            idx1, idx2 = 0, 0
        elif v >= 1:
            idx1, idx2 = len(colors) - 1, len(colors) - 1
        else:
            val = v * (len(colors) - 1)
            idx1 = int(floor(val))
            idx2 = idx1 + 1
            fb = val - float(idx1)

        r = (colors[idx2][0] - colors[idx1][0]) * fb + colors[idx1][0]
        g = (colors[idx2][1] - colors[idx1][1]) * fb + colors[idx1][1]
        b = (colors[idx2][2] - colors[idx1][2]) * fb + colors[idx1][2]

        r, g, b = [x * 255 for x in (r, g, b)]
        return "#%02x%02x%02x" % (int(r), int(g), int(b))

    def __init__(self, layout):
        self.log = {}
        self.total = 0
        self.max_cnt = 0
        self.layout = layout

    def update_log(self, coords):
        (c, r) = coords
        if not (c, r) in self.log:
            self.log[(c, r)] = 0
        self.log[(c, r)] = self.log[(c, r)] + 1
        self.total = self.total + 1
        if self.max_cnt < self.log[(c, r)]:
            self.max_cnt = self.log[(c, r)]

    def get_heatmap(self):
        with open("%s/heatmap-layout.%s.json" % (dirname(sys.argv[0]), self.layout), "r") as f:
            self.heatmap = json.load (f)

        ## Reset colors
        for row in self.coords:
            for coord in row:
                if coord != []:
                    self.set_bg (coord, "#d9dae0")

        for (c, r) in self.log:
            coords = self.coord(c, r)
            cap = self.max_cnt
            if cap == 0:
                cap = 1
            v = float(self.log[(c, r)]) / cap
            self.set_bg (coords, self.heatmap_color (v))
            self.set_tap_info (coords, self.log[(c, r)], self.total)
        return self.heatmap

    def get_stats(self):
        usage = [
            # left hand
            [0, 0, 0, 0, 0],
            # right hand
            [0, 0, 0, 0, 0]
        ]
        finger_map = [0, 0, 1, 2, 3, 3, 3, 1, 1, 1, 2, 3, 4, 4]
        for (c, r) in self.log:
            if r == 5: # thumb cluster
                if c <= 6: # left side
                    usage[0][4] = usage[0][4] + self.log[(c, r)]
                else:
                    usage[1][0] = usage[1][0] + self.log[(c, r)]
            elif r == 4 and (c == 4 or c == 9): # bottom row thumb keys
                if c <= 6: # left side
                    usage[0][4] = usage[0][4] + self.log[(c, r)]
                else:
                    usage[1][0] = usage[1][0] + self.log[(c, r)]
            else:
                fc = c
                hand = 0
                if fc >= 7:
                    hand = 1
                fm = finger_map[fc]
                usage[hand][fm] = usage[hand][fm] + self.log[(c, r)]
        hand_usage = [0, 0]
        for f in usage[0]:
            hand_usage[0] = hand_usage[0] + f
        for f in usage[1]:
            hand_usage[1] = hand_usage[1] + f

        total = self.total
        if total == 0:
            total = 1
        stats = {
            "total-keys": total,
            "hands": {
                "left": {
                    "usage": round(float(hand_usage[0]) / total * 100, 2),
                    "fingers": {
                        "pinky": 0,
                        "ring": 0,
                        "middle": 0,
                        "index": 0,
                        "thumb": 0,
                    }
                },
                "right": {
                    "usage": round(float(hand_usage[1]) / total * 100, 2),
                    "fingers": {
                        "thumb": 0,
                        "index": 0,
                        "middle": 0,
                        "ring": 0,
                        "pinky": 0,
                    }
                },
            }
        }

        hmap = ['left', 'right']
        fmap = ['pinky', 'ring', 'middle', 'index', 'thumb',
                'thumb', 'index', 'middle', 'ring', 'pinky']
        for hand_idx in range(len(usage)):
            hand = usage[hand_idx]
            for finger_idx in range(len(hand)):
                stats['hands'][hmap[hand_idx]]['fingers'][fmap[finger_idx + hand_idx * 5]] = round(float(hand[finger_idx]) / total * 100, 2)
        return stats

def dump_all(out_dir, heatmaps):
    stats = {}
    t = Terminal()
    t.clear()
    sys.stdout.write("\x1b[2J\x1b[H")

    print ('{t.underline}{outdir}{t.normal}\n'.format(t=t, outdir=out_dir))

    keys = list(heatmaps.keys())
    keys.sort()

    for layer in keys:
        if len(heatmaps[layer].log) == 0:
            continue

        with open ("%s/%s.json" % (out_dir, layer), "w") as f:
            json.dump(heatmaps[layer].get_heatmap(), f)
        stats[layer] = heatmaps[layer].get_stats()

        left = stats[layer]['hands']['left']
        right = stats[layer]['hands']['right']

        print ('{t.bold}{layer}{t.normal} ({total:,} taps):'.format(t=t, layer=layer,
                                                                    total=int(stats[layer]['total-keys'] / 2)))
        print (('{t.underline}        | ' + \
                'left ({l[usage]:6.2f}%)  | ' + \
                'right ({r[usage]:6.2f}%) |{t.normal}').format(t=t, l=left, r=right))
        print ((' {t.bright_magenta}pinky{t.white}  |     {left[pinky]:6.2f}%     |     {right[pinky]:6.2f}%     |\n' + \
                ' {t.bright_cyan}ring{t.white}   |     {left[ring]:6.2f}%     |     {right[ring]:6.2f}%     |\n' + \
                ' {t.bright_blue}middle{t.white} |     {left[middle]:6.2f}%     |     {right[middle]:6.2f}%     |\n' + \
                ' {t.bright_green}index{t.white}  |     {left[index]:6.2f}%     |     {right[index]:6.2f}%     |\n' + \
                ' {t.bright_red}thumb{t.white}  |     {left[thumb]:6.2f}%     |     {right[thumb]:6.2f}%     |\n' + \
                '').format(left=left['fingers'], right=right['fingers'], t=t))

def process_line(line, heatmaps, opts, stamped_log = None):
    m = re.search ('KL: col=(\d+), row=(\d+), pressed=(\d+), layer=(.*)', line)
    if not m:
        return False
    if stamped_log is not None:
        if line.startswith("KL:"):
            print ("%10.10f %s" % (time.time(), line),
                   file = stamped_log, end = '')
        else:
            print (line,
                   file = stamped_log, end = '')
        stamped_log.flush()

    (c, r, l) = (int(m.group (2)), int(m.group (1)), m.group (4))
    if (c, r) not in opts.allowed_keys:
        return False

    heatmaps[l].update_log ((c, r))

    return True

def setup_allowed_keys(opts):
    if len(opts.only_key):
        incmap={}
        for v in opts.only_key:
            m = re.search ('(\d+),(\d+)', v)
            if not m:
                continue
            (c, r) = (int(m.group(1)), int(m.group(2)))
            incmap[(c, r)] = True
    else:
        incmap={}
        for r in range(0, 6):
            for c in range(0, 14):
                incmap[(c, r)] = True

        for v in opts.ignore_key:
            m = re.search ('(\d+),(\d+)', v)
            if not m:
                continue
            (c, r) = (int(m.group(1)), int(m.group(2)))
            del(incmap[(c, r)])

    return incmap

def main(opts):
    heatmaps = {"Dvorak": Heatmap("Dvorak"),
                "ADORE": Heatmap("ADORE")
    }
    cnt = 0
    out_dir = opts.outdir

    if not os.path.exists(out_dir):
        os.makedirs(out_dir)

    opts.allowed_keys = setup_allowed_keys(opts)

    if not opts.one_shot:

        try:
            with open("%s/stamped-log" % out_dir, "r") as f:
                while True:
                    line = f.readline()
                    if not line:
                        break
                    if not process_line(line, heatmaps, opts):
                        continue
        except Exception:
            pass

        stamped_log = open ("%s/stamped-log" % (out_dir), "a+")
    else:
        stamped_log = None

    while True:
        line = sys.stdin.readline()
        if not line:
            break
        if not process_line(line, heatmaps, opts, stamped_log):
            continue

        cnt = cnt + 1

        if opts.dump_interval != -1 and cnt >= opts.dump_interval and not opts.one_shot:
            cnt = 0
            dump_all(out_dir, heatmaps)

    dump_all (out_dir, heatmaps)

if __name__ == "__main__":
    parser = argparse.ArgumentParser (description = "keylog to heatmap processor")
    parser.add_argument ('outdir', action = 'store',
                         help = 'Output directory')
    parser.add_argument ('--dump-interval', dest = 'dump_interval', action = 'store', type = int,
                         default = 100, help = 'Dump stats and heatmap at every Nth event, -1 for dumping at EOF only')
    parser.add_argument ('--ignore-key', dest = 'ignore_key', action = 'append', type = str,
                         default = [], help = 'Ignore the key at position (x, y)')
    parser.add_argument ('--only-key', dest = 'only_key', action = 'append', type = str,
                         default = [], help = 'Only include key at position (x, y)')
    parser.add_argument ('--one-shot', dest = 'one_shot', action = 'store_true',
                         help = 'Do not load previous data, and do not update it, either.')
    args = parser.parse_args()
    if len(args.ignore_key) and len(args.only_key):
        print ("--ignore-key and --only-key are mutually exclusive, please only use one of them!",
               file = sys.stderr)
        sys.exit(1)
    main(args)
