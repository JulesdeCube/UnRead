#include "load.h"

GtkWidget* create_image ()
{
  GtkWidget *image;
  image = gtk_image_new_from_file ("./src/load_Image/Images/oiseau.bmp");
  return image;
}

void activate_window (GtkApplication *app, gpointer user_data)
{
    UNUSED(user_data);
    GtkWidget *window;
    GtkWidget *imagec;

    //Create our first window with size. 
    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Window");
    gtk_window_set_default_size (GTK_WINDOW (window), 1000, 500);
    

    //Create an Image
    imagec = create_image();
    gtk_container_add (GTK_CONTAINER (window), imagec);
    

    /*
      ################################################
          HERE TO CHANGE THE TRANSFORMATION
      ################################################
    */
    rotate(imagec, -20);


    //To show our Image
    gtk_widget_show_all (window);
}


int create_window(int argc, char **argv)
{
    GtkApplication *app;
    int status;

    app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate_window), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);


    return status;
} 
