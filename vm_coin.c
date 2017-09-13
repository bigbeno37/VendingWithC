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
Boolean isValidDenomination(int value, VmSystem *system) {
    int i;

    for (i = 0; i < LEN(system->cashRegister); i++) {
        if (value == system->cashRegister[i].count) {
            return TRUE;
        }
    }

    return FALSE;
}