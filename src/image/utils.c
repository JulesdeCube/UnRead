/**
** \file src/image/utils.c
** \author Jules Lefebvre <jules.lefebvre@epita.fr
** \version 1.0.0
** \date 2020/12/13
** \brief utils function for dataset
*/

#include "utils.h"

long fsize(FILE *fp)
{
  int prev = ftell(fp);
  fseek(fp, 0L, SEEK_END);
  long sz = ftell(fp);
  fseek(fp, prev, SEEK_SET); //go back to where we were
  return sz;
}
void fget_revers(void *value, size_t size, FILE *fp, enum sp_error *error, enum sp_error end_error)
{
  for (char *cp = value; size; --size)
  {
    if (feof(fp) || *error)
    {
      *error = end_error;
      return;
    }

    *(cp + size - 1) = fgetc(fp);
  }
}

unsigned int fgetu(FILE *fp, enum sp_error *error, enum sp_error end_error)
{
  unsigned int value = 0;
  fget_revers(&value, sizeof(value), fp, error, end_error);
  return !*error ? value : 0;
}