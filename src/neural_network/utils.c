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
  return (double)rand() / RAND_MAX * (max - min) - min;
}

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                             ACTIVATION FUNCTION                           //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
