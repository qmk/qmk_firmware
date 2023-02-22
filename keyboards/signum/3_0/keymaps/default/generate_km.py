#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import json
import layout
import os
import re


def gen_uc_iter():
    length = len(layout.uc_dict)
    for key, value in sorted(layout.uc_dict.items()):
        length -= 1
        if length:
            yield (key, value, False)
        else:
            yield (key, value, True)


def _translate(s):
    if re.match("^[0-9]$", s):
        return ("KC_{0}".format(s), "   {0}   ".format(s))
    elif re.match("^[a-z]$", s):
        return ("KC_{0}".format(s.upper()), "   {0}   ".format(s))
    elif re.match("^[A-Z]$", s):
        return ("S(KC_{0})".format(s), "   {0}   ".format(s))
    elif re.match("^F[0-9]{1,2}$", s):  # Fn, works from F0 to F99
        return ("KC_{0}".format(s), "{0:^7}".format(s))
    elif re.match("^DF[0-9]{1,2}$", s):  # DFn, works from DF0 to DF99
        return ("DF({0})".format(s[2:]), "{0:^7}".format(s))
    elif re.match("^MO[0-9]{1,2}$", s):  # MOn, works from MO0 to MO99
        return ("MO({0})".format(s[2:]), "{0:^7}".format(s))
    elif re.match("^OSL[0-9]{1,2}$", s):  # OSLn, works from OSL0 to OSL99
        return ("OSL({0})".format(s[3:]), "{0:^7}".format(s))
    elif re.match("^TG[0-9]{1,2}$", s):  # TGn, works from TG0 to TG99
        return ("TG({0})".format(s[2:]), "{0:^7}".format(s))
    elif re.match("^TO[0-9]{1,2}$", s):  # Tn, works from TO0 to TO99
        return ("TO({0})".format(s[2:]), "{0:^7}".format(s))
    elif re.match("^TT[0-9]{1,2}$", s):  # Tn, works from TT0 to TT99
        return ("TT({0})".format(s[2:]), "{0:^7}".format(s))
    elif s in layout.uc_dict:
        return ("X("+s+")", "   {0}   ".format(chr(int(layout.uc_dict[s], 0))))
    elif s in layout.qmk_dict:
        return (layout.qmk_dict[s], "{0:^7}".format(s))
    elif s == s.upper() and s.startswith("KC_"):
        return (s, "{0:^7}".format(s[2:]))
    else:
        return ("XXXXXXX", "  {0}   ".format(chr(128165)))


def toKC(s):
    return _translate(s)[0]


def toLgd(s):
    return _translate(s)[1]


def quoteC(text):
    yield "/*"
    for line in text:
        yield " * " + line
    yield " */\n"


def getKeymapText(id, layer, columns, rows):
    keymap = []
    keymap.append("Layer %d" % id)
    keymap.append("-------------------------------------------------               -------------------------------------------------")
    keymap.append("|{0}|{1}|{2}|{3}|{4}|{5}|               |{6}|{7}|{8}|{9}|{10}|{11}|".format(*map(toLgd, layer[:12])))
    keymap.append("-------------------------------------------------               -------------------------------------------------")
    keymap.append("|{0}|{1}|{2}|{3}|{4}|{5}|               |{6}|{7}|{8}|{9}|{10}|{11}|".format(*map(toLgd, layer[12:24])))
    keymap.append("-------------------------------------------------               -------------------------------------------------")
    keymap.append("|{0}|{1}|{2}|{3}|{4}|{5}|               |{6}|{7}|{8}|{9}|{10}|{11}|".format(*map(toLgd, layer[24:36])))
    keymap.append("-----------------------------------------------------------------------------------------------------------------")
    keymap.append(" {0} {1} {2}        |{3}|{4}|{5}|{6}|{7}|{8}|        {9} {10} {11}".format(*map(toLgd, layer[36:48])).rstrip())
    keymap.append("                                -------------------------------------------------")
    return keymap


def writeKeymap(f_template, f_keymap, layers, columns, rows):
    doCopy = False

    for line in f_template:
        doCopy = True
        if line.startswith("//<enum/>"):
            doCopy = False
            # f_keymap.write(str(layout.uc_dict))
            for k, v, isLast in gen_uc_iter():
                if isLast:
                    f_keymap.write(k + "\n")
                else:
                    f_keymap.write(k + ",\n")
        elif line.startswith("//<uc_map/>"):
            doCopy = False
            for k, v, isLast in gen_uc_iter():
                if isLast:
                    f_keymap.write(u"\t[{0}] = {1}  // {2}\n".format(k, v, chr(int(v, 0))))
                else:
                    f_keymap.write(u"\t[{0}] = {1},  // {2}\n".format(k, v, chr(int(v, 0))))
        elif line.startswith("//<keymaps/>"):
            doCopy = False
            for layer, L in enumerate(layers):
                r_counter = rows
                f_keymap.write('\n'.join(quoteC(getKeymapText(layer, L, columns, rows))))

                l_code = '\tLAYOUT_ortho_4x12(\n'
                for r in range(r_counter):
                    r_counter -= 1
                    c_counter = columns
                    l_code += '\t\t'
                    for c in range(c_counter):
                        c_counter -= 1
                        if c != 0:
                            l_code += " "
                        l_code += "%s" % toKC(L[r*columns + columns-c_counter-1])
                        if r_counter or c_counter:
                            l_code += ","
                    l_code += '\n'
                if layer + 1 != len(layout.layers):
                    l_code += "\t),\n\n"
                else:
                    l_code += "\t)\n"
                f_keymap.write(l_code)
        if doCopy:
            f_keymap.write(line)


def getKeymapJSON(keyboard, keymap, layout, layers):
    return json.dumps({
        'keyboard': keyboard,
        'keymap': keymap,
        'layout': layout,
        'layers': layers
        }, sort_keys=True, indent=4)


def getKeymapAsciidoc(title, layers, columns, rows):
    yield '= ' + title
    yield ''
    for id, layer in enumerate(layers):
        keymap = getKeymapText(id, layer, columns, rows)
        if len(keymap):
            yield '.' + keymap[0]
            yield '--------------------------'
            for line in keymap[1:]:
                yield ' ' + line
            yield '--------------------------'
            yield ''


def layersToKC(layers):
    return [list(map(toKC, layer)) for layer in layers]


def pathToKeymap(path):
    head, keymap = os.path.split(path)
    _, keymapsdir = os.path.split(head)
    if keymapsdir == 'keymaps':
        return keymap


def pathToKeyboard(path):
    head, keymap = os.path.split(path)
    head, keymapsdir = os.path.split(head)
    if keymapsdir == 'keymaps':
        head, dir = os.path.split(head)
        while dir not in ('/', 'keyboards'):
            yield dir
            head, dir = os.path.split(head)


if __name__ == "__main__":
    with open("km_template.txt", mode="r") as f_template:
        with open("keymap.c", mode="w", encoding='utf-8') as f_keymap:
            writeKeymap(f_template, f_keymap, layout.layers, columns=12, rows=4)

    abspath = os.path.dirname(os.path.abspath(__file__))
    keyboard = list(reversed(list(pathToKeyboard(abspath))))
    keymap = pathToKeymap(abspath)
    keyboard_layout = 'LAYOUT_ortho_4x12'
    with open("%s_%s.json" % ('_'.join(keyboard), keymap), mode="w") as f_keymapjson:
        f_keymapjson.write(
                getKeymapJSON(
                    '/'.join(keyboard),
                    keymap,
                    keyboard_layout,
                    layersToKC(layout.layers))
                )

    with open("keymap.adoc", mode="w") as f_keymapasciidoc:
        f_keymapasciidoc.write('\n'.join(getKeymapAsciidoc('Signum 3.0 %s_%s' % ('_'.join(keyboard), keymap), layout.layers, columns=12, rows=4)))
        print("Run the following command to generate a PDF from the keymap")
        print("a2x -f pdf --xsltproc-opts '--stringparam page.orientation landscape --stringparam body.font.master 12' --fop -v keymap.adoc")
