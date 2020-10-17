/**
** \file src/image/set.h
** \author Jules Lefebvre <jules.lefebvre@epita.fr
** \version 1.0.0
** \date 2020/10/04
** \brief declaraton of the `s_set` object.
**
** definition of constuctor, destructor and method of the  s_set` object.
*/

#ifndef UNREAD__SRC_IMAGE__SET_H_
#define UNREAD__SRC_IMAGE__SET_H_

#include <stdio.h>
#include "sample.h"

/**
** \struct s_set
** \brief a contaigner of mask
*/
struct s_set
{
  unsigned int count;
  struct s_sample *samples;
};

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                CONSTRUCTOR                                //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

/**
** \brief `s_set` constuctor.
**
** create a colation
**
** \return a new instance of `s_set`
*/
struct s_set st_consructor(unsigned int count, unsigned int height, unsigned int width, enum sp_error *error);

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                 DESTRUCTOR                                //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

/**
** \brief `s_set` destructor.
**
**
**
** \param set a pointer to the set to destroy
*/
void st_destructor(struct s_set *set);

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                  METHODE                                  //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

/**
** \brief apply a function to all the sample
**
** \param mask the set to browse
*/
void st_foreach(struct s_set *set, void (*f)(struct s_sample *));


///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                   VIEWER                                  //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

/**
** \brief diplay all the sample in the set
**
** \param set the set to print
*/
void sp_print(struct s_set *set);

#endif // UNREAD__SRC_IMAGE__SET_H_