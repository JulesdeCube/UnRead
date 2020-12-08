#ifndef UNREAD__SRC__LOAD_IMAGE__ROTATE_H__
#define UNREAD__SRC__LOAD_IMAGE__ROTATE_H__

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>

#include "tools.h"
#include "../src/utils/bool.h"

/**
 ** \brief Run on each pixel from image and apply the function in parameters
 ** 
 ** \param image which image to apply rotation*
 ** \param degree of rotation in trigonometry rotation
 ** \param has_inverse_HW true if the image need to inverse height and width
 ** \param filter function to apply on each pixel
*/
void apply_rotation(GtkWidget* image, bool has_inverse_HW,
                    guchar* filter(int, int, guchar *, int, int , int , int));


/**
 ** \brief Switch from param degree and call the corresponding function 
 **
 ** \param image which image to change color
 ** \param degree how many degrees to rotate the image
 */
void rotate(GtkWidget* image, int degree);

#endif