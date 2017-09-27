/**************************************************************

** Student Name: Ben O'Sullivan

** Student Number: s3662617

** Date of submission: Wednesday, 27 Sept 2017

** Course: COSC1076 / COSC2207, Semester 2, 2017

***************************************************************/

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
    Node *newNode = malloc(sizeof(Node));
    Stock *currentStock;
    Node *currentNode = list->head, *previousNode = NULL;
    newNode->next = NULL;
    newNode->data = data;

    /* If the list doesn't contain a node, add one */
    if (list->head == NULL) {
        newNode->next = NULL;

        list->head = newNode;
        list->size = 1;

        return;
    }

    /* The list is not empty, so continue */
    /* While the node has not been placed */
    while(TRUE) {
        currentStock = currentNode->data;

        if (getValueOfID(currentStock->id) > getValueOfID(data->id)) {
            /* If previousNode is not NULL */
            if (previousNode) {
                previousNode->next = newNode;
            } else {
                /* There is no previous node, so set the list head to the new node */
                list->head = newNode;
            }

            newNode->next = currentNode;

            break;
        /* If this is the final node and the value is less than the
         * current ID, then set the new node to the end of the list */
        } else if (currentNode->next == NULL) {
            currentNode->next = newNode;

            break;
        }

        currentNode = currentNode->next;

        if (previousNode == NULL) {
            previousNode = list->head;
        } else {
            previousNode = previousNode->next;
        }
    }

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
    int counter = 1;
    Node *node = list->head;

    while (counter < n) {
        node = node->next;

        counter++;
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

/*
 * Removes a node with specified ID if it exists
 */
void removeNode(char *id, List *list) {
    Node *previousNode = NULL, *currentNode = list->head;

    while (TRUE) {
        /* If the ID matches the current node's */
        if (strcmp(currentNode->data->id, id) == 0) {
            /* If we're at the HEAD, then set the next node to be the head */
            if (previousNode == NULL) {
                list->head = currentNode->next;


                /* If we're at the end of the list, then set the previous
                 * node's next to be NULL*/
            } else if (currentNode->next == NULL) {
                previousNode->next = NULL;
                /* Node is inbetween two other nodes */
            } else {
                previousNode->next = currentNode->next;
            }

            free(currentNode);
            list->size = getListSize(list);
            break;
        }

        /* Node didn't contain same ID, so move to the next */
        if (previousNode != NULL) {
            previousNode = previousNode->next;
        } else {
            previousNode = list->head;
        }
        currentNode = currentNode->next;
    }
}