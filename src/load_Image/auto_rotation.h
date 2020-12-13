#ifndef UNREAD_AUTO_ROTATION_H
#define UNREAD_AUTO_ROTATION_H


#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <string.h>
#include <dirent.h>
#include "segmentation.h"
#include "rotate.h"

int get_variance(GtkWidget* image,double degree);
void auto_rotation(GtkWidget* image);


#endif //UNREAD_AUTO_ROTATION_H
