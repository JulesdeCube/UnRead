#ifndef UNREAD__SRC__LOAD_IMAGE__RESIZE_CHAR_H__
#define UNREAD__SRC__LOAD_IMAGE__RESIZE_CHAR_H__

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>

#include "tools.h"
#include "resize.h"


/**
 ** \brief resize image without deformation and 
 ** return the array of pixel from this new image
 **  the size of image if define by SIZE_OF_IMAGE_CHAR
 ** 
 ** \param image which image to get the new array
 **
 ** \return array of pixels (malloc)
*/
double *image_to_array(GtkWidget *image);

#endif