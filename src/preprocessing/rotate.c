#include "rotate.h"

/**
** \brief Get the new position of x with an rotation of degree
**
** \param x position
** \param y position
** \param degree degree of rotation IN GRADIENT
**
** \return new position of x
*/
int get_new_x(int x, int y, double degree)
{
    return x * cos(degree) - y * sin(degree);
}

/**
** \brief Get the new position of y with an rotation of degree
**
** \param x position
** \param y position
** \param degree degree of rotation IN GRADIENT
**
** \return new position of y
*/
int get_new_y(int x, int y, double degree)
{
    return x * sin(degree) + y * cos(degree);
}

void apply_rotation(GtkWidget *image, enum e_rotate_type r_type, double degree,
                    guchar *filter(struct s_rotate_tools))
{
    // Initialize our tools
    struct s_rotate_tools tools;

    // Transform degrees in radient
    tools.degree = 3.14159265358979323846264338 * degree / 180;

    // All informations to take of the pixbuffer
    GdkPixbuf *pixbuf = gtk_image_get_pixbuf((GtkImage *)image);
    tools.n_channels = gdk_pixbuf_get_n_channels(pixbuf);
    tools.rowstride = gdk_pixbuf_get_rowstride(pixbuf);
    tools.height = gdk_pixbuf_get_height(pixbuf);
    tools.width = gdk_pixbuf_get_width(pixbuf);
    tools.which_pixels = gdk_pixbuf_get_pixels(pixbuf);

    // To inverse width and height for future rotation
    int w, h;
    switch (r_type)
    {
    case INVERSE_HW:
        tools.newHeight = tools.width;
        tools.newWidth = tools.height;
        break;
    case NONE:
        tools.newHeight = tools.height;
        tools.newWidth = tools.width;
        break;
    case MORE_SPACE:
        w = tools.width / 2;
        h = tools.height / 2;
        tools.newWidth = 2 * max(abs(get_new_x(-w, h, tools.degree)),
                                 abs(get_new_x(w, h, tools.degree)));
        tools.newHeight = 2 * max(abs(get_new_y(-w, h, tools.degree)),
                                  abs(get_new_y(w, h, tools.degree)));
        break;
    default:
        break;
    }

    // New pixbuf for an image
    GdkPixbuf *newpixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, 0, 8, tools.newWidth, tools.newHeight);
    int newRowstride = gdk_pixbuf_get_rowstride(newpixbuf);
    guchar *new_which_pixels = gdk_pixbuf_get_pixels(newpixbuf);

    for (int y = 0; y < tools.newHeight; ++y)
    {
        for (int x = 0; x < tools.newWidth; ++x)
        {
            tools.x = x;
            tools.y = y;
            guchar *newp = new_which_pixels + y * newRowstride + x * tools.n_channels;
            guchar *oldp = filter(tools);
            // Change colors of RGB
            if (oldp != NULL)
                // Put with colors of the older pixbuf
                set_3values(newp, oldp[0], oldp[1], oldp[2]);
            else
                // Do not find an old pixel, put in white
                set_3values(newp, 255, 255, 255);
        }
    }

    // Change old image with the new pixbuf
    gtk_image_set_from_pixbuf(GTK_IMAGE(image), newpixbuf);
}

/**
** \brief return the old position of the pixel with an rotation of tools.degree
**
** \param tools all tools to use for rotation
**
** \return old pixel or NULL if does not exist
*/
guchar *classicRotate(struct s_rotate_tools tools)
{
    tools.x -= tools.newWidth / 2;
    tools.y -= tools.newHeight / 2;
    int oldX = get_new_x(tools.x, tools.y, tools.degree) + tools.width / 2;
    int oldY = get_new_y(tools.x, tools.y, tools.degree) + tools.height / 2;
    if (oldX < 0 || oldX >= tools.width || oldY < 0 || oldY >= tools.height)
        return NULL;
    return tools.which_pixels + oldY * tools.rowstride + oldX * tools.n_channels;
}

/**
** \brief return the old position of the pixel with an rotation of 180 degrees
**
** \param tools all tools to use for rotation
**
** \return old pixel
*/
guchar *rotate180(struct s_rotate_tools tools)
{
    return tools.which_pixels + (tools.height - tools.y - 1) * tools.rowstride + (tools.width - tools.x - 1) * tools.n_channels;
}

/**
** \brief return the old position of the pixel with an rotation of 90 degrees
** in trigonometry rotation
**
** \param tools all tools to use for rotation
**
** \return old pixel
*/
guchar *rotate90(struct s_rotate_tools tools)
{
    return tools.which_pixels + tools.x * tools.rowstride + (tools.width - tools.y - 1) * tools.n_channels;
}

/**
** \brief return the old position of the pixel with an rotation of -90 degrees
** in trigonometry rotation
**
** \param tools all tools to use for rotation
**
** \return old pixel
*/
guchar *rotate270(struct s_rotate_tools tools)
{
    return tools.which_pixels + (tools.height - tools.x - 1) * tools.rowstride + tools.y * tools.n_channels;
}

void rotate(GtkWidget *image, double degree)
{
    degree = modulo(degree, 360);
    switch ((long)degree)
    {
    case 0:
        break;

    case 90:
        apply_rotation(image, INVERSE_HW, degree, rotate90);
        break;

    case 270:
        apply_rotation(image, INVERSE_HW, degree, rotate270);
        break;

    case 180:
        apply_rotation(image, NONE, degree, rotate180);
        break;
    default:
        apply_rotation(image, MORE_SPACE, degree, classicRotate);
        break;
    }
}