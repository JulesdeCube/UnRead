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

  if (!activation_func.derivate || !activation_func.self ||
      !error_func.self || !error_func.derivate)
  {
    *error = NN_NO_FUNCTION;
    return NULL;
  }

  struct s_neural_network *self = calloc(1, sizeof(struct s_neural_network));

  if (!self)
  {
    *error = NN_ERROR_SPACE;
    return NULL;
  }

  self->activation_func = activation_func;
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
    *error = NN_ERROR_SPACE;
    nn_destructor(self);
    return NULL;
  }

  return self;
}

struct s_neural_network *nn_file_consructor(FILE *fp, struct s_function_1p activation_func, struct s_function_2p error_func, enum e_nn_error *error)
{
  *error = NN_SUCCESS;

  // check if there is a file
  if (!fp)
  {
    *error = NN_PERMISSION_DENIED;
    return NULL;
  }

  if (!activation_func.derivate || !activation_func.self ||
      !error_func.self || !error_func.derivate)
  {
    *error = NN_NO_FUNCTION;
    return NULL;
  }

  struct s_neural_network *self = calloc(1, sizeof(struct s_neural_network));

  if (!self)
  {
    *error = NN_ERROR_SPACE;
    return NULL;
  }

  self->activation_func = activation_func;
  self->error_func = error_func;
  // FIXME - check for end of file
  fread(&self->nb_layer, sizeof(self->nb_layer), 1, fp);
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
  for (; layer < last_layer && !*error; previous_layer = layer, ++layer)
    *layer = la_file_consructor(fp, previous_layer ? *previous_layer : NULL, self, error);

  if (*error)
  {
    nn_destructor(self);
    return NULL;
  }

  return self;
}

struct s_neural_network *nn_from_file(char *filename, struct s_function_1p activation_func, struct s_function_2p error_func, enum e_nn_error *error)
{
  *error = NN_SUCCESS;

  FILE *fp = fopen(filename, "rb");

  // check if file exist
  if (!fp)
  {
    *error = NN_PERMISSION_DENIED;
    return NULL;
  }

  // create the neural network from the file
  struct s_neural_network *self = nn_file_consructor(fp, activation_func, error_func, error);

  // free the file
  fclose(fp);

  return self;
}

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                                 DESTRUCTOR                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

void nn_destructor(struct s_neural_network *self)
{
  if (!self)
    return;

  struct s_layer **layer = self->layers;
  struct s_layer **last_layer = layer + self->nb_layer;
  for (; layer < last_layer; ++layer)
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
  la_set_values(*self->layers, input, error);
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

double nn_total_error(struct s_neural_network *self, double *targets, enum e_nn_error *error)
{
  *error = NN_SUCCESS;

  if (!self)
  {
    *error = NN_NO_NEURAL_NETWORK;
    return 0.;
  }

  if (!targets)
  {
    *error = NN_NO_VALUES;
    return 0.;
  }

  if (!self->nb_layer)
  {
    *error = NN_NO_LAYER;
    return 0.;
  }

  return la_get_sum_error(*(self->layers + self->nb_layer - 1), targets, error);
}

void nn_back_propagage(struct s_neural_network *self, enum e_nn_error *error)
{
  *error = NN_SUCCESS;

  if (!self)
  {
    *error = NN_NO_NEURAL_NETWORK;
    return;
  }

  // get the last layer pointer
  struct s_layer **layer = self->layers + self->nb_layer - 1;

  // loop between the last and the second layer
  for (; layer > self->layers && !*error; --layer)
    la_back_propagage(*layer, error);
}

void nn_get_outputs(struct s_neural_network *self, double *outputs, enum e_nn_error *error)
{
  *error = NN_SUCCESS;

  if (!self)
    *error = NN_NO_NEURAL_NETWORK;

  else if (!self->nb_layer)
    *error = NN_NO_LAYER;

  if (*error)
    return;

  la_get_outputs(*(self->layers + self->nb_layer - 1), outputs, error);
}

unsigned int nn_get_last_layer_size(struct s_neural_network *self, enum e_nn_error *error)
{

  *error = NN_SUCCESS;

  if (!self)
    *error = NN_NO_NEURAL_NETWORK;

  else if (!self->nb_layer)
    *error = NN_NO_LAYER;

  if (*error)
    return 0;

  return self->layers[self->nb_layer - 1]->size;
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

  /*   printf("////////////////////////////////////////////////////////////////////////////////\n");
  printf("//                                                                            //\n");
  printf("//                                    INPUT                                   //\n");
  printf("//                                                                            //\n");
  printf("////////////////////////////////////////////////////////////////////////////////\n"); */
  printf("\n=================================== INPUT ====================================\n");

  // check if it exist at less 1 layer
  if (self->nb_layer)
    la_print(*self->layers);

  /*   printf("\n\n\n");
  printf("////////////////////////////////////////////////////////////////////////////////\n");
  printf("//                                                                            //\n");
  printf("//                                   HIDDEN                                   //\n");
  printf("//                                                                            //\n");
  printf("////////////////////////////////////////////////////////////////////////////////\n"); */

  // loop beween the second layer and the penultimate
  for (unsigned int i = 2; i < self->nb_layer; ++i)
  {
    printf("\n=================================== HIDDEN %i ====================================\n", i - 1);
    la_print(*(self->layers + i - 1));
  }

  /*   printf("\n\n\n");
  printf("////////////////////////////////////////////////////////////////////////////////\n");
  printf("//                                                                            //\n");
  printf("//                                   OUTPUT                                   //\n");
  printf("//                                                                            //\n");
  printf("////////////////////////////////////////////////////////////////////////////////\n"); */

  printf("\n=================================== OUTPUT ====================================\n");

  // print the last layer if there is at less 1 layer
  if (self->nb_layer)
    la_print(*(self->layers + self->nb_layer - 1));
}