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

/*
 * Converts the passed in value to a Denomination if applicable
 */
Denomination toDenom(int value) {
    switch (value) {
        case 5:
            return FIVE_CENTS;
        case 10:
            return TEN_CENTS;
        case 20:
            return TWENTY_CENTS;
        case 50:
            return FIFTY_CENTS;
        case 100:
            return ONE_DOLLAR;
        case 200:
            return TWO_DOLLARS;
        case 500:
            return FIVE_DOLLARS;
        case 1000:
            return TEN_DOLLARS;
        default:
            return 0;
    }
}

/*
 * Converts a line passed in to a Coin instance
 */
void getCoinFromLine(char *line, Coin *newCoin) {
    char *denomination = strtok(line, COIN_DELIM);
    char *count = strtok(NULL, COIN_DELIM);

    newCoin->denom = toDenom(toInt(denomination));

    newCoin->count = (unsigned int) toInt(count);
}

/*
 * Get a specific coin instance in the system based on its
 * denomination
 */
Coin *getCoin(Denomination denom, VmSystem *system) {
    int i;

    for (i = 0; i < LEN(system->cashRegister); i++) {
        if (system->cashRegister[i].denom == denom) {
            return &system->cashRegister[i];
        }
    }

    return NULL;
}

/*
 * Returns if change of a specific denomination exists eg. 5 cents
 */
Boolean changeAvailable(Denomination denom, VmSystem *system) {
    if (getCoin(denom, system)->count > 0) {
        return TRUE;
    }

    return FALSE;
}

/*
 * Removes a singular coin of a specific denomination from the system
 */
void removeCoin(Denomination denom, VmSystem *system) {
    getCoin(denom, system)->count--;
}

/*
 * Adds a singular coin of a specific denomination to the system
 */
void addCoin(Denomination denom, VmSystem *system) {
    getCoin(denom, system)->count++;
}

/*
 * Identifies if change is able to be given to the user
 */
Boolean changeCanBeGiven(Price price, VmSystem *system) {
    int dollars = price.dollars, cents = price.cents;

    VmSystem copy = *system;

    while (dollars > 0) {
        if (dollars - 10 >= 0 && changeAvailable(TEN_DOLLARS, system)) {
            dollars -= 10;

            removeCoin(TEN_DOLLARS, &copy);
        } else if (dollars - 5 >= 0 && changeAvailable(FIVE_DOLLARS, system)) {
            dollars -= 5;

            removeCoin(FIVE_DOLLARS, &copy);
        } else if (dollars - 2 >= 0 && changeAvailable(TWO_DOLLARS, system)) {
            dollars -= 2;

            removeCoin(TWO_DOLLARS, &copy);
        } else if (dollars - 1 >= 0 && changeAvailable(ONE_DOLLAR, system)) {
            dollars -= 1;

            removeCoin(ONE_DOLLAR, &copy);
        } else {
            return FALSE;
        }
    }

    while (cents > 0) {
        if (cents - 50 >= 0 && changeAvailable(FIFTY_CENTS, system)) {
            cents -= 50;

            removeCoin(FIFTY_CENTS, &copy);
        } else if (cents - 20 >= 0 && changeAvailable(TWENTY_CENTS, system)) {
            cents -= 20;

            removeCoin(TWENTY_CENTS, &copy);
        } else if (cents - 10 >= 0 && changeAvailable(TEN_CENTS, system)) {
            cents -= 10;

            removeCoin(TEN_CENTS, &copy);
        } else if (cents - 5 >= 0 && changeAvailable(FIVE_CENTS, system)) {
            cents -= 5;

            removeCoin(FIVE_CENTS, &copy);
        } else {
            return FALSE;
        }
    }

    return TRUE;
}

/*
 * Given a price, print off each coin necessary to reach 'price's value. In the
 * process, this function also removes a coin of a specific denomination from
 * the system
 */
void printChange(Price price, VmSystem *system) {
    int dollars = price.dollars, cents = price.cents;

    while (dollars > 0) {
        if (dollars - 10 >= 0 && changeAvailable(TEN_DOLLARS, system)) {
            dollars -= 10;

            printf(" $10");
            removeCoin(TEN_DOLLARS, system);
        } else if (dollars - 5 >= 0 && changeAvailable(FIVE_DOLLARS, system)) {
            dollars -= 5;

            printf(" $5");
            removeCoin(FIVE_DOLLARS, system);
        } else if (dollars - 2 >= 0 && changeAvailable(TWO_DOLLARS, system)) {
            dollars -= 2;

            printf(" $2");
            removeCoin(TWO_DOLLARS, system);
        } else if (dollars - 1 >= 0 && changeAvailable(ONE_DOLLAR, system)) {
            dollars -= 1;

            printf(" $1");
            removeCoin(ONE_DOLLAR, system);
        }
    }

    while (cents > 0) {
        if (cents - 50 >= 0 && changeAvailable(FIFTY_CENTS, system)) {
            cents -= 50;

            printf(" 50c");
            removeCoin(FIFTY_CENTS, system);
        } else if (cents - 20 >= 0 && changeAvailable(TWENTY_CENTS, system)) {
            cents -= 20;

            printf(" 20c");
            removeCoin(TWENTY_CENTS, system);
        } else if (cents - 10 >= 0 && changeAvailable(TEN_CENTS, system)) {
            cents -= 10;

            printf(" 10c");
            removeCoin(TEN_CENTS, system);
        } else if (cents - 5 >= 0 && changeAvailable(FIVE_CENTS, system)) {
            cents -= 5;

            printf(" 5c");
            removeCoin(FIVE_CENTS, system);
        }
    }
}