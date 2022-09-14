// number of bytes in array. If you change sprites, minimize for adequate firmware size. max is 1024
#define ANIM_SIZE 96
#define ANIM_LENGTH 2

typedef struct PetAnim {
  char sit[ANIM_LENGTH][ANIM_SIZE];
  char walk[ANIM_LENGTH][ANIM_SIZE];
  char run[ANIM_LENGTH][ANIM_SIZE];
  char noisey[ANIM_LENGTH][ANIM_SIZE];
  char sneak[ANIM_LENGTH][ANIM_SIZE];
} PetAnim;
