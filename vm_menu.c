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
    MenuItem displayAll;
    strcpy(displayAll.text, "Display Items");
    displayAll.function = displayItems;

    MenuItem purchaseItems;
    strcpy(purchaseItems.text, "Purchase Items");
    purchaseItems.function = purchaseItem;

    MenuItem exit;
    strcpy(exit.text, "Save amd Exit");
    exit.function = saveAndExit;

    MenuItem add;
    strcpy(add.text, "Add Item");
    add.function = addItem;

    MenuItem remove;
    strcpy(remove.text, "Remove Item");
    remove.function = removeItem;

    MenuItem coins;
    strcpy(coins.text, "Display Coins");
    coins.function = displayCoins;

    MenuItem resetStockValues;
    strcpy(resetStockValues.text, "Reset Stock");
    resetStockValues.function = resetStock;

    MenuItem resetCoinStock;
    strcpy(resetCoinStock.text, "Reset Coins");
    resetCoinStock.function = resetCoins;

    MenuItem abort;
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
    return NULL;
}
