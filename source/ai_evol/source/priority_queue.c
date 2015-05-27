#include "../header/priority_queue.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

#include <debug_util/debug.h>

#define PARENT(i)      ((i) / 2)
#define LEFT_CHILD(i)  (2 * (i))
#define RIGHT_CHILD(i) (2 * (i) + 1)
#define _BUFFER _private->buffer
#define _CAPACITY _private->capacity
#define _CURRENT_SIZE _private->current_size
#define _ELEMENT_SIZE _private->element_size
#define HAS_LEFT_CHILD(queue, i) (LEFT_CHILD(i) < queue->_CURRENT_SIZE)
#define HAS_RIGHT_CHILD(queue, i) (RIGHT_CHILD(i) < queue->_CURRENT_SIZE)

static void
swap_element(priority_queue_QUEUE* queue, unsigned position1, unsigned position2);

static void
erease_element(priority_queue_QUEUE* queue, unsigned position);

static void
trace_element(void* element, char buffer[DEBUG_UTIL_BUFFER_SIZE]);

/*****************************************************************************/

static void
default_destroy(void * element);

/*****************************************************************************/


/*****************************************************************************/

struct priority_queue_PRIVATE
{
  priority_queue_ELEMENT* buffer;
  unsigned capacity;
  unsigned current_size;
  unsigned element_size;
  priority_queue_DESTROY destroy_func;
  priority_queue_COPY copy_func;
};

/*****************************************************************************/

void
priority_queue_init(priority_queue_QUEUE* queue,
                    const unsigned capacity,
                    const unsigned element_size,
                    priority_queue_DESTROY destroy_func,
                    priority_queue_COPY copy_func)
{
  DEBUG_UTIL_DEBUG(1, "Init priority queue\n", 0);
  assert(queue != NULL);
  queue->_private = malloc(sizeof(struct priority_queue_PRIVATE));
  assert(queue->_private != NULL);

  queue->_private->buffer = (priority_queue_ELEMENT*)
                            malloc(capacity * sizeof(priority_queue_ELEMENT));
  assert(queue->_private->buffer != NULL);

  queue->_private->capacity = capacity;
  queue->_private->current_size = 0;
  queue->_private->element_size = element_size;
  queue->_private->destroy_func = destroy_func ? destroy_func
                                               : default_destroy;
  queue->_private->copy_func = copy_func ? copy_func
                                           : memcpy;
  
  DEBUG_UTIL_TRACE_ELEMENT(DEBUG_UTIL_LEVEL_DEBUG + 3,
                           queue,
                           trace_element);
}

/*****************************************************************************/

void
priority_queue_init_like(priority_queue_QUEUE* queue,
                         const priority_queue_QUEUE* other)
{
  priority_queue_init(queue,
                      other->_private->capacity,
                      other->_private->element_size,
                      other->_private->destroy_func,
                      other->_private->copy_func);
}

/*****************************************************************************/

priority_queue_QUEUE
priority_queue_copy(const priority_queue_QUEUE* queue)
{
  priority_queue_QUEUE ret;
  unsigned i = 0;
  priority_queue_init(&ret, 
                      queue->_private->capacity,
                      queue->_private->element_size,
                      queue->_private->destroy_func,
                      queue->_private->copy_func);
  for (i = 0; i < queue->_CURRENT_SIZE; ++i)
  {
    priority_queue_insert(&ret,
        queue->_BUFFER[i].element,
        queue->_BUFFER[i].rank);
  }

  return ret;
}

/*****************************************************************************/

void
priority_queue_insert(priority_queue_QUEUE* queue,
                      const void* element,
                      const int rank)
{
  unsigned current_position;
  void* copy_of_element;
  DEBUG_UTIL_DEBUG(1, "Insert to priority queue with rank: %d\n", rank);

  assert(queue != NULL);
  assert(queue->_private != NULL);
  assert(element != NULL);
  assert(queue->_CURRENT_SIZE < queue->_private->capacity);
  DEBUG_UTIL_TRACE_ELEMENT(DEBUG_UTIL_LEVEL_DEBUG + 3,
                           queue,
                           trace_element);

  copy_of_element = malloc(queue->_ELEMENT_SIZE);
  assert(copy_of_element != NULL);

  current_position = queue->_CURRENT_SIZE;
  queue->_private->copy_func(copy_of_element,
      element,
      queue->_ELEMENT_SIZE);

  queue->_BUFFER[current_position].rank = rank;
  queue->_BUFFER[current_position].element = copy_of_element;

  /* reorder elements */
  while (current_position != 0
         && queue->_BUFFER[current_position].rank 
            > queue->_BUFFER[PARENT(current_position)].rank)
  {
    swap_element(queue, current_position, PARENT(current_position));
    current_position = PARENT(current_position);
  }
  queue->_CURRENT_SIZE++;
  DEBUG_UTIL_DEBUG(3, "content after insert\n", 0);
  DEBUG_UTIL_TRACE_ELEMENT(DEBUG_UTIL_LEVEL_DEBUG + 3,
                           queue,
                           trace_element);
}

/*****************************************************************************/

void
priority_queue_pop(priority_queue_QUEUE* queue)
{
  unsigned current_pos;
  int current_rank;
  assert(queue != NULL);
  assert(queue->_private != NULL);
  assert(queue->_CURRENT_SIZE > 0);
  DEBUG_UTIL_DEBUG(1, "Pop from priority queue\n", 0);
  DEBUG_UTIL_TRACE_ELEMENT(DEBUG_UTIL_LEVEL_DEBUG + 3,
                           queue,
                           trace_element);

  swap_element(queue, 0, queue->_CURRENT_SIZE - 1);
  erease_element(queue, queue->_CURRENT_SIZE - 1);

  current_pos = 0;
  current_rank = queue->_BUFFER[0].rank;
  queue->_CURRENT_SIZE--;

  /* reorder elements */
  while ((HAS_LEFT_CHILD(queue, current_pos)
          && current_rank < queue->_BUFFER[LEFT_CHILD(current_pos)].rank)
         || (HAS_RIGHT_CHILD(queue, current_pos)
             && current_rank < queue->_BUFFER[RIGHT_CHILD(current_pos)].rank))
  {
    unsigned next_pos = HAS_LEFT_CHILD(queue, current_pos) 
      ? LEFT_CHILD(current_pos)
      : RIGHT_CHILD(current_pos);
    if (HAS_LEFT_CHILD(queue, current_pos) && HAS_RIGHT_CHILD(queue, current_pos)
        && queue->_BUFFER[LEFT_CHILD(current_pos)].rank
           < queue->_BUFFER[RIGHT_CHILD(current_pos)].rank)
    {
      next_pos = RIGHT_CHILD(current_pos);
    }
    swap_element(queue, current_pos, next_pos);
    current_pos = next_pos;
  }
  DEBUG_UTIL_DEBUG(3, "content after pop\n", 0);
  DEBUG_UTIL_TRACE_ELEMENT(DEBUG_UTIL_LEVEL_DEBUG + 3,
                           queue,
                           trace_element);
}

/*****************************************************************************/

priority_queue_ELEMENT
priority_queue_first(const priority_queue_QUEUE* queue)
{
  assert(queue != NULL);
  assert(queue->_private != NULL);
  assert(queue->_CURRENT_SIZE > 0);
  return queue->_BUFFER[0];
}

/*****************************************************************************/

static void
default_destroy(void* element)
{ 
  free(element);
}

/*****************************************************************************/

void
priority_queue_destroy(priority_queue_QUEUE* queue)
{
  assert(queue != NULL);
  assert(queue->_private != NULL);
  DEBUG_UTIL_DEBUG(1, "destroy priority queue\n", 0);
  while (queue->_CURRENT_SIZE > 0)
  {
    priority_queue_pop(queue);
  }
  free(queue->_private->buffer);
  free(queue->_private);
  queue->_private = NULL;
}

/*****************************************************************************/

static void
swap_element(priority_queue_QUEUE* queue, unsigned position1, unsigned position2)
{
  priority_queue_ELEMENT tmp = queue->_BUFFER[position1];
  queue->_BUFFER[position1] = queue->_BUFFER[position2];
  queue->_BUFFER[position2] = tmp;
}

/*****************************************************************************/

static void
erease_element(priority_queue_QUEUE* queue, unsigned position)
{
  (queue->_private->destroy_func)(queue->_BUFFER[position].element);
  memset(&queue->_BUFFER[position], 0, sizeof(priority_queue_ELEMENT));
}

/*****************************************************************************/

unsigned
priority_queue_capacity(const priority_queue_QUEUE* queue)
{
  assert(queue != NULL);
  assert(queue->_private != NULL);
  return queue->_private->capacity;
}

/*****************************************************************************/

unsigned
priority_queue_current_size(const priority_queue_QUEUE* queue)
{
  assert(queue != NULL);
  assert(queue->_private != NULL);
  return queue->_CURRENT_SIZE;
}

/*****************************************************************************/

unsigned
priority_queue_element_size(const priority_queue_QUEUE* queue)
{
  assert(queue != NULL);
  assert(queue->_private != NULL);
  return queue->_ELEMENT_SIZE;
}

/*****************************************************************************/

list_LIST
priority_queue_to_list(const priority_queue_QUEUE* queue)
{
  list_LIST ret;
  assert(queue != NULL);
  assert(queue->_private != NULL);
  DEBUG_UTIL_DEBUG(1, "Priority queue to list\n", 0);
  {
    priority_queue_QUEUE copy_queue = priority_queue_copy(queue);
    list_init_list(&ret, queue->_ELEMENT_SIZE,
                   queue->_private->destroy_func,
                   queue->_private->copy_func);
    while (priority_queue_current_size(&copy_queue) > 0)
    {
      list_add_element(&ret, priority_queue_first(&copy_queue).element);
      priority_queue_pop(&copy_queue);
    }
    priority_queue_destroy(&copy_queue);
  }
  list_revert(&ret);
  return ret;
}

/*****************************************************************************/

static void
trace_element(void* element, char buffer[DEBUG_UTIL_BUFFER_SIZE])
{
  assert(element);
  {
    priority_queue_QUEUE* queue = (priority_queue_QUEUE*)element;
    unsigned i = 0, j = 0;
    int written = sprintf(buffer, "queue elements:\n");
    for (i = 0; i < queue->_CURRENT_SIZE; ++i)
    {
      written += sprintf(buffer + written, "  [%u-%d]: ",
              i, queue->_BUFFER[i].rank);

      for (j = 0; j < queue->_ELEMENT_SIZE / sizeof(unsigned char); ++j)
      {
        written += sprintf(buffer + written,
                "%02X ", ((unsigned char*)queue->_BUFFER[i].element)[j]);
      }
      written += sprintf(buffer + written, "\n");
    }

  }
}

/*****************************************************************************/

void
priority_queue_pop_back(priority_queue_QUEUE* queue, 
                        unsigned num_of_elements)
{
  assert(queue != NULL);
  if (num_of_elements == 0)
  {
    return;
  }
  {
    /* There is no deep copy at the end.
    *  therefore do not destroy the tmp_queue. 
    *  */
    priority_queue_QUEUE tmp_queue;
    unsigned current_size = priority_queue_current_size(queue);
    int i = 0;
    int num_of_elements_to_keep;
    priority_queue_init_like(&tmp_queue, queue);

    /* save the elements to keep */
    num_of_elements_to_keep = current_size - num_of_elements;
    assert(num_of_elements_to_keep >= 0);

    while (i < num_of_elements_to_keep)
    {
      priority_queue_ELEMENT first = priority_queue_first(queue);
      priority_queue_insert(&tmp_queue, 
                            first.element,
                            first.rank);
      priority_queue_pop(queue);
      ++i;
    }
    priority_queue_destroy(queue);

    /* shallow copy */
    priority_queue_init_like(queue, &tmp_queue);
    queue->_CURRENT_SIZE = tmp_queue._CURRENT_SIZE;
    memcpy(queue->_BUFFER, tmp_queue._BUFFER, 
           tmp_queue._CAPACITY * sizeof(priority_queue_ELEMENT));
    
  }
}
