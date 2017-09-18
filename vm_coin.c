#include "vm_coin.h"

/**
 * Implement functions here for managing coins and the
 * "cash register" contained in the VmSystem struct.
 **/

/**
 * Some example functions:
 * init coins array, insert coin, change coin count for Denomination,
 * convert Denomination to coin value, deducting coins from register, etc...
 */

/*
 * Determine if the passed in value is a valid denomination as
 * found in the coins array
 */
Boolean isValidDenomination(char *value, VmSystem *system) {
    switch(toInt(value)) {
        case 5:
        case 10:
        case 20:
        case 50:
        case 100:
        case 200:
        case 500:
        case 1000:
            return TRUE;
        default:
            return FALSE;
    }
}

/*
 * Returns the decimal value of a Price instance
 */
int getDecimalValue(Price price) {
    return 100*price.dollars + price.cents;
}

/*
 * Returns a price instance created from the amountOfCents passed in
 */
Price getPriceFromValue(int amountOfCents) {
    Price price;
    /* Discard the last two digits */
    price.dollars = (unsigned int) (amountOfCents / 100.0f);
    price.cents = amountOfCents - price.dollars * 100;

    return price;
}

void getCoinFromLine(char *line, Coin *newCoin) {
    char *denomination = strtok(line, COIN_DELIM);
    char *count = strtok(NULL, COIN_DELIM);

    switch(toInt(denomination)) {
        case 5:
            newCoin->denom = FIVE_CENTS;
            break;
        case 10:
            newCoin->denom = TEN_CENTS;
            break;
        case 20:
            newCoin->denom = TWENTY_CENTS;
            break;
        case 50:
            newCoin->denom = FIFTY_CENTS;
            break;
        case 100:
            newCoin->denom = ONE_DOLLAR;
            break;
        case 200:
            newCoin->denom = TWO_DOLLARS;
            break;
        case 500:
            newCoin->denom = FIVE_DOLLARS;
            break;
        case 1000:
            newCoin->denom = TEN_DOLLARS;
            break;
        default:
            break;
    }

    newCoin->count = (unsigned int) toInt(count);
}