#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <pthread.h>
#include "linked_list.h"

void init_ll(LinkedList *ll) {
    ll->head = NULL;
    ll->tail = NULL;
    ll->size = 0;
    pthread_mutex_init(&ll->lock, NULL);
}

void push(LinkedList *ll, void *new_data, size_t data_size) {
    pthread_mutex_lock(&ll->lock);
    Node *new_node = malloc(sizeof(Node));
    new_node->data = malloc(data_size);
    new_node->data = new_data;
    new_node->next = NULL;
    if(ll->size == 0) {
        ll->head = new_node;
        ll->tail = new_node;
    } else {
        ll->tail->next = new_node;
        ll->tail = new_node;
    }
    ll->size++;
    pthread_mutex_unlock(&ll->lock);
}

void *pop(LinkedList *ll) {
    pthread_mutex_lock(&ll->lock);
    if(ll->size == 0) {
        printf("Nothing to pop!\n");  
        pthread_mutex_unlock(&ll->lock);
        return NULL;  
    } else if (ll->size == 1) {
        void *res = ll->head->data;

        ll->size--;
        free(ll->head);
        ll->head = NULL;
        ll->tail = NULL;
        pthread_mutex_unlock(&ll->lock);
        return res;
    } else {
        Node *return_node = ll->head;
        void *res;
        while (return_node->next->next != NULL) {
            return_node = return_node->next;
        }
        res = return_node->next->data;
        free(return_node->next);
        return_node->next = NULL;
        ll->tail = return_node;
        ll->size--;

        pthread_mutex_unlock(&ll->lock);
        return res;
    }
}

void delete_list(LinkedList *ll)
{  
  Node* current = ll->head;
  Node* next;
  while (current != NULL) {
    next = current->next;
    free(current);
    current = next;
  }
  ll->head = NULL;
  ll->tail = NULL;
  pthread_mutex_destroy(&ll->lock);
}

void print_char(LinkedList *ll) {
    Node *current = ll->head;
    while(current != NULL) {
        printf("%s\n", current->data);
        current = current->next;
    }
    free(current);
}

void print_int(LinkedList *ll) {
    Node *current = ll->head;
    while(current != NULL) {
        printf("%d\n", *(int*)current->data);
        current = current->next;
    }
    free(current);
}

// int main() {
//     LinkedList ll;
//     init_ll(&ll);
 
//     int arr[] = {10, 20, 30, 40, 50}; 
//     const char *arr1[] = {"one","two","three"};

//     for (int i = 0; i < 3; i++){
//         push(&ll, (char*)arr1[i], sizeof(arr1[i]));
//         printf("%s\n", pop(&ll));
//     }

//     for (int i = 0; i < 5; i++){
//         push(&ll, &arr[i], sizeof(arr[i]));
//         printf("%d\n", *(int*)pop(&ll));
//     }

//     delete_list(&ll);

//     return 0;
// }
