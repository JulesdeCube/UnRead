#ifndef UNREAD__SRC_SEGMENTATION__AUTO_ROTATION_H_
#define UNREAD__SRC_SEGMENTATION__AUTO_ROTATION_H_

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <string.h>
#include <dirent.h>

#include "segmentation.h"

#include "../preprocessing/rotate.h"

//find variance of horizontal projection of an image after rotation
int get_variance(GtkWidget *image, double degree);

//auto_rotation take an image and find the rotation from -30° to 30° with the best variance. image is change by the function.
void auto_rotation(GtkWidget *image);

#endif //UNREAD__SRC_SEGMENTATION__AUTO_ROTATION_H_
