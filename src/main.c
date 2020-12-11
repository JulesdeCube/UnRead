#include <gtk/gtk.h>
#include <load_Image/change_color.h>
#include <stdio.h>
#define UNUSED(x) (void)(x)

typedef struct 
{
    GtkWidget *w_dlg_save_file;
    GtkWidget *w_dlg_file_choose;       // Pointer to file chooser dialog box
    GtkWidget *w_img_main;              // Pointer to image widget 
    char      *w_path;                  //path of the image open
    char      *w_save_path;             //path of the file where the text is save
    char      *w_text_to_save;          //string of the text to save
} app_widgets;

int main(int argc, char *argv[])
{
    GtkBuilder      *builder;
    GtkWidget       *window;
    app_widgets     *widgets = g_slice_new(app_widgets);
    
    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file("src/UI/main_window.glade");

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));

    widgets->w_dlg_save_file = GTK_WIDGET(gtk_builder_get_object(builder, "dlg_save_file"));
    widgets->w_dlg_file_choose = GTK_WIDGET(gtk_builder_get_object(builder, "dlg_file_choose"));
    widgets->w_img_main = GTK_WIDGET(gtk_builder_get_object(builder, "img_main"));
    widgets->w_path = malloc(sizeof(char));
    widgets->w_save_path = "test/save_file/save.txt";
    widgets->w_text_to_save = "oui";

    gtk_builder_connect_signals(builder, widgets);
    
    g_object_unref(builder);

    gtk_widget_show(window);                
    gtk_main();
    g_slice_free(app_widgets, widgets);
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
        if(app_wdgts->w_path != NULL)
            g_free(app_wdgts->w_path);
        app_wdgts->w_path = file_name;
    
        if (file_name != NULL) 
        {
            gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main), file_name);
        }
    }
    // Finished with the "Open Image" dialog box, so hide it
    gtk_widget_hide(app_wdgts->w_dlg_file_choose);
}

//file ->save in the w_save_path
void on_menuitm_save_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
    UNUSED(menuitem);
    //GtkWidget *image;
    
    // Show the "Open Image" dialog box
    gtk_widget_show(app_wdgts->w_dlg_save_file);

    FILE *fp = fopen(app_wdgts->w_save_path, "w");
    //write
    fputs(app_wdgts->w_text_to_save, fp);
    // add new line at the end of the file  
    fputc('\n', fp);
    // free the file
    fclose(fp);
    // Finished with the "Open Image" dialog box, so hide it
    gtk_widget_hide(app_wdgts->w_dlg_save_file);
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
        }
        g_free(file_name);
    }

    // Finished with the "Open Image" dialog box, so hide it
    gtk_widget_hide(app_wdgts->w_dlg_file_choose);
}

//Set the color of the image in grey lvl normalised
void on_button_clicked(GtkButton *button, app_widgets *app_wdgts)
{
    UNUSED(button);
    gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main), app_wdgts->w_path);
    Change_Color(app_wdgts->w_img_main,Colored_to_classicGreyLvl);
    Change_Color(app_wdgts->w_img_main,ClassicGLVL_to_NormalizedGLVL);
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
