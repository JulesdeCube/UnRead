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

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                                 CONSTRUCTOR                                //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

struct s_layer *la_consructor(unsigned int size, struct s_layer *previous_layer, struct s_neural_network *neural_network, enum e_nn_error *error)
{
  // set the error to success
  *error = NN_SUCCESS;

  // if no neural network given return an error
  if (!neural_network)
  {
    *error = NN_NO_NEURAL_NETWORK;
    return NULL;
  }

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
  self->neural_network = neural_network;
  self->previous_layer = previous_layer;
  self->next_layer = NULL;

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

  // if there is a error during neurone initialisation return the error and
  // destroy the layer
  if (*error)
  {
    la_destructor(self);
    return NULL;
  }

  // update previous layer
  if (self->previous_layer)
    self->previous_layer->next_layer = self;

  return self;
}

struct s_layer *la_file_consructor(FILE *fp, struct s_layer *previous_layer, struct s_neural_network *neural_network, enum e_nn_error *error)
{
  // set the error to success
  *error = NN_SUCCESS;

  // check if there is a file
  if (!fp)
  {
    *error = NN_PERMISSION_DENIED;
    return NULL;
  }

  // if no neural network given return an error
  if (!neural_network)
  {
    *error = NN_NO_NEURAL_NETWORK;
    return NULL;
  }

  // create the layer
  struct s_layer *self = calloc(1, sizeof(struct s_layer));

  // if we didn't have enought free space trow error
  if (!self)
  {
    *error = NN_ERROR_SPACE;
    return self;
  }

  // FIXME - check for end of file
  // init each value
  fread(&self->size, sizeof(self->size), 1, fp);
  self->neurones = NULL;
  self->previous_layer = previous_layer;
  self->next_layer = NULL;
  self->neural_network = neural_network;

  // alocate the memory for each neurone struct
  self->neurones = calloc(self->size, sizeof(struct s_neurone));

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
    *neurone = ne_file_consructor(fp, self, error);

  // if there is a error during neurone initialisation return the error and
  // destroy the layer
  if (*error)
  {
    la_destructor(self);
    return NULL;
  }

  // update previous layer
  if (self->previous_layer)
    self->previous_layer->next_layer = self;

  return self;
}

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                                 DESTRUCTOR                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

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

  // remove pointer to this instance of layer to avoid segmentation fault
  if (self->next_layer)
    self->next_layer->previous_layer = NULL;
  if (self->previous_layer)
    self->previous_layer->next_layer = NULL;

  free(self);
}

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                                  METHODE                                   //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

void la_set_values(struct s_layer *self, double *values, enum e_nn_error *error)
{
  // set the error to success
  *error = NN_SUCCESS;

  if (!values)
  {
    *error = NN_NO_VALUES;
    return;
  }

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

  // check if the neurone exist
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

  // check if it provide a layer
  if (!self)
  {
    *error = NN_NO_LAYER;
    return;
  }

  // check if the file is open
  if (!fp)
  {
    *error = NN_PERMISSION_DENIED;
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

double la_get_sum_error(struct s_layer *self, double *targets, enum e_nn_error *error)
{
  *error = NN_SUCCESS;

  if (!self)
  {
    *error = NN_NO_LAYER;
    return 0.;
  }

  if (!targets)
  {
    *error = NN_NO_VALUES;
    return 0.;
  }

  double total = 0;

  // init start and stop element
  struct s_neurone *neurone = self->neurones;
  struct s_neurone *last_neurone = neurone + self->size;

  for (; neurone < last_neurone && !*error; ++neurone, ++targets)
    total += ne_get_error(neurone, *targets, error);

  return total;
}

void la_get_outputs(struct s_layer *self, double *outputs, enum e_nn_error *error)
{
  *error = NN_SUCCESS;

  if (!self)
  {
    *error = NN_NO_LAYER;
    return;
  }

  if (!outputs)
  {
    *error = NN_NO_VALUES;
    return;
  }

  // init start and stop element
  struct s_neurone *neurone = self->neurones;
  struct s_neurone *last_neurone = neurone + self->size;

  for (; neurone < last_neurone && !*error; ++neurone, ++outputs)
    *outputs = ne_get_output(neurone, error);
}

void la_foreach_neurone(struct s_layer *self, void (*f)(struct s_neurone *, enum e_nn_error *error), enum e_nn_error *error)
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

  // loop to each neurone to backpropagate
  for (; neurone < last_neurone && !*error; ++neurone)
    f(neurone, error);
}

void la_back_propagage(struct s_layer *self, enum e_nn_error *error)
{
  *error = NN_SUCCESS;

  if (!self)
  {
    *error = NN_NO_LAYER;
    return;
  }

  // resert the gradiant layer
  if (self->previous_layer)
    la_reset_error(self->previous_layer, error);
  // make propagate
  if (!*error)
    la_foreach_neurone(self, ne_back_propagage, error);
}

void la_reset_error(struct s_layer *self, enum e_nn_error *error)
{

  *error = NN_SUCCESS;

  if (!self)
  {
    *error = NN_NO_LAYER;
    return;
  }

  la_foreach_neurone(self, ne_reset_error, error);
}

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                                   VIEWER                                   //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

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
    printf("Neurone %d :: ", i);
    // print the neurone
    ne_print(self->neurones + i);
  }
}
