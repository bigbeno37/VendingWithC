#include "vm_options.h"
#include "vm_stock.h"
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
{
    /* Free the linked list */
    int i;
    for (i = system->itemList->size; i > 0; i--) {
        free(getNthNode(system->itemList, i)->data);
        free(getNthNode(system->itemList, i));
    }

    free(system->itemList);
}

/**
 * Loads the stock and coin data into the system. You will also need to assign
 * the char pointers to the stock and coin file names in the system here so
 * that the same files will be used for saving. A key part of this function is
 * validation. A substantial number of marks are allocated to this function.
 **/
Boolean loadData(
    VmSystem * system, const char * stockFileName, const char * coinsFileName)
{
    system->stockFileName = stockFileName;
    system->coinFileName = coinsFileName;

    loadStock(system, stockFileName);
    loadCoins(system, coinsFileName);

    return TRUE;
}

/**
 * Loads the stock file data into the system.
 **/
Boolean loadStock(VmSystem * system, const char * fileName)
{
    FILE *stockFile;
    char stockData[MAX_STOCK_LINE_LEN];

    if (!fileExists(fileName)) {
        puts("Error: File not found!");

        return FALSE;
    }

    /* Open the file for read only access */
    stockFile = fopen(fileName, "r");

    /* While there is another line to read, continue reading lines
     * and generating Stock instances from them*/
    while (fgets(stockData, MAX_STOCK_LINE_LEN, stockFile) != NULL) {
        Stock *stock = malloc(sizeof(Stock));

        createStockFromLine(stockData, stock);

        /* For each stock instance created, at it to the linked list */
        addNode(system->itemList, stock);
    }

    fclose(stockFile);

    return TRUE;
}

/*
 * Return a stock instance based on the line input
 */
void createStockFromLine(char *line, Stock *newStock) {
    char separator[2] = "|";
    char priceSeparator[2] = ".";

    char *id = strtok(line, separator);
    char *name = strtok(NULL, separator);
    char *description = strtok(NULL, separator);
    char *priceString = strtok(NULL, separator);
    char *quantityString = strtok(NULL, separator);

    char *dollarsString = strtok(priceString, priceSeparator);
    char *centsString = strtok(NULL, priceSeparator);

    unsigned int dollars = (unsigned int) toInt(dollarsString);
    unsigned int cents = (unsigned int) toInt(centsString);

    unsigned int quantity = (unsigned int) toInt(quantityString);

    Price price;
    price.dollars = dollars;
    price.cents = cents;

    newStock->onHand = quantity;
    newStock->price = price;
    strcpy(newStock->id, id);
    strcpy(newStock->name, name);
    strcpy(newStock->desc, description);
}

/*
 * Takes in a stock instance and returns a formatted string containing
 * the stock's information
 */
void createLineFromStock(Stock *stock, char *outputLine) {

    char cents[PRICE_LEN], dollars[PRICE_LEN], quantity[3];

    strcat(outputLine, stock->id);
    strcat(outputLine, "|");
    strcat(outputLine, stock->name);
    strcat(outputLine, "|");
    strcat(outputLine, stock->desc);
    strcat(outputLine, "|");
    /* Amount of dollars must not exceed two digits */

    if (stock->price.dollars < 10) {
        iToString(dollars, stock->price.dollars, 1);
    } else {
        iToString(dollars, stock->price.dollars, 2);
    }

    strcat(outputLine, dollars);

    strcat(outputLine, ".");
    /* Amount of cents must not exceed two digits */
    iToString(cents, stock->price.cents, 1);
    strcat(outputLine, cents);

    /* Add an extra 0 onto the price if there are 0 cents */
    if (stock->price.cents == 0) {
        strcat(outputLine, "0");
    }

    strcat(outputLine, "|");
    /* Amount of stock items must not exceed two digits */

    iToString(quantity, stock->onHand, 2);
    strcat(outputLine, quantity);
}

/**
 * Loads the coin file data into the system.
 **/
Boolean loadCoins(VmSystem * system, const char * fileName)
{
    FILE *coinFile;
    char coinLine[MAX_COIN_LINE_LEN] = "";
    int i;

    if (!fileExists(fileName)) {
        puts("Error: File not found!");

        return FALSE;
    }

    /* Open the file for read only access */
    coinFile = fopen(fileName, "r");

    /* While there is another line to read, continue reading lines
     * and generating Coin instances from them*/
    for (i=0; fgets(coinLine, MAX_COIN_LINE_LEN, coinFile) != NULL; i++) {

        if (strcmp(coinLine, "\n") == 0) {
            break;
        }

        getCoinFromLine(coinLine, &system->cashRegister[i]);
    }

    fclose(coinFile);

    return TRUE;
}

/**
 * Saves all the stock back to the stock file.
 **/
Boolean saveStock(VmSystem * system)
{
    FILE *file;
    int i;

    /* Remove the stock file */
    remove(system->stockFileName);

    /* Recreate stock file and open for read / write access */
    file = fopen(system->stockFileName, "w+");

    for (i = 1; i <= system->itemList->size; i++) {
        Stock *currentStock = getNthNode(system->itemList, i)->data;

        char outputLine[MAX_STOCK_LINE_LEN] = "";
        createLineFromStock(currentStock, outputLine);

        fprintf(file, "%s\n", outputLine);
    }

    fclose(file);

    return TRUE;
}

/**
 * Saves all the coins back to the coins file.
 **/
Boolean saveCoins(VmSystem * system)
{
    FILE *file;
    int i;

    /* Remove the coin file */
    remove(system->coinFileName);

    /* Recreate coin file and open for read / write access */
    file = fopen(system->coinFileName, "w+");

    for (i = 0; i < LEN(system->cashRegister); i++) {
        char outputLine[MAX_COIN_LINE_LEN] = "";
        getLineFromCoin(system->cashRegister[i], outputLine);

        fprintf(file, "%s\n", outputLine);
    }

    fclose(file);

    return TRUE;
}

/**
 * This option allows the user to display the items in the system.
 * This is the data loaded into the linked list in the requirement 2.
 **/
void displayItems(VmSystem * system)
{
    int i, j;
    /* Amount of characters in each word */
    int idLength = 2, nameLength = 4, quantityLength = 9, priceLength = 5;
    int currentIDLength, currentNameLength, currentQuantityLength, currentPriceLength;
    Stock **stock = malloc(system->itemList->size * sizeof(Stock));

    printf("Items Menu\n\n");

    /* Determine the minimum column sizes */
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

    printf("%-*s | %-*s | %-*s | %-*s\n", idLength, "ID", nameLength, "Name",
           quantityLength, "Available", priceLength, "Price");

    /* Print the dashes to separate the heading from the data */
    printNDashes(idLength + nameLength + quantityLength + priceLength + COLUMN_SPACES);
    puts(EMPTY_STRING);

    /* Add all current node stocks to the stock array */
    for (i = 1; i <= system->itemList->size; i++) {
        stock[i-1] = getNthNode(system->itemList, i)->data;
    }

    /* Sort the stocks array by name alphabetically */
    for (i = 0; i < system->itemList->size; i++) {
        for (j = i + 1; j < system->itemList->size; j++) {
            /* If the second stock's name is higher alphabetically,
             * swap the two stocks around in the array */
            if (strcmp(stock[i]->name, stock[j]->name) > 0) {
                Stock *temp = stock[i];
                stock[i] = stock[j];
                stock[j] = temp;
            }
        }
    }

    /* Print out each stock item on their own row, showing ID, stock amount,
     * quantity, and price */
    for (i = 0; i < system->itemList->size; i++) {
        Stock *currentStock = stock[i];

        printf("%-*s | %-*s | %-*d | %d.%02d\n", idLength, currentStock->id, nameLength, currentStock->name,
               quantityLength, currentStock->onHand, currentStock->price.dollars, currentStock->price.cents);
    }

    free(stock);
}

/**
 * This option allows the user to purchase an item.
 * This function implements requirement 5 of the assignment specification.
 **/
void purchaseItem(VmSystem * system)
{
    Stock *stock;
    char input[ID_LEN] = "", cashInput[PRICE_LEN+NEW_LINE_SPACE] = "";
    int amountOwed, originalAmount;
    Price cashLeft, refund, change;

    puts("Purchase item");
    puts("-------------");
    printf("Please enter the id of the item you wish to purchase: ");

    getUserInput(input, ID_LEN);

    /* If the user inputs a newline, return to the menu */
    if (strcmp(input, EMPTY_STRING) == 0) {
        return;
    }

    /* If the specified stock exists... */
    stock = getStockWithID(input, system->itemList);
    if (stock) {
        if (stock->onHand > 0) {
            printf("You have selected \"%s\t%s\". This will cost you $%d.%02d.\n", stock->name,
                   stock->desc, stock->price.dollars, stock->price.cents);

            puts("Please hand over the money – type in the value of each note/coin in cents.\n"
                         "Press enter on a new and empty line to cancel this purchase:");

            originalAmount = getDecimalValue(stock->price);
            amountOwed = getDecimalValue(stock->price);
            cashLeft = getPriceFromValue(amountOwed);

            while (amountOwed > 0) {
                printf("You still need to give us $%d.%02d: ", cashLeft.dollars, cashLeft.cents);
                getUserInput(cashInput, PRICE_LEN);

                /* If the user enters a newline, refund user and go back
                 * to the menu */
                if (strcmp(cashInput, EMPTY_STRING) == 0) {
                    refund = getPriceFromValue(originalAmount-amountOwed);

                    if (originalAmount-amountOwed > 0) {
                        refund = getPriceFromValue(originalAmount-amountOwed);

                        if (changeCanBeGiven(refund, system)) {
                            printf("Order cancelled. Here is your $%d.%02d back:",
                                   refund.dollars, refund.cents);

                            printChange(refund, system);
                        } else {
                            printf("Unable to give correct change. Order cancelled.\n"
                                           "Here is your $%d.%02d back.\n", refund.dollars, refund.cents);
                        }
                    } else {
                        puts("Order cancelled.");
                    }

                    return;
                }

                if (isValidDenomination(cashInput, system)) {
                    amountOwed -= toInt(cashInput);
                    addCoin(toDenom(toInt(cashInput)), system);
                    cashLeft = getPriceFromValue(amountOwed);
                } else {
                    Price cashEntered = getPriceFromValue(toInt(cashInput));

                    printf("Error: $%d.%02d is not a valid denomination of money.\n",
                           cashEntered.dollars, cashEntered.cents);
                }
            }

            change = getPriceFromValue(-1*amountOwed);

            if (amountOwed == 0) {
                printf("Thank you. Here is your %s\n", stock->name);

                stock->onHand--;
            } else if (amountOwed < 0 && changeCanBeGiven(change, system)) {
                printf("Thank you. Here is your %s, and your change of $%d.%02d:",
                       stock->name, change.dollars, change.cents);

                printChange(change, system);
                puts(".\nPlease come back soon.");

                stock->onHand--;
            } else {
                printf("Unable to give correct change. Order cancelled.\n"
                               "Here is your $%d.%02d back.\n", change.dollars, change.cents);
            }
        } else {
            puts("We're out of stock on that item sorry!");
        }
    } else {
        puts("Stock doesn't exist!");
    }
}

/**
 * You must save all data to the data files that were provided on the command
 * line when the program loaded up, display goodbye and free the system.
 * This function implements requirement 6 of the assignment specification.
 **/
void saveAndExit(VmSystem * system)
{
    puts("\nGoodbye! Please come back soon!");

    saveStock(system);
    saveCoins(system);

    systemFree(system);

    exit(EXIT_SUCCESS);
}

/**
 * This option adds an item to the system. This function implements
 * requirement 7 of of assignment specification.
 **/
void addItem(VmSystem * system)
{
    /* In the list, it is ordered from lowest ID to highest.
            * As such, the highest node will have the highest ID,
            * thus adding one to it will yield the ID that will be created*/
    int newID = getValueOfID(getNthNode(system->itemList,
                                        system->itemList->size)->data->id)+1;
    Price amount;
    char name[NAME_LEN] = "", description[DESC_LEN] = "",
            price[PRICE_LEN+1] = "", buffer[ID_LEN] = "",
            *dollars, *cents;
    Stock *newStock = malloc(sizeof(Stock));


    char generatedID[ID_LEN+1] = "I";
    /* The numerical value of the ID is only 4 digits, so subtract 1
     * when passing it in */
    iToString(buffer, newID, ID_LEN - 1);
    strcat(generatedID, buffer);


    printf("This new meal item will have an ID of %s\n", generatedID);
    printf("Enter the item name: ");
    getUserInput(name, NAME_LEN);
    if (strcmp(name, EMPTY_STRING) == 0) {
        return;
    }

    printf("Enter the item description: ");
    getUserInput(description, DESC_LEN);
    if (strcmp(description, EMPTY_STRING) == 0) {
        return;
    }

    printf("Enter the price for this item: ");
    getUserInput(price, sizeof(price));

    if (strcmp(price, EMPTY_STRING) == 0) {
        return;
    }
    while (TRUE) {
        /* If the entered price has a . in it */
        if (strchr(price, '.' )) {
            dollars = strtok(price, ".");
            cents = strtok(NULL, ".");

            if ((strlen(dollars) == 1 || strlen(dollars) == 2)
                && strlen(cents) == 2) {

                amount.dollars = (unsigned int) toInt(dollars);
                amount.cents = (unsigned int) toInt(cents);

                if (amount.dollars < 10 || (amount.dollars == 10 && amount.cents == 0)) {
                    break;
                }
            }
        }

        printf("Price entered was invalid! Please enter a valid price: ");
        getUserInput(price, sizeof(price));
    }

    strcpy(newStock->id, generatedID);
    strcpy(newStock->name, name);
    strcpy(newStock->desc, description);
    newStock->price = amount;
    newStock->onHand = DEFAULT_STOCK_LEVEL;

    addNode(system->itemList, newStock);

    printf("This item \"%s - %s\" has now been added to the menu.\n",
        name, description);
}

/**
 * Remove an item from the system, including free'ing its memory.
 * This function implements requirement 8 of the assignment specification.
 **/
void removeItem(VmSystem * system)
{
    char id[ID_LEN+EXTRA_SPACES] = "";
    Stock *toBeRemoved;

    printf("Enter the item id of the item to remove from the menu: ");
    getUserInput(id, sizeof(id));

    if (strcmp(id, EMPTY_STRING) == 0) {
        return;
    }

    toBeRemoved = getStockWithID(id, system->itemList);

    if (toBeRemoved == NULL) {
        puts("Item doesn't exist!");

        return;
    }

    printf("\"%s - %s\t%s\" has been removed from the system.\n",
           toBeRemoved->id, toBeRemoved->name, toBeRemoved->desc);

    removeNode(id, system->itemList);
    free(toBeRemoved);
}

/**
 * This option will require you to display the coins from lowest to highest
 * value and the counts of coins should be correctly aligned.
 * This function implements part 4 of requirement 18 in the assignment
 * specifications.
 **/
void displayCoins(VmSystem * system)
{

    printf("Denomination | Count\n");
    printf("%-*s | %d\n", DENOM_COL_LEN, "5 cents", getCoin(toDenom(5), system)->count);
    printf("%-*s | %d\n", DENOM_COL_LEN, "10 cents", getCoin(toDenom(10), system)->count);
    printf("%-*s | %d\n", DENOM_COL_LEN, "20 cents", getCoin(toDenom(20), system)->count);
    printf("%-*s | %d\n", DENOM_COL_LEN, "50 cents", getCoin(toDenom(50), system)->count);
    printf("%-*s | %d\n", DENOM_COL_LEN, "1 dollar", getCoin(toDenom(100), system)->count);
    printf("%-*s | %d\n", DENOM_COL_LEN, "2 dollars", getCoin(toDenom(200), system)->count);
    printf("%-*s | %d\n", DENOM_COL_LEN, "5 dollars", getCoin(toDenom(500), system)->count);
    printf("%-*s | %d\n", DENOM_COL_LEN, "10 dollars", getCoin(toDenom(1000), system)->count);
}

/**
 * This option will require you to iterate over every stock in the
 * list and set its onHand count to the default value specified in
 * the startup code.
 * This function implements requirement 9 of the assignment specification.
 **/
void resetStock(VmSystem * system)
{
    int i;

    for (i = 1; i <= system->itemList->size; i++) {
        getNthNode(system->itemList, i)->data->onHand = DEFAULT_STOCK_LEVEL;
    }

    printf("All stock has been reset to the default level of %d\n", DEFAULT_STOCK_LEVEL);
}

/**
 * This option will require you to iterate over every coin in the coin
 * list and set its 'count' to the default value specified in the
 * startup code.
 * This requirement implements part 3 of requirement 18 in the
 * assignment specifications.
 **/
void resetCoins(VmSystem * system)
{
    int i;

    for (i = 0; i < LEN(system->cashRegister); i++) {
        system->cashRegister[i].count = DEFAULT_COIN_COUNT;
    }

    printf("All coins have been reset to the default level of %d\n", DEFAULT_COIN_COUNT);
}

/**
 * This option will require you to display goodbye and free the system.
 * This function implements requirement 10 of the assignment specification.
 **/
void abortProgram(VmSystem * system)
{
    puts("Goodbye!");

    systemFree(system);

    exit(EXIT_SUCCESS);
}
