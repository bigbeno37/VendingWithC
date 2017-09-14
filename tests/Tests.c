#include <stdio.h>
#include "../vm.h"
#include "TestLinkedList.h"
#include "TestLoadData.h"
#include "TestUtils.h"
#include "TestCoins.h"

/*
 * Reflects if all tests have passed; if one fails, then this
 * will change to false
 */
Boolean allTestsPassed = TRUE;

/*
 * assertThat two integers are equal
 */
void iAssertThat(char *assertion, int expected, int actual) {
    if (expected != actual) {
        printf("There was an error in test: %s\n", assertion);
        allTestsPassed = FALSE;
    }
}

/*
 * assertThat two strings are equivalent
 */
void sAssertThat(char *assertion, char *expected, char *actual) {
    if (strcmp(expected, actual) != 0) {
        printf("There was an error in test: %s\n", assertion);
        allTestsPassed = FALSE;
    }
}

/*
 * assertThat the value passed in is NULL
 */
void assertNull(char *assertion, void *actual) {
    if (actual) {
        printf("There was an error in test: %s\n", assertion);
        allTestsPassed = FALSE;
    }
}

/*
 * assertThat the value passed in is not NULL
 */
void assertNotNull(char *assertion, void *actual) {
    if (!actual) {
        printf("There was an error in test: %s\n", assertion);
        allTestsPassed = FALSE;
    }
}

/*
 * assertThat the value passed in is TRUE
 */
void assertTrue(char *assertion, Boolean actual) {
    if (!actual) {
        printf("There was an error in test: %s\n", assertion);
        allTestsPassed = FALSE;
    }
}

/*
 * assertThat the value passed in is FALSE
 */
void assertFalse(char *assertion, Boolean actual) {
    if (actual) {
        printf("There was an error in test: %s\n", assertion);
        allTestsPassed = FALSE;
    }
}

/*
 * The main location where all tests are run
 */
void run_tests() {
    copyStringCorrectlyCopiesString();

    getSizeWillCorrectlyReturnSize();
    getNodeWillCorrectlyReturnNode();
    nodeWithIDExistsWillCorrectlyReturnIfSpecifiedNodeExists();

    loadStockCorrectlyLoadsStock();
    createStockFromLineCorrectlyCreatesStock();

    isValidDenominationWillDetermineValidDenomination();
    getDecimalValueWillCorrectlyDetermineCorrectValue();
    getPriceFromValueWillCorrectlyReturnPrice();

    if(!allTestsPassed) {
        puts("There were errors running tests!");
    }
}