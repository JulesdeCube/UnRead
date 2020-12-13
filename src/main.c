#include <gtk/gtk.h>
#include "load_Image/change_color.h"
#include "load_Image/segmentation.h"
#include "load_Image/rotate.h"
#include "load_Image/resize.h"

#include <stdio.h>

#include "load_Image/load.h"

#define UNUSED(x) (void)(x)

typedef struct
{
    GtkWidget *w_dlg_save_file;         // Pointer to file chooser dialog box
    GtkWidget *w_dlg_file_choose;       // Pointer to file chooser dialog box
    GtkWidget *w_img_main;              // Pointer to image widget
    GtkWidget *w_window_label;          // Pointer to a window to display the text
    GtkWidget *w_window_help;           // Pointer to a window to display the text
    GtkWidget *w_label_text_help;       // Pointer to an label to display the text to help
    GtkWidget *w_label_text;            // Pointer to an label to display the text
    char      *w_path;                  // path of the image open
    char      *w_save_path;             // path of the file where the text is save
    char      *w_text_to_save;          // string of the text to save
    int        w_step;
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
    widgets->w_window_label = GTK_WIDGET(gtk_builder_get_object(builder, "window_label"));
    widgets->w_window_help = GTK_WIDGET(gtk_builder_get_object(builder, "window_help"));
    widgets->w_label_text = GTK_WIDGET(gtk_builder_get_object(builder, "text"));
    widgets->w_label_text_help = GTK_WIDGET(gtk_builder_get_object(builder, "text_help"));
    widgets->w_path = malloc(sizeof(char));
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

// Open the text
void on_menuitm_about_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
    UNUSED(menuitem);
    const gchar *text =
    "-File: \n\
    1)open     : ouvrir une image à l'aide de l'explorateur de fichier \n\
    2)save     : sauvegarde le texte retourner par le réseau de neurones \n\
    3)save as  : \n\
    4)quit     : ferme le sous menu \n\
    -Help: \n\
            -about: ouvre une fenêtre avec des instructions d'utilisations \n\
    \n\
    Les autres boutons: \n\
                    -Next step : permet après l'ouverture d'une image par l'explorateur de fichier de voir la procédure de traitement de l'image et le texte retourner\
    par le réseau de neurones etape par etape.\n\
                    -Apply : permet après ouverture d'une image par l'explorateur de fichier de voir le résultat final après analyse du réseau de neurones\n\
    \n\
    La fenetre Help->about : fenêtre d'aide avec les instructions d'utilisations du projet\n\
    La fenetre de texte : montre le texte renvoyer par le réseau de neuronne après traitement.\n\
    \n\
    Elle contient 2 boutons:\n\
                        -Train : permet d'envoyer le texte au réseau de neuronne après modification par l'utilisateur s'il y avait une erreur.\n\
                        -Close : masque la fenetre au lieu de la détruire ce qui lui permet de se réouvrir plus tard avec d'autres images.\n\
                        En effet la croix en haut à gauche détruit la fenêtrece qui l'empêche de se réouvrir plus tard après le traitement d'une autre image.\n";
    gtk_widget_show(app_wdgts->w_window_help);
    gtk_label_set_text (GTK_LABEL(app_wdgts->w_label_text_help),text);
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
            GdkPixbuf *newpixbuf = New_Size_Image(app_wdgts->w_img_main, 500, 500);
            gtk_image_set_from_pixbuf (GTK_IMAGE(app_wdgts->w_img_main), newpixbuf);
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

    FILE *fp = fopen(app_wdgts->w_save_path, "a");
    //write
    fputs(app_wdgts->w_text_to_save, fp);
    // add new line at the end of the file
    fputc('\n', fp);
    // free the file
    fclose(fp);
    // Finished with the "Open Image" dialog box, so hide it
    gtk_widget_hide(app_wdgts->w_dlg_save_file);
}

//step zero of the process od the ocr
void step_zero(app_widgets *app_wdgts)
{
    //UNUSED(button);
    //image grey lvl normalised
    gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main), app_wdgts->w_path);
    Change_Color(app_wdgts->w_img_main,Colored_to_classicGreyLvl);
    Change_Color(app_wdgts->w_img_main,ClassicGLVL_to_NormalizedGLVL);
    Change_Color(app_wdgts->w_img_main,Colored_to_OnlyBlack);
    GdkPixbuf *newpixbuf = New_Size_Image(app_wdgts->w_img_main, 500, 500);
    gtk_image_set_from_pixbuf (GTK_IMAGE(app_wdgts->w_img_main), newpixbuf);
}

//step one of the process od the ocr
void step_one(app_widgets *app_wdgts)
{
    //image grey only black
    gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main), app_wdgts->w_path);
    Change_Color(app_wdgts->w_img_main,Colored_to_classicGreyLvl);
    Change_Color(app_wdgts->w_img_main,ClassicGLVL_to_NormalizedGLVL);
    Change_Color(app_wdgts->w_img_main,Colored_to_OnlyBlack);
    GdkPixbuf *newpixbuf = New_Size_Image(app_wdgts->w_img_main, 500, 500);
    gtk_image_set_from_pixbuf (GTK_IMAGE(app_wdgts->w_img_main), newpixbuf);
    //segmentation
}

//step two of the process od the ocr
void step_two(app_widgets *app_wdgts)
{
    //image grey lvl normalised
    gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main), app_wdgts->w_path);
    Change_Color(app_wdgts->w_img_main,Colored_to_classicGreyLvl);
    Change_Color(app_wdgts->w_img_main,ClassicGLVL_to_NormalizedGLVL);
    Change_Color(app_wdgts->w_img_main,Colored_to_OnlyBlack);
    GdkPixbuf *newpixbuf = New_Size_Image(app_wdgts->w_img_main, 500, 500);
    gtk_image_set_from_pixbuf (GTK_IMAGE(app_wdgts->w_img_main), newpixbuf);
    //segmentation

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

void on_button_apply_clicked(GtkButton *button, app_widgets *app_wdgts)
{
    UNUSED(button);
    //g_print("ca marche");
    //UNUSED(app_wdgts);
    step_two(app_wdgts);
}

//Close the pop up window
void on_button_close_clicked(GtkButton *button, app_widgets *app_wdgts)
{
    UNUSED(button);
    gtk_widget_hide(app_wdgts->w_window_label);
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
