#include <gtk/gtk.h>
#include "load_Image/change_color.h"
#include "load_Image/segmentation.h"
#include "load_Image/rotate.h"

#include <stdio.h>

#include "load_Image/load.h"

#define UNUSED(x) (void)(x)


typedef struct {
    GtkWidget *w_dlg_file_choose;       // Pointer to file chooser dialog box
    GtkWidget *w_img_main;              // Pointer to image widget
} app_widgets;

int main(int argc, char *argv[])
{
    create_window(argc, argv);

    //With baptiste code
    /*
    GtkBuilder      *builder;
    GtkWidget       *window;
    app_widgets     *widgets = g_slice_new(app_widgets);

    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file("src/UI/main_window.glade");

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    widgets->w_dlg_file_choose = GTK_WIDGET(gtk_builder_get_object(builder, "dlg_file_choose"));
    widgets->w_img_main = GTK_WIDGET(gtk_builder_get_object(builder, "img_main"));
    
    gtk_builder_connect_signals(builder, widgets);

    g_object_unref(builder);

    gtk_widget_show(window);                
    gtk_main();
    g_slice_free(app_widgets, widgets);
    */
    return 0;
}

// File --> Open
void on_menuitm_open_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
    UNUSED(menuitem);
    gchar *file_name = NULL;        // Name of file to open from dialog box
    
    // Show the "Open Image" dialog box
    gtk_widget_show(app_wdgts->w_dlg_file_choose);
    
    // Check return value from Open Image dialog box to see if user clicked the Open button
    if (gtk_dialog_run(GTK_DIALOG (app_wdgts->w_dlg_file_choose)) == GTK_RESPONSE_OK) 
    {
        // Get the file name from the dialog box
        file_name = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(app_wdgts->w_dlg_file_choose));
        if (file_name != NULL) 
        {
            gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main), file_name);
        }
        g_free(file_name);
    }

    // Finished with the "Open Image" dialog box, so hide it
    gtk_widget_hide(app_wdgts->w_dlg_file_choose);
}
//File ->Open grey lvl
void on_menuitm_open_grey_lvl_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
    UNUSED(menuitem);
    gchar *file_name = NULL;        // Name of file to open from dialog box
    
    // Show the "Open Image" dialog box
    gtk_widget_show(app_wdgts->w_dlg_file_choose);
    
    // Check return value from Open Image dialog box to see if user clicked the Open button
    if (gtk_dialog_run(GTK_DIALOG (app_wdgts->w_dlg_file_choose)) == GTK_RESPONSE_OK) {
        // Get the file name from the dialog box
        file_name = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(app_wdgts->w_dlg_file_choose));
        if (file_name != NULL) 
        {
            gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main), file_name);
            Change_Color(app_wdgts->w_img_main,Colored_to_classicGreyLvl);
        }
        g_free(file_name);
    }

    // Finished with the "Open Image" dialog box, so hide it
    gtk_widget_hide(app_wdgts->w_dlg_file_choose);
}

//File -> open black and white
void on_menuitm_open_bw_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
    UNUSED(menuitem);
    gchar *file_name = NULL;        // Name of file to open from dialog box
    
    // Show the "Open Image" dialog box
    gtk_widget_show(app_wdgts->w_dlg_file_choose);
    
    // Check return value from Open Image dialog box to see if user clicked the Open button
    if (gtk_dialog_run(GTK_DIALOG (app_wdgts->w_dlg_file_choose)) == GTK_RESPONSE_OK) {
        // Get the file name from the dialog box
        file_name = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(app_wdgts->w_dlg_file_choose));
        if (file_name != NULL) 
        {
            gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main), file_name);
            Change_Color(app_wdgts->w_img_main,Colored_to_BW);
        }
        g_free(file_name);
    }

    // Finished with the "Open Image" dialog box, so hide it
    gtk_widget_hide(app_wdgts->w_dlg_file_choose);
}

//File -> Open grey lvl normalised
void on_menuitm_open_grey_lvl_n_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
    UNUSED(menuitem);
    gchar *file_name = NULL;        // Name of file to open from dialog box
    
    // Show the "Open Image" dialog box
    gtk_widget_show(app_wdgts->w_dlg_file_choose);
    
    // Check return value from Open Image dialog box to see if user clicked the Open button
    if (gtk_dialog_run(GTK_DIALOG (app_wdgts->w_dlg_file_choose)) == GTK_RESPONSE_OK) {
        // Get the file name from the dialog box
        file_name = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(app_wdgts->w_dlg_file_choose));
        if (file_name != NULL) 
        {
            gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main), file_name);
            Change_Color(app_wdgts->w_img_main,Colored_to_classicGreyLvl);
            Change_Color(app_wdgts->w_img_main,ClassicGLVL_to_NormalizedGLVL);
        }
        g_free(file_name);
    }

    // Finished with the "Open Image" dialog box, so hide it
    gtk_widget_hide(app_wdgts->w_dlg_file_choose);
}
// File --> Open only Text
void on_menuitm_open_preprocess_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
    UNUSED(menuitem);
    gchar *file_name = NULL;        // Name of file to open from dialog box
    
    // Show the "Open Image" dialog box
    gtk_widget_show(app_wdgts->w_dlg_file_choose);
    
    // Check return value from Open Image dialog box to see if user clicked the Open button
    if (gtk_dialog_run(GTK_DIALOG (app_wdgts->w_dlg_file_choose)) == GTK_RESPONSE_OK) 
    {
        // Get the file name from the dialog box
        file_name = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(app_wdgts->w_dlg_file_choose));
        if (file_name != NULL) 
        {
            gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main), file_name);
            Change_Color(app_wdgts->w_img_main,Colored_to_OnlyBlack);
            mainSegmentation(app_wdgts->w_img_main);
        }
        g_free(file_name);
    }

    // Finished with the "Open Image" dialog box, so hide it
    gtk_widget_hide(app_wdgts->w_dlg_file_choose);
}

// File --> Quit
void on_menuitm_close_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
    UNUSED(menuitem);
    UNUSED(app_wdgts);
    gtk_main_quit();
}

// called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();
}
