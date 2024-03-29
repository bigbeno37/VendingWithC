/**************************************************************

** Student Name: Ben O'Sullivan

** Student Number: s3662617

** Date of submission: Wednesday, 27 Sept 2017

** Course: COSC1076 / COSC2207, Semester 2, 2017

***************************************************************/

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

    strcpy(exit.text, "Save and Exit");
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
    char choiceStr[1 + NEW_LINE_SPACE];
    int choice = 0;
/*
    while (choice == 0) {
        strcpy(choiceStr, "");
        getUserInput(choiceStr, CHOICE_SIZE);
        choice = toInt(choiceStr);

        if (strcmp(choiceStr, "") == 0) {
            printf("\nSelect your option (1-9): ");
        } else if(choice < 1 || choice > 9) {
            printf("Invalid choice!");
        }
    }
*/
    getUserInput(choiceStr, CHOICE_SIZE);
    choice = toInt(choiceStr);

    while (choice < 1) {
        printf("Invalid choice! Please enter a valid choice: ");
        getUserInput(choiceStr, CHOICE_SIZE);
        choice = toInt(choiceStr);
    }

    return menu[choice-1].function;
}

/* Iterate through all menu items, and display them
 * to the screen */
void displayMenu(MenuItem *menu) {
    int i;

    for (i = 0; i < NUMBER_OF_MENU_ITEMS; i++) {

        if (i == 0) {
            puts("\nMain Menu:");
        } else if (i == 3) {
            puts("Administrator-Only Menu:");
        }

        printf("%i. %s\n", i+1, menu[i].text);
    }
}
