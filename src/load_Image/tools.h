#ifndef UNREAD__SRC__LOAD_IMAGE__TOOLS_H_
#define UNREAD__SRC__LOAD_IMAGE__TOOLS_H_

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>

#define UNUSED(x) (void)(x)

struct s_int_tuple{
    int min;
    int max;
};

struct s_int_tuple search_BW_pixel(GtkWidget* image);

#endif