import pcbnew

SCALE = 1000000.0
board = pcbnew.GetBoard()

def place_linear(footprints_to_place, ref_fp, step_x, step_y, step, rotation):
    # get proper footprint list
    footprints = []
    for fp in footprints_to_place:
        footprints.append(fp)

    #ref_fp = footprints_to_place[0]

    # get reference footprint position
    ref_fp_pos = ref_fp.GetPosition()
    ref_fp_index = -1 #footprints.index(ref_fp)

    for fp in footprints:
        index = footprints.index(fp)
        delta_index = index-ref_fp_index

        if fp.IsFlipped() != ref_fp.IsFlipped():
            fp.Flip(fp.GetPosition(), False)

        new_position = (ref_fp_pos.x + delta_index*step_x*SCALE, ref_fp_pos.y + delta_index*step_y * SCALE)
        new_position = [int(x) for x in new_position]
        fp.SetPosition(pcbnew.wxPoint(*new_position))
        footprint_angle = ref_fp.GetOrientationDegrees()
        footprint_angle = footprint_angle + index // step * rotation
        fp.SetOrientationDegrees(footprint_angle)

def place_matrix(footprints_to_place, ref_fp, step_x, step_y, col):
    #row = len(footprints_to_place) / col

    #matrix = [footprints_to_place[i:i + col] for i in range(0, len(footprints_to_place), col)]
    #first row
    place_linear(footprints_to_place[:col], ref_fp, step_x, 0, 1, 0)
    for i in range(col):
        place_linear(footprints_to_place[i+col::col], footprints_to_place[i], 0, step_y, 1, 0)
    pcbnew.Refresh()

def get_selected():
    #get list of selected fp
    selected = [x for x in board.GetFootprints() if x.IsSelected()]
    return selected
    #fp_to_place.sort(key=sortByRefNew, reverse=isReverse)
def sort_by_ref(fpList, reversed=False):
    str = fpList[0].GetReference()
    for i, char in enumerate(str):
        # Checking if char is numeric
        if char.isdigit():
            index = i
            break
    fpList.sort(key=lambda x: int(x.GetReference()[index:]), reverse=reversed)
    return fpList
