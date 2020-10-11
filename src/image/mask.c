/**
** \file src/image/mask.c
** \author Jules Lefebvre <jules.lefebvre@epita.fr
** \version 1.0.0
** \date 2020/09/30
** \brief implemtation of the `s_mask` object
**
** containe every contructor, desturctor and method use in `s_mask` struct
** manipution
*/

#include "mask.h"

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                CONSTRUCTOR                                //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

struct s_mask mk_constructor(unsigned int height, unsigned int width, enum mk_error *error)
{
  // create the structure and set height and width
  struct s_mask mask = {height, width, NULL};

  // alocate pixels
  mask.pixels = (unsigned char *)calloc(height * width, sizeof(unsigned char));

  // if there is not enofe space return an error
  *error = mask.pixels == NULL ? MK_ERROR_SPACE : MK_SUCCESS;

  // if there is an error destroy the mask
  if (*error != MK_SUCCESS)
    mk_destructor(&mask);

  return mask;
}

struct s_mask mk_cconstructor(struct s_mask *mask, enum mk_error *error)
{
  // alocate the memory
  struct s_mask new_mask = mk_constructor(mask->height, mask->width, error);

  // `in_constructor` error handler
  switch (*error)
  {
  // success continue
  case MK_SUCCESS:
    break;

  // error during space alocation
  case MK_ERROR_SPACE:
    return new_mask;

  // mk_constuctor can't return this error
  case MK_ERROR_EOF:
    mk_destructor(&new_mask);
    printf("ERROR: `mk_fconstructor`: `mk_constructor` impossible error : MK_ERROR_EOF");
    return new_mask;

  // unkown error
  default:
    mk_destructor(&new_mask);
    printf("ERROR: `mk_fconstructor`: `mk_constructor` return unkown code error : %d",
           *error);
    return new_mask;
  }

  // pointer to the pixel
  unsigned char *pixel = mask->pixels;
  unsigned char *new_pixel = new_mask.pixels;
  // copy pixels value
  for (unsigned long i = mk_count(mask); i; --i, ++pixel, ++new_pixel)
    *new_pixel = *pixel;

  return new_mask;
}

struct s_mask mk_fconstructor(unsigned int height, unsigned int width, FILE *fp, enum mk_error *error)
{
  // create a new mask
  struct s_mask mask = mk_constructor(height, width, error);

  // `in_constructor` error handler
  switch (*error)
  {
  // success continue
  case MK_SUCCESS:
    break;

  // error during space alocation
  case MK_ERROR_SPACE:
    return mask;

  // mk_constuctor can't return this error
  case MK_ERROR_EOF:
    mk_destructor(&mask);
    printf("ERROR: `mk_fconstructor`: `mk_constructor` impossible error : MK_ERROR_EOF");
    return mask;

  // unkown error
  default:
    mk_destructor(&mask);
    printf("ERROR: `mk_fconstructor`: `mk_constructor` return unkown code error : %d",
           *error);
    return mask;
  }

  // fill it with file inforamtion
  mk_fimport(&mask, fp, error);

  // if there is an error during the creation return
  if (error != MK_SUCCESS)
    mk_destructor(&mask);

  return mask;
}

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                 DESTRUCTOR                                //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

void mk_destructor(struct s_mask *mask)
{
  // gard to not destroy an already destroy mask
  if (mask->pixels == NULL)
    return;

  // free alocate pixel
  free(mask->pixels);
  // set pixel to null to prevent probleme
  mask->pixels = NULL;
}

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                 OPERATIONS                                //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

void mk_fimport(struct s_mask *mask, FILE *fp, enum mk_error *error)
{
  // create a pointer to the fist pixel
  unsigned char *pixel = mask->pixels;

  //check if mask is alocate / or already destroy
  if (pixel == NULL)
  {
    // set error and exit
    *error = MK_ERROR_SPACE;
    return;
  }

  // loop to each pixel
  for (unsigned long i = mk_count(mask); i; --i, ++pixel)
  {
    // check if end of file
    if (feof(fp))
    {
      // set error and exit
      *error = MK_ERROR_EOF;
      return;
    }
    // set the value of the pixel base on file data
    *pixel = fgetc(fp);
  }

  // everything is ok set error to ok
  *error = MK_SUCCESS;
}

unsigned long mk_count(struct s_mask *mask)
{
  return mask->pixels == NULL ? 0 : mask->height * mask->width;
}
///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                   VIEWER                                  //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

void px_print(unsigned char value)
{
  // print a pixel in th rgb format but with all the channel equal
  printf("\x1B[38;2;%d;%d;%dm██", value, value, value);
}

void mk_print(struct s_mask *mask)
{
  unsigned char *pixel = mask->pixels;
  // if there is no pixel just quite
  if (pixel == NULL)
    return;

  // loop for each row
  for (unsigned int row = mask->height; row; --row)
  {
    // print each pixel of each line one by one
    for (unsigned int col = mask->width; col; --col, ++pixel)
      px_print(*pixel);

    // return to an new line at end of each row of pixel
    printf("\n");
  }
}

void mk_debug(struct s_mask *mask)
{
  unsigned char *pixel = mask->pixels;

  // if there is no pixel just print an error
  if (pixel == NULL)
  {
    printf("unalocate mask.\n");
    return;
  }

  // loop for each row
  for (unsigned int row = mask->height; row; --row)
  {
    // print each pixel value in hex
    for (unsigned int col = mask->width; col; --col, ++pixel)
      printf("%02x ", *pixel);

    // return to an new line at end of each row of pixel
    printf("\n");
  }
}