#ifndef UNREAD__SRC__LOAD_IMAGE__TOOLS_H_
#define UNREAD__SRC__LOAD_IMAGE__TOOLS_H_

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>

#define UNUSED(x) (void)(x)

/**
 * \brief tuple of int with min and max
 */
struct s_int_tuple{
    int min;
    int max;
};

/**
 ** \brief Search the withest (maximum) and the blackest (minimum) pixel of a pixbuf 
 ** corresponding to an image
 ** 
 ** \param image search on this image
 **
 ** \return tuple with minimum and maximum values
*/
struct s_int_tuple search_BW_pixel(GtkWidget* image);

#endif