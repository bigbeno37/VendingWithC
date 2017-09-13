#include "../vm_coin.h"
#include "Tests.h"
#include "../vm_stock.h"

/*
 * Determine if getListSize will accurately reflect the size
 * of the linked list
 */
void getSizeWillCorrectlyReturnSize() {
    /* Create a new list and stock item */
    List list;
    Stock stock;
    list.head = NULL;

    iAssertThat("Before adding a node, list size is 0", 0, getListSize(&list));

    addNode(&list, &stock);

    iAssertThat("After adding a node, list size is 1", 1, getListSize(&list));

    addNode(&list, &stock);
    addNode(&list, &stock);

    iAssertThat("After adding 3 nodes, the size of the list should be 3", 3, getListSize(&list));
}

/*
 * Determine if getNthNode will return the correct node in the list
 */
void getNodeWillCorrectlyReturnNode() {
    List list;
    Stock stock, newStock;
    list.head = NULL;

    strcpy(stock.id, "1");

    addNode(&list, &stock);

    sAssertThat("After adding a node, I can retrieve the first node", "1", getNthNode(&list, 1)->data->id);

    addNode(&list, &stock);

    strcpy(newStock.id, "2");
    addNode(&list, &newStock);

    sAssertThat("After adding three nodes, I can retrieve the third node", "2", getNthNode(&list, 3)->data->id);
    sAssertThat("After adding three nodes, I can retrieve the second node", "1", getNthNode(&list, 2)->data->id);
}

/*
 * Determine if getStockWithID will correctly return the node with ID
 * specified, and if not, will return NULL
 */
void nodeWithIDExistsWillCorrectlyReturnIfSpecifiedNodeExists() {
    List *list = malloc(sizeof(List));
    Stock stock;
    Stock newStock;
    list->head = NULL;

    strcpy(stock.id, "2");
    strcpy(newStock.id, "1");

    assertNull("Before adding Stock with ID 2, it will not exist", getStockWithID("2", list));

    addNode(list, &stock);

    assertNull("Stock with ID 1 will be NULL", getStockWithID("1", list));
    assertNotNull("Stock with ID 2 will exist", getStockWithID("2", list));

    addNode(list, &newStock);

    assertNotNull("After adding stock with ID 1, it will now exist", getStockWithID("1", list));
}