#include "resize_char.h"

#define SIZE_OF_IMAGE_CHAR 28

double *get_great_char(GtkWidget *image)
{
    // Informations about the old pixbuf
    GdkPixbuf *pixbuf = gtk_image_get_pixbuf((GtkImage *)image);
    float h = gdk_pixbuf_get_height(pixbuf);
    float w = gdk_pixbuf_get_width(pixbuf);
    float ratio;
    if (h > w)
        ratio = h / SIZE_OF_IMAGE_CHAR;
    else
        ratio = w / SIZE_OF_IMAGE_CHAR;
    int height = h / ratio;
    int width = w / ratio;
    // Resize the image
    pixbuf = New_Size_Image(image, height, width);
    int n_channels = gdk_pixbuf_get_n_channels(pixbuf);
    int oldRowstride = gdk_pixbuf_get_rowstride(pixbuf);
    guchar *old_which_pixels = gdk_pixbuf_get_pixels(pixbuf);

    // Informations about the new pixbuf
    GdkPixbuf *newpixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, 0, 8,
                                          SIZE_OF_IMAGE_CHAR, SIZE_OF_IMAGE_CHAR);
    int newRowstride = gdk_pixbuf_get_rowstride(newpixbuf);
    guchar *new_which_pixels = gdk_pixbuf_get_pixels(newpixbuf);

    // Get coordinates of the old pixbuf, to put it on the middle
    int start_height = abs(height - SIZE_OF_IMAGE_CHAR) / 2;
    int end_height = start_height + height;
    int start_width = abs(width - SIZE_OF_IMAGE_CHAR) / 2;
    int end_width = start_width + width;

    // Build the array of double
    size_t count = SIZE_OF_IMAGE_CHAR * SIZE_OF_IMAGE_CHAR;
    double *array = malloc(count * sizeof(double));

    // Make new image with old pixbuf and put other pixels in white
    guchar *p_new, *p_old;
    for (int y = 0; y < SIZE_OF_IMAGE_CHAR; ++y)
    {
        for (int x = 0; x < SIZE_OF_IMAGE_CHAR; ++x)
        {
            p_new = new_which_pixels + y * newRowstride + x * n_channels;
            if (x < start_width || x >= end_width || y < start_height || y >= end_height)
            {
                set_3values(p_new, 255, 255, 255);
            }
            else
            {
                p_old = old_which_pixels + (y - start_height) * oldRowstride +
                        (x - start_width) * n_channels;
                set_3values(p_new, p_old[0], p_old[1], p_old[2]);
            }

            array[x + y] = (double)p_new[0] / 255.;
        }
    }
    return array;
}