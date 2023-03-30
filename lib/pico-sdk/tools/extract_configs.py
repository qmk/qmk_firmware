#!/usr/bin/env python3
#
# Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
#
# SPDX-License-Identifier: BSD-3-Clause
#
#
# Script to scan the Raspberry Pi Pico SDK tree searching for configuration items
# Outputs a tab separated file of the configuration item:
# name	location	description	type	advanced	default	depends	enumvalues	group	max	min
#
# Usage:
#
# ./extract_configs.py <root of source tree> [output file]
#
# If not specified, output file will be `pico_configs.tsv`


import os
import sys
import re
import csv
import logging

logger = logging.getLogger(__name__)
logging.basicConfig(level=logging.INFO)

scandir = sys.argv[1]
outfile = sys.argv[2] if len(sys.argv) > 2 else 'pico_configs.tsv'

CONFIG_RE = re.compile(r'//\s+PICO_CONFIG:\s+(\w+),\s+([^,]+)(?:,\s+(.*))?$')
DEFINE_RE = re.compile(r'#define\s+(\w+)\s+(.+?)(\s*///.*)?$')

all_configs = {}
all_attrs = set()
all_descriptions = {}
all_defines = {}



def ValidateAttrs(config_attrs, file_path, linenum):
    _type = config_attrs.get('type', 'int')

    # Validate attrs
    if _type == 'int':
        assert 'enumvalues' not in config_attrs
        _min = _max = _default = None
        if config_attrs.get('min', None) is not None:
            value = config_attrs['min']
            m = re.match(r'^(\d+)e(\d+)$', value.lower())
            if m:
                _min = int(m.group(1)) * 10**int(m.group(2))
            else:
                _min = int(value, 0)
        if config_attrs.get('max', None) is not None:
            value = config_attrs['max']
            m = re.match(r'^(\d+)e(\d+)$', value.lower())
            if m:
                _max = int(m.group(1)) * 10**int(m.group(2))
            else:
                _max = int(value, 0)
        if config_attrs.get('default', None) is not None:
            if '/' not in config_attrs['default']:
                try:
                    value = config_attrs['default']
                    m = re.match(r'^(\d+)e(\d+)$', value.lower())
                    if m:
                        _default = int(m.group(1)) * 10**int(m.group(2))
                    else:
                        _default = int(value, 0)
                except ValueError:
                    pass
        if _min is not None and _max is not None:
            if _min > _max:
                raise Exception('{} at {}:{} has min {} > max {}'.format(config_name, file_path, linenum, config_attrs['min'], config_attrs['max']))
        if _min is not None and _default is not None:
            if _min > _default:
                raise Exception('{} at {}:{} has min {} > default {}'.format(config_name, file_path, linenum, config_attrs['min'], config_attrs['default']))
        if _default is not None and _max is not None:
            if _default > _max:
                raise Exception('{} at {}:{} has default {} > max {}'.format(config_name, file_path, linenum, config_attrs['default'], config_attrs['max']))
    elif _type == 'bool':

        assert 'min' not in config_attrs
        assert 'max' not in config_attrs
        assert 'enumvalues' not in config_attrs

        _default = config_attrs.get('default', None)
        if _default is not None:
            if '/' not in _default:
                if (_default.lower() != '0') and (config_attrs['default'].lower() != '1') and ( _default not in all_configs):
                    logger.info('{} at {}:{} has non-integer default value "{}"'.format(config_name, file_path, linenum, config_attrs['default']))

    elif _type == 'enum':

        assert 'min' not in config_attrs
        assert 'max' not in config_attrs
        assert 'enumvalues' in config_attrs

        _enumvalues = tuple(config_attrs['enumvalues'].split('|'))
        _default = None
        if config_attrs.get('default', None) is not None:
            _default = config_attrs['default']
        if _default is not None:
            if _default not in _enumvalues:
                raise Exception('{} at {}:{} has default value {} which isn\'t in list of enumvalues {}'.format(config_name, file_path, linenum, config_attrs['default'], config_attrs['enumvalues']))
    else:
        raise Exception("Found unknown PICO_CONFIG type {} at {}:{}".format(_type, file_path, linenum))




# Scan all .c and .h files in the specific path, recursively.

for dirpath, dirnames, filenames in os.walk(scandir):
    for filename in filenames:
        file_ext = os.path.splitext(filename)[1]
        if file_ext in ('.c', '.h'):
            file_path = os.path.join(dirpath, filename)

            with open(file_path, encoding="ISO-8859-1") as fh:
                linenum = 0
                for line in fh.readlines():
                    linenum += 1
                    line = line.strip()
                    m = CONFIG_RE.match(line)
                    if m:
                        config_name = m.group(1)
                        config_description = m.group(2)
                        _attrs = m.group(3)
                        # allow commas to appear inside brackets by converting them to and from NULL chars
                        _attrs = re.sub(r'(\(.+\))', lambda m: m.group(1).replace(',', '\0'), _attrs)

                        if '=' in config_description:
                            raise Exception("For {} at {}:{} the description was set to '{}' - has the description field been omitted?".format(config_name, file_path, linenum, config_description))
                        if config_description in all_descriptions:
                            raise Exception("Found description {} at {}:{} but it was already used at {}:{}".format(config_description, file_path, linenum, os.path.join(scandir, all_descriptions[config_description]['filename']), all_descriptions[config_description]['line_number']))
                        else:
                            all_descriptions[config_description] = {'config_name': config_name, 'filename': os.path.relpath(file_path, scandir), 'line_number': linenum}

                        config_attrs = {}
                        prev = None
                        # Handle case where attr value contains a comma
                        for item in _attrs.split(','):
                            if "=" not in item:
                                assert(prev)
                                item = prev + "," + item
                            try:
                                k, v = (i.strip() for i in item.split('='))
                            except ValueError:
                                raise Exception('{} at {}:{} has malformed value {}'.format(config_name, file_path, linenum, item))
                            config_attrs[k] = v.replace('\0', ',')
                            all_attrs.add(k)
                            prev = item
                        #print(file_path, config_name, config_attrs)

                        if 'group' not in config_attrs:
                            raise Exception('{} at {}:{} has no group attribute'.format(config_name, file_path, linenum))

                        #print(file_path, config_name, config_attrs)
                        if config_name in all_configs:
                            raise Exception("Found {} at {}:{} but it was already declared at {}:{}".format(config_name, file_path, linenum, os.path.join(scandir, all_configs[config_name]['filename']), all_configs[config_name]['line_number']))
                        else:
                            all_configs[config_name] = {'attrs': config_attrs, 'filename': os.path.relpath(file_path, scandir), 'line_number': linenum, 'description': config_description}
                    else:
                        m = DEFINE_RE.match(line)
                        if m:
                            name = m.group(1)
                            value = m.group(2)
                            # discard any 'u' qualifier
                            m = re.match(r'^((0x)?\d+)u$', value.lower())
                            if m:
                                value = m.group(1)
                            else:
                                # discard any '_u(X)' macro
                                m = re.match(r'^_u\(((0x)?\d+)\)$', value.lower())
                                if m:
                                    value = m.group(1)
                            if name not in all_defines:
                                all_defines[name] = dict()
                            if value not in all_defines[name]:
                                all_defines[name][value] = set()
                            all_defines[name][value] = (file_path, linenum)

# Check for defines with missing PICO_CONFIG entries
resolved_defines = dict()
for d in all_defines:
    if d not in all_configs and d.startswith("PICO_"):
        logger.warning("Potential unmarked PICO define {}".format(d))
    # resolve "nested defines" - this allows e.g. USB_DPRAM_MAX to resolve to USB_DPRAM_SIZE which is set to 4096 (which then matches the relevant PICO_CONFIG entry)
    for val in all_defines[d]:
        if val in all_defines:
            resolved_defines[d] = all_defines[val]

for config_name, config_obj in all_configs.items():
    file_path = os.path.join(scandir, config_obj['filename'])
    linenum = config_obj['line_number']

    ValidateAttrs(config_obj['attrs'], file_path, linenum)

    # Check that default values match up
    if 'default' in config_obj['attrs']:
        config_default = config_obj['attrs']['default']
        if config_name in all_defines:
            defines_obj = all_defines[config_name]
            if config_default not in defines_obj and (config_name not in resolved_defines or config_default not in resolved_defines[config_name]):
                if '/' in config_default or ' ' in config_default:
                    continue
                # There _may_ be multiple matching defines, but arbitrarily display just one in the error message
                first_define_value = list(defines_obj.keys())[0]
                first_define_file_path, first_define_linenum = defines_obj[first_define_value]
                raise Exception('Found {} at {}:{} with a default of {}, but #define says {} (at {}:{})'.format(config_name, file_path, linenum, config_default, first_define_value, first_define_file_path, first_define_linenum))
        else:
            raise Exception('Found {} at {}:{} with a default of {}, but no matching #define found'.format(config_name, file_path, linenum, config_default))

with open(outfile, 'w', newline='') as csvfile:
    fieldnames = ('name', 'location', 'description', 'type') + tuple(sorted(all_attrs - set(['type'])))
    writer = csv.DictWriter(csvfile, fieldnames=fieldnames, extrasaction='ignore', dialect='excel-tab')

    writer.writeheader()
    for config_name, config_obj in sorted(all_configs.items()):
        writer.writerow({'name': config_name, 'location': '{}:{}'.format(config_obj['filename'], config_obj['line_number']), 'description': config_obj['description'], **config_obj['attrs']})
