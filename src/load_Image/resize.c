#include "resize.h"

void New_Size_Image(GtkWidget *image, int newHeight, int newWidth)
{
    //GtkWidget *newimage;
    GdkPixbuf *newpixbuf, *pixbuf;
    int n_channels, oldRowstride, height, width;
    guchar *newp, *oldp, *new_which_pixels, *old_which_pixels;

    pixbuf = gtk_image_get_pixbuf ((GtkImage*) image);
    n_channels = gdk_pixbuf_get_n_channels (pixbuf);
    oldRowstride = gdk_pixbuf_get_rowstride (pixbuf);
    height = gdk_pixbuf_get_height (pixbuf);
    width = gdk_pixbuf_get_width (pixbuf);
    old_which_pixels = gdk_pixbuf_get_pixels (pixbuf);



    newpixbuf = gdk_pixbuf_new (GDK_COLORSPACE_RGB, 0, 8, newWidth, newHeight);
    int newRowstride = gdk_pixbuf_get_rowstride (newpixbuf);
    new_which_pixels = gdk_pixbuf_get_pixels (newpixbuf);

    for(int y = 0; y < newHeight; ++y)
    {
        for(int x = 0; x < newWidth; ++x)
        {
            newp = new_which_pixels + y * newRowstride + x * n_channels;
            //oldp = old_which_pixels + y * (height / newHeight) * oldRowstride + x * (width / newWidth) * n_channels;
            oldp = old_which_pixels + y * oldRowstride + x * n_channels;
            for(unsigned char i = 0; i < 3; ++i)
                newp[i] = oldp[i];
        }
    }

    gdk_pixbuf_save(newpixbuf, "src/load_Image/Images/img.bmp", "bmp", NULL, NULL);
}