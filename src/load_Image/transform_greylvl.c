#include "transform_greylvl.h"


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

    pixbuf = gtk_image_get_pixbuf ((GtkImage*) image_to_change);
    int n_channels = gdk_pixbuf_get_n_channels (pixbuf);
    int rowstride = gdk_pixbuf_get_rowstride (pixbuf);
    int height = gdk_pixbuf_get_height (pixbuf);
    int width = gdk_pixbuf_get_width (pixbuf);

    printf("Tranform into GreyLevel is starting\n");

    which_pixels = gdk_pixbuf_get_pixels (pixbuf);

    for(int y = 0; y < height; ++y)
    {
        for(int x = 0; x < width; ++x)
        {
            pixel = which_pixels + y * rowstride + x * n_channels;
            tmp = change_pixel_greylvl(pixel);
            for(unsigned char i = 0; i < 3; ++i)
                pixel[i] = (int) tmp;
        }
    }

    return image_to_change;
}