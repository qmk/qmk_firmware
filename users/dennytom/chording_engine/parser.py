#!/usr/bin/env python3

import json
from functools import reduce 
from chord import *
import sys

comma_separator = (lambda x, y: str(x) + ", " + str(y))
string_sum = (lambda x, y: str(x) + " + " + str(y))
newline_separator = (lambda x, y: str(x) + "\n" + str(y))

def add_includes(data):
    output_buffer = ""
    if not ("do_not_include_QMK" in data["parameters"] and data["parameters"]["do_not_include_QMK"] == True):
        output_buffer += "#include QMK_KEYBOARD_H\n"
    if len(data["extra_dependencies"]) > 0:
        for dependecy in data["extra_dependencies"]:
            output_buffer += '#include "' + dependecy + '"\n'
    
    return output_buffer + "\n"

def add_parameters(data):
    output_buffer = ""
    
    number_of_keys = len(data["keys"])
    if number_of_keys <= 8:
        hash_type = "uint8_t"
    elif number_of_keys <= 16:
        hash_type = "uint16_t"
    elif number_of_keys <= 32:
        hash_type = "uint32_t"
    elif number_of_keys <= 64:
        hash_type = "uint64_t"
    else:
        raise Exception("The engine currently supports only up to 64 keys.")
    
    output_buffer += "#define CHORD_TIMEOUT " + str(data["parameters"]["chord_timeout"]) + "\n"
    output_buffer += "#define DANCE_TIMEOUT " + str(data["parameters"]["dance_timeout"]) + "\n"
    output_buffer += "#define LEADER_TIMEOUT " + str(data["parameters"]["leader_timeout"]) + "\n"
    output_buffer += "#define TAP_TIMEOUT " + str(data["parameters"]["tap_timeout"]) + "\n"
    output_buffer += "#define LONG_PRESS_MULTIPLIER " + str(data["parameters"]["long_press_multiplier"]) + "\n"
    output_buffer += "#define DYNAMIC_MACRO_MAX_LENGTH " + str(data["parameters"]["dynamic_macro_max_length"]) + "\n"
    output_buffer += "#define COMMAND_MAX_LENGTH " + str(data["parameters"]["command_max_length"]) + "\n"
    output_buffer += "#define STRING_MAX_LENGTH " + str(data["parameters"]["string_max_length"]) + "\n"
    output_buffer += "#define LEADER_MAX_LENGTH " + str(data["parameters"]["leader_max_length"]) + "\n"
    output_buffer += "#define HASH_TYPE " + hash_type + "\n"
    output_buffer += "#define NUMBER_OF_KEYS " + str(len(data["keys"])) + "\n"
    output_buffer += "#define DEFAULT_PSEUDOLAYER " + data["parameters"]["default_pseudolayer"] + "\n"
    
    return output_buffer + "\n"

def add_keycodes(data):
    output_buffer = ""
    
    if not len(data["keys"]) == len(set(data["keys"])):
        raise Exception("The keys must have unique names")
    
    for key, counter in zip(data["keys"], range(0, len(data["keys"]))):
        output_buffer += "#define H_" + key + " ((HASH_TYPE) 1 << " + str(counter) + ")\n"
    output_buffer += "\n"
    
    output_buffer += "enum internal_keycodes {\n"
    output_buffer += "    " + data["keys"][0] + " = SAFE_RANGE,\n"
    output_buffer += "    " + reduce(comma_separator, [key for key in data["keys"][1:]]) + ",\n"
    output_buffer += "    FIRST_INTERNAL_KEYCODE = " + data["keys"][0] + ",\n"
    output_buffer += "    LAST_INTERNAL_KEYCODE = " + data["keys"][-1] + "\n"
    output_buffer += "};\n"
    
    return output_buffer + "\n"

def add_pseudolayers(data):
    output_buffer = ""
    
    if len(data["pseudolayers"]) == 0:
        raise Exception("You didn't define any pseudolayers")
    
    if not len([pseudolayer["name"] for pseudolayer in data["pseudolayers"]]) == len(set([pseudolayer["name"] for pseudolayer in data["pseudolayers"]])):
        raise Exception("The pseudolayers must have unique names")
    
    pseudolayers = data["pseudolayers"]
    if not "ALWAYS_ON" in [layer["name"] for layer in pseudolayers]:
        pseudolayers += [{"name": "ALWAYS_ON", "chords": []}] # the engine expects ALWAYS_ON to exist
    
    output_buffer += "enum pseudolayers {\n"
    output_buffer += "    " + reduce(comma_separator, [layer["name"] for layer in pseudolayers]) + "\n"
    output_buffer += "};\n"
    
    return output_buffer + "\n"

def add_layers(data):
    output_buffer = ""
    
    output_buffer += "const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {\n"
    for layer, counter in zip(data["layers"], range(0,len(data["layers"]))):
        if layer["type"] == "auto":
            output_buffer += "    [" + str(counter) + "] = " + data["parameters"]["layout_function_name"] + "(" + reduce(comma_separator, [key for key in data["keys"]]) + "),\n"
        else:
            output_buffer += "    [" + str(counter) + "] = " + data["parameters"]["layout_function_name"] + "(" + reduce(comma_separator, [key for key in layer["keycodes"]]) + "),\n"
    output_buffer += "};\n"
    output_buffer += "size_t keymapsCount = " + str(len(data["layers"])) + ";\n"
    
    return output_buffer + "\n"

def prep_buffers(data):
    output_buffer = ""
    
    output_buffer += "uint8_t keycodes_buffer_array[] = {\n"
    output_buffer += "    " + reduce(comma_separator, ["0"] * len(data["keys"])) + "\n"
    output_buffer += "};\n"
    output_buffer += "\n"
    
    output_buffer += "uint8_t command_buffer[] = {\n"
    output_buffer += "    " + reduce(comma_separator, ["0"] * data["parameters"]["command_max_length"]) + "\n"
    output_buffer += "};\n"
    output_buffer += "\n"
    
    output_buffer += "uint16_t leader_buffer[] = {\n"
    output_buffer += "    " + reduce(comma_separator, ["0"] * data["parameters"]["leader_max_length"]) + "\n"
    output_buffer += "};\n"
    output_buffer += "\n"
    
    output_buffer += "uint8_t dynamic_macro_buffer[] = {\n"
    output_buffer += "    " + reduce(comma_separator, ["0"] * data["parameters"]["dynamic_macro_max_length"]) + "\n"
    output_buffer += "};"
    
    return output_buffer + "\n"

def parse_keyboard_specifics(data):
    keyboard_part_0 = add_includes(data)
    keyboard_part_0 += add_keycodes(data)
    keyboard_part_0 += add_pseudolayers(data)
    keyboard_part_0 += add_parameters(data)
    keyboard_part_0 += add_layers(data)
    keyboard_part_0 += prep_buffers(data)
    
    return keyboard_part_0 + '\n'

def parse_chords(data):
    keyboard_part_2 = ""
    strings = []
    number_of_strings = 0
    number_of_chords = 0
    
    for pseudolayer in data["pseudolayers"]:
        name = pseudolayer["name"]
        for chord in pseudolayer["chords"]:
            if chord["type"] == "chord_set":
                keycodes = reduce(comma_separator, [word for word in chord["keycodes"]])
                [keyboard_part_2, number_of_chords, number_of_strings, strings] = add_chord_set(name, keycodes, chord["set"], data, keyboard_part_2, number_of_chords, number_of_strings, strings)
            if chord["type"] == "visual_array":
                [keyboard_part_2, number_of_chords, number_of_strings, strings] = add_dictionary(name, chord["keys"], chord["dictionary"], keyboard_part_2, number_of_chords, number_of_strings, strings)
            if chord["type"] == "visual":
                keycodes = reduce(comma_separator, [word for word in chord["chord"]])
                [keyboard_part_2, number_of_chords, number_of_strings, strings] = secret_chord(name, chord["keycode"], keycodes, data, keyboard_part_2, number_of_chords, number_of_strings, strings)
            elif chord["type"] == "simple":
                keycodes = reduce(string_sum, ["H_" + word for word in chord["chord"]])
                [keyboard_part_2, number_of_chords, number_of_strings, strings] = add_key(name, keycodes, chord["keycode"], keyboard_part_2, number_of_chords, number_of_strings, strings)
    keyboard_part_2 += "\n"
    
    keyboard_part_2 += "const struct Chord* const list_of_chords[] PROGMEM = {\n"
    keyboard_part_2 += "    " + reduce(comma_separator, ["&chord_" + str(i) for i in range(0, number_of_chords)]) + "\n"
    keyboard_part_2 += "};\n"
    keyboard_part_2 += "\n"
    
    if len(data["leader_sequences"]) > 0:
        keyboard_part_2 += reduce(newline_separator, [sequence["function"] for sequence in data["leader_sequences"]]) + "\n\n"
        keyboard_part_2 += "const uint16_t leader_triggers[][LEADER_MAX_LENGTH] PROGMEM = {\n"
        for sequence in data["leader_sequences"]:
            keyboard_part_2 += "    {" + reduce(comma_separator, sequence["sequence"] + ["0"] * (data["parameters"]["leader_max_length"] - len(sequence["sequence"]))) + "},\n"
        keyboard_part_2 += "};\n\n"
        keyboard_part_2 += "void (*leader_functions[]) (void) = {\n"
        keyboard_part_2 += "    " + reduce(comma_separator, ["&" + sequence["name"] for sequence in data["leader_sequences"]]) + "\n"
        keyboard_part_2 += "};\n"
    else:
        keyboard_part_2 += "const uint16_t** const leader_triggers PROGMEM = NULL;\n"
        keyboard_part_2 += "void (*leader_functions[]) (void) = {};\n"
    keyboard_part_2 += "\n"
    
    keyboard_part_2 += "#define NUMBER_OF_CHORDS " + str(number_of_chords) + "\n"
    keyboard_part_2 += "#define NUMBER_OF_LEADER_COMBOS " + str(len(data["leader_sequences"]))
    
    return keyboard_part_2 + "\n\n"

def parse_strings_for_chords(data):
    keyboard_part_1 = ""
    
    for string, i in zip(strings, range(0, len(strings))):
        keyboard_part_1 += "const char string_" + str(i) + " [] PROGMEM = \"" + string + "\";\n"

    keyboard_part_1 += "\n"
    keyboard_part_1 += "const char * const strings[] PROGMEM = {\n"
    if len(strings) > 0:
        keyboard_part_1 += "    " + reduce(comma_separator, ["string_" + str(i) for i in range(0, len(strings))]) 
    keyboard_part_1 += "\n};\n"
    
    return keyboard_part_1

def main():
    if len(sys.argv) != 3:
        raise Exception("Wrong number of arguments.\n\nUsage: python parser.py keymap.json keymap.c")
    
    input_filepath = sys.argv[1]
    output_filepath = sys.argv[2]
    
    with open(input_filepath, "r") as read_file:
        data = json.load(read_file)
        
        keyboard_part_0 = parse_keyboard_specifics(data)
        keyboard_part_1 = parse_strings_for_chords(data)
        keyboard_part_2 = parse_chords(data)
        
        engine_part_1 = open("engine.part.1", "r").read()
        engine_part_2 = open("engine.part.2", "r").read() + "\n"
        engine_part_3 = open("engine.part.3", "r").read()
        
        output_buffer = keyboard_part_0
        output_buffer += engine_part_1
        
        if len(data["extra_code"]) > 0:
            output_buffer += data["extra_code"] + "\n"
        
        output_buffer += keyboard_part_1
        output_buffer += engine_part_2
        output_buffer += keyboard_part_2
        output_buffer += engine_part_3
        
        with open(output_filepath, "w") as write_file:
            write_file.write(output_buffer)

if __name__ == "__main__":
    main()