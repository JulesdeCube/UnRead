/**
** \file src/image/sample.h
** \author Jules Lefebvre <jules.lefebvre@epita.fr
** \version 1.0.0
** \date 2020/10/04
** \brief declaration of the `s_sample` object
**
** declartion of all the methode use to manipulate the `s_sample` object
*/

#ifndef UNREAD__SRC_IMAGE__SAMPLE_H_
#define UNREAD__SRC_IMAGE__SAMPLE_H_

#include "mask.h";

/**
** \struct s_sample
** \brief a sample to be proccess by the neurole network.
**
** for the label the value `\x00` is considere as unkown label
*/
struct s_sample
{
  struct s_mask image;
  char label;
};

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                CONSTRUCTOR                                //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

/**
** \brief `s_sample` constuctor.
**
** ⚠️** you need to use the `sp_destructor` function after sample use (to free
** space )** ⚠️
**
** \param height the number of row of pixels in the image
** \param width the number of collum of pixels in the image
** \param label the repesenting letter.
** \param error error return see `mk_constructor` for more information
**
** \return a new instance of `s_sample`
*/
struct s_sample sp_consructor(unsigned int height, unsigned int width, char label, enum mk_error *error);

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                 DESTRUCTOR                                //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

/**
** \brief `s_sample` destructor.
**
** \param sample a pointer to the sample to destroy
*/
void sp_destructor(struct s_sample *sample);

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                  METHODE                                  //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // UNREAD__SRC_IMAGE__SAMPLE_H_