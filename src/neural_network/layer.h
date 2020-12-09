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

#include <stdlib.h>
#include <stdio.h>

#include "neural_network_error.h"
#include "neural_network.h"
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
  struct s_neural_network *neural_network;
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
** ⚠️** you need to use the `la_destructor` function after use (to free space )
** ** ⚠️
**
** \return a pointer to a new instance of `s_layer`
*/
struct s_layer *la_consructor(unsigned int size, struct s_layer *previous_layer, struct s_neural_network *neural_network, enum e_nn_error *error);

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
** \param self a pointer to the layer to destroy
*/
void la_destructor(struct s_layer *self);

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                  METHODE                                  //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

/**
** \brief set output of neurone of the layer
**
** set each output of each neurone of the layer base on a array
**
** \param self the layer to set values
** \param value the list of values
*/
void la_set(struct s_layer *self, double *values, enum e_nn_error *error);

/**
** \brief apply forward propagation to each neurone
**
** compute with the previous neurone the output of each neurone of the layer
**
** \param self the layer compute
*/
void la_compute(struct s_layer *self, enum e_nn_error *error);

/**
** \brief write the content of a layer
**
** write the weight and the biais of a the neural
**
** \param self the layer to save
** \param fp file
*/
void la_write(struct s_layer *self, FILE *fp, enum e_nn_error *error);

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