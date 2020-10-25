#include <stdio.h>
#include "neural_network/neural_network.h"
#include "neural_network/utils.h"

int main(void)
{
  srand(time(NULL));

  printf("UnRead 0.1.0\n");

  enum nn_error error;
  unsigned int layers_size[4] = {2, 3, 3, 3};
  struct s_function_1p activation_func = {&sigmoid, &sigmoid_derivate};
  struct s_function_2p error_func = {&sq_difference, &sq_difference_derivate};
  struct s_neural_network *nn = nn_consructor(4u, layers_size, activation_func, error_func, &error);
  if (error != NN_SUCCESS)
  {
    printf("error durring initialisation of neural network : %u\n", error);
    return error;
  }

  nn_print(nn);

  printf("\n\n\n\n\n\n\n\napply input\n\n\n\n\n\n\n\n");
  double input[2] = {1., 0.};
  nn_apply(nn, input);
  nn_print(nn);

  double output[3] = {1., 0., 0.5};
  nn_back_propagate(nn, output);

  nn_destructor(nn);
  return 0;
}
