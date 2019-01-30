/* hsv2rgb.c
 * Integer only conversion functions between HSV and RGB
 */

#include "hsv2rgb.h"

// TODO fix these buggy macros
#define max(x,y) ((x>y) ? x:y)
#define min(x,y) ((x>y) ? y:x)
#define min3(x,y,z) (min(min(x,y),z))
#define max3(x,y,z) (max(max(x,y),z))


rgb_color hsv2rgb(hsv_color hsv)
{
  // From : http://qscribble.blogspot.fr/2008/06/integer-conversion-from-hsl-to-rgb.html
  int h = hsv.h;
  int s = hsv.s;
  int v = hsv.v;
  rgb_color rgb = {0, 0, 0};

  if (v == 0)
    return rgb;

  // sextant = 0 .. 5
  int sextant = (h*6)/256;
  // f = 0 .. 42
  int f = h - (sextant*256)/6;

  int p = (v * (256 - s))/256;
  int q = (v * (256*43 - s*f))/(256*43);
  int t = (v * (256*43 - s*(43-f)))/(256*43);

  // Corrige les erreurs dues aux arrondis
  p = max(min(p, 255), 0);
  q = max(min(q, 255), 0);
  t = max(min(t, 255), 0);

  switch(sextant){
  case 0: rgb.r = v; rgb.g = t; rgb.b = p; break;
  case 1: rgb.r = q; rgb.g = v; rgb.b = p; break;
  case 2: rgb.r = p; rgb.g = v; rgb.b = t; break;
  case 3: rgb.r = p; rgb.g = q; rgb.b = v; break;
  case 4: rgb.r = t; rgb.g = p; rgb.b = v; break;
  default:rgb.r = v; rgb.g = p; rgb.b = q; break;
  }
  return rgb;
}


hsv_color rgb2hsv(rgb_color rgb)
{
  // From : http://www.ruinelli.ch/rgb-to-hsv
  hsv_color hsv = {0, 0, 0};
  int min, max, delta;

  min = min3(rgb.r, rgb.g, rgb.b);
  max = max3(rgb.r, rgb.g, rgb.b);

  if(max==0) {
    hsv.h = 0;
    hsv.s = 0;
    hsv.v = 0;
    return hsv;
  }

  hsv.v = max;
  delta = max - min;

  hsv.s = (delta)*255 / max;

  if(rgb.r == max)
    hsv.h = (rgb.g - rgb.b)*42/delta;        // between yellow & magenta
  else if(rgb.g == max)
    hsv.h = 120 + (rgb.b - rgb.r)*42/delta;    // between cyan & yellow
  else
    hsv.h = 240 + (rgb.r - rgb.g)*42/delta;    // between magenta & cyan

  return hsv;
}