#ifndef UNREAD__SRC_PREPROCESSING__RESIZE_H_
#define UNREAD__SRC_PREPROCESSING__RESIZE_H_

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>

#define UNUSED(x) (void)(x)

/**
** \brief return the new pixels buffer of the image for new height and new width
**        you can apply the new pixbuf on an image or save it on a new file.
**        The function use the linear strtching
**
** \param image which image to get the new pixels buffer with new size
** \param newHeight new height to for the new pixels buffer
** \param newWidth new wdth to for the new pixels buffer
**
** \return new pixels buffer with new height and new size.
*/
GdkPixbuf *New_Size_Image(GtkWidget *image, int newHeight, int newWidth);

#endif // UNREAD__SRC_PREPROCESSING__RESIZE_H_