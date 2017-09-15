#include "../vm_coin.h"
#include "Tests.h"
#include "../vm_stock.h"

/*
 * Determine if getListSize will accurately reflect the size
 * of the linked list
 */
void getSizeWillCorrectlyReturnSize() {
    /* Create a new list and stock item */
    List *list = malloc(sizeof(List));
    Stock *stock = malloc(sizeof(Stock)), *secondStock = malloc(sizeof(Stock)),
        *thirdStock = malloc(sizeof(Stock));
    list->head = NULL;
    strcpy(stock->id, "I0001");
    strcpy(secondStock->id, "I0002");
    strcpy(thirdStock->id, "I0003");

    iAssertThat("Before adding a node, list size is 0", 0, getListSize(list));

    addNode(list, stock);

    iAssertThat("After adding a node, list size is 1", 1, getListSize(list));

    addNode(list, secondStock);
    addNode(list, thirdStock);

    iAssertThat("After adding 3 nodes, the size of the list should be 3", 3, getListSize(list));

    free(list);
    free(stock);
    free(secondStock);
    free(thirdStock);
}

/*
 * Determine if getNthNode will return the correct node in the list
 */
void getNodeWillCorrectlyReturnNode() {
    List *list = malloc(sizeof(List));
    Stock *stock = malloc(sizeof(Stock)), *newStock = malloc(sizeof(Stock));
    list->head = NULL;

    strcpy(stock->id, "I0001");

    addNode(list, stock);

    sAssertThat("After adding a node, I can retrieve the first node",
                "I0001", getNthNode(list, 1)->data->id);

    strcpy(newStock->id, "I0002");
    addNode(list, newStock);

    sAssertThat("After adding two nodes, I can retrieve the second node",
                "I0002", getNthNode(list, 2)->data->id);

    free(list);
    free(stock);
    free(newStock);
}

/*
 * Determine if getStockWithID will correctly return the node with ID
 * specified, and if not, will return NULL
 */
void nodeWithIDExistsWillCorrectlyReturnIfSpecifiedNodeExists() {
    List *list = malloc(sizeof(List));
    Stock *stock = malloc(sizeof(Stock)), *newStock = malloc(sizeof(Stock));
    list->head = NULL;

    strcpy(stock->id, "I0001");
    strcpy(newStock->id, "I0002");

    addNode(list, stock);

    assertNull("Stock with ID I0002 will be NULL", getStockWithID("I0002", list));
    assertNotNull("Stock with ID I0001 will exist", getStockWithID("I0001", list));

    addNode(list, newStock);

    assertNotNull("After adding stock with ID I0002, it will now exist",
                  getStockWithID("I0002", list));

    free(list);
    free(stock);
    free(newStock);
}

/*
 * Determine if addNode will correctly position the node passed in
 * based on ID entered
 */
void addNodeWillCorrectlyPositionAddedNode() {
    List *list = malloc(sizeof(List));
    Stock *firstStock = malloc(sizeof(Stock)), *fifthStock = malloc(sizeof(Stock)),
    *secondStock = malloc(sizeof(Stock));

    list->head = NULL;
    list->size = 0;

    strcpy(firstStock->id, "I0001");

    addNode(list, firstStock);
    assertNotNull("After adding the first stock, it will exist", getNthNode(list, 1));

    strcpy(fifthStock->id, "I0005");
    addNode(list, fifthStock);
    assertNotNull("After adding the fifth stock, it will exist", getNthNode(list, 2));
    sAssertThat("After adding the fifth stock, the second node will have ID I0005",
        "I0005", getNthNode(list, 2)->data->id);

    strcpy(secondStock->id, "I0002");
    addNode(list, secondStock);
    sAssertThat("After adding the second stock, the second node will have ID I0002",
        "I0002", getNthNode(list, 2)->data->id);
    sAssertThat("After adding the second stock, the third node will have ID I0005",
        "I0005", getNthNode(list, 3)->data->id);

    free(list);
    free(firstStock);
    free(fifthStock);
    free(secondStock);
}

/*
 * Determine if removeNode will correctly remove nodes from the system
 */
void removeNodeWillCorrectlyRemoveNodeFromSystem() {
    List *list = malloc(sizeof(List));
    Stock *firstStock = malloc(sizeof(Stock)), *secondStock = malloc(sizeof(Stock)),
        *thirdStock = malloc(sizeof(Stock));

    strcpy(firstStock->id, "I0001");
    strcpy(secondStock->id, "I0002");
    strcpy(thirdStock->id, "I0003");

    addNode(list, firstStock);
    addNode(list, secondStock);
    addNode(list, thirdStock);

    sAssertThat("The first node will have ID I0001", "I0001", getNthNode(list, 1)->data->id);
    removeNode("I0001", list);
    sAssertThat("After removing the first node, the new first node will have ID I0002",
        "I0002", getNthNode(list, 1)->data->id);

    addNode(list, firstStock);
    sAssertThat("The second node will have ID I0002", "I0002", getNthNode(list, 2)->data->id);
    removeNode("I0002", list);
    sAssertThat("After removing the second node, the new second node will have ID I0003",
        "I0003", getNthNode(list, 2)->data->id);

    free(list);
    free(firstStock);
    free(secondStock);
    free(thirdStock);
}