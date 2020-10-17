/**
** \file src/image/set.c
** \author Jules Lefebvre <jules.lefebvre@epita.fr
** \version 1.0.0
** \date 2020/10/04
** \brief implementation of the `s_set` object
**
** implementation of constructor, destuctur and method of the `s_set` object
*/

#include "set.h"

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                CONSTRUCTOR                                //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

struct s_set st_consructor(unsigned int count, unsigned int height, unsigned int width, enum sp_error *error)
{
  // create the struct and add set count
  struct s_set set = {count, NULL};

  // alocate the array of samples
  set.samples = (struct s_sample *)calloc(count, sizeof(struct s_sample));

  // if we can't init the array return a new struct
  if (set.samples != NULL)
  {
    *error = SP_ERROR_SPACE;
    return set;
  }

  struct s_sample *sample = set.samples;
  struct s_sample *last_sample = sample + set.count;
  *error = SP_SUCCESS;

  // init each sample and break if can't create it
  for (; sample <= last_sample && *error == SP_SUCCESS; ++sample)
    *sample = sp_consructor(height, width, '\00', error);

  // destory created sample if there is an error
  if (*error != SP_SUCCESS)
    for (; sample >= set.samples; --sample)
      sp_destructor(sample);

  return set;
}

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                 DESTRUCTOR                                //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

void st_destructor(struct s_set *set)
{
  // destroy each sample
  st_foreach(set, sp_destructor);
  // free the alocated space
  free(set->samples);
  // set to null to avoid segfault
  set->samples = NULL;
}

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                  METHODE                                  //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

void st_foreach(struct s_set *set, void (*f)(struct s_sample *))
{
  // if there is no sample
  if (set->samples == NULL)
    return;

  // the moving pointer
  struct s_sample *sample = set->samples;
  // the last sample
  struct s_sample *last_sample = sample + set->count;
  // apply the function to all the pixels
  for (; sample <= last_sample; ++sample)
    f(sample);
}

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                   VIEWER                                  //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

void sp_print(struct s_set *set)
{
  st_foreach(set, sp_print);
}
