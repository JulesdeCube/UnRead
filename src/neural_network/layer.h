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

/**
** \enum la_errror
** \brief code error of the `s_layer`'s function
**
** this containe return code error for constuctor and methode of the `s_layer`
** object
*/
enum la_error
{
  /**
  ** succes creation of a `s_neurone`
  */
  LA_SUCCESS = 0,
  /**
  ** no neural network provided
  */
  LA_NO_NEURAL_NETWORK,
  /**
  ** not enought free space evalable
  */
  LA_ERROR_SPACE,
  /**
  ** no layer provided to the neurone
  */
  LA_NO_LAYER
};

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
  struct s_neural_network *neural_network;
};

#include <stdlib.h>
#include <stdio.h>
#include "neurone.h"
#include "neural_network.h"

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
** ⚠️** you need to use the `la_destructor` function after use (to free space )
** ** ⚠️
**
** \return a pointer to a new instance of `s_layer`
*/
struct s_layer *la_consructor(unsigned int size, struct s_layer *previous_layer, struct s_neural_network *neural_network, enum la_error *error);

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
void la_destructor(struct s_layer *self);

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                  METHODE                                  //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

/**
** \brief convert an neurone error to a layer error
**
**  convert `ne_error` to `la_error`
**
** \param error the neurone error
**
** \return the equivalent layer error
*/
enum la_error ne_to_la_error(enum ne_error error);

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                   VIEWER                                  //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

/**
** \brief diplay the layer information
**
** \param self the layer to print
*/
void la_print(struct s_layer *self);

#endif // UNREAD__SRC_NEURAL_NETWORK__LAYER_H_