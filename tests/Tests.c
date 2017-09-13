/*
 * Created by bigbeno37 on 12/09/17.
 */

#include <stdio.h>
#include "../vm.h"
#include "TestLinkedList.h"
#include "TestLoadData.h"
#include "TestUtils.h"
#include "TestCoins.h"

Boolean allTestsPassed = TRUE;

void iAssertThat(char *assertion, int expected, int actual) {
    if (expected != actual) {
        printf("There was an error in test: %s\n", assertion);
        allTestsPassed = FALSE;
    }
}

void sAssertThat(char *assertion, char *expected, char *actual) {
    if (strcmp(expected, actual)) {
        printf("There was an error in test: %s\n", assertion);
        allTestsPassed = FALSE;
    }
}

void assertNull(char *assertion, void *actual) {
    if (actual) {
        printf("There was an error in test: %s\n", assertion);
        allTestsPassed = FALSE;
    }
}

void assertNotNull(char *assertion, void *actual) {
    if (!actual) {
        printf("There was an error in test: %s\n", assertion);
        allTestsPassed = FALSE;
    }
}

void assertTrue(char *assertion, Boolean actual) {
    if (!actual) {
        printf("There was an error in test: %s\n", assertion);
        allTestsPassed = FALSE;
    }
}

void assertFalse(char *assertion, Boolean actual) {
    if (actual) {
        printf("There was an error in test: %s\n", assertion);
        allTestsPassed = FALSE;
    }
}

void run_tests() {
    copyStringCorrectlyCopiesString();

    getSizeWillCorrectlyReturnSize();
    getNodeWillCorrectlyReturnNode();
    nodeWithIDExistsWillCorrectlyReturnIfSpecifiedNodeExists();

    loadStockCorrectlyLoadsStock();
    createStockFromLineCorrectlyCreatesStock();

    isValidDenominationWillDetermineValidDenomination();
    getDecimalValueWillCorrectlyDetermineCorrectValue();

    if(!allTestsPassed) {
        puts("There were errors running tests!");
    }
}