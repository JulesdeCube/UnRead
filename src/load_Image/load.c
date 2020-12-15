#include "load.h"

GtkWidget *create_image()
{
    return gtk_image_new_from_file ("./test/traitement/c.bmp");
}

void activate_window (GtkApplication *app, gpointer user_data)
{
    UNUSED(user_data);

    //Create our first window with size. 
    GtkWidget *window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Window");
    gtk_window_set_default_size (GTK_WINDOW (window), 1000, 500);
    
    //Create an Image
    GtkWidget *imagec = create_image();
    gtk_container_add (GTK_CONTAINER (window), imagec);
    

    /*
      ################################################
          HERE TO CHANGE THE TRANSFORMATION
      ################################################
    */
    //Change_Color(imagec, Inverse_color);
    //Change_Color(imagec, Colored_to_classicGreyLvl);
    //Change_Color(imagec, ClassicGLVL_to_NormalizedGLVL);
    //histo_greylvl(imagec, 5, 40);
    //Change_Color(imagec, Colored_to_BW);
    //Change_Color(imagec, Colored_to_OnlyBlack);
    //remove_noise_image(imagec, 1);
    //remove_noise_image(imagec, 2);
    
    
    double *array = get_great_char(imagec);
    free(array);
    //rotate(imagec, 217);

    //Segmentation for hugo
    //mainSegmentation(imagec);

    //To show our Image
    gtk_widget_show_all (window);
}


int create_window(int argc, char **argv)
{
    GtkApplication *app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate_window), NULL);
    int status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    return status;
} 
