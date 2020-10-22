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
#include <math.h>
///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                  RANDOM                                  //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

/**
** \brief uniforme law
**
**  génerate a random number folowing a uniforme rule between `min` and `max`
**
** \param min the minimal value that can take the return value
** \param max the maximal value that can take the return value
**
** \return and random value between min and max
*/
double random_uniforme(double min, double max);

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                             ACTIVATION FUNCTION                           //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

/**
** \brief sigmoind
**
** $$
** \frac{1}{1+e^{-x}}
** $$
**
** \param x the input of the function
**
** \return the image of x by the sigmoid
*/
double sigmoid(double x);

/**
** \brief sigmoind derivate in fonction of the sigmoid it self
**
** $$
** \sigma' = \sigma (1 - \sigma)
** $$
**
** \param x the value of the sigmoid
**
** \return the derivate of the sigmoid
*/
double sigmoid_derivate(double x);

#endif // UNREAD__SRC_NEURAL_NETWORK__UTILS_H_