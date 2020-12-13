/**
** \file src/image/utils.h
** \author Jules Lefebvre <jules.lefebvre@epita.fr
** \version 1.0.0
** \date 2020/12/13
** \brief utils function for dataset
*/

#ifndef UNREAD__SRC_IMAGE__UTILS_H_
#define UNREAD__SRC_IMAGE__UTILS_H_

#include <stdio.h>
#include "sample.h"

unsigned int fgetu(FILE *fp, enum sp_error *error, enum sp_error end_error);

long fsize(FILE *fp);

void fget_revers(void *value, size_t size, FILE *fp, enum sp_error *error, enum sp_error end_error);

#endif // UNREAD__SRC_IMAGE__UTILS_H_