#ifndef UNREAD__SRC_NEURAL_NETWORK__NEURAL_NETWORK_ERROR_H_
#define UNREAD__SRC_NEURAL_NETWORK__NEURAL_NETWORK_ERROR_H_

/**
** \enum e_nn_error
** \brief error code for neural network
**
** error code and succes for all the constructor and methode of the neural
** network and it's sub class
*/
enum e_nn_error
{
  /**
  ** succes creation of a `s_neurone_network`
  */
  NN_SUCCESS = 0,
  /**
  ** no neural network provided
  */
  NN_NO_NEURAL_NETWORK,
  /**
  ** not enought free space evalable
  */
  NN_ERROR_SPACE,
  /**
  ** no neurone provided
  */
  NN_NO_NEURONE,
  /**
  ** no layer provided to the neurone
  */
  NN_NO_LAYER,
  /**
  ** no function provided
  */
  NN_NO_FUNCTION,
  /**
  ** the given neurone has no parrented layer
  */
  NN_NO_PARRENT_LAYER,
  /**
  ** the given layer has no parrented neural network
  */
  NN_NO_PARRENT_NEURAL_NETWORK,
  /**
  ** file permission eception
  */
  NN_PERMISSION_DENIED
};

#endif // UNREAD__SRC_NEURAL_NETWORK__NEURAL_NETWORK_ERROR_H_