#include "auto_rotation.h"


int get_variance(GtkWidget* image,double degree){
    printf("var\n");
    rotate(image,degree);
    GdkPixbuf *pixbuf;
    pixbuf = gtk_image_get_pixbuf ((GtkImage*) image);
    int * hp = horizontalProjection(pixbuf);
    int height = gdk_pixbuf_get_height (pixbuf);
    int average;
    printf("var\n");
    for (int i = 0; i < height; ++i) {
        average += hp[i];
    }
    average = average / height;
    int var;
    printf("var\n");
    for (int i = 0; i < height; ++i) {
        var += (hp[i] - average) * (hp[i] - average);
    }
    var = var / height;
    printf("var\n");
    return var;


}

void auto_rotation(GtkWidget* image) {
    printf("test\n");
    GtkWidget *temp_image;
    int degree_max;
    int var_max = 0;
    printf("test\n");
    for (int i = -30; i <= 30; i = i + 2) {
        printf("test\n");
        temp_image = image;
        int var = get_variance(temp_image, i);
        if (var > var_max) {
            var_max = var;
            degree_max = i;
        }
    }
    printf("test\n");
    rotate(image, degree_max);
}