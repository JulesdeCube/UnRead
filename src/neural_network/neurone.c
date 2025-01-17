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
  struct s_neurone self = {0., 0., random_uniforme(-1.0, 1.0), NULL, 0., parrent};

  // if no layer given return an error
  if (!parrent)
  {
    *error = NN_NO_PARRENT_LAYER;
    return self;
  }

  // get the number of neurone in the previous layer
  unsigned int nb_neurone_previous_layer = 0;
  if (self.layer->previous_layer)
    nb_neurone_previous_layer = self.layer->previous_layer->size;

  // alocate space for every weight
  self.weights = calloc(nb_neurone_previous_layer, sizeof(double));

  // if we can't alocate the memory return an error
  if (!self.weights)
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

struct s_neurone ne_file_consructor(FILE *fp, struct s_layer *parrent, enum e_nn_error *error)
{

  // set the error to success
  *error = NN_SUCCESS;

  // init the sum and output to null a bias between -1 and 1 and the layer but no weight
  struct s_neurone self = {0., 0., 0, NULL, 0., parrent};

  // check if there is a file
  if (!fp)
  {
    *error = NN_PERMISSION_DENIED;
    return self;
  }

  // check parrent is provided
  if (!parrent)
  {
    *error = NN_NO_PARRENT_LAYER;
    return self;
  }

  // if there is a previous layer get the bias
  if (self.layer->previous_layer)
    // FIXME - check for end of file
    fread(&self.bias, sizeof(self.bias), 1, fp);

  // if no layer given return an error
  if (!parrent)
  {
    *error = NN_NO_PARRENT_LAYER;
    return self;
  }

  // get the number of neurone in the previous layer
  unsigned int nb_neurone_previous_layer = 0;
  if (self.layer->previous_layer)
    nb_neurone_previous_layer = self.layer->previous_layer->size;

  // alocate space for every weight
  self.weights = calloc(nb_neurone_previous_layer, sizeof(double));

  // if we can't alocate the memory return an error
  if (!self.weights)
  {
    *error = NN_ERROR_SPACE;
    return self;
  }

  // init each weight one by one with a value between -1 and 1
  double *weight = self.weights;
  double *last_weight = weight + nb_neurone_previous_layer;
  // FIXME - check for end of file
  for (; weight < last_weight; ++weight)
    fread(weight, sizeof(*weight), 1, fp);

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
  if (!self)
    return;

  // remove layer
  self->layer = NULL;

  // if there is weight remove it
  if (self->weights)
  {
    // remove weight
    free(self->weights);
    self->weights = NULL;
  }
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

double ne_get_error(struct s_neurone *self, double target, enum e_nn_error *error)
{
  *error = NN_SUCCESS;

  if (!self)
    *error = NN_NO_NEURONE;
  else if (!self->layer)
    *error = NN_NO_PARRENT_LAYER;
  else if (!self->layer->neural_network)
    *error = NN_NO_PARRENT_NEURAL_NETWORK;
  else if (!self->layer->neural_network->error_func.self)
    *error = NN_NO_FUNCTION;
  else if (!self->layer->neural_network->error_func.derivate)
    *error = NN_NO_FUNCTION;

  if (*error)
    return 0.;

  self->derivate_error = self->layer->neural_network->error_func.derivate(target, self->output);

  return self->layer->neural_network->error_func.self(target, self->output);
}

double ne_get_output(struct s_neurone *self, enum e_nn_error *error)
{
  *error = NN_SUCCESS;

  if (!self)
  {
    *error = NN_NO_NEURONE;
    return 0.;
  }

  return self->output;
}

void ne_back_propagage(struct s_neurone *self, enum e_nn_error *error)
{
  *error = NN_SUCCESS;

  if (!self)
    *error = NN_NO_NEURONE;
  else if (!self->layer)
    *error = NN_NO_PARRENT_LAYER;
  else if (!self->layer->previous_layer)
    *error = NN_NO_PARRENT_LAYER;

  if (*error)
    return;

  struct s_layer *previous_layer = self->layer->previous_layer;
  struct s_neural_network *neural_network = self->layer->neural_network;
  double (*activation_derivate)(double) = neural_network->activation_func.derivate;

  // init start and stop element
  struct s_neurone *previous_neurone = previous_layer->neurones;
  struct s_neurone *last_previous_neurone = previous_layer->neurones + previous_layer->size;

  double *weight = self->weights;

  // FIXME - introduce learning rate
  double partial_deriavate = self->derivate_error * activation_derivate(self->output) * 0.5;

  // loop in each neurone and set his value
  for (; previous_neurone < last_previous_neurone; ++previous_neurone, ++weight)
  {

    double delta_weight = partial_deriavate * previous_neurone->output;
    previous_neurone->derivate_error += delta_weight;
    *weight -= delta_weight;
  }
  self->bias -= partial_deriavate;
}

void ne_reset_error(struct s_neurone *self, enum e_nn_error *error)
{
  if (!self)
  {
    *error = NN_NO_NEURONE;
    return;
  }

  self->derivate_error = 0;
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
  printf("out: %lf, b: %lf, err : %lf, w:", self->output, self->bias, self->derivate_error);

  // if there is no previous layer just print the value
  struct s_layer *previous_layer = self->layer->previous_layer;
  if (previous_layer)
  {

    // print the bias
    //printf("bias : %lf\n", self->bias);

    // print the weight
    //printf("weight : ");
    // if there is more than 1 neurone in the previous layer print the fist
    // element
    if (previous_layer->size)
      printf("[ %lf", *self->weights);

    // for all weight exept the fist one print the separator and the value
    for (unsigned int i = 1; i < previous_layer->size; ++i)
      printf(", %lf", self->weights[i]);
    // return a line at the end of the list of weight
    printf(" ]");
  }
  printf("\n");
}
