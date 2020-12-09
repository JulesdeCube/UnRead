/**
** \file src/neural_network/neurone.h
** \author Jules Lefebvre <jules.lefebvre@epita.fr
** \version 1.0.0
** \date 2020/10/04
** \brief declaraton of the `neurone` object.
**
** definition of constuctor, destructor and method of the `neurone` object.
*/

#ifndef UNREAD__SRC_NEURAL_NETWORK__NEURONE_H_
#define UNREAD__SRC_NEURAL_NETWORK__NEURONE_H_

#include <stdlib.h>

/**
** \struct s_neurone
** \brief a neurone for neural network
*/
struct s_neurone
{
  double sum;
  double output;
  double bias;
  double *weights;
  struct s_layer *layer;
};

#include <stdio.h>
#include "layer.h"
#include "utils.h"
#include "neural_network_error.h"

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                CONSTRUCTOR                                //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

/**
** \brief `s_neurone` constuctor.
**
** create a neurone for neural network
**
** \param layer the parrent layer
** \param error the return error channel
**
** \return a new instance of `s_neurone`
**
** \throw NN_NO_PARRENT_LAYER no parrent layer provided to the neurone
** \throw NN_ERROR_SPACE there is not enought free space to store the neurone
**        it's self or his weight
*/
struct s_neurone ne_consructor(struct s_layer *layer, enum e_nn_error *error);

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                 DESTRUCTOR                                //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

/**
** \brief `s_neural_network` destructor.
**
**  free space and propely destruct the neural network
**
** \param self a pointer to the neural network to destroy
*/
void ne_destructor(struct s_neurone *neurone);

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                  METHODE                                  //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

/**
** \brief update the value of the neurone
**
** make the sum of the previous layer weighted and pass all the sum into the
** activation function
**
** \param self the neurone to update
** \param error the return error channel
**
** \throw NN_NO_NEURONE no neurone provided
** \throw NN_NO_PARRENT_LAYER no parrent layer in the neurone
** \throw NN_NO_PARRENT_NEURAL_NETWORK no parrented neural network in the parent
**        of th neurone
*/
void ne_compute(struct s_neurone *self, enum e_nn_error *error);

/**
** \brief write the content of a neurone
**
** write the weight and the biais of a the neurone
**
** \param self the neuone to save
** \param fp file
** \param error the return error channel
**
** \throw NN_NO_NEURONE no neurone provided
** \throw NN_NO_PARRENT_LAYER no parrent layer in the neurone
*/
void ne_write(struct s_neurone *self, FILE *fp, enum e_nn_error *error);

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                   VIEWER                                  //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

/**
** \brief diplay the neurone information
**
** \param self the neurone to print
*/
void ne_print(struct s_neurone *self);

#endif // UNREAD__SRC_NEURAL_NETWORK__NEURONE_H_