/**************************************************************

** Student Name: Ben O'Sullivan

** Student Number: s3662617

** Date of submission: Wednesday, 27 Sept 2017

** Course: COSC1076 / COSC2207, Semester 2, 2017

***************************************************************/

#ifndef VM_STOCK_H
#define VM_STOCK_H

#include "vm_coin.h"

/**
 * The default stock level that all new stock should start with and the value
 * to use when restting stock.
 **/
#define DEFAULT_STOCK_LEVEL 20

#define STOCK_DELIM "|"

unsigned int getListSize(List *list);
void addNode(List *list, Stock *data);
Node *getNthNode(List *list, int n);
Stock *getStockWithID(char *id, List *list);
void removeNode(char *id, List *list);

#endif
