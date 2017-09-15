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

    if (!fileExists((char *) fileName)) {
        puts("Error: File not found!");

        return FALSE;
    }

    /* Open the file for read only access */
    stockFile = fopen(fileName, "r");

    /* While there is another line to read, continue reading lines
     * and generating Stock instances from them*/
    while (fgets(stockData, MAX_STOCK_LINE_LEN, stockFile) != NULL) {
        Stock *stock = createStockFromLine(stockData);

        /* For each stock instance created, at it to the linked list */
        addNode(system->itemList, stock);
    }

    fclose(stockFile);

    return TRUE;
}

/*
 * Return a stock instance based on the line input
 */
Stock *createStockFromLine(char *line) {
    char separator[2] = "|";
    char priceSeparator[2] = ".";

    char *lineCopy = copyString(line);

    char *id = strtok(lineCopy, separator);
    char *name = strtok(NULL, separator);
    char *description = strtok(NULL, separator);
    char *priceString = strtok(NULL, separator);
    char *quantityString = strtok(NULL, separator);

    char *dollarsString = strtok(priceString, priceSeparator);
    char *centsString = strtok(NULL, priceSeparator);

    unsigned int dollars = (unsigned int) toInt(dollarsString);
    unsigned int cents = (unsigned int) toInt(centsString);

    unsigned int quantity = (unsigned int) toInt(quantityString);
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

/*
 * Takes in a stock instance and returns a formatted string containing
 * the stock's information
 */
char *createLineFromStock(Stock *stock) {
    char formattedOutput[MAX_STOCK_LINE_LEN] = "";

    strcat(formattedOutput, stock->id);
    strcat(formattedOutput, "|");
    strcat(formattedOutput, stock->name);
    strcat(formattedOutput, "|");
    strcat(formattedOutput, stock->desc);
    strcat(formattedOutput, "|");
    /* Amount of dollars must not exceed two digits */
    strcat(formattedOutput, iToString(stock->price.dollars, 2));
    strcat(formattedOutput, ".");
    /* Amount of cents must not exceed two digits */
    strcat(formattedOutput, iToString(stock->price.cents, 2));

    /* Add an extra 0 onto the price if there are 0 cents */
    if (stock->price.cents == 0) {
        strcat(formattedOutput, "0");
    }

    strcat(formattedOutput, "|");
    /* Amount of stock items must not exceed two digits */
    strcat(formattedOutput, iToString(stock->onHand, 2));

    return copyString(formattedOutput);
}

/**
 * Loads the coin file data into the system.
 **/
Boolean loadCoins(VmSystem * system, const char * fileName)
{
    /* TODO
     Load in denominations from file */
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
    FILE *file;
    int i;

    /* Remove the stock file */
    remove(system->stockFileName);

    /* Recreate stock file and open for read / write access */
    file = fopen(system->stockFileName, "w+");

    for (i = 1; i <= system->itemList->size; i++) {
        Stock *currentStock = getNthNode(system->itemList, i)->data;

        fprintf(file, "%s\n", createLineFromStock(currentStock));
    }

    fclose(file);

    return TRUE;
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
    /* Amount of characters in each word */
    int idLength = 2, nameLength = 4, quantityLength = 9, priceLength = 5;
    int currentIDLength, currentNameLength, currentQuantityLength, currentPriceLength;

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

    /* Print each column with the respective spacing required */
    printf("ID");
    printNSpaces((int) (idLength - strlen("ID")));
    printf(" | Name");
    printNSpaces((int) (nameLength - strlen("Name")));
    printf(" | Available");
    printNSpaces((int) (quantityLength - strlen("Available")));
    printf(" | Price");
    printNSpaces((int) (priceLength - strlen("Price")));
    puts(EMPTY_STRING);

    /* Print the dashes to separate the heading from the data */
    printNDashes(idLength + nameLength + quantityLength + priceLength + COLUMN_SPACES);
    puts(EMPTY_STRING);

    /* Print out each stock item on their own row, showing ID, stock amount,
     * quantity, and price */
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
    char *input, *cashInput;
    int amountOwed, originalAmount;
    Price cashLeft, refund;

    puts("Purchase item");
    puts("-------------");
    printf("Please enter the id of the item you wish to purchase: ");

    input = getUserInput(ID_LEN);

    /* If the user inputs a newline, return to the menu */
    if (strcmp(input, EMPTY_STRING) == 0) {
        puts("Returning to main menu...");
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
                cashInput = getUserInput(4);

                /* If the user enters a newline, refund user and go back
                 * to the menu */
                if (strcmp(cashInput, EMPTY_STRING) == 0) {
                    refund = getPriceFromValue(originalAmount-amountOwed);

                    if (originalAmount-amountOwed > 0) {
                        refund = getPriceFromValue(originalAmount-amountOwed);

                        printf("Order cancelled. Here is your $%d.%02d back.\n",
                               refund.dollars, refund.cents);
                    } else {
                        puts("Order cancelled.");
                    }

                    return;
                }

                if (isValidDenomination(cashInput, system)) {
                    amountOwed -= toInt(cashInput);
                    cashLeft = getPriceFromValue(amountOwed);
                } else {
                    Price cashEntered = getPriceFromValue(toInt(cashInput));

                    printf("Error: $%d.%02d is not a valid denomination of money.\n",
                           cashEntered.dollars, cashEntered.cents);
                }
            }

            stock->onHand = stock->onHand - 1;

            printf("Thank you. Here is your %s", stock->name);

            if (amountOwed < 0) {
                Price change = getPriceFromValue(-1*amountOwed);

                printf(", and your change of $%d.%02d", change.dollars, change.cents);
            }

            puts(".\nPlease come back soon.");
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

    exit(EXIT_SUCCESS);
}

/**
 * This option adds an item to the system. This function implements
 * requirement 7 of of assignment specification.
 **/
void addItem(VmSystem * system)
{
    printf("This new meal item will have an ID of I%04d\n",
           /* In the list, it is ordered from lowest ID to highest.
            * As such, the highest node will have the highest ID,
            * thus adding one to it will yield the ID that will be created*/
           getValueOfID(getNthNode(system->itemList, system->itemList->size)->data->id)+1);
}

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
