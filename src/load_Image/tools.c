#include "tools.h"

/*
    Search and return the withest and the blackest pixel of a pixbuf
*/
struct s_int_tuple search_BW_pixel(GdkPixbuf *pixbuf)
{
    guchar *p;
    int tmp;
    int tmpmin;
    int tmpmax;
    int min;
    int max;
    struct s_int_tuple tuple;
    

    int rowstride = gdk_pixbuf_get_rowstride (pixbuf);
    int n_channels = gdk_pixbuf_get_n_channels (pixbuf);
    guchar *which_pixels = gdk_pixbuf_get_pixels (pixbuf);
    int height = gdk_pixbuf_get_height (pixbuf);
    int width = gdk_pixbuf_get_width (pixbuf);

    min = 255; //Cannot be superior than 255
    max = 0; //Cannot be inferior than 0

    for(int y = 0; y < height; ++y)
    {
        for(int x = 0; x < width; ++x)
        {
            p = which_pixels + y * rowstride + x * n_channels;
            tmp = (p[0] + p[1] + p[2]) / 3;
            tmpmin = tmp;
            tmpmax = tmp;
            if(tmpmin < min)
                min = tmpmin;
            if(tmpmax > max)
                max = tmpmax;
        }
    }
    tuple.first = min;
    tuple.second = max;
    return tuple;
}


/*
    Return a value of grey corresponding to the pixel in parameters
*/
float change_pixel_greylvl(guchar *pixel)
{
    /*
        pixel[0] => RED
        pixel[1] => GREEN
        pixel[3] => BLUE
    */
    return 0.3 * pixel[0] + 0.59 * pixel[1] + 0.11 * pixel[2];
}