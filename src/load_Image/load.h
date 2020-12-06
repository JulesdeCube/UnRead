#ifndef UNREAD__SRC__LOAD_IMAGE__LOAD_H__
#define UNREAD__SRC__LOAD_IMAGE__LOAD_H__

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>

#include "change_color.h"
#include "segmentation.h"
#include "resize.h"

#define UNUSED(x) (void)(x)

/**
 ** \brief Create an Image from a file
 **
 ** \return Return an GtkWidget *image
 */
GtkWidget* create_image();

/**
 ** \brief We start our first window
 ** and display it
 ** 
 ** \param app the application
 ** \param user_data Unused parameter
 */
void activate_window(GtkApplication *app, gpointer user_data);

/**
 ** \brief Generate our window with GTK
 **
 ** 
 ** \return if the window is create successfuly
 */
int create_window(int argc, char **argv);

#endif
