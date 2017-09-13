#include "vm_menu.h"

/**
 * vm_menu.c handles the initialisation and management of the menu array.
 **/

/**
 * In this function you need to initialise the array of menu items
 * according to the text to be displayed for the menu. This array is
 * an array of MenuItem with text and a pointer to the function
 * that will be called.
 **/
void initMenu(MenuItem * menu)
{
    MenuItem displayAll, purchaseItems, exit, add, remove, coins, resetStockValues, resetCoinStock, abort;
    strcpy(displayAll.text, "Display Items");
    displayAll.function = displayItems;

    strcpy(purchaseItems.text, "Purchase Items");
    purchaseItems.function = purchaseItem;

    strcpy(exit.text, "Save amd Exit");
    exit.function = saveAndExit;

    strcpy(add.text, "Add Item");
    add.function = addItem;

    strcpy(remove.text, "Remove Item");
    remove.function = removeItem;

    strcpy(coins.text, "Display Coins");
    coins.function = displayCoins;

    strcpy(resetStockValues.text, "Reset Stock");
    resetStockValues.function = resetStock;

    strcpy(resetCoinStock.text, "Reset Coins");
    resetCoinStock.function = resetCoins;

    strcpy(abort.text, "Abort Program");
    abort.function = abortProgram;

    menu[0] = displayAll;
    menu[1] = purchaseItems;
    menu[2] = exit;
    menu[3] = add;
    menu[4] = remove;
    menu[5] = coins;
    menu[6] = resetStockValues;
    menu[7] = resetCoinStock;
    menu[8] = abort;
}

/**
 * Gets input from the user and returns a pointer to the MenuFunction
 * that defines how to perform the user's selection. NULL is returned
 * if an invalid option is entered.
 **/
MenuFunction getMenuChoice(MenuItem * menu)
{
    Boolean correctInput = FALSE;
    int choice;
    char *buffer = copyString(EMPTY_STRING);

    while ( !correctInput ) {
        correctInput = TRUE;

        /* Get the input and store it in name */
        fgets( buffer, CHOICE_SIZE, stdin );

        /* If name doesn't have a newline character (and thus the input was bigger than 20) */
        /* remove overflowed characters and ask for new input */
        if ( !strchr( buffer, '\n' )) {
            printf( "\nBuffer overflow! Please enter a valid choice: " );
            readRestOfLine();

            correctInput = FALSE;
        }
    }

    choice = toInt(buffer);

    return menu[choice-1].function;
}

/* Iterate through all menu items, and display them
 * to the screen */
void displayMenu(MenuItem *menu) {
    int i;

    for (i = 0; i < NUMBER_OF_MENU_ITEMS; i++) {

        if (i == 0) {
            puts("Main Menu:");
        } else if (i == 3) {
            puts("Administrator-Only Menu:");
        }

        printf("%i. %s\n", i+1, menu[i].text);
    }
}
