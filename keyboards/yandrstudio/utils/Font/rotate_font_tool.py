import font_user
# print(font_user.font)
# one_f = [0x3E, 0x5B, 0x4F, 0x5B, 0x3E, 0x00]

cur_H = 8
cur_W = 6

aim_H = 6
aim_W = 8

def cvo(one_f):
    new_one_f = []
    cols_old_t = []
    for f_c in one_f:
        c = bin(f_c)[2:].ljust(8, '0')[::-1]
        cols_old_t.append(c)
    for i in range(aim_W):
        cur_str=''
        for j in range(cur_W):
            cur_str += cols_old_t[j][i]
        cur_str += '00'
        new_one_f.append(hex(int(cur_str,2)))
    return new_one_f
# print(','.join(new_one_f))
# new_one_f.append(int(c,2))

f_num = len(font_user.font)//cur_W

new_font=[]
for i in range(f_num):
    one_f = []
    for j in range(cur_W):
        one_f.append(i*cur_W+j)
    st = cvo(one_f)
    st = ','.join(st)+','
    new_font.append(st)
for i in new_font:
    print(i)
