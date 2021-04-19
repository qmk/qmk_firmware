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