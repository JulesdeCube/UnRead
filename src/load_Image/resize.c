#include "resize.h"

GdkPixbuf *New_Size_Image(GtkWidget *image, int newHeight, int newWidth)
{
    // Informations about the old pixbuf
    GdkPixbuf *pixbuf = gtk_image_get_pixbuf ((GtkImage*) image);
    int n_channels = gdk_pixbuf_get_n_channels (pixbuf);
    int oldRowstride = gdk_pixbuf_get_rowstride (pixbuf);
    int height = gdk_pixbuf_get_height (pixbuf);
    int width = gdk_pixbuf_get_width (pixbuf);
    guchar *old_which_pixels = gdk_pixbuf_get_pixels (pixbuf);

    // Informations about the new pixbuf
    GdkPixbuf *newpixbuf = gdk_pixbuf_new (GDK_COLORSPACE_RGB, 0, 8, newWidth, newHeight);
    int newRowstride = gdk_pixbuf_get_rowstride (newpixbuf);
    guchar *new_which_pixels = gdk_pixbuf_get_pixels (newpixbuf);

    // Image ratio on each size
    double x_ratio =  (double) width / newWidth;
    double y_ratio =  (double) height / newHeight;
    
    guchar *newp, *oldp;
    for(int y = 0; y < newHeight; ++y)
    {
        for(int x = 0; x < newWidth; ++x)
        {
            // Get X and Y of the old pixbuf
            int old_x = x * width / newWidth;
            int old_y = y * height / newHeight;

            double x_pix = x_ratio * x - old_x;
            double y_pix = y_ratio * y - old_y;
            newp = new_which_pixels + y * newRowstride + x * n_channels;
            oldp = old_which_pixels + old_y * oldRowstride + old_x * n_channels;
            
            // To change RGB values from old pixel to new pixel
            for(unsigned char i = 0; i < 3; ++i)
            {
                // Linear stretching (work only on x)
                newp[i] = (1 - y_pix) * (oldp[i] * (1 - x_pix) + oldp[i+3] * x_pix) + 
                          y_pix * (oldp[i] * (1 - x_pix) +
                          oldp[i+3]
                            * x_pix);
            }      
        }
    }
    //gdk_pixbuf_save(newpixbuf, "src/load_Image/images/img.bmp", "bmp", NULL, NULL);
    //gtk_image_set_from_pixbuf (GTK_IMAGE(image), newpixbuf);
    return newpixbuf;
}

