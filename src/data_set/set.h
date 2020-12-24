/**
** \file src/data_set/set.h
** \author Jules Lefebvre <jules.lefebvre@epita.fr
** \version 1.0.0
** \date 2020/10/04
** \brief declaraton of the `s_set` object.
**
** definition of constuctor, destructor and method of the  s_set` object.
*/

#ifndef UNREAD__SRC_DATA_SET__SET_H_
#define UNREAD__SRC_DATA_SET__SET_H_

#include <stdio.h>
#include "sample.h"
#include "utils.h"

/**
** \struct s_set
** \brief a list of sample
**
** is a dataset to use in a neurole network
*/
struct s_set
{
  unsigned int count;
  struct s_sample *samples;
};

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                CONSTRUCTOR                                //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

/**
** \brief `s_set` constuctor.
**
** each sample is initalise with the same dimentions and a null label.
**
** ⚠️** you need to use the `st_destructor` function after dataset use (to free
** space )** ⚠️
**
** \param count the number of sample in the dataset
** \param height the height of each images of the dataset
** \param width the width of each images of the datadset
** \param error error return. in case of error all the will be destroy
**
** \return a new instance of `s_set`
*/
struct s_set st_consructor(unsigned int count, unsigned int height, unsigned int width, enum sp_error *error);

/**
** \brief `s_set` file constuctor from file
**
** create an `s_set` base on a image file and a label file.
**
** ⚠️** you need to use the `st_destructor` function after set use (to free
** space )** ⚠️
**
** \param count the number of sample in the dataset
** \param height the height of each images of the dataset
** \param width the width of each images of the datadset
** \param fp_images a file contaiging the images data, see `mk_fconstructor`
** \param fp_label a file contaiging the label, each one code in a 1 pont
** \param error error return. in case of error all will be destroy
**
** \return a new instance of `s_set`
*/
struct s_set st_fconsructor(unsigned int count, unsigned int height, unsigned int width, FILE *fp_images, FILE *fp_label, enum sp_error *error);

/**
** \brief `s_set` MNIST constuctor
**
** create an `s_set` base on file in MNIST format
**
** ⚠️** you need to use the `st_destructor` function after set use (to free
** space )** ⚠️
**
** \param fp_images a file contaiging the images data, see `mk_fconstructor`
** \param fp_label a file contaiging the label, each one code in a 1 pont
** \param error error return. in case of error all will be destroy
**
** \return a new instance of `s_set`
*/
struct s_set st_from_file(FILE *fp_images, FILE *fp_label, enum sp_error *error);

/**
** \brief `s_set` MNIST constuctor from path
**
** create an `s_set` by giving 2 file in MNIST format
**
** ⚠️** you need to use the `st_destructor` function after set use (to free
** space )** ⚠️
**
** \param image_dataset_path path to the images part of the dataset
** \param labels_dataset_path path to the labels part of the dataset
** \param error error return. in case of error all will be destroy
**
** \return a new instance of `s_set`
*/
struct s_set st_import(char *image_dataset_path, char *labels_dataset_path, enum sp_error *error);

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                 DESTRUCTOR                                //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

/**
** \brief `s_set` destructor.
**
** \param set a pointer to the set to destroy
*/
void st_destructor(struct s_set *set);

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                  METHODE                                  //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

/**
** \brief apply a function to all the sample
**
** \param mask the set to browse
*/
void st_foreach(struct s_set *set, void (*f)(struct s_sample *));

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                   VIEWER                                  //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

/**
** \brief diplay all the sample in the set
**
** \param set the set to print
*/
void st_print(struct s_set *set);

#endif // UNREAD__SRC_DATA_SET__SET_H_