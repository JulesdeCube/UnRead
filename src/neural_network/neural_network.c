/**
** \file src/neural_network/neural_network.c
** \author Jules Lefebvre <jules.lefebvre@epita.fr
** \version 1.0.0
** \date 2020/09/30
** \brief implemtation of the `neural_network` object
**
** containe every contructor, desturctor and method use in `neural_network`
** struct manipution
*/

#include <stdlib.h>
#include "neural_network.h"

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                CONSTRUCTOR                                //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

struct s_neural_network *nn_consructor(unsigned int nb_layer, unsigned int *layers_size, struct s_function_1p activation_func, struct s_function_2p error_func, enum nn_error *error)
{

  struct s_neural_network *self = calloc(1, sizeof(struct s_neural_network));

  if (self == NULL)
  {
    *error = NN_ERROR_SPACE;
    return NULL;
  }

  if (activation_func.derivate == NULL || activation_func.self == NULL)
  {
    *error = NN_NO_FUNCTION;
    nn_destructor(self);
    return NULL;
  }
  self->activation_func = activation_func;

  if (error_func.self == NULL || error_func.derivate == NULL)
  {
    *error = NN_NO_FUNCTION;
    nn_destructor(self);
    return NULL;
  }
  self->error_func = error_func;

  self->nb_layer = nb_layer;
  self->layers = calloc(self->nb_layer, sizeof(struct s_layer *));

  if (self->layers == NULL)
  {
    *error = NN_ERROR_SPACE;
    nn_destructor(self);
    return NULL;
  }

  enum la_error layer_error = LA_SUCCESS;
  struct s_layer **previous_layer = NULL;
  struct s_layer **layer = self->layers;
  struct s_layer **last_layer = layer + self->nb_layer;
  for (; layer < last_layer && layer_error == LA_SUCCESS; previous_layer = layer, ++layer, ++layers_size)
    *layer = la_consructor(*layers_size, previous_layer ? *previous_layer : NULL, self, &layer_error);

  if (layer_error != LA_SUCCESS)
  {
    for (; *layer >= *self->layers; --layer)
      la_destructor(*layer);
    self->layers = NULL;

    nn_destructor(self);

    *error = NN_ERROR_SPACE;
    return NULL;
  }

  *error = NN_SUCCESS;
  return self;
}

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                 DESTRUCTOR                                //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

void nn_destructor(struct s_neural_network *self)
{
  if (self == NULL)
    return;

  struct s_layer **layer = self->layers;
  struct s_layer **last_layer = layer + self->nb_layer;
  for (; *layer < *last_layer; ++layer)
    la_destructor(*layer);

  free(self->layers);
}

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                 OPERATIONS                                //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

void nn_apply(struct s_neural_network *self, double *input)
{
  // if there is no layer do nothing
  if (!self->nb_layer)
    return;
  // set the value in the fist layer
  la_set(*self->layers, input);
  // use forward propagation
  nn_compute(self);
}

void nn_compute(struct s_neural_network *self)
{
  // first and last layer of the neural network
  struct s_layer **layer = self->layers;
  struct s_layer **last_layer = layer + self->nb_layer;

  // apply computation to each layer exept the fist
  for (++layer; layer < last_layer; ++layer)
    la_compute(*layer);
}

enum nn_error la_to_nn_error(enum la_error error)
{
  switch (error)
  {
  case LA_SUCCESS:
    return NN_SUCCESS;

  case LA_ERROR_SPACE:
    return NN_ERROR_SPACE;

  case LA_NO_NEURAL_NETWORK:
    return NN_NO_NEURAL_NETWORK;

  case LA_NO_LAYER:
    return NN_NO_LAYER;

  default:
    printf("ERROR: `la_to_nn_error`: unkown error : %d", error);
    return (enum la_error) - 1;
  }
}

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                   VIEWER                                  //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

void nn_print(struct s_neural_network *self)
{
  printf("///////////////////////////////////////////////////////////////////////////////\n");
  printf("//                                                                           //\n");
  printf("//                                   INPUT                                   //\n");
  printf("//                                                                           //\n");
  printf("///////////////////////////////////////////////////////////////////////////////\n");
  // check if it exist at less 1 layer
  if (self->nb_layer)
    la_print(*self->layers);

  printf("\n\n\n");
  printf("///////////////////////////////////////////////////////////////////////////////\n");
  printf("//                                                                           //\n");
  printf("//                                  HIDDEN                                   //\n");
  printf("//                                                                           //\n");
  printf("///////////////////////////////////////////////////////////////////////////////\n");

  // loop beween the second layer and the penultimate
  for (unsigned int i = 2; i < self->nb_layer; ++i)
  {
    printf("\n=================================== LAYER %u ===================================\n", i - 1);
    la_print(*(self->layers + i - 1));
  }

  printf("\n\n\n");
  printf("///////////////////////////////////////////////////////////////////////////////\n");
  printf("//                                                                           //\n");
  printf("//                                  OUTPUT                                   //\n");
  printf("//                                                                           //\n");
  printf("///////////////////////////////////////////////////////////////////////////////\n");
  // print the last layer if there is at less 1 layer
  if (self->nb_layer)
    la_print(*(self->layers + self->nb_layer - 1));
}