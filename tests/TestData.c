#include "TestData.h"
#include "../vm_options.h"
#include "Tests.h"
#include "../vm_stock.h"

/*
 * Determine if createStockFromLine will correctly return a Stock instance
 * based on the input line
 */
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

    free(stock);
}

/*
 * Determine if loadStock correctly loads Stock from the file specified
 * Will physically create a file and then perform tests, removing the file
 * afterwards
 */
void loadStockCorrectlyLoadsStock() {
    char *testFile = "stock-file.dat";

    FILE *file = fopen(testFile, "w+");
    char *line = "I0002|Apple Pie|Delicious Stewed Apple in a Yummy Pastry envelope|3.0|20\n";
    char *secondLine = "I0003|Apple Pie|Delicious Stewed Apple in a Yummy Pastry envelope|3.0|20\n";

    VmSystem system;

    List *list = malloc(sizeof(List));
    list->head = NULL;
    list->size =  0;

    system.itemList = list;

    fputs(line, file);
    fputs(secondLine, file);
    fclose(file);

    iAssertThat("Before loading stock from file, the list size is 0", 0, list->size);

    loadStock(&system, testFile);

    sAssertThat("After loading stock form file, the first node will have ID I0002",
                "I0002", getNthNode(list, 1)->data->id);
    sAssertThat("After loading stock form file, the second node will have ID I0003",
                "I0003", getNthNode(list, 2)->data->id);
    iAssertThat("After loading stock from file, the list size is 2", 2, list->size);

    remove(testFile);
    free(list);
}

/*
 * Determine if createLineFromStock will return a correctly formatted
 * line based on the stock passed in
 */
void createLineFromStockCorrectlyFormatsLine() {
    Stock *stock = malloc(sizeof(Stock));

    stock->price = getPriceFromValue(375);
    stock->onHand = 20;
    strcpy(stock->name, "Meat Pie");
    strcpy(stock->id, "I0001");
    strcpy(stock->desc, "Aussie classic");

    sAssertThat("Stock will be converted into the appropriate string",
    "I0001|Meat Pie|Aussie classic|3.75|20", createLineFromStock(stock));

    stock->price = getPriceFromValue(1000);
    stock->onHand = 99;
    strcpy(stock->name, "Apple Pie");
    strcpy(stock->id, "I0002");
    strcpy(stock->desc, "Yummy dessert!");

    sAssertThat("New stock will be converted into the appropriate string",
    "I0002|Apple Pie|Yummy dessert!|10.00|99", createLineFromStock(stock));

    free(stock);
}

/*
 * Determine if saveStock correctly updates the stock file
 */
void saveStockCorrectlyUpdatesStockFile() {
    char *filename = "stock-test.dat";
    VmSystem *system = malloc(sizeof(VmSystem));
    List *list = malloc(sizeof(List));
    Stock *stock = malloc(sizeof(Stock)), *newStock = malloc(sizeof(Stock));

    list->head = NULL;
    list->size = 0;

    system->itemList = list;
    system->stockFileName = copyString(filename);

    stock->price = getPriceFromValue(375);
    stock->onHand = 20;
    strcpy(stock->id, "I0001");
    strcpy(stock->name, "Meat pie");
    strcpy(stock->desc, "Aussie classic");

    addNode(list, stock);

    newStock->price = getPriceFromValue(375);
    newStock->onHand = 20;
    strcpy(newStock->id, "I0002");
    strcpy(newStock->name, "Meat pie");
    strcpy(newStock->desc, "Aussie classic");
    addNode(list, newStock);

    saveStock(system);

    assertTrue("stock-test.dat will exist", fileExists(filename));

    /* Reset list */
    list->head = NULL;
    list->size = 0;

    /* Load the stocks in from file */
    loadStock(system, filename);

    sAssertThat("The first node will have ID I0001", "I0001", getNthNode(list, 1)->data->id);
    sAssertThat("The second node will have ID I0002", "I0002", getNthNode(list, 2)->data->id);

    remove(filename);
    free(system);
    free(list);
    free(stock);
    free(newStock);
}