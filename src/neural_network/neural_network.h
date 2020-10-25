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

/**
** \enum s_neural_network
** \brief code error of the `s_neural_network`'s function
**
** this containe return code error for constuctor and methode of the
** `s_neural_network` object
*/
enum nn_error
{
  /**
  ** succes creation of a `s_neurone_network`
  */
  NN_SUCCESS = 0,
  /**
  ** no neural network provided
  */
  NN_NO_NEURAL_NETWORK,
  /**
  ** not enought free space evalable
  */
  NN_ERROR_SPACE,
  /**
  ** no layer provided to the neurone
  */
  NN_NO_LAYER,
  /**
  ** no function provided
  */
  NN_NO_FUNCTION
};

/**
** \struct s_function_1p
** \brief a function with 1 parameter and is derivate
*/
struct s_function_1p
{
  double (*self)(double);
  double (*derivate)(double);
};

/**
** \struct s_function_2p
** \brief a function with 2 parameter and is derivate
*/
struct s_function_2p
{
  double (*self)(double, double);
  double (*derivate)(double, double);
};

/**
** \struct s_neural_network
** \brief a multi layer neural network
*/
struct s_neural_network
{
  unsigned int nb_layer;
  struct s_layer **layers;
  struct s_function_1p activation_func;
  struct s_function_2p error_func;
};

#include <stdlib.h>
#include "layer.h"

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
** \param nb_layer the number of layer in the network
** \param layers_size a array containging the number of neurone of each layer
** \param activation_func the activation and is derivate
**        function for each neurone
** \param error_func the error function and is derivate
** \param error the error callback code
**
** \return a new instance of `s_neural_network`
*/
struct s_neural_network *nn_consructor(unsigned int nb_layer, unsigned int *layers_size, struct s_function_1p activation_func, struct s_function_2p error_func, enum nn_error *error);

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
void nn_destructor(struct s_neural_network *self);

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                  METHODE                                  //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

/**
** \brief apply the neural network to the given input
**
** take a list of value a put it into the neural network and compute the output
**
** \param self the neural network to compute
** \param input the value of the first layer
*/
void nn_apply(struct s_neural_network *self, double *input);

/**
** \brief compute neural network
**
** compute the value of each neurone layer by layer
**
** \param self the neural network to compute
** \param input the value of the first layer
*/
void nn_compute(struct s_neural_network *self);

/**
** \brief convert an layer error to a neural network error
**
**  convert `la_error` to `nn_error`
**
** \param error the layer error
**
** \return the equivalent neural network error
*/
enum nn_error la_to_nn_error(enum la_error error);

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                   VIEWER                                  //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

/**
** \brief diplay the neural network state
**
** \param self the neural network to print
*/
void nn_print(struct s_neural_network *self);

#endif // UNREAD__SRC_NEURAL_NETWORK__NEURAL_NETWORK_H_