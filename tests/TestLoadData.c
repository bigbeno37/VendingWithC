/*
 * Created by bigbeno37 on 13/09/17.
 */

#include "TestLoadData.h"
#include "../vm_options.h"
#include "Tests.h"

void createStockFromLineCorrectlyCreatesStock() {
    char *line = "I0002|Apple Pie|Delicious Stewed Apple in a Yummy Pastry envelope|3.0|20";

    Stock *stock = createStockFromLine(line);

    sAssertThat("Created stock should have a valid ID", "I0002", stock->id);
    sAssertThat("Created stock should have a valid name", "Apple Pie", stock->name);
    sAssertThat("Created stock should have a valid description",
                "Delicious Stewed Apple in a Yummy Pastry envelope", stock->desc);
    iAssertThat("Created stock should have a valid price", 3, stock->price.dollars);
    iAssertThat("Created stock should have a valid price in cents", 0, stock->price.cents);
    iAssertThat("Created stock should have a valid amount of stock", 20, stock->onHand);
}

void loadStockCorrectlyLoadsStock() {
    char *testFile = "stock-file.dat";

    FILE *file = fopen(testFile, "w+");
    char *line = "I0002|Apple Pie|Delicious Stewed Apple in a Yummy Pastry envelope|3.0|20\n";
    char *secondLine = "I0003|Apple Pie|Delicious Stewed Apple in a Yummy Pastry envelope|3.0|20\n";

    VmSystem *system = malloc(sizeof(VmSystem));

    List *list = malloc(sizeof(List));
    list->head = NULL;
    list->size =  0;

    system->itemList = list;

    fputs(line, file);
    fputs(secondLine, file);
    fclose(file);

    iAssertThat("Before loading stock from file, the list size is 0", 0, list->size);

    loadStock(system, testFile);

    iAssertThat("After loading stock from file, the list size is 2", 2, list->size);

    remove(testFile);
}