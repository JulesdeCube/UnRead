#ifndef UNREAD_AUTO_ROTATION_H
#define UNREAD_AUTO_ROTATION_H

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <string.h>
#include <dirent.h>

#include "segmentation.h"

#include "../load_Image/rotate.h"

//find variance of horizontal projection of an image after rotation
int get_variance(GtkWidget *image, double degree);

//auto_rotation take an image and find the rotation from -30° to 30° with the best variance. image is change by the function.
void auto_rotation(GtkWidget *image);

#endif //UNREAD_AUTO_ROTATION_H
