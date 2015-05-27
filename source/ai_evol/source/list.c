#include "../header/list.h"

#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include <debug_util/debug.h>

struct list_PRIVATE
{
  unsigned element_size;
  unsigned current_size;
  list_DESTROY destroy_func;
  list_COPY copy_func;
};

/******************************************************************************/

static void
default_destroy(void* element);

/******************************************************************************/

static void
trace_element(void* element, char buffer[DEBUG_UTIL_BUFFER_SIZE]);

/******************************************************************************/

void 
list_init_list(list_LIST* list,
               unsigned element_size,
               list_DESTROY destroy_func,
               list_COPY copy_func)
{

  DEBUG_UTIL_DEBUG(1, "Init list\n", 0);
  list->_private = malloc(sizeof(struct list_PRIVATE));
  assert(list != NULL);
  assert(list->_private != NULL);

  list->_private->element_size = element_size;
  list->_private->current_size = 0;
  list->first_element = NULL;
  list->_private->destroy_func = destroy_func ? destroy_func : default_destroy;
  list->_private->copy_func = copy_func ? copy_func 
                                        : memcpy;

}

/******************************************************************************/

void
list_init_like(list_LIST* list,
               const list_LIST* other)
{
  list_init_list(list,
                 other->_private->element_size,
                 other->_private->destroy_func,
                 other->_private->copy_func);
}

/******************************************************************************/

void 
list_add_element(list_LIST* list,
                  const void* element)
{
  struct list_NODE* new_element = malloc(sizeof(struct list_NODE));
  DEBUG_UTIL_DEBUG(1, "Init add new element\n", 0);
  assert(list != NULL);
  assert(list->_private != NULL);
  assert(new_element != NULL);

  new_element->element = malloc(list->_private->element_size);
  assert(new_element->element != NULL);

  list->_private->copy_func(new_element->element,
                            element,
                            list->_private->element_size);
  list->_private->current_size++;

  new_element->next = list->first_element;
  list->first_element = new_element;
  DEBUG_UTIL_TRACE_ELEMENT(DEBUG_UTIL_LEVEL_DEBUG + 3,
                           list,
                           trace_element);
}

/******************************************************************************/

unsigned
list_size(const list_LIST* list)
{
  assert(list != NULL);
  assert(list->_private != NULL);
  return list->_private->current_size;
}

/******************************************************************************/

unsigned
list_element_size(const list_LIST* list)
{
  assert(list != NULL);
  assert(list->_private != NULL);
  return list->_private->element_size;
}

/******************************************************************************/

bool 
list_is_empty(const list_LIST* list)
{
  assert(list != NULL);
  return list->first_element == NULL;
}

/******************************************************************************/

static void
default_destroy(void* element)
{
  free(element);
}

/******************************************************************************/

void
list_destroy(list_LIST* list)
{
  assert(list != NULL);
  {
    struct list_NODE* it = list->first_element;
    struct list_NODE* prev = NULL;
    while (it != NULL)
    {
      prev = it;
      it = it->next;
      (*list->_private->destroy_func)(prev->element);
      free(prev);
    }
    free(list->_private);
  }
}

/******************************************************************************/

/**
 * Free the memory of the current list
 */
list_LIST
list_copy(const list_LIST* list)
{
  list_LIST ret;
  assert(list);
  list_init_list(&ret,
                 list->_private->element_size,
                 list->_private->destroy_func,
                 list->_private->copy_func);
  {
    struct list_NODE* item = list->first_element;
    while (item)
    {
      list_add_element(&ret, item->element);
      item = item->next;
    }
  }
  return ret;
}

/******************************************************************************/

void
list_concat_list(list_LIST* dest, const list_LIST* source)
{
  struct list_NODE* last_element;

  assert(dest != NULL);
  assert(source != NULL);
  assert(dest->_private != NULL);
  assert(source->_private != NULL);

  last_element = dest->first_element;
  while (last_element != NULL) last_element = last_element->next;

  last_element->next = source->first_element;
}

/******************************************************************************/

static void
trace_element(void* element, char buffer[DEBUG_UTIL_BUFFER_SIZE])
{
  assert(element);
  {
    list_LIST* list = (list_LIST*)element;
    unsigned i = 0, j = 0;
    int written = sprintf(buffer, "list elements (element size: %u:\n",
                          list->_private->element_size);
    struct list_NODE* item = list->first_element;
    while (item != NULL)
    {
      written += sprintf(buffer + written, "  [%u]: ",
              i);

      for (j = 0; j < list->_private->element_size
                      / sizeof(unsigned char); ++j)
      {
        written += sprintf(buffer + written,
                "%02X ", ((unsigned char*)item->element)[j]);
      }
      written += sprintf(buffer + written, "\n");
      item = item->next;
      ++i;
    }
  }
}

/******************************************************************************/

void
list_revert(list_LIST* list)
{
  assert(list != NULL);
  {
    struct list_NODE* orig_next = NULL;
    struct list_NODE* prev_node = NULL;
    struct list_NODE* current_node = list->first_element;
    DEBUG_UTIL_DEBUG(1, "list_revert\n", 0);
    while (current_node != NULL)
    {
      orig_next = current_node->next;

      current_node->next = prev_node;
      prev_node = current_node;

      current_node = orig_next; /* current_node->next */
    }
    list->first_element = prev_node;
    DEBUG_UTIL_DEBUG(1, "list_revert end\n", 0);
  }
}

