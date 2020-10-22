#include "transform_greylvl.h"


/*
    Transform an image to the same into grey level
        -it runs each and replace it with grey level associate
    Return the same image into grey level
*/
GtkWidget* image_to_greylvl (GtkWidget* image_to_change)
{
    GdkPixbuf *pixbuf;
    guchar *which_pixels;
    guchar *pixel;
    float tmp;
    struct s_int_tuple tuple;
    int min;
    int max;

    pixbuf = gtk_image_get_pixbuf ((GtkImage*) image_to_change);
    int n_channels = gdk_pixbuf_get_n_channels (pixbuf);
    int rowstride = gdk_pixbuf_get_rowstride (pixbuf);
    int height = gdk_pixbuf_get_height (pixbuf);
    int width = gdk_pixbuf_get_width (pixbuf);

    printf("Tranform into GreyLevel is starting\n");

    which_pixels = gdk_pixbuf_get_pixels (pixbuf);

    printf("Start (color are not change)\n");
    tuple = search_BW_pixel(pixbuf);
    max = tuple.second;
    printf("Max : %d\n", max);
    min = tuple.first;
    printf("Min : %d\n", min);

    for(int y = 0; y < height; ++y)
    {
        for(int x = 0; x < width; ++x)
        {
            pixel = which_pixels + y * rowstride + x * n_channels;
            tmp = change_pixel_greylvl(pixel);

            for(unsigned char i = 0; i < 3; ++i)
                pixel[i] = tmp;
                
        }
    }

    printf("Classic grey Level\n");
    tuple = search_BW_pixel(pixbuf);
    max = tuple.second;
    printf("Max : %d\n", max);
    min = tuple.first;
    printf("Min : %d\n", min);

    int newcolor;
    for(int y = 0; y < height; ++y)
    {
        for(int x = 0; x < width; ++x)
        {
            pixel = which_pixels + y * rowstride + x * n_channels;
            newcolor = (pixel[0] - min) * (255./ (max - min));
            for(unsigned char i = 0; i < 3; ++i)
                pixel[i] = newcolor;
        }
    }

     printf("Normalized grey Level\n");
    tuple = search_BW_pixel(pixbuf);
    max = tuple.second;
    printf("Max : %d\n", max);
    min = tuple.first;
    printf("Min : %d\n", min);
    return image_to_change;
}


//- min value * (256 / max - min)