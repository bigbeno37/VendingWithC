#include "vm_stock.h"

/**
 * vm_stock.c this is the file where you will implement the
 * interface functions for managing the stock list.
 **/

/**
 * Some example functions:
 * create list, free list, create node, free node, insert node, etc...
 */

/*
 * Returns the size of the linked list passed in
 */
unsigned int getListSize(List *list) {
    unsigned int length = 0;

    /* Iterate through each node and increment length by 1
     * until the final node is reached (AKA its 'next' value
     * is NULL) */
    Node *currentNode = list->head;
    while(currentNode != NULL) {
        length++;

        currentNode = currentNode->next;
    }

    return length;
}

/*
 * Add a node with the data passed in to the linked list
 * also passed in
 */
void addNode(List *list, Stock *data) {
    /* Create the Node that will be added */
    Node *pointer = malloc(sizeof(Node));
    pointer->data = data;

    /* Set the current node's 'next' variable to the linked
     * list's head node. If it does not exist, this node will
     * become the head of the linked list, and its 'next' variable
     * will remain NULL*/
    pointer->next = list->head;

    /* Replace the head of the node with the current node */
    list->head = pointer;

    /* Update the size of the list with the new size */
    list->size = getListSize(list);
}

/*
 * Returns the nth node of the linked list, where the 1st node is
 * the starting node (the one initially store in the linked list)
 * and continues backwards
 *
 * Eg
 * HEAD
 * I0004 -> I0003 -> I0002 -> I0001
 *
 * getNthNode(1) will return I0001
 */
Node *getNthNode(List *list, int n) {
    int counter = list->size;
    Node *node = list->head;

    while (counter > n) {
        node = node->next;

        counter--;
    }

    return node;
}

/*
 * Retrieves the stock in the linked list with the ID
 * passed in if it exists. If not, it will return NULL
 */
Stock *getStockWithID(char *id, List *list) {
    int i;

    for (i = 1; i <= list->size; i++) {
        Node *node = getNthNode(list, i);

        /* If the ID of the retrieved node matches the ID passed in
         * then return the node*/
        if (strcmp(node->data->id, id) == 0) {
            return node->data;
        }
    }

    return NULL;
}