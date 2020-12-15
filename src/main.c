#include <gtk/gtk.h>
#include <stdio.h>

#include "preprocessing/change_color.h"
#include "preprocessing/rotate.h"
#include "preprocessing/resize.h"
#include "preprocessing/histo_grey_lvl.h"
#include "preprocessing/noise.h"

#include "segmentation/segmentation.h"
#include "segmentation/auto_rotation.h"

#include "neural_network/neural_network.h"
#include "neural_network/utils.h"

#include "data_set/set.h"

#define nb_layers 4
#define nb_test 10000

#define UNUSED(x) (void)(x)

typedef struct
{
    GtkWidget *w_dlg_save_file;   // Pointer to file chooser dialog box
    GtkWidget *w_dlg_file_choose; // Pointer to file chooser dialog box
    GtkWidget *w_img_main;        // Pointer to image widget
    GtkWidget *w_window_label;    // Pointer to a window to display the text
    GtkWidget *w_window_help;     // Pointer to a window to display the text
    GtkWidget *w_label_text_help; // Pointer to an label to display the text to help
    GtkWidget *w_label_text;      // Pointer to an label to display the text
    char *w_path;                 // path of the image open
    char *w_save_path;            // path of the file where the text is save
    char *w_text_to_save;         // string of the text to save
    int w_step;                   //value of the current step


} app_widgets;

int main(int argc, char *argv[])
{
    GtkBuilder *builder;
    GtkWidget *window;
    app_widgets *widgets = g_slice_new(app_widgets);

    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file("src/UI/main_window.glade");

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));

    widgets->w_dlg_save_file = GTK_WIDGET(gtk_builder_get_object(builder, "dlg_save_file"));
    widgets->w_dlg_file_choose = GTK_WIDGET(gtk_builder_get_object(builder, "dlg_file_choose"));
    widgets->w_img_main = GTK_WIDGET(gtk_builder_get_object(builder, "img_main"));
    widgets->w_window_label = GTK_WIDGET(gtk_builder_get_object(builder, "window_label"));
    widgets->w_window_help = GTK_WIDGET(gtk_builder_get_object(builder, "window_help"));
    widgets->w_label_text = GTK_WIDGET(gtk_builder_get_object(builder, "text"));
    widgets->w_label_text_help = GTK_WIDGET(gtk_builder_get_object(builder, "text_help"));
    widgets->w_path = malloc(sizeof(char));
    widgets->w_path[0] = '\0';
    widgets->w_save_path = "test/save_file/save.txt";
    widgets->w_text_to_save = "oui";
    widgets->w_step = 0;


    gtk_builder_connect_signals(builder, widgets);

    g_object_unref(builder);

    gtk_widget_show(window);
    gtk_main();
    g_slice_free(app_widgets, widgets);

    return 0;
}

// Open the helper text
void on_menuitm_about_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
    UNUSED(menuitem);
    gtk_widget_show(app_wdgts->w_window_help);
}

// File --> Open
void on_menuitm_open_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
    UNUSED(menuitem);
    gchar *file_name = NULL; // Name of file to open from dialog box
    // Show the "Open Image" dialog box
    gtk_widget_show(app_wdgts->w_dlg_file_choose);

    // Check return value from Open Image dialog box to see if user clicked the Open button
    if (gtk_dialog_run(GTK_DIALOG(app_wdgts->w_dlg_file_choose)) == GTK_RESPONSE_OK)
    {
        // Get the file name from the dialog box
        file_name = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(app_wdgts->w_dlg_file_choose));
        if (app_wdgts->w_path != NULL)
            g_free(app_wdgts->w_path);
        app_wdgts->w_path = file_name;

        if (file_name != NULL)
        {
            gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main), file_name);
            GdkPixbuf *newpixbuf = New_Size_Image(app_wdgts->w_img_main, 500, 500);
            gtk_image_set_from_pixbuf(GTK_IMAGE(app_wdgts->w_img_main), newpixbuf);
        }
    }
    app_wdgts->w_step = 0;
    // Finished with the "Open Image" dialog box, so hide it
    gtk_widget_hide(app_wdgts->w_dlg_file_choose);
}

//save the text in the chosen file
void on_menuitm_save_as_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
    UNUSED(menuitem);
    gchar *file_name = NULL; // Name of file to open from dialog box
    // Show the "Open Image" dialog box
    gtk_widget_show(app_wdgts->w_dlg_save_file);

    // Check return value from Open Image dialog box to see if user clicked the Open button
    if (gtk_dialog_run(GTK_DIALOG(app_wdgts->w_dlg_save_file)) == GTK_RESPONSE_OK)
    {
        // Get the file name from the dialog box
        file_name = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(app_wdgts->w_dlg_save_file));
        if (file_name != NULL)
        {
            FILE *fp = fopen(file_name, "a");
            //write
            fputs(app_wdgts->w_text_to_save, fp);
            // add new line at the end of the file
            fputc('\n', fp);
            // free the file
            fclose(fp);
        }
    }
    g_free(file_name);
    // Finished with the "Open Image" dialog box, so hide it
    gtk_widget_hide(app_wdgts->w_dlg_save_file);
}

//file ->save in the w_save_path
void on_menuitm_save_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
    UNUSED(menuitem);
    FILE *fp = fopen(app_wdgts->w_save_path, "a");
    //write
    fputs(app_wdgts->w_text_to_save, fp);
    // add new line at the end of the file
    fputc('\n', fp);
    // free the file
    fclose(fp);
}

//step zero of the process od the ocr
void step_zero(app_widgets *app_wdgts)
{
    //UNUSED(button);
    //image->only black
    gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main), app_wdgts->w_path);
    Change_Color(app_wdgts->w_img_main, Colored_to_classicGreyLvl);
    histo_greylvl(app_wdgts->w_img_main, 5, 40);
    remove_noise_image(app_wdgts->w_img_main, 1);
    remove_noise_image(app_wdgts->w_img_main, 2);
    Change_Color(app_wdgts->w_img_main, Colored_to_OnlyBlack);
    GdkPixbuf *newpixbuf = New_Size_Image(app_wdgts->w_img_main, 500, 500);
    gtk_image_set_from_pixbuf(GTK_IMAGE(app_wdgts->w_img_main), newpixbuf);
}

//step one of the process od the ocr
void step_one(app_widgets *app_wdgts)
{
    //image-> only black
    gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main), app_wdgts->w_path);
    Change_Color(app_wdgts->w_img_main, Colored_to_classicGreyLvl);
    histo_greylvl(app_wdgts->w_img_main, 5, 40);
    remove_noise_image(app_wdgts->w_img_main, 1);
    remove_noise_image(app_wdgts->w_img_main, 2);
    Change_Color(app_wdgts->w_img_main, Colored_to_OnlyBlack);
    //rotation
    auto_rotation(app_wdgts->w_img_main);
    //segmentation
    mainSegmentation(app_wdgts->w_img_main);
    //affichage
    GdkPixbuf *newpixbuf = New_Size_Image(app_wdgts->w_img_main, 500, 500);
    gtk_image_set_from_pixbuf(GTK_IMAGE(app_wdgts->w_img_main), newpixbuf);
}

//step two of the process od the ocr
void step_two(app_widgets *app_wdgts)
{
    //image-> only black
    gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main), app_wdgts->w_path);
    Change_Color(app_wdgts->w_img_main, Colored_to_classicGreyLvl);
    histo_greylvl(app_wdgts->w_img_main, 5, 40);
    remove_noise_image(app_wdgts->w_img_main, 1);
    remove_noise_image(app_wdgts->w_img_main, 2);
    Change_Color(app_wdgts->w_img_main, Colored_to_OnlyBlack);
    //rotation
    auto_rotation(app_wdgts->w_img_main);
    //segmentation
    mainSegmentation(app_wdgts->w_img_main);
    //affichage
    GdkPixbuf *newpixbuf = New_Size_Image(app_wdgts->w_img_main, 500, 500);
    gtk_image_set_from_pixbuf(GTK_IMAGE(app_wdgts->w_img_main), newpixbuf);

    //passage réseau de neuronne

    //montrer le texte
    const gchar *text = "un zolie texte";
    // Show the "Open Image" dialog box
    gtk_widget_show(app_wdgts->w_window_label);
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(app_wdgts->w_label_text));
    gtk_text_buffer_set_text(buffer, text, strlen(text));

    //sauvegarde du texte dans le w_text_to_save
}

//Set the color of the image in grey lvl normalised
//do something depending of the current step
void on_button_clicked(GtkButton *button, app_widgets *app_wdgts)
{
    UNUSED(button);
    if(app_wdgts->w_path[0] == '\0')
        return;
    else
    {
        switch (app_wdgts->w_step)
        {
        case 0:
            step_zero(app_wdgts);
            break;
        case 1:
            step_one(app_wdgts);
            break;
        case 2:
            step_two(app_wdgts);
            break;
        default:
            return;
        }
        app_wdgts->w_step++;
        app_wdgts->w_step %= 3;
    }
}

//DO all process
void on_button_apply_clicked(GtkButton *button, app_widgets *app_wdgts)
{
    UNUSED(button);
    if(app_wdgts->w_path[0] == '\0')
        return;
    step_two(app_wdgts);
}

//Train the neurones
void on_button_train_clicked(GtkButton *button, app_widgets *app_wdgts)
{
    UNUSED(button);
    UNUSED(app_wdgts);
    //g_print("ca marche");
}

//Close the pop up window label
void on_button_close_clicked(GtkButton *button, app_widgets *app_wdgts)
{
    UNUSED(button);
    gtk_widget_hide(app_wdgts->w_window_label);
}

//Close the pop up window help
void on_button_close_help_clicked(GtkButton *button, app_widgets *app_wdgts)
{
    UNUSED(button);
    gtk_widget_hide(app_wdgts->w_window_help);
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
