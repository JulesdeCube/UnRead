#include "change_color.h"

/*
    for each pixel of the image, change the color with the function called in parameters
    No return, because it will be apply on the image
*/
void apply_color(GtkWidget* image, void filter(guchar *, struct s_int_tuple))
{
    GdkPixbuf *pixbuf;
    guchar *which_pixels, *p;
    int n_channels, rowstride, height, width;

    pixbuf = gtk_image_get_pixbuf ((GtkImage*) image);
    n_channels = gdk_pixbuf_get_n_channels (pixbuf);
    rowstride = gdk_pixbuf_get_rowstride (pixbuf);
    height = gdk_pixbuf_get_height (pixbuf);
    width = gdk_pixbuf_get_width (pixbuf);

    which_pixels = gdk_pixbuf_get_pixels (pixbuf);
    
    struct s_int_tuple min_max = search_BW_pixel(image);

    for(int y = 0; y < height; ++y)
    {
        for(int x = 0; x < width; ++x)
        {
            p = which_pixels + y * rowstride + x * n_channels;
            filter(p, min_max);
        }
    }
}



/*
    Return a value of grey corresponding to the pixel in parameters
*/
void Colored_to_classicGreyLvl1( guchar *pixel, struct s_int_tuple min_max)
{
    UNUSED(min_max);
    char value = 0.3 * pixel[0] + 0.59 * pixel[1] + 0.11 * pixel[2];
    for(unsigned char i = 0; i < 3; ++i)
        pixel[i] = value;
}

/*
    Change the i
*/
void ClassicGLVL_to_NormalizedGLVL1( guchar *pixel, struct s_int_tuple min_max)
{
    char value = (pixel[0] - min_max.min) * (255./ (min_max.max - min_max.min));
    for(unsigned char i = 0; i < 3; ++i)
        pixel[i] = value;
}

/*
    Change image coded in grey level to an image code into black and white binary
    - pixel can be coded in Classic or Normalized grey level
*/
void Greylvl_to_BW1(guchar *pixel, struct s_int_tuple min_max)
{       
    UNUSED(min_max);
    char value = 255 * (pixel[0] >= 128);
    for(unsigned char i = 0; i < 3; ++i)
        pixel[i] = value;
}


void Colored_to_BW1(guchar *pixel, struct s_int_tuple min_max)
{
    int medium = (min_max.max - min_max.min) /2;
    int greycolor = (pixel[0] + pixel[1] + pixel[2]) / 3; 
    char value = 255 * (greycolor > min_max.min + medium);
    for(unsigned char i = 0; i < 3; ++i)
        pixel[i] = value;
}

/**
 ** \brief transform pixel if his color value is under 15+minimal
 ** of the image into a black one. Else into a white one
 **
 ** \param pixel will be modify
 ** \param min_max the withest(maximal value) and blackest (minimal value) of the image
*/
void Colored_to_OnlyBlack1(guchar *pixel, struct s_int_tuple min_max)
{
    int value;
    if((pixel[0] + pixel[1] + pixel[2]) / 3 - min_max.min < 15)
        value = 0;
    else
        value = 255;
    for(unsigned char i = 0; i < 3; ++i)
        pixel[i] = value;
}

void Change_Color(GtkWidget* image, enum function f)
{
    switch (f)
    {
    case Colored_to_classicGreyLvl:
        apply_color(image, Colored_to_classicGreyLvl1);
        break;
    
    case ClassicGLVL_to_NormalizedGLVL:
        apply_color(image, ClassicGLVL_to_NormalizedGLVL1);
        break;

    case Greylvl_to_BW:
        apply_color(image, Greylvl_to_BW1);
        break;
    
    case Colored_to_BW:
        apply_color(image, Colored_to_BW1);
        break;
        
    case Colored_to_OnlyBlack:
        apply_color(image, Colored_to_OnlyBlack1);
        break;

    default:
        printf("ERROR : Change_color : You don't choose a changing color !\n");
        break;
    }
}