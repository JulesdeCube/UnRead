#ifndef UNREAD__SRC__LOAD_IMAGE__TOOLS_H_
#define UNREAD__SRC__LOAD_IMAGE__TOOLS_H_

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>

#define UNUSED(x) (void)(x)

struct s_int_tuple{
    int first;
    int second;
};

struct s_int_tuple search_BW_pixel(GdkPixbuf *pixbuf);
float change_pixel_greylvl(guchar *p);

#endif