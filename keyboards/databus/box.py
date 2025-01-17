#!/ bin / env python3
#Created / amended by OleVoip 2024.
#SPDX - License - Identifier : GPL - 2.0 - or -later

BOX_C = (None,None,None,'┌','','│','└','├',None,'┐','─','┬','┘','┤','┴','┼')
BOX_BITP = {k: i for i, k in enumerate(BOX_C)}
def comb(c_old, c_new):
  try:
    return BOX_C[BOX_BITP[c_old] | BOX_BITP[c_new]]
  except KeyError:
    return c_new
for c1 in BOX_C:
  for c2 in BOX_C:
    if c1 is not None and c2 is not None: 
      print(c1,c2,comb(c1,c2))
