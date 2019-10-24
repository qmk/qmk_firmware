
#include "bmp_matrix.h"
#include "quantum.h"
#include "apidef.h"

static void init_row2col();
static void init_col2row();
static uint32_t get_device_row() { return BMPAPI->app.get_config()->matrix.rows; };
static uint32_t get_device_col() { return BMPAPI->app.get_config()->matrix.cols; };
static uint32_t scan_row2col();
static uint32_t scan_col2row();
extern const bmp_matrix_func_t matrix_func_row2col;
extern const bmp_matrix_func_t matrix_func_col2row;

const bmp_matrix_func_t matrix_func_row2col2row = {init_row2col, get_device_row, get_device_col, scan_row2col};
const bmp_matrix_func_t matrix_func_col2row2col = {init_col2row, get_device_row, get_device_col, scan_col2row};

//
//// col2row matrix
//
static void init_col2row() {
    matrix_func_col2row.init();
}

static uint32_t scan_col2row(matrix_row_t *matrix_raw)
{
    const bmp_api_config_t *config = BMPAPI->app.get_config();
    uint8_t matrix_offset = 0;
    uint32_t change = 0;

    matrix_func_col2row.init();
    change |= matrix_func_col2row.scan(matrix_raw);

    matrix_offset = config->matrix.device_rows;
    matrix_func_row2col.init();
    change |= matrix_func_row2col.scan(&matrix_raw[matrix_offset]);

    return change;
}

//
//// row2col matrix
//
static void init_row2col() {
    matrix_func_row2col.init();
}

static uint32_t scan_row2col(matrix_row_t *matrix_raw)
{
    const bmp_api_config_t *config = BMPAPI->app.get_config();
    uint8_t matrix_offset = 0;
    uint32_t change = 0;

    matrix_func_row2col.init();
    change |= matrix_func_row2col.scan(matrix_raw);

    matrix_offset = config->matrix.device_rows;
    matrix_func_col2row.init();
    change |= matrix_func_col2row.scan(&matrix_raw[matrix_offset]);

    return change;
}
