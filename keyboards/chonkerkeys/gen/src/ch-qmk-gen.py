import json
import argparse

def print_array(array, indent):
    result = ""
    for i in range(0, indent):
        result += "    "
    result += "{\n"
    size = len(array)
    for i, element in enumerate(array):
        if (isinstance(element, list)):
            result += print_array(element, indent + 1)
        else:
            for j in range(0, indent + 1):
                result += "    "
            result += "{}".format(element)
        if (i + 1 < size):
            result += ",\n"
        else:
            result += "\n"
    for i in range(0, indent):
        result += "    "
    result += "}"
    return result

def map_element_or_list_mapper(element, func):
    if (isinstance(element, list)):
        return list(map(lambda e: map_element_or_list_mapper(e, func), element))
    else:
        return func(element)

def map_element_or_list(func, array):
    return list(map(lambda e: map_element_or_list_mapper(e, func), array))

parser = argparse.ArgumentParser()
parser.add_argument("--firmware-version", type=int, required=True)
parser.add_argument("--config", type=str, required=True)
parser.add_argument("--output", type=str, required=True)

args = parser.parse_args()

firmware_version = args.firmware_version
config = json.loads(args.config)
layers = config["layers"]
layer_count = len(layers)
size_ordinals = config["sizeOrdinals"]
keymaps = config["keymaps"]
actionTypeToAnimationMaps = {
    "CH_ZOOM_MUTE_TOGGLE": "RGB_STRAND_EFFECT_MOMENTARY",
    "CH_ZOOM_VIDEO_TOGGLE": "RGB_STRAND_EFFECT_MOMENTARY",
    "CH_ZOOM_SHARE_SCREEN_START_STOP_TOGGLE": "RGB_STRAND_EFFECT_BLINKY",
    "CH_ZOOM_RAISE_HAND_TOGGLE": "RGB_STRAND_EFFECT_LIKE",
    "CH_ZOOM_LEAVE_MEETING": "RGB_STRAND_EFFECT_DRAINSWIRL"
}
noAnimation = "RGB_STRAND_EFFECT_NONE"
animations = map_element_or_list(lambda k: actionTypeToAnimationMaps.get(k) or noAnimation, keymaps)

if (len(size_ordinals) != layer_count or len(keymaps) != layer_count):
    print("length of size ordinals or keymaps doesn't match layer count")
    exit(1)

# TODO: Validate row/column count

output_path = args.output

output = "#include \"../../../keyconfig.h\"\n"
output += "#include \"../../../layer_type.h\"\n"
output += "\n"
output += "const uint32_t firmware_version = {};\n".format(firmware_version)
output += "\n"
output += "#define LAYER_COUNT {}\n".format(layer_count)
output += "\n"
output += "const uint8_t layers[LAYER_COUNT] = "
output += print_array(layers, 0)
output += ";\n"
output += "\n"
output += "const uint8_t key_size_and_ordinals[LAYER_COUNT][MATRIX_ROWS][MATRIX_COLS] = "
output += print_array(size_ordinals, 0)
output += ";\n"
output += "\n"
output += "const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = "
output += print_array(keymaps, 0)
output += ";\n"
output += "\n"
output += "const rgb_strands_anim_t key_anim[][MATRIX_ROWS][MATRIX_COLS] = "
output += print_array(animations, 0)
output += ";\n"
output += "\n"

file = open(output_path, "w")
file.write(output)
file.close()
