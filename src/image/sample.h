/**
** \file src/image/sample.h
** \author Jules Lefebvre <jules.lefebvre@epita.fr
** \version 1.0.0
** \date 2020/10/04
** \brief declaration of the `s_sample` object
**
** declartion of all the methode use to manipulate the `s_sample` object
*/

#ifndef UNREAD__SRC_IMAGE__SAMPLE_H_
#define UNREAD__SRC_IMAGE__SAMPLE_H_

#include <stdio.h>
#include "mask.h"

/**
** \enum sp_errror
** \brief code error of the `s_sample` function
**
** this containe return code error for constuctor and methode of the `s_sample` object
*/
enum sp_error
{
  /**
  ** success creation of a `s_sample`
  */
  SP_SUCCESS = 0,
  /**
  ** error during creation of image `s_mask` : not enought free space
  */
  SP_ERROR_SPACE,
  /**
  ** error we arrive to end of file containing image
  */
  SP_ERROR_EOF_IMAGE,
  /**
  ** error we arrive to end of file containing label
  */
  SP_ERROR_EOF_LABEL,
  /**
  ** error throw when the start code of the images file is not correct
  */
  SP_ERROR_WONG_FILECODE_IMAGE,
  /**
  ** error throw when the start code of the labels file is not correct
  */
  SP_ERROR_WONG_FILECODE_LABEL,
  /**
  ** error the image and labels count is not the same
  */
  SP_ERROR_SIZE_NOT_MATCH,
  /**
  ** error throw when the sample given path didn't exist
  */
  SP_ERROR_NO_SAMPLES_FILE,
  /**
  ** error throw when the image given path didn't exist
  */
  SP_ERROR_NO_IMAGES_FILE
};

/**
** \struct s_sample
** \brief a sample to be proccess by the neurole network.
**
** for the label the value `\x00` is considere as unkown label
*/
struct s_sample
{
  struct s_mask image;
  char label;
};

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                CONSTRUCTOR                                //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

/**
** \brief `s_sample` constuctor.
**
** ⚠️** you need to use the `sp_destructor` function after sample use (to free
** space )** ⚠️
**
** \param height the number of row of pixels in the image
** \param width the number of collum of pixels in the image
** \param label the repesenting letter.
** \param error error return see `mk_constructor` for more information
**
** \return a new instance of `s_sample`
*/
struct s_sample sp_consructor(unsigned int height, unsigned int width, char label, enum sp_error *error);

/**
** \brief `s_sample` constuctor from file
**
** create an `s_sample` base on a image file and a label file.
**
** ⚠️** you need to use the `sp_destructor` function after sample use (to free
** space )** ⚠️
**
** \param height the number of row of pixels in the image
** \param width the number of collum of pixels in the image
** \param fp_images a file contaiging the images data, see `mk_fconstructor`
** \param fp_label a file contaiging the label, each one code in a 1 pont
** \param error error return see `mk_constructor`.
**
** \return a new instance of `s_sample`
*/
struct s_sample sp_fconsructor(unsigned int height, unsigned int width, FILE *fp_images, FILE *fp_label, enum sp_error *error);

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                 DESTRUCTOR                                //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

/**
** \brief `s_sample` destructor.
**
** \param sample a pointer to the sample to destroy
*/
void sp_destructor(struct s_sample *sample);

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                  METHODE                                  //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
/**
** \brief convert an mask to an sample error.
**
** translate the `mk_error` to an `sp_error` and return -1 if not find
**
** \param error the mask error
*/
enum sp_error mk_to_sp_error(enum mk_error error);

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                   VIEWER                                  //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

/**
** \brief diplay the sample
**
** \param sample the sample to print
*/
void sp_print(struct s_sample *sample);

/**
** \brief display value of the sample
**
** print the lablel and the image in hexa.
**
** \param sample the sample to debug
*/
void sp_debug(struct s_sample *sample);

#endif // UNREAD__SRC_IMAGE__SAMPLE_H_