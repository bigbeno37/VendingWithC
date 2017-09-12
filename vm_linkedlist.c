//
// Created by bigbeno37 on 13/09/17.
//

#include "vm_linkedlist.h"
#include "vm_coin.h"

unsigned int getListSize(List *list) {
    unsigned int length = 0;

    Node *currentNode = list->head;

    while(currentNode != NULL) {
        length++;

        currentNode = currentNode->next;
    }

    return length;
}

void addNode(List *list, Stock *data) {
    Node *pointer = malloc(sizeof(Node));
    pointer->next = NULL;
    pointer->data = data;

    if (list->head == NULL) {
        list->head = pointer;
    } else {
        pointer->next = list->head;

        list->head = pointer;
    }

    list->size = getListSize(list);
}

Node *getNthNode(List *list, int index) {
    int counter = list->size;
    Node *node = list->head;

    while (counter > index) {
        node = node->next;

        counter--;
    }

    return node;
}
