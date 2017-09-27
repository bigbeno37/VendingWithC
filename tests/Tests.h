/**************************************************************

** Student Name: Ben O'Sullivan

** Student Number: s3662617

** Date of submission: Wednesday, 27 Sept 2017

** Course: COSC1076 / COSC2207, Semester 2, 2017

***************************************************************/

#ifndef VENDINGWITHC_TESTS_H
#define VENDINGWITHC_TESTS_H

#include "../utility.h"

void run_tests();
void iAssertThat(char *assertion, int expected, int actual);
void sAssertThat(char *assertion, char *expected, char *actual);
void assertNull(char *assertion, void *actual);
void assertNotNull(char *assertion, void *actual);
void assertTrue(char *assertion, Boolean actual);

#endif