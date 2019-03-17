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
    elif re.match("^F[0-9]{1,2}$", s): # Fn, works from F0 to F99
        return ("KC_{0}".format(s), "{0:^7}".format(s))
    elif re.match("^L[0-9]{1,2}$", s): # Ln, works from L0 to L99
        return ("MO({0})".format(s[1:]), "{0:^7}".format(s))
    elif re.match("^T[0-9]{1,2}$", s): # Tn, works from T0 to T99
        return ("TG({0})".format(s[1:]), "{0:^7}".format(s))
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

##test = open("test.txt", mode="w")
##
##length = len(layout.uc_dict)
##for k, v, isLast in gen_uc_iter():
##    length -= 1
##    if length:
##        test.write(k+",\n")
##    else:
##        test.write(k)
##
##test.close()

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
            S = layout.static
            for L in layout.layers:
                counter -= 1
                output.write("/* -------------------------------------------------               -------------------------------------------------\n")
                output.write(" * |{0}|{1}|{2}|{3}|{4}|{5}|               |{6}|{7}|{8}|{9}|{10}|{11}|\n".format(toLgd(L[0][0]), toLgd(L[0][1]), toLgd(L[0][2]), toLgd(L[0][3]), toLgd(L[0][4]), toLgd(L[0][5]), toLgd(L[0][6]), toLgd(L[0][7]), toLgd(L[0][8]), toLgd(L[0][9]), toLgd(L[0][10]), toLgd(L[0][11])))
                output.write(" * -------------------------------------------------               -------------------------------------------------\n")
                output.write(" * |{0}|{1}|{2}|{3}|{4}|{5}|               |{6}|{7}|{8}|{9}|{10}|{11}|\n".format(toLgd(L[1][0]), toLgd(L[1][1]), toLgd(L[1][2]), toLgd(L[1][3]), toLgd(L[1][4]), toLgd(L[1][5]), toLgd(L[1][6]), toLgd(L[1][7]), toLgd(L[1][8]), toLgd(L[1][9]), toLgd(L[1][10]), toLgd(L[1][11])))
                output.write(" * -------------------------------------------------               -------------------------------------------------\n")
                output.write(" * |{0}|{1}|{2}|{3}|{4}|{5}|               |{6}|{7}|{8}|{9}|{10}|{11}|\n".format(toLgd(L[2][0]), toLgd(L[2][1]), toLgd(L[2][2]), toLgd(L[2][3]), toLgd(L[2][4]), toLgd(L[2][5]), toLgd(L[2][6]), toLgd(L[2][7]), toLgd(L[2][8]), toLgd(L[2][9]), toLgd(L[2][10]), toLgd(L[2][11])))
                output.write(" * -------------------------------------------------               -------------------------------------------------\n")
                output.write(" * |{0}|{1}|{2}|{3}|{4}|{5}|               |{6}|{7}|{8}|{9}|{10}|{11}|\n".format(toLgd(L[3][0]), toLgd(L[3][1]), toLgd(L[3][2]), toLgd(L[3][3]), toLgd(L[3][4]), toLgd(L[3][5]), toLgd(L[3][6]), toLgd(L[3][7]), toLgd(L[3][8]), toLgd(L[3][9]), toLgd(L[3][10]), toLgd(L[3][11])))
                output.write(" * -----------------------------------------------------------------------------------------------------------------\n")
                output.write(" *  {6}         {7} {8}|{0}|{1}|{2}|{3}|{4}|{5}|{9} {10}         {11} \n".format(toLgd(L[4][0]), toLgd(L[4][1]), toLgd(L[4][2]), toLgd(L[4][3]), toLgd(L[4][4]), toLgd(L[4][5]), toLgd(S[0]), toLgd(S[1]), toLgd(S[2]), toLgd(S[3]), toLgd(S[4]), toLgd(S[5])))
                output.write(" *                                 -------------------------------------------------\n")
                output.write(" */\n")
                output.write("\tKEYMAP(\n")
                output.write("\t\t{0}, {1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9},\n".format(toKC(L[0][0]), toKC(L[0][1]), toKC(L[0][2]), toKC(L[0][3]), toKC(L[0][4]), toKC(L[0][7]), toKC(L[0][8]), toKC(L[0][9]), toKC(L[0][10]), toKC(L[0][11])))
                output.write("\t\t{0}, {1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9},\n".format(toKC(L[1][0]), toKC(L[1][1]), toKC(L[1][2]), toKC(L[1][3]), toKC(L[1][4]), toKC(L[1][7]), toKC(L[1][8]), toKC(L[1][9]), toKC(L[1][10]), toKC(L[1][11])))
                output.write("\t\t{0}, {1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9},\n".format(toKC(L[2][0]), toKC(L[2][1]), toKC(L[2][2]), toKC(L[2][3]), toKC(L[2][4]), toKC(L[2][7]), toKC(L[2][8]), toKC(L[2][9]), toKC(L[2][10]), toKC(L[2][11])))
                output.write("\t\t{0}, {1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9},\n".format(toKC(L[3][0]), toKC(L[3][1]), toKC(L[3][2]), toKC(L[3][3]), toKC(L[3][4]), toKC(L[3][7]), toKC(L[3][8]), toKC(L[3][9]), toKC(L[3][10]), toKC(L[3][11])))
                output.write("\t\t{4}, {0}, {5}, {6}, {1}, {2}, {7}, {8}, {3}, {9},\n".format(toKC(L[4][2]), toKC(L[4][0]), toKC(L[4][5]), toKC(L[4][3]), toKC(S[0]), toKC(S[1]), toKC(S[2]), toKC(S[3]), toKC(S[4]), toKC(S[5])))
                output.write("\t\t{0}, {1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9})".format(toKC(L[4][1]), toKC(L[3][5]), toKC(L[2][5]), toKC(L[1][5]), toKC(L[0][5]), toKC(L[0][6]), toKC(L[1][6]), toKC(L[2][6]), toKC(L[3][6]), toKC(L[4][4])))
                if counter:
                    output.write(",\n\n")
                else:
                    output.write("\n")
        if doCopy == True:
            output.write(line)

    template.close()
    output.close()
