/**
 * CS 2110 - Spring 2015 - Homework #10
 * Edited by: Brandon Whitehead, Andrew Wilder
 *
 * list.c: Complete the functions!
 */

/* Connor Lindquist */

#include <stdlib.h>
#include <stdio.h>
#include "list.h"

/* The node struct.  Has a prev pointer, next pointer, and data. */
/* DO NOT DEFINE ANYTHING OTHER THAN WHAT'S GIVEN OR YOU WILL GET A ZERO*/
/* Design consideration only this file should know about nodes */
/* Only this file should be manipulating nodes */
/* DO NOT TOUCH THIS DECLARATION DO NOT PUT IT IN OTHER FILES */
typedef struct lnode
{
  struct lnode* prev; /* Pointer to previous node */
  struct lnode* next; /* Pointer to next node */
  void* data; /* User data */
} node;


/* Do not create any global variables here. Your linked list library should obviously work for multiple linked lists */
// This function is declared as static since you should only be calling this inside this file.
static node* create_node(void* data);

/** create_node
  *
  * Helper function that creates a node by allocating memory for it on the heap.
  * Be sure to set its pointers to NULL.
  *
  * @param data a void pointer to data the user wants to store in the list
  * @return a node
  */
static node* create_node(void* data)
{
  node *createNode = malloc(sizeof *createNode);
  createNode->data = data; //Set data and pointers
  createNode->prev = NULL;
  createNode->next = NULL;
  return createNode;
}

/** create_list
  *
  * Creates a list by allocating memory for it on the heap.
  * Be sure to initialize size to zero and head/tail to NULL.
  *
  * @return an empty linked list
  */
list* create_list(void)
{
  list *createList = malloc(sizeof *createList);
  createList->head = NULL; //Set pointers and size
  createList->tail = NULL;
  createList->size = 0;
  return createList;
}

/** push_front
  *
  * Adds the data to the front of the linked list
  *
  * @param llist a pointer to the list.
  * @param data pointer to data the user wants to store in the list.
  */
void push_front(list* llist, void* data)
{
    node *newNode = create_node(data);
    if(llist->size == 0) { //If empty, must set pointers
        llist->head = newNode;
        llist->tail = newNode;
        llist->size = 1;
    } else { //If not empty, must set head pointer and next pointer
        newNode->next = llist->head;
        ((llist->head)->prev) = newNode;
        llist->head = newNode;
        llist->size = (llist->size) + 1;
    }
}

/** push_back
  *
  * Adds the data to the back/end of the linked list
  *
  * @param llist a pointer to the list.
  * @param data pointer to data the user wants to store in the list.
  */
void push_back(list* llist, void* data)
{
  node *createNode = create_node(data);
  if(llist->head != NULL) { //If not empty, must set tail pointer and previous
    createNode->prev = llist->tail;
    llist->tail->next = createNode;
    llist->tail = createNode;
  } else { //If empty, must set head and tail pointer
    llist->head = createNode;
    llist->tail = createNode; 
  }
  llist->size++;
}

/** front
  *
  * Gets the data at the front of the linked list
  * If the list is empty return NULL.
  *
  * @param llist a pointer to the list
  * @return The data at the first node in the linked list or NULL.
  */
void* front(list* llist)
{
  return (llist->head->data); //Returns head's data
}

/** back
  *
  * Gets the data at the "end" of the linked list
  * If the list is empty return NULL.
  *
  * @param llist a pointer to the list
  * @return The data at the last node in the linked list or NULL.
  */
void* back(list* llist)
{
  return (llist->tail->data); //Returns tail's data
}

/** remove_front
  *
  * Removes the node at the front of the linked list
  *
  * @warning Note the data the node is pointing to is also freed. If you have any pointers to this node's data it will be freed!
  *
  * @param llist a pointer to the list.
  * @param free_func pointer to a function that is responsible for freeing the node's data.
  * @return -1 if the remove failed (which is only there are no elements) 0 if the remove succeeded.
  */
int remove_front(list* llist, list_op free_func)
{
  if(llist->head == NULL){ //If list is empty return -1
    return -1;
  } else { //Otherwise set to head->next and free head
    node *lnode = (llist->head);
    free_func(lnode->data);
    llist->head=lnode->next;
    free(lnode);
    lnode=NULL;
    llist->size--;
    return 0;
  }
}

/** remove_back
  *
  * Removes the node at the back of the linked list
  *
  * @warning Note the data the node is pointing to is also freed. If you have any pointers to this node's data it will be freed!
  *
  * @param llist a pointer to the list.
  * @param free_func pointer to a function that is responsible for freeing the node's data.
  * @return -1 if the remove failed 0 if the remove succeeded.
  */
int remove_back(list* llist, list_op free_func)
{
  if(is_empty(llist)) { 
    return -1;
  } else {
    free_func(llist->tail->data);
    if(llist->size == 1){ //If list will be empty after removing
      free(llist->tail);
      llist->head = llist->tail = NULL;
    } else { //List more than 1 in size
      node* temp = llist->tail->prev;
      free(llist->tail);
      llist->tail = temp;
      llist->tail->next = NULL;
    }
    (llist->size)--;
  }
  return 0;
}

/** copy_list
  *
  * Create a new list structure, new nodes, and new copies of the data by using
  * the copy function. Its implementation for any test structure must copy
  * EVERYTHING!
  *
  * @param llist A pointer to the linked list to make a copy of
  * @param copy_func A function pointer to a function that makes a copy of the
  *        data that's being used in this linked list, allocating space for
  *        every part of that data on the heap. This is some function you must
  *        write yourself for testing, tailored specifically to whatever context
  *        you're using the linked list for in your test.
  * @return The linked list created by copying the old one
  */
list* copy_list(list* llist, list_cpy copy_func)
{
  list *newlList = create_list();
  node *tempNode = llist->head;
  while(tempNode!=NULL){ //Copy into new list
    push_back(newlList, copy_func(tempNode->data));
    tempNode = tempNode->next;
  }
  return newlList;
}

/** size
  *
  * Gets the size of the linked list
  *
  * @param llist a pointer to the list
  * @return The size of the linked list
  */
int size(list* llist)
{
  return (llist->size);
}

/** remove_if
  *
  * Removes all nodes whose data when passed into the predicate function returns true
  *
  * @param llist a pointer to the list
  * @param pred_func a pointer to a function that when it returns true it will remove the element from the list and do nothing otherwise @see list_pred.
  * @param free_func a pointer to a function that is responsible for freeing the node's data
  * @return the number of nodes that were removed.
  */
int remove_if(list* llist, list_pred pred_func, list_op free_func)
{
  node* cur = llist->head;     
  node* p;
  node* n;
  int removed = 0;
  int j = size(llist);
  volatile int i=0;
  for (i; i < j; i++) { // loop through list
    if (cur != NULL && pred_func(cur->data)) {
      free_func(cur->data); // free the node's data
      p = cur->prev;
      n = cur->next;
      if (p == NULL && n == NULL) { // the only element is the head
        cur = NULL;
        free(cur);
      } else if (p == NULL) { // previous is only null when removing the head
        n->prev = NULL;
        llist->head = n;
        free(cur);
        cur = n;  
      } else if (n == NULL) { // n is only null if we're removing the tail
        p->next = NULL;
        llist->tail = p;
        free(cur);  
      } else { // removing somewhere in the middle of the list
        p->next = n;
        n->prev = p;
        free(cur);
        cur = n; // move to the next node in the list
      }
      removed++;
      llist->size = llist->size - 1;
    } else {
      cur = cur->next; // move to the next node if nothing was removed
    }
  }
  return removed;
}

/** is_empty
  *
  * Checks to see if the list is empty.
  *
  * @param llist a pointer to the list
  * @return 1 if the list is indeed empty 0 otherwise.
  */
int is_empty(list* llist)
{
  if(llist->size==0){ //If empty return 1
    return 1;
  }
  return 0; //Return 0 if not empty
}

/** empty_list
  *
  * Empties the list after this is called the list should be empty.
  *
  * @param llist a pointer to a linked list.
  * @param free_func function used to free the node's data.
  */
void empty_list(list* llist, list_op free_func)
{
  while(llist->head!=NULL) { //Traverse list and free
    remove_front(llist, free_func);
  }
  llist->size=0; //Reset size to zero
}

/** traverse
  *
  * Traverses the linked list calling a function on each node's data.
  *
  * @param llist a pointer to a linked list.
  * @param do_func a function that does something to each node's data.
  */
void traverse(list* llist, list_op do_func)
{
  node *tempNode = llist->head;
  while(tempNode!=NULL) {
    do_func(tempNode->data);
    tempNode=tempNode->next;
  }
}
