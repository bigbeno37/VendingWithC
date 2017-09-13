/*
 * Created by bigbeno37 on 13/09/17.
 */

#include "vm_coin.h"

#ifndef VENDINGWITHC_VM_LINKEDLIST_H
#define VENDINGWITHC_VM_LINKEDLIST_H

#endif

void addNode(List *list, Stock *data);
unsigned int getListSize(List *list);
Node *getNthNode(List *list, int index);
Stock *getStockWithID(char *id, List *list);