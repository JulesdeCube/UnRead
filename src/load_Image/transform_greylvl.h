#ifndef UNREAD__SRC__LOAD_IMAGE__TRANSFORM_GREYLVL_H_
#define UNREAD__SRC__LOAD_IMAGE__TRANSFORM_GREYLVL_H_

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>

#define UNUSED(x) (void)(x)

float change_pixel_greylvl(guchar *p);
GtkWidget* image_to_greylvl (GtkWidget* image_to_change);

#endif