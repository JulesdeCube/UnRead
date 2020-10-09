/**
** \file src/image/sample.c
** \author Jules Lefebvre <jules.lefebvre@epita.fr
** \version 1.0.0
** \date 2020/10/04
** \brief implemetation of the `s_sample` object
**
** cantaigne all the fuction use to maipulate the s_sample object
*/

#include "sample.h"

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                CONSTRUCTOR                                //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

struct s_sample sp_consructor(unsigned int height, unsigned int width, char label, enum sp_error *error)
{
  // error catcher
  enum mk_error image_error;

  // create the sample
  struct s_sample sample = {mk_constructor(height, width, &image_error), label};
  // convert the returning error to be return
  *error = mk_to_sp_error(image_error);

  // return the created sample
  return sample;
}

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                 DESTRUCTOR                                //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

void sp_destructor(struct s_sample *sample)
{
  // destroy the mask
  mk_destructor(&(sample->image));
}

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                  METHODE                                  //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

enum sp_error mk_to_sp_error(enum mk_error error)
{
  switch (error)
  {
  case MK_SUCCESS:
    return SP_SUCCESS;

  case MK_ERROR_SPACE:
    return SP_ERROR_SPACE;

  case MK_ERROR_EOF:
    return SP_ERROR_EOF_IMAGE;

  default:
    printf("ERROR: `mk_t_to_Sp`: unkown error : %d", error);
    return (enum sp_error) - 1;
  }
}