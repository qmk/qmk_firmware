#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from sortedcontainers import SortedDict
import layout
import re

# TODO: auto-generate mutex layers
# TODO: auto-generate update_tri_layer (_state)


def gen_uc_iter():
    length = len(layout.uc_dict)
    for key, value in layout.uc_dict.items():
        length -= 1
        if length:
            yield (key, value, False)
        else:
            yield (key, value, True)


def translate(s):
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
    (kc, lgd) = translate(s)
    return kc


def toLgd(s):
    (kc, lgd) = translate(s)
    return lgd


if __name__ == "__main__":

    template = open("km_template.txt", mode="r")
    output = open("keymap.c", mode="w", encoding='utf-8')

    doCopy = False

    for line in template:
        doCopy = True
        if line.startswith("//<enum/>"):
            doCopy = False
#            output.write(str(layout.uc_dict))
            for k, v, isLast in gen_uc_iter():
                if isLast:
                    output.write(k + "\n")
                else:
                    output.write(k + ",\n")
        if line.startswith("//<uc_map/>"):
            doCopy = False
            for k, v, isLast in gen_uc_iter():
                if isLast:
                    output.write(u"\t[{0}] = {1}  // {2}\n".format(k, v, chr(int(v, 0))))
                else:
                    output.write(u"\t[{0}] = {1},  // {2}\n".format(k, v, chr(int(v, 0))))
        if line.startswith("//<keymaps/>"):
            doCopy = False
            counter = len(layout.layers)
            layer = 0
            S = layout.static
            for L in layout.layers:
                counter -= 1
                r_counter = 4
                output.write("/* Layer %d\n" % layer)
                output.write(" * -------------------------------------------------               -------------------------------------------------\n")
                output.write(" * |{0}|{1}|{2}|{3}|{4}|{5}|               |{6}|{7}|{8}|{9}|{10}|{11}|\n".format(toLgd(L[0][0]), toLgd(L[0][1]), toLgd(L[0][2]), toLgd(L[0][3]), toLgd(L[0][4]), toLgd(L[0][5]), toLgd(L[0][6]), toLgd(L[0][7]), toLgd(L[0][8]), toLgd(L[0][9]), toLgd(L[0][10]), toLgd(L[0][11])))
                output.write(" * -------------------------------------------------               -------------------------------------------------\n")
                output.write(" * |{0}|{1}|{2}|{3}|{4}|{5}|               |{6}|{7}|{8}|{9}|{10}|{11}|\n".format(toLgd(L[1][0]), toLgd(L[1][1]), toLgd(L[1][2]), toLgd(L[1][3]), toLgd(L[1][4]), toLgd(L[1][5]), toLgd(L[1][6]), toLgd(L[1][7]), toLgd(L[1][8]), toLgd(L[1][9]), toLgd(L[1][10]), toLgd(L[1][11])))
                output.write(" * -------------------------------------------------               -------------------------------------------------\n")
                output.write(" * |{0}|{1}|{2}|{3}|{4}|{5}|               |{6}|{7}|{8}|{9}|{10}|{11}|\n".format(toLgd(L[2][0]), toLgd(L[2][1]), toLgd(L[2][2]), toLgd(L[2][3]), toLgd(L[2][4]), toLgd(L[2][5]), toLgd(L[2][6]), toLgd(L[2][7]), toLgd(L[2][8]), toLgd(L[2][9]), toLgd(L[2][10]), toLgd(L[2][11])))
                output.write(" * -----------------------------------------------------------------------------------------------------------------\n")
                output.write(" *  {0} {1} {2}        |{3}|{4}|{5}|{6}|{7}|{8}|        {9} {10} {11}".format(toLgd(L[3][0]), toLgd(L[3][1]), toLgd(L[3][2]), toLgd(L[3][3]), toLgd(L[3][4]), toLgd(L[3][5]), toLgd(L[3][6]), toLgd(L[3][7]), toLgd(L[3][8]), toLgd(L[3][9]), toLgd(L[3][10]), toLgd(L[3][11])).rstrip()+"\n")
                output.write(" *                                 -------------------------------------------------\n")
                output.write(" */\n")

                l_code = '\tLAYOUT(\n'
                for r in range(r_counter):
                    r_counter -= 1
                    c_counter = 12
                    l_code += '\t\t'
                    for c in range(c_counter):
                        c_counter -= 1
                        if c != 0:
                            l_code += " "
                        l_code += "%s" % toKC(L[r][c])
                        if r_counter or c_counter:
                            l_code += ","
                    l_code += '\n'
                if counter:
                    l_code += "\t),\n\n"
                else:
                    l_code += "\t)\n"
                output.write(l_code)
                layer += 1
        if doCopy:
            output.write(line)

    template.close()
    output.close()
