#ifndef VENDINGWITHC_TESTS_H
#define VENDINGWITHC_TESTS_H

#include "../utility.h"

void run_tests();
void iAssertThat(char *assertion, int expected, int actual);
void sAssertThat(char *assertion, char *expected, char *actual);
void assertNull(char *assertion, void *actual);
void assertNotNull(char *assertion, void *actual);
void assertTrue(char *assertion, Boolean actual);
void assertFalse(char *assertion, Boolean actual);

#endif