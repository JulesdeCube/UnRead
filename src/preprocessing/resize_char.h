#ifndef UNREAD__SRC_PREPROCESSING__RESIZE_CHAR_H_
#define UNREAD__SRC_PREPROCESSING__RESIZE_CHAR_H_

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

#endif // UNREAD__SRC_PREPROCESSING__RESIZE_CHAR_H_