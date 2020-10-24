#include "tools.h"

struct s_int_tuple search_BW_pixel(GtkWidget *image)
{
    GdkPixbuf *pixbuf;
    guchar *which_pixels, *p;
    int tmp, n_channels, rowstride, height, width;
    struct s_int_tuple tuple;

    pixbuf = gtk_image_get_pixbuf ((GtkImage*) image);
    n_channels = gdk_pixbuf_get_n_channels (pixbuf);
    rowstride = gdk_pixbuf_get_rowstride (pixbuf);
    height = gdk_pixbuf_get_height (pixbuf);
    width = gdk_pixbuf_get_width (pixbuf);

    which_pixels = gdk_pixbuf_get_pixels (pixbuf);

    tuple.min = 255; //Cannot be superior than 255
    tuple.max = 0; //Cannot be inferior than 0

    //run on each pixel
    for(int y = 0; y < height; ++y)
    {
        for(int x = 0; x < width; ++x)
        {
            p = which_pixels + y * rowstride + x * n_channels;
            tmp = (p[0] + p[1] + p[2]) / 3;
            if(tmp < tuple.min)
                tuple.min = tmp;
            if(tmp > tuple.max)
                tuple.max = tmp;
        }
    }
    return tuple;
}
