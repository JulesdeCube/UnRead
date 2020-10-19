/**
** \file src/neural_network/layer.h
** \author Jules Lefebvre <jules.lefebvre@epita.fr
** \version 1.0.0
** \date 2020/10/04
** \brief declaraton of the `s_layer` object.
**
** definition of constuctor, destructor and method of the  s_layer` object.
*/

#ifndef UNREAD__SRC_NEURAL_NETWORK__LAYER_H_
#define UNREAD__SRC_NEURAL_NETWORK__LAYER_H_

#include <stdio.h>
#include "neurone.h"

/**
** \struct s_layer
** \brief layer for a neural network
*/
struct s_layer
{
  unsigned int size;
  struct s_neurone *neurones;
  struct s_layer *previous_layer;
  struct s_layer *next_layer;
};

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                CONSTRUCTOR                                //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

/**
** \brief `s_layer` constuctor.
**
** create a layer for neural network
**
** \return a new instance of `s_layer`
*/
struct s_layer la_consructor(unsigned int size, struct s_layer *previous_layer, enum la_error *error);

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                 DESTRUCTOR                                //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

/**
** \brief `s_layer` destructor.
**
**  free space and propely destruct the layer neural network
**
** \param set a pointer to the set to destroy
*/
void la_destructor(struct s_layer *layer);

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

#endif // UNREAD__SRC_NEURAL_NETWORK__NEURAL_NETWORK_H_