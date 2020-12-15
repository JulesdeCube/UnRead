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

#include <stdlib.h>
#include <stdio.h>
#include "neural_network_error.h"
#include "layer.h"

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

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                                CONSTRUCTOR                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

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
**
** \throw NN_NO_FUNCTION no error or/and activation function provided
** \throw NN_ERROR_SPACE there is not enought free space to store the neural
**        netowrk and his layer/neurone
**
** \see layer.h:la_consructor for sub error code
*/
struct s_neural_network *nn_consructor(unsigned int nb_layer, unsigned int *layers_size, struct s_function_1p activation_func, struct s_function_2p error_func, enum e_nn_error *error);

/**
** \brief `s_neural_network` file constuctor.
**
** create a neural network from a file
**
** \param fp file where the neural netowork as store
** \param activation_func the activation and is derivate
**        function for each neurone
** \param error_func the error function and is derivate
** \param error the error callback code
**
** \return a new instance of `s_neural_network`
**
** \throw NN_PERMISSION_DENIED no file provided
** \throw NN_NO_FUNCTION no error or/and activation function provided
** \throw NN_ERROR_SPACE there is not enought free space to store the neural
**        netowrk and his layer/neurone
**
** \see layer.h:la_file_consructor for sub error code
*/
struct s_neural_network *nn_file_consructor(FILE *fp, struct s_function_1p activation_func, struct s_function_2p error_func, enum e_nn_error *error);

/**
** \brief `s_neural_network` constuctor by file path.
**
** create a neural network from the path of a file
**
** \param filename path to file where the neural netowrk is store
** \param activation_func the activation and is derivate
**        function for each neurone
** \param error_func the error function and is derivate
** \param error the error callback code
**
** \return a new instance of `s_neural_network`
**
** \throw NN_PERMISSION_DENIED file can't be found
**
** \see s_neural_network for sub error code
*/
struct s_neural_network *nn_from_file(char *filename, struct s_function_1p activation_func, struct s_function_2p error_func, enum e_nn_error *error);

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                                 DESTRUCTOR                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

/**
** \brief `s_neural_network` destructor.
**
**  free space and propely destruct the neural network
**
** \param set a pointer to the set to destroy
*/
void nn_destructor(struct s_neural_network *self);

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                                   METHODE                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

/**
** \brief apply the neural network to the given input
**
** take a list of value a put it into the neural network and compute the output
**
** \param self the neural network to compute
** \param input the value of the first layer
** \param error the return error channel
**
** \throw NN_NO_NEURAL_NETWORK no neural network provided to the function
**
** \see layer.h:la_apply for sub error code
*/
void nn_apply(struct s_neural_network *self, double *input, enum e_nn_error *error);

/**
** \brief compute neural network
**
** compute the value of each neurone layer by layer
**
** \param self the neural network to compute
** \param error the return error channel
**
** \throw NN_NO_NEURAL_NETWORK no neural network provided to the function
**
** \see layer.h:na_compute for sub error code
*/
void nn_compute(struct s_neural_network *self, enum e_nn_error *error);

/**
** \brief save the neural_network to file
**
** open and create a file in not exist and save the neural network information
** into it
**
** \param self the neural network to save
** \param filename the path to a file (that can not exist) where the neural
**        network will be save.
** \param error the return error channel
**
** \throw NN_NO_NEURAL_NETWORK no neural network provided to the function
** \throw NN_PERMISSION_DENIED the file can't be open
**
** \see la_write for sub error code
*/
void nn_save(struct s_neural_network *self, char *filename, enum e_nn_error *error);

/**
** \brief write the content of a neural network
**
** write the weight and the biais of a neural network in the given file
**
** \param self the neural network to save
** \param fp file
** \param error the return error channel
**
** \throw NN_NO_NEURAL_NETWORK no neural network provided to the function
** \throw NN_PERMISSION_DENIED no file provided
**
** \see layer.h:la_write for sub error code
*/
void nn_write(struct s_neural_network *self, FILE *fp, enum e_nn_error *error);

/**
** \brief update the neural netowrk
**
** back propagate derivate error on each weight and baias
**
** \param self the neural network
** \param error the return error channel
**
** \throw NN_NO_NEURAL_NETWORK no neural network provided to the function
**
** \see layer.h:la_back_propagage for sub error code
*/
void nn_back_propagage(struct s_neural_network *self, enum e_nn_error *error);

/**
** \brief update the neural netowrk
**
** update weight and bias of each neurone to match with the targeted value
**
** \param self the neural network
** \param targets the targeted output values
** \param error the return error channel
**
** \return the totale error value
**
** \throw NN_NO_NEURAL_NETWORK no neural network was provided
** \throw NN_NO_VALUES if the targets array is empty
** \throw NN_NO_LAYER if there is not layer inside the neural network
**
** \see layer.h:la_get_sum_error for sub error code
*/
double nn_total_error(struct s_neural_network *self, double *targets, enum e_nn_error *error);

/**
** \brief transfer the output into the outputs pointer
**
** get the ouput of the neural network
**
** \param self the neural network
** \param outputs an array to store the outputs
** \param error the return error channel
**
** \throw NN_NO_NEURAL_NETWORK no neural network was provided
** \throw NN_NO_LAYER if there is not layer inside the neural network
**
** \see layer.h:la_get_outputs for sub error code
*/
void nn_get_outputs(struct s_neural_network *self, double *outputs, enum e_nn_error *error);

/**
** \brief return the size of the last layer
**
** return the number of neurone in the last layer
**
** \param self the neural network
** \param error the return error channel
**
** \return the size of the last neurone
**
** \throw NN_NO_NEURAL_NETWORK no neural network was provided
** \throw NN_NO_LAYER if there is not layer inside the neural network
*/
unsigned int nn_get_last_layer_size(struct s_neural_network *self, enum e_nn_error *error);

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                                   VIEWER                                   //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

/**
** \brief diplay the neural network state
**
** \param self the neural network to print
*/
void nn_print(struct s_neural_network *self);

#endif // UNREAD__SRC_NEURAL_NETWORK__NEURAL_NETWORK_H_