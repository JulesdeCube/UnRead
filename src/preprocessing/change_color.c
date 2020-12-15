#include "change_color.h"

void apply_color(GtkWidget *image, void filter(guchar *, struct s_int_tuple))
{
    GdkPixbuf *pixbuf;
    guchar *which_pixels, *p;
    int n_channels, rowstride, height, width;

    pixbuf = gtk_image_get_pixbuf((GtkImage *)image);
    n_channels = gdk_pixbuf_get_n_channels(pixbuf);
    rowstride = gdk_pixbuf_get_rowstride(pixbuf);
    height = gdk_pixbuf_get_height(pixbuf);
    width = gdk_pixbuf_get_width(pixbuf);

    which_pixels = gdk_pixbuf_get_pixels(pixbuf);

    struct s_int_tuple min_max = search_BW_pixel(image);

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            p = which_pixels + y * rowstride + x * n_channels;
            filter(p, min_max);
        }
    }
}

/**
 ** \brief  Change pixel code in RGB to a pixel code in CLASSIC grey level
 **
 ** \param pixel which apply new color
 ** \param min_max Unused it
*/
void Colored_to_classicGreyLvl1(guchar *pixel, struct s_int_tuple min_max)
{
    UNUSED(min_max);
    char value = 0.3 * pixel[0] + 0.59 * pixel[1] + 0.11 * pixel[2];
    set_3values(pixel, value, value, value);
}

/**
 ** \brief  Change pixel code in CLASSIC grey level to a pixel code in NORMALIZED grey level
 **
 ** \param pixel which apply new color
 ** \param min_max tuple with the maximum and minimum color of the image
*/
void ClassicGLVL_to_NormalizedGLVL1(guchar *pixel, struct s_int_tuple min_max)
{
    normalized_pixel(pixel, min_max);
}

/**
 ** \brief  Change pixel code in grey level to a pixel code in black and white binary
 **
 ** \param pixel which apply new color
 ** \param min_max Unused it
*/
void Greylvl_to_BW1(guchar *pixel, struct s_int_tuple min_max)
{
    UNUSED(min_max);
    char value = 255 * (pixel[0] >= 128);
    set_3values(pixel, value, value, value);
}

/**
 ** \brief Change pixel code in RGB to a pixel code in black and white binary
 **
 ** \param pixel which apply new color
 ** \param min_max tuple with the maximum and minimum color of the image
*/
void Colored_to_BW1(guchar *pixel, struct s_int_tuple min_max)
{
    int medium = (min_max.max - min_max.min) / 2;
    int greycolor = (pixel[0] + pixel[1] + pixel[2]) / 3;
    char value = 255 * (greycolor > min_max.min + medium);
    set_3values(pixel, value, value, value);
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
    if ((pixel[0] + pixel[1] + pixel[2]) / 3 - min_max.min < 20)
        value = 0;
    else
        value = 255;
    set_3values(pixel, value, value, value);
}

/**
 ** \brief inverse the color of the pixel
 **
 ** \param pixel will be modify
 ** \param min_max useless
*/
void inverse_color1(guchar *pixel, struct s_int_tuple min_max)
{
    UNUSED(min_max);
    set_3values(pixel, 255 - pixel[0], 255 - pixel[1], 255 - pixel[2]);
}

void Change_Color(GtkWidget *image, enum function f)
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

    case Inverse_color:
        apply_color(image, inverse_color1);
        break;

    default:
        printf("ERROR : Change_color : You don't choose a changing color !\n");
        break;
    }
}