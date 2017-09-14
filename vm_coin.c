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
    int i, coinValue = toInt(value);

    for (i = 0; i < LEN(system->cashRegister); i++) {
        if (coinValue == system->cashRegister[i].count) {
            return TRUE;
        }
    }

    return FALSE;
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