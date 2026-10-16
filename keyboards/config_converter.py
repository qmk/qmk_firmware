#!/usr/bin/env python
# -*- coding:utf-8 -*-

import os
import sys
import re


def red(string):
    return '\033[31m' + string + '\033[0m'


def yellow(string):
    return '\033[33m' + string + '\033[0m'


def green(string):
    return '\033[32m' + string + '\033[0m'


class ConfigConverter:
    PIN_TABLE = {'D3': 1, 'D2': 2, 'D1': 5, 'D0': 6, 'D4': 7, 'C6': 8, 'D7': 9, 'E6': 10, 'B4': 11,
                 'B5': 12, 'B6': 13, 'B2': 14, 'B3': 15, 'B1': 16, 'F7': 17, 'F6': 18, 'F5': 19, 'F4': 20}

    def __init__(self):
        self.is_split = False
        self.vid = ''
        self.pid = ''
        self.name = ''
        self.manufacture = ''
        self.description = ''
        self.row_num = ''
        self.col_num = ''
        self.row_pins = ''
        self.col_pins = ''
        self.row_pins_right = ''
        self.col_pins_right = ''
        self.layout = ''
        self.led_pin = ''
        self.led_num = ''
        self.diode_direction = ''
        self.mode = ''
        self.layout_macro = []
        self.search_layout = ''

    def find_layout_macro(self, f):
        lines = f.readlines()
        layout_detect = False
        layout_str = ''
        line = 1
        for string in lines:
            string = self.remove_comment(string)
            layout_name = re.match(
                r'^\s*#\s*define\s+LAYOUT[^\r\n\t\f\v \\]*\s*', string)
            if layout_name is not None:
                layout_name = layout_name.group().split("#define")[1]
                layout_name = layout_name.replace('(', '')
                layout_name = layout_name.strip()
                file_name = f.name
                if 'keyboards/' in file_name:
                    file_name = file_name.split('keyboards/')[1]
                self.layout_macro.append(
                    {"name": layout_name, "file": file_name, "line": line})
            line = line + 1

    def set_layout_index(self, idx):
        idx = int(idx)
        if idx >= len(self.layout_macro):
            raise ValueError

        self.search_layout = self.layout_macro[idx]["name"]

    def print_layout_list(self):
        index = 0
        for layout in self.layout_macro:
            print(
                f'{index}: {layout["name"]}\t\t{layout["file"]}:{layout["line"]}')
            index = index + 1

    def convert_pindef(self, arg):
        str2 = arg.split('{')[1]
        str2 = re.sub(r'(\(|{|})', '', str2)
        str2 = str2.replace(' ', '')
        str2 = str2.replace('\n', '')
        str2 = str2.replace('\r', '')

        pin_array = []
        for pin in str2.split(','):
            if pin == '':
                continue
            if 'PIN' in pin:
                pin_array.append(pin.replace('PIN', ''))
            else:
                pin_array.append(self.PIN_TABLE[pin])
        pin_str = str(pin_array)

        return pin_str

    def convert_layout(self, arg):
        # remove "#define LAYOUTxxx(" from arg
        str2 = re.sub(r'(\(|{|})', '', arg)
        str2 = str2.replace('#define', '')
        str2 = str2.replace(self.search_layout, '')
        str2 = str2.replace(' ', '')

        # split layout macro to "LAYOUT macro" arguments and array definition
        # place = "R00, R01\nL01, L00"
        # array = "R00, R01, L00, L01"
        [place, array] = str2.split(')')

        # remove spaces
        array = array.replace('\n', '')
        array = array.replace('\r', '')
        array = array.replace('\t', '')
        array = array.replace('\\', '')
        place = place.replace('\r', '')
        place = place.replace('\t', '')
        place = place.replace('\\', '')

        array = array.split(',')

        # pick up a element from LAYOUT macro arguments and find it from array
        layout = []
        for row in place.split('\n'):
            if row == '':
                continue
            for key in row.split(','):
                if key == '':
                    continue
                idx = array.index(key)
                layout.append(idx + 1)
            layout.append(0)

        layout_str = str(layout)
        layout_str = layout_str.replace(' 0,', ' 0,\n')
        layout_str = layout_str.replace(', 0]', ']')

        return layout_str

    def waring_multiple_definition(self, symbol, f, line):
        print(yellow('warning') +
              f': multiple definition of {symbol} in {f.name}:{line}. Previous definition is used.')

    def remove_comment(self, arg):
        return arg.split('//')[0]

    def parse_file(self, f):
        cform = f.readlines()
        layout_detect = False
        layout_str = ''
        line = 0
        for string in cform:
            line = line + 1
            string = self.remove_comment(string)
            if 'VENDOR_ID' in string:
                self.vid = string.split('VENDOR_ID')[
                    1].replace('\n', '').strip()
            elif 'PRODUCT_ID' in string:
                self.pid = string.split('PRODUCT_ID')[
                    1].replace('\n', '').strip()
            elif 'MANUFACTURER' in string:
                self.manufacture = string.split('MANUFACTURER')[
                    1].replace('\n', '').strip()
            elif 'PRODUCT' in string:
                self.name = string.split('PRODUCT')[
                    1].replace('\n', '').strip()
            elif 'DESCRIPTION' in string:
                self.description = string.split('DESCRIPTION')[
                    1].replace('\n', '').strip()
            elif re.match(r'\s*#\s*define\s+MATRIX_ROWS\s', string):
                if self.row_num != '':
                    self.waring_multiple_definition('MATRIX_ROWS', f, line)
                else:
                    self.row_num = string.split('MATRIX_ROWS')[
                        1].replace('\n', '').strip()
            elif re.match(r'\s*#\s*define\s+MATRIX_COLS\s', string):
                if self.col_num != '':
                    self.waring_multiple_definition('MATRIX_COLS', f, line)
                else:
                    self.col_num = string.split('MATRIX_COLS')[
                        1].replace('\n', '').strip()
            elif re.match(r'\s*#\s*define\s+MATRIX_ROW_PINS\s', string):
                if self.row_pins != '':
                    self.waring_multiple_definition('MATRIX_ROW_PINS', f, line)
                else:
                    self.row_pins = self.convert_pindef(string)
            elif re.match(r'\s*#\s*define\s+MATRIX_COL_PINS\s', string):
                if self.col_pins != '':
                    self.waring_multiple_definition('MATRIX_COL_PINS', f, line)
                else:
                    self.col_pins = self.convert_pindef(string)
            elif re.match(r'\s*#\s*define\s+MATRIX_ROW_PINS_RIGHT\s', string):
                if self.row_pins_right != '':
                    self.waring_multiple_definition(
                        'MATRIX_ROW_PINS_RIGHT', f, line)
                else:
                    self.row_pins_right = self.convert_pindef(string)
            elif re.match(r'\s*#\s*define\s+MATRIX_COL_PINS_RIGHT\s', string):
                if self.col_pins_right != '':
                    self.waring_multiple_definition(
                        'MATRIX_COL_PINS_RIGHT', f, line)
                else:
                    self.col_pins_right = self.convert_pindef(string)
            elif re.match(r'\s*#\s*define\s+DIODE_DIRECTION\s', string):
                if self.diode_direction != '':
                    self.waring_multiple_definition('DIODE_DIRECTION', f, line)
                else:
                    direction = string.split('DIODE_DIRECTION')[
                        1].replace('\n', '').strip()
                    if direction == 'ROW2COL':
                        self.diode_direction = 1
                    else:
                        self.diode_direction = 0
            elif re.match(r'\s*#\s*define\s+RGB_DI_PIN\s', string):
                if self.led_pin != '':
                    self.waring_multiple_definition('RGB_DI_PIN', f, line)
                else:
                    pin = string.split('RGB_DI_PIN')[
                        1].replace('\n', '').strip()
                    self.led_pin = self.PIN_TABLE[pin]
            elif re.match(r'\s*#\s*define\s+RGBLED_NUM\s', string):
                if self.led_num != '':
                    self.waring_multiple_definition('RGBLED_NUM', f, line)
                else:
                    self.led_num = string.split('RGBLED_NUM')[
                        1].replace('\n', '').strip()
            elif '#define ' + self.search_layout + '(' in string:
                if self.layout != '':
                    self.waring_multiple_definition(
                        self.search_layout, f, line)
                else:
                    layout_detect = True

            if layout_detect:
                layout_str = layout_str + string

            if '}\n' in string and layout_detect:
                layout_detect = False
                self.layout = self.convert_layout(layout_str)

        return

    def assertion(self):
        res = True
        if self.layout == '':
            print(red('ERROR') + ': Failed to find LAYOUT')
            res = False

        if self.col_pins == '':
            print(red('ERROR') + ': Failed to find MATRIX_COL_PINS')
            res = False

        if self.row_pins == '':
            print(red('ERROR') + ': Failed to find MATRIX_ROW_PINS')
            res = False

        if self.col_num == '':
            print(red('ERROR') + ': Failed to find MATRIX_COLS')
            res = False

        if self.row_num == '':
            print(red('ERROR') + ': Failed to find MATRIX_ROWS')
            res = False

        if (int(self.col_num) != len(self.col_pins.split(',')) or int(self.row_num) != len(self.row_pins.split(','))):
            self.is_split = True
            print('This keyboard is split keyboard')

        if (int(self.col_num) != len(self.col_pins.split(',')) and int(self.row_num) != len(self.row_pins.split(','))):
            print(yellow('warning') +
                  ': MATRIX len and PINS len do not match in both row and col.')

        return res

    def apply_default(self):
        if self.diode_direction == '':
            print('DIODE_DIRECTION is not found. Apply ROW2COL.')
            self.diode_direction = '0'

        if self.led_pin == '':
            print('RGB_DI_PIN is not found. Apply 255(not used)')
            self.led_pin = '255'

        if self.led_num == '':
            print('RGBLED_NUM is not found. Apply 0(not used)')
            self.led_num = '0'

        if self.is_split:
            if self.col_pins_right == '':
                self.col_pins_right = self.col_pins

            if self.row_pins_right == '':
                self.row_pins_right = self.row_pins


if __name__ == '__main__':
    args = sys.argv
    if len(args) == 1:
        print(
            ('Usage : config_converter.py [TARGET]\n' ' ex: ./config_covnerte.py ~/qmk_firmware/keyboards/helix/rev2\n'))
        sys.exit()

    config = ConfigConverter()

    dirc = args[1]
    files = os.listdir(dirc)

    print(f' ** Making config.json from {dirc} ** ')

    for fname in files:
        path = os.path.join(dirc, fname)
        if not '.h' in path:
            continue
        with open(path) as f:
            config.find_layout_macro(f)

    config.print_layout_list()

    if len(config.layout_macro) == 1:
        layout_idx = 0
    else:
        print('')
        layout_idx = input('Use layout: ')

    try:
        config.set_layout_index(layout_idx)
    except:
        print('invalid input')
        sys.exit()

    for fname in files:
        path = os.path.join(dirc, fname)
        if not '.h' in path:
            continue
        with open(path) as f:
            config.parse_file(f)

    if not config.assertion():
        sys.exit()

    config.apply_default()

    config_name = dirc.split('keyboards/')[1]
    if '/' in config_name:
        config_name = config_name.replace('/', '_')

    if config_name[-1] != '_':
        config_name = config_name + '_'

    if config.search_layout != 'LAYOUT':
        config_name = config_name + config.search_layout.lower() + '_'

    mode = 'SINGLE'
    if config.is_split:
        config_name = config_name + 'master_left_'
        mode = 'SPLIT_MASTER'

    config_name = config_name + 'config.json'

    config_file_format = (
        '{{"config":\n\t{{\n\t\t"version":2,\n\t\t"device_info":{{"vid":"{0}","pid":"{1}",\n\t\t\t"name":"{2}","manufacture":"{3}","description":"{4}"}},\n'
        '\t\t"matrix":{{"rows":{5},"cols":{6},"device_rows":{7}, "device_cols":{8},\n\t\t\t"debounce":1,"is_left_hand":1,"diode_direction":{9},\n\t\t\t"row_pins":{10},\n\t\t\t"col_pins":{11},\n'
        '\t\t"layout":{12}}},\n\t\t"mode":"{13}","startup":1,\n\t\t"peripheral":{{"max_interval":60,"min_interval":30,"slave_latency":7}},\n'
        '\t\t"central":{{"max_interval":60,"min_interval":30,"slave_latency":0}},\n'
        '\t\t"led":{{"pin":{14}, "num":{15}}},\n\t\t"keymap":{{"locale":"US","use_ascii":0}}\n}}}}'
    )

    with open(config_name, 'w') as f:
        f.write(
            config_file_format.format(
                config.vid, config.pid, config.name, config.manufacture, config.description, config.row_num, config.col_num, len(
                    config.row_pins.split(',')), len(config.col_pins.split(',')), config.diode_direction, config.row_pins, config.col_pins,
                config.layout.replace(
                    '\n', '\n\t\t\t'), mode, config.led_pin, config.led_num
            )
        )

    print(f' ** Output to {config_name} ** \n')

    if not config.is_split:
        sys.exit()

    config_name = config_name.replace('master_left_', 'slave_right_')
    mode = 'SPLIT_SLAVE'
    with open(config_name, 'w') as f:
        f.write(
            config_file_format.replace('"is_left_hand":1', '"is_left_hand":0').format(
                config.vid, config.pid, config.name, config.manufacture, config.description, config.row_num, config.col_num, len(
                    config.row_pins_right.split(',')), len(config.col_pins_right.split(',')), config.diode_direction, config.row_pins_right,
                config.col_pins_right, config.layout.replace(
                    '\n', '\n\t\t\t'), mode, config.led_pin, config.led_num
            )
        )

    print(f' ** Output to {config_name} ** \n')

    config_name = config_name.replace('slave_right_', 'lpme_left_')
    lpme_row = ([int(r) for r in config.row_pins.strip('[]').split(',')])
    lpme_row.extend([int(r)
                     for r in config.row_pins_right.strip('[]').split(',')])
    lpme_col = ([int(r) for r in config.col_pins.strip('[]').split(',')])
    lpme_col.extend([int(r)
                     for r in config.col_pins_right.strip('[]').split(',')])
    mode = 'SINGLE'
    with open(config_name, 'w') as f:
        f.write(
            config_file_format.format(
                config.vid, config.pid, config.name, config.manufacture,
                config.description, config.row_num, config.col_num,
                len(config.row_pins.split(',')), len(
                    config.col_pins.split(',')),
                str(int(config.diode_direction) + 2),
                str(lpme_row),
                str(lpme_col),
                config.layout.replace('\n', '\n\t\t\t'),
                mode,
                config.led_pin, config.led_num
            )
        )

    print(f' ** Output to {config_name} ** \n')
