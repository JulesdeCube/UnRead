#ifndef UNREAD__SRC__LOAD_IMAGE__TRANSFORM_BW_H_
#define UNREAD__SRC__LOAD_IMAGE__TRANSFORM_BW_H_

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>

#include "tools.h"

#define UNUSED(x) (void)(x)

GtkWidget* image_to_BW_binary (GtkWidget* image_to_change);

#endif