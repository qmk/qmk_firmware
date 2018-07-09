
import sys

def remove_prefix(text, prefix):
    if text.startswith(prefix):
        return text[len(prefix):]
    return text

if len(sys.argv) < 2:
    print("Usage: map.py <map file> [object]")
    exit(1)

mapfile = sys.argv[1]
objname = None
if len(sys.argv) == 3:
    objname = sys.argv[2]

with open(mapfile) as f:
    s = None
    dtotal = 0
    text_total = 0
    rodata_total = 0
    data_total = 0
    bss_total = 0
    other_total = 0
    fill_total = 0
    omap = {}
    smap = {}
    for line in f:
        line = line.strip()
        if line == "Archive member included to satisfy reference by file (symbol)":
            #print("Archives")
            s = 'a'
        elif line == "Discarded input sections":
            #print("Discarded")
            s = 'd'
        elif line == "Memory Configuration":
            #print("Memory")
            s = 'm'
        elif line == "Linker script and memory map":
            #print("Linker")
            s = 'l'
        elif line == "Cross Reference Table":
            #print("XRef")
            s = 'x'

        elif s == 'd':
            spl = line.split()
            if len(spl) == 1:
                sym = spl[0]
                continue
            elif len(spl) == 3:
                spl = [ sym ] + spl

            if len(spl) == 4:
                size = int(spl[2], 16)
                #print(spl)
                #print(size)
                dtotal += size

        elif s == 'l':
            if line.startswith("LOAD"):
                continue

            try:
                spl = line.split()
                if len(spl) == 3 and spl[0] == "*fill*":
                    addr = int(spl[1], 16)
                    size = int(spl[2], 16)
                    if addr >= 0x3400 and addr < 0x20000000:
                        fill_total += size
                    continue

                if len(spl) == 1:
                    # Store section name
                    sym = spl[0]
                    continue
                elif len(spl) == 3:
                    # Add section name
                    spl = [ sym ] + spl\

                if len(spl) == 4:
                    section = spl[0]
                    addr = int(spl[1], 16)
                    size = int(spl[2], 16)
                    obj = spl[3]
                    #obj = remove_prefix(obj, ".build/obj_vortex_pok3r_rgb/")
                    #obj = remove_prefix(obj, ".build/obj_vortex_pok3r_rgb_default/")
                    if not obj in omap:
                      omap[obj] = (0, 0, 0, 0)
                      smap[obj] = []

                    if addr >= 0x3400 and addr < 0x20000000:
                      if spl[0].startswith(".text") or spl[0] == ".vectors":
                          text_total += size
                          omap[obj] = (omap[obj][0] + size, omap[obj][1], omap[obj][2], omap[obj][3])
                          smap[obj].append((section, size))

                      elif spl[0].startswith(".rodata"):
                          rodata_total += size
                          omap[obj] = (omap[obj][0], omap[obj][1] + size, omap[obj][2], omap[obj][3])
                          smap[obj].append((section, size))
                      else:
                          #print("flash " + section + " " + str(size))
                          pass

                    elif addr >= 0x20000000:
                      if spl[0].startswith(".data"):
                          data_total += size
                          omap[obj] = (omap[obj][0], omap[obj][1], omap[obj][2] + size, omap[obj][3])
                          smap[obj].append((section, size))

                      elif spl[0].startswith(".bss"):
                          bss_total += size
                          omap[obj] = (omap[obj][0], omap[obj][1], omap[obj][2], omap[obj][3] + size)
                          smap[obj].append((section, size))
                      else:
                          print("ram " + section + " " + str(size))
                          pass
            except:
                pass

    if not objname:
        print("Discarded %d" % dtotal)

        print("{0:>4} {1:>4} {2:>4} {3:>4} {4}".format("text", "ro", "data", "bss", "object"))
        for k in sorted(omap.keys()):
        #for k in sorted(omap, key=lambda k: omap.get(k)[0], reverse=True):
            print("{0:4d} {1:4d} {2:4d} {3:4d} {4}".format(omap[k][0], omap[k][1], omap[k][2], omap[k][3], k))

        print("text %d, rodata %d, data %d, bss %d, fill %d" % (text_total, rodata_total, data_total, bss_total, fill_total))
        print("flash total %d" % (text_total + rodata_total + data_total + fill_total))
        print("ram total %d" % (data_total + bss_total))

    else:
        if objname in smap:
            print(objname)
            tsize = 0
            for sec in smap[objname]:
                print("{1:4d} {0}".format(sec[0], sec[1]))
                tsize += sec[1]
            #print("Total size: " + str(tsize))
