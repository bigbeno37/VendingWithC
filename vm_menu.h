/**************************************************************

** Student Name: Ben O'Sullivan

** Student Number: s3662617

** Date of submission: Wednesday, 27 Sept 2017

** Course: COSC1076 / COSC2207, Semester 2, 2017

***************************************************************/

#ifndef VM_MENU_H
#define VM_MENU_H

#include "vm_options.h"

/**
 * The maximum length of a menu item's text.
 **/
#define MENU_NAME_LEN 50

/*
 * Amount of menu options to be selected
 */
#define NUMBER_OF_MENU_ITEMS 9

/**
 * Represents a function that can be selected from the list of
 * menu_functions - creates a new type called a menu_function.
 */
typedef void (*MenuFunction)(VmSystem *);

/**
 * Represents a menu item to be displayed and executed in the program.
 **/
typedef struct menu_item
{
    char text[MENU_NAME_LEN + NULL_SPACE];
    MenuFunction function;
} MenuItem;

void initMenu(MenuItem * menu);
MenuFunction getMenuChoice(MenuItem * menu);
void displayMenu(MenuItem *menu);

#endif
