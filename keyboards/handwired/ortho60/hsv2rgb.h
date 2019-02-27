/* hsv2rgb.h
 * Convert Hue Saturation Value to Red Green Blue
 *
 * Programme de convertion d'une information HSV en RGB
 */
#ifndef HSV2RGB_H
#define HSV2RGB_H

typedef struct {
  unsigned char h;
  unsigned char s;
  unsigned char v;
} hsv_color;

typedef struct {
  unsigned char r;
  unsigned char g;
  unsigned char b;
} rgb_color;

rgb_color hsv2rgb(hsv_color hsv);

#endif