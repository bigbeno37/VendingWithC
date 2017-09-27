/**************************************************************

** Student Name: Ben O'Sullivan

** Student Number: s3662617

** Date of submission: Wednesday, 27 Sept 2017

** Course: COSC1076 / COSC2207, Semester 2, 2017

***************************************************************/

#ifndef VM_OPTIONS_H
#define VM_OPTIONS_H

#include "vm_stock.h"

Boolean systemInit(VmSystem * system);
void systemFree(VmSystem * system);
Boolean loadData(
    VmSystem * system, const char * stockFileName, const char * coinsFileName);
Boolean loadStock(VmSystem * system, const char * fileName);
Boolean loadCoins(VmSystem * system, const char * fileName);
Boolean saveStock(VmSystem * system);
Boolean saveCoins(VmSystem * system);

void displayItems(VmSystem * system);
void purchaseItem(VmSystem * system);
void saveAndExit(VmSystem * system);
void addItem(VmSystem * system);
void removeItem(VmSystem * system);
void displayCoins(VmSystem * system);
void resetStock(VmSystem * system);
void resetCoins(VmSystem * system);
void abortProgram(VmSystem * system);

void createStockFromLine(char *line, Stock *newStock);
void createLineFromStock(Stock *stock, char *outputLine);

/*
 * The amount of extra characters in the displayed price
 * $ + .XX
 * Dollar sign + space + period + cents to two decimals = 5
 */
#define EXTRA_CHAR_IN_PRICE 5

/*
 * Spaces left over from the column padding
 * Each bit of padding adds three extra spaces
 * 3 columns to pad * 3 spaces = 9 extra spaces
 */
#define COLUMN_SPACES 9

#endif
