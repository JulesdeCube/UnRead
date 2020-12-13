#include <stdio.h>
#include "neural_network/neural_network.h"
#include "neural_network/utils.h"

void print_array(size_t size, double *values, char *preffix)
{
  printf("%s : [", preffix);
  for (size_t i = 0; i < size; i++)
    printf("%f, ", values[i]);
  printf("]\n");
}

int main(void)
{
  srand(time(NULL));

  printf("UnRead 0.1.0\n");

  char *path = "test/neural_network/net1.hex";

  enum e_nn_error error;
  struct s_function_1p activation_func = {&sigmoid, &sigmoid_derivate};
  struct s_function_2p error_func = {&sq_difference, &sq_difference_derivate};

  // struct s_neural_network *nn = nn_from_file(path, activation_func, error_func, &error);

  unsigned int layers_size[3u] = {2, 4, 1};
  struct s_neural_network *nn = nn_consructor(3, layers_size, activation_func, error_func, &error);

  if (error)
  {
    printf("error durring initialisation of neural network : %u\n", error);
    return error;
  }

  nn_print(nn);

  printf("\n\n\n\n\n\n\n\nTRAINNING\n\n\n\n\n\n\n\n");
  double inputs[8] = {0., 0., 0., 1., 1., 0., 1., 1.};
  double targets[4] = {0., 1., 1., 0.};
  double output[2];

  double total_error;
  //do
  //{
  total_error = 0.;
  for (size_t i = 0; i < 8 && !error; i++)
  {
    size_t sample = rand() % 4;
    double *input = inputs + sample * 2;
    double *target = targets + sample;

    printf("sample %li:\n", sample);

    nn_apply(nn, input, &error);
    if (error)
    {
      printf("can't apply value for %lu sample\n", sample);
      break;
    }

    double layer_error = nn_total_error(nn, targets + sample, &error);
    if (error)
    {
      printf("can't calcule error for %lu sample\n", sample);
      break;
    }
    nn_back_propagage(nn, targets, &error);
    if (error)
      printf("can't back propagate %lu sample\n", sample);

    nn_get_outputs(nn, output, &error);

    print_array(2, input, "inputs");
    print_array(1, target, "targets");
    print_array(1, output, "output");

    printf("error: %f\n\n", layer_error);

    total_error += layer_error;
  }

  printf("ERROR : %f\n================\n\n", total_error);

  //} while (!error && total_error > 0.1);

  if (error)
  {
    printf("error durring training : %u\n", error);
    return error;
  }

  nn_save(nn, path, &error);

  if (error)
  {
    printf("error durring export of the network : %u\n", error);
    return error;
  }

  nn_destructor(nn);

  return 0;
}
