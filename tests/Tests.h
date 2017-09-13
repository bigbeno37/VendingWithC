/*
 * Created by bigbeno37 on 12/09/17.
 */

#ifndef VENDINGWITHC_TESTS_H
#define VENDINGWITHC_TESTS_H

#endif

#include "../utility.h"

void run_tests();
void assertThat(char *assertion, void *expected, void *actual);
void iAssertThat(char *assertion, int expected, int actual);
void sAssertThat(char *assertion, char *expected, char *actual);
void assertNull(char *assertion, void *actual);
void assertNotNull(char *assertion, void *actual);