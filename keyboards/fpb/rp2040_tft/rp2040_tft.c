#include "rp2040_tft.h"

#include <qp.h>
//#include <qp_lvgl.h>

//#include <lvgl.h>


#include "graphics/Apple-Orchard-128x160.qgf.h"
#include "graphics/qmklogo.qgf.h"

static painter_device_t qp_display;
static painter_image_handle_t qp_image;

void keyboard_post_init_kb(void) {
    //qp_display = qp_st7735_make_spi_device(
    qp_display = qp_gc9107_make_spi_device(
        PANEL_WIDTH, 
        PANEL_HEIGHT, 
        PANEL_CS, 
        PANEL_DC, 
        PANEL_RST, 
        8, //spi_divisor, 
        0  //spi_mode
    );         // Create the display
    qp_init(qp_display, QP_ROTATION_180);   // Initialise the display
    qp_rect(qp_display, 0, 0, PANEL_WIDTH, PANEL_HEIGHT, 128, 255, 255, true);
    
    // if (qp_lvgl_attach(display)) {     // Attach LVGL to the display
    //     //...Your code to draw           // Run LVGL specific code to draw
    // }
    qp_image = qp_load_image_mem(gfx_qmklogo);
    qp_drawimage(qp_display, 0, 0, qp_image);

    // if (qp_lvgl_attach(qp_display)) {     // Attach LVGL to the display
    //     lv_obj_t * label1 = lv_label_create(lv_display_get_screen_active());
    //     lv_label_set_long_mode(label1, LV_LABEL_LONG_WRAP);     /*Break the long lines*/
    //     lv_label_set_text(label1, "Recolor is not supported for v9 now.");
    //     lv_obj_set_width(label1, 150);  /*Set smaller width to make the lines wrap*/
    //     lv_obj_set_style_text_align(label1, LV_TEXT_ALIGN_CENTER, 0);
    //     lv_obj_align(label1, LV_ALIGN_CENTER, 0, -40);

    //     lv_obj_t * label2 = lv_label_create(lv_screen_active());
    //     lv_label_set_long_mode(label2, LV_LABEL_LONG_SCROLL_CIRCULAR);     /*Circular scroll*/
    //     lv_obj_set_width(label2, 150);
    //     lv_label_set_text(label2, "It is a circularly scrolling text. ");
    //     lv_obj_align(label2, LV_ALIGN_CENTER, 0, 40);
    // }


    return keyboard_post_init_user();
}

void housekeeping_task_kb(void) {
    static uint32_t last_draw = 0;
    if (timer_elapsed32(last_draw) > 33) { // Throttle to 30fps
        last_draw = timer_read32();
        // Draw 8px-wide rainbow down the left side of the display
        for (int i = 0; i < PANEL_WIDTH; ++i) {
            qp_line(qp_display, i, 0, i, 7, i, 255, 255);
        }
        qp_flush(qp_display);
    }
}

