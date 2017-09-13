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