/**************************************************************

** Student Name: Ben O'Sullivan

** Student Number: s3662617

** Date of submission: Wednesday, 27 Sept 2017

** Course: COSC1076 / COSC2207, Semester 2, 2017

***************************************************************/

#ifndef VM_SYSTEM_H
#define VM_SYSTEM_H

#include "utility.h"

/**
 * The length of the id string not counting the nul terminator.
 **/
#define ID_LEN 5

/**
 * The maximum length of a product name not counting the nul terminator.
 **/
#define NAME_LEN 40

/**
 * The maximum length of a product description not counting the nul terminator.
 **/
#define DESC_LEN 255

/**
 * The number of denominations of currency available in the system.
 **/
#define NUM_DENOMS 8

/*
 * The max length of the price of an item
 */
#define PRICE_LEN 4

/*
 * The max length of the quantity of an item
 */
#define ITEM_LEN 2

/*
 * The amount of seperators ( '|' ) in the stock file
 */
#define STOCK_SEPERATORS 4

/*
 * The maximum length of a valid line of input for a stock file
 * +1 to include a newline character
 */
#define MAX_STOCK_LINE_LEN (ID_LEN + NAME_LEN + DESC_LEN + PRICE_LEN + ITEM_LEN + STOCK_SEPERATORS + 1)

/*
 * The maximum length of a valid line of input for a coin file
 * +1 to include a newline character
 */
#define MAX_COIN_LINE_LEN (7 + 1)

/*
 * The maximum length of a denomination column
 */
#define DENOM_COL_LEN 12

/**
 * A structure to represent a price. One of the problems with the floating
 * point formats in C like float and double is that they have minor issues
 * of inaccuracy due to rounding. In the case of currency this really is
 * not acceptable so we introduce our own type to keep track of currency.
 **/
typedef struct price
{
    unsigned dollars;
    unsigned cents;
} Price;

/**
 * Stores data for a stock item.
 **/
typedef struct stock
{
    char id[ID_LEN + NULL_SPACE];
    char name[NAME_LEN + NULL_SPACE];
    char desc[DESC_LEN + NULL_SPACE];
    Price price;
    unsigned onHand;
} Stock;

/**
 * The node that holds the data about an item stored in memory.
 **/
typedef struct node
{
    Stock * data;
    struct node * next;
} Node;

/**
 * The list of products - each link in the list is a Node.
 **/
typedef struct list
{
    Node * head;
    unsigned size;
} List;

/**
 * Enumeration representing the various types of currency available.
 **/
typedef enum denomination
{
    FIVE_CENTS, TEN_CENTS, TWENTY_CENTS, FIFTY_CENTS, ONE_DOLLAR,
    TWO_DOLLARS, FIVE_DOLLARS, TEN_DOLLARS
} Denomination;

/**
 * Represents a coin type stored in the cash register. Each demonination
 * will have exactly one of these in the cash register.
 **/
typedef struct coin
{
    Denomination denom;
    unsigned count;
} Coin;

/**
 * This is the header structure for all the datatypes that are
 * passed around and manipulated.
 **/
typedef struct vm_system
{
    /**
     * The container for all the money in the system.
     **/
    Coin cashRegister[NUM_DENOMS];

    /**
     * The linked list.
     **/
    List * itemList;

    /**
     * The name of the stock file.
     **/
    const char * stockFileName;

    /**
     * The name of the coin file.
     **/
    const char * coinFileName;
} VmSystem;

#endif
