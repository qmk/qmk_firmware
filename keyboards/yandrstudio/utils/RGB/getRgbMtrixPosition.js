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

cal = function gen_rgb_matrix_2(rownum, colnum) {
	    function get_x(col, colnum){
	    	var x = 224 / (colnum - 1) * col;
	    	return Math.round(x);
	    }
	    function get_y(row, rownum) {
	    	var y =  64 / (rownum - 1) * row;
	    	return Math.round(y);
	    }
	    var gen_rgb_matrix_text = new String();
	    for (var i = 0; i < colnum; i++) {
	    	var row_rgb_text = new String();
	    	var xx = get_x(i, colnum).toString();
	    	for (var j = 0; j < rownum; j++) {
	    		var yy = get_y(j, rownum).toString();
	    		row_rgb_text += '{' + xx + ',' + yy + '}'
	    		if (i != colnum -1 | j != rownum - 1) {
	    			row_rgb_text += ', ';
	    		}
	    	}
	    	if (i != colnum - 1) {
	    		row_rgb_text += '\n';
	    	}
	    	gen_rgb_matrix_text += row_rgb_text
	    }
	    return gen_rgb_matrix_text
	}
