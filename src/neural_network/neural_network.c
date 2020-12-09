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

#include "neural_network.h"

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                                 CONSTRUCTOR                                //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

struct s_neural_network *nn_consructor(unsigned int nb_layer, unsigned int *layers_size, struct s_function_1p activation_func, struct s_function_2p error_func, enum e_nn_error *error)
{
  *error = NN_SUCCESS;

  struct s_neural_network *self = calloc(1, sizeof(struct s_neural_network));

  if (!self)
  {
    *error = NN_ERROR_SPACE;
    return NULL;
  }

  if (!activation_func.derivate || !activation_func.self)
  {
    *error = NN_NO_FUNCTION;
    nn_destructor(self);
    return NULL;
  }
  self->activation_func = activation_func;

  if (!error_func.self || !error_func.derivate)
  {
    *error = NN_NO_FUNCTION;
    nn_destructor(self);
    return NULL;
  }
  self->error_func = error_func;

  self->nb_layer = nb_layer;
  self->layers = calloc(self->nb_layer, sizeof(struct s_layer *));

  if (!self->layers)
  {
    *error = NN_ERROR_SPACE;
    nn_destructor(self);
    return NULL;
  }

  struct s_layer **previous_layer = NULL;
  struct s_layer **layer = self->layers;
  struct s_layer **last_layer = layer + self->nb_layer;
  for (; layer < last_layer && !*error; previous_layer = layer, ++layer, ++layers_size)
    *layer = la_consructor(*layers_size, previous_layer ? *previous_layer : NULL, self, error);

  if (*error)
  {
    for (; *layer >= *self->layers; --layer)
      la_destructor(*layer);
    self->layers = NULL;

    nn_destructor(self);

    *error = NN_ERROR_SPACE;
    return NULL;
  }

  return self;
}

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                                 DESTRUCTOR                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                                  METHODE                                   //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

void nn_apply(struct s_neural_network *self, double *input, enum e_nn_error *error)
{
  *error = NN_SUCCESS;

  if (!self)
  {
    *error = NN_NO_NEURAL_NETWORK;
    return;
  }

  // if there is no layer do nothing
  if (!self->nb_layer)
    return;
  // set the value in the fist layer
  la_set(*self->layers, input, error);
  // use forward propagation
  nn_compute(self, error);
}

void nn_compute(struct s_neural_network *self, enum e_nn_error *error)
{
  *error = NN_SUCCESS;

  if (!self)
  {
    *error = NN_NO_NEURAL_NETWORK;
    return;
  }

  // first and last layer of the neural network
  struct s_layer **layer = self->layers;
  struct s_layer **last_layer = layer + self->nb_layer;

  // apply computation to each layer exept the fist
  for (++layer; layer < last_layer && !*error; ++layer)
    la_compute(*layer, error);
}

void nn_save(struct s_neural_network *self, char *filename, enum e_nn_error *error)
{
  *error = NN_SUCCESS;

  // check if the neural network is provided
  if (!self)
  {
    *error = NN_NO_NEURAL_NETWORK;
    return;
  }

  FILE *fp = fopen(filename, "wb");

  // check if file exist
  if (!fp)
  {
    *error = NN_PERMISSION_DENIED;
    return;
  }

  // write neural_network information
  nn_write(self, fp, error);
  // free the file
  fclose(fp);
}

void nn_write(struct s_neural_network *self, FILE *fp, enum e_nn_error *error)
{
  *error = NN_SUCCESS;

  // check if the neural netowrk provided
  if (!self)
  {
    *error = NN_NO_NEURAL_NETWORK;
    return;
  }

  // no file provided
  if (!fp)
  {
    *error = NN_PERMISSION_DENIED;
    return;
  }

  // write the number of layer
  fwrite(&self->nb_layer, sizeof(self->nb_layer), 1u, fp);

  // first and last layer of the neural network
  struct s_layer **layer = self->layers;
  struct s_layer **last_layer = layer + self->nb_layer;

  // write each layer informations
  for (; layer < last_layer && !*error; ++layer)
    la_write(*layer, fp, error);
}

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                                   VIEWER                                   //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

void nn_print(struct s_neural_network *self)
{

  // if it not exist exit and print a message
  if (!self)
  {
    printf("ERROR: `nn_print` : no neural network provided\n");
    return;
  }

  printf("////////////////////////////////////////////////////////////////////////////////\n");
  printf("//                                                                            //\n");
  printf("//                                    INPUT                                   //\n");
  printf("//                                                                            //\n");
  printf("////////////////////////////////////////////////////////////////////////////////\n");
  // check if it exist at less 1 layer
  if (self->nb_layer)
    la_print(*self->layers);

  printf("\n\n\n");
  printf("////////////////////////////////////////////////////////////////////////////////\n");
  printf("//                                                                            //\n");
  printf("//                                   HIDDEN                                   //\n");
  printf("//                                                                            //\n");
  printf("////////////////////////////////////////////////////////////////////////////////\n");

  // loop beween the second layer and the penultimate
  for (unsigned int i = 2; i < self->nb_layer; ++i)
  {
    printf("\n=================================== LAYER %u ===================================\n", i - 1);
    la_print(*(self->layers + i - 1));
  }

  printf("\n\n\n");
  printf("////////////////////////////////////////////////////////////////////////////////\n");
  printf("//                                                                            //\n");
  printf("//                                   OUTPUT                                   //\n");
  printf("//                                                                            //\n");
  printf("////////////////////////////////////////////////////////////////////////////////\n");
  // print the last layer if there is at less 1 layer
  if (self->nb_layer)
    la_print(*(self->layers + self->nb_layer - 1));
}