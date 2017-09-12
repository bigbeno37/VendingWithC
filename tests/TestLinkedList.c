//
// Created by bigbeno37 on 13/09/17.
//

#include "../vm_coin.h"
#include "Tests.h"
#include "../vm_linkedlist.h"

void getSizeWillCorrectlyReturnSize() {
    List list;
    list.head = NULL;
    Stock stock;

    iAssertThat("Before, list size is 0", 0, getListSize(&list));

    addNode(&list, &stock);

    iAssertThat("After adding a node, list size is 1", 1, list.size);

    addNode(&list, &stock);
    addNode(&list, &stock);

    iAssertThat("After adding 3 nodes, the size of the list should be 3", 3, list.size);
}

void getNodeWillCorrectlyReturnNode() {
    List list;
    list.head = NULL;

    Stock *stock = malloc(sizeof(Stock));
    strcpy(stock->id, "1");

    addNode(&list, stock);

    sAssertThat("After adding a node, I can retrieve the first node", "1", getNthNode(&list, 1)->data->id);

    addNode(&list, stock);

    Stock *newStock = malloc(sizeof(Stock));
    strcpy(newStock->id, "2");
    addNode(&list, newStock);

    sAssertThat("After adding three nodes, I can retrieve the third node", "2", getNthNode(&list, 3)->data->id);
    sAssertThat("After adding three nodes, I can retrieve the second node", "1", getNthNode(&list, 2)->data->id);
}