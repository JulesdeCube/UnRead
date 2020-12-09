/**
** \file src/neural_network/neurone.c
** \author Jules Lefebvre <jules.lefebvre@epita.fr
** \version 1.0.0
** \date 2020/09/30
** \brief implemtation of the `s_neurone` object
**
** containe every contructor, desturctor and method use in `s_neurone` struct
** manipution
*/

#include "neurone.h"

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                                 CONSTRUCTOR                                //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

struct s_neurone ne_consructor(struct s_layer *parrent, enum e_nn_error *error)
{
  // set the error to success
  *error = NN_SUCCESS;

  // init the sum and output to null a bias between -1 and 1 and the layer but no weight
  struct s_neurone self = {0., 0., random_uniforme(-1.0, 1.0), NULL, parrent};

  // if no layer given return an error
  if (!parrent)
  {
    *error = NN_NO_PARRENT_LAYER;
    return self;
  }

  // get the number of neurone in the previous layer
  unsigned int nb_neurone_previous_layer = 0;
  if (self.layer->previous_layer != NULL)
    nb_neurone_previous_layer = self.layer->previous_layer->size;

  // alocate space for every weight
  self.weights = calloc(nb_neurone_previous_layer, sizeof(double));

  // if we can't alocate the memory return an error
  if (self.weights == NULL)
  {
    *error = NN_ERROR_SPACE;
    return self;
  }

  // init each weight one by one with a value between -1 and 1
  double *weight = self.weights;
  double *last_weight = weight + nb_neurone_previous_layer;
  for (; weight < last_weight; ++weight)
    *weight = random_uniforme(-1.0, 1.0);

  return self;
}

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                                 DESTRUCTOR                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

void ne_destructor(struct s_neurone *self)
{
  // if no layer remove it
  if (self == NULL)
    return;

  // remove layer
  self->layer = NULL;

  // if there is no biases return
  if (self->weights == NULL)
    return;

  // remove biases
  free(self->weights);
  self->weights = NULL;
}

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                                  METHODE                                   //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

void ne_compute(struct s_neurone *self, enum e_nn_error *error)
{
  *error = NN_SUCCESS;

  // if no neurone provided return an error
  if (!self)
  {
    *error = NN_NO_NEURONE;
    return;
  }

  //  if there is no layer in linked with the neurone return an error;
  if (!self->layer)
  {
    *error = NN_NO_PARRENT_LAYER;
    return;
  }

  //  if there is no layer in linked with the neurone return an error;
  if (!self->layer->neural_network)
  {
    *error = NN_NO_PARRENT_NEURAL_NETWORK;
    return;
  }

  // quite if there is no previous_layer (nothing to do)
  if (!self->layer->previous_layer)
    return;

  // the previous layer
  struct s_layer *previous_layer = self->layer->previous_layer;

  // add the bias of the neurone
  self->sum = self->bias;

  // init the begin and the end of the array
  double *weight = self->weights;
  double *last_weight = weight + previous_layer->size;
  struct s_neurone *neurone_previous_layer = previous_layer->neurones;

  // make the sum of previous neurone multiply by they weight
  for (; weight < last_weight; ++neurone_previous_layer, ++weight)
    self->sum += *weight * neurone_previous_layer->output;

  // path the value of the neurone to the activation function
  self->output = self->layer->neural_network->activation_func.self(self->sum);
}

void ne_write(struct s_neurone *self, FILE *fp, enum e_nn_error *error)
{
  // set to be a success
  *error = NN_SUCCESS;

  // if no neurone provided return an error
  if (!self)
  {
    *error = NN_NO_NEURONE;
    return;
  }

  // check if the file is open
  if (!fp)
  {
    *error = NN_PERMISSION_DENIED;
    return;
  }

  //  if there is no layer in linked with the neurone return an error;
  if (!self->layer)
  {
    *error = NN_NO_PARRENT_LAYER;
    return;
  }

  // if there is no a previous layer just quite (no need to add this informations)
  if (!self->layer->previous_layer)
    return;

  // write the bias
  fwrite(&self->bias, sizeof(self->bias), 1u, fp);

  // the previous layer
  struct s_layer *previous_layer = self->layer->previous_layer;

  // init the begin and the end of the array
  double *weight = self->weights;
  double *last_weight = weight + previous_layer->size;

  // make the sum of previous neurone multiply by they weight
  for (; weight < last_weight; ++weight)
    fwrite(weight, sizeof(*weight), 1u, fp);
}

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                                   VIEWER                                   //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

void ne_print(struct s_neurone *self)
{

  // if there is no layer in the struct return an error
  if (!self->layer)
  {
    printf("ERROR: `ne_print` : no neurone\n");
    return;
  }

  // print the output of the neurone
  printf("output : %lf, sum : %lf\n", self->output, self->sum);

  // if there is no previous layer just print the value
  struct s_layer *previous_layer = self->layer->previous_layer;
  if (!previous_layer)
    return;

  // print the bias
  printf("bias : %lf\n", self->bias);

  // print the weight
  printf("weight : ");
  // if there is more than 1 neurone in the previous layer print the fist
  // element
  if (previous_layer->size)
    printf("[0]%lf", *self->weights);

  // for all weight exept the fist one print the separator and the value
  for (unsigned int i = 1; i < previous_layer->size; ++i)
    printf(", [%u]%lf", i, self->weights[i]);
  // return a line at the end of the list of weight
  printf("\n");
}
