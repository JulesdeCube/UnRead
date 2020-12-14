/**
** \file src/neural_network/neurone.c
** \author Jules Lefebvre <jules.lefebvre@epita.fr
** \version 1.0.0
** \date 2020/09/30
** \brief declaraton of utils function for the neural network
**
** random and activation fonction for the neural netw ork
*/

#include "utils.h"

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                  RANDOM                                  //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

double random_uniforme(double min, double max)
{
  return (double)rand() / RAND_MAX * (max - min) + min;
}

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                               ERROR FUNCTION                              //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

double sq_difference(double target, double output)
{
  output -= target;
  return output * output;
}

double sq_difference_derivate(double target, double output)
{
  return 2. * (output - target);
}

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                             ACTIVATION FUNCTION                           //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

double sigmoid(double x)
{
  return 1.0 / (1.0 + exp(-x));
}

double sigmoid_derivate(double x)
{
  return x * (1 - x);
}