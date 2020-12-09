#ifndef UNREAD__SRC__LOAD_IMAGE__ROTATE_H__
#define UNREAD__SRC__LOAD_IMAGE__ROTATE_H__

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>

#include "tools.h"

/**
 ** \brief call the change for height and width for each 
 **       type of rotation
 ** 
 ** \param INVERSE_HW inverse values of height and width
 ** \param MORE_SPACE apply pythagore to have maximum 
 **      space for rotation
 ** \param NONE Nothing happened, just copy height and width
 */
enum rotate_type
{
    INVERSE_HW,
    MORE_SPACE,
    NONE
};

/**
 ** \brief all parameters to apply on rotation
 **
 ** \param x position of the new pixbuf
 ** \param y position of the new pixbuf
 ** \param which_pixels in the old pixbuf
 ** \param rowstride in the old pixbuf
 ** \param n_channels in the old pixbuf
 ** \param width of the old pixbuff
 ** \param height of the old pixbuff
 ** \param degree in radient to wich degree it will be rotate
 ** \param newHeight height of the new pixbuf
 ** \param newWidth width of the new pixbuf
 */
struct rotate_tools
{
    int x;
    int y;
    guchar *which_pixels;
    int rowstride;
    int n_channels;
    int width;
    int height;
    double degree;
    int newHeight;
    int newWidth;
};

/**
 ** \brief Run on each pixel from image and apply the function in parameters
 ** 
 ** \param image which image to apply rotation*
 ** \param degree of rotation in trigonometry rotation
 ** \param r_type for witch values of height and width it will be apply in
 **               function of type of rotation
 ** \param fun function to apply on each pixel
 */
void apply_rotation(GtkWidget* image, enum rotate_type r_type, double degree,
                guchar* filter(struct rotate_tools));


/**
 ** \brief Rotate the image with degrees
 **
 ** \param image which image to change color
 ** \param degree how many degrees to rotate the image
 */
void rotate(GtkWidget* image, double degree);

#endif