#include "auto_rotation.h"

//find variance of horizontal projection of an image after rotation
int get_variance(GtkWidget *image, double degree)
{
    rotate(image, degree);
    GdkPixbuf *pixbuf;
    pixbuf = gtk_image_get_pixbuf((GtkImage *)image);
    //getting horizontal projection from segmentation.
    int *hp = horizontalProjection(pixbuf);
    int height = gdk_pixbuf_get_height(pixbuf);
    int average;
    for (int i = 0; i < height; ++i)
    {
        average += hp[i];
    }
    average = average / height;
    int var;
    for (int i = 0; i < height; ++i)
    {
        var += (hp[i] - average) * (hp[i] - average);
    }
    var = var / height;
    free(hp);
    return var;
}

//auto_rotation take an image and find the rotation from -30° to 30° with the best variance.
void auto_rotation(GtkWidget *image)
{
    GtkWidget *temp_image;
    GdkPixbuf *pixbuf;
    int degree_max;
    int var_max = 0;

    for (int i = -30; i <= 30; i = i + 2)
    {
        //getting a temporary image for test
        pixbuf = gtk_image_get_pixbuf((GtkImage *)image);
        GdkPixbuf *newpixbuf = gdk_pixbuf_new_subpixbuf(pixbuf, 0, 0,
                                                        gdk_pixbuf_get_width(pixbuf),
                                                        gdk_pixbuf_get_height(pixbuf));
        temp_image = gtk_image_new_from_pixbuf(newpixbuf);

        int var = get_variance(temp_image, i);
        if (var > var_max)
        {
            var_max = var;
            degree_max = i;
        }
    }

    rotate(image, degree_max);
}