#ifndef UNREAD__SRC__LOAD_IMAGE__NOISE_H__
#define UNREAD__SRC__LOAD_IMAGE__NOISE_H__

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
void remove_noise_image(GtkWidget* image, int radius);

#endif