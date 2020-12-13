#include "tools.h"

struct s_int_tuple search_BW_pixel(GtkWidget *image)
{
    struct s_int_tuple tuple;

    GdkPixbuf *pixbuf = gtk_image_get_pixbuf ((GtkImage*) image);
    int n_channels = gdk_pixbuf_get_n_channels (pixbuf);
    int rowstride = gdk_pixbuf_get_rowstride (pixbuf);
    int height = gdk_pixbuf_get_height (pixbuf);
    int width = gdk_pixbuf_get_width (pixbuf);

    guchar *which_pixels = gdk_pixbuf_get_pixels (pixbuf);

    tuple.min = 255; //Cannot be superior than 255
    tuple.max = 0; //Cannot be inferior than 0

    //run on each pixel
    for(int y = 0; y < height; ++y)
    {
        for(int x = 0; x < width; ++x)
        {
            guchar *p = which_pixels + y * rowstride + x * n_channels;
            int tmp = (p[0] + p[1] + p[2]) / 3;
            if(tmp < tuple.min)
                tuple.min = tmp;
            if(tmp > tuple.max)
                tuple.max = tmp;
        }
    }
    return tuple;
}

void set_3values(guchar *p, int v1, int v2, int v3)
{
    p[0] = v1;
    p[1] = v2;
    p[2] = v3;
}

void normalized_pixel(guchar *pixel, struct s_int_tuple min_max)
{
    int value;
    if(pixel[0] >= min_max.max)
        value = 255;
    else if(pixel[0] <= min_max.min)
        value = 0;
    else
        value = (pixel[0] - min_max.min) * (255./ (min_max.max - min_max.min));
    set_3values(pixel, value, value, value);
}

int pythagore(int a, int b)
{
    return sqrt((a*a) + (b*b));
}

int max(int a, int b)
{
    if(a < b)
        return b;
    return a;
}

double modulo(double x, double y)
{
    x -= y * abs((int) (x / y));
    return x + (x < 0) * y;  
}