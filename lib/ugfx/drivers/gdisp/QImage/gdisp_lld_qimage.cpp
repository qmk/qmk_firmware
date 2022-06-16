#include <QImage>
#include "../../../gfx.h"
#include "../../../src/gdisp/gdisp_driver.h"
#include "gdisp_lld_qimage.h"

gBool qimage_init(GDisplay* g, gCoord width, gCoord height)
{
    QImage* qimage = new QImage(width, height, QImage::Format_RGB888);
    if (!qimage) {
        return gFalse;
    }
    qimage->fill(Qt::gray);

    g->priv = qimage;

    return gTrue;
}

void qimage_setPixel(GDisplay* g)
{
    QImage* qimage = static_cast<QImage*>(g->priv);
    if (!qimage) {
        return;
    }

    QRgb rgbVal = qRgb(RED_OF(g->p.color), GREEN_OF(g->p.color), BLUE_OF(g->p.color));
    qimage->setPixel(g->p.x, g->p.y, rgbVal);
}

gColor qimage_getPixel(GDisplay* g)
{
    const QImage* qimage = static_cast<const QImage*>(g->priv);
    if (!qimage) {
        return 0;
    }

    return static_cast<gColor>(qimage->pixel(g->p.x, g->p.y));
}
