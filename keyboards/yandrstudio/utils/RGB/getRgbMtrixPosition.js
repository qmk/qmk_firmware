/* Copyright 2021 JasonRen(biu)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

cal_z_rgb = function gen_rgb_matrix_1(rownum, colnum) {
	    function get_x(col, colnum){
	    	var x = 224 / (colnum - 1) * col;
	    	return Math.round(x);
	    }
	    function get_y(row, rownum) {
	    	var y =  64 / (rownum - 1) * row;
	    	return Math.round(y);
	    }
	    var gen_rgb_matrix_text = new String();
	    for (var i = 0; i < rownum; i++) {
	    	var row_rgb_text = new String();
	    	var yy = get_y(i, rownum).toString();
	    	for (var j = 0; j < colnum; j++) {
	    		var xx = get_x(j, colnum).toString();
	    		row_rgb_text += '{' + xx + ',' + yy + '}'
	    		if (i != rownum -1 | j != colnum - 1) {
	    			row_rgb_text += ', ';
	    		}
	    	}
	    	if (i != rownum - 1) {
	    		row_rgb_text += '\n';
	    	}
	    	gen_rgb_matrix_text += row_rgb_text
	    }
	    return gen_rgb_matrix_text
	}

cal_u_rgb = function gen_rgb_matrix_2(rownum, colnum, reverse) {
    function get_x(col, colnum){
        var x = 224 / (colnum - 1) * col;
        return Math.round(x);
    }
    function get_y(row, rownum) {
        var y =  64 / (rownum - 1) * row;
        return Math.round(y);
    }
    var gen_rgb_matrix_text = new String();
    for (var i = 0; i < rownum; i++) {
        var row_rgb_text = new String();
        var yy = get_y(i, rownum).toString();
        var cnd = 0;
        if (reverse) {
            cnd = 1;
        }
        if (i % 2 == cnd) {
            for (var j = 0; j < colnum; j++) {
                var xx = get_x(j, colnum).toString();
                row_rgb_text += '{' + xx + ',' + yy + '}'
                if (i != rownum -1 | j != colnum - 1) {
                    row_rgb_text += ', ';
                }
            }
        } else {
            for (var j = colnum-1; j >= 0; j--) {
                var xx = get_x(j, colnum).toString();
                row_rgb_text += '{' + xx + ',' + yy + '}'
                if (i != rownum -1 | j != 0) {
                    row_rgb_text += ', ';
                }
            }
        }

        if (i != rownum - 1) {
            row_rgb_text += '\n';
        }
        gen_rgb_matrix_text += row_rgb_text
    }
    return gen_rgb_matrix_text
}


cal_u_rgb_sb_l = function gen_rgb_matrix_3(rownum, colnum, reverse) {
    function get_x(col, colnum){
        var x = 224 / (colnum - 1) * col;
        return Math.round(x);
    }
    function get_y(row, rownum) {
        var y =  64 / (rownum - 1) * row;
        return Math.round(y);
    }
    var gen_rgb_matrix_text = new String();
    for (var i = 0; i < rownum; i++) {
        var row_rgb_text = new String();
        var yy = get_y(i, rownum).toString();
        var cnd = 0;
        if (reverse) {
            cnd = 1;
        }
        if (i % 2 == cnd) {
            for (var j = 0; j < colnum/2; j++) {
                var xx = get_x(j, colnum).toString();
                row_rgb_text += '{' + xx + ',' + yy + '}'
                if (i != rownum -1 | j != colnum - 1) {
                    row_rgb_text += ', ';
                }
            }
        } else {
            for (var j = colnum/2-1; j >= 0; j--) {
                var xx = get_x(j, colnum).toString();
                row_rgb_text += '{' + xx + ',' + yy + '}'
                if (i != rownum -1 | j != 0) {
                    row_rgb_text += ', ';
                }
            }
        }

        if (i != rownum - 1) {
            row_rgb_text += '\n';
        }
        gen_rgb_matrix_text += row_rgb_text
    }
    return gen_rgb_matrix_text
}

cal_u_rgb_sb_r = function gen_rgb_matrix_4(rownum, colnum, reverse) {
    function get_x(col, colnum){
        var x = 224 / (colnum - 1) * col;
        return Math.round(x);
    }
    function get_y(row, rownum) {
        var y =  64 / (rownum - 1) * row;
        return Math.round(y);
    }
    var gen_rgb_matrix_text = new String();
    for (var i = 0; i < rownum; i++) {
        var row_rgb_text = new String();
        var yy = get_y(i, rownum).toString();
        var cnd = 0;
        if (reverse) {
            cnd = 1;
        }
        if (i % 2 == cnd) {
            for (var j = colnum/2; j < colnum; j++) {
                var xx = get_x(j, colnum).toString();
                row_rgb_text += '{' + xx + ',' + yy + '}'
                if (i != rownum -1 | j != colnum - 1) {
                    row_rgb_text += ', ';
                }
            }
        } else {
            for (var j = colnum-1; j >= colnum/2; j--) {
                var xx = get_x(j, colnum).toString();
                row_rgb_text += '{' + xx + ',' + yy + '}'
                if (i != rownum -1 | j != 0) {
                    row_rgb_text += ', ';
                }
            }
        }

        if (i != rownum - 1) {
            row_rgb_text += '\n';
        }
        gen_rgb_matrix_text += row_rgb_text
    }
    return gen_rgb_matrix_text
}



cal_a_row_rgb = function gen_rgb_matrix_5(row, rownum, colnum, reverse) {
    function get_x(col, colnum){
        var x = 224 / (colnum - 1) * col;
        return Math.round(x);
    }
    function get_y(row, rownum) {
        var y =  64 / (rownum - 1) * row;
        return Math.round(y);
    }
    var row_rgb_text = new String();
    var yy = get_y(row, rownum).toString();

    if (reverse) {
        for (var j = colnum-1; j >= 0; j--) {
            var xx = get_x(j, colnum).toString();
            row_rgb_text += '{' + xx + ',' + yy + '},'
        }
    } else {
        for (var j = 0; j < colnum; j++) {
            var xx = get_x(j, colnum).toString();
            row_rgb_text += '{' + xx + ',' + yy + '},'
        }
    }

    return row_rgb_text
}
