#include <stdio.h>
#include "neural_network/neural_network.h"
#include "neural_network/utils.h"
#include "image/set.h"

#define nb_layers 4
#define nb_test 10000

double *cahrs_to_doubles(size_t count, unsigned char *values)
{
  double *array = malloc(count * sizeof(double));
  for (size_t i = 0; i < count; i++)
    array[i] = (double)values[i] / 255.;

  return array;
}

void set_at_place(double *values, unsigned int to_set)
{
  printf("[ ");
  for (size_t i = 0; i < 10; i++)
  {
    values[i] = i == to_set;
    printf("%f ", values[i]);
  }
  printf("]\n");
}

void print_array(double *values)
{
  printf("[ ");
  for (size_t i = 0; i < 10; i++)
  {
    printf("%f ", values[i]);
  }
  printf("]\n");
}

int main(void)
{
  srand(time(NULL));

  char *path = "test/neural_network/net1.hex";
  double targets[10] = {0.};
  double outputs[10] = {0.};

  enum e_nn_error nn_error;
  enum sp_error sp_error;

  struct s_set set = st_import(
      "test/dataset/train-images-idx3-ubyte",
      "test/dataset/train-labels-idx1-ubyte",
      &sp_error);

  // st_print(&set);

  unsigned int width = set.samples->image.width;
  unsigned int height = set.samples->image.height;
  unsigned int layers_size[nb_layers] = {width * height, 20, 20, 10};

  struct s_neural_network *nn = nn_consructor(
      nb_layers,
      layers_size,
      (struct s_function_1p){&sigmoid, &sigmoid_derivate},
      (struct s_function_2p){&sq_difference, &sq_difference_derivate},
      &nn_error);

  if (nn_error)
  {
    printf("error durring initialisation of neural network : %u\n", nn_error);
    return nn_error;
  }

  int j = 0;
  double total_error;

  do
  {
    printf("\033[s");
    size_t id = j % 100;
    struct s_sample *sample = (set.samples + id);
    double *input = cahrs_to_doubles(mk_count(&sample->image), sample->image.pixels);
    set_at_place(targets, sample->label);

    // printf("sample %li:\n", sample);
    if (!nn_error)
      nn_apply(nn, input, &nn_error);

    if (!nn_error)
      total_error = nn_total_error(nn, targets, &nn_error);

    if (!nn_error)
      nn_back_propagage(nn, &nn_error);

    nn_get_outputs(nn, outputs, &nn_error);
    print_array(outputs);
    //nn_print(nn);
    printf("STEPS: %i\n", j);
    printf("\nERROR: %f", total_error);
    printf("\033[u");

    free(input);
    j++;
  } while (!nn_error && j < nb_test);

  if (nn_error)
  {
    printf("error durring training : %u\n", nn_error);
    return nn_error;
  }

  nn_save(nn, path, &nn_error);

  if (nn_error)
  {
    printf("error durring export of the network : %u\n", nn_error);
    return nn_error;
  }

  getchar();

  nn_destructor(nn);
  st_destructor(&set);

  return 0;
}
