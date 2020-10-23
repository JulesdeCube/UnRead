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

struct s_layer *la_consructor(unsigned int size, struct s_layer *previous_layer, struct s_neural_network *neural_network, enum la_error *error)
{
  // create the layer
  struct s_layer *self = calloc(1, sizeof(struct s_layer));

  // if we didn't have enought free space trow error
  if (self == NULL)
  {
    *error = LA_ERROR_SPACE;
    return self;
  }

  // init each value
  self->size = size;
  self->neurones = NULL;
  self->previous_layer = previous_layer;
  self->next_layer = NULL;

  // if no neural network given return an error
  if (neural_network == NULL)
  {
    *error = LA_NO_NEURAL_NETWORK;
    la_destructor(self);
    return NULL;
  }

  // alocate the memory for each neurone struct
  self->neurones = calloc(size, sizeof(struct s_neurone));

  // if we can't alocate memory throw error and desotry it
  if (self->neurones == NULL)
  {
    *error = LA_ERROR_SPACE;
    la_destructor(self);
    return NULL;
  }

  // for each nerone init it
  struct s_neurone *neurone = self->neurones;
  struct s_neurone *last_neurone = neurone + self->size;
  enum ne_error neurone_error = NE_SUCCESS;
  for (; neurone < last_neurone && neurone_error == NE_SUCCESS; ++neurone)
    *neurone = ne_consructor(self, &neurone_error);

  // if there is a error during neurone initialisation remove previouslý created
  // neurone and desotry the layer
  if (neurone_error != NE_SUCCESS)
  {
    // destroy layer
    for (; neurone >= self->neurones; --neurone)
      ne_destructor(neurone);
    free(self->neurones);
    // prevent destuctor to destruct neurones
    self->neurones = NULL;
    la_destructor(self);
    // get error
    *error = ne_to_la_error(*error);
    return NULL;
  }
  // set the error to success
  *error = LA_SUCCESS;
  // update previous layer
  if (self->previous_layer != NULL)
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
  if (self == NULL)
    return;

  // if neurones are not destroy remove it
  if (self->neurones != NULL)
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

enum la_error ne_to_la_error(enum ne_error error)
{
  switch (error)
  {
  case NE_SUCCESS:
    return LA_SUCCESS;

  case NE_ERROR_SPACE:
    return LA_ERROR_SPACE;

  case NE_NO_LAYER:
    return LA_NO_LAYER;

  default:
    printf("ERROR: `ne_to_la_error`: unkown error : %d", error);
    return (enum la_error) - 1;
  }
}

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                   VIEWER                                  //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
void la_print(struct s_layer *self)
{
  for (unsigned int i = 0; i < self->size; ++i)
  {
    printf("\n                       ---------- neurone %d ----------                       \n", i);
    ne_print(self->neurones + i);
  }
}
