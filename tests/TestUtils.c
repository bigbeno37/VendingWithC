#include "TestUtils.h"
#include "Tests.h"
#include "../utility.h"

/*
 * Determine if iToString will correctly return a string with
 * the number passed in
 */
void iToStringCorrectlyReturnsNumber() {

    char *buffer = malloc(2 + NULL_SPACE);

    iToString(buffer, 3, 1);
    sAssertThat("3 should return '3'", "3", buffer);

    strcpy(buffer, "");
    iToString(buffer, 12, 2);
    sAssertThat("12 should return '12'", "12", buffer);

    free(buffer);
}

/*
 * Determine if getValueOfID will correctly translate an ID
 * of format IXXXX where X is a number into an int
 */
void getValueOfIDCorrectlyReturnsValue() {
    iAssertThat("I0001 will return a value of 1", 1, getValueOfID("I0001"));
    iAssertThat("I9999 will return a value of 9999", 9999, getValueOfID("I9999"));
}