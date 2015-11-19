#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Here we are going to write some functions to support a linked list that stores
 * Person data (name, age)
 */
typedef struct person_t
{
    char* name;
    int age;
} Person;

/* Example functions given to you. If you want to truly grasp these concepts, try
 * writing your own structs and functions as well!
 */

// Create a new Person
Person* create_person(const char* name, int age)
{
    Person* p = (Person*) malloc(sizeof(Person));
    p->name = strdup(name); // Uses malloc!
    p->age = age;
    return p;
}

// Make a deep copy of a Person
void* copy_person(const void* data)
{
    Person *p = (Person*) data;
    return create_person(p->name, p->age);
}

// Print a Person
void print_person(void* data)
{
    Person *p = (Person*) data;
    printf("%s, %d\n", p->name, p->age);
}

// Free a Person
void free_person(void* data)
{
    // This is safe because we should only be passing in Person struct pointers
    Person *p = (Person*) data;
    // free any malloc'd pointers contained in the Person struct (just name)
    free(p->name);
    // Now free the struct itself; this takes care of non-malloc'd data, like age.
    free(p);
}

// Return 1 if the person's name is 8+ characters long
int long_name(const void *data)
{
	Person *p = (Person*) data;
	return strlen(p->name) > 7;
}

/* This main function does a little testing
   Like all good CS Majors you should test
   your code here. There is no substitute for testing
   and you should be sure to test for all edge cases
   e.g., calling remove_front on an empty list.
*/
int main(void)
{
	/* Now to make use of all of this stuff */
	list* llist = create_list();

  /* What does an empty list contain?  Lets use our handy traversal function */
  printf("TEST CASE 1\nAn Empty list should print nothing here:\n");
  traverse(llist, print_person);
	printf("\n");

 	/* Lets add a person and then print */
 	push_front(llist, create_person("Andrew", 24));
 	printf("TEST CASE 2\nA List with one person should print that person:\n");
 	traverse(llist, print_person);
 	printf("\n");

 	/* Lets remove that person and then print */
 	remove_front(llist, free_person);
 	printf("TEST CASE 3\nAnother Empty list should print nothing here:\n");
 	traverse(llist, print_person);
 	printf("\n");

 	/* Lets add two people and then print */
 	push_front(llist, create_person("Nick", 22));
 	push_front(llist, create_person("Randal", 21));
 	printf("TEST CASE 4\nA List with two people should print those two people:\n");
 	traverse(llist, print_person);
 	printf("\n");

	/* Lets copy this list */
	list* llist2 = copy_list(llist, copy_person);
	printf("TEST CASE 5\nA copied list should print out the same two people:\n");
 	traverse(llist2, print_person);
 	printf("\n");

  /* Lets kill the list */
  empty_list(llist, free_person);
 	printf("TEST CASE 6\nAfter freeing all nodes the list should be empty:\n");
 	traverse(llist, print_person);
	printf("\n");

	/* Let's make a list of people, and remove certain ones! */
	/* Should remove anyone whose name is 8+ characters long */
	push_front(llist, create_person("Josephine", 27));
	push_front(llist, create_person("Dave", 34));
	push_front(llist, create_person("Benjamin", 23));
	push_front(llist, create_person("Lisa", 41));
	push_front(llist, create_person("Maximilian", 24));
	remove_if(llist, long_name, free_person);
	printf("TEST CASE 7\nShould only print 2 people with short names:\n");
	traverse(llist, print_person);
  printf("\n");

  /* Check push_back */
  empty_list(llist, free_person);
  push_back(llist, create_person("Abby", 16));
  push_back(llist, create_person("Connor", 20));
  push_back(llist, create_person("Jake", 22));
  printf("TEST CASE 8\nShould print all three people in order of age:\n");
  traverse(llist, print_person);
  printf("\n");

  /* Check push_back in empty list */
  empty_list(llist, free_person);
  push_back(llist, create_person("Abby", 16));
  printf("TEST CASE 9\nShould print one person:\n");
  traverse(llist, print_person);
  printf("\n");

  /* Check push_front in empty list */
  empty_list(llist, free_person);
  push_front(llist, create_person("Abby", 16));
  printf("TEST CASE 10\nShould print one person:\n");
  traverse(llist, print_person);
  printf("\n");

  /* Check back and front */
  empty_list(llist, free_person);
  push_back(llist, create_person("Abby", 16));
  push_back(llist, create_person("Connor", 20));
  push_back(llist, create_person("Jake", 22));
  printf("TEST CASE 11A\nShould print front of list:\n");
  print_person(front(llist));
  printf("\nTEST CASE 11B\nShould print back of list:\n");
  print_person(back(llist));
  empty_list(llist, free_person);
  printf("\n");

  /* Check remove_back */
  empty_list(llist, free_person);
  push_back(llist, create_person("Abby", 16));
  push_back(llist, create_person("Connor", 20));
  push_back(llist, create_person("Jake", 22));
  printf("TEST CASE 12\nShould print front of list:\n");
  remove_back(llist, free_person);
  traverse(llist, print_person);
  printf("\n");

  /* Test size of list */
  printf("TEST CASE 13A\nShould print 2:\n");
  printf("%d", size(llist));
  printf("\n");
  empty_list(llist, free_person);
  printf("\nTEST CASE 13B\nShould print 0:\n");
  printf("%d", size(llist));
  printf("\n");

  /* Test is empty on full and empty list */
  push_back(llist, create_person("Abby", 16));
  push_back(llist, create_person("Connor", 20));
  push_back(llist, create_person("Jake", 22));
  printf("\nTEST CASE 14A\nShould print 0:\n");
  printf("%d", is_empty(llist));
  printf("\n");
  empty_list(llist, free_person);
  printf("\nTEST CASE 14B\nShould print 1:\n");
  printf("%d\n", is_empty(llist));
  printf("\n");

  // Add 2 students to the front of the list, remove the a single entry
  push_back(llist, create_person("Abby", 16));
  push_back(llist, create_person("Connor", 20));
  remove_back(llist, free_person);
  printf("TEST CASE 15\nPrints out the two people:\n");
  traverse(llist, print_person);
  printf("\n");

  /*Test remove_front on empty list */
  empty_list(llist, free_person);
  printf("TEST CASE 16\nTrying to remove front of empty list:\n");
  printf("%d\n",remove_front(llist,free_person));
  printf("\n");

  /*Test remove_back on empty list */
  empty_list(llist, free_person);
  printf("TEST CASE 17\nTrying to remove back of empty list:\n");
  printf("%d\n",remove_back(llist,free_person));
  printf("\n");

 	/* Testing over clean up*/
	empty_list(llist, free_person);
 	free(llist);
	empty_list(llist2, free_person);
	free(llist2);

  return 0;
}

