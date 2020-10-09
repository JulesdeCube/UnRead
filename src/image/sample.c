/**
** \file src/image/sample.c
** \author Jules Lefebvre <jules.lefebvre@epita.fr
** \version 1.0.0
** \date 2020/10/04
** \brief implemetation of the `s_sample` object
**
** cantaigne all the fuction use to maipulate the s_sample object
*/

#include "sample.h";

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                CONSTRUCTOR                                //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

struct s_sample sp_consructor(unsigned int height, unsigned int width, char label, enum mk_error *error)
{
  return (struct s_sample) {mk_constructor(height, width, error),  label};
}

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                 DESTRUCTOR                                //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

void sp_destructor(struct s_sample *sample)
{
  mk_destructor(&(sample->image));
}

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                  METHODE                                  //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
