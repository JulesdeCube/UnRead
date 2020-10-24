#ifndef UNREAD_SEGMENTATION_H
#define UNREAD_SEGMENTATION_H


#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <string.h>
#include <dirent.h>

//create an array of the horizontal projection of a pixbuf image. Each array[i] link to the sum of black pixel of the 'i' line.
int * horizontalProjection(GdkPixbuf *pixbuf);

//create an array of the vertical projection of a pixbuf image. Each array[i] link to the sum of black pixel of the 'i' collum.
int * verticalProjection(GdkPixbuf *pixbuf);

//take a pixbuf image and create crop each line in a specific directory
void lineSegmentation(GdkPixbuf *pixbuf);

//take a pixbuf image and create crop each character in a specific directory
void charSegmentation(GdkPixbuf *pixbuf,int lineNumber);

//sub function used to create a gtk widget from a file
GtkWidget* create_image2 (char path[255]);

//main segmentation, use line Segmentation on the pixbuf image. Then use charSegmentation on each line.
void mainSegmentation(GtkWidget* image_to_change);



#endif //UNREAD_SEGMENTATION_H
