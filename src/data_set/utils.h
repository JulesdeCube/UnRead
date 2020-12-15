/**
** \file src/data_set/utils.h
** \author Jules Lefebvre <jules.lefebvre@epita.fr
** \version 1.0.0
** \date 2020/12/13
** \brief utils function for dataset
*/

#ifndef UNREAD__SRC_DATA_SET__UTILS_H_
#define UNREAD__SRC_DATA_SET__UTILS_H_

#include <stdio.h>
#include "sample.h"

/**
** \brief get unsigned int from a file
**
** read the 4 fist bytes and convert it into unsigned int
** will not read if it's the end of the file or if there is an error
**
** \param fp the file to read
** \param error error channel
** \param end_error error to return if it's the end of the file
**
** \return the unsigned int
*/
unsigned int fgetu(FILE *fp, enum sp_error *error, enum sp_error end_error);

/**
** \brief get the number of bytes in a file
**
** \param fp the file
**
** \return the size
*/
long fsize(FILE *fp);

/**
** \brief write size number of bytes into a buffer (in revers order) from the file
**
** will not read if it's the end of the file or if there is an error
**
** \param value the output buffer
** \param size the number of bytes to read
** \param fp the file to read
** \param error error channel
** \param end_error error to return if it's the end of the file
**
** \return the unsigned int
*/
void fget_revers(void *value, size_t size, FILE *fp, enum sp_error *error, enum sp_error end_error);

#endif // UNREAD__SRC_DATA_SET__UTILS_H_