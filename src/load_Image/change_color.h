#ifndef UNREAD__SRC__LOAD_IMAGE__CHANGE_COLOR_H__
#define UNREAD__SRC__LOAD_IMAGE__CHANGE_COLOR_H__

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>

#include "tools.h"

#define UNUSED(x) (void)(x)

enum function
{
    Colored_to_classicGreyLvl,
    ClassicGLVL_to_NormalizedGLVL,
    Greylvl_to_BW,
    Colored_to_BW,
    Colored_to_OnlyBlack
};

void apply_color(GtkWidget* image, void filter(guchar *, struct s_int_tuple));
void Change_Color(GtkWidget* image, enum function f);

#endif