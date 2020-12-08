#include "rotate.h"

void apply_rotation(GtkWidget* image, bool has_inverse_HW,
                    guchar* filter(int, int, guchar *, int, int , int , int))
{
    GdkPixbuf *pixbuf, *newpixbuf;
    guchar *which_pixels, *oldp, *new_which_pixels, *newp;
    int n_channels, rowstride, height, width, newheight, newwidth;

    // All informations to take of the pixbuffer
    pixbuf = gtk_image_get_pixbuf ((GtkImage*) image);
    n_channels = gdk_pixbuf_get_n_channels (pixbuf);
    rowstride = gdk_pixbuf_get_rowstride (pixbuf);
    height = gdk_pixbuf_get_height (pixbuf);
    width = gdk_pixbuf_get_width (pixbuf);
    which_pixels = gdk_pixbuf_get_pixels (pixbuf);
    
    // To inverse width and height for future rotation
    if(has_inverse_HW)
    {
        newheight = width;
        newwidth = height;
    }
    else
    {
        newheight = height;
        newwidth = width;        
    }

    //New pixbuf for an image
    newpixbuf = gdk_pixbuf_new (GDK_COLORSPACE_RGB, 0, 8, newwidth, newheight);
    int newRowstride = gdk_pixbuf_get_rowstride (newpixbuf);
    new_which_pixels = gdk_pixbuf_get_pixels (newpixbuf);

    for(int y = 0; y < newheight; ++y)
    {
        for(int x = 0; x < newwidth; ++x)
        {
            newp = new_which_pixels + y * newRowstride + x * n_channels;
            oldp = filter(x, y, which_pixels, rowstride, n_channels, width, height);
            // Change colors of RGB
            for(unsigned char i = 0; i < 3; ++i)
                newp[i] = oldp[i];
        }
    }
    gtk_image_set_from_pixbuf (GTK_IMAGE(image), newpixbuf);
}


/**
 ** \brief return the old position of the pixel with an rotation of 180 degrees
 **
 ** \param x actually position
 ** \param y actually postion
 ** \param which_pixels
 ** \param rowstride
 ** \param n_channels
 ** \param width of the old pixbuff
 ** \param height of the old pixbuff
 **
 ** \return old pixel
*/
guchar* rotate180(int x, int y, guchar *which_pixels,
                int rowstride, int n_channels, int width, int height)
{
    guchar *p;
    p = which_pixels + (height - y - 1) * rowstride + (width - x - 1) * n_channels;
    return p;
}

/**
 ** \brief return the old position of the pixel with an rotation of 90 degrees
 ** in trigonometry rotation
 **
 ** \param x actually position
 ** \param y actually postion
 ** \param which_pixels
 ** \param rowstride
 ** \param n_channels
 ** \param width of the old pixbuff
 ** \param height of the old pixbuff
 **
 ** \return old pixel
*/
guchar* rotate90(int x, int y, guchar *which_pixels,
                int rowstride, int n_channels, int width, int height)
{
    UNUSED(height);
    guchar *p;
    p = which_pixels + x * rowstride + (width - y - 1) * n_channels;
    return p;
}

/**
 ** \brief return the old position of the pixel with an rotation of -90 degrees
 ** in trigonometry rotation
 **
 ** \param x actually position
 ** \param y actually postion
 ** \param which_pixels
 ** \param rowstride
 ** \param n_channels
 ** \param width of the old pixbuff
 ** \param height of the old pixbuff
 **
 ** \return old pixel
*/
guchar* rotate270(int x, int y, guchar *which_pixels,
                int rowstride, int n_channels, int width, int height)
{
    UNUSED(width);
    guchar *p;
    p = which_pixels + (height - x - 1) * rowstride + y * n_channels;
    return p;
}


void rotate(GtkWidget* image, int degree)
{
    switch (degree)
    {
    case 90:
    case -270:
        apply_rotation(image, true, rotate90);
        break;
    
    case -90:
    case 270:
        apply_rotation(image, true, rotate270);
        break;

    case 180:
        apply_rotation(image, false, rotate180);
        break;
    default:
        printf("ERROR : rotate : You don't choose a good degree of rotation !\n");
        break;
    }
}