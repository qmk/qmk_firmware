uint8_t matrix_scan(void)
{
    uint8_t mchanged;
    uint8_t row;
    uint8_t col;
    uint32_t scans[2]; //PA PB

    if (timer_read64() < mdebouncing) return 1; //mdebouncing == 0 when no debouncing active

    memset(mlatest, 0, MATRIX_ROWS * sizeof(matrix_row_t)); //Zero the result buffer

    for (col = 0; col < MATRIX_COLS; col++)
    {
        PORT->Group[col_ports[col]].OUTSET.reg = 1 << col_pins[col]; //Set col output

        wait_us(40); //Delay for output

        scans[PA] = PORT->Group[PA].IN.reg & row_masks[PA]; //Read PA row pins data
        scans[PB] = PORT->Group[PB].IN.reg & row_masks[PB]; //Read PB row pins data

        PORT->Group[col_ports[col]].OUTCLR.reg = 1 << col_pins[col]; //Clear col output

        for (row = 0; row < MATRIX_ROWS; row++)
        {
            //Move scan bits from scans array into proper row bit locations
            if (scans[row_ports[row]] & (1 << row_pins[row]))
                mlatest[row] |= 1 << col;
        }
    }

    mchanged = 0; //Default to no matrix change since last

    for (row = 0; row < MATRIX_ROWS; row++)
    {
        if (mlast[row] != mlatest[row])
            mchanged = 1;
        mlast[row] = mlatest[row];
    }

    if (!mchanged)
    {
        for (row = 0; row < MATRIX_ROWS; row++)
            mdebounced[row] = mlatest[row];
        mdebouncing = 0;
    }
    else
    {
        //Begin or extend debounce on change
        mdebouncing = timer_read64() + DEBOUNCE;
    }

    matrix_scan_quantum();

    return 1;
}