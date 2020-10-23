#ifndef UNREAD__SRC__LOAD_IMAGE__LOAD_H__
#define UNREAD__SRC__LOAD_IMAGE__LOAD_H__

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>

#include "change_color.h"

#define UNUSED(x) (void)(x)

GtkWidget* create_image();
void activate_window(GtkApplication *app, gpointer user_data);
int create_window(int argc, char **argv);

#endif