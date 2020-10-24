#ifndef UNREAD_SEGMENTATION_H
#define UNREAD_SEGMENTATION_H


#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <string.h>
#include <dirent.h>

struct s_int_array
{
    int *values;
    size_t size;
};
int * horizontalProjection(GdkPixbuf *pixbuf);
int * verticalProjection(GdkPixbuf *pixbuf);
void lineSegmentation(GdkPixbuf *pixbuf);
void charSegmentation(GdkPixbuf *pixbuf,int lineNumber);
GtkWidget* create_image2 (char path[255]);
void mainSegmentation(GtkWidget* image_to_change);



#endif //UNREAD_SEGMENTATION_H
