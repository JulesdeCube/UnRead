#ifndef UNREAD__SRC_PREPROCESSING__TOOLS_H_
#define UNREAD__SRC_PREPROCESSING__TOOLS_H_

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <math.h>

#define UNUSED(x) (void)(x)

/**
 * \brief tuple of int with min and max
 */
struct s_int_tuple
{
    int min;
    int max;
};

/**
** \brief Search the whitest (maximum) and the blackest (minimum) pixel of a pixbuf
** corresponding to an image
**
** \param image search on this image
**
** \return tuple with minimum and maximum values
*/
struct s_int_tuple search_BW_pixel(GtkWidget *image);

/**
** \brief set 3 values on a pointer p
**
** \param p pointer to change values
** \param v1 first value
** \param v2 second value
** \param v3 third value
*/
void set_3values(guchar *p, int v1, int v2, int v3);

/**
** \brief  Change pixel code in CLASSIC grey level to a pixel code in NORMALIZED grey level
** /!\ Only works with an image which is already in grey level /!\
**
** \param pixel which apply new color
** \param min_max tuple with the maximum and minimum color of the image
*/
void normalized_pixel(guchar *pixel, struct s_int_tuple min_max);

/**
** \brief pythagore function
**
** \param a a side
** \param b an other side
**
** \return result of pyth for a third side
*/
int pythagore(int a, int b);

/**
** \brief maximum function
**
** \param a a value
** \param b an other value
**
** \return the maximum between 2 parameters
*/
int max(int a, int b);

/**
** \brief modulo function
**
** \param x a value
** \param y an other value to divide the first
**
** \return result of modulo division
*/
double modulo(double x, double y);
#endif // UNREAD__SRC_PREPROCESSING__TOOLS_H_