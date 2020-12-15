#ifndef UNREAD__SRC_PREPROCESSING__HISTO_GREY_LVL_H_
#define UNREAD__SRC_PREPROCESSING__HISTO_GREY_LVL_H_

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>

#include "tools.h"

/**
 ** \brief Apply normalized grey level on a image with the use of histogram
 **  (precise lower and higher limits)
 **
 ** \param image which image to apply
 ** \param black_percent lower limit of the histogram in PERCENTAGE
 ** \param white_percent higher limit of the histogral in PERCENTAGE
*/
void histo_greylvl(GtkWidget *image, double black_percent, double white_percent);

#endif // UNREAD__SRC_PREPROCESSING__HISTO_GREY_LVL_H_