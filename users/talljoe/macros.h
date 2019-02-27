typedef enum OSTYPE {
  WINDOWS,
  MACOSX,
  LINUX
} ostype_t;

ostype_t get_os(void);

void macro_copy(void);
void macro_paste(void);
void macro_lock(void);
