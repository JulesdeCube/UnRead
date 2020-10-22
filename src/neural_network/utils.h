/**
** \file src/neural_network/utils.h
** \author Jules Lefebvre <jules.lefebvre@epita.fr
** \version 1.0.0
** \date 2020/10/04
** \brief declaraton of utils function for the neural network
**
** random and activation fonction for the neural network
*/

#ifndef UNREAD__SRC_NEURAL_NETWORK__UTILS_H_
#define UNREAD__SRC_NEURAL_NETWORK__UTLIS_H_

#include <time.h>
#include <stdlib.h>

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                  RANDOM                                  //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

/**
** \brief loi uniforme
**
**  génère une variable aléatoire uniforme entre `min` et `max`
**
** \param min the minimal value that can take the return value
** \param max the maximal value that can take the return value
*/
double random_uniforme(double min, double max);

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                             ACTIVATION FUNCTION                           //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // UNREAD__SRC_NEURAL_NETWORK__UTILS_H_