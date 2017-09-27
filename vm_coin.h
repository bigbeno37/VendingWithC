/**************************************************************

** Student Name: Ben O'Sullivan

** Student Number: s3662617

** Date of submission: Wednesday, 27 Sept 2017

** Course: COSC1076 / COSC2207, Semester 2, 2017

***************************************************************/

#ifndef VM_COIN_H
#define VM_COIN_H

#include "vm_system.h"

/**
 * The default coin level used when resetting values.
 **/
#define DEFAULT_COIN_COUNT 20

#define COIN_DELIM ","

Boolean isValidDenomination(char *value, VmSystem *system);
int getDecimalValue(Price price);
Price getPriceFromValue(int amountOfCents);

void getCoinFromLine(char *line, Coin *coin);
void printChange(Price price, VmSystem *system);
Boolean changeCanBeGiven(Price price, VmSystem *system);
void addCoin(Denomination denom, VmSystem *system);
Denomination toDenom(int value);
Coin *getCoin(Denomination denom, VmSystem *system);
void getLineFromCoin(Coin coin, char *line);

#endif
