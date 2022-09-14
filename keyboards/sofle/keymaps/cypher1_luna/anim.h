#define ANIM_SIZE           96   // number of bytes in array. If you change sprites, minimize for adequate firmware size. max is 1024
                                 //
typedef struct Anim {
  char sit[2][ANIM_SIZE];
  char walk[2][ANIM_SIZE];
  char run[2][ANIM_SIZE];
  char bark[2][ANIM_SIZE];
  char sneak[2][ANIM_SIZE];
} Anim;
