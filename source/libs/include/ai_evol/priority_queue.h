/**
* @file priority_queue.h
* @brief Priority queue implementation.
* @details This implementation is based on a heap.
*/
#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "list.h"

#include <stdlib.h>


/*****************************************************************************/

/**
* The element in the queue
*/
typedef struct
{
  /** The rank of this element */
  int rank;
  /** The content of this element */
  void* element;
} priority_queue_ELEMENT;

/*****************************************************************************/

/**
* @brief callback function to destroy an element
* @param element the destroyable element
*/
typedef void (*priority_queue_DESTROY)(void* element);

/*****************************************************************************/

/**
* @brief callback function to clone an element
* @param dest the destination of the copy
* @param element the element to copy
* @param size size of the element
* @param returns pointer to destination
*/
typedef void* (*priority_queue_COPY)(void* dest,
    const void* element, size_t size);

/*****************************************************************************/

/**
* Representation of the maximum queue.
*/
typedef struct
{
  /** private members */
  struct priority_queue_PRIVATE* _private;
} priority_queue_QUEUE;

/*****************************************************************************/

/**
* Create a new queue.
* @param queue Queue to create
* @param element_size The size of the elemets in the queue.
* @param capacity Maximum capacity of the queue.
* @param destroy_func function to distroy an element. If it NULL, only a free 
* will be done.
* @param copy_func function to copy an element. If it NULL, memcpy is the default
*/
void
priority_queue_init(priority_queue_QUEUE* queue,
                    const unsigned capacity,
                    const unsigned element_size,
                    priority_queue_DESTROY destroy_func,
                    priority_queue_COPY clone_func);

/*****************************************************************************/

/**
* Create a new queue similary like the other one.
* @param queue Queue to create
* @param other This queue's data is used during init
*/
void
priority_queue_init_like(priority_queue_QUEUE* queue,
                         const priority_queue_QUEUE* other);

/*****************************************************************************/

/**
* insert a new element in the queue.
* Insert the given element in the last place in the heap (e.g.: in the last level
* most right place). With swapping move the element in the correct place.
* The element will be copied with the copy function which was given during 
* initialization.
* @param queue Queue to expand.
* @param element Element to insert.
* @param rank the rank of the given element
*/
void
priority_queue_insert(priority_queue_QUEUE* queue,
                      const void* element,
                      const int rank);

/*****************************************************************************/

/** 
* Remove the first element in the queue.
* This element is the maximum element.
* After the deletition the last element (e.g.: in the last level the most
* right one) will be placed to the root place. After this with swapping the 
* elements will be reordered.
*/
void
priority_queue_pop(priority_queue_QUEUE* queue);

/*****************************************************************************/

/**
* Getter for the maximum element
*/
priority_queue_ELEMENT
priority_queue_first(const priority_queue_QUEUE* queue);

/*****************************************************************************/

/**
* Free the memory, which is used by the given queue
*/
void
priority_queue_destroy(priority_queue_QUEUE* queue);

/*****************************************************************************/

/**
* @returns Capacity of the given queue
*/
unsigned
priority_queue_capacity(const priority_queue_QUEUE* queue);

/*****************************************************************************/

/**
* @returns Current size of the given queue
*/
unsigned
priority_queue_current_size(const priority_queue_QUEUE* queue);

/*****************************************************************************/

/**
* @param queue: queue to copy
* @returns A deep copy of the input
*/
priority_queue_QUEUE
priority_queue_copy(const priority_queue_QUEUE* queue);

/*****************************************************************************/

/**
* @returns Elements size of the given queue
*/
unsigned
priority_queue_element_size(const priority_queue_QUEUE* queue);

/*****************************************************************************/

/**
* Creates a sorted list from the given queue.
* It is usefull to iterates over the elements which is sorted by rank. 
* @returns A list with the copy of elements which are ordered by rank.
*/
list_LIST
priority_queue_to_list(const priority_queue_QUEUE* queue);

/*****************************************************************************/

/**
* Removes the given number of elements from the back of the queue.
* This function removes the num_of_elements worths elements from the given 
* queue.
*
* This function do memory allocations therefore it is not so efficient.
* If it is possible to avoid this usage it worth it.
* \param num_of_elements: number of removeable elements
* \param queue: Queue to modify
*/
void
priority_queue_pop_back(priority_queue_QUEUE* queue, unsigned num_of_elements);

#endif

