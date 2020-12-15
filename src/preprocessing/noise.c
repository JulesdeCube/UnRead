#include "noise.h"

void remove_noise_image(GtkWidget *image, int radius)
{
    // Image informations
    GdkPixbuf *pixbuf = gtk_image_get_pixbuf((GtkImage *)image);
    int n_channels = gdk_pixbuf_get_n_channels(pixbuf);
    int rowstride = gdk_pixbuf_get_rowstride(pixbuf);
    int height = gdk_pixbuf_get_height(pixbuf);
    int width = gdk_pixbuf_get_width(pixbuf);
    guchar *which_pixels = gdk_pixbuf_get_pixels(pixbuf);

    // Copy of the image
    GdkPixbuf *newpixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, 0, 8, width, height);
    guchar *new_which_pixels = gdk_pixbuf_get_pixels(newpixbuf);

    struct s_int_tuple min_max = search_BW_pixel(image);

    guchar *p_choose, *p_new, *p_test;
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            p_choose = which_pixels + y * rowstride + x * n_channels;
            p_new = new_which_pixels + y * rowstride + x * n_channels;

            //Copy the pixel on the new pixel buffer
            set_3values(p_new, p_choose[0], p_choose[1], p_choose[2]);

            //Get coordinates to not be out of the pixel buffer
            int y_min = CLAMP(y - radius, 0, height - 1);
            int y_max = CLAMP(y + radius, 0, height - 1);
            int x_min = CLAMP(x - radius, 0, width - 1);
            int x_max = CLAMP(x + radius, 0, width - 1);
            int density = 0;
            for (int y_f = y_min; y_f <= y_max; ++y_f)
            {
                for (int x_f = x_min; x_f <= x_max; ++x_f)
                {
                    p_test = which_pixels + y_f * rowstride + x_f * n_channels;
                    if (p_test[0] <= min_max.max - min_max.min)
                        ++density;
                }
            }
            if (density <= 2 * radius)
                set_3values(p_new, 255, 255, 255);
        }
    }
    // Update the image
    gtk_image_set_from_pixbuf(GTK_IMAGE(image), newpixbuf);
}