#include "transform_BW.h"

//return the approximative value of the whitest pixel
int blackest_pixel(GdkPixbuf *pixbuf)
{
    guchar *p;
    int tmp;
    int min;

    int rowstride = gdk_pixbuf_get_rowstride (pixbuf);
    int n_channels = gdk_pixbuf_get_n_channels (pixbuf);
    guchar *which_pixels = gdk_pixbuf_get_pixels (pixbuf);
    int height = gdk_pixbuf_get_height (pixbuf);
    int width = gdk_pixbuf_get_width (pixbuf);

    min = 255; //Cannot be superior than 255
    
    for(int y = 0; y < height; ++y)
    {
        for(int x = 0; x < width; ++x)
        {
            p = which_pixels + y * rowstride + x * n_channels;
            tmp = (p[0] + p[1] + p[2]) / 3;
            if(tmp < min)
                min = tmp;
        }
    }
    return min;
}


//return the approximative value of the whitest pixel
int whitest_pixel(GdkPixbuf *pixbuf)
{
    guchar *p;
    int tmp;
    int max;

    int rowstride = gdk_pixbuf_get_rowstride (pixbuf);
    int n_channels = gdk_pixbuf_get_n_channels (pixbuf);
    guchar *which_pixels = gdk_pixbuf_get_pixels (pixbuf);
    int height = gdk_pixbuf_get_height (pixbuf);
    int width = gdk_pixbuf_get_width (pixbuf);

    max = 0;
    
    for(int y = 0; y < height; ++y)
    {
        for(int x = 0; x < width; ++x)
        {
            p = which_pixels + y * rowstride + x * n_channels;
            tmp = (p[0] + p[1] + p[2]) / 3;
            if(tmp > max)
                max = tmp;
        }
    }
    return max;
}


GtkWidget* image_to_BW_binary (GtkWidget* image_to_change)
{
    GdkPixbuf *pixbuf;
    int n_bits;
    guchar *which_pixels;
    guchar *p;
    int tmp;

    pixbuf = gtk_image_get_pixbuf ((GtkImage*) image_to_change);
    int n_channels = gdk_pixbuf_get_n_channels (pixbuf);
    int rowstride = gdk_pixbuf_get_rowstride (pixbuf);
    int height = gdk_pixbuf_get_height (pixbuf);
    int width = gdk_pixbuf_get_width (pixbuf);

    printf("TEST for BW\n");

    printf("Taille : %d\n", n_channels);

    n_bits = gdk_pixbuf_get_bits_per_sample (pixbuf);
    printf("Bits per sample : %d\n", n_bits);

    which_pixels = gdk_pixbuf_get_pixels (pixbuf);
    /*printf("Pixels Red : %hhu\n", *which_pixels);
    printf("Pixels Green : %hhu\n", which_pixels[1]);
    which_pixels += 2;
    printf("Pixels Blue : %hhu\n", *which_pixels);*/

    
    int white_max = whitest_pixel(pixbuf);
    printf("The whitest pixel is approximatively : %d\n", white_max);
    int black_min = blackest_pixel(pixbuf);
    printf("The blackest pixel is approximatively : %d\n", black_min);

    int medium = (white_max - black_min) /2;

    for(int y = 0; y < height; ++y)
    {
        for(int x = 0; x < width; ++x)
        {
            p = which_pixels + y * rowstride + x * n_channels;
            tmp = (p[0] + p[1] + p[2]) / 3;
            if(tmp <= black_min + medium)
            {
                p[0] = 0;
                p[1] = 0;
                p[2] = 0;
            }
            else
            {
                p[0] = 255;
                p[1] = 255;
                p[2] = 255;
            }
        }
    }


    UNUSED(n_bits);

    return image_to_change;
}