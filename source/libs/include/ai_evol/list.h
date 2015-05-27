/**
  * @file list.h
  * @brief This file contains a primitive list implementation - which exactly a list.
  */
#ifndef LIST_H
#define LIST_H
#include <stdbool.h>
#include <stdlib.h>

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/
/******************************************************************************/
/* TYPES                                                                      */
/******************************************************************************/

/**
  * Element of the list.
  */
struct list_NODE
{
  /** The content */
  void* element;
  /** Pointer to the next element */
  struct list_NODE* next;
};

/******************************************************************************/

/**
 * The list representation.
 */
typedef struct
{
  /** Private members */
  struct list_PRIVATE* _private;
  /** pointer to the first element */
  struct list_NODE* first_element;
} list_LIST;

/*****************************************************************************/

/**
* @brief callback function to destroy an element
* @param element the destroyable element
*/
typedef void (*list_DESTROY)(void* element);

/*****************************************************************************/

/**
* @brief callback function to clone an element
* @param dest the destination of the copy
* @param element the element to copy
* @param size size of the element
* @param returns pointer to destination
*/
typedef void* (*list_COPY)(void* dest,
    const void* element, size_t size);

/*****************************************************************************/
/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/

/**
 * Initialize function for the list
 * @param element_size the size of one element in the list
 * @param list the list to initialize
 * @param destroy_func Destroy function for an element. If this pointer is NULL
 * @param copy_func copy function for an element. If this pointer is NULL
 * the default behavior is memcpy.
 */
void
list_init_list(list_LIST* list,
               unsigned element_size,
               list_DESTROY destroy_func,
               list_COPY copy_func);

/******************************************************************************/

/**
 * Initialize a list like another one.
 * @param list: list to initialize
 * @param other: list to clone basic structure
 */
void
list_init_like(list_LIST* list,
               const list_LIST* other);

/******************************************************************************/

/**
 * Add a new element to the list
 * @details The element will be copied
 * The element will be copied with the copy function which was given during 
 * initialization.
 * This function insert the element to the begining of the list
 * @param list list to increase
 * @param element the element to push
 */
void 
list_add_element(list_LIST* list,
                  const void* element);

/******************************************************************************/

/**
* Returns the size of the given list.
* @param list the given list
*/
unsigned
list_size(const list_LIST* list);

/******************************************************************************/

/**
* Returns the size of the element in the list.
* @param list the given list
*/
unsigned
list_element_size(const list_LIST* list);

/******************************************************************************/

/**
* Returns true if the list is empty
* @param list the given list
*/
bool
list_is_empty(const list_LIST* list);

/******************************************************************************/

/**
 * Free the memory of the current list
 */
void
list_destroy(list_LIST* list);
           
/******************************************************************************/

/**
 * @param list: List to copy 
 * @return a copy of the input list
 */
list_LIST
list_copy(const list_LIST* list);

/******************************************************************************/

/**
 * Concatenate two list.
 * @param dest list to extends
 * @param source list which is the source
 * @warning This function does not copy the source list, only makes connection
 * between theme.
 */
void
list_concat_list(list_LIST* dest, const list_LIST* source);

/******************************************************************************/

/**
 * Revert the order of the list.
 * This list representation is a chained list, but the chaining is only done
 * to one direction. Sometimes it is not enough, but it has better performance.
 * To solve some problem sometimes it is enough if we can revert the list.
 * This function change the directio of the elements, and in that way the
 * first element will be the last and the last will be the first.
 * @param list: list to revert
 */
void
list_revert(list_LIST* list);

#endif
