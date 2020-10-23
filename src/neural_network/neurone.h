/**
** \file src/neural_network/neurone.h
** \author Jules Lefebvre <jules.lefebvre@epita.fr
** \version 1.0.0
** \date 2020/10/04
** \brief declaraton of the `neurone` object.
**
** definition of constuctor, destructor and method of the `neurone` object.
*/

#ifndef UNREAD__SRC_NEURAL_NETWORK__NEURONE_H_
#define UNREAD__SRC_NEURAL_NETWORK__NEURONE_H_

/**
** \enum ne_errror
** \brief code error of the `s_neurone`'s function
**
** this containe return code error for constuctor and methode of the `s_neurone`
** object
*/
enum ne_error
{
  /**
  ** succes creation of a `s_neurone`
  */
  NE_SUCCESS = 0,
  /**
  ** no layer provided
  */
  NE_NO_LAYER,
  /**
  ** not enought free space evalable
  */
  NE_ERROR_SPACE
};

//prevent definition of ne error before usage in defintion

/**
** \struct s_neurone
** \brief a neurone for neural network
*/
struct s_neurone
{
  double value;
  double bias;
  double *weights;
  struct s_layer *layer;
};

#include <stdlib.h>
#include "layer.h"
#include "utils.h"

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                CONSTRUCTOR                                //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

/**
** \brief `s_neurone` constuctor.
**
** create a neurone for neural network
**
** \return a new instance of `s_neurone`
*/
struct s_neurone ne_consructor(struct s_layer *layer, enum ne_error *error);

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                 DESTRUCTOR                                //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

/**
** \brief `s_neural_network` destructor.
**
**  free space and propely destruct the neural network
**
** \param set a pointer to the set to destroy
*/
void ne_destructor(struct s_neurone *neurone);

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                  METHODE                                  //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                   VIEWER                                  //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

/**
** \brief diplay the neurone information
**
** \param self the neurone to print
*/
void ne_print(struct s_neurone *self);

#endif // UNREAD__SRC_NEURAL_NETWORK__NEURONE_H_