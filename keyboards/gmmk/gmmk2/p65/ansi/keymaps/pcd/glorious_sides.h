// Side LED Arrays
int side1[] = {67,68,69,70,71,72,73,74,75,76};
int side2[] = {77,78,79,80,81,82,83,84,85,86};

void set_glorious_side(char glorious_side, uint8_t r, uint8_t g, uint8_t b){
    uint8_t rgb[3];
    rgb[0] = r;
    rgb[1] = g;
    rgb[2] = b;
    int* this_side;
    if(glorious_side == 'r'){this_side = side1;}
    else {this_side = side2;}
    for(int i = 0; i < 9; i++ ){
        rgb_matrix_set_color(this_side[i], rgb[0], rgb[1], rgb[2]);
    }
}
