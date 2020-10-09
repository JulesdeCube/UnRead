/**
** \file src/image/mask.h
** \author Jules Lefebvre <jules.lefebvre@epita.fr
** \version 1.0.0
** \date 2020/09/30
** \brief declaration of the `s_mask` object
**
** definition of constuctor, destructor and method of the `s_mask` object
*/

#ifndef UNREAD__SRC_IMAGE__MASK_H_
#define UNREAD__SRC_IMAGE__MASK_H_

#include <stdio.h>
#include <stdlib.h>

/**
** \enum mk_errror
** \brief code error of the `s_mask` function
**
** this containe return code error for constuctor and methode of the `s_mask`object
*/
enum mk_error
{
  /**
  ** success creation of a `s_mask`
  */
  MK_SUCCESS = 0,
  /**
  ** error during creation of a `s_mask` : not enought free space evalable
  */
  MK_ERROR_SPACE,
  /**
  ** error we arrive to end of file
  */
  MK_ERROR_EOF
};

/**
** \struct s_mask
** \brief an 1 channel image.
**
** En object contaigning the size of the mask and the list the 1 channel pixels.
*/
struct s_mask
{
  unsigned int height;
  unsigned int width;
  unsigned char *pixels;
};

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                CONSTRUCTOR                                //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

/**
** \brief `s_mask` constructor.
**
** create a blank mask of the given size and alocate memory for each pixel.
** ⚠️** you need to use the `mk_destructor` function after mask use (to free
** space )** ⚠️
**
** \param height number of pixel line
** \param width number of pixel in each line
** \param error error return, can be `MK_SUCCESS` if success or `IK_ERROR_SPACE`
**              if not enought free space
**
** \return a new blank instance of `s_mask` base on given dimention
*/
struct s_mask mk_constructor(unsigned int height, unsigned int width, enum mk_error *error);

/**
** \brief `s_mask` copy constructor.
**
** duplicate a mask.
** ⚠️** you need to use the `mk_destructor` function after mask use (to free
** space )** ⚠️
**
** \param mask a pointer to the mask to copy
** \param error error return, can be `MK_SUCCESS` if success or `IK_ERROR_SPACE`
**              if not enought free space
**
** \return a new blank instance of `s_mask` base on given dimention
*/
struct s_mask im_cconstructor(struct s_mask *mask, enum mk_error *error);

/**
** \brief create mask from file.
**
** create an `s_mask` base on a file data. each pixel 1 channel unsigned char
** value in line.
** ⚠️** you need to use the `mk_destructor` function after mask use (to free
** space )** ⚠️
**
** \param height number of pixel line
** \param width number of pixel in each line
** \param fp file pointer to the start of the mask data
** \param error error return, can be `MK_SUCCESS` if success or `MK_ERROR_SPACE`
**              if not enought free space
**
** \return a new instance of `s_mask` base on the file and given dimention
*/
struct s_mask mk_fconstructor(unsigned int height, unsigned int width, FILE *fp, enum mk_error *error);

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                 DESTRUCTOR                                //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
/**
** \brief destory an given `s_mask`.
**
** safe way to destoy and free space alocate for a mask. need to be call
** after mask use
**
** \param mask a pointer to the mask to destroy
*/
void mk_destructor(struct s_mask *mask);

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                 OPERATIONS                                //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
/**
** \brief fill mask with file data.
** Read the file data byte by bite and put each value in th given mask
**
** \param mask a pointer to the mask to fill
** \param fp a pointer to the start of the mask data
** \param error error return value can be MK_SUCCESS, MK_ERROR_SPACE and
**             MK_ERROR_EOF.
*/
void mk_fimport(struct s_mask *mask, FILE *fp, enum mk_error *error);

/**
** \brief return number of pixels in the mask.
**  return height * width or 0 if the mask was been destroys or not allocate
**
** \param mask a pointer to the mask to get count of pixels
**
** \return the number of pixels
*/
unsigned long mk_count(struct s_mask *mask);

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                   VIEWER                                  //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

/**
** \brief display a grey scale pixel in the console.
**
** \param value the brightness of the pixel
*/
void px_print(unsigned char value);

/**
** \brief diplay a grey scale mask on the console.
**
** \param mask the mask to print
*/
void mk_print(struct s_mask *mask);

/**
** \brief diplay a list of each value of the mask.
**
** print row by row the value of each pixel in hexa.
**
** \param mask the mask to debug
*/
void mk_debug(struct s_mask *image);

#endif // UNREAD__SRC_IMAGE__MASK_H_