//
// Created by bigbeno37 on 12/09/17.
//

#include <stdio.h>
#include "../vm.h"
#include "TestLinkedList.h"

Boolean allTestsPassed = TRUE;

void assertThat(char *assertion, void *expected, void *actual) {
    if (expected != actual) {
        printf("There was an error in test: %s\n", assertion);
        allTestsPassed = FALSE;
    }
}

void fAssertThat(char *assertion, float expected, float actual) {
    if (expected != actual) {
        printf("There was an error in test: %s\n", assertion);
        allTestsPassed = FALSE;
    }
}

void dAssertThat(char *assertion, double expected, double actual) {
    if (expected != actual) {
        printf("There was an error in test: %s\n", assertion);
        allTestsPassed = FALSE;
    }
}

void iAssertThat(char *assertion, int expected, int actual) {
    if (expected != actual) {
        printf("There was an error in test: %s\n", assertion);
        allTestsPassed = FALSE;
    }
}

void sAssertThat(char *assertion, char *expected, char *actual) {
    if (strcmp(expected, actual) != 0) {
        printf("There was an error in test: %s\n", assertion);
        allTestsPassed = FALSE;
    }
}

void run_tests() {
    getSizeWillCorrectlyReturnSize();
    getNodeWillCorrectlyReturnNode();

    if(!allTestsPassed) {
        puts("There were errors running tests!");
    }
}