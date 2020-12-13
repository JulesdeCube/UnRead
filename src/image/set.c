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

struct s_set st_fconsructor(unsigned int count, unsigned int height, unsigned int width, FILE *fp_images, FILE *fp_label, enum sp_error *error)
{
  struct s_set set = st_consructor(count, height, width, error);

  struct s_sample *sample = set.samples;
  struct s_sample *last_sample = sample + set.count;
  *error = SP_SUCCESS;

  // if can't create the set return error
  if (*error != SP_SUCCESS)
    return set;

  // init each sample and break if can't create it
  for (; sample < last_sample && *error == SP_SUCCESS; ++sample)
    *sample = sp_fconsructor(height, width, fp_images, fp_label, error);

  // destory created sample if there is an error
  if (*error != SP_SUCCESS)
    for (; sample >= set.samples; --sample)
      sp_destructor(sample);

  return set;
}

struct s_set st_import(char *image_dataset_path, char *labels_dataset_path, enum sp_error *error)
{
  struct s_set self = (struct s_set){0, NULL};

  FILE *fp_images = fopen(image_dataset_path, "rb");
  if (!fp_images)
  {
    *error = SP_ERROR_NO_IMAGES_FILE;
    return self;
  }

  FILE *fp_labels = fopen(labels_dataset_path, "rb");
  if (!fp_images)
  {
    *error = SP_ERROR_NO_SAMPLES_FILE;
    return self;
  }

  self = st_from_file(fp_images, fp_labels, error);

  fclose(fp_images);
  fclose(fp_labels);

  return self;
}

struct s_set st_from_file(FILE *fp_images, FILE *fp_labels, enum sp_error *error)
{

  *error = SP_SUCCESS;

  if (!fp_images)
    *error = SP_ERROR_NO_SAMPLES_FILE;

  if (!fp_images)
    *error = SP_ERROR_NO_SAMPLES_FILE;

  unsigned int code_images = fgetu(fp_images, error, SP_ERROR_EOF_IMAGE);
  unsigned int code_labels = fgetu(fp_labels, error, SP_ERROR_EOF_LABEL);
  unsigned int nb_images = fgetu(fp_images, error, SP_ERROR_EOF_IMAGE);
  unsigned int nb_labels = fgetu(fp_labels, error, SP_ERROR_EOF_LABEL);
  unsigned int height = fgetu(fp_images, error, SP_ERROR_EOF_IMAGE);
  unsigned int width = fgetu(fp_images, error, SP_ERROR_EOF_IMAGE);

  if (code_images != 0x00000803)
    *error = SP_ERROR_WONG_FILECODE_IMAGE;

  if (code_labels != 0x00000801)
    *error = SP_ERROR_WONG_FILECODE_LABEL;

  if (nb_images != nb_labels)
    *error = SP_ERROR_SIZE_NOT_MATCH;

  if (*error)
    return (struct s_set){0, NULL};

  return st_fconsructor(nb_images, height, width, fp_images, fp_labels, error);
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
  for (; sample < last_sample; ++sample)
    f(sample);
}

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                   VIEWER                                  //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

void st_print(struct s_set *set)
{
  st_foreach(set, sp_print);
}
