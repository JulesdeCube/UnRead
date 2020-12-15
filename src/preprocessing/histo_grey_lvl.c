#include "histo_grey_lvl.h"

void histo_greylvl(GtkWidget *image, double black_percent, double white_percent)
{
    // Get great percentage to do not make errors
    white_percent = modulo(white_percent, 100);
    black_percent = modulo(black_percent, 100);

    // Get all informations about the image
    GdkPixbuf *pixbuf = gtk_image_get_pixbuf((GtkImage *)image);
    int n_channels = gdk_pixbuf_get_n_channels(pixbuf);
    int rowstride = gdk_pixbuf_get_rowstride(pixbuf);
    int height = gdk_pixbuf_get_height(pixbuf);
    int width = gdk_pixbuf_get_width(pixbuf);
    guchar *which_pixels = gdk_pixbuf_get_pixels(pixbuf);

    // Initialize the histogram to 0
    const int size_histo = 256;
    int histo[size_histo];
    for (int i = 0; i < size_histo; ++i)
        histo[i] = 0;

    // Make histogram with all pixels
    guchar *p;
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            p = which_pixels + y * rowstride + x * n_channels;
            ++histo[p[0]];
        }
    }

    // How many pixels there is in the picture
    double n_pix = height * width;

    // Work on whitest
    double when_stop_white = white_percent * n_pix / 100;
    double temp_white = 0;
    int withest = 0;
    while (withest < size_histo && temp_white < when_stop_white)
    {
        temp_white += histo[withest];
        ++withest;
    }

    // Work on blackest
    double when_stop_black = black_percent * n_pix / 100;
    double temp_black = 0;
    int blackest = 0;
    while (blackest < size_histo && temp_black < when_stop_black)
    {
        temp_black += histo[blackest];
        ++blackest;
    }

    // Apply normalization on each pixel
    struct s_int_tuple tuple;
    tuple.min = blackest;
    tuple.max = withest;
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            p = which_pixels + y * rowstride + x * n_channels;
            normalized_pixel(p, tuple);
        }
    }
}
