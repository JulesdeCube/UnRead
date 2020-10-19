/**
** \file src/neural_network/neural_network.h
** \author Jules Lefebvre <jules.lefebvre@epita.fr
** \version 1.0.0
** \date 2020/10/04
** \brief declaraton of the `s_neural_network` object.
**
** definition of constuctor, destructor and method of the  s_neural_network`
** object.
*/

#ifndef UNREAD__SRC_NEURAL_NETWORK__NEURAL_NETWORK_H_
#define UNREAD__SRC_NEURAL_NETWORK__NEURAL_NETWORK_H_

#include <stdio.h>
#include "layer.h"

/**
** \struct s_function
** \brief une fonction et sa derive
*/
struct s_function
{
  float (*self)(double);
  float (*derivate)(double);
}

/**
** \struct s_neural_network
** \brief a multi layer neural network
*/
struct s_neural_network
{
  unsigned int nb_layer;
  struct s_layers *layers;
  struct s_function activation_func;  
};

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                CONSTRUCTOR                                //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

/**
** \brief `s_neural_network` constuctor.
**
** create a neural network
**
** \return a new instance of `s_neural_network`
*/
struct s_neural_network nn_consructor(unsigned int nb_layer,unsigned int *layers_size, struct s_function function,  enum nn_error *error);

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
void nn_destructor(struct s_neural_network *neural_network);

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