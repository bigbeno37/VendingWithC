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
Boolean isValidDenomination(char *value, VmSystem *system) {
    int i, coinValue = toInt(value);

    for (i = 0; i < LEN(system->cashRegister); i++) {
        if (coinValue == system->cashRegister[i].count) {
            return TRUE;
        }
    }

    return FALSE;
}

int getDecimalValue(Price price) {
    return 100*price.dollars + price.cents;
}