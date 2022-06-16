#ifndef _JG10_H_
#define _JG10_H_

#define JG10_CELL_WIDTH         54
#define JG10_CELL_HEIGHT        54
#define JG10_FIELD_WIDTH        5
#define JG10_FIELD_HEIGHT       5
#define JG10_TOTAL_FIELD_WIDTH  (JG10_FIELD_WIDTH*JG10_CELL_WIDTH)
#define JG10_TOTAL_FIELD_HEIGHT (JG10_FIELD_HEIGHT*JG10_CELL_HEIGHT)
#define JG10_SEL_COLOR          GFX_YELLOW
#define JG10_MAX_COUNT          21          // Max number you can get +1, so if max number would be 20, then this number should be 21 (+ background)

void jg10Init(void);
void jg10Start(void);
#if JG10_SHOW_SPLASH
    void jg10ShowSplash(void);
#endif

#endif  /* _JG10_H_ */