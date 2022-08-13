# Copyright 2022 Jose Pablo Ramirez <jp.ramangulo@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

import json
import pathlib
import jsonschema

__dirname = pathlib.Path(__file__).parent.resolve()

# Standard files
header_file = open(f"{__dirname}/transpiler_template.h", "r")
keymap_json = open(f"{__dirname}/../t_keymap.json", "r")
keymap = json.load(keymap_json)

# Locations for secrets files
p_secrets_json = f"{__dirname}/../secrets.json"
p_template = f"{__dirname}/keys_template.h"

use_secrets = False

# Include secret file if it exists
if(pathlib.Path(p_secrets_json).is_file()):
    use_secrets = True

    secret_json = open(p_secrets_json, "r")
    secrets = json.load(secret_json)

    key_file = open(p_template, "r")

keycode_schema = {
    "id": "/keycode",
    "type": "array",
    "items": {
        "properties": {
        "alias": { "type": "string" },
        "action": { "type": "string" }
        },
    "required": ["alias", "action"]
  }
}

layer_schema = {
    "id": "/layer",
    "type": "array",
    "items": {
        "properties": {
        "layer_label": {"type": "string"},
        "layer": {
            "type": "array",
            "items": {
            "propierties":{
                "type": "array",
                "items": {"type": "string"},
            },
            "minItems": 3,
            "maxItems": 3
            },
            "minItems": 13,
            "maxItems": 13
        }
        },
        "required": [ "layer_label", "layer" ]
    },
    "minItems": 1,
}

complete_schema = {
    "id": "/keymap",
    "type": "object",
    "properties": {
        "totp_layer": { "type": "integer" },
        "keycodes": {"$ref": "/keycode"},
        "keymap": {"$ref": "/layer"},
    },
    "required": ["keymap"]
}

schema_store = {
   layer_schema["id"] : layer_schema,
   keycode_schema["id"] : keycode_schema
}

resolver = jsonschema.RefResolver.from_schema(complete_schema, store=schema_store)
res = jsonschema.validate(keymap, complete_schema, resolver=resolver)

# Assume no exception occured

# Get OTP Layer
totp_layer = keymap["totp_layer"]

# Get layer number
layer_count = len(keymap["keymap"])

# Get custom keycodes
keycodes_enum = ",".join(map(lambda k: k["alias"], keymap["keycodes"]))

# Transpile custom keycodes
custom_keycodes = " ".join(map(lambda k: f'case {k["alias"]}: SEND_STRING({k["action"]}); break;', keymap["keycodes"]))

# Get layer strings
layer_string = ",".join(map(lambda l: f'"{l["layer_label"]}"', keymap["keymap"]))

def get_layer_string(l):
    rows_strings = [f'{{"","","{l["layer"][0][1]}"}}']
    for row in range(0,4):
        col_strings = []
        for col in range(0, 3):
            index = (row * 3) + col + 1
            col_strings.append(f'"{l["layer"][index][1]}"')
        rows_strings.append(f'{{{",".join(col_strings)}}}')

    return f'{{{",".join(rows_strings)}}}'

# Get keymap strings
keymap_string = ",".join(map(lambda l: get_layer_string(l), keymap["keymap"]))

def get_layer_indicator(l):
    rows_strings = []
    for row in range(0,4):
        col_strings = []
        for col in range(0, 3):
            index = (row * 3) + col + 1
            col_strings.append(f'{{{l["layer"][index][0]}}}')
        rows_strings.append(f'{{{", ".join(col_strings)}}}')

    return f'{{{",".join(rows_strings)}}}'

indicators = ",".join(map(lambda l: get_layer_indicator(l), keymap["keymap"]))

# Get keymap
t_keymap = ",".join(map(lambda l: f'[{l[0]}] = LAYOUT({",".join(map(lambda k: k[2], l[1]["layer"]))})', enumerate(keymap["keymap"])))

# print(header_file.read())
new_file = header_file.read().replace("{{trans_layer_no}}", str(layer_count))
new_file = new_file.replace("{{trans_keycodes_enum}}", keycodes_enum)
new_file = new_file.replace("{{trans_custom_keycodes}}", custom_keycodes)
new_file = new_file.replace("{{trans_layer_string}}", layer_string)
new_file = new_file.replace("{{trans_keymap_string}}", keymap_string)
new_file = new_file.replace("{{trans_indicators}}", indicators)
new_file = new_file.replace("{{trans_keymap}}", t_keymap)
new_file = new_file.replace("{{totp_layer}}", str(totp_layer))

header_nfile = open(f"{__dirname}/../transpiler.h", "w")
header_nfile.write(new_file)

if use_secrets:

    hashed_pass = ','.join(f'0x{secrets["password"][x:x+2]}' for x in range(0, len(secrets["password"]), 2))
    otp_hashed_keys = ','.join(f"{{{','.join(f'0x{key[x:x+2]}' for x in range(0, len(key), 2))}}}" for key in secrets["keys"])

    new_sfile = key_file.read().replace("{{totp_keys}}", otp_hashed_keys)
    new_sfile = new_sfile.replace("{{password}}", hashed_pass)
    new_sfile = new_sfile.replace("{{password_len}}", str(secrets["password-length"]))

    header_snfile = open(f"{__dirname}/../keys.h", "w")
    header_snfile.write(new_sfile)

print("Done!")
