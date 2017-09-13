#include "vm_options.h"
#include "vm_linkedlist.h"
#include "utility.h"
#include <string.h>

/**
 * vm_options.c this is where you need to implement the system handling
 * functions (e.g., init, free, load, save) and the main options for
 * your program. You may however have some of the actual work done
 * in functions defined elsewhere.
 **/

/**
 * Initialise the system to a known safe state. Look at the structure
 * defined in vm_system.h.
 **/
Boolean systemInit(VmSystem * system)
{
    List *list = malloc(sizeof(VmSystem));
    list->head = NULL;
    list->size = 0;
    system->itemList = list;

    return FALSE;
}

/**
 * Free all memory that has been allocated. If you are struggling to
 * find all your memory leaks, compile your program with the -g flag
 * and run it through valgrind.
 **/
void systemFree(VmSystem * system)
{ }

/**
 * Loads the stock and coin data into the system. You will also need to assign
 * the char pointers to the stock and coin file names in the system here so
 * that the same files will be used for saving. A key part of this function is
 * validation. A substantial number of marks are allocated to this function.
 **/
Boolean loadData(
    VmSystem * system, const char * stockFileName, const char * coinsFileName)
{
    loadStock(system, stockFileName);
    loadCoins(system, coinsFileName);

    return FALSE;
}

/**
 * Loads the stock file data into the system.
 **/
Boolean loadStock(VmSystem * system, const char * fileName)
{
    FILE *stockFile;
    char stockData[MAX_STOCK_LINE_LEN];

    stockFile = fopen(fileName, "r");

    if (stockFile == NULL) {
        puts("Error: File not found!");

        return FALSE;
    }

    while (fgets(stockData, MAX_STOCK_LINE_LEN, stockFile) != NULL) {
        Stock *stock = createStockFromLine(stockData);

        addNode(system->itemList, stock);
    }

    fclose(stockFile);

    return TRUE;
}

/*
 * Return a stock instance based on the line input
 */
Stock *createStockFromLine(char *line) {
    char seperator[2] = "|";
    char priceSeperator[2] = ".";

    char *lineCopy = copyString(line);

    char *id = strtok(lineCopy, seperator);
    char *name = strtok(NULL, seperator);
    char *description = strtok(NULL, seperator);
    char *priceString = strtok(NULL, seperator);
    char *quantityString = strtok(NULL, seperator);

    char *dollarsString = strtok(priceString, priceSeperator);
    char *centsString = strtok(NULL, priceSeperator);

    unsigned int dollars = (unsigned int) strtol(dollarsString, NULL, 10);
    unsigned int cents = (unsigned int) strtol(centsString, NULL, 10);

    unsigned int quantity = (unsigned int) strtol(quantityString, NULL, 10);
    Stock *stock = malloc(sizeof(Stock));

    Price price;
    price.dollars = dollars;
    price.cents = cents;

    stock->onHand = quantity;
    stock->price = price;
    strcpy(stock->id, id);
    strcpy(stock->name, name);
    strcpy(stock->desc, description);

    return stock;
}

/**
 * Loads the coin file data into the system.
 **/
Boolean loadCoins(VmSystem * system, const char * fileName)
{
    // TODO
    // Load in denominations from file
    Coin fiveCents, tenCents, twentyCents, fiftyCents, oneDollar,
    twoDollars, fiveDollars, tenDollars;

    fiveCents.count = 5;
    fiveCents.denom = FIVE_CENTS;

    tenCents.count = 10;
    tenCents.denom = TEN_CENTS;

    twentyCents.count = 20;
    twentyCents.denom = TWENTY_CENTS;

    fiftyCents.count = 50;
    fiftyCents.denom = FIFTY_CENTS;

    oneDollar.count = 100;
    oneDollar.denom = ONE_DOLLAR;

    twoDollars.count = 200;
    twoDollars.denom = TWO_DOLLARS;

    fiveDollars.count = 500;
    fiveDollars.denom = FIVE_DOLLARS;

    tenDollars.count = 1000;
    tenDollars.denom = TEN_DOLLARS;

    system->cashRegister[0] = fiveCents;
    system->cashRegister[1] = tenCents;
    system->cashRegister[2] = twentyCents;
    system->cashRegister[3] = fiftyCents;
    system->cashRegister[4] = oneDollar;
    system->cashRegister[5] = twoDollars;
    system->cashRegister[6] = fiveDollars;
    system->cashRegister[7] = tenDollars;

    return FALSE;
}

/**
 * Saves all the stock back to the stock file.
 **/
Boolean saveStock(VmSystem * system)
{
    return FALSE;
}

/**
 * Saves all the coins back to the coins file.
 **/
Boolean saveCoins(VmSystem * system)
{
    return FALSE;
}

/**
 * This option allows the user to display the items in the system.
 * This is the data loaded into the linked list in the requirement 2.
 **/
void displayItems(VmSystem * system)
{
    int i;
    int idLength = 2, nameLength = 4, quantityLength = 9, priceLength = 5;
    int currentIDLength, currentNameLength, currentQuantityLength, currentPriceLength;

    printf("Items Menu\n\n");

    for (i = 1; i <= system->itemList->size; i++) {

        currentIDLength = (int) strlen(getNthNode(system->itemList, i)->data->id);
        currentNameLength = (int) strlen(getNthNode(system->itemList, i)->data->name);
        currentQuantityLength = getDigits(getNthNode(system->itemList, i)->data->onHand);
        currentPriceLength = getDigits(getNthNode(system->itemList, i)->data->price.dollars)
                + EXTRA_CHAR_IN_PRICE;

        if (currentIDLength > idLength) {
            idLength = currentIDLength;
        }

        if (currentNameLength > nameLength) {
            nameLength = currentNameLength;
        }

        if (currentQuantityLength > quantityLength) {
            quantityLength = currentQuantityLength;
        }

        if (currentPriceLength > priceLength) {
            priceLength = currentPriceLength;
        }
    }

    printf("ID");
    printNSpaces((int) (idLength - strlen("ID")));
    printf(" | Name");
    printNSpaces((int) (nameLength - strlen("Name")));
    printf(" | Available");
    printNSpaces((int) (quantityLength - strlen("Available")));
    printf(" | Price");
    printNSpaces((int) (priceLength - strlen("Price")));
    puts(EMPTY_STRING);

    printNDashes(idLength + nameLength + quantityLength + priceLength + COLUMN_SPACES);

    puts(EMPTY_STRING);

    for (i = 1; i <= system->itemList->size; i++) {
        Stock *currentStock = getNthNode(system->itemList, i)->data;

        printf("%s", currentStock->id);
        printNSpaces((int) (idLength - strlen(currentStock->id)));
        printf(" | %s", currentStock->name);
        printNSpaces((int) (nameLength - strlen(currentStock->name)));
        printf(" | %d", currentStock->onHand);
        printNSpaces(quantityLength - getDigits(currentStock->onHand));
        printf(" | $ %d.%02d", currentStock->price.dollars, currentStock->price.cents);
        puts(EMPTY_STRING);
    }
}

/**
 * This option allows the user to purchase an item.
 * This function implements requirement 5 of the assignment specification.
 **/
void purchaseItem(VmSystem * system)
{
    Stock *stock;

    puts("Purchase item");
    puts("-------------");
    printf("Please enter the id of the item you wish to purchase: ");

    char *input = getUserInput(ID_LEN);

    /* If the specified stock exists... */
    stock = getStockWithID(input, system->itemList);
    if (stock) {
        printf("You have selected \"%s\t%s\". This will cost you $%d.%02d.\n", stock->name,
        stock->desc, stock->price.dollars, stock->price.cents);

        puts("Please hand over the money – type in the value of each note/coin in cents.\n"
                     "Press enter on a new and empty line to cancel this purchase:");
        printf("You still need to give us $%d.%02d: ", stock->price.dollars, stock->price.cents);


    }
}

/**
 * You must save all data to the data files that were provided on the command
 * line when the program loaded up, display goodbye and free the system.
 * This function implements requirement 6 of the assignment specification.
 **/
void saveAndExit(VmSystem * system)
{ }

/**
 * This option adds an item to the system. This function implements
 * requirement 7 of of assignment specification.
 **/
void addItem(VmSystem * system)
{ }

/**
 * Remove an item from the system, including free'ing its memory.
 * This function implements requirement 8 of the assignment specification.
 **/
void removeItem(VmSystem * system)
{ }

/**
 * This option will require you to display the coins from lowest to highest
 * value and the counts of coins should be correctly aligned.
 * This function implements part 4 of requirement 18 in the assignment
 * specifications.
 **/
void displayCoins(VmSystem * system)
{ }

/**
 * This option will require you to iterate over every stock in the
 * list and set its onHand count to the default value specified in
 * the startup code.
 * This function implements requirement 9 of the assignment specification.
 **/
void resetStock(VmSystem * system)
{ }

/**
 * This option will require you to iterate over every coin in the coin
 * list and set its 'count' to the default value specified in the
 * startup code.
 * This requirement implements part 3 of requirement 18 in the
 * assignment specifications.
 **/
void resetCoins(VmSystem * system)
{ }

/**
 * This option will require you to display goodbye and free the system.
 * This function implements requirement 10 of the assignment specification.
 **/
void abortProgram(VmSystem * system)
{ }
