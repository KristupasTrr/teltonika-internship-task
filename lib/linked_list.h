#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <pthread.h>

/**
 * @brief A linked list node
 */
typedef struct Node { 
    void  *data; 
    struct Node *next; 
} Node;

/**
 * @brief Linked list structure
 */
typedef struct LinkedList {
    Node *head;
    Node *tail;
    int size;
    pthread_mutex_t lock;
} LinkedList;

/**
 * @brief Initialize linked list 
 * 
 * @param ll Linked list pointer
 */
void init_ll(LinkedList *ll);

/**
 * @brief Add data to linked list end
 * 
 * @param ll Linked list pointer
 * @param new_data Data to add to linked list
 * @param data_size Data size
 */
void push(LinkedList *ll, void *new_data, size_t data_size);

/**
 * @brief Return last node's data, change tail node to second to last node and delete last node
 * 
 * @param ll Linked list pointer
 * @return void* Returns pointer to data
 */
void *pop(LinkedList *ll);

/**
 * @brief Free every node, delete pointers and mutex lock
 * 
 * @param ll Linked list pointer
 */
void delete_list(LinkedList *ll);

/**
 * @brief Print elements in the linked list of type char
 * 
 * @param ll Linked list pointer
 */
void print_char(LinkedList *ll);

/**
 * @brief Print elements in the linked list of type int
 * 
 * @param ll Linked list pointer
 */
void print_int(LinkedList *ll);
