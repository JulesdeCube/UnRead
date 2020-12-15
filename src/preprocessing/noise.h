#ifndef UNREAD__SRC_PREPROCESSING__NOISE_H_
#define UNREAD__SRC_PREPROCESSING__NOISE_H_

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>

#include "tools.h"

/**
 ** \brief remove the noise of an image (with precision of radius)
 **
 ** \param image which image will be remove the noise
 ** \param radius specify the radius to look around each pixel
*/
void remove_noise_image(GtkWidget *image, int radius);

#endif // UNREAD__SRC_PREPROCESSING__NOISE_H_