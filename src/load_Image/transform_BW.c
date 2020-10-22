#include "transform_BW.h"

/*
    Change your image into the same but in black and white binary
        -take the withest and blackest pîxel
        -take the medium =  (whitest - blackest) /2
        -each pixel under medium will be black and each pixel upper medium will be white
    Return image with only white and black pixels
*/
GtkWidget* image_to_BW_binary (GtkWidget* image_to_change)
{
    GdkPixbuf *pixbuf;
    guchar *which_pixels;
    guchar *pixel;
    int tmp;
    int applied_color;
    struct s_int_tuple tuple;

    pixbuf = gtk_image_get_pixbuf ((GtkImage*) image_to_change);
    int n_channels = gdk_pixbuf_get_n_channels (pixbuf);
    int rowstride = gdk_pixbuf_get_rowstride (pixbuf);
    int height = gdk_pixbuf_get_height (pixbuf);
    int width = gdk_pixbuf_get_width (pixbuf);

    printf("Tranform into Black and White Binary is starting\n");

    which_pixels = gdk_pixbuf_get_pixels(pixbuf);

    tuple = search_BW_pixel(pixbuf);
    int white_max = tuple.second;
    int black_min = tuple.first;
    int medium = (white_max - black_min) /2;

    for(int y = 0; y < height; ++y)
    {
        for(int x = 0; x < width; ++x)
        {
            pixel = which_pixels + y * rowstride + x * n_channels;

            /*
                pixel[0] => RED
                pixel[1] => GREEN
                pixel[3] => BLUE
            */
            tmp = (pixel[0] + pixel[1] + pixel[2]) / 3;
            
            if(tmp <= black_min + medium)
                applied_color = 0;
            else
                applied_color = 255;
            for(unsigned char i = 0; i < 3; ++i)
                pixel[i] = applied_color;

        }
    }

    return image_to_change;
}