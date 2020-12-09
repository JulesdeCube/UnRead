/**
** \file src/neural_network/layer.c
** \author Jules Lefebvre <jules.lefebvre@epita.fr
** \version 1.0.0
** \date 2020/09/30
** \brief implemtation of the `s_layer` object
**
** containe every contructor, desturctor and method use in `s_layer` struct
** manipution
*/

#include "layer.h"

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                CONSTRUCTOR                                //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

struct s_layer *la_consructor(unsigned int size, struct s_layer *previous_layer, struct s_neural_network *neural_network, enum e_nn_error *error)
{
  // set the error to success
  *error = NN_SUCCESS;

  // create the layer
  struct s_layer *self = calloc(1, sizeof(struct s_layer));

  // if we didn't have enought free space trow error
  if (!self)
  {
    *error = NN_ERROR_SPACE;
    return self;
  }

  // init each value
  self->size = size;
  self->neurones = NULL;
  self->previous_layer = previous_layer;
  self->next_layer = NULL;

  // if no neural network given return an error
  if (!neural_network)
  {
    *error = NN_NO_NEURAL_NETWORK;
    la_destructor(self);
    return NULL;
  }

  self->neural_network = neural_network;

  // alocate the memory for each neurone struct
  self->neurones = calloc(size, sizeof(struct s_neurone));

  // if we can't alocate memory throw error and desotry it
  if (!self->neurones)
  {
    *error = NN_ERROR_SPACE;
    la_destructor(self);
    return NULL;
  }

  // for each nerone init it
  struct s_neurone *neurone = self->neurones;
  struct s_neurone *last_neurone = neurone + self->size;
  for (; neurone < last_neurone && !*error; ++neurone)
    *neurone = ne_consructor(self, error);

  // if there is a error during neurone initialisation remove previouslý created
  // neurone and desotry the layer
  if (*error)
  {
    // destroy layer
    for (; neurone >= self->neurones; --neurone)
      ne_destructor(neurone);
    free(self->neurones);
    // prevent destuctor to destruct neurones
    self->neurones = NULL;
    la_destructor(self);
    // get error
    return NULL;
  }

  // update previous layer
  if (self->previous_layer)
    self->previous_layer->next_layer = self;

  return self;
}

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                 DESTRUCTOR                                //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

void la_destructor(struct s_layer *self)
{
  // if already destroy remove do nothing
  if (!self)
    return;

  // if neurones are not destroy remove it
  if (self->neurones)
  {
    struct s_neurone *neurone = self->neurones;
    struct s_neurone *last_neurone = neurone + self->size;
    for (; neurone < last_neurone; ++neurone)
      ne_destructor(neurone);
    free(self->neurones);
  }

  // reclusive remove next layer (if not we can't have previous size)
  la_destructor(self->next_layer);
  self->previous_layer->next_layer = NULL;

  free(self);
}

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                 OPERATIONS                                //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

void la_set(struct s_layer *self, double *values, enum e_nn_error *error)
{
  if (!self)
  {
    *error = NN_NO_LAYER;
    return;
  }

  // init start and stop element
  struct s_neurone *neurone = self->neurones;
  struct s_neurone *last_neurone = neurone + self->size;

  // loop in each neurone and set his value
  for (; neurone < last_neurone; ++neurone, ++values)
    neurone->output = *values;

  *error = NN_SUCCESS;
}

void la_compute(struct s_layer *self, enum e_nn_error *error)
{
  *error = NN_SUCCESS;
  if (!self)
  {
    *error = NN_NO_LAYER;
    return;
  }

  // init start and stop element
  struct s_neurone *neurone = self->neurones;
  struct s_neurone *last_neurone = neurone + self->size;

  // propagate computation in every neurone
  for (; neurone < last_neurone && !*error; ++neurone)
    ne_compute(neurone, error);
}

void la_write(struct s_layer *self, FILE *fp, enum e_nn_error *error)
{
  *error = NN_SUCCESS;

  if (!self)
  {
    *error = NN_NO_LAYER;
    return;
  }

  // write the number of neurone
  fwrite(&self->size, sizeof(self->size), 1u, fp);

  // init start and stop element
  struct s_neurone *neurone = self->neurones;
  struct s_neurone *last_neurone = neurone + self->size;

  // write neurones's informations
  for (; neurone < last_neurone && !*error; ++neurone)
    ne_write(neurone, fp, error);
}

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                   VIEWER                                  //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

void la_print(struct s_layer *self)
{
  // if it not exist exit and print a message
  if (!self)
  {
    printf("ERROR: `la_print` : no layer\n");
    return;
  }

  // loop to each neurone by id
  for (unsigned int i = 0; i < self->size; ++i)
  {
    // print neurone separator
    printf("\n                       ---------- neurone %d ----------                       \n", i);
    // print the neurone
    ne_print(self->neurones + i);
  }
}
